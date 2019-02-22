#include "pch.h"
#include "AUIApplication.h"

#if defined( _MSC_VER )
#   include "AUIMFCApplication.h"
#else
#   error Implement OS dependent Impl
#endif

#include "AUIWidgetTreeHelper.h"
#include "AUIWindow.h"
#include "AUIInstance.h"
#include "AUIWidgetManager.h"
#include "AUIAsyncTask.h"
#include "AUIWidget.h"
#include "AUILazyTask.h"
#include "AUILazyTaskManager.h"
#include "AUIDebug.h"

class AUIWindowLazyDeleteTask final : public AUILazyTask
{
public:
    AUIWindowLazyDeleteTask(const std::shared_ptr< AUIWindow >& pWindow) : m_pWindow(pWindow) {}
    ~AUIWindowLazyDeleteTask() override = default;

    //////////////////////////////////////////////////////////////////////////
    // ModelessDialog
private:
    std::shared_ptr<AUIWindow> m_pWindow;


    //////////////////////////////////////////////////////////////////////////
    // Run
protected:
    void OnExecute() override
    {
        // Nothing (Automatically deallocated by shared_ptr)
    }
};

class TooltipForm : public AUIForm
{
public:
    TooltipForm()
    {
        SetVisible(false);
        SetNonActivate(true);
        SetTopMost(true);
    }
    ~TooltipForm() override = default;
private:
};


AUIApplication::AUIApplication()
    : m_pImpl(std::make_unique<Impl>() )
    , m_pWidgetTree(std::make_unique<AUIWidgetTreeHelper>() )
    , m_pLazyTaskManager(std::make_unique<AUILazyTaskManager>() )
    , m_bVisualizeLayout( false )
    , m_bTraceWidgetLifecycle( false )
    , m_bInUpdateInstanceTask( false )
    , m_bInitialized(false)
{
    m_arrWidgetLazyTask.reserve( 200 );
    SkGraphics::Init();
}

AUIApplication::~AUIApplication()
{
    m_Windows.clear();
    m_RegisteredWindows.clear();
}

AUIApplication& AUIApplication::Instance()
{
    static AUIApplication sApplication;
    return sApplication;
}

AUIWidgetTreeHelper& AUIApplication::GetWidgetTree() const
{
    return *m_pWidgetTree;
}

void AUIApplication::Refresh()
{
    RefreshSignal.Send();
}

void AUIApplication::RunLazyUpdate()
{
    std::vector< std::shared_ptr< AUIAsyncTask > > arrEndedAsyncTask;
    for ( auto asyncTask : m_setAsyncExecute )
    {
        if ( asyncTask->IsPublishedProgress() )
        {
            asyncTask->ProgressUpdate();
        }

        if ( false == asyncTask->IsRunning() )
        {
            if ( asyncTask->IsCancelled() )
            {
                // Task cancelled
                asyncTask->Cancelled();
            }
            else
            {
                // Task ended
                asyncTask->PostExecute();
            }

            arrEndedAsyncTask.emplace_back( asyncTask );
        }
    }
    for ( auto asyncTask : arrEndedAsyncTask )
    {
        m_setAsyncExecute.erase( asyncTask );
    }



    LazyUpdateSignal.Send();

    m_pLazyTaskManager->RunTasks();

    AfterLazyUpdateSignal.Send();

    // Tooltip
    for ( const auto& pWidgetManager : m_setWidgetManager )
    {
        pWidgetManager->LazyUpdateTooltip();
    }
}

void AUIApplication::PostLazyUpdate()
{
    PostLazyUpdateSignal.Send();
}

void AUIApplication::RegisterWindow( const std::shared_ptr< AUIWindow >& pWindow )
{
    RegisterWindow( pWindow, nullptr );
}

