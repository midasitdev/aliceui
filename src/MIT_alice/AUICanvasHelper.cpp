#include "pch.h"
#include "AUICanvasHelper.h"
#include "MAUISkiaUtil.h"
#include "AUINinePatch.h"

namespace
{
    inline void SetupTextRenderingOption(SkCanvas* canvas, SkPaint& targetPaint )
    {
        AUIAssert(canvas);
        SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);
        if (canvas->getProps(&props))
        {
            if (SkPixelGeometry::kUnknown_SkPixelGeometry != props.pixelGeometry())
            {
                targetPaint.setLCDRenderText(true);
                //targetPaint.setAutohinted(true);
                //targetPaint.setAntiAlias(true);
                //targetPaint.setSubpixelText(true);
            }
        }
        else
        {
            targetPaint.setAntiAlias( true );
        }
        targetPaint.setTextEncoding( SkPaint::kUTF16_TextEncoding );
    }
}

AUICanvasHelper::AUICanvasHelper( SkCanvas* const pCanvas )
    : m_pCanvas( pCanvas )
{
    AUIAssert( GetCanvas() );
}

AUICanvasHelper::~AUICanvasHelper()
{

}

void AUICanvasHelper::drawText( const std::wstring& text, SkScalar x, SkScalar y, const SkPaint& paint )
{
    auto targetPaint = paint;

    SetupTextRenderingOption(GetCanvas(), targetPaint );

    AUIAssert( SkPaint::kUTF16_TextEncoding == targetPaint.getTextEncoding() );  // Use this code first : paint.setTextEncoding( SkPaint::kUTF16_TextEncoding );
    GetCanvas()->drawText( text.c_str(), text.length() * sizeof( std::wstring::value_type ), x, y, targetPaint );
}

void AUICanvasHelper::drawText(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, const SkPaint& paint )
{
    auto targetPaint = paint;

    SetupTextRenderingOption(GetCanvas(), targetPaint );

    const auto p = AUISkiaUtil::CalcTextStartPos( text, textArea, vAlign, hAlign, false, targetPaint );
    drawText( text, p.x(), p.y(), targetPaint );
}

void AUICanvasHelper::drawText(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, bool useTrailingSpace, const SkPaint& paint)
{
    auto targetPaint = paint;

    SetupTextRenderingOption(GetCanvas(), targetPaint );

    const auto p = AUISkiaUtil::CalcTextStartPos( text, textArea, vAlign, hAlign, useTrailingSpace, targetPaint );
    drawText( text, p.x(), p.y(), targetPaint );
}

void AUICanvasHelper::drawPosText( const std::wstring& text, const SkPoint pos[], const SkPaint& paint )
{
    auto targetPaint = paint;

    SetupTextRenderingOption(GetCanvas(), targetPaint );

    AUIAssert( SkPaint::kUTF16_TextEncoding == paint.getTextEncoding() );  // Use this code first : paint.setTextEncoding( SkPaint::kUTF16_TextEncoding );
    GetCanvas()->drawPosText( text.c_str(), text.length() * sizeof( std::wstring::value_type ), pos, targetPaint );
}

void AUICanvasHelper::drawPosTextH( const std::wstring& text, const SkScalar xpos[], SkScalar constY, const SkPaint& paint )
{
    auto targetPaint = paint;

    SetupTextRenderingOption(GetCanvas(), targetPaint );

    AUIAssert( SkPaint::kUTF16_TextEncoding == targetPaint.getTextEncoding() );  // Use this code first : paint.setTextEncoding( SkPaint::kUTF16_TextEncoding );
    GetCanvas()->drawPosTextH( text.c_str(), text.length() * sizeof( std::wstring::value_type ), xpos, constY, targetPaint );
}

void AUICanvasHelper::drawNinePatch( const AUINinePatch& ninepatch, const SkRect& rect, const SkPaint* paint /*= nullptr */)
{
    GetCanvas()->drawImageNine( ninepatch, ninepatch.GetCenter(), rect, paint );
}

void AUICanvasHelper::drawMultilineText( const std::vector< std::wstring >& arrTexts, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, const SkPaint& paint, const SkScalar lineHeight)
{
    auto targetPaint = paint;

    SetupTextRenderingOption(GetCanvas(), targetPaint );
    AUIAssert(SkPaint::kUTF16_TextEncoding == targetPaint.getTextEncoding());  // Use this code first : paint.setTextEncoding( SkPaint::kUTF16_TextEncoding );

    const auto arrPos = AUISkiaUtil::CalcTextStartPos(arrTexts, textArea, vAlign, hAlign, targetPaint, lineHeight);
    AUIAssert( arrPos.size() == arrTexts.size() );
    for ( auto idx = 0 ; idx < arrTexts.size() ; idx++ )
    {
        GetCanvas()->drawText( arrTexts[idx].c_str(), arrTexts[idx].length() * sizeof( std::wstring::value_type ), arrPos[idx].x(), arrPos[idx].y(), targetPaint );
    }
}

void AUICanvasHelper::drawTextOnLine(const std::wstring& text, SkScalar x0, SkScalar y0, SkScalar x1, SkScalar y1, const SkPaint& paint)
{
    auto targetPaint = paint;

    SetupTextRenderingOption(GetCanvas(), targetPaint);
    AUIAssert(SkPaint::kUTF16_TextEncoding == targetPaint.getTextEncoding());  // Use this code first : paint.setTextEncoding( SkPaint::kUTF16_TextEncoding );

    const auto _dx = x1 - x0;
    const auto _dy = y1 - y0;
    const auto _len = (std::sqrt)(_dx * _dx + _dy * _dy);
    const auto _scos = (_dx / _len);
    const auto _ssin = (_dy / _len);
    auto _tx = x0;
    auto _ty = y0;

    std::vector<SkRSXform> transforms(text.length(), { 0.0f, });

    AUIAssert(transforms.size() == text.length());
    for (size_t idx = 0; idx < text.length(); ++idx)
    {
        const auto _ch = text[idx];
        const auto _adv = targetPaint.measureText(&_ch, sizeof(std::wstring::value_type));
        transforms[idx] = SkRSXform::Make(_scos, _ssin, _tx, _ty);
        _tx += _adv * _scos;
        _ty += _adv * _ssin;
    }

    GetCanvas()->drawTextRSXform(text.c_str(), text.length() * sizeof(std::wstring::value_type), transforms.data(), nullptr, targetPaint);
}

void AUICanvasHelper::drawTextOnLine(const std::wstring& text, SkPoint p0, SkPoint p1, const SkPaint& paint)
{
    this->drawTextOnLine(text, p0.fX, p0.fY, p1.fX, p1.fY, paint);
}
