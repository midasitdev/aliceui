#include "pch.h"
#include "AUIEditWidget.h"
#include "AUIStringFilter.h"
#include "AUIStateDrawable.h"
#include "AUIWidgetManager.h"
#include "AUIClipboard.h"
#include "AUISmootherStepInterpolator.h"
#include "AUIJsonDrawableParser.h"
#include "AUIStringConvert.h"
#include "AUIApplication.h"


namespace {
    constexpr wchar_t DefaultCaption[] = L"";
    constexpr wchar_t DefaultCaptionHint[] = L"Insert Here";
    constexpr SkColor TrueStateCaptionColor = SkColorSetRGB( 201, 211, 219 ); // default text color

    constexpr bool DefaultTabToChar = false;
    constexpr bool DefaultReturnToChar = false;
    constexpr bool DefaultUseBuffered = true;
    constexpr bool DefaultCaptionSelectable = true;
    constexpr bool DefaultFocusable = true;

    constexpr SkColor DefaultCaptionCompColor = SkColorSetRGB( 66, 151, 255 ); // cursor color 어따 쓰는지 몰겠
    constexpr SkColor DefaultSelectBackgroundColor = SkColorSetRGB( 130, 186, 255 ); // select 시 background color
    constexpr SkColor DefaultCaptionSelectColor = SkColorSetRGB( 255, 255, 255 ); // select 시 text color
    constexpr SkColor DefaultCaptionHintColor = kAUIColorGray; // SkColorSetRGB( 201, 211, 219 ); // hint text color
    constexpr SkScalar DefaultCaptionHintSize = 13.0f;

    constexpr std::chrono::milliseconds AnimTickLength( 300 );
}

namespace {

    std::shared_ptr< AUIDrawable > GetEditDrawable()
    {
        AUIJsonDrawableParser parser;
        if (auto refDrawable = parser.LoadFromPathByResource(L"drawable/edit.json"))
            return *refDrawable;


        class UnderlineDrawable : public AUIDrawable
        {
        public:
            UnderlineDrawable() = default;
            ~UnderlineDrawable() override = default;

        public:
            void SetColor( SkColor color ) { m_Color = color; }
            SkColor GetColor() const { return m_Color; }
        private:
            SkColor m_Color = SK_ColorTRANSPARENT;

        protected:
            virtual void OnDraw( SkCanvas* const canvas )
            {
                const auto rect = GetDrawBound();

                SkPaint paint;
                //paint.setAntiAlias( true );
                paint.setColor( GetColor() );
                paint.setStrokeWidth( 1.0f );
                canvas->drawLine( rect.left(), rect.bottom() - 1.0f, rect.right(), rect.bottom() - 1.0f, paint );
            }
        };
        class EditBGDrawable : public AUIStateDrawable
        {
        public:
            EditBGDrawable()
            {
                {
                    auto pDrawable = std::make_shared< UnderlineDrawable >();
                    pDrawable->SetColor( SkColorSetRGB( 177, 177, 177 ) );
                    SetTrueStateDrawable( AUIState::kDefault, pDrawable );
                }
                {
                    auto pDrawable = std::make_shared< UnderlineDrawable >();
                    pDrawable->SetColor( SkColorSetRGB( 118, 179, 255 ) );
                    SetTrueStateDrawable( AUIState::kMouseHovered, pDrawable );
                }
                {
                    auto pDrawable = std::make_shared< UnderlineDrawable >();
                    pDrawable->SetColor( SkColorSetRGB( 118, 179, 255 ) );
                    SetTrueStateDrawable( AUIState::kPressed, pDrawable );
                }
                {
                    auto pDrawable = std::make_shared< UnderlineDrawable >();
                    pDrawable->SetColor( SkColorSetRGB( 118, 179, 255 ) );
                    SetTrueStateDrawable( AUIState::kFocused, pDrawable );
                }
            }
        protected:
        };
        return std::make_shared< EditBGDrawable >();
    }
}

// Selection
const std::wstring::size_type AUIEditWidget::SelClearStart = std::wstring::npos;
const std::wstring::size_type AUIEditWidget::SelClearEnd = 0;
const std::wstring::size_type AUIEditWidget::SelAllStart = 0;
const std::wstring::size_type AUIEditWidget::SelAllEnd = std::wstring::npos;

