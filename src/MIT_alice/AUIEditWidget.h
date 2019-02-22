#pragma once

#include "AUITextWidget.h"


class AUIStringFilter;
class ALICEUI_API AUIEditWidget : public AUITextWidget
{
    typedef AUITextWidget SuperWidget;
public:
    AUIEditWidget();
    explicit AUIEditWidget(const std::wstring& captionhint);
    virtual ~AUIEditWidget();


    //////////////////////////////////////////////////////////////////////////
    // Signal
public:
    AUISignal<void(AUIWidget*, const std::wstring&, wchar_t)> SignalCharChanged;
    AUISignal<void(AUIWidget*, const std::wstring&)> SignalAfterTextChanged;
    AUISignal<void(AUIWidget*)> SignalReturn;
    AUISignal<void(AUIWidget*)> SignalTab;

	//////////////////////////////////////////////////////////////////////////
	// Create & Destroy
public:
	virtual void OnDestroy() override;

    //////////////////////////////////////////////////////////////////////////
    // Focus control
protected:
    virtual void OnFocusIn() override;
    virtual void OnFocusOut() override;


    //////////////////////////////////////////////////////////////////////////
    // Text Buffer
public:
    void FlushBuffer();
    void ResetBuffer();
    void SetCaptionBuffer(const std::wstring& text) { m_CaptionBuffer = text; }
    std::wstring GetCaptionBuffer() const { return m_CaptionBuffer; }
    std::wstring GetTargetCaption() const;
    void SetTargetCaption(const std::wstring& text);
private:
    std::wstring m_CaptionBuffer;


    //////////////////////////////////////////////////////////////////////////
    // Caption
protected:
    virtual std::wstring OnSetCaption(const std::wstring& text) override;
    virtual std::wstring OnGetCaption(const std::wstring& text) const override;

    //////////////////////////////////////////////////////////////////////////
    // Special options
public:
    bool IsTabToChar() const { return m_bTabToChar; }
    void SetTabToChar(bool state) { m_bTabToChar = state; }
    bool IsReturnToChar() const { return m_bReturnToChar; }
    void SetReturnToChar(bool state) { m_bReturnToChar = state; }
    bool IsUseBuffer() const { return m_bUseBuffer; }
    void SetUseBuffer(bool state) { m_bUseBuffer = state; }
    bool IsPassword() const { return m_bPassword; }
    void SetPassword(bool state) { m_bPassword = state; }
private:
    bool m_bTabToChar;
    bool m_bReturnToChar;
    bool m_bUseBuffer;
    bool m_bPassword;


    //////////////////////////////////////////////////////////////////////////
    // String Filter
public:
    void SetStringFilter(AUIStringFilter* pFilter);
    void SetStringFilter(std::unique_ptr< AUIStringFilter >& pFilter);
    AUIStringFilter* const GetStringFilter() const { return m_pFilter.get(); }
private:
    std::unique_ptr< AUIStringFilter > m_pFilter;


    //////////////////////////////////////////////////////////////////////////
    // Caption hint
public:
    void SetCaptionHint(const std::wstring& caption) { m_CaptionHint = caption; }
    std::wstring GetCaptionHint() const { return m_CaptionHint; }
private:
    std::wstring m_CaptionHint;


    //////////////////////////////////////////////////////////////////////////
    // Selection
public:
    std::wstring GetSelectedCaption() const;
    void SetCaptionSelectable(bool val) { m_bCaptionSelectable = val; }
    bool IsCaptionSelectable() const { return m_bCaptionSelectable; }
    bool IsSelectionAll() const;
    bool IsSelectionClear() const;
    bool IsSelectionCursor() const;
    void SetSelection(std::wstring::size_type start, std::wstring::size_type end);
    void SetSelection(std::wstring::size_type pos);
    void SetSelectionAll();
    void SetSelectionClear();
    void GetSelection(std::wstring::size_type& start, std::wstring::size_type& end) const;
    std::wstring::size_type GetSelectionStart() const { return m_SelStart; }
    std::wstring::size_type GetSelectionEnd() const { return m_SelEnd; }
    std::wstring::size_type GetSelectionCursor() const { return m_SelCursor; }
    static const std::wstring::size_type SelAllStart;
    static const std::wstring::size_type SelAllEnd;
    static const std::wstring::size_type SelClearStart;
    static const std::wstring::size_type SelClearEnd;
private:
    bool m_bCaptionSelectable;
    std::wstring::size_type m_SelStart;
    std::wstring::size_type m_SelEnd;
    std::wstring::size_type m_SelCursor;



