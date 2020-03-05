#include "pch.h"
#include "AUIImageCaptionButtonWidget.h"
#include "AUIImageWidget.h"
#include "AUITextWidget.h"
#include "AUIStateDrawable.h"
#include "AUIRoundRectShape.h"
#include "AUIShapeDrawable.h"

namespace {
    constexpr SkScalar DefaultWidth = 80.0f;
    constexpr SkScalar DefaultHeight = 20.0f;
    constexpr SkScalar DefaultImageWidth = 30.0f;
    constexpr SkScalar DefaultImageHeight = 20.0f;
}

AUIImageCaptionButtonWidget::AUIImageCaptionButtonWidget()
	: AUIImageCaptionButtonWidget(false) {}

AUIImageCaptionButtonWidget::AUIImageCaptionButtonWidget( bool horizontal )
    : AUILinearLayoutWidget( horizontal )
    , m_Style( AUIImageCaptionStyle::kImageAndText )
    , m_pCaption( std::make_shared< AUITextWidget >() )
    , m_pImage( std::make_shared< AUIImageWidget >() )
{
	m_pImage->SetPropLayoutGravityCenter(true);

    // Don't receive event
    //m_pImage->Freeze();
    //m_pCaption->Freeze();

	m_pImage->SetEventPassThrough(true);
	m_pCaption->SetEventPassThrough(true);
	
	AddSubWidget( m_pImage );
    AddSubWidget( m_pCaption );

    SetImageDefaultSize( DefaultImageWidth, DefaultImageHeight );
    SetDefaultSize( DefaultWidth, DefaultHeight );

    SetClickable( true );

    constexpr SkScalar radii[] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };

    auto pDefaultBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pDefaultBG->SetColor( SkColorSetRGB( 245, 245, 245 ) );
    pDefaultBG->SetUseAA( true );

    auto pHoverBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pHoverBG->SetColor( SkColorSetRGB( 245, 245, 245 ) );
    pHoverBG->SetUseAA( true );

    auto pPressBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pPressBG->SetColor( SkColorSetRGB( 234, 238, 244 ) );
    pPressBG->SetUseAA( true );

    auto pDisableBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pDisableBG->SetColor( SkColorSetRGB( 221, 221, 221 ) );
    pDisableBG->SetUseAA( true );

    auto pCheckBG = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pCheckBG->SetColor( SkColorSetRGB( 245, 245, 245 ) );
    pCheckBG->SetUseAA( true );

    auto pOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pOutline->SetColor( SkColorSetRGB( 197, 197, 197 ) );
    pOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pOutline->SetStrokeWidth( 2.0f );
    pOutline->SetUseAA( true );

    auto pHoverOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pHoverOutline->SetColor( SkColorSetRGB( 130, 186, 255 ) );
    pHoverOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pHoverOutline->SetStrokeWidth( 2.0f );
    pHoverOutline->SetUseAA( true );

    auto pPressOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pPressOutline->SetColor( SkColorSetRGB( 130, 186, 255 ) );
    pPressOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pPressOutline->SetStrokeWidth( 2.0f );
    pPressOutline->SetUseAA( true );


    auto pCheckOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pCheckOutline->SetColor( SkColorSetRGB( 161, 174, 194 ) );
    pCheckOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pCheckOutline->SetStrokeWidth( 2.0f );
    pCheckOutline->SetUseAA( true );


    auto pDisableOutline = std::make_shared< AUIShapeDrawable >( std::make_shared< AUIRoundRectShape >( radii ) );
    pDisableOutline->SetColor( SkColorSetRGB( 204, 204, 204 ) );
    pDisableOutline->SetStrokeStyle( SkPaint::kStroke_Style );
    pDisableOutline->SetStrokeWidth( 2.0f );
    pDisableOutline->SetUseAA( true );

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


    SetBackgroundDrawable( pStateDrawable );
}

AUIImageCaptionButtonWidget::~AUIImageCaptionButtonWidget()
{

}

void AUIImageCaptionButtonWidget::SetCaption( const std::wstring& text )
{
    m_pCaption->SetCaption( text );
}

void AUIImageCaptionButtonWidget::SetCaptionHorzAlign( AUITextHorzAlign align )
{
    m_pCaption->SetCaptionHorzAlign( align );
}

void AUIImageCaptionButtonWidget::SetCaptionVertAlign( AUITextVertAlign align )
{
    m_pCaption->SetCaptionVertAlign( align );
}