AUIEditWidget::AUIEditWidget()
    : AUITextWidget( DefaultCaption )
    , m_CaptionHint( DefaultCaptionHint )
    , m_bTabToChar( DefaultTabToChar )
    , m_bReturnToChar( DefaultReturnToChar )
    , m_bUseBuffer( DefaultUseBuffered )
    , m_bCaptionSelectable( DefaultCaptionSelectable )
    , m_SelStart( SelClearStart )
    , m_SelEnd( SelClearEnd )
    , m_SelCursor( std::wstring::npos )
    , m_SelectBGColor( DefaultSelectBackgroundColor )
    , m_CaptionSelectColor( DefaultCaptionSelectColor )
    , m_CaptionHintColor( DefaultCaptionHintColor )
    , m_CaptionCompColor( DefaultCaptionCompColor )
    , m_bPassword( false )
{
    SetCaptionColor( TrueStateCaptionColor );
    SetFocusable( DefaultFocusable );

    SetCaptionSize( 13.0f );
    SetCaptionHintSize( DefaultCaptionHintSize );
    SetCaptionHorzAlign( AUITextHorzAlign::kCenter );

    SetUseHotkeyCopy( true );
    SetUseHotkeyCut( true );
    SetUseHotkeyPaste( true );
	SetClickable(true);
    SetBackgroundDrawable( GetEditDrawable() );
}

AUIEditWidget::AUIEditWidget( const std::wstring& captionhint )
    : AUITextWidget( DefaultCaption )
    , m_CaptionHint( DefaultCaptionHint )
    , m_bTabToChar( DefaultTabToChar )
    , m_bReturnToChar( DefaultReturnToChar )
    , m_bUseBuffer( DefaultUseBuffered )
    , m_bCaptionSelectable( DefaultCaptionSelectable )
    , m_SelStart( SelClearStart )
    , m_SelEnd( SelClearEnd )
    , m_SelCursor( std::wstring::npos )
    , m_SelectBGColor( DefaultSelectBackgroundColor )
    , m_CaptionSelectColor( DefaultCaptionSelectColor )
    , m_CaptionHintColor( DefaultCaptionHintColor )
    , m_CaptionCompColor( DefaultCaptionCompColor )
    , m_bPassword( false )
{
    SetCaptionColor( TrueStateCaptionColor );
    SetFocusable( DefaultFocusable );

    SetCaptionSize( 13.0f );
    SetCaptionHorzAlign( AUITextHorzAlign::kCenter );

    SetUseHotkeyCopy( true );
    SetUseHotkeyCut( true );
	SetUseHotkeyPaste(true);
	SetClickable(true);

    SetBackgroundDrawable( GetEditDrawable() );
}

AUIEditWidget::~AUIEditWidget()
{
}

void AUIEditWidget::OnDestroy()
{
}

void AUIEditWidget::OnFocusIn()
{
    if ( IsUseBuffer() )
        ResetBuffer();

    StartBlink();
}

void AUIEditWidget::OnFocusOut()
{
    auto sendSignal = true;
    if ( IsUseBuffer() )
    {
        if ( GetCaptionBuffer().compare( GetCaption() ) == 0 )
            sendSignal = false;
        FlushBuffer();
    }
    if ( sendSignal )
        SignalAfterTextChanged.Send( this, GetCaption() );


    SetSelectionClear();

    StopBlink();
}

void AUIEditWidget::SetSelection( std::wstring::size_type start, std::wstring::size_type end )
{
    if ( start == std::wstring::npos && end == std::wstring::npos )
    {
        start = SelClearStart;
        end = SelClearEnd;
    }

    // Last changed as cursor position
    if ( start != end )
    {
        if ( m_SelStart == start && m_SelEnd == end )
        {
            // No change
        }
        else
        {
            if ( m_SelEnd == end )
                m_SelCursor = start;
            else
                m_SelCursor = end;
        }
    }
    else
    {
        m_SelCursor = start;
    }

    m_SelStart = start;
    m_SelEnd = end;
}

void AUIEditWidget::SetSelection( std::wstring::size_type pos )
{
    SetSelection( pos, pos );
}

void AUIEditWidget::SetSelectionAll()
{
    m_SelStart = SelAllStart;
    m_SelEnd = SelAllEnd;
    m_SelCursor = std::wstring::npos;
}

void AUIEditWidget::SetSelectionClear()
{
    m_SelStart = SelClearStart;
    m_SelEnd = SelClearEnd;
    m_SelCursor = std::wstring::npos;
}

void AUIEditWidget::GetSelection( std::wstring::size_type& start, std::wstring::size_type& end ) const
{
    start = m_SelStart;
    end = m_SelEnd;
}

void AUIEditWidget::SetStringFilter( AUIStringFilter* pFilter )
{
     m_pFilter = std::unique_ptr< AUIStringFilter >( pFilter );
}

void AUIEditWidget::SetStringFilter( std::unique_ptr< AUIStringFilter >& pFilter )
{
     m_pFilter = std::move( pFilter );
}

void AUIEditWidget::FlushBuffer()
{
    SetCaption( GetCaptionBuffer() );
}