void AUIApplication::RegisterWindow( const std::shared_ptr< AUIWindow >& pWindow, const std::shared_ptr< AUIWindow >& pParent )
{
    if ( pWindow == nullptr )
    {
        AUIAssertFailReason("Invalid window");
        return;
    }
    if ( IsRegisteredWindow( pWindow ) == true )
    {
        AUIAssertFailReason("Already registered window");
        return;
    }

    const auto found = m_Windows.find( pParent.get() );
    if ( found != m_Windows.end() )
    {
        found->second.emplace_back( pWindow );
    }
    else
    {
        m_Windows[pParent.get()].emplace_back( pWindow );
    }
    m_RegisteredWindows.emplace( pWindow.get(), pParent );
}

void AUIApplication::UnregisterWindow( const std::shared_ptr< AUIWindow >& pWindow )
{
    if ( pWindow == nullptr )
    {
        AUIAssertFailReason("Invalid window");
        return;
    }
    if ( IsRegisteredWindow( pWindow ) == false )
    {
        AUIAssertFailReason("Unregistered window");
        return;
    }

    const auto& childFound = m_Windows.find( pWindow.get() );
    if ( childFound != m_Windows.end() )
    {
        const auto children = childFound->second;   // Copy
        for ( auto& child : children )
        {
            UnregisterWindow( child );
        }
        m_Windows.erase( childFound );
    }


    const auto parentFound = m_RegisteredWindows.find( pWindow.get() );
    const auto& listFound = m_Windows.find( parentFound->second.lock().get() );
    if ( listFound == m_Windows.end() )
    {
        AUIAssertFailReason("Can't be here!");
        return;
    }
    const auto& windowFound = std::find_if( listFound->second.begin(), listFound->second.end(), [pWindow]( const std::weak_ptr< AUIWindow >& pR )->bool {
        return ( pR.lock() == pWindow );
    } );
    if ( windowFound == listFound->second.end() )
    {
        AUIAssertFailReason("Can't be here!");
        return;
    }
    listFound->second.erase( windowFound );
    m_RegisteredWindows.erase( parentFound );

    m_pLazyTaskManager->PushTask(std::make_shared<AUIWindowLazyDeleteTask>( pWindow ) );

    PostLazyUpdate();
}

void AUIApplication::UnregisterAllWindows()
{
    for ( auto& winlist : m_Windows )
    {
        for ( auto& window : winlist.second )
        {
            m_pLazyTaskManager->PushTask(std::make_shared< AUIWindowLazyDeleteTask >( window ) );
        }
    }
    m_Windows.clear();
    m_RegisteredWindows.clear();

    PostLazyUpdate();

}

bool AUIApplication::IsRegisteredWindow( const std::shared_ptr< AUIWindow >& pWindow ) const
{
    return ( m_RegisteredWindows.find( pWindow.get() ) != m_RegisteredWindows.end() );
}

AUIHandle* const AUIApplication::GetApplicationHandle() const
{
    return GetImpl()->GetApplicationHandle();
}

void AUIApplication::GetApplicationSize( int& width, int& height ) const
{
    GetImpl()->GetApplicationSize( width, height );
}

void AUIApplication::GetApplicationPosition( int& x, int& y ) const
{
    GetImpl()->GetApplicationPosition( x, y );
}

void AUIApplication::GetApplicationPositionAndSize( int& x, int& y, int& width, int& height ) const
{

    GetImpl()->GetApplicationPositionAndSize( x, y, width, height );
}

std::wstring AUIApplication::GetApplicationDirectory() const
{
    return GetImpl()->GetApplicationDirectory();
}

AUIHandle* const AUIApplication::GetDesktopHandle() const
{
    return GetImpl()->GetDesktopHandle();
}

void AUIApplication::GetDesktopSize( int& width, int& height ) const
{
    GetImpl()->GetDesktopSize( width, height );
}

void AUIApplication::GetMonitorCount( int& count ) const
{
    GetImpl()->GetMonitorCount( count );
}

void AUIApplication::GetVirtualScreenSize( int& width, int& height ) const
{
    GetImpl()->GetVirtualScreenSize( width, height );
}

void AUIApplication::GetMousePosition( int& x, int& y ) const
{
    GetImpl()->GetMousePosition( x, y );
}

void AUIApplication::GetMouseDragOffset( int& x, int& y ) const
{
    GetImpl()->GetMouseDragOffset( x, y );
}

