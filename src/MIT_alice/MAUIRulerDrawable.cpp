#include "pch.h"
#include "MAUIRulerDrawable.h"

using namespace mit::alice;

std::wstring ToFormattedStr(double val)
{
    std::array<wchar_t, 512> buffer{ L'\0', };
    swprintf(buffer.data(), 512, L"%.2f", val);
    return { buffer.data() };
}

MAUIRulerDrawable::MAUIRulerDrawable()
    : m_Location( AUIRulerLocation::kTop )
    , m_RefPos( 0.0f )
    , m_Basis( 5.0f )
    , m_GradationSize( 5.0f )
    , m_MaxTextWidth(50.0f) // 30.0f-->50.0f
    , m_MaxTextHeight( 15.0f )
{
    m_LinePaint.setColor( 0xFFA8A7A7 );
    m_TextPaint.setColor(kAUIColorBlack );
    m_TextPaint.setAntiAlias( true );
}

MAUIRulerDrawable::~MAUIRulerDrawable()
{

}

void MAUIRulerDrawable::OnDraw( SkCanvas* const canvas )
{
    switch ( GetLocation() )
    {
    case AUIRulerLocation::kLeft:
        OnDrawLeft( canvas );
        break;
    case AUIRulerLocation::kTop:
        OnDrawTop( canvas );
        break;
    case AUIRulerLocation::kRight:
        OnDrawRight( canvas );
        break;
    case AUIRulerLocation::kBottom:
        OnDrawBottom( canvas );
        break;
    default:
        AUIAssertFail();
        break;
    }
}

void MAUIRulerDrawable::OnDrawLeft(SkCanvas* const canvas)
{
    const auto rect = GetDrawBound();
    const auto padding = GetDrawPadding();
    const auto linePaint = RefLinePaint();
    const auto textPaint = RefTextPaint();
    const auto maxTextLength = GetMaxTextWidth();
    const auto textSize = GetMaxTextHeight();
    const auto refPos = GetRefPos();
    const auto scale = GetScale();
    const auto grad = GetGradationSize();
    const auto basis = GetBasis();

    const auto basisLineLeft = maxTextLength + rect.left() + padding.left();
    const auto textLineLeft = rect.left() + padding.left();
    const auto basisLineRight = rect.right() - padding.right();
    const auto scaleLineLeft = maxTextLength + rect.left() + padding.left();
    const auto scaleLineRight = scaleLineLeft + (basisLineRight - basisLineLeft) * SkScalar(0.5f);

    //AUIAssert( scale >= 1.0 );
    //AUIAssert( basis >= 1.0 );

    AUICanvasHelper canvasHelper(canvas);

    // Top of basis (+ Center)
    const auto startTopOfBasisY = rect.top() + padding.top();
    const auto endTopOfBasisY = refPos;
    const auto lenTopOfBasisY = endTopOfBasisY - startTopOfBasisY;
    const auto offsetTopOfBasisY = SkScalarCeilToInt(lenTopOfBasisY / (grad * scale));
    for (auto idx = 0; idx < offsetTopOfBasisY; idx++)
    {
        const auto posY = refPos - grad * scale * idx;
        if (rect.top() + padding.top() > posY || rect.bottom() - padding.bottom() < posY)
            continue;


        if (idx % SkScalarCeilToInt(basis) == 0)
        {
            auto textValueInInteger = idx * grad;
            auto textValue = ToFormattedStr(textValueInInteger);
            std::wstring unitBy1000 = L"k";

            if (textValueInInteger >= 1000)
            {
                textValueInInteger /= 1000;
                textValue = ToFormattedStr(textValueInInteger).append(unitBy1000);
            }
            const auto textRect = SkRect::MakeLTRB(textLineLeft, SkScalarCeilToScalar(posY - textSize * 0.5f) + 1.0f, basisLineLeft, SkScalarFloorToScalar(posY + textSize * 0.5f));
            canvasHelper.drawText(textValue, textRect, AUITextVertAlign::kCenter, AUITextHorzAlign::kCenter, textPaint);

            if (IsUseMarking())//눈금 사이의 더 작은 눈금(현재 안쓰임)
                canvas->drawLine(basisLineLeft, posY, basisLineRight, posY, linePaint);


        }
        else
        {
            if (IsUseMarking())
                canvas->drawLine(scaleLineLeft, posY, scaleLineRight, posY, linePaint);
        }
    }

    // Bottom of basis
    const auto startBottomOfBasisY = refPos;
    const auto endBottomOfBasisY = rect.bottom() - padding.bottom();
    const auto lenBottomOfBasisY = endBottomOfBasisY - startBottomOfBasisY;
    const auto offsetBottomOfBasisY = SkScalarCeilToInt(lenBottomOfBasisY / (grad * scale));
    for (auto idx = 1; idx < offsetBottomOfBasisY; idx++)
    {
        const auto posY = refPos + grad * scale * idx;
        if (rect.top() + padding.top() > posY || rect.bottom() - padding.bottom() < posY)
            continue;

        if (idx % SkScalarCeilToInt(basis) == 0)
        {
            auto textValueInInteger = -idx * grad;
            auto textValue = ToFormattedStr(textValueInInteger);
            std::wstring unitBy1000 = L"k";


            if (textValueInInteger <= -1000)
            {
                textValueInInteger /= 1000;
                textValue = ToFormattedStr(textValueInInteger).append(unitBy1000);
            }

            const auto textRect = SkRect::MakeLTRB(textLineLeft, SkScalarCeilToScalar(posY - textSize * 0.5f) + 1.0f, basisLineLeft, SkScalarFloorToScalar(posY + textSize * 0.5f));
            canvasHelper.drawText(textValue, textRect, AUITextVertAlign::kCenter, AUITextHorzAlign::kCenter, textPaint);

            if (IsUseMarking())
                canvas->drawLine(basisLineLeft, posY, basisLineRight, posY, linePaint);

        }
        else
        {
            if (IsUseMarking())
                canvas->drawLine(scaleLineLeft, posY, scaleLineRight, posY, linePaint);
        }
    }
}

