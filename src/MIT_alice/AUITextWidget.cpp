#include "pch.h"
#include "AUITextWidget.h"
#include "AUIStyleNotion.h"
#include "AUIStringConvert.h"
#include "AUIStringUtil.h"
#include "AUIStyleSheetUtil.h"

namespace {
    constexpr wchar_t DefaultCaption[] = L"Label";
    constexpr bool DefaultFocusable = true;
}

namespace {
    constexpr SkScalar DefaultWidth = 100.0f;
    constexpr SkScalar DefaultHeight = 23.0f;
    constexpr bool DefaultCaptionAntialias = true;
    constexpr SkScalar DefaultCaptionSize = 13.0f;
    constexpr AUITextHorzAlign DefaultHorzAlign = AUITextHorzAlign::kLeft;
    constexpr AUITextVertAlign DefaultVertAlign = AUITextVertAlign::kCenter;
    constexpr SkColor DefaultCaptionColor = SkColorSetRGB( 17, 17, 17 );
}

AUITextWidget::AUITextWidget()
    : m_Caption( DefaultCaption )
    , m_bCaptionAA( DefaultCaptionAntialias )
    , m_fCaptionSize( DefaultCaptionSize )
    , m_MultilineType( AUITextLineFeed::kNewline )
    , m_iMinLines( 1 )
    , m_iMaxLines( ( std::numeric_limits< int >::max )( ) )
    , m_iLines( 0 )
    , m_bUseMultiline(false)
    , m_mapTrueStateCaptionColor{ {AUIState::kDefault, DefaultCaptionColor} }
    , m_mapFalseStateCaptionColor{ {AUIState::kDefault, DefaultCaptionColor} }
{
    SetCaptionHorzAlign( DefaultHorzAlign );
    SetCaptionVertAlign( DefaultVertAlign );

    SetDefaultSize( DefaultWidth, DefaultHeight );

    SetFocusable( DefaultFocusable );
}

AUITextWidget::AUITextWidget( const std::wstring& caption )
    : m_Caption( caption )
    , m_bCaptionAA( DefaultCaptionAntialias )
    , m_fCaptionSize( DefaultCaptionSize )
    , m_MultilineType( AUITextLineFeed::kNewline )
    , m_iMinLines( 1 )
    , m_iMaxLines( ( std::numeric_limits< int >::max )( ) )
    , m_iLines( 0 )
    , m_bUseMultiline( false )
    , m_mapTrueStateCaptionColor{ {AUIState::kDefault, DefaultCaptionColor} }
    , m_mapFalseStateCaptionColor{ {AUIState::kDefault, DefaultCaptionColor} }
{
    SetCaptionHorzAlign( DefaultHorzAlign );
    SetCaptionVertAlign( DefaultVertAlign );

    SetDefaultSize( DefaultWidth, DefaultHeight );

    SetFocusable( DefaultFocusable );
}

AUITextWidget::~AUITextWidget()
{

}

void AUITextWidget::OnDestroy()
{
	SuperWidget::OnDestroy();
}

void AUITextWidget::SetCaption( const std::wstring& text )
{
    const auto targetCaption = OnSetCaption(text);

    if (m_Caption != targetCaption)
        InvalidateCaption();

    m_Caption = targetCaption;
}

void AUITextWidget::SetCaptionHorzAlign( AUITextHorzAlign align )
{
    SetPropGravityLeft( false );
    SetPropGravityCenterHorizontal( false );
    SetPropGravityRight( false );

    switch ( align )
    {
    case AUITextHorzAlign::kLeft:
        SetPropGravityLeft( true );
        break;
    case AUITextHorzAlign::kCenter:
        SetPropGravityCenterHorizontal( true );
        break;
    case AUITextHorzAlign::kRight:
        SetPropGravityRight( true );
        break;
    default:
        AUIAssert( false );
        break;
    }
    InvalidateCaption();
}

void AUITextWidget::SetCaptionVertAlign( AUITextVertAlign align )
{
    SetPropGravityTop( false );
    SetPropGravityCenterVertical( false );
    SetPropGravityBottom( false );

    switch ( align )
    {
    case AUITextVertAlign::kTop:
        SetPropGravityTop( true );
        break;
    case AUITextVertAlign::kCenter:
        SetPropGravityCenterVertical( true );
        break;
    case AUITextVertAlign::kBottom:
        SetPropGravityBottom( true );
        break;
    default:
        AUIAssert( false );
        break;
    }
    InvalidateCaption();
}

