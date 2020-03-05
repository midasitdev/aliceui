#include "pch.h"
#include "AUIComboWidget.h"
#include "AUIComboPopupWidget.h"
#include "AUIComboDefaultValue.h"
#include "AUIWidgetManager.h"
#include "AUIComboAdapter.h"
#include "AUIStateDrawable.h"
#include "AUILayerDrawable.h"
#include "AUIShapeDrawable.h"
#include "AUIRectShape.h"
#include "AUITriangleShape.h"
#include "AUIApplication.h"
#include "AUIJsonDrawableParser.h"
#include "AUIDrawableWidget.h"


namespace
{
    std::shared_ptr< AUIDrawable > GetComboDrawable()
    {
        AUIJsonDrawableParser parser;
        if (auto refDrawable = parser.LoadFromPathByResource(L"drawable/mp_btn.json"))
            return *refDrawable;

        auto pDefaultBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pDefaultBG->SetColor( SkColorSetRGB( 253, 253, 253 ) );
        auto pHoverBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pHoverBG->SetColor( SkColorSetRGB( 245, 245, 245 ) );
        auto pPressBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pPressBG->SetColor( SkColorSetRGB( 234, 238, 244 ) );
        auto pDisableBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pDisableBG->SetColor( SkColorSetRGB( 221, 221, 221 ) );
        auto pCheckBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pCheckBG->SetColor( SkColorSetRGB( 234, 238, 244 ) );
        auto pOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pOutline->SetColor( SkColorSetRGB( 177, 177, 177 ) );
        pOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        auto pHoverOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pHoverOutline->SetColor( SkColorSetRGB( 130, 186, 255 ) );
        pHoverOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        pHoverOutline->SetStrokeWidth( 2.0f );
        auto pPressOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pPressOutline->SetColor( SkColorSetRGB( 130, 186, 255 ) );
        pPressOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        pPressOutline->SetStrokeWidth( 2.0f );
        auto pCheckOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pCheckOutline->SetColor( SkColorSetRGB( 161, 174, 194 ) );
        pCheckOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        pCheckOutline->SetStrokeWidth( 2.0f );
        auto pDisableOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRectShape >() );
        pDisableOutline->SetColor( SkColorSetRGB( 204, 204, 204 ) );
        pDisableOutline->SetStrokeStyle( SkPaint::kStroke_Style );
        pDisableOutline->SetStrokeWidth( 2.0f );
        auto pBackground = std::make_shared< AUILayerDrawable >();
        pBackground->InsertLayer( pDefaultBG );
        pBackground->InsertLayer( pOutline );

        auto pHoverBackground = std::make_shared< AUILayerDrawable >();
        pHoverBackground->InsertLayer( pHoverBG );
        pHoverBackground->InsertLayer( pHoverOutline );

        auto pPressBackground = std::make_shared< AUILayerDrawable >();
        pPressBackground->InsertLayer( pPressBG );
        pPressBackground->InsertLayer( pPressOutline );

        auto pDisabledBackground = std::make_shared< AUILayerDrawable >();
        pDisabledBackground->InsertLayer( pDisableBG );
        pDisabledBackground->InsertLayer( pDisableOutline );

        auto pCheckBackground = std::make_shared< AUILayerDrawable >();
        pCheckBackground->InsertLayer( pCheckBG );
        pCheckBackground->InsertLayer( pCheckOutline );


        auto pStateDrawable = std::make_shared< AUIStateDrawable >();
        pStateDrawable->SetTrueStateDrawable( AUIState::kDefault, pBackground );
        pStateDrawable->SetTrueStateDrawable( AUIState::kMouseHovered, pHoverBackground );
        pStateDrawable->SetTrueStateDrawable( AUIState::kPressed, pPressBackground );
        pStateDrawable->SetTrueStateDrawable( AUIState::kDisabled, pDisabledBackground );
        pStateDrawable->SetTrueStateDrawable( AUIState::kChecked, pCheckBackground );