void MAUIRulerDrawable::OnDrawTop(SkCanvas* const canvas)
{
    const auto rect = GetDrawBound();
    const auto padding = GetDrawPadding();
    const auto linePaint = RefLinePaint();
    const auto textPaint = RefTextPaint();
    const auto maxTextLength = GetMaxTextWidth();
    const auto textSize = GetMaxTextHeight();
    const auto refPos = GetRefPos();
    const auto scale = GetScale();
    const auto grad = GetGradationSize();
    const auto basis = GetBasis();
    const auto textbasis = basis > 4 ? basis : basis * 2;

    const auto basisLineTop = rect.top() + padding.top() + textSize;
    const auto TextLineTop = rect.top() + padding.top();
    const auto basisLineBottom = rect.bottom() - padding.bottom();
    const auto scaleLineTop = rect.top() + padding.top() + textSize;
    const auto scaleLineBottom = scaleLineTop + (basisLineBottom - basisLineTop) * SkScalar(0.5f);

    //AUIAssert( grad >= 1.0 );
    //AUIAssert( basis >= 1.0 );

    AUICanvasHelper canvasHelper(canvas);

    // Left of basis (+ Center)
    const auto startLeftOfBasisX = rect.left() + padding.left();
    const auto endLeftOfBasisX = refPos;
    const auto lenLeftOfBasisX = endLeftOfBasisX - startLeftOfBasisX;
    const auto offsetLeftOfBasisX = SkScalarCeilToInt(lenLeftOfBasisX / (grad * scale));
    for (auto idx = 0; idx < offsetLeftOfBasisX; idx++)
    {
        const auto posX = refPos - grad * scale * idx;
        if (rect.left() + padding.left() > posX || rect.right() - padding.right() < posX)
            continue;

        if (idx % SkScalarCeilToInt(basis) == 0)
        {

            if (IsUseMarking())
                canvas->drawLine(posX, basisLineTop, posX, basisLineBottom, linePaint);
        }
        else
        {

            if (IsUseMarking())
                canvas->drawLine(posX, scaleLineTop, posX, scaleLineBottom, linePaint);
        }

        if (idx % SkScalarCeilToInt(textbasis) == 0)
        {
            auto textValueInInteger = -idx * grad;
            auto textValue = ToFormattedStr(textValueInInteger);
            std::wstring unitBy1000 = L"k";

            if (textValueInInteger <= -1000)
            {
                textValueInInteger /= 1000;
                textValue = ToFormattedStr(textValueInInteger).append(unitBy1000);
            }

            const auto textRect = SkRect::MakeLTRB(SkScalarCeilToScalar(posX - maxTextLength * 0.5f) + 1.0f, TextLineTop, SkScalarFloorToScalar(posX + maxTextLength * 0.5f), basisLineTop);
            canvasHelper.drawText(textValue, textRect, AUITextVertAlign::kCenter, AUITextHorzAlign::kCenter, textPaint);



        }
    }

    // Right of basis
    const auto startRightOfBasisX = refPos;
    const auto endRightOfBasisX = rect.right() - padding.right();
    const auto lenRightOfBasisX = endRightOfBasisX - startRightOfBasisX;
    const auto offsetRightOfBasisX = lenRightOfBasisX / (grad * scale);
    for (auto idx = 1; idx < offsetRightOfBasisX; idx++)
    {
        const auto posX = refPos + grad * scale * idx;
        if (rect.left() + padding.left() > posX || rect.right() - padding.right() < posX)
            continue;

        if (idx % SkScalarCeilToInt(basis) == 0)
        {

            if (IsUseMarking())
                canvas->drawLine(posX, basisLineTop, posX, basisLineBottom, linePaint);
        }
        else
        {
            if (IsUseMarking())
                canvas->drawLine(posX, scaleLineTop, posX, scaleLineBottom, linePaint);
        }
        if (idx % SkScalarCeilToInt(textbasis) == 0)
        {
            auto textValueInInteger = idx * grad;
            auto textValue = ToFormattedStr(textValueInInteger);
            std::wstring unitBy1000 = L"k";

            if (textValueInInteger >= 1000)
            {
                textValueInInteger /= 1000;
                textValue = ToFormattedStr(textValueInInteger).append(unitBy1000);
            }
            const auto textRect = SkRect::MakeLTRB(SkScalarCeilToScalar(posX - maxTextLength * 0.5f) + 1.0f, TextLineTop, SkScalarFloorToScalar(posX + maxTextLength * 0.5f), basisLineTop);
            canvasHelper.drawText(textValue, textRect, AUITextVertAlign::kCenter, AUITextHorzAlign::kCenter, textPaint);


        }
    }
}