bool AUIApplication::IsMouseRightHanded() const
{
    return GetImpl()->IsMouseRightHanded();
}

void AUIApplication::AttachWidgetManager( AUIWidgetManager* const pWidgetManager )
{
    if ( nullptr == pWidgetManager )
    {
        AUIAssertFailReason("WidgetManager is null");
        return;
    }
    const auto found = m_setWidgetManager.find( pWidgetManager );
    if ( m_setWidgetManager.end() != found )
    {
        AUIAssertFailReason("WidgetManager is already attached!");
        return;
    }

    m_setWidgetManager.emplace( pWidgetManager );
}

void AUIApplication::DetachWidgetmanager( AUIWidgetManager* const pWidgetManager )
{
    if ( nullptr == pWidgetManager )
    {
        AUIAssertFailReason("Null WidgetManager");
        return;
    }
    const auto found = m_setWidgetManager.find( pWidgetManager );
    if ( m_setWidgetManager.end() == found )
    {
        AUIAssertFailReason("WidgetManager is not attached!");
        return;
    }

    this->ClearInstance( pWidgetManager );
    this->RunUpdateInstanceTask();

    m_setWidgetManager.erase( found );
}

void AUIApplication::ConvertToDesktopPos( int& desktopX, int& desktopY, const int x, const int y, AUIHandle* const pHandle )
{
    GetImpl()->ConvertToDesktopPos( desktopX, desktopY, x, y, pHandle );
}

void AUIApplication::GetMonitorRectFromPoint( SkRect& monitorRect, const int& desktopX, const int& desktopY )
{
    GetImpl()->GetMonitorRectFromPoint( monitorRect, desktopX, desktopY );
}

void AUIApplication::CreateInstance( AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget )
{
    if ( nullptr == pWidgetManager )
    {
        AUIAssertFailReason("Invalid widget manager");
        return;
    }
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    if ( pWidget->IsInstanced() && pWidget->m_LifeState.IsPendingDestory() == false )
    {
        AUIAssertFailReason("Already instance but not to be destroyed");
        return;
    }

    pWidget->m_LifeState.SetPendingCreate( true );
    pWidget->m_LifeState.SetPendingCreateWidgetManager( pWidgetManager );


    m_arrWidgetLazyTask.emplace_back( WidgetLazyTask::MakeCreate( pWidget, pWidgetManager ) );


    const auto arrChildren = AUIApplication::Instance().GetWidgetTree().GetChildren( pWidget.get() );
    for ( auto child = arrChildren.rbegin() ; child != arrChildren.rend() ; child++ )
    {
        this->CreateInstance( pWidgetManager, *child );
    }
}

void AUIApplication::DestroyInstance( AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget )
{
    if ( nullptr == pWidgetManager )
    {
        AUIAssertFailReason("Invalid widget manager");
        return;
    }
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    if ( pWidget->IsInstanced() == false && pWidget->m_LifeState.IsPendingCreate() == false )
    {
        AUIAssertFailReason("Not instanced and not to be created");
        return;
    }


    const auto arrChildren = AUIApplication::Instance().GetWidgetTree().GetChildren( pWidget.get() );
    for ( auto child = arrChildren.rbegin() ; child != arrChildren.rend() ; child++ )
    {
        this->DestroyInstance( pWidgetManager, *child );
    }

    pWidget->m_LifeState.SetPendingDestroy( true );
    pWidget->m_LifeState.SetPendingDestroyWidgetManager( pWidgetManager );


    m_arrWidgetLazyTask.emplace_back( WidgetLazyTask::MakeDestroy( pWidget, pWidgetManager ) );

}

void AUIApplication::ClearInstance( AUIWidgetManager* const pWidgetManager )
{
    if ( nullptr == pWidgetManager )
    {
        AUIAssertFailReason("Invalid widget manager");
        return;
    }


    // Clear Pending Task for WidgetManager
    std::vector< WidgetLazyTask > arrTmpWidgetLazyTask;
    arrTmpWidgetLazyTask.reserve( m_arrWidgetLazyTask.size() );
    for ( const auto& lazyTask : m_arrWidgetLazyTask )
    {
        if ( pWidgetManager != lazyTask.fWidgetManager )
            arrTmpWidgetLazyTask.emplace_back( lazyTask );
    }
    m_arrWidgetLazyTask = std::move( arrTmpWidgetLazyTask );

    for ( auto& instance : pWidgetManager->m_Instances )
    {
        this->DestroyInstance( pWidgetManager, instance->GetWidget()->shared_from_this() );
    }
}