void AUIEditWidget::ResetBuffer()
{
    SetCaptionBuffer( GetCaption() );
}

bool AUIEditWidget::IsSelectionAll() const
{
    return ( m_SelStart == SelAllStart ) && ( m_SelEnd == SelAllEnd );
}

bool AUIEditWidget::IsSelectionClear() const
{
    return ( m_SelStart == SelClearStart ) && ( m_SelEnd == SelClearEnd );
}

bool AUIEditWidget::IsSelectionCursor() const
{
    return ( m_SelStart == m_SelEnd ) && ( m_SelStart != std::wstring::npos );
}

std::wstring AUIEditWidget::OnSetCaption( const std::wstring& text )
{
    if ( IsUseBuffer() )
        SetCaptionBuffer( text );
    return text;
}

std::wstring AUIEditWidget::OnGetCaption( const std::wstring& text ) const
{
    return text;
}

std::wstring AUIEditWidget::GetSelectedCaption() const
{
    std::wstring::size_type selStart;
    std::wstring::size_type selEnd;
    GetSelection( selStart, selEnd );


    const auto caption = GetTargetCaption();
    auto strSelected = caption;
    if ( selStart == AUIEditWidget::SelAllStart && selEnd == AUIEditWidget::SelAllEnd )
    {
        //strSelected = caption;
    }
    else if ( selStart == AUIEditWidget::SelClearStart && selEnd == AUIEditWidget::SelClearEnd )
    {
        strSelected = std::wstring();
    }
    else
    {
        // Check range
        const auto len = caption.size();
        selStart = std::clamp( selStart, std::wstring::size_type( 0 ), std::wstring::size_type( len ) );
        selEnd = std::clamp( selEnd, std::wstring::size_type( 0 ), std::wstring::size_type( len ) );

        if ( selStart != selEnd )
        {
            const auto selLen = selEnd - selStart;
            strSelected = caption.substr( selStart, selLen );
        }
    }

    return strSelected;
}

std::wstring AUIEditWidget::GetTargetCaption() const
{
    std::wstring text;
    if ( IsUseBuffer() && IsFocused() )
        text = GetCaptionBuffer();
    else
        text = GetCaption();

    if ( IsPassword() )
    {
        std::transform( text.begin(), text.end(), text.begin(), []( wchar_t )->wchar_t {
            return L'*';
        } );
    }

    return text;
}

void AUIEditWidget::SetTargetCaption( const std::wstring& text )
{
    auto caption = text;
    if ( auto pFilter = GetStringFilter() )
        caption = pFilter->Filter( caption );

    if ( IsUseBuffer() && IsFocused() )
        SetCaptionBuffer( caption );
    else
        SetCaption( caption );
}

void AUIEditWidget::OnDrawCaption( SkCanvas* const canvas )
{
    if ( IsUseMultiline() )
    {
        OnDrawEditCaption_Multiline( canvas );
    }
    else
    {
        OnDrawEditCaption_Single( canvas );
    }
}