        return pStateDrawable;
    }
}

size_t AUIComboWidget::InvalidPos = (std::numeric_limits< size_t >::max)();

AUIComboWidget::AUIComboWidget()
    : m_pPopup( std::make_shared< AUIComboPopupWidget >() )
    , m_curPos( InvalidPos )
    , m_PopupMaxHeight( -1.0f )
    , m_bUsePopuptHitRect(false)
    , m_bArrowDirection(true)
{
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);
    SetDefaultSize( COMBO::kDefaultWidth, COMBO::kDefaultHeight );

    SetPopupWidget( m_pPopup );

    Connect( ComboPopupSignal, this, &AUIComboWidget::OnClickPopup );
    Connect( m_pPopup->PopupFocusLostSignal, this, &AUIComboWidget::OnPopupFocusLost );
    Connect(AUIApplication::Instance().MouseWheelSignal, [&](AUIWidgetManager* _pWM, int, int, float) {
        if (auto _pTargetWM = this->GetWidgetManager())
        {
            if (_pTargetWM == _pWM)
                this->Dismiss();
        }
    });

    SetBackgroundDrawable( ::GetComboDrawable() );
}

void AUIComboWidget::OnDraw( SkCanvas* const canvas )
{
    SuperWidget::OnDraw( canvas );

    const auto rect = GetDrawBound();
    const auto triOffsetY = rect.height() * 0.5f - COMBO::ARROW::kComboArrowSize * 0.5f;

    // TOOD : Designed shape
    static auto pTriShape = std::make_shared< AUITriangleShape >();
    static auto pTriangle = std::make_shared< AUIShapeDrawable >( pTriShape );
    if (GetArrowDirection())
        pTriShape->SetAngle( 180.0f );
    pTriangle->SetUseAA( true );
    pTriangle->SetDrawBound( SkRect::MakeWH(COMBO::ARROW::kComboArrowSize, COMBO::ARROW::kComboArrowSize) );
    pTriangle->SetColor( COMBO::ARROW::kComboArrowColor );
    canvas->translate( GetWidth() - COMBO::ARROW::kComboArrowSize - COMBO::ARROW::kComboArrowOffset, triOffsetY );
    pTriangle->Draw( canvas );
}

void AUIComboWidget::OnAfterMeasureSize(SkScalar width, SkScalar height)
{
    const auto trioffsetleft = 5.0f;
    SetPopupHitRect(SkRect::MakeLTRB(width - COMBO::ARROW::kComboArrowSize
                                     - COMBO::ARROW::kComboArrowOffset
                                     - trioffsetleft, 0.0f, width, height));
}

void AUIComboWidget::OnMouseEnter()
{
    SuperWidget::OnMouseEnter();
    Invalidate();
}

void AUIComboWidget::OnMouseHover()
{
    SuperWidget::OnMouseHover();
    Invalidate();
}

void AUIComboWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();
    Invalidate();
}

bool AUIComboWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnUp( flag );

    if ( false == IsDisabled() )
    {
        if (false == IsUsePopupHitRect())
            ComboPopupSignal.Send(this);
        else
        {
            // Check Hit Test
            if (m_PopupHitRect.isEmpty() || AUISkiaUtil::IsInRect(m_PopupHitRect, GetMouseLocPos()))
                ComboPopupSignal.Send(this);
            else
                ComboClickSignal.Send(this);
        }
    }

    return true;
}

void AUIComboWidget::OnDestroy()
{
    SuperWidget::OnDestroy();

    if (IsInvoked())
        Dismiss();
}

void AUIComboWidget::SetAdapter( const std::shared_ptr< AUIComboAdapter >& pAdapter )
{
    if ( m_pPopup->GetAdapter() == pAdapter )
        return;

    m_spoolItemClick.DisconnectAll();
    m_spoolDataChange.DisconnectAll();

    AUIAssert( pAdapter );

    m_spoolItemClick.Connect(pAdapter->ClickItemSignal, this, &AUIComboWidget::OnItemClicked );
    m_spoolDataChange.Connect(pAdapter->DataChangedSignal, this, &AUIComboWidget::OnAdapterDataChanged );

    // Reset
    m_curPos = InvalidPos;

    m_pPopup->SetAdapter( pAdapter );

    RefreshLabel();
}

