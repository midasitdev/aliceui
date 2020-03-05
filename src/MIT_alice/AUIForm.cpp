#include "pch.h"
#include "AUIForm.h"
#include "AUIHandle.h"

#if defined( _MSC_VER )
#include "AUIMFCWindowHandle.h"
#else
#   error Implement handle
#endif

AUIForm::AUIForm()
{
#if defined( _MSC_VER )
    m_pHandle = std::make_shared<AUIMFCWindowHandle>();
#else
#   error Implement handle
#endif
}

AUIForm::AUIForm( AUIForm&& form )
    : m_pHandle( std::move( form.m_pHandle ) )
{
#if defined( _MSC_VER )
    form.m_pHandle = std::make_shared<AUIMFCWindowHandle>();
#else
#   error Implement handle
#endif
}

AUIForm::~AUIForm()
{

}

void AUIForm::SetRootWidget( const std::shared_ptr< AUIWidget >& pWidget )
{
    GetHandle()->SetRootWidget( pWidget );
}

void AUIForm::Activate()
{
    GetHandle()->Activate();
    OnActivate();
}

void AUIForm::Activate( AUIForm* const pParent )
{
    AUIHandle* pParentHandle = nullptr;
    if ( pParent )
        pParentHandle = pParent->GetHandle();
    Activate( pParentHandle );
    OnActivate();
}

void AUIForm::Activate( AUIHandle* const pHandle )
{
    GetHandle()->Activate( pHandle );
    OnActivate();
}

void AUIForm::ActivateModal()
{
    GetHandle()->ActivateModal();
    OnActivate();
}

void AUIForm::ActivateModal(AUIHandle* const pHandle)
{
    GetHandle()->ActivateModal(pHandle);
    OnActivate();
}

void AUIForm::ActivateModal(AUIForm* const pParent)
{
    AUIHandle* pParentHandle = nullptr;
    if (pParent)
        pParentHandle = pParent->GetHandle();
    GetHandle()->ActivateModal(pParentHandle);
    OnActivate();
}

void AUIForm::Deactivate()
{
    GetHandle()->Deactivate();
    OnDeactivate();
}

bool AUIForm::IsActivated() const
{
    return GetHandle()->IsActivated();
}

void AUIForm::OnActivate()
{

}

void AUIForm::OnDeactivate()
{

}

void AUIForm::SetSize( int width, int height )
{
    GetHandle()->SetSize( width, height );
}

void AUIForm::SetPosition( int x, int y )
{
    GetHandle()->SetPosition( x, y );
}

void AUIForm::SetPositionAndSize( int x, int y, int width, int height )
{
    GetHandle()->SetPositionAndSize( x, y, width, height );
}

void AUIForm::GetSize( int& width, int& height )
{
    GetHandle()->GetSize( width, height );
}

void AUIForm::GetPosition( int& x, int& y )
{
    GetHandle()->GetPosition( x, y );
}

void AUIForm::SetTitle( const std::wstring& title )
{
    GetHandle()->SetTitle( title );
}

std::wstring AUIForm::GetTitle() const
{
    return GetHandle()->GetTitle();
}

void AUIForm::CaptureMouseEvent()
{
    GetHandle()->CaptureMouseEvent();
}

void AUIForm::ReleaseMouseEvent()
{
    GetHandle()->ReleaseMouseEvent();
}

void AUIForm::DoShowMinimized()
{
    GetHandle()->DoShowMinimized();
}

void AUIForm::DoShowMaximized()
{
    GetHandle()->DoShowMaximized();
}

void AUIForm::DoShowDefault()
{
    GetHandle()->DoShowDefault();
}

void AUIForm::SetMode( AUIHandleMode mode )
{
    GetHandle()->SetMode( mode );
}

void AUIForm::SetVisible( bool state )
{
    GetHandle()->SetVisible( state );
}

void AUIForm::SetFocus()
{
    GetHandle()->SetFocus();
}

bool AUIForm::IsNonActivate() const
{
    return GetHandle()->IsNonActivate();
}

void AUIForm::SetNonActivate( bool val )
{
    GetHandle()->SetNonActivate( val );
}

bool AUIForm::IsTopMost() const
{
    return GetHandle()->IsTopMost();
}

void AUIForm::SetTopMost( bool val )
{
    GetHandle()->SetTopMost( val );
}

void AUIForm::Invalidate()
{
    GetHandle()->Invalidate();
}

void AUIForm::UpdateWindow()
{

}

bool AUIForm::IsResizeable() const
{
    return GetHandle()->IsResizeable();
}

void AUIForm::SetResizeable(bool val)
{
    GetHandle()->SetResizeable(val);
}

void AUIForm::SetMinSize(int width, int height)
{
    GetHandle()->SetMinSize(width, height);
}

void AUIForm::SetMaxSize(int width, int height)
{
    GetHandle()->SetMaxSize(width, height);
}

void AUIForm::SetSubWindowType(const SUB_WINDOW_TYPE& type)
{
    GetHandle()->SetSubWindowType(type);
}

SUB_WINDOW_TYPE AUIForm::GetSubWindowType() const
{
    return GetHandle()->GetSubWindowType();
}

void AUIForm::SetTransparent(bool val)
{
    GetHandle()->SetTransparent(val);
}

bool AUIForm::IsTransparent() const
{
    return GetHandle()->IsTransparent();
}