void AUIApplication::RunUpdateInstanceTask()
{
    // Prevent recursive call (This method can be called multiple times)
    if ( m_bInUpdateInstanceTask )
        return;
    m_bInUpdateInstanceTask = true;


    do 
    {
        if ( m_arrWidgetLazyTask.size() == 0 )
            break;

        struct _PendingData
        {
            AUIWidget* fWidget;
            AUIWidgetManager* fWidgetManager;

            _PendingData() noexcept : fWidget( nullptr ), fWidgetManager( nullptr ) {}
            _PendingData( AUIWidget* const _pWidget, AUIWidgetManager* const _pWidgetManager ) noexcept
                : fWidget( _pWidget ), fWidgetManager( _pWidgetManager ) {}
            _PendingData( const WidgetLazyTask& _lazyTask ) noexcept
                : fWidget( _lazyTask.fWidget.get() ), fWidgetManager( _lazyTask.fWidgetManager ) {}
            _PendingData( _PendingData&& _other ) noexcept
                : fWidget( _other.fWidget ), fWidgetManager( _other.fWidgetManager ) {}

            bool operator==( const _PendingData& _data ) const noexcept
            {
                return ( this->fWidget == _data.fWidget &&
                    this->fWidgetManager == _data.fWidgetManager );
            }
            bool operator<( const _PendingData& _data ) const noexcept
            {
                return ( this->fWidget < _data.fWidget );
            }
        };
        std::vector< WidgetLazyTask > arrPendingTask;
        arrPendingTask.reserve( m_arrWidgetLazyTask.size() );

        std::set< _PendingData > setPendingDestroy;

        for ( const auto& lazyTask : m_arrWidgetLazyTask )
        {
            const auto pWidget = lazyTask.fWidget;
            const auto pWidgetManager = lazyTask.fWidgetManager;
            const auto taskType = lazyTask.fTaskType;
            if ( nullptr == pWidget )
            {
                AUIAssertFailReason("No Widget");
                continue;
            }

            if ( WidgetLazyTask::kCreate_TaskType == taskType )
            {
                // Merge Destroy->Create
                const auto foundDestroy = std::find_if( arrPendingTask.begin(), arrPendingTask.end(), [lazyTask]( const WidgetLazyTask& _otherTask )->bool {
                    return ( WidgetLazyTask::kDestroy_TaskType == _otherTask.fTaskType &&
                        lazyTask.fWidget == _otherTask.fWidget &&
                        lazyTask.fWidgetManager == _otherTask.fWidgetManager );
                } );
                if ( arrPendingTask.end() != foundDestroy )
                {
                    const auto foundParentDestroy = std::find_if( arrPendingTask.begin(), arrPendingTask.end(), [lazyTask]( const WidgetLazyTask& _otherTask )->bool {
                        return ( WidgetLazyTask::kDestroy_TaskType == _otherTask.fTaskType &&
                            lazyTask.fWidget->GetParent() == _otherTask.fWidget.get() &&
                            lazyTask.fWidgetManager == _otherTask.fWidgetManager );
                    } );
                    if ( arrPendingTask.end() != foundParentDestroy )
                    {
                        // Do not merge Destroy->Create
                        continue;
                    }

                    arrPendingTask.erase( foundDestroy );
                    if ( false == pWidget->IsInstanced() )
                        setPendingDestroy.emplace( lazyTask );
                    continue;
                }

                // Merge Create->Create
                const auto foundCreate = std::find_if( arrPendingTask.begin(), arrPendingTask.end(), [lazyTask]( const WidgetLazyTask& _otherTask )->bool {
                    return ( WidgetLazyTask::kCreate_TaskType == _otherTask.fTaskType &&
                        lazyTask.fWidget == _otherTask.fWidget &&
                        lazyTask.fWidgetManager == _otherTask.fWidgetManager );
                } );
                if ( arrPendingTask.end() != foundCreate )
                {
                    continue;
                }

                const auto foundPendingDestroy = setPendingDestroy.find( lazyTask );
                if ( setPendingDestroy.end() != foundPendingDestroy )
                {
                    setPendingDestroy.erase( foundPendingDestroy );
                }

                // Check widget manager change
                if ( pWidget->IsInstanced() )
                {
                    if ( pWidget->GetWidgetManager() == lazyTask.fWidgetManager )
                    {
                        continue;
                    }
                }
                arrPendingTask.emplace_back( lazyTask );
            }
            else if ( WidgetLazyTask::kDestroy_TaskType == taskType )
            {
                // Merge Create->Destroy
                const auto foundCreate = std::find_if( arrPendingTask.begin(), arrPendingTask.end(), [lazyTask]( const WidgetLazyTask& _otherTask )->bool {
                    return ( WidgetLazyTask::kCreate_TaskType == _otherTask.fTaskType &&
                        lazyTask.fWidget == _otherTask.fWidget &&
                        lazyTask.fWidgetManager == _otherTask.fWidgetManager );
                } );
                if ( arrPendingTask.end() != foundCreate )
                {
                    arrPendingTask.erase( foundCreate );
                    setPendingDestroy.emplace( lazyTask );
                    continue;
                }


                // Merge Destroy->Destroy
                const auto foundDestroy = std::find_if( arrPendingTask.begin(), arrPendingTask.end(), [lazyTask]( const WidgetLazyTask& _otherTask )->bool {
                    return ( WidgetLazyTask::kDestroy_TaskType == _otherTask.fTaskType &&
                        lazyTask.fWidget == _otherTask.fWidget &&
                        lazyTask.fWidgetManager == _otherTask.fWidgetManager );
                } );
                if ( arrPendingTask.end() != foundDestroy )
                {
                    continue;
                }

                const auto foundPendingDestroy = setPendingDestroy.find( lazyTask );
                if ( setPendingDestroy.end() != foundPendingDestroy )
                {
                    continue;
                }

                arrPendingTask.emplace_back( lazyTask );
            }
            else
            {
                // NOTE : Nothing to do
            }
        }

        for ( const auto& lazyTask : arrPendingTask )
        {
            if ( WidgetLazyTask::kCreate_TaskType == lazyTask.fTaskType )
            {
                if (2 >= lazyTask.fWidget.use_count() && lazyTask.fWidget->IsRoot())
                {
                    AUIDebugPrint("Grabage Widget > name : %s, child count : %d, pointer : %p\n",
                        typeid(*lazyTask.fWidget).name(),
                        lazyTask.fWidget->GetChildren().size(),
                        lazyTask.fWidget.get());
                    continue;
                }
                this->OnRunLazyCreateInstance( lazyTask.fWidgetManager, lazyTask.fWidget );
            }
            else if ( WidgetLazyTask::kDestroy_TaskType == lazyTask.fTaskType )
            {
                this->OnRunLazyDestroyInstance( lazyTask.fWidgetManager, lazyTask.fWidget );
            }
            else
            {
                // NOTE : Nothing to do
            }

        }

    } while ( false );

    m_arrWidgetLazyTask.clear();

    // Prevent recursive call
    m_bInUpdateInstanceTask = false;
}