void AUITextWidget::SetCaptionColor( const SkColor color )
{
    SetCaptionColor( AUIState::kDefault, true, color );
    SetCaptionColor( AUIState::kDefault, false, color );
}

void AUITextWidget::SetCaptionColor( AUIState::Index idx, bool state, const SkColor color )
{
    if ( state )
    {
        m_mapTrueStateCaptionColor[idx] = color;
    }
    else
    {
        m_mapFalseStateCaptionColor[idx] = color;
    }
}

std::wstring AUITextWidget::GetCaption() const
{
    return OnGetCaption( m_Caption );
}

AUITextHorzAlign AUITextWidget::GetCaptionHorzAlign() const
{
    auto align = AUITextHorzAlign::kLeft;
    if ( GetPropGravityLeft() )
        align = AUITextHorzAlign::kLeft;
    if ( GetPropGravityRight() )
        align = AUITextHorzAlign::kRight;
    if ( GetPropGravityCenterVertical() || GetPropGravityCenter() )
        align = AUITextHorzAlign::kCenter;
    return align;
}

AUITextVertAlign AUITextWidget::GetCaptionVertAlign() const
{
    auto align = AUITextVertAlign::kCenter;
    if ( GetPropGravityTop() )
        align = AUITextVertAlign::kTop;
    if ( GetPropGravityBottom() )
        align = AUITextVertAlign::kBottom;
    if ( GetPropGravityCenterHorizontal() || GetPropGravityCenter() )
        align = AUITextVertAlign::kCenter;
    return align;
}

SkColor AUITextWidget::GetCaptionColor() const
{
    return GetCaptionColor( AUIState::kDefault, true );
}

void AUITextWidget::OnDraw( SkCanvas* const canvas )
{
    SuperWidget::OnDraw( canvas );

    // Caption
    OnDrawCaption( canvas );

}

void AUITextWidget::OnDrawCaption( SkCanvas* const canvas )
{
    if ( IsUseMultiline() )
    {
        OnDrawCaption_Multiline( canvas );
    }
    else
    {
        OnDrawCaption_SingleLine( canvas );
    }

}

void AUITextWidget::OnDrawCaption_SingleLine( SkCanvas* const canvas )
{
    if (0 == m_MeasuredCaption.size())
        return;

    SkPaint captionPaint;
    GetCaptionPaint( captionPaint );

    AUICanvasHelper mcanvas(canvas);
    mcanvas.drawText(m_MeasuredCaption[0], GetCaptionAreaRect(), GetCaptionVertAlign(), GetCaptionHorzAlign(), captionPaint);
}

void AUITextWidget::OnDrawCaption_Multiline( SkCanvas* const canvas )
{
    if (0 == m_MeasuredCaption.size())
        return;

    const auto captionAreaRect = GetCaptionAreaRect();

    SkPaint captionPaint;
    GetCaptionPaint(captionPaint);

    AUICanvasHelper mcanvas(canvas);
    mcanvas.drawMultilineText(m_MeasuredCaption, captionAreaRect, GetCaptionVertAlign(), GetCaptionHorzAlign(), captionPaint, GetLineHeight());
}