void AUIEditWidget::OnDrawEditCaption_Single( SkCanvas* const canvas )
{
    const auto rect = GetRect();

    const auto compChar = m_CaptionComp;
    const auto hasCompChar = !compChar.empty();

    const auto captionArea = GetCaptionAreaRect();

    float compAdvance = 0.0f;

    auto useHintCaption = false;
    auto captionPaint = GetCaptionPaint();
    auto targetCaption = GetTargetCaption();
    SkRect strTargetBound;

    AUICanvasHelper mcanvas( canvas );

    auto strTargetPos = AUISkiaUtil::CalcTextStartPos( targetCaption, captionArea, GetCaptionVertAlign(), GetCaptionHorzAlign(), true, strTargetBound, captionPaint );
    if ( targetCaption.empty() )
    {
        useHintCaption = true;
        targetCaption = GetCaptionHint();
        AUISkiaUtil::MeasureTextBound( targetCaption, strTargetBound, true, captionPaint );

        if ( hasCompChar )
        {
            captionPaint.setTextSize( GetCaptionSize() );
            captionPaint.setColor( GetCaptionCompColor() );

            SkRect compBound;
            AUISkiaUtil::MeasureTextBound( compChar, compBound, true, captionPaint );
            compAdvance = compBound.right();

            mcanvas.drawText( compChar, captionArea, GetCaptionVertAlign(), GetCaptionHorzAlign(), true, captionPaint );
        }
        else
        {
            mcanvas.drawText( targetCaption, captionArea, GetCaptionVertAlign(), GetCaptionHorzAlign(), true, captionPaint );
        }
    }
    else
    {
        std::wstring preCaption;
        std::wstring selCaption;
        std::wstring postCaption;
        if ( IsSelectionClear() )
        {
            preCaption = targetCaption;
        }
        else if ( IsSelectionAll() )
        {
            selCaption = targetCaption;
        }
        else
        {
            // Selection
            auto selStart = AUIEditWidget::SelClearStart;
            auto selEnd = AUIEditWidget::SelClearEnd;
            GetSelection( selStart, selEnd );
            selStart = ( std::min )( selStart, targetCaption.size() );
            selEnd = ( std::min )( selEnd, targetCaption.size() );

            preCaption.assign( targetCaption.begin(), targetCaption.begin() + selStart );
            selCaption.assign( targetCaption.begin() + selStart, targetCaption.begin() + selEnd );
            postCaption.assign( targetCaption.begin() + selEnd, targetCaption.end() );
        }

        auto captionSelPaint = captionPaint;
        captionSelPaint.setColor( GetCaptionSelectColor() );

        SkRect preBound;
        SkRect selBound;
        SkRect postBound;
        const auto preAdvance = AUISkiaUtil::MeasureTextBound( preCaption, preBound, true, captionPaint );
        const auto selAdvance = AUISkiaUtil::MeasureTextBound( selCaption, selBound, true, captionSelPaint );
        const auto postAdvance = AUISkiaUtil::MeasureTextBound( postCaption, postBound, true, captionPaint );

        SkPaint selBGPaint;
        selBGPaint.setAntiAlias( true );
        selBGPaint.setColor( GetSelectBGColor() );
        selBGPaint.setStyle( SkPaint::kFill_Style );

        SkPaint::FontMetrics metric;
        captionSelPaint.getFontMetrics( &metric );

        if ( selCaption.empty() == false )
        {
            auto selBGRect = SkRect::MakeLTRB( strTargetPos.x() + preBound.left() + preBound.width(), strTargetPos.y() + metric.fTop, strTargetPos.x() + preBound.left() + preBound.width() + selBound.left() + selBound.width(), strTargetPos.y() + metric.fBottom );
            canvas->drawRect( selBGRect, selBGPaint );
        }

        // Pre
        const float preStartPosX = strTargetPos.x();
        const float preStartPosY = strTargetPos.y();
        if ( preCaption.empty() == false )
            mcanvas.drawText( preCaption, preStartPosX, preStartPosY, captionPaint );

        // Sel
        const float selStartPosX = preStartPosX + preAdvance;// preBound.right();
        const float selStartPosY = preStartPosY;
        if ( selCaption.empty() == false )
            mcanvas.drawText( selCaption, selStartPosX, selStartPosY, captionSelPaint );

        // Comp
        const float compStartPosX = selStartPosX + selAdvance;// selBound.right();
        const float compStartPosY = preStartPosY;
        if ( compChar.empty() == false )
        {
            auto captionCompPaint = captionPaint;
            captionCompPaint.setTextSize( GetCaptionSize() );
            captionCompPaint.setColor( GetCaptionCompColor() );

            SkRect compBound;
            compAdvance = AUISkiaUtil::MeasureTextBound( compChar, compBound, true, captionCompPaint );
            //compAdvance = compBound.right();

            mcanvas.drawText( compChar, compStartPosX, preStartPosY, captionCompPaint );
        }


        // Post
        const float postStartPosX = compStartPosX + compAdvance;
        const float postStartPosY = compStartPosY;
        if ( postCaption.empty() == false )
            mcanvas.drawText( postCaption, postStartPosX, postStartPosY, captionPaint );
    }

    if ( IsAnimRunning() && IsFocused() && false == IsDisabled() )
    {
        static auto pInterpolator = std::make_shared< AUISmootherStepInterpolator >();
        float weight = pInterpolator->GetValueByTime( GetAnimStartTick(), GetAnimStartTick() + AnimTickLength, GetTimeTick() );

        if ( weight >= 1.0f )
        {
            m_bBlinkState = !m_bBlinkState;
            StartAnimRunning(); // Restart
        }

        if ( m_bBlinkState )
        {
            SkRect strCompBound;
            auto strCompPos = AUISkiaUtil::CalcTextStartPos( compChar, captionArea, GetCaptionVertAlign(), GetCaptionHorzAlign(), true, strCompBound, captionPaint );

            SkPaint::FontMetrics metric;
            captionPaint.getFontMetrics( &metric );

            float x0 = 0.0f;
            float y0 = 0.0f;
            float x1 = 0.0f;
            float y1 = 0.0f;

            if ( useHintCaption )
            {
                if ( hasCompChar )
                {
                    x0 = strCompPos.x() + strCompBound.left() + strCompBound.width();
                    y0 = strCompPos.y() + metric.fTop;
                    x1 = x0;
                    y1 = strCompPos.y() + metric.fBottom;
                }
                else
                {
                    x0 = strTargetPos.x();
                    y0 = strTargetPos.y() + metric.fTop;
                    x1 = x0;
                    y1 = strTargetPos.y() + metric.fBottom;
                }
            }
            else
            {
                x0 = GetAdvanceOfStringPos( GetSelectionCursor() ) + compAdvance;//strTargetPos.x() + strTargetBound.left() + strTargetBound.width() + strCompBound.left() + strCompBound.width();
                y0 = strTargetPos.y() + metric.fTop;
                x1 = x0;
                y1 = strTargetPos.y() + metric.fBottom;
            }
            x0 = SkScalarRoundToScalar( x0 );
            y0 = SkScalarRoundToScalar( y0 );
            x1 = SkScalarRoundToScalar( x1 );
            y1 = SkScalarRoundToScalar( y1 );
            SkPaint indicatorPaint;
            indicatorPaint.setColor( captionPaint.getColor() );
            canvas->drawLine( x0, y0, x1, y1, indicatorPaint );
        }

        Invalidate();
    }

}

