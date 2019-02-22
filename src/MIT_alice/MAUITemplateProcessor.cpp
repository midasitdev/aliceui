#include "pch.h"
#include "MAUITemplateProcessor.h"
#include "MAUITemplate.h"
#include "AUILinearLayoutWidget.h"
#include "MAUITemplatePool.h"
#include "AUIStringUtil.h"

using namespace mit::alice;

MAUITemplateProcessor::MAUITemplateProcessor()
    : m_pPool( new MAUITemplatePool() )
    , m_pRootWidget( new AUILinearLayoutWidget() )
    , m_bLoaded( false )
    , m_bTrPrepared( false )
{

}

void MAUITemplateProcessor::SetPool( const std::shared_ptr< MAUITemplatePool >& pPool )
{
    if ( IsLoaded() )
    {
        AUIAssertFailReason("Unload first");
        return;
    }

    if ( nullptr == pPool )
    {
        AUIAssertFailReason("Invalid pool");
        return;
    }

    m_pPool = pPool;
}

void MAUITemplateProcessor::Clear()
{
    if ( IsLoaded() )
    {
        //AUIAssert( !"Unload first" );
        //return;
		m_mapTag2Widget.clear();
    }
    AUIAssert( m_pPool );
    m_pPool->Clear();
}

bool MAUITemplateProcessor::Insert( const std::wstring& tag, const std::shared_ptr< MAUITemplate >& pTemplate )
{
    if ( IsLoaded() )
    {
        AUIAssertFailReason("Unload first");
        return false;
    }
    AUIAssert( m_pPool );
	if(!m_pPool->Insert( tag, pTemplate ))
		return false;

    pTemplate->SetMSSClass( tag );

	if( IsLoaded() )
	{
		const auto pWidget = pTemplate->CreateWidget();
		if ( nullptr == pWidget )
			return false;
		m_mapTag2Widget[tag] = pWidget;
	}

    return true;
}

bool MAUITemplateProcessor::Remove( const std::wstring& tag )
{
    if ( IsLoaded() )
    {
		m_mapTag2Widget.erase(tag);
        //AUIAssert( !"Unload first" );
        //return false;
    }
    AUIAssert( m_pPool );
    return m_pPool->Remove( tag );
}

void MAUITemplateProcessor::SetRootWidget( const std::shared_ptr< AUILinearLayoutWidget >& pRootWidget )
{
    if ( IsLoaded() )
    {
        AUIAssertFailReason("Unload first");
        return;
    }
    if ( nullptr == pRootWidget )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    m_pRootWidget = pRootWidget;
}

void MAUITemplateProcessor::SetRootWidget( AUILinearLayoutWidget* const pRootWidget )
{
    if ( nullptr == pRootWidget )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }
    this->SetRootWidget( std::static_pointer_cast< AUILinearLayoutWidget >( pRootWidget->shared_from_this() ) );
}

void MAUITemplateProcessor::SetRootTags( const std::vector< std::wstring >& arrRootTags )
{
    if ( IsLoaded() )
    {
        AUIAssertFailReason("Unload first");
        return;
    }
    m_RootTags = arrRootTags;
}

bool MAUITemplateProcessor::Load()
{
    if ( IsLoaded() )
    {
        AUIAssertFailReason("Unload first");
        return false;
    }

    Unload();

    const auto arrTags = m_pPool->GetTags();


    for ( auto tag : arrTags )
    {
        const auto pTemplate = m_pPool->GetTemplate( tag );
        if ( nullptr == pTemplate )
            continue;
        const auto pWidget = pTemplate->CreateWidget();
        if ( nullptr == pWidget )
            continue;

        m_mapTag2Widget[tag] = pWidget;
    }




    AUIAssert( m_pRootWidget );
    for ( auto rootTag : m_RootTags )
    {
        const auto found = m_mapTag2Widget.find( rootTag );
        if ( m_mapTag2Widget.end() == found )
            continue;
        const auto pWidget = found->second;
        if ( nullptr == pWidget )
            continue;

        m_pRootWidget->AddSubWidget( pWidget );
    }

    m_bLoaded = true;
    m_bTrPrepared = false;

    return true;
}

bool MAUITemplateProcessor::Unload()
{
    if ( false == IsLoaded() )
    {
        return true;
    }

    AUIAssert( m_pRootWidget );

    m_pRootWidget->ClearSubWidget();

    m_mapTag2Widget.clear();



    m_bLoaded = false;
    m_bTrPrepared = false;

    return true;
}