void AUIImageCaptionButtonWidget::SetCaptionSize( float size )
{
    m_pCaption->SetCaptionSize( size );
}

void AUIImageCaptionButtonWidget::ResetCaptionColor(const SkColor color)
{
    m_pCaption->ResetCaptionColor(color);
}

void AUIImageCaptionButtonWidget::SetCaptionColor( const SkColor color )
{
    m_pCaption->SetCaptionColor( color );
}

void AUIImageCaptionButtonWidget::SetCaptionColor( AUIState::Index idx, bool state, const SkColor color )
{
    m_pCaption->SetCaptionColor( idx, state, color );
}

void AUIImageCaptionButtonWidget::SetCaptionStyle(SkFontStyle style )
{
    m_pCaption->SetCaptionStyle( style );
}

void AUIImageCaptionButtonWidget::SetCaptionFontName( const std::wstring& name )
{
    m_pCaption->SetCaptionFontName( name );
}

void AUIImageCaptionButtonWidget::SetCaptionMarginLTRB(float marginLeft, float marginTop, float marginRight, float marginBottom)
{
	m_pCaption->SetMarginLTRB(marginLeft, marginTop, marginRight, marginBottom);
}

std::wstring AUIImageCaptionButtonWidget::GetCaption() const
{
    return m_pCaption->GetCaption();
}

AUITextHorzAlign AUIImageCaptionButtonWidget::GetCaptionHorzAlign() const
{
    return m_pCaption->GetCaptionHorzAlign();
}

AUITextVertAlign AUIImageCaptionButtonWidget::GetCaptionVertAlign() const
{
    return m_pCaption->GetCaptionVertAlign();
}

float AUIImageCaptionButtonWidget::GetCaptionSize() const
{
    return m_pCaption->GetCaptionSize();
}

SkColor AUIImageCaptionButtonWidget::GetCaptionColor() const
{
    return m_pCaption->GetCaptionColor();
}

SkFontStyle AUIImageCaptionButtonWidget::GetCaptionStyle() const
{
    return m_pCaption->GetCaptionStyle();
}

std::wstring AUIImageCaptionButtonWidget::GetCaptionFontName() const
{
    return m_pCaption->GetCaptionFontName();
}

SkColor AUIImageCaptionButtonWidget::GetCaptionColor( AUIState::Index idx, bool state ) const
{
    return m_pCaption->GetCaptionColor( idx, state );
}

void AUIImageCaptionButtonWidget::SetImageDrawable( const std::shared_ptr< AUIDrawable >& pBitmap )
{
    m_pImage->SetImageDrawable( pBitmap );
}

void AUIImageCaptionButtonWidget::OnSetChecked( bool state )
{
    m_pCaption->SetChecked( state );
    m_pImage->SetChecked( state );
}

void AUIImageCaptionButtonWidget::OnMouseEnter()
{
    SuperWidget::OnMouseEnter();

    // TODO : milestone ±ò²ûÇÏ°Ô
    GetCaptionWidget()->SetHovered( true );
    GetImageWidget()->SetHovered( true );

    Invalidate();
    InvalidateChildren();
}

void AUIImageCaptionButtonWidget::OnMouseHover()
{
    SuperWidget::OnMouseHover();

    // TODO : milestone ±ò²ûÇÏ°Ô
    GetCaptionWidget()->SetHovered( true );
    GetImageWidget()->SetHovered( true );


    Invalidate();
    InvalidateChildren();
}

void AUIImageCaptionButtonWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();

    // TODO : milestone ±ò²ûÇÏ°Ô
    GetCaptionWidget()->SetHovered( false );
    GetImageWidget()->SetHovered( false );
    GetCaptionWidget()->SetPressed( false );
    GetImageWidget()->SetPressed( false );


    Invalidate();
    InvalidateChildren();
}

bool AUIImageCaptionButtonWidget::OnMouseLBtnDown( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnDown( flag );



    // TODO : milestone ±ò²ûÇÏ°Ô
    GetCaptionWidget()->SetPressed( true );
    GetImageWidget()->SetPressed( true );

    Invalidate();
    InvalidateChildren();

    return true;
}

bool AUIImageCaptionButtonWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{

    SuperWidget::OnMouseLBtnUp( flag );


    // TODO : milestone ±ò²ûÇÏ°Ô
    GetCaptionWidget()->SetPressed( false );
    GetImageWidget()->SetPressed( false );


    Invalidate();
    InvalidateChildren();

    return true;
}

