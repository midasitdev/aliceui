#include "pch.h"
#include "AUICheckboxWidget.h"
#include "AUISmootherStepInterpolator.h"
#include "AUICheckboxDrawable.h"

namespace {
    constexpr SkScalar DefaultWidth = 16.0f;
    constexpr SkScalar DefaultHeight = 16.0f;
    constexpr std::chrono::milliseconds AnimTickLength( 200 );
}

AUICheckboxWidget::AUICheckboxWidget()
    : m_bUseIndeterminate( false )
    , m_bPrevChecked( false )
    , m_bPrevCheckedIndeterminate( false )
    , m_AnimTickLength( AnimTickLength )
{
    SetDefaultSize( DefaultWidth, DefaultHeight );
    SetChecked( false );
	SetCheckable(true);
    SetClickable( true );
    SetCheckAnimDrawable( std::make_shared< AUICheckboxDrawable >() );
}

AUICheckboxWidget::AUICheckboxWidget( bool state )
    : m_bUseIndeterminate( false )
    , m_bPrevChecked( false )
    , m_bPrevCheckedIndeterminate( false )
    , m_AnimTickLength( AnimTickLength )
{

    SetDefaultSize( DefaultWidth, DefaultHeight );
    SetClickable( true );
	SetCheckable(true);
    SetChecked( state );
    SetCheckAnimDrawable( std::make_shared< AUICheckboxDrawable >() );
}

AUICheckboxWidget::~AUICheckboxWidget()
{

}

void AUICheckboxWidget::OnDestroy()
{
	SuperWidget::OnDestroy();
}

void AUICheckboxWidget::SetLocked( bool locked )
{
    SetCheckable( !locked );
}

bool AUICheckboxWidget::IsLocked() const
{
    return !IsCheckable();
}

void AUICheckboxWidget::OnDraw( SkCanvas* const canvas )
{
    SuperWidget::OnDraw( canvas );
	if (auto pFG = GetForegroundLayer())
		return;

	if (IsDisabled())
	{

		return;
	}
    if ( IsPrevChecked() != IsChecked() || IsPrevCheckedIndeterminate() != IsCheckedIndeterminate() )
    {

        if ( IsAnimRunning() == false )
            StartAnimRunning();
    }

    float checkWeight = 1.0f;
    if ( IsAnimRunning() )
    {
        Invalidate();
        static auto pInterpolator = std::make_shared< AUISmootherStepInterpolator >();
        checkWeight = pInterpolator->GetValueByTime( GetAnimStartTick(), GetAnimStartTick() + GetAnimTickLength(), GetTimeTick() );
        if ( checkWeight >= 1.0f )
        {
            checkWeight = 1.0f;
            StopAnimRunning();
        }
    }

    bool bToggled = false;
    if ( IsChecked() || IsCheckedIndeterminate() )
    {
        if ( checkWeight < 1.0f )
            bToggled = false;
        else
            bToggled = true;
    }
    else
    {
        if ( checkWeight < 1.0f )
            bToggled = true;
        else
            bToggled = false;
        checkWeight = 1.0f - checkWeight;
    }
    if ( bToggled )
    {
        SetPrevChecked( IsChecked() );
        SetPrevCheckedIndeterminate( IsCheckedIndeterminate() );
    }

    if ( auto pAnimDrawable = GetCheckAnimDrawable() )
    {
        pAnimDrawable->SetDrawBound( GetDrawBound() );
        pAnimDrawable->SetDrawPadding( SkRect::MakeLTRB( GetPaddingLeft(), GetPaddingTop(), GetPaddingRight(), GetPaddingBottom() ) );
        pAnimDrawable->SetDrawUIState( GetDrawUIState() );
        pAnimDrawable->SetBlendFactor( checkWeight );
        pAnimDrawable->Draw( canvas );
    }

}

void AUICheckboxWidget::OnMouseEnter()
{
    SuperWidget::OnMouseEnter();

    Invalidate();
}

void AUICheckboxWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();


    Invalidate();
}

bool AUICheckboxWidget::OnMouseLBtnDown( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnDown( flag );

    Invalidate();
    return true;
}

bool AUICheckboxWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{
    if ( IsCheckable() == false )
        return true;

    const auto curChecked = IsChecked();
    if ( IsUseIndeterminate() )
    {
        SetCheckedIndeterminate( false );
    }
    SetChecked( !IsChecked() );

    Invalidate();

    return true;
}

void AUICheckboxWidget::SetBackgroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable)
{
	AUIDrawableWidget::SetBackgroundDrawable(pDrawable);
	SetCheckAnimDrawable(nullptr);
}

void AUICheckboxWidget::SetForegroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable)
{
	AUIDrawableWidget::SetForegroundDrawable(pDrawable);
	SetCheckAnimDrawable(nullptr);
}