    //////////////////////////////////////////////////////////////////////////
    // Editable
public:
    void SetEditable(bool val) { SetDisabled(!val); }
    bool IsEditable() const { return IsDisabled() == false; }






    //////////////////////////////////////////////////////////////////////////
    // Sub drawings - Implement this
protected:
    virtual void OnDrawCaption(SkCanvas* const canvas) override;
    void OnDrawEditCaption_Single(SkCanvas* const canvas);
    void OnDrawEditCaption_Multiline(SkCanvas* const canvas);


    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual void OnMouseHover() override;
    virtual void OnMouseLeave() override;
    virtual bool OnMouseLBtnDown(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnDblClk(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMove(MAUIMouseEvent::EventFlag flag) override;

    //////////////////////////////////////////////////////////////////////////
    // Cursor Icon
public:
    virtual bool OnChangeCursorIcon(AUICursorIcon& cursoricon) override;

    //////////////////////////////////////////////////////////////////////////
    // Keyboard event
protected:
    virtual bool OnKeyDown(AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode) override;
    virtual bool OnKeyUp(AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode) override;
    virtual bool OnChar(AUIKeyboardEvent::MaskCode mask, unsigned int charcode, unsigned int repcount, unsigned int flag) override;
    virtual bool OnKeyIMEComp(unsigned int charcode, int64_t param) override;
    virtual bool OnCopy() override;
    virtual bool OnPaste() override;
    virtual bool OnCut() override;



    //////////////////////////////////////////////////////////////////////////
    // Blink animation
public:
    void StartBlink();
    void StopBlink();
private:
    bool m_bBlinkState = false;


    //////////////////////////////////////////////////////////////////////////
    // Cursor
public:
private:
    std::wstring::size_type m_cursorSelStart;

    //////////////////////////////////////////////////////////////////////////
    // Text operation
private:
    void OpDeleteWord();
    void OpBackspace();
    void OpDelete();
    void OpAddCharCode(wchar_t charcode);
    void OpComposing(wchar_t charcode);
    void OpRemoveSelection(bool reverse = false);
    void OpReplaceSelection(const std::wstring& text);
    std::wstring::size_type GetStringPos(float x, float y);
    float GetAdvanceOfStringPos(std::wstring::size_type pos);
    SkPaint GetCaptionPaint();


    //////////////////////////////////////////////////////////////////////////
    // Caption composition
public:
    void SetCaptionCompColor(const SkColor color) { m_CaptionCompColor = color; Invalidate(); }
    SkColor GetCaptionCompColor() const { return m_CaptionCompColor; }
private:
    SkColor m_CaptionCompColor;
    std::wstring m_CaptionComp;


    //////////////////////////////////////////////////////////////////////////
    // Caption
public:
    void SetCaptionSelectColor(const SkColor color) { m_CaptionSelectColor = color; Invalidate(); }
    void SetSelectBGColor(const SkColor color) { m_SelectBGColor = color; Invalidate(); }
    SkColor GetCaptionSelectColor() const { return m_CaptionSelectColor; }
    SkColor GetSelectBGColor() const { return m_SelectBGColor; }
private:
    SkColor m_SelectBGColor;
    SkColor m_CaptionSelectColor;


    //////////////////////////////////////////////////////////////////////////
    // Caption Hint
public:
    void SetCaptionHintColor(const SkColor color) { m_CaptionHintColor = color; Invalidate(); }
    void SetCaptionHintSize(float size) { m_fCaptionHintSize = size; Invalidate(); }
    SkColor GetCaptionHintColor() const { return m_CaptionHintColor; }
    float GetCaptionHintSize() const { return m_fCaptionHintSize; }
private:
    SkColor m_CaptionHintColor;
    float m_fCaptionHintSize;


};

