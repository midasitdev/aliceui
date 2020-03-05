#include "pch.h"
#include "AUIComboItemWidget.h"
#include "AUIComboDefaultValue.h"
#include "AUIColorDrawable.h"
#include "AUIStateDrawable.h"
#include "AUIJsonDrawableParser.h"


AUIComboItemWidget::AUIComboItemWidget()
    : m_pContent( std::make_shared< AUIAbsoluteLayoutWidget >() )
    , m_ItemPos( 0 )
    , m_bUseMarquee( false )
{
    SetClickable( true );

    SetMinimumSize({ COMBO::ITEM::kComboItemMinWidth, COMBO::ITEM::kComboItemMinHeight });
    SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kContent);
    SetMarginLTRB(COMBO::ITEM::kComboItemMarginLeft,
                    COMBO::ITEM::kComboItemMarginTop,
                    COMBO::ITEM::kComboItemMarginRight,
                    COMBO::ITEM::kComboItemMarginBottom);
    /*auto pHoverBG = std::make_shared< AUIColorDrawable >();
    pHoverBG->SetColor( SkColorSetRGB( 144, 194, 255 ) );

    auto pPressBG = std::make_shared< AUIColorDrawable >();
    pPressBG->SetColor( SkColorSetRGB( 118, 179, 255 ) );

    auto pStateDrawable = std::make_shared< AUIStateDrawable >();
    pStateDrawable->SetTrueStateDrawable( AUIState::kMouseHovered, pHoverBG );
    pStateDrawable->SetTrueStateDrawable( AUIState::kPressed, pPressBG );

    pStateDrawable->SetDrawPadding( SkRect::MakeLTRB( 1.0f, 0.0f, 1.0f, 0.0f ) );

    SetBackgroundDrawable( pStateDrawable );
*/
	AUIJsonDrawableParser parser;
	if (auto refDrawable = parser.LoadFromPathByResource(COMBO::ITEM::kComboItemBackground))
		SetBackgroundDrawable(*refDrawable);

    m_pContent->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kContent);
    AddSubWidget( m_pContent );

    // Don't catch event
    m_pContent->Freeze();
}

AUIComboItemWidget::AUIComboItemWidget(const std::wstring& bgPath)
    : m_pContent(std::make_shared< AUIAbsoluteLayoutWidget >())
    , m_ItemPos(0)
    , m_bUseMarquee(false)
{
    SetClickable(true);

    SetMinimumSize({ COMBO::ITEM::kComboItemMinWidth, COMBO::ITEM::kComboItemMinHeight });
    SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kContent);
    SetMarginLTRB(COMBO::ITEM::kComboItemMarginLeft,
        COMBO::ITEM::kComboItemMarginTop,
        COMBO::ITEM::kComboItemMarginRight,
        COMBO::ITEM::kComboItemMarginBottom);

    AUIJsonDrawableParser parser;
    if (bgPath != L"")
    {
        if (auto refDrawable = parser.LoadFromPathByResource(bgPath))
            SetBackgroundDrawable(*refDrawable);
    }
    else
    {
        if (auto refDrawable = parser.LoadFromPathByResource(COMBO::ITEM::kComboItemBackground))
            SetBackgroundDrawable(*refDrawable);
    }

    m_pContent->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kContent);
    AddSubWidget(m_pContent);

    // Don't catch event
    m_pContent->Freeze();
}

AUIComboItemWidget::~AUIComboItemWidget()
{

}

void AUIComboItemWidget::OnMouseEnter()
{
    SuperWidget::OnMouseEnter();
    Invalidate();
}

void AUIComboItemWidget::OnMouseHover()
{
    SuperWidget::OnMouseHover();

    if ( IsUseMarquee() )
    {

    }

    Invalidate();
}

void AUIComboItemWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();
    Invalidate();
}

bool AUIComboItemWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnUp( flag );

    ClickSignal.Send( this, GetItemPos() );

    return true;
}

void AUIComboItemWidget::SetContent( const std::shared_ptr< AUIWidget >& pWidget, size_t pos )
{
    if ( pWidget == nullptr )
    {
        AUIAssertFailReason("Invalid widget");
        return;
    }

    // Don't catch event
    pWidget->Freeze();
    if (AUISizePolicy::kParent == pWidget->GetSizePolicyHeight())
        pWidget->SetSizePolicyHeight(AUISizePolicy::kContent);
    if (AUISizePolicy::kParent != pWidget->GetSizePolicyWidth())
        pWidget->SetSizePolicyWidth(AUISizePolicy::kParent);

    m_pContent->ClearSubWidget();
    m_pContent->AddSubWidget( pWidget );
    m_pContentItem = pWidget;
    m_ItemPos = pos;
}