std::shared_ptr< AUIComboAdapter > AUIComboWidget::GetAdapter() const
{
    return m_pPopup->GetAdapter();
}

void AUIComboWidget::OnAdapterDataChanged(AUIComboAdapter* pAdapter )
{
    //if ( InvalidPos == GetCurPos() )
    RefreshLabel();
}

void AUIComboWidget::OnClickPopup( AUIComboWidget* const )
{
    if ( m_PopupMaxHeight > 0 )
    {
        m_pPopup->SetMaximumHeight( m_PopupMaxHeight );
        m_pPopup->SetDefaultHeight( m_PopupMaxHeight );
    }
    m_pPopup->SetDefaultWidth( GetWidth() );

    AUIAssert( IsCreated() );
    if ( IsInvoked() )
    {
        Dismiss();
    }
    else
    {
        SetPopupPosition( glm::vec3( 0.0f, GetHeight(), 0.0f ) );
        Invoke(GetWidgetManager(), shared_from_this(), GetPopupOpt());
    }
}

void AUIComboWidget::OnItemClicked(AUIComboAdapter*, size_t pos )
{
    SetCurPos( pos );
    Dismiss();
}

void AUIComboWidget::OnPopupFocusLost()
{
    SetCurPos( GetCurPos() );
    Dismiss();
}

void AUIComboWidget::RefreshLabel()
{
	auto pAdapter = GetAdapter();
    if (pAdapter && 
		pAdapter->GetCount() != 0 &&
		InvalidPos != GetCurPos())
    {
        auto pNewLabel = pAdapter->GetWidget( GetCurPos(), GetLabel(), shared_from_this() );
        SetLabel( pNewLabel );
    }
    else
	{
		SetLabel(nullptr);
    }
}

void AUIComboWidget::SetLabel( const std::shared_ptr< AUIWidget >& pLabel )
{
    if (GetLabel() && GetLabel() == pLabel )
    {
        GetLabel()->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kParent);
        GetLabel()->SetPosition( 0.0f, 0.0f );
        GetLabel()->SetDefaultSize( GetDefaultSize() );
        UpdateSize();
        UpdateChildPosition();
        return;
    }

    if (GetLabel())
    {
        DelChild(GetLabel());
    }

    m_pLabel = pLabel;

    if (GetLabel())
    {
        GetLabel()->Freeze();
        GetLabel()->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kParent);
        GetLabel()->SetPosition( 0.0f, 0.0f );
        GetLabel()->SetDefaultSize( GetDefaultSize() );

        AddChild(GetLabel());
	}
	else
	{
		auto _tmplabel = std::make_shared<AUIDrawableWidget>();
		m_pLabel = _tmplabel;
		_tmplabel->Freeze();
		_tmplabel->SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kParent);
		_tmplabel->SetPosition(0.0f, 0.0f);
		_tmplabel->SetDefaultSize(GetDefaultSize());

		AddChild(_tmplabel);
	}

	UpdateSize();
	UpdateChildPosition();
}

void AUIComboWidget::SetCurPos( size_t pos )
{
    m_curPos = pos;
    RefreshLabel();
}

void AUIComboWidget::OnSetDefaultSize( const AUIScalar2& size )
{
    AUIFrameLayoutWidget::OnSetDefaultSize( size );
    if (GetLabel())
        GetLabel()->SetDefaultSize( size );
    m_pPopup->SetDefaultWidth( size.fX );
}

void AUIComboWidget::SetUseMarquee( bool val )
{
    m_pPopup->SetUseMarquee( val );
}

bool AUIComboWidget::IsUseMarquee() const
{
    return m_pPopup->IsUseMarquee();
}