void MAUITemplateProcessor::UpdateParam( const std::wstring& tag, const MAUITemplParam& param )
{
    if ( false == IsLoaded() )
    {
        AUIAssertFail();
        return;
    }
    const auto pTemplate = m_pPool->GetTemplate( tag );
    if ( nullptr == pTemplate )
        return;

    const auto pWidget = this->GetTagWidget( tag ).get();
    if ( nullptr == pWidget )
        return;

    pTemplate->UpdateParam( pWidget, param );
}

std::shared_ptr< AUIWidget > MAUITemplateProcessor::GetTagWidget( const std::wstring& tag ) const
{
    const auto found = m_mapTag2Widget.find( tag );
    if ( m_mapTag2Widget.end() == found )
        return nullptr;
    return found->second;
}

bool mit::alice::MAUITemplateProcessor::Has( const std::wstring& tag ) const
{
    return m_pPool->Has( tag );
}

bool mit::alice::MAUITemplateProcessor::TrPrepare()
{
    if ( false == IsLoaded() )
    {
        AUIAssertFailReason("Must be loaded");
        return false;
    }

    m_Transactions.clear();





    m_bTrPrepared = true;

    return true;
}

bool mit::alice::MAUITemplateProcessor::TrCommit()
{
    if ( false == IsTrPrepared() )
    {
        AUIAssertFailReason("Prepare TR first");
        return false;
    }

    this->TrOptimize();

    for ( auto& tr : m_Transactions )
    {
        auto pTemplate = m_pPool->GetTemplate( tr.fToTag );
        if ( nullptr == pTemplate )
        {
            AUIAssertFailReason("WTF");
            continue;
        }
        auto pWidget = this->GetTagWidget( tr.fToTag ).get();
        if ( nullptr == pWidget )
        {
            AUIAssertFailReason("WTF");
            continue;
        }




        if ( Tr::Param_Cmd == tr.fCmd )
        {
            AUIAssertFail();
            //MAUITemplParam param;
            //param.fImage = tr.fImage;
            //param.fText = tr.fText;
            //param.fWidget = tr.fWidget;
            //pTemplate->UpdateParam( pWidget, param );
        }
        else if ( Tr::Insert_Cmd == tr.fCmd )
        {
            if ( false == tr.fTargetTag.empty() )
            {
                auto pTargetWidget = this->GetTagWidget( tr.fTargetTag );
                if ( nullptr == pTargetWidget )
                {
                   // AUIAssert( !"WTF" );
                    continue;
                }

                MAUITemplInput input;
                input.fImage = tr.fImage;
                input.fText = tr.fText;
                input.fWidget = pTargetWidget->shared_from_this();
                pTemplate->UpdateInsert( pWidget, input );

                m_Tag2Tag[tr.fTargetTag] = tr.fToTag;
            }
            else if ( tr.fWidget )
            {
                MAUITemplInput input;
                input.fImage = tr.fImage;
                input.fText = tr.fText;
                input.fWidget = tr.fWidget;
                pTemplate->UpdateInsert( pWidget, input );

                m_Widget2Tag[tr.fWidget.get()] = tr.fToTag;
            }
            else
            {
                AUIAssertFailReason("WTF");
                continue;
            }
        }
        else if ( Tr::Remove_Cmd == tr.fCmd )
        {
            if ( false == tr.fTargetTag.empty() )
            {
                auto pTargetWidget = this->GetTagWidget( tr.fTargetTag );
                if ( nullptr == pTargetWidget )
                {
                    AUIAssertFailReason("WTF");
                    continue;
                }
                MAUITemplInput input;
                input.fImage = tr.fImage;
                input.fText = tr.fText;
                input.fWidget = pTargetWidget->shared_from_this();
                pTemplate->UpdateRemove( pWidget, input );

                m_Tag2Tag.erase( tr.fTargetTag );
            }
            else if ( tr.fWidget )
            {
                MAUITemplInput input;
                input.fImage = tr.fImage;
                input.fText = tr.fText;
                input.fWidget = tr.fWidget;
                pTemplate->UpdateRemove( pWidget, input );

                m_Widget2Tag.erase( tr.fWidget.get() );
            }
            else
            {
                AUIAssertFailReason("WTF");
                continue;
            }
        }
        else if ( Tr::Clear_Cmd == tr.fCmd )
        {
            MAUITemplInput input;
            input.fImage = tr.fImage;
            input.fText = tr.fText;
            input.fWidget = tr.fWidget;
            pTemplate->UpdateClear( pWidget, input );

            std::set< AUIWidget* > eraseWidget;
            for ( auto& w2t : m_Widget2Tag )
            {
                if (AUIStringUtil::IsEqualIgnoreCase( w2t.second, tr.fToTag ) )
                    eraseWidget.emplace( w2t.first );
            }
            for ( auto& itr : eraseWidget )
                m_Widget2Tag.erase( itr );
            std::set< std::wstring > eraseTag;
            for ( auto& t2t : m_Tag2Tag )
            {
                if ( AUIStringUtil::IsEqualIgnoreCase( t2t.second, tr.fToTag ) )
                    eraseTag.emplace( t2t.first );
            }
            for ( auto itr : eraseTag )
                m_Tag2Tag.erase( itr );
        }
        else
        {
            AUIAssertFailReason("WTF");
        }
    }



    return true;
}

