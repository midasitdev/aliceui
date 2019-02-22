#pragma once

#include "AUIRelativeLayoutWidget.h"

class AUIExpandHeaderSpinWidget;
class AUIExpandHeaderTextWidget;
class ALICEUI_API AUIExpandHeaderWidget : public AUIRelativeLayoutWidget
{
    using SuperWidget = AUIRelativeLayoutWidget;
public:
    AUIExpandHeaderWidget();
    virtual ~AUIExpandHeaderWidget();


    //////////////////////////////////////////////////////////////////////////
    // Mouse event
protected:
    void OnMouseEnter() override;
    void OnMouseLeave() override;
    void OnMouseHover() override;

    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;

    //////////////////////////////////////////////////////////////////////////
    // Child position
protected:
    void OnUpdateChildPosition() override;

    //////////////////////////////////////////////////////////////////////////
    // State Callback
public:
    void SetExpandState(bool expanded);

    //////////////////////////////////////////////////////////////////////////
    // Contents
public:
    void SetSpinMarginLTRB(const SkScalar left, const SkScalar top, const SkScalar right, const SkScalar bottom);
    void SetSpinSize(const SkScalar width, const SkScalar height);
    void SetSpinDrawable(const std::shared_ptr<AUIDrawable>& pDrawable);
    void SetTextMarginLTRB(const SkScalar left, const SkScalar top, const SkScalar right, const SkScalar bottom);
    void SetTextWidgetSize(const SkScalar width, const SkScalar height);
    void SetTextFontSize(const SkScalar size);
	void SetTextFontColor(const SkColor color);
	void SetTextFontColor(AUIState::Index idx, bool state, const SkColor color);
    void SetText(const std::wstring& text);
    void SetContentState(bool hovered);
private:
    std::shared_ptr<AUIExpandHeaderSpinWidget> m_pSpin;
    std::shared_ptr<AUIExpandHeaderTextWidget> m_pText;

    //////////////////////////////////////////////////////////////////////////
    // MSS Support
public:
    void SetSpinStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
    void SetTextStyleSheet(std::shared_ptr<const AUIWidgetStyle> style);
};
