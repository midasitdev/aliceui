#include "pch.h"
#include "AUILayoutWidget.h"
#include "AUIColor.h"
#include "AUIApplication.h"
#include "AUIStateDrawable.h"
#include "AUIColorDrawable.h"
#include "AUINinePatchDrawable.h"
#include "AUINinePatch.h"
#include "AUIGalleria.h"
#include "AUIJsonDrawableParser.h"
#include "AUIStyleNotion.h"
#include "AUIImageDrawable.h"
#include "AUILayoutManager.h"
#include "AUIAbsoluteLayout.h"

AUILayoutWidget::AUILayoutWidget()
    : m_pLayoutManager(new AUILayoutManager())
{
    m_pLayoutManager->SetTargetWidget(this);
    m_pLayoutManager->SetLayout(std::make_shared<AUIAbsoluteLayout>());

    SetSizePolicy(AUISizePolicy::kContent, AUISizePolicy::kContent);

    m_DebugColor = SkColorSetA( AUIColor::GetRandomColor(), kAUIAlpha_20 );

    // Set default layers
    InsertLayer(nullptr);   // Background
    InsertLayer(nullptr);   // Foreground

    LoadDefault2DSensor();

    SetHitTestAffectedByParent(true);
}

AUILayoutWidget::~AUILayoutWidget()
{

}

bool AUILayoutWidget::IsLayoutRoot() const
{
    if ( IsRoot() )
        return true;
    if (GetParent()->IsKindOf< AUILayoutWidget >() == false)
        return true;
    return false;
}

bool AUILayoutWidget::OnSetParent( AUIWidget* const pParent )
{
    if ( pParent == nullptr )
        return false;
    return pParent->IsKindOf< AUIInnerGroupWidget >();
}

void AUILayoutWidget::SetBackgroundDrawable( const std::shared_ptr< AUIDrawable >& pDrawable )
{
    SetLayer(BackgroundLayer, pDrawable);
    Invalidate();
}

void AUILayoutWidget::SetForegroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable)
{
    SetLayer(ForegroundLayer, pDrawable);
    Invalidate();
}

void AUILayoutWidget::SetAllDisabled( bool state )
{
    SetDisabled( state );
    OnSetAllDisabled( state );
}

void AUILayoutWidget::OnSetAllDisabled( bool state )
{
    auto children = GetChildren();
    for ( auto& child : children )
    {
        if ( auto pLayoutChild = child->DynCast< AUILayoutWidget >() )
        {
            pLayoutChild->SetAllDisabled( state );
        }
        else
        {
            child->SetDisabled( state );
        }
    }
}

void AUILayoutWidget::SetAllIgnored( bool state )
{
    SetIgnored( state );
    OnSetAllIgnored( state );
}

void AUILayoutWidget::OnDraw( SkCanvas* const canvas )
{
    SetDrawBound( GetRect() );
    SetDrawUIState( GetUIState() );
    AUILayerDrawable::OnDraw( canvas );

    if ( AUIApplication::Instance().IsVisualizeLayout() )
    {
        if ( IsMouseHover() )
        {
            SkPaint paint;
            paint.setColor( m_DebugColor );
            canvas->drawRect( GetRect(), paint );
        }
    }

    if (IsRefreshDraw())
        Invalidate();
}

void AUILayoutWidget::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    AUIAssert(m_pLayoutManager);

    m_pLayoutManager->OnMeasureSize(width, widthSpec, height, heightSpec);
}

void AUILayoutWidget::OnUpdateChildPosition()
{
    AUIAssert(m_pLayoutManager);

    m_pLayoutManager->OnUpdateChildPosition();
}

void AUILayoutWidget::SetLayout(const std::shared_ptr<AUILayoutBase>& pLayout)
{
    AUIAssert(pLayout);
    m_pLayoutManager->SetLayout(pLayout);
    this->UpdateSize();
    this->UpdateChildPosition();
    this->Invalidate();
}

SkRect AUILayoutWidget::GetRect() const
{
    const auto minRange = GetRangeMin();
    const auto maxRange = GetRangeMax();
    return SkRect::MakeLTRB( minRange.fX, minRange.fY, maxRange.fX, maxRange.fY );
}

void AUILayoutWidget::OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value)
{
	if (uiKey == MNV_BACKGROUND_IMAGE)
	{
		std::shared_ptr<AUIDrawable> pDrawable;
		if (value.GetValue(pDrawable))
			SetBackgroundDrawable(pDrawable);
	}
	else
		AUIWidget::OnSetStyleNotion(uiKey, value);
}

void AUILayoutWidget::OnMouseHover()
{
    SuperWidget::OnMouseHover();

    if ( AUIApplication::Instance().IsVisualizeLayout() )
    {
        Invalidate();
    }

    if (IsRefreshDraw())
        Invalidate();
}

void AUILayoutWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();

    if ( AUIApplication::Instance().IsVisualizeLayout() )
    {
        Invalidate();
    }
}

void AUILayoutWidget::OnUpdate()
{
    const auto minRange = GetRangeMin();
    Draw( int( minRange.fX ), int( minRange.fY ), int( GetWidth() ), int( GetHeight() ) );

}

void AUILayoutWidget::OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime)
{
    SuperWidget::OnTickTime(prevTime, curTime);
    m_pLayoutManager->OnTickTime(prevTime, curTime);
}

void AUILayoutWidget::OnSetAllIgnored( bool state )
{
    auto children = GetChildren();
    for ( auto& child : children )
    {
        if ( auto pLayoutChild = child->DynCast< AUILayoutWidget >() )
        {
            pLayoutChild->SetAllIgnored( state );
        }
        else
        {
            child->SetIgnored( state );
        }
    }
}

AUIDrawable * AUILayoutWidget::GetAsDrawable() const
{
    return static_cast<AUIDrawable*>(const_cast<AUILayoutWidget*>(this));
}