void AUIApplication::OnRunLazyCreateInstance( AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget )
{
    if ( nullptr == pWidgetManager )
    {
        AUIAssertFailReason("Invalid widget manager");
        return;
    }
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    // Create instance
    pWidgetManager->RegisterWidget( pWidget );
}

void AUIApplication::OnRunLazyDestroyInstance( AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget )
{
    if ( nullptr == pWidgetManager )
    {
        AUIAssertFailReason("Invalid widget manager");
        return;
    }
    if ( nullptr == pWidget )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    pWidgetManager->UnregisterWidget( pWidget );
}

void AUIApplication::AsyncExecute( const std::shared_ptr< AUIAsyncTask >& pAsyncTask )
{
    if ( nullptr == pAsyncTask )
    {
        AUIAssertFailReason("Task is null");
        return;
    }
    if ( pAsyncTask->IsRunning() )
    {
        AUIAssertFailReason("Already executed");
        return;
    }
    if ( m_setAsyncExecute.end() != m_setAsyncExecute.find( pAsyncTask ) )
    {
        AUIAssertFailReason("Already executed!");
        return;
    }

    m_setAsyncExecute.insert( pAsyncTask );

    PostLazyUpdate();
}

void AUIApplication::DebugPrintTreeInfo_Private( AUIWidget* pWidget, int step /*= 0 */ ) const
{
    std::stringstream ss;
    if ( nullptr == pWidget )
    {
        ss << "(null) widget";
        return;
    }

    const auto funcPrintStep = []( std::stringstream& _ss, int step )->void {
        for ( int _idx = 0 ; _idx < step ; _idx++ )
            _ss << " ";
    };

    funcPrintStep( ss, step ); ss << typeid(*pWidget).name() << "\n";

    AUIDebugPrint("%s", ss.str().c_str());

    const auto children = pWidget->GetChildren();
    for ( auto& child : children )
    {
        DebugPrintTreeInfo_Private( child.get(), step + 1 );
    }
}

