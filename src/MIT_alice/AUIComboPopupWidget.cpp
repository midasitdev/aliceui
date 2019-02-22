#include "pch.h"
#include "AUIComboPopupWidget.h"
#include "AUIComboAdapter.h"
#include "AUIWidgetManager.h"
#include "AUIColorDrawable.h"
#include "AUIComboItemWidget.h"
#include "AUIWidget.h"
#include "AUIShapeDrawable.h"
#include "AUIRectShape.h"
#include "AUILayerDrawable.h"
#include "AUILinearLayoutWidget.h"
#include "AUIScrollableBarWidget.h"


namespace {
    constexpr SkScalar DefaultComboItemHeight = 23.0f;
}

AUIComboPopupWidget::AUIComboPopupWidget()
    : m_pContent( std::make_shared< AUILinearLayoutWidget >() )
    , m_bUseMarquee( false )
{
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kContent);
    m_pContent->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kContent);

    AddSubWidget( m_pContent );

    // TODO : change bg
    auto pBG = std::make_shared< AUIColorDrawable >();
    pBG->SetColor( SkColorSetRGB( 245, 245, 245 ) );
    auto pBorder = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
    pBorder->SetColor( SkColorSetRGB( 197, 197, 197 ) );
    pBorder->SetStrokeStyle( SkPaint::kStroke_Style );
    auto pBGDrawable = std::make_shared< AUILayerDrawable >();
    pBGDrawable->InsertLayer( pBG );
    pBGDrawable->InsertLayer( pBorder );
    SetBackgroundDrawable( pBGDrawable );


    Connect(GetScrollBarWidget()->FocusOutSignal, [this](AUIWidget*) {
        this->OnFocusOut();
    });
}

AUIComboPopupWidget::~AUIComboPopupWidget()
{
    m_spoolAdapterDataChanged.DisconnectAll();
}

void AUIComboPopupWidget::SetAdapter( const std::shared_ptr< AUIComboAdapter >& pAdapter )
{
    if ( pAdapter == nullptr )
    {
        m_spoolAdapterDataChanged.DisconnectAll();
        m_pAdapter.reset();
        AUIAssertFailReason("Invalid adapter");
        return;
    }

    if ( m_pAdapter == pAdapter )
        return;

    m_spoolAdapterDataChanged.DisconnectAll();

    m_pAdapter = pAdapter;

    m_spoolAdapterDataChanged.Connect(m_pAdapter->DataChangedSignal, this, &AUIComboPopupWidget::OnAdapterDataChanged );

    OnAdapterDataChanged(pAdapter.get());
}

void AUIComboPopupWidget::OnAdapterDataChanged(AUIComboAdapter*)
{
    AUIAssert( m_pAdapter );
    GetContentWidget()->ClearSubWidget();

    const auto totalCount = m_pAdapter->GetCount();
    for ( auto idx = 0 ; idx < totalCount ; idx++ )
    {
        auto pItemWidget = std::make_shared< AUIComboItemWidget >();
        pItemWidget->SetDefaultSize( GetWidth(), DefaultComboItemHeight );
        pItemWidget->SetUseMarquee( m_bUseMarquee );

        Connect( pItemWidget->ClickSignal, this, &AUIComboPopupWidget::OnItemClicked );
        Connect( pItemWidget->FocusInSignal, this, &AUIComboPopupWidget::OnItemFocusChange );
        Connect( pItemWidget->FocusOutSignal, this, &AUIComboPopupWidget::OnItemFocusChange );

        if ( auto pWidget = m_pAdapter->GetComboItemWidget( idx, nullptr, shared_from_this() ) )
        {
            pItemWidget->SetContent( pWidget, idx );
            if (auto pTooltip = pWidget->GetTooltip())
            {
                pItemWidget->SetShowTooltip(true);
                pItemWidget->SetTooltip(pTooltip);
            }
        }

        GetContentWidget()->AddSubWidget( pItemWidget ); 
    }
    this->SetDefaultHeight(totalCount * DefaultComboItemHeight);
    GetContentWidget()->UpdateSize();
    GetContentWidget()->UpdateChildPosition();
}

void AUIComboPopupWidget::OnItemClicked( AUIWidget*, size_t pos )
{
    AUIAssert( m_pAdapter );
    m_pAdapter->ClickItemSignal.Send(m_pAdapter.get(), pos );
}

void AUIComboPopupWidget::OnItemFocusChange( AUIWidget* )
{
    const auto children = GetContentWidget()->GetChildren();

    bool childHasFocus = IsFocused();
    for ( auto& child : children )
    {
        childHasFocus |= child->IsMouseHover();
    }
    if ( childHasFocus == false )
        PopupFocusLostSignal.Send();
}

void AUIComboPopupWidget::OnFocusOut()
{
    OnItemFocusChange( this );
}

void AUIComboPopupWidget::SetUseMarquee( bool val )
{
    m_bUseMarquee = val;
}
