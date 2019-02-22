#pragma once

#include "AUICommonDef.h"

class AUINinePatch;


class ALICEUI_API AUICanvasHelper
{
public:
    AUICanvasHelper(SkCanvas* const pCanvas);
    virtual ~AUICanvasHelper();


    //////////////////////////////////////////////////////////////////////////
    // Canvas
protected:
    SkCanvas* const GetCanvas() const { return m_pCanvas; }
private:
    SkCanvas* const m_pCanvas;


    //////////////////////////////////////////////////////////////////////////
    // Extra text function
public:
    void drawText(const std::wstring& text, SkScalar x, SkScalar y, const SkPaint& paint);
    void drawText(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, const SkPaint& paint);
    void drawText(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, bool useTrailingSpace, const SkPaint& paint);
    void drawPosText(const std::wstring& text, const SkPoint pos[], const SkPaint& paint);
    void drawPosTextH(const std::wstring& text, const SkScalar xpos[], SkScalar constY, const SkPaint& paint);
    //void drawTextOnPath( const std::wstring& text, const SkPath& path, const SkMatrix* matrix, const SkPaint& paint );
    void drawTextOnLine(const std::wstring& text, SkScalar x0, SkScalar y0, SkScalar x1, SkScalar y1, const SkPaint& paint);
    void drawTextOnLine(const std::wstring& text, SkPoint p0, SkPoint p1, const SkPaint& paint);

    void drawMultilineText(const std::vector< std::wstring >& arrTexts, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, const SkPaint& paint, const SkScalar lineHeight);



    //////////////////////////////////////////////////////////////////////////
    // Nine Patch
public:
    void drawNinePatch(const AUINinePatch& ninepatch, const SkRect& rect, const SkPaint* paint = nullptr);

};
