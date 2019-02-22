#include "pch.h"
#include "AUIExpandHeaderWidget.h"
#include "AUIExpandHeaderSpinWidget.h"
#include "AUIExpandHeaderTextWidget.h"
#include "AUIColor.h"
#include "AUIColorDrawable.h"
#include "AUIShapeDrawable.h"
#include "AUIRectShape.h"
#include "AUIStateDrawable.h"

namespace
{
    std::shared_ptr< AUIDrawable > GetDefaultHeaderDrawable()
    {
        auto pDefaultBG = std::make_shared< AUIShapeDrawable >(std::make_shared< AUIRectShape >());
        pDefaultBG->SetColor(SkColorSetARGB(64, 253, 253, 253));
        auto pHoverBG = std::make_shared< AUIShapeDrawable >(std::make_shared< AUIRectShape >());
        pHoverBG->SetColor(SkColorSetARGB(64, 130, 186, 255));
        auto pPressBG = std::make_shared< AUIShapeDrawable >(std::make_shared< AUIRectShape >());
        pPressBG->SetColor(SkColorSetARGB(64, 130, 186, 255));
        auto pDisableBG = std::make_shared< AUIShapeDrawable >(std::make_shared< AUIRectShape >());
        pDisableBG->SetColor(SkColorSetARGB(64, 204, 204, 204));
        auto pCheckBG = std::make_shared< AUIShapeDrawable >(std::make_shared< AUIRectShape >());
        pCheckBG->SetColor(SkColorSetARGB(64, 161, 174, 194));

        auto pStateDrawable = std::make_shared< AUIStateDrawable >();
        pStateDrawable->SetTrueStateDrawable(AUIState::kDefault, pDefaultBG);
        pStateDrawable->SetTrueStateDrawable(AUIState::kMouseHovered, pHoverBG);
        pStateDrawable->SetTrueStateDrawable(AUIState::kPressed, pPressBG);
        pStateDrawable->SetTrueStateDrawable(AUIState::kDisabled, pDisableBG);
        pStateDrawable->SetTrueStateDrawable(AUIState::kChecked, pCheckBG);

        return pStateDrawable;
    }
}

AUIExpandHeaderWidget::AUIExpandHeaderWidget()
    : m_pSpin(std::make_shared<AUIExpandHeaderSpinWidget>())
    , m_pText(std::make_shared<AUIExpandHeaderTextWidget>())
{
    m_pSpin->SetClickable(true);
    m_pText->SetClickable(true);
    SetClickable(true);
    SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kFixed);
    SetDefaultHeight(20.0f);

    m_pSpin->SetPropParentLeft(true);
    m_pText->SetPropToRightOf(m_pSpin->GetRuntimeID());

    AddChild(m_pSpin);
    AddChild(m_pText);

    Connect(m_pSpin->ClickSignal, [&](AUIWidget*) {
        this->ClickSignal.Send(this);
    });
    Connect(m_pText->ClickSignal, [&](AUIWidget*) {
        this->ClickSignal.Send(this);
    });
    Connect(m_pSpin->MouseRBtnClickSignal, [&](AUIWidget*) {
        this->MouseRBtnClickSignal.Send(this);
    });
    Connect(m_pText->MouseRBtnClickSignal, [&](AUIWidget*) {
        this->MouseRBtnClickSignal.Send(this);
    });


    SetBackgroundDrawable(::GetDefaultHeaderDrawable());
    // TEST
    //SetBackgroundDrawable(std::make_shared<MAUIColorDrawable>(MAUIColor::GetRandomColor(0.1f)));
}

AUIExpandHeaderWidget::~AUIExpandHeaderWidget()
{

}

void AUIExpandHeaderWidget::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    SuperWidget::OnMeasureSize(width, widthSpec, height, heightSpec);
}

void AUIExpandHeaderWidget::OnUpdateChildPosition()
{
    SuperWidget::OnUpdateChildPosition();
}

void AUIExpandHeaderWidget::SetExpandState(bool expanded)
{
    m_pSpin->SetChecked(expanded);
}

void AUIExpandHeaderWidget::SetText(const std::wstring& text)
{
    m_pText->SetCaption(text);
    m_pText->UpdateSize();
    m_pText->Invalidate();
}

void AUIExpandHeaderWidget::SetSpinStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
    m_pSpin->SetStyleSheet(style);
}

void AUIExpandHeaderWidget::SetTextStyleSheet(std::shared_ptr<const AUIWidgetStyle> style)
{
    m_pText->SetStyleSheet(style);
}

void AUIExpandHeaderWidget::SetSpinMarginLTRB(const SkScalar left, const SkScalar top, const SkScalar right, const SkScalar bottom)
{
    m_pSpin->SetMarginLTRB(left, top, right, bottom);
}

void AUIExpandHeaderWidget::SetSpinDrawable(const std::shared_ptr<AUIDrawable>& pDrawable)
{
    m_pSpin->SetBackgroundDrawable(pDrawable);
}

void AUIExpandHeaderWidget::SetSpinSize(const SkScalar width, const SkScalar height)
{
    m_pSpin->SetDefaultSize(width, height);
    m_pSpin->UpdateSize();
}

void AUIExpandHeaderWidget::SetTextWidgetSize(const SkScalar width, const SkScalar height)
{
    m_pText->SetDefaultSize(width, height);
}

void AUIExpandHeaderWidget::SetTextMarginLTRB(const SkScalar left, const SkScalar top, const SkScalar right, const SkScalar bottom)
{
    m_pText->SetMarginLTRB(left, top, right, bottom);
}

void AUIExpandHeaderWidget::SetTextFontSize(const SkScalar size)
{
    m_pText->SetCaptionSize(size);
}

void AUIExpandHeaderWidget::SetContentState(bool hovered)
{
    m_pSpin->SetHovered(hovered);
    m_pText->SetHovered(hovered);
    m_pSpin->Invalidate();
    m_pText->Invalidate();
}

void AUIExpandHeaderWidget::SetTextFontColor(const SkColor color)
{
    m_pText->SetCaptionColor(color);
}

void AUIExpandHeaderWidget::SetTextFontColor(AUIState::Index idx, bool state, const SkColor color)
{
	m_pText->SetCaptionColor(idx, state, color);
}

void AUIExpandHeaderWidget::OnMouseEnter()
{
    SuperWidget::OnMouseEnter();

    Invalidate();
}

void AUIExpandHeaderWidget::OnMouseLeave()
{
    SuperWidget::OnMouseLeave();

    SetContentState(false);

    Invalidate();
}

void AUIExpandHeaderWidget::OnMouseHover()
{
    SuperWidget::OnMouseHover();

    SetContentState(true);

    Invalidate();
}