void MAUIRulerDrawable::OnDrawRight( SkCanvas* const canvas )
{
    const auto rect = GetDrawBound();
    const auto padding = GetDrawPadding();
    const auto linePaint = RefLinePaint();
    const auto textPaint = RefTextPaint();
    const auto maxTextLength = GetMaxTextWidth();
    const auto textSize = GetMaxTextHeight();
    const auto refPos = GetRefPos();
    const auto scale = GetGradationSize();
    const auto basis = GetBasis();

    const auto basisLineLeft = rect.left() + padding.left() + maxTextLength;
    const auto basisLineRight = rect.right() - padding.right();
    const auto scaleLineRight = rect.right() - padding.right();
    const auto scaleLineLeft = scaleLineRight - ( basisLineRight - basisLineLeft ) * SkScalar( 0.5 );

    AUIAssert( scale >= 1.0 );
    AUIAssert( basis >= 1.0 );

    AUICanvasHelper canvasHelper( canvas );

    // Top of basis (+ Center)
    const auto startTopOfBasisY = rect.top() + padding.top();
    const auto endTopOfBasisY = refPos;
    const auto lenTopOfBasisY = endTopOfBasisY - startTopOfBasisY;
    const auto offsetTopOfBasisY = SkScalarCeilToInt( lenTopOfBasisY / scale );
    for ( auto idx = 0 ; idx < offsetTopOfBasisY ; idx++ )
    {
        const auto posY = refPos - scale * idx;
        if ( rect.top() + padding.top() > posY || rect.bottom() - padding.bottom() < posY )
            continue;

        if ( idx % SkScalarCeilToInt( basis ) == 0 )
        {

            if (IsUseMarking())
                canvas->drawLine( basisLineLeft, posY, basisLineRight, posY, linePaint );
            const auto textRect = SkRect::MakeLTRB( rect.left() + padding.left(), SkScalarCeilToScalar( posY - textSize * 0.5f ) + 1.0f, basisLineLeft, SkScalarFloorToScalar( posY + textSize * 0.5f ) );
            canvasHelper.drawText( std::to_wstring( idx ), textRect, AUITextVertAlign::kCenter, AUITextHorzAlign::kCenter, textPaint );
        }
        else
        {
            canvas->drawLine( scaleLineLeft, posY, scaleLineRight, posY, linePaint );
        }
    }

    // Bottom of basis
    const auto startBottomOfBasisY = refPos;
    const auto endBottomOfBasisY = rect.bottom() - padding.bottom();
    const auto lenBottomOfBasisY = endBottomOfBasisY - startBottomOfBasisY;
    const auto offsetBottomOfBasisY = SkScalarCeilToInt( lenBottomOfBasisY / scale );
    for ( auto idx = 1 ; idx < offsetBottomOfBasisY ; idx++ )
    {
        const auto posY = refPos + scale * idx;
        if ( rect.top() + padding.top() > posY || rect.bottom() - padding.bottom() < posY )
            continue;

        if ( idx % SkScalarCeilToInt( basis ) == 0 )
        {

            if (IsUseMarking())
                canvas->drawLine( basisLineLeft, posY, basisLineRight, posY, linePaint );
            const auto textRect = SkRect::MakeLTRB( rect.left() + padding.left(), SkScalarCeilToScalar( posY - textSize * 0.5f ) + 1.0f, basisLineLeft, SkScalarFloorToScalar( posY + textSize * 0.5f ) );
            canvasHelper.drawText( std::to_wstring( -idx ), textRect, AUITextVertAlign::kCenter, AUITextHorzAlign::kCenter, textPaint );
        }
        else
        {

            if (IsUseMarking())
                canvas->drawLine( scaleLineLeft, posY, scaleLineRight, posY, linePaint );
        }
    }
}