bool mit::alice::MAUITemplateProcessor::TrRollback()
{
    if ( false == IsTrPrepared() )
    {
        AUIAssertFailReason("Prepare TR first");
        return false;
    }

    m_Transactions.clear();


    return true;
}

void mit::alice::MAUITemplateProcessor::TrInsert( const std::wstring& toTag, const std::wstring& targetTag, const std::wstring& text, const std::shared_ptr< AUIDrawable>& pImage )
{
    m_Transactions.emplace_back( Tr::Insert_Cmd, toTag, targetTag, text, pImage );
}

void mit::alice::MAUITemplateProcessor::TrInsert( const std::wstring& toTag, const std::shared_ptr< AUIWidget >& pWidget, const std::wstring& text, const std::shared_ptr< AUIDrawable >& pImage )
{
    m_Transactions.emplace_back( Tr::Insert_Cmd, toTag, pWidget, text, pImage );
}

void mit::alice::MAUITemplateProcessor::TrRemove( const std::wstring& toTag, const std::wstring& targetTag )
{
    m_Transactions.emplace_back( Tr::Remove_Cmd, toTag, targetTag );
}

void mit::alice::MAUITemplateProcessor::TrRemove( const std::wstring& toTag, const std::shared_ptr< AUIWidget >& pWidget )
{
    m_Transactions.emplace_back( Tr::Remove_Cmd, toTag, pWidget );
}

void mit::alice::MAUITemplateProcessor::TrClear( const std::wstring& toTag )
{
    m_Transactions.emplace_back( Tr::Clear_Cmd, toTag, L"" );
}