void AUIApplication::MainRefresh()
{
    RefreshMainSignal.Send();
}

bool AUIApplication::Initialize()
{
    m_bInitialized = true;

    return IsInitialized();
}

bool AUIApplication::Finalize()
{
    m_bInitialized = false;
    return !IsInitialized();
}

bool AUIApplication::InitializeTooltip()
{
    if (m_pTooltipForm)
    {
        if (m_pTooltipForm->IsActivated())
            m_pTooltipForm->Deactivate();
    }
    m_pTooltipForm = std::make_shared<TooltipForm>();
    m_pTooltipForm->SetNonActivate(true);
    m_pTooltipForm->SetTopMost(true);
    m_pTooltipForm->Activate();

    return true;
}

void AUIApplication::RunInstanceGarbageCollection()
{
    const auto& widgettree = GetWidgetTree();
    for (const auto& [widget, relation] : widgettree.m_mapWidgetRelation)
    {
        AUIAssert(widget);
        auto pWidget = widget->shared_from_this();
        if (pWidget->IsRoot())
        {
            if (pWidget->IsInstanced())
            {
                const auto cnt = pWidget.use_count();
                // Least reference count : pWidget (1) + WidgetTree (1) = 2
                if (2 == cnt)
                {
                    auto pWidgetManager = pWidget->GetWidgetManager();
                    this->DestroyInstance(pWidgetManager, pWidget);
                }
            }
        }
    }

}

AUIApplication::WidgetLazyTask::WidgetLazyTask(const TaskType& _taskType, const std::shared_ptr< AUIWidget >& _widget, AUIWidgetManager* const _widgetManager) noexcept
    : fTaskType(_taskType)
    , fWidget(_widget)
    , fWidgetManager(_widgetManager)
{

}

AUIApplication::WidgetLazyTask AUIApplication::WidgetLazyTask::MakeCreate(const std::shared_ptr< AUIWidget >& _widget, AUIWidgetManager* const _widgetManager) noexcept
{
    WidgetLazyTask _newTask(kCreate_TaskType, _widget, _widgetManager);
    return _newTask;
}

AUIApplication::WidgetLazyTask AUIApplication::WidgetLazyTask::MakeDestroy(const std::shared_ptr< AUIWidget >& _widget, AUIWidgetManager* const _widgetManager) noexcept
{
    WidgetLazyTask _newTask(kDestroy_TaskType, _widget, _widgetManager);
    return _newTask;
}

AUIApplicationAutoInit::AUIApplicationAutoInit()
{
    AUIApplication::Instance().Initialize();
}

AUIApplicationAutoInit::~AUIApplicationAutoInit()
{
    AUIApplication::Instance().Finalize();
}
