#include "pch.h"
#include "AUISkiaExampleWidget.h"
#include "AUIGalleria.h"
#include "SkFontMgr.h"


namespace {
    const float DefaultWidth = 640.0f;
    const float DefaultHeight = 720.0f;
}

AUISkiaExampleWidget::AUISkiaExampleWidget()
    : m_fBaseScaleX( 1.0f )
    , m_fBaseScaleY( 1.0f )
    , m_fBaseTransX( 0.0f )
    , m_fBaseTransY( 0.0f )
{
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);
    SetDefaultSize( DefaultWidth, DefaultHeight );

}

AUISkiaExampleWidget::~AUISkiaExampleWidget()
{

}

void AUISkiaExampleWidget::OnDraw( SkCanvas * const canvas )
{
    SuperWidget::OnDraw( canvas );

    canvas->translate( m_fBaseTransX, m_fBaseTransY );

    // TODO : Scale 변환의 경우 늘어나는 위치 중심을 조절할 필요가 있음
    canvas->scale( m_fBaseScaleX, m_fBaseScaleY );


    const auto rect = GetDrawBound();


    //////////////////////////////////////////////////////////////////////////
    // Basic defines
    const SkVector radii[4] = { SkVector::Make( 5.0f, 5.0f ), SkVector::Make( 9.0f, 9.0f ), SkVector::Make( 5.0f, 5.0f ), SkVector::Make( 9.0f, 9.0f ) };
    SkPaint textPaint;
    textPaint.setColor(kAUIColorBlack );
    textPaint.setAntiAlias( true );
    textPaint.setTextSize( 13.0f );
    textPaint.setTextEncoding( SkPaint::kUTF16_TextEncoding );
    SkPaint defaultBorderPaint;
    defaultBorderPaint.setColor(kAUIColorBlack );
    defaultBorderPaint.setStyle( SkPaint::kStroke_Style );
    SkPaint colorPaint;
    colorPaint.setAntiAlias( true );
    SkPaint colorStrokePaint;
    colorStrokePaint.setAntiAlias( true );
    colorStrokePaint.setStyle( SkPaint::kStroke_Style );
    AUIGalleria galleria;
    auto pAliceBitmap = galleria.GetFromResource( L"basic_images/no_image.png" );
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // Text
    AUICanvasHelper canvasHelper( canvas );
    canvasHelper.drawText( L"1st Milestone", 0.0f, 15.0f, textPaint );
    // Text by bound
    SkRect textRegion = SkRect::MakeXYWH( 100.0f, 0.0f, 100.0f, 15.0f );
    canvasHelper.drawText( L"헬로우, 월드!", textRegion, AUITextVertAlign::kCenter, AUITextHorzAlign::kCenter, true, textPaint );
    canvas->drawRect( textRegion, defaultBorderPaint );
    //////////////////////////////////////////////////////////////////////////
    canvas->translate( 0.0f, 20.0f );

    //////////////////////////////////////////////////////////////////////////
    // Font Family Test
    SkPaint textFontChange;
    textFontChange.setColor(kAUIColorRed);
    textFontChange.setAntiAlias(true);
    textFontChange.setTextSize(13.0f);
    textFontChange.setTextEncoding(SkPaint::kUTF16_TextEncoding);
    canvasHelper.drawText(L"1st Milestone", 0.0f, 15.0f, textFontChange);
    // Text by bound
    //////////////////////////////////////////////////////////////////////////
    canvas->translate(0.0f, 20.0f);

    //////////////////////////////////////////////////////////////////////////
    // Rectangle shape
    float shapesOffsetX = 10.0f;
    colorPaint.setColor(kAUIColorPastelRed );
    canvas->drawRect( SkRect::MakeXYWH( shapesOffsetX, 0.0f, 25.0f, 25.0f ), colorPaint );
    shapesOffsetX += 25.0f + 10.0f;
    // Rounded Rectangle shape
    colorPaint.setColor(kAUIColorPastelGreen );
    SkRRect roundedRect;
    roundedRect.setRectRadii( SkRect::MakeXYWH( shapesOffsetX, 0.0f, 25.0f, 25.0f ), radii );
    canvas->drawRRect( roundedRect, colorPaint );
    shapesOffsetX += 25.0f + 10.0f;
    // Oval shape
    colorPaint.setColor(kAUIColorPastelBlue );
    canvas->drawOval( SkRect::MakeXYWH( shapesOffsetX, 0.0f, 45.0f, 25.0f ), colorPaint );
    shapesOffsetX += 45.0f + 10.0f;
    // Circle shape
    colorPaint.setColor(kAUIColorPastelBrown );
    canvas->drawCircle( shapesOffsetX + 12.5f, 12.5f, 12.5f, colorPaint );
    shapesOffsetX += 25.0f + 10.0f;
    // Arc (Sweep)
    colorPaint.setColor(kAUIColorPastelViolet );
    canvas->drawArc( SkRect::MakeXYWH( shapesOffsetX, 0.0f, 45.0f, 25.0f ), -90.0f, 300.0f, true, colorPaint );
    shapesOffsetX += 45.0f + 10.0f;
    //////////////////////////////////////////////////////////////////////////
    canvas->translate( 0.0f, 30.0f );


    //////////////////////////////////////////////////////////////////////////
    // Rectangle shape
    shapesOffsetX = 10.0f;
    colorStrokePaint.setColor(kAUIColorPastelRed );
    canvas->drawRect( SkRect::MakeXYWH( shapesOffsetX, 0.0f, 25.0f, 25.0f ), colorStrokePaint );
    shapesOffsetX += 25.0f + 10.0f;
    // Rounded Rectangle shape
    colorStrokePaint.setColor(kAUIColorPastelGreen );
    roundedRect.setRectRadii( SkRect::MakeXYWH( shapesOffsetX, 0.0f, 25.0f, 25.0f ), radii );
    canvas->drawRRect( roundedRect, colorStrokePaint );
    shapesOffsetX += 25.0f + 10.0f;
    // Oval shape
    colorStrokePaint.setColor(kAUIColorPastelBlue );
    canvas->drawOval( SkRect::MakeXYWH( shapesOffsetX, 0.0f, 45.0f, 25.0f ), colorStrokePaint );
    shapesOffsetX += 45.0f + 10.0f;
    // Circle shape
    colorStrokePaint.setColor(kAUIColorPastelBrown );
    canvas->drawCircle( shapesOffsetX + 12.5f, 12.5f, 12.5f, colorStrokePaint );
    shapesOffsetX += 25.0f + 10.0f;
    // Arc (Sweep)
    colorStrokePaint.setColor(kAUIColorPastelViolet );
    canvas->drawArc( SkRect::MakeXYWH( shapesOffsetX, 0.0f, 45.0f, 25.0f ), -90.0f, 300.0f, true, colorStrokePaint );
    shapesOffsetX += 45.0f + 10.0f;
    colorStrokePaint.setColor(kAUIColorPastelOrange );
    canvas->drawArc( SkRect::MakeXYWH( shapesOffsetX, 0.0f, 45.0f, 25.0f ), -90.0f, 300.0f, false, colorStrokePaint );
    shapesOffsetX += 45.0f + 10.0f;
    //////////////////////////////////////////////////////////////////////////
    canvas->translate( 0.0f, 30.0f );


    //////////////////////////////////////////////////////////////////////////
    // Lines
    SkPaint defaultLinePaint;
    defaultLinePaint.setColor(kAUIColorBlack );
    canvas->drawLine( 10.0f, 0.0f, rect.width() - 10.0f, 0.0f, defaultLinePaint );
    canvas->translate( 0.0f, 5.0f );
    defaultLinePaint.setStrokeWidth( 2.0f );
    canvas->drawLine( 10.0f, 0.0f, rect.width() - 10.0f, 0.0f, defaultLinePaint );
    canvas->translate( 0.0f, 5.0f );
    defaultLinePaint.setStrokeWidth( 3.0f );
    canvas->drawLine( 10.0f, 0.0f, rect.width() - 10.0f, 0.0f, defaultLinePaint );
    canvas->translate( 0.0f, 5.0f );
    defaultLinePaint.setStrokeWidth( 4.0f );
    canvas->drawLine( 10.0f, 0.0f, rect.width() - 10.0f, 0.0f, defaultLinePaint );
    canvas->translate( 0.0f, 5.0f );
    defaultLinePaint.setStrokeWidth( 5.0f );
    canvas->drawLine( 10.0f, 0.0f, rect.width() - 10.0f, 0.0f, defaultLinePaint );
    canvas->translate( 0.0f, 5.0f );
    //////////////////////////////////////////////////////////////////////////
    canvas->translate( 0.0f, 10.0f );


    //////////////////////////////////////////////////////////////////////////
    // Dash effects
    const std::array< float, 2 > dash0 = { 1.0f, 1.0f };
    SkPaint pathEffectPaint;
    pathEffectPaint.setColor(kAUIColorBlack );
    pathEffectPaint.setStrokeWidth( 2.0f );
    pathEffectPaint.setStyle( SkPaint::kStroke_Style );
    pathEffectPaint.setPathEffect( SkDashPathEffect::Make( dash0.data(), static_cast<int>( dash0.size() ), 0.0f ) );
    canvas->drawLine( 10.0f, 0.0f, rect.width() - 10.0f, 0.0f, pathEffectPaint );
    canvas->translate( 0.0f, 5.0f );
    // Custom Dash
    const std::array< float, 4 > dash1 = { 5.0f, 1.0f, 3.0f, 2.0f };
    pathEffectPaint.setPathEffect( SkDashPathEffect::Make( dash1.data(), static_cast<int>( dash1.size() ), 0.0f ) );
    canvas->drawLine( 10.0f, 0.0f, rect.width() - 10.0f, 0.0f, pathEffectPaint );
    canvas->translate( 0.0f, 5.0f );
    //////////////////////////////////////////////////////////////////////////
    canvas->translate( 0.0f, 10.0f );


    //////////////////////////////////////////////////////////////////////////
    // Define Path
    SkPaint pathPaint;
    pathPaint.setAntiAlias( true );
    pathPaint.setColor(kAUIColorPastelMagenta );
    pathPaint.setStrokeWidth( 2.0f );
    SkPath myPath;
    myPath.moveTo( 10.0f, 0.0f );
    myPath.quadTo( 25.0f, 15.0f, 80.0f, 0.0f );
    myPath.addRect( 80.0f, 0.0f, 130.0f, 25.0f );
    myPath.moveTo( 130.0f, 25.0f );
    myPath.lineTo( 180.0f, 5.0f );
    myPath.lineTo( 130.0f, 5.0f );
    // Path fill
    canvas->drawPath( myPath, pathPaint );
    canvas->translate( 0.0f, 28.0f );
    // Path stroke
    pathPaint.setStyle( SkPaint::kStroke_Style );
    canvas->drawPath( myPath, pathPaint );
    canvas->translate( 0.0f, 28.0f );
    //////////////////////////////////////////////////////////////////////////
    canvas->translate( 0.0f, 20.0f );



    //////////////////////////////////////////////////////////////////////////
    // Define curve path
    //SkPath curvePath;
    //curvePath.moveTo( 10.0f, 0.0f );
    //curvePath.quadTo( 30.0f, 30.0f, 100.0f, 0.0f );
    //curvePath.quadTo( 180.0f, -10.0f, 200.0f, 20.0f );
    //SkPaint curvePathPaint;
    //curvePathPaint.setAntiAlias( true );
    //curvePathPaint.setColor( ColorSkyBlue );
    //curvePathPaint.setStrokeWidth( 2.0f );
    //curvePathPaint.setTextSize( 10.0f );
    //// Path
    //curvePathPaint.setStyle( SkPaint::kStroke_Style );
    //canvas->drawPath( curvePath, curvePathPaint );
    //// Text
    //curvePathPaint.setColor( ColorBlack );
    //curvePathPaint.setStyle( SkPaint::kFill_Style );
    //curvePathPaint.setTextEncoding( SkPaint::kUTF16_TextEncoding );
    //canvasHelper.drawTextOnPath( L"Hello, World! 곡선 위에서 헬로우, 월드! 외쳐!", curvePath, nullptr, curvePathPaint );
    //canvas->translate( 0.0f, 30.0f );
    //////////////////////////////////////////////////////////////////////////
    canvas->translate( 0.0f, 5.0f );


    //////////////////////////////////////////////////////////////////////////
    // Inner canvas
    colorPaint.setColor(kAUIColorSkyMagenta );
    SkBitmap myBitmap;
    myBitmap.allocN32Pixels( 600, 100 );
    SkCanvas myCanvas( myBitmap );
    myCanvas.clear(kAUIColorTransparent );
    myCanvas.drawColor(SkColorSetARGB(128, 120, 180, 210));
    myCanvas.drawRect( SkRect::MakeXYWH( 10.0f, 10.0f, 300.0f, 50.0f ), colorPaint );
    canvas->drawBitmap( myBitmap, 10.0f, 0.0f );
    //////////////////////////////////////////////////////////////////////////
    canvas->translate( 0.0f, 110.0f );


    //////////////////////////////////////////////////////////////////////////
    // Using bitmaps
    float bitmapOffsetX = 0.0f;
    canvas->drawImage( pAliceBitmap, bitmapOffsetX, 0.0f );
    bitmapOffsetX += pAliceBitmap->width() + 5.0f;
    // Change opacity
    SkPaint opacityPaint;
    opacityPaint.setAlpha( 128 );
    canvas->drawImage( pAliceBitmap, bitmapOffsetX, 0.0f, &opacityPaint );
    bitmapOffsetX += pAliceBitmap->width() + 5.0f;
    //// Blur filter
    //SkPaint blurPaint;
    //blurPaint.setAntiAlias( true );
    //blurPaint.setImageFilter( SkBlurImageFilter::Make( SkBlurStyle::kNormal_SkBlurStyle, 5.0f ) );
    //canvas->drawImage( pAliceBitmap, bitmapOffsetX, 0.0f, &blurPaint );
    //bitmapOffsetX += pAliceBitmap->width() + 5.0f;
    // Bitmap shader
    auto localMat = SkMatrix::MakeScale( 0.7f );
    localMat.postRotate( 30.0f );
    SkPaint shaderPaint;
    shaderPaint.setAntiAlias( true );
    shaderPaint.setShader(pAliceBitmap->makeShader(SkShader::kRepeat_TileMode, SkShader::kRepeat_TileMode, &localMat ) );
    canvas->drawRect( SkRect::MakeXYWH( bitmapOffsetX, 0.0f, static_cast<SkScalar>( pAliceBitmap->width() ), static_cast<SkScalar>( pAliceBitmap->height() ) ), shaderPaint );
    bitmapOffsetX += pAliceBitmap->width() + 5.0f;
    //////////////////////////////////////////////////////////////////////////
    canvas->translate( 0.0f, pAliceBitmap->height() + 10.0f );




    //////////////////////////////////////////////////////////////////////////
    // Canvas state
    bitmapOffsetX = 10.0f;
    canvas->save();
    canvas->translate( bitmapOffsetX, 0.0f );
    canvas->drawImage( pAliceBitmap, 0.0f, 0.0f );
    canvas->restore();
    bitmapOffsetX += pAliceBitmap->width() + 10.0f;
    // Scale
    do {
        SkAutoCanvasRestore autorestore( canvas, true );
        canvas->translate( bitmapOffsetX, 0.0f );
        canvas->scale( 2.0f, 1.5f );
        canvas->drawImage( pAliceBitmap, 0.0f, 0.0f );
        bitmapOffsetX += pAliceBitmap->width() + 10.0f;
    } while ( false );

}