void MAUIRulerDrawable::OnDrawBottom( SkCanvas* const canvas )
{
    const auto rect = GetDrawBound();
    const auto padding = GetDrawPadding();
    const auto linePaint = RefLinePaint();
    const auto textPaint = RefTextPaint();
    const auto maxTextLength = GetMaxTextWidth();
    const auto textSize = GetMaxTextHeight();
    const auto refPos = GetRefPos();
    const auto scale = GetGradationSize();
    const auto basis = GetBasis();

    const auto basisLineTop = rect.top() + padding.top() + textSize;
    const auto basisLineBottom = rect.bottom() - padding.bottom();
    const auto scaleLineBottom = rect.bottom() - padding.bottom();
    const auto scaleLineTop = scaleLineBottom - ( basisLineBottom - basisLineTop ) * SkScalar( 0.5 );

    AUIAssert( scale >= 1.0 );
    AUIAssert( basis >= 1.0 );

    AUICanvasHelper canvasHelper( canvas );

    // Left of basis (+ Center)
    const auto startLeftOfBasisX = rect.left() + padding.left();
    const auto endLeftOfBasisX = refPos;
    const auto lenLeftOfBasisX = endLeftOfBasisX - startLeftOfBasisX;
    const auto offsetLeftOfBasisX = SkScalarCeilToInt( lenLeftOfBasisX / scale );
    for ( auto idx = 0 ; idx < offsetLeftOfBasisX ; idx++ )
    {
        const auto posX = refPos - scale * idx;
        if ( rect.left() + padding.left() > posX || rect.right() - padding.right() < posX )
            continue;

        if ( idx % SkScalarCeilToInt( basis ) == 0 )
        {

            if (IsUseMarking())
                canvas->drawLine( posX, basisLineTop, posX, basisLineBottom, linePaint );
            const auto textRect = SkRect::MakeLTRB( SkScalarCeilToScalar( posX - maxTextLength * 0.5f ) + 1.0f, rect.top() + padding.top(), SkScalarFloorToScalar( posX + maxTextLength * 0.5f ), basisLineTop );
            canvasHelper.drawText( std::to_wstring( -idx ), textRect, AUITextVertAlign::kCenter, AUITextHorzAlign::kCenter, textPaint );
        }
        else
        {

            if (IsUseMarking())
                canvas->drawLine( posX, scaleLineTop, posX, scaleLineBottom, linePaint );
        }
    }

    // Right of basis
    const auto startRightOfBasisX = refPos;
    const auto endRightOfBasisX = rect.right() - padding.right();
    const auto lenRightOfBasisX = endRightOfBasisX - startRightOfBasisX;
    const auto offsetRightOfBasisX = lenRightOfBasisX / scale;
    for ( auto idx = 1 ; idx < offsetRightOfBasisX ; idx++ )
    {
        const auto posX = refPos + scale * idx;
        if ( rect.left() + padding.left() > posX || rect.right() - padding.right() < posX )
            continue;

        if ( idx % SkScalarCeilToInt( basis ) == 0 )
        {

            if (IsUseMarking())
                canvas->drawLine( posX, basisLineTop, posX, basisLineBottom, linePaint );
            const auto textRect = SkRect::MakeLTRB( SkScalarCeilToScalar( posX - maxTextLength * 0.5f ) + 1.0f, rect.top() + padding.top(), SkScalarFloorToScalar( posX + maxTextLength * 0.5f ), basisLineTop );
            canvasHelper.drawText( std::to_wstring( idx ), textRect, AUITextVertAlign::kCenter, AUITextHorzAlign::kCenter, textPaint );
        }
        else
        {

            if (IsUseMarking())
                canvas->drawLine( posX, scaleLineTop, posX, scaleLineBottom, linePaint );
        }
    }
}