void AUIEditWidget::OnDrawEditCaption_Multiline( SkCanvas* const canvas )
{
    AUIAssertFailReason("TODO");
    OnDrawEditCaption_Single( canvas );
}

void AUIEditWidget::OnMouseHover()
{
    SuperWidget::OnMouseHover();
    Invalidate();
}

void AUIEditWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();
    Invalidate();
}

bool AUIEditWidget::OnMouseLBtnDown( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnDown( flag );
	if (false == IsClickable())
		return false;

    const auto startPos = GetStringPos( GetMouseLocPosX(), GetMouseLocPosY() );
    m_cursorSelStart = startPos;

    SetSelection( m_cursorSelStart, m_cursorSelStart );

    return true;

}

bool AUIEditWidget::OnMouseLBtnUp( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnUp( flag );
	if (false == IsClickable())
		return false;

    const auto endPos = GetStringPos( GetMouseLocPosX(), GetMouseLocPosY() );

    return true;
}

bool AUIEditWidget::OnMouseLBtnDblClk( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseLBtnDblClk( flag );
	if (false == IsClickable())
		return false;

    m_cursorSelStart = std::wstring::npos;

    if ( IsSelectionAll() )
    {
        SetSelectionClear();
    }
    else if ( IsSelectionClear() )
    {
        SetSelectionAll();
    }
    else
    {
        // TODO : word selection
        SetSelectionAll();
    }

    return true;

}

bool AUIEditWidget::OnMouseMove( MAUIMouseEvent::EventFlag flag )
{
    SuperWidget::OnMouseMove( flag );

    if ( IsMouseLDown() )
    {
        if ( m_cursorSelStart != std::wstring::npos )
        {
            const auto startPos = GetStringPos( GetMouseLocPosX(), GetMouseLocPosY() );

            if ( m_cursorSelStart < startPos )
                SetSelection( m_cursorSelStart, startPos );
            else
                SetSelection( startPos, m_cursorSelStart );
        }
    }

    return true;

}

bool AUIEditWidget::OnChangeCursorIcon( AUICursorIcon& cursoricon )
{
    if ( IsDisabled() )
        return false;
	if (false == IsClickable())
		return false;
    cursoricon.SetCursorIcon( AUICursorIcon::kIBeam_CursorIcon );
    return true;
}