bool AUIImageCaptionButtonWidget::OnMouseLBtnDblClk( MAUIMouseEvent::EventFlag flag )
{
    auto ret = SuperWidget::OnMouseLBtnDblClk( flag );

    if ( IsDisabled() )
        return ret;

    // TODO : milestone ±ò²ûÇÏ°Ô
    GetCaptionWidget()->SetPressed( false );
    GetImageWidget()->SetPressed( false );


    Invalidate();
    InvalidateChildren();

    return true;

}

bool AUIImageCaptionButtonWidget::OnMouseMove( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseMove( flag );


    Invalidate();
    InvalidateChildren();

    return true;
}

void AUIImageCaptionButtonWidget::SetUseMultiline( bool use )
{
    m_pCaption->SetUseMultiline( use );
}

bool AUIImageCaptionButtonWidget::IsUseMultiline() const
{
    return m_pCaption->IsUseMultiline();
}

void AUIImageCaptionButtonWidget::SetMultilineType( const AUITextLineFeed& type )
{
    m_pCaption->SetMultilineType( type );

}

AUITextLineFeed AUIImageCaptionButtonWidget::GetMultilineType() const
{
    return m_pCaption->GetMultilineType();
}

void AUIImageCaptionButtonWidget::SetImage(const sk_sp<SkImage>& image)
{
    m_pImage->SetImage(image);
}

sk_sp<SkImage> AUIImageCaptionButtonWidget::GetImage() const
{
    return m_pImage->GetImage();
}

void AUIImageCaptionButtonWidget::SetImageMarginLTRB(float marginLeft, float marginTop, float marginRight, float marginBottom)
{
	m_pImage->SetMarginLTRB(marginLeft, marginTop, marginRight, marginBottom);
}

void AUIImageCaptionButtonWidget::SetImageDefaultSize( float width, float height )
{
    m_pImage->SetDefaultSize( width, height );
    //if ( GetImageCaptionStyle() == ImageCaptionStyle::ImageAndText )
    //{
    //    m_pImage->SetDefaultSize( width, height );
    //}
    //else if ( GetImageCaptionStyle() == ImageCaptionStyle::TextOnly )
    //{
    //    m_pImage->SetDefaultSize( 0.0f, 0.0f );
    //}
    //else if ( GetImageCaptionStyle() == ImageCaptionStyle::ImageOnly )
    //{
    //    m_pImage->SetDefaultSize( GetDefaultSize() );
    //}
}

void AUIImageCaptionButtonWidget::OnSetDefaultSize(const AUIScalar2& size)
{
    const auto imgsize = m_pImage->GetDefaultSize();

    if ( GetImageCaptionStyle() == AUIImageCaptionStyle::kImageAndText )
    {
        auto captionwidth = size.fX;
        auto captionheight = size.fY;
        if ( IsHorizontal() )
        {
            captionwidth = (std::max)( 0.0f, captionwidth - imgsize.fX );
        }
        else
        {
            captionheight = (std::max)( 0.0f, captionheight - imgsize.fY );
        }

        m_pCaption->SetDefaultSize( captionwidth, captionheight );
    }
    else if ( GetImageCaptionStyle() == AUIImageCaptionStyle::kImageOnly )
    {
        m_pImage->SetDefaultSize( size );
    }
    else if ( GetImageCaptionStyle() == AUIImageCaptionStyle::kTextOnly )
    {
        m_pCaption->SetDefaultSize( size );
    }
}

void AUIImageCaptionButtonWidget::SetImageCaptionStyle( AUIImageCaptionStyle style )
{
    m_Style = style;

    if ( GetImageCaptionStyle() == AUIImageCaptionStyle::kImageAndText )
    {
        m_pImage->SetIgnored( false );
        m_pCaption->SetIgnored( false );

    }
    else if ( GetImageCaptionStyle() == AUIImageCaptionStyle::kImageOnly )
    {
        m_pImage->SetIgnored( false );
        m_pCaption->SetIgnored( true );

    }
    else if ( GetImageCaptionStyle() == AUIImageCaptionStyle::kTextOnly )
    {
        m_pImage->SetIgnored( true );
        m_pCaption->SetIgnored( false );
    }
    else
    {
        AUIAssert( false );
    }
    SetDefaultSize( GetDefaultSize() );
    UpdateSize();
    UpdateChildPosition();
}