bool mit::alice::MAUITemplateProcessor::TrOptimize()
{
    if ( false == IsTrPrepared() )
    {
        AUIAssertFailReason("Prepare TR first");
        return false;
    }

    std::unordered_set< AUIWidget* > tmpWidgetPendingRemove;
    std::unordered_set< std::wstring > tmpTagPendingRemove;
    std::unordered_map< AUIWidget*, std::wstring > tmpWidget2Tag = m_Widget2Tag;
    std::unordered_map< std::wstring, std::wstring > tmpTag2Tag = m_Tag2Tag;

    std::vector< Tr > optTransaction;

    for ( auto transaction : m_Transactions )
    {
        if ( false == m_pPool->Has( transaction.fToTag ) )
        {
           // AUIAssert( !"Invalid tag" );
            continue;
        }

        if ( Tr::Param_Cmd == transaction.fCmd )
        {
            optTransaction.emplace_back( transaction );
        }
        else if ( Tr::Insert_Cmd == transaction.fCmd )
        {
            if ( false == transaction.fTargetTag.empty() )
            {
                if ( false == m_pPool->Has( transaction.fTargetTag ) )
                {
                    AUIAssert( !"Invalid tag" );
                    continue;
                }

                // Remove first
                if ( tmpTagPendingRemove.end() == tmpTagPendingRemove.find( transaction.fTargetTag ) )
                {
                    if ( tmpTag2Tag.end() != tmpTag2Tag.find( transaction.fTargetTag ) )
                    {
                        optTransaction.emplace_back( Tr::Remove_Cmd, transaction.fToTag, transaction.fTargetTag );
                    }
                }
                else
                {
                    tmpTagPendingRemove.erase( transaction.fTargetTag );
                }

                optTransaction.emplace_back( transaction );
                tmpTag2Tag[transaction.fTargetTag] = transaction.fToTag;
            }
            else if ( transaction.fWidget )
            {
                if ( transaction.fWidget->GetParent() )
                {
                    if ( tmpWidgetPendingRemove.end() == tmpWidgetPendingRemove.find( transaction.fWidget.get() ) )
                    {
                        const auto foundTag = tmpWidget2Tag.find( transaction.fWidget.get() );
                        if ( tmpWidget2Tag.end() == foundTag )
                        {
                            AUIAssertFailReason("Widget is not managed by this Template Processor");
                            continue;
                        }
                        if ( false == m_pPool->Has( foundTag->second ) )
                        {
                            AUIAssertFailReason("Invalid tag");
                            continue;
                        }

                        // Remove first
                        optTransaction.emplace_back( Tr::Remove_Cmd, transaction.fToTag, transaction.fWidget );
                    }
                    else
                    {
                        if ( m_Widget2Tag.end() == m_Widget2Tag.find( transaction.fWidget.get() ) )
                        {
                            AUIAssertFailReason("Widget is not managed by this Template Processor");
                            continue;
                        }
                        tmpWidgetPendingRemove.erase( transaction.fWidget.get() );
                    }
                }

                optTransaction.emplace_back( transaction );
                tmpWidget2Tag[transaction.fWidget.get()] = transaction.fToTag;
            }
            else
            {
                AUIAssertFailReason("Invalid Command");
            }
        }
        else if ( Tr::Remove_Cmd == transaction.fCmd )
        {
            if ( false == transaction.fTargetTag.empty() )
            {
                if ( false == m_pPool->Has( transaction.fTargetTag ) )
                {
                    AUIAssertFailReason("Invalid tag");
                    continue;
                }

                if ( tmpTag2Tag.end() == tmpTag2Tag.find( transaction.fTargetTag ) )
                {
                    AUIAssertFailReason("Already single");
                    continue;
                }

                optTransaction.emplace_back( transaction );
                tmpTagPendingRemove.emplace( transaction.fTargetTag );
                tmpTag2Tag.erase( transaction.fTargetTag );
            }
            else if ( transaction.fWidget )
            {
                if ( false == transaction.fWidget->GetParent() )
                {
                    AUIAssertFailReason("No parent");
                    continue;
                }
                const auto foundTag = tmpWidget2Tag.find( transaction.fWidget.get() );
                if ( tmpWidget2Tag.end() == foundTag )
                {
                    AUIAssertFailReason("Widget is not managed by this Template Processor");
                    continue;
                }
                if ( false == m_pPool->Has( foundTag->second ) )
                {
                    AUIAssertFailReason("Invalid tag");
                    continue;
                }

                optTransaction.emplace_back( transaction );
                tmpWidgetPendingRemove.emplace( foundTag->first );
                tmpWidget2Tag.erase( foundTag );
            }
            else
            {
                AUIAssertFailReason("Invalid Command");
            }
        }
        else if ( Tr::Clear_Cmd == transaction.fCmd )
        {

            std::set< AUIWidget* > eraseWidget;
            for ( auto& w2t : tmpWidget2Tag )
            {
                if ( AUIStringUtil::IsEqualIgnoreCase( w2t.second, transaction.fToTag ) )
                    eraseWidget.emplace( w2t.first );
            }
            for ( auto& itr : eraseWidget )
            {
                tmpWidgetPendingRemove.emplace( itr );
                tmpWidget2Tag.erase( itr );
            }
            std::set< std::wstring > eraseTag;
            for ( auto& t2t : tmpTag2Tag )
            {
                if (AUIStringUtil::IsEqualIgnoreCase( t2t.second, transaction.fToTag ) )
                    eraseTag.emplace( t2t.first );
            }
            for ( auto itr : eraseTag )
            {
                tmpTagPendingRemove.emplace( itr );
                tmpTag2Tag.erase( itr );
            }
            optTransaction.emplace_back( transaction );
        }
        else
        {
            AUIAssertFailReason("Invalid TR");
        }
    }

    m_Transactions = optTransaction;
    return true;
}

std::vector< std::wstring > mit::alice::MAUITemplateProcessor::GetAllTag() const
{
    std::vector< std::wstring > arrTags;
    arrTags.reserve( m_mapTag2Widget.size() ); 
    for ( const auto& itrTag2Widget : m_mapTag2Widget )
    {
        arrTags.emplace_back( itrTag2Widget.first );
    }
    return arrTags;
}