bool AUIEditWidget::OnKeyDown( AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode )
{
    SuperWidget::OnKeyDown( mask, keycode, repcount, charcode );

	if (IsEditable() == false)
		return false;

    if ( keycode == MAUIKeycode::kArrowLeft )
    {
        std::wstring::size_type selStart;
        std::wstring::size_type selEnd;
        GetSelection( selStart, selEnd );

        if ( mask & AUIKeyboardEvent::kShiftOn_MaskCode )
        {
            const auto selCursor = GetSelectionCursor();
            if ( selCursor == selStart )
            {
                if ( selStart > 0 )
                    selStart--;
            }
            else
            {
                if ( selEnd > 0 )
                    selEnd--;
            }
        }
        else if ( mask == AUIKeyboardEvent::kNone_MaskCode )
        {
            if ( selStart > 0 )
                selStart--;

            selEnd = selStart;
        }


        if ( selStart > selEnd )
        {
            std::swap( selStart, selEnd );
        }
        AUIAssert( selStart <= selEnd );

        SetSelection( selStart, selEnd );
    }
    else if ( keycode == MAUIKeycode::kArrowRight )
    {
        std::wstring caption;
        if ( IsUseBuffer() )
            caption = GetCaptionBuffer();
        else
            caption = GetCaption();
        const auto captionsize = caption.size();
        std::wstring::size_type selStart;
        std::wstring::size_type selEnd;
        GetSelection( selStart, selEnd );

        if ( mask & AUIKeyboardEvent::kShiftOn_MaskCode )
        {
            const auto selCursor = GetSelectionCursor();
            if ( selCursor == selStart )
            {
                if ( selStart < captionsize )
                    selStart++;
            }
            else
            {
                if ( selEnd < captionsize )
                    selEnd++;
            }
        }
        else if ( mask == AUIKeyboardEvent::kNone_MaskCode )
        {
            if ( selEnd < captionsize )
                selEnd++;

            selStart = selEnd;
        }

        if ( selStart > selEnd )
        {
            std::swap( selStart, selEnd );
        }
        AUIAssert( selStart <= selEnd );

        SetSelection( selStart, selEnd );
    }
    else if ( keycode == MAUIKeycode::kDelete )
    {
       OpDelete();
    }
    else if ( charcode == MAUIKeycode::kEscape )
    {
        // ESC
        if ( IsUseBuffer() )
            ResetBuffer();

        GetWidgetManager()->SetFocusTarget();
    }
    else if ( charcode == MAUIKeycode::kKey_A )
    {
        if ( mask & AUIKeyboardEvent::kCtrlOn_MaskCode )
        {
            SetSelectionAll();
        }
    }
    else if ( charcode == MAUIKeycode::kEnter && IsReturnToChar() == false )
    {
        // Return

        if ( IsUseBuffer() )
            FlushBuffer();

        // After text change
        SignalAfterTextChanged.Send( this, GetCaption() );

        GetWidgetManager()->SetFocusTarget();

        SignalReturn.Send( this );
    }

    return false;

}

bool AUIEditWidget::OnKeyUp( AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode )
{
    SuperWidget::OnKeyUp( mask, keycode, repcount, charcode );

    if ( IsEditable() == false )
        return false;

	if (charcode == '\t' && IsTabToChar() == false)
	{
		if (IsUseBuffer())
			FlushBuffer();

		// After text change
		SignalAfterTextChanged.Send(this, GetCaption());

		SignalTab.Send(this);

		Invalidate();
		return true;
	}

    return false;
}

bool AUIEditWidget::OnChar( AUIKeyboardEvent::MaskCode mask, unsigned int charcode, unsigned int repcount, unsigned int flag )
{
    if ( IsEditable() == false )
        return false;

    bool ret = false;
    if ( mask == AUIKeyboardEvent::kNone_MaskCode || mask & AUIKeyboardEvent::kShiftOn_MaskCode )
    {
        if ( charcode != 0 )
        {
            if ( charcode == 0x08 )
            {
                // Backspace
                OpBackspace();
            }
            else if ( charcode == '\t' && IsTabToChar() == false )
            {
                if ( IsUseBuffer() )
                    FlushBuffer();

                // After text change
                SignalAfterTextChanged.Send( this, GetCaption() );

                // Tab
                GetWidgetManager()->SetFocusTarget( GetNextFocusable() );
            }
            else if ( charcode == 0x0D && IsReturnToChar() == false )
            {
                // Return

                if ( IsUseBuffer() )
                    FlushBuffer();

                // After text change
                SignalAfterTextChanged.Send( this, GetCaption() );

                GetWidgetManager()->SetFocusTarget();

                SignalReturn.Send( this );
            }
            else
            {
                OpAddCharCode( (wchar_t)charcode );
            }
            ret = true;
        }
    }
    else
    {
        if ( mask & AUIKeyboardEvent::kCtrlOn_MaskCode )
        {
            if ( charcode == 0x7F )
            {
                // Ctrl + Backspace (charcode is Delete)
                OpDeleteWord();
            }
        }
    }

    Invalidate();

    return ret;

}

bool AUIEditWidget::OnKeyIMEComp( unsigned int charcode, int64_t param )
{
    if ( !IsEditable() )
        return false;

    bool ret = false;
    if ( param == AUIKeyboardEvent::kResult_IMEParam )
    {
        OpAddCharCode( (wchar_t)charcode );
        Invalidate();
        ret = true;
    }
    else if ( param == AUIKeyboardEvent::kComp_IMEParam )
    {
        OpComposing( (wchar_t)charcode );
        Invalidate();
        ret = true;
    }

    return ret;

}

bool AUIEditWidget::OnCopy()
{
    const auto strSelected = GetSelectedCaption();

    AUIClipboard::Instance().SetText( strSelected );

    return true;
}

bool AUIEditWidget::OnPaste()
{
    OpReplaceSelection( AUIClipboard::Instance().GetText() );
    return true;
}

bool AUIEditWidget::OnCut()
{
    const auto strSelected = GetSelectedCaption();
    AUIClipboard::Instance().SetText( strSelected );
    OpRemoveSelection();

    return true;
}