void AUITextWidget::OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value)
{
	
	switch (uiKey)
	{
	case 	MNV_TEXT_HORZONTAL_ALIGN:
	{
		AUITextHorzAlign eTexHorzAlign;
		if (value.GetValue(eTexHorzAlign))
		{
			SetCaptionHorzAlign(eTexHorzAlign);
		}
	}
	break;
	case 	MNV_TEXT_VERTICAL_ALIGN:
	{
		AUITextVertAlign eTexVertAlign;
		if (value.GetValue(eTexVertAlign))
		{
			SetCaptionVertAlign(eTexVertAlign);
		}

	}
	break;
	case 	MNV_FONT_SIZE:
	{
		int iSize;
		if (value.GetValue(iSize))
		{
			SetCaptionSize((SkScalar)iSize);
		}

	}
	break;
	case 	MNV_FONT_COLOR:
	{
		std::wstring strcolor;
		if (value.GetValue(strcolor))
		{
			SkColor color;
			if (AUIStyleSheetUtil::ToColorValue(strcolor, color))
				SetCaptionColor(color);
		}
	}
	break;
	case 	MNV_FONT_DISABLED_COLOR:
	{
		std::wstring strcolor;
		if (value.GetValue(strcolor))
		{
			SkColor color;
			if (AUIStyleSheetUtil::ToColorValue(strcolor, color))
				SetCaptionColor(AUIState::kDisabled, true, color);
		}
	}
	break;
	case 	MNV_FONT_STYLE:
	{
		SkFontStyle eFontStyle;
		if (value.GetValue(eFontStyle))
		{
			SetCaptionStyle(eFontStyle);
		}
	}
	break;
	case 	MNV_FONT_FAMILY:
	{
		std::vector< std::wstring > arrFonts;
		if (value.GetValue(arrFonts))
		{
			std::wstring targetFontName;
			for (auto& f : arrFonts)
			{
                const auto fontname = AUIStringConvert::WCSToUTF8(f);
				auto pType = SkTypeface::MakeFromName(fontname.c_str(), SkFontStyle::Normal());
				if (pType)
				{
					targetFontName = AUIStringConvert::UTF8ToWCS(fontname);
					break;
				}
			}
			if (false == targetFontName.empty())
				SetCaptionFontName(targetFontName);
		}

	}
	break;
	default:
		AUIDrawableWidget::OnSetStyleNotion(uiKey, value);
	}
}

void AUITextWidget::SetBackgroundDrawable( const std::shared_ptr< AUIDrawable >& pDrawable )
{
    m_pBackgroundDrawable = pDrawable;
    SetLayer( BackgroundLayer, m_pBackgroundDrawable );
    Invalidate();
}

void AUITextWidget::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    auto baseSize = GetDefaultSize();
    MeasureCaption(baseSize, width, widthSpec, height, heightSpec);
    SetMeasureSize(baseSize);
}

SkRect AUITextWidget::GetCaptionAreaRect() const
{
    const auto captionHorzAlign = GetCaptionHorzAlign();
    const auto captionVertAlign = GetCaptionVertAlign();

    float captionRectLeft = ( std::max )( 1.0f, GetPaddingLeft() );
    float captionRectRight = GetWidth() - ( std::max )( 1.0f, GetPaddingRight() );

    float captionRectTop = ( std::max )( 1.0f, GetPaddingTop() );
    float captionRectBottom = GetHeight() - ( std::max )( 1.0f, GetPaddingBottom() );

    return SkRect::MakeLTRB( captionRectLeft, captionRectTop, captionRectRight, captionRectBottom );
}

void AUITextWidget::GetCaptionPaint( SkPaint& paint ) const
{
    paint.setAntiAlias( GetCaptionAntialias() );
    paint.setStyle( SkPaint::kFill_Style );
    paint.setTextSize( GetCaptionSize() );
    paint.setTextEncoding( SkPaint::kUTF16_TextEncoding );
    paint.setColor( GetCaptionColor( AUIState::kDefault, true ) );

    if ( IsDisabled() )
    {
		if (HasTrueStateColor(AUIState::kDisabled))
			paint.setColor( GetCaptionColor( AUIState::kDisabled, true ) );
    }
    else
    {
        if ( IsChecked() )
        {
            if ( HasTrueStateColor( AUIState::kChecked ) )
            {
                paint.setColor( GetCaptionColor( AUIState::kChecked, true ) );
            }
        }
        else
        {
            if ( HasFalseStateColor( AUIState::kChecked ) )
            {
                paint.setColor( GetCaptionColor( AUIState::kChecked, false ) );
            }
        }

        if ( IsMouseHover() )
        {
            if ( HasTrueStateColor( AUIState::kMouseHovered ) )
            {
                paint.setColor( GetCaptionColor( AUIState::kMouseHovered, true ) );
            }
        }

    }

    // Setup font
    static auto pFontMgr = SkFontMgr::RefDefault();
    AUIAssert(pFontMgr);
    static SkString defaultFontName;
    if (defaultFontName.isEmpty())
    {
        SkTypeface::MakeDefault()->getFamilyName(&defaultFontName);
    }
    const auto kDefaultFontStyle = SkFontStyle::Normal();
    if (GetCaptionFontName().empty() == false )
    {
        const auto fontName = AUIStringConvert::WCSToUTF8(GetCaptionFontName().c_str());
        sk_sp<SkTypeface> pTypeface(pFontMgr->matchFamilyStyle(fontName.c_str(), GetCaptionStyle()));
        if (nullptr == pTypeface)
            pTypeface.reset(pFontMgr->matchFamilyStyle(defaultFontName.c_str(), GetCaptionStyle()));
        paint.setTypeface(pTypeface);
    }
    else if (!(m_captionStyle == kDefaultFontStyle))
    {
        sk_sp<SkTypeface> pTypeface(pFontMgr->matchFamilyStyle(defaultFontName.c_str(), GetCaptionStyle()));
        paint.setTypeface(pTypeface);
    }

}


