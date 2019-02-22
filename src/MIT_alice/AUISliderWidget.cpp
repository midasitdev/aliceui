#include "pch.h"
#include "AUISliderWidget.h"
#include "AUISliderIndicatorWidget.h"

AUISliderWidget::AUISliderWidget()
    : m_pIndicator(std::make_shared<AUISliderIndicatorWidget>())
    , m_bHorizontal( false )
    , m_RangeMin( 0.0 )
    , m_RangeMax( 1.0 )
    , m_Value( 0.0 )
{
    SetClickable( true );
    SetDraggable( true );
    SetDefaultSize( 50, 50 );
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);
    SetPaddingLeft( 5.0f );
    SetPaddingRight( 5.0f );

    AddSubWidget( m_pIndicator );
}

AUISliderWidget::~AUISliderWidget()
{

}

void AUISliderWidget::SetValue( SkScalar val )
{
    m_Value = val;

    UpdateChildPosition();
    Invalidate();
}

SkScalar AUISliderWidget::GetValue() const
{
    return m_Value;
}

void AUISliderWidget::SetHorizontal( bool val )
{
    m_bHorizontal = val;
    Invalidate();
}

void AUISliderWidget::OnDraw( SkCanvas* const canvas )
{
    SuperWidget::OnDraw( canvas );
    const auto rect = GetRect();
    const auto thick = 5.0f;
    const auto weight = std::clamp((GetValue() - GetSlideRangeMin()) / (GetSlideRangeMax() - GetSlideRangeMin()), 0.0f, 1.0f);
    const auto indicatorSize = m_pIndicator->GetSize();

    SkScalar lineStart = 0.0f;
    SkScalar lineEnd = 0.0f;
    SkScalar validRange = 0.0f;
    SkScalar indicatorPosX = 0.0f;
    SkScalar indicatorPosY = 0.0f;
    if (IsHorizontal())
    {
        lineStart = indicatorSize.fX * 0.5f;
        lineEnd = rect.width() - indicatorSize.fX * 0.5f;

        validRange = rect.width() - indicatorSize.fX;
        indicatorPosX = indicatorSize.fX * 0.5f + validRange * weight;
        indicatorPosY = rect.height() * 0.5f - indicatorSize.fY * 0.5f;
        m_pIndicator->SetPosition(indicatorPosX, indicatorPosY);
    }
    else
    {
        lineStart = indicatorSize.fY * 0.5f;
        lineEnd = rect.height() - indicatorSize.fY * 0.5f;

        validRange = rect.height() - indicatorSize.fY;
        indicatorPosX = rect.width() * 0.5f - indicatorSize.fX * 0.5f;
        indicatorPosY = indicatorSize.fY + validRange * (1.0f - weight);
        m_pIndicator->SetPosition(indicatorPosX, indicatorPosY);
    }

    SkPaint paint1, paint2;
    paint1.setAntiAlias( true );
    paint1.setStyle( SkPaint::kStroke_Style );
    paint1.setStrokeMiter(1.0f);
    paint1.setColor( 0xFF51B7DB );
    paint2 = paint1;
    paint2.setColor( 0xFFE3E4E8 );


    if ( IsHorizontal() )
    {
        const auto indiPos = indicatorPosX;
        canvas->drawLine(lineStart, rect.centerY(), indiPos, rect.centerY(), paint1);
        canvas->drawLine(indiPos, rect.centerY(), lineEnd, rect.centerY(), paint2);
    }
    else
    {
        const auto indiPos = indicatorPosY;
        canvas->drawLine( rect.centerX(), indiPos, rect.centerX(), lineEnd, paint1 );
        canvas->drawLine( rect.centerX(), lineStart, rect.centerX(), indiPos, paint2 );
    }


    SkPaint paintCircle;
    paintCircle.setAntiAlias( true );
    if (weight > 0.5f)
        paintCircle.setColor( paint1.getColor() );
    else
        paintCircle.setColor( paint2.getColor() );
    canvas->drawCircle( rect.centerX(), rect.centerY(), 5.0f, paintCircle );
}

bool AUISliderWidget::OnMouseLBtnDown( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnDown( flag );

    auto x = GetMouseLocPosX();
    auto y = GetMouseLocPosY();

    const auto rect = GetRect();
    if ( IsHorizontal() )
    {
        const auto val = GetSlideRangeMin() + x / rect.width() * ( GetSlideRangeMax() - GetSlideRangeMin() );
        SetValue( val );
    }
    else
    {
        const auto val = GetSlideRangeMin() + ( 1.0f - y / rect.height() ) * ( GetSlideRangeMax() - GetSlideRangeMin() );
        SetValue( val );
    }

    return true;

}

bool AUISliderWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnUp( flag );

    auto x = GetMouseLocPosX();
    auto y = GetMouseLocPosY();
    const auto rect = GetRect();
    if ( IsHorizontal() )
    {
        const auto val = GetSlideRangeMin() + x / rect.width() * ( GetSlideRangeMax() - GetSlideRangeMin() );
        SetValue( val );
    }
    else
    {
        const auto val = GetSlideRangeMin() + ( 1.0f - y / rect.height() ) * ( GetSlideRangeMax() - GetSlideRangeMin() );
        SetValue( val );
    }

    return true;

}

bool AUISliderWidget::OnMouseMove( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseMove( flag );

    auto x = GetMouseLocPosX();
    auto y = GetMouseLocPosY();
    if ( IsMouseLDown() )
    {
        const auto rect = GetRect();
        if ( IsHorizontal() )
        {
            const auto val = GetSlideRangeMin() + x / rect.width() * ( GetSlideRangeMax() - GetSlideRangeMin() );
            SetValue( val );
        }
        else
        {
            const auto val = GetSlideRangeMin() + ( 1.0f - y / rect.height() ) * ( GetSlideRangeMax() - GetSlideRangeMin() );
            SetValue( val );
        }

        Invalidate();
    }



    return true;

}