void AUIEditWidget::StartBlink()
{
    StartAnimRunning();
    m_bBlinkState = false;
    Invalidate();
}

void AUIEditWidget::StopBlink()
{
    StopAnimRunning();
    m_bBlinkState = false;
    Invalidate();
}

void AUIEditWidget::OpDeleteWord()
{
    if ( IsSelectionCursor() )
    {
        if ( m_CaptionComp.size() > 0 )
        {
            OpBackspace();
            return;
        }

        const auto caption = GetTargetCaption();

        std::wstring::size_type start;
        std::wstring::size_type end;
        GetSelection( start, end );
        AUIAssert( start == end );


        const auto precaption = caption.substr( 0, start );
        const auto postcaption = caption.substr( start );

        const auto found = precaption.rfind( L" " );
        if ( found == std::wstring::npos )
        {
            SetTargetCaption( postcaption );
            SetSelection( 0, 0 );
        }
        else
        {
            AUIAssert( 0 < precaption.size() );
            // Remove if space
            std::wstring::size_type offset = 1;
            if ( precaption[precaption.size() - 1] == L' ' )
                offset = 0;

            const auto newprecaption = precaption.substr( 0, found + offset );
            const auto newcaption = newprecaption + postcaption;
            const auto newselpos = newprecaption.size();
            SetTargetCaption( newcaption );
            SetSelection( newselpos, newselpos );
        }
    }
    else if ( IsSelectionClear() == false )
    {
        OpRemoveSelection();
    }
    else
    {
        if ( m_CaptionComp.size() > 0 )
        {
            OpBackspace();
            return;
        }

        const auto caption = GetTargetCaption();

        const auto found = caption.rfind( L" " );
        if ( found == std::wstring::npos )
        {
            SetTargetCaption( L"" );
        }
        else
        {
            SetTargetCaption( caption.substr( 0, found ) );
        }
    }
}

void AUIEditWidget::OpBackspace()
{
    OpRemoveSelection();
    m_CaptionComp.clear();

}

void AUIEditWidget::OpDelete()
{
    OpRemoveSelection( true );
    m_CaptionComp.clear();

}

void AUIEditWidget::OpAddCharCode( wchar_t charcode )
{
    if ( IsSelectionClear() == false && IsSelectionCursor() == false )
    {
        OpRemoveSelection();
    }

    auto caption = GetTargetCaption();
    bool wasClear = false;
    if ( charcode != 0x1b ) // Not ESC
    {
        std::wstring::size_type selStart;
        std::wstring::size_type selEnd;
        GetSelection( selStart, selEnd );

        if ( IsSelectionClear() )
        {
            caption.push_back( charcode );

            const auto selPos = std::wstring::size_type( 1 );
            SetSelection( selPos, selPos );
            wasClear = true;
        }
        else
        {
            AUIAssert( selStart == selEnd );
            selStart = ( std::min )( caption.size(), selStart );
            caption.insert( selStart, std::wstring( 1, charcode ) );

            const auto selPos = selStart + 1;
            SetSelection( selPos, selPos );
        }
    }
    else
    {
        charcode = L'\0';
    }

    SetTargetCaption( caption );

    const auto captionFiltered = GetTargetCaption();

    if ( caption != captionFiltered && wasClear == false )
    {
        std::wstring::size_type newselpos = captionFiltered.size();

        auto itrCaption = caption.rbegin();
        auto itrCaptionFiltered = captionFiltered.rbegin();
        while ( itrCaptionFiltered != captionFiltered.rend() )
        {
            if ( itrCaption == caption.rend() )
                break;

            if ( ( *itrCaption ) != ( *itrCaptionFiltered ) )
            {
                break;
            }

            itrCaption++;
            itrCaptionFiltered++;
            newselpos--;
        }
        SetSelection( newselpos, newselpos );
    }


    m_CaptionComp.clear();

    SignalCharChanged.Send( this, GetCaption(), charcode );

}

void AUIEditWidget::OpComposing( wchar_t charcode )
{
    if ( IsSelectionClear() == false && IsSelectionCursor() == false )
        OpRemoveSelection();

    m_CaptionComp.clear();
    if ( charcode != 0x1b ) // ESC
        m_CaptionComp.push_back( charcode );
}

