#pragma once

#include "AUIAPIDef.h"
#include "AUIBasicEnumDef.h"
#include "AUISkiaConfig.h"

class ALICEUI_API AUISkiaUtil
{
public:
    //////////////////////////////////////////////////////////////////////////
    static SkMatrix ToSkMat(const glm::mat4& m);

    //////////////////////////////////////////////////////////////////////////
    // Color mix helper
    static SkColor MixColor(const SkColor& src, const SkColor& dst, SkScalar weight);

    //////////////////////////////////////////////////////////////////////////
    // Determine
    static bool IsInRect(const SkRect& rect, const SkPoint& p);
    static bool IsInRect(const SkRect& rect, SkScalar x, SkScalar y);


    //////////////////////////////////////////////////////////////////////////
    // SkColor to glm
    static glm::vec4 SkColorToVec4(const SkColor color);
    static glm::vec3 SkColor2vec3(const SkColor color);

    //////////////////////////////////////////////////////////////////////////
    // Text utility
    static SkScalar MeasureTextBound(const std::wstring& text, SkRect& bound, bool useTrailingSpace, const SkPaint& paint);
    static SkScalar MeasureTextBound(const std::wstring& text, const SkPaint& paint);
    static SkScalar MeasureTextBound(const std::wstring& text, SkRect& bound, const SkPaint& paint);
    static SkScalar MeasureTextBound(const std::wstring& text, bool useTrailingSpace, const SkPaint& paint);
    static SkScalar MeasureTextBound(const std::vector< std::wstring >& arrTexts, SkRect& bound, const SkPaint& paint);
    static SkPoint CalcTextStartPos(const SkRect& textBound, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, const SkPaint& paint);
    static SkPoint CalcTextStartPos(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, bool useTrailingSpace, const SkPaint& paint);
    static SkPoint CalcTextStartPos(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, SkRect& textBound, const SkPaint& paint);
    static SkPoint CalcTextStartPos(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, bool useTrailingSpace, SkRect& textBound, const SkPaint& paint);
    static std::vector< SkPoint > CalcTextStartPos(const std::vector< std::wstring >& arrTexts, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, const SkPaint& paint, const SkScalar lineHeight);
    static size_t BreakText(const std::wstring& text, bool useTrailingSpace, SkScalar maxWidth, SkScalar* measuredWidth, const SkPaint& paint);
    static size_t BreakText(const std::wstring& text, bool useTrailingSpace, SkScalar maxWidth, const SkPaint& paint);
};
