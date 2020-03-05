#include "pch.h"
#include "AUIConsoleWidget.h"
#include "AUIEditWidget.h"
#include "AUIScrollableWidget.h"
#include "AUISeparatorWidget.h"
#include "AUIWidgetManager.h"

AUIConsoleWidget::AUIConsoleWidget()
    : m_pScroll( std::make_shared<AUIScrollableWidget>() )
    , m_pEdit( std::make_shared<AUIEditWidget>() )
    , m_MaxListSize( 50 )
{
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);
    SetDefaultSize( 600.0f, 400.0f );

    m_pScroll->SetDefaultHeight(350.0f);
    m_pScroll->SetSizePolicyHeight( AUISizePolicy::kFixed);
    m_pEdit->SetSizePolicyWidth( AUISizePolicy::kParent );

    AddChild( m_pScroll );
    AddChild( m_pEdit );

    Connect( m_pEdit->SignalReturn, this, &AUIConsoleWidget::OnEditReturn );
}

AUIConsoleWidget::~AUIConsoleWidget()
{

}

void AUIConsoleWidget::AddSubWidgetAt( const std::shared_ptr< AUIWidget >& widget, const size_t pos )
{
    AUIAssertFailReason("Deleted method");
}

void AUIConsoleWidget::DelSubWidget( const std::shared_ptr< AUIWidget >& widget )
{
    AUIAssertFailReason("Deleted method");
}

void AUIConsoleWidget::PopSubWidget()
{
    AUIAssertFailReason("Deleted method");
}

void AUIConsoleWidget::ClearSubWidget()
{
    AUIAssertFailReason("Deleted method");
}

std::shared_ptr< AUIWidget > AUIConsoleWidget::FindSubWidget( size_t pos )
{
    AUIAssertFailReason("Deleted method");
    return nullptr;
}

size_t AUIConsoleWidget::SubWidgetCount() const 
{
    AUIAssertFailReason("Deleted method");
    return 0;
}

void AUIConsoleWidget::OnSetDefaultSize(const AUIScalar2& size)
{
    m_pScroll->SetDefaultHeight(size.fY - 100.0f);
}

void AUIConsoleWidget::OnEditReturn( AUIWidget* )
{
    const auto caption = m_pEdit->GetCaption();
    if ( false == caption.empty() )
    {
        m_pEdit->SetCaption( L"" );

        AddText( caption );

        SignalAddInput.Send( this, caption );
    }
    GetWidgetManager()->SetFocusTarget( m_pEdit );
}

void AUIConsoleWidget::AddText( const std::wstring& text )
{
    this->AddText( text, kAUIColorBlack );
}

void AUIConsoleWidget::AddText( const std::wstring& text, const SkColor& color )
{
    auto pText = std::make_shared< AUITextWidget >( text );
    pText->SetCaptionColor( color );
    pText->SetMinimumHeight( 20.0f );
    pText->SetSizePolicyHeight( AUISizePolicy::kContent );
    pText->SetSizePolicyWidth( AUISizePolicy::kParent );
	if (AUITextLineFeed::kNone != m_MultilineType)
	{
		pText->SetUseMultiline(true);
		pText->SetMultilineType(m_MultilineType);
	}
	else if (std::wstring::npos != text.find(L'\n'))
	{
		pText->SetMultilineType(AUITextLineFeed::kNewline);
		pText->SetUseMultiline(true);
	}

    m_InputLists.emplace( pText );
    m_pScroll->AddSubWidget( pText );
    m_pScroll->ScrollToBottom();

    while ( m_InputLists.size() > m_MaxListSize )
    {
        auto pEraseTarget = m_InputLists.front();
        m_pScroll->DelSubWidget( pEraseTarget );
        m_InputLists.pop();
    }
    AUIAssert( m_InputLists.size() <= m_MaxListSize );
}

void AUIConsoleWidget::SetMaxListSize( size_t size )
{
    if ( size < 5 )
    {
        AUIAssertFailReason("Max list size is too small");
        size = 5;
    }
    m_MaxListSize = size;
}

void AUIConsoleWidget::ClearScreen()
{
    m_pScroll->ClearSubWidget();
}

void AUIConsoleWidget::SetMultilineType(AUITextLineFeed multilineType)
{
	m_MultilineType = multilineType;
}