bool AUISkiaExampleWidget::OnMouseMove( MAUIMouseEvent::EventFlag flag )
{
    if ( IsMouseMDown() )
    {
        auto x = GetMouseLocPosX();
        auto y = GetMouseLocPosY();
        const auto diffX = x - m_fPrevMDownPosX;
        const auto diffY = y - m_fPrevMDownPosY;

        m_fBaseTransX += diffX * m_fBaseScaleX;
        m_fBaseTransY += diffY * m_fBaseScaleY;

        m_fPrevMDownPosX = x;
        m_fPrevMDownPosY = y;

    }

    Invalidate();
    return true;
}

bool AUISkiaExampleWidget::OnMouseWheel( MAUIMouseEvent::EventFlag flag, float delta )
{
    if ( delta > 0.0f )
    {
        m_fBaseScaleX += 0.05f;
        m_fBaseScaleY += 0.05f;
    }
    else if ( delta < 0.0f )
    {
        m_fBaseScaleX -= 0.05f;
        m_fBaseScaleY -= 0.05f;
    }

    Invalidate();

    return true;
}

bool AUISkiaExampleWidget::OnMouseMBtnDown( MAUIMouseEvent::EventFlag flag )
{
    m_fPrevMDownPosX = GetMouseLocPosX();
    m_fPrevMDownPosY = GetMouseLocPosY();

    Invalidate();

    return true;
}

bool AUISkiaExampleWidget::OnMouseMBtnUp( MAUIMouseEvent::EventFlag flag )
{
    Invalidate();

    return true;
}