void AUIEditWidget::OpRemoveSelection( bool reverse /*= false */ )
{

    std::wstring::size_type selStart = 0;
    std::wstring::size_type selEnd = 0;
    GetSelection( selStart, selEnd );

    auto caption = GetTargetCaption();

    if ( selStart == selEnd )
    {
        if (std::wstring::npos == selStart)
        {
            AUIAssertFail();
            SetSelectionClear();
        }
        else
        {
            AUIAssert(selStart != std::wstring::npos);
            std::wstring::size_type selPos = selStart;
            if (selPos > 0)
            {
                if (reverse == false)
                {
                    selPos--;
                    caption.erase(selPos, 1);
                    SetSelection(selPos, selPos);
                }
                else
                {
                    if (selPos < caption.size())
                    {
                        caption.erase(selPos, 1);
                        SetSelection(selPos, selPos);
                    }
                    //SetSelection(selPos, selPos);
                }
            }
            else
            {
                // 0 == selPos
                if (reverse)
                {
                    if (0 < caption.size())
                    {
                        caption.erase(0, 1);
                        SetSelection(0, 0);
                    }
                }
            }
        }
    }
    else
    {
        selStart = ( std::min )( selStart, caption.size() );
        selEnd = ( std::min )( selEnd, caption.size() );

        const auto eraselen = selEnd - selStart;
        caption.erase( selStart, eraselen );
        SetSelection( selStart, selStart );
    }

    SetTargetCaption( caption );
}

void AUIEditWidget::OpReplaceSelection( const std::wstring& text )
{

    OpRemoveSelection();

    auto caption = GetTargetCaption();

    std::wstring::size_type selStart = 0;
    std::wstring::size_type selEnd = 0;
    GetSelection( selStart, selEnd );

    if ( selStart == selEnd )
    {
        if (std::wstring::npos == selStart)
        {
            AUIAssertFail();
            SetSelectionClear();
        }
        else
        {
            AUIAssert(selStart != std::wstring::npos);
            std::wstring::size_type selPos = selStart;
            caption.insert(selPos, text);
            SetSelection(selStart + text.size(), selStart + text.size());
        }
    }
    else
    {
        AUIAssert( false );
    }
    SetTargetCaption( caption );
}

std::wstring::size_type AUIEditWidget::GetStringPos( float x, float y )
{
    auto captionPaint = GetCaptionPaint();
    auto targetCaption = GetTargetCaption();
    const auto captionArea = GetCaptionAreaRect();

    if ( targetCaption.empty() )
        return std::wstring::npos;

    SkRect captionBound;
    AUISkiaUtil::MeasureTextBound( targetCaption, captionBound, true, captionPaint );
    const auto textStartPos = AUISkiaUtil::CalcTextStartPos( targetCaption, captionArea, GetCaptionVertAlign(), GetCaptionHorzAlign(), true, captionPaint );

    const auto diffX = x - textStartPos.x();
    const auto diffY = y - textStartPos.y();

    const auto p = AUISkiaUtil::BreakText( targetCaption, true, diffX, captionPaint );
    return p;


}

float AUIEditWidget::GetAdvanceOfStringPos( std::wstring::size_type pos )
{
    auto captionPaint = GetCaptionPaint();
    auto targetCaption = GetTargetCaption();
    const auto captionArea = GetCaptionAreaRect();

    if ( targetCaption.empty() )
        return captionArea.centerX();

    SkRect captionBound;
    AUISkiaUtil::MeasureTextBound( targetCaption, captionBound, true, captionPaint );
    const auto textStartPos = AUISkiaUtil::CalcTextStartPos( targetCaption, captionArea, GetCaptionVertAlign(), GetCaptionHorzAlign(), true, captionPaint );


    auto targetSubCaption = targetCaption.substr( 0, pos );
    const auto subadvance = AUISkiaUtil::MeasureTextBound( targetSubCaption, true, captionPaint );

    return textStartPos.x() + subadvance;
}

SkPaint AUIEditWidget::GetCaptionPaint()
{
    auto targetCaptionColor = GetCaptionColor();
    auto targetCaptionSize = GetCaptionSize();

    const auto caption = GetTargetCaption();

    if ( caption.empty() )
    {
        targetCaptionColor = GetCaptionHintColor();
        targetCaptionSize = GetCaptionHintSize();
    }

    SkPaint captionPaint;
    captionPaint.setAntiAlias( GetCaptionAntialias() );
    captionPaint.setColor( targetCaptionColor );
    captionPaint.setStyle( SkPaint::kFill_Style );
    captionPaint.setTextSize( targetCaptionSize );
    captionPaint.setTextEncoding( SkPaint::kUTF16_TextEncoding );

	if (IsDisabled())
		captionPaint.setColor(GetCaptionColor(AUIState::kDisabled, true));

    // Setup font
    if (GetCaptionFontName().empty() == false )
    {
        const auto fontName = AUIStringConvert::WCSToUTF8(GetCaptionFontName().c_str());
        captionPaint.setTypeface( SkTypeface::MakeFromName(fontName.c_str(), GetCaptionStyle()));
    }


    return captionPaint;

}