SkColor AUITextWidget::GetCaptionColor( AUIState::Index idx, bool state ) const
{
    SkColor color = SK_ColorBLACK;
    if ( state )
    {
        const auto found = m_mapTrueStateCaptionColor.find( idx );
        if ( found == m_mapTrueStateCaptionColor.end() )
            color = m_mapTrueStateCaptionColor.at( AUIState::kDefault );
        else
            color = found->second;
    }
    else
    {
        const auto found = m_mapFalseStateCaptionColor.find( idx );
        if ( found == m_mapFalseStateCaptionColor.end() )
            color = m_mapFalseStateCaptionColor.at( AUIState::kDefault );
        else
            color = found->second;
    }
    return color;

}

void AUITextWidget::InvalidateCaption()
{
    UpdateSize();
    Invalidate();
}

bool AUITextWidget::HasTrueStateColor( AUIState::Index idx ) const
{
    return m_mapTrueStateCaptionColor.find( idx ) != m_mapTrueStateCaptionColor.end();

}

bool AUITextWidget::HasFalseStateColor( AUIState::Index idx ) const
{
    return m_mapFalseStateCaptionColor.find( idx ) != m_mapFalseStateCaptionColor.end();

}

void AUITextWidget::SetMinLines( int line )
{
    m_iMinLines = line;
    InvalidateCaption();
}

void AUITextWidget::SetMaxLines( int line )
{
    m_iMaxLines = line;
    InvalidateCaption();
}

void AUITextWidget::SetLines( int line )
{
    m_iLines = line;
    InvalidateCaption();
}

void AUITextWidget::MeasureCaption(AUIScalar2& out, SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    const auto minimumSize = GetMinimumSize();
    const auto maximumSize = GetMaximumSize();

    SkPaint paint;
    GetCaptionPaint(paint);
    const auto caption = GetCaption();
    const auto spWidth = GetSizePolicyWidth();
    const auto spHeight = GetSizePolicyHeight();

    const auto defaultSize = GetDefaultSize();


    if (spWidth == AUISizePolicy::kParent)
        out.fX = width;
    if (spHeight == AUISizePolicy::kParent)
        out.fY = height;


    if (IsUseMultiline())
    {
        const auto multilineType = GetMultilineType();
        const auto newlineCaptions = AUIStringUtil::SplitByNewline(caption);

        SkScalar possibleWidth = 0.0f;
        if (spWidth == AUISizePolicy::kFixed)
            possibleWidth = (std::min)(defaultSize.fX, maximumSize.fX);
        else if (spWidth == AUISizePolicy::kParent)
            possibleWidth = width;
        else if (spWidth == AUISizePolicy::kContent)
            possibleWidth = (std::min)(width, maximumSize.fX);
        else
            possibleWidth = width;

        if (AUITextLineFeed::kNewline == multilineType)
        {
            m_MeasuredCaption = newlineCaptions;
        }
        else if (AUITextLineFeed::kNewlineCharBreak == multilineType)
        {
            m_MeasuredCaption.clear();
            if (0 < m_MeasuredCaption.size())
            {
                size_t idx = 0;
                auto tmpCaption = newlineCaptions[0];
                while (idx < newlineCaptions.size())
                {
                    const auto possibleCharCount = paint.breakText(tmpCaption.c_str(), tmpCaption.length() * sizeof(std::wstring::value_type), possibleWidth) / sizeof(std::wstring::value_type);
                    if (tmpCaption.length() > possibleCharCount)
                    {
                        m_MeasuredCaption.emplace_back(tmpCaption.substr(0, possibleCharCount));
                        tmpCaption = tmpCaption.substr(possibleCharCount);
                    }
                    else
                    {
                        m_MeasuredCaption.emplace_back(tmpCaption);
                        idx++;
                        if (idx < newlineCaptions.size())
                            tmpCaption = newlineCaptions[idx];
                    }
                }

            }
        }
        else if (AUITextLineFeed::kNewlineWordBreak == multilineType)
        {
            m_MeasuredCaption.clear();
            if (0 < newlineCaptions.size())
            {
                constexpr wchar_t WordDelim[] = L"\t \v\f,.:;\\-~!@#$%^&*_+-=/";
                size_t idx = 0;
                auto tmpCaption = newlineCaptions[0];
                while (idx < newlineCaptions.size())
                {
                    auto possibleCharCount = paint.breakText(tmpCaption.c_str(), tmpCaption.length() * sizeof(std::wstring::value_type), possibleWidth) / sizeof(std::wstring::value_type);
                    if (0 == possibleCharCount)
                        possibleCharCount = 1;  // At least one character
                    if (tmpCaption.length() > possibleCharCount)
                    {
                        const auto found = tmpCaption.find_last_of(WordDelim, possibleCharCount);
                        if (std::string::npos == found || 0 == found)
                        {
                            m_MeasuredCaption.emplace_back(tmpCaption.substr(0, possibleCharCount));
                            tmpCaption = tmpCaption.substr(possibleCharCount);
                        }
                        else
                        {
                            m_MeasuredCaption.emplace_back(tmpCaption.substr(0, found + 1));
                            tmpCaption = tmpCaption.substr(found + 1);
                        }
                    }
                    else
                    {
                        m_MeasuredCaption.emplace_back(tmpCaption);
                        idx++;
                        if (idx < newlineCaptions.size())
                            tmpCaption = newlineCaptions[idx];
                    }
                }
            }
            else
            {
                //AUIAssert(!"Unknown Multiline Option");
                m_MeasuredCaption = newlineCaptions;
            }
        }

        while (GetMinLines() > m_MeasuredCaption.size())
            m_MeasuredCaption.emplace_back(L"");
        while (GetMaxLines() < m_MeasuredCaption.size())
            m_MeasuredCaption.pop_back();

        SkRect textBound;
        AUISkiaUtil::MeasureTextBound(m_MeasuredCaption, textBound, paint);

        if (spWidth == AUISizePolicy::kContent)
        {
            out.fX = textBound.width() + ((std::max)(1.0f, GetPaddingLeft()) + (std::max)(1.0f, GetPaddingRight()));
        }
        if (spHeight == AUISizePolicy::kContent)
        {
            out.fY = textBound.height() + ((std::max)(1.0f, GetPaddingTop()) + (std::max)(1.0f, GetPaddingBottom()));
        }
    }
    else
    {
        SkPaint captionPaint;
        GetCaptionPaint(captionPaint);

        m_MeasuredCaption.resize(1);
        m_MeasuredCaption[0] = caption;
        SkRect textBound;
        AUISkiaUtil::MeasureTextBound(m_MeasuredCaption[0], textBound, false, captionPaint);

        if (spWidth == AUISizePolicy::kContent)
            out.fX = textBound.width() + ((std::max)(1.0f, GetPaddingLeft()) + (std::max)(1.0f, GetPaddingRight()));
        if (spHeight == AUISizePolicy::kContent)
            out.fY = textBound.height() + ((std::max)(1.0f, GetPaddingTop()) + (std::max)(1.0f, GetPaddingBottom()));
    }

    if (0 == caption.size())
    {
        AUIAssert(m_MeasuredCaption.size() == 1);
    }

    out = AUIScalar2::Bigger(out, minimumSize );
    out = AUIScalar2::Smaller(out, maximumSize );

    // Fit at most
    if (AUIMeasureSpec::kAtMost == widthSpec)
        out.fX = (std::min)(out.fX, width);
    if (AUIMeasureSpec::kAtMost == heightSpec)
        out.fY = (std::min)(out.fY, height);

    // To fit pixel size
    out.fX = SkScalarCeilToScalar(out.fX);
    out.fY = SkScalarCeilToScalar(out.fY);
}
