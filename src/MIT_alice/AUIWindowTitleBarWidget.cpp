#include "pch.h"
#include "AUIWindowTitleBarWidget.h"
#include "AUIGalleria.h"
#include "AUIJsonDrawableParser.h"
#include "AUIImageDrawable.h"
#include "AUIImageButtonWidget.h"
#include "AUITextWidget.h"
#include "AUIWidgetManager.h"
#include "AUIHandle.h"
#include "AUITitleBarDefaultValue.h"

namespace {
    constexpr SkScalar DefaultTitleBarHeight = 29.0f;
}

class MaximizeButtonWidget : public AUIImageButtonWidget
{
public:
    MaximizeButtonWidget()
    {
        SetDefaultSize(TitleBar::SysButton::kBGWidth, TitleBar::SysButton::kBGHeight);
        SetSizePolicy(TitleBar::SysButton::kWidthPolicy, TitleBar::SysButton::kHeightPolicy);

        OnPostMeasureSize();

        //background
        AUIJsonDrawableParser parser;
        if (auto refDrawable = parser.LoadFromPathByResource(TitleBar::SysButton::kBackground))
            SetBackgroundDrawable(*refDrawable);
        // Default
        SetRestoreIcon();
    }

    virtual void OnPostMeasureSize() override
    {
        auto pWidgetManager = GetWidgetManager();
        if (nullptr == pWidgetManager)
            return;
        auto pHandle = pWidgetManager->GetHandle();
        if (nullptr == pHandle)
            return;
        if (pHandle->IsZoomed())
            SetRestoreIcon();
        else
            SetMaximizeIcon();
    }

private:
    void SetMaximizeIcon()
    {
        AUIGalleria galleria;
        auto pDefaultIcon = galleria.GetFromResource(TitleBar::SysButton::kMaximizeIcon);
        auto pDefaultDrawable = std::make_shared< AUIImageDrawable >();
        pDefaultDrawable->SetImage(pDefaultIcon);
        pDefaultDrawable->SetImageStretch(AUIImageStretch::kOriginal);
        SetImageDrawable(pDefaultDrawable);
    }

    void SetRestoreIcon()
    {
        AUIGalleria galleria;

        auto pDefaultIcon = galleria.GetFromResource(TitleBar::SysButton::kRestoreIcon);
        auto pDefaultDrawable = std::make_shared< AUIImageDrawable >();
        pDefaultDrawable->SetImage(pDefaultIcon);
        pDefaultDrawable->SetImageStretch(AUIImageStretch::kOriginal);
        SetImageDrawable(pDefaultDrawable);
    }
};

class CloseButtonWidget : public AUIImageButtonWidget
{
public:
    CloseButtonWidget()
    {
        SetDefaultSize(TitleBar::SysButton::kBGWidth, TitleBar::SysButton::kBGHeight);
        SetSizePolicy(TitleBar::SysButton::kWidthPolicy, TitleBar::SysButton::kHeightPolicy);

        //background
        AUIJsonDrawableParser parser;
        if (auto refDrawable = parser.LoadFromPathByResource(TitleBar::SysButton::kBackground))
            SetBackgroundDrawable(*refDrawable);

        AUIGalleria galleria;

        auto pDefaultIcon = galleria.GetFromResource(TitleBar::SysButton::kCloseIcon);
        auto pDefaultDrawable = std::make_shared< AUIImageDrawable >();
        pDefaultDrawable->SetImage(pDefaultIcon);
        pDefaultDrawable->SetImageStretch(AUIImageStretch::kOriginal);
        SetImageDrawable(pDefaultDrawable);
    }
};
class HideButtonWidget : public AUIImageButtonWidget
{
public:
    HideButtonWidget()
    {
        SetDefaultSize(TitleBar::SysButton::kBGWidth, TitleBar::SysButton::kBGHeight);
        SetSizePolicy(TitleBar::SysButton::kWidthPolicy, TitleBar::SysButton::kHeightPolicy);

        AUIGalleria galleria;

        auto pDefaultIcon = galleria.GetFromResource(TitleBar::SysButton::kMinimizeIcon);
        auto pDefaultDrawable = std::make_shared< AUIImageDrawable >();
        pDefaultDrawable->SetImage(pDefaultIcon);
        pDefaultDrawable->SetImageStretch(AUIImageStretch::kOriginal);
        SetImageDrawable(pDefaultDrawable);

        //background
        AUIJsonDrawableParser parser;
        if (auto refDrawable = parser.LoadFromPathByResource(TitleBar::SysButton::kBackground))
            SetBackgroundDrawable(*refDrawable);
    }
};

class TitleTextWidget : public AUITextWidget
{
public:
    TitleTextWidget() : AUITextWidget(L"Title")
    {
        SetDefaultSize(TitleBar::SysButton::kBGWidth, TitleBar::SysButton::kBGHeight);
        SetSizePolicy(AUISizePolicy::kContent, AUISizePolicy::kParent);
    }
};

class MainIconWidget : public AUIImageWidget
{
public:
    MainIconWidget()
    {
        SetDefaultSize(TitleBar::SysButton::kBGWidth, TitleBar::SysButton::kBGHeight);
        SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);
    }
};

AUIWindowTitleBarWidget::AUIWindowTitleBarWidget()
    : m_pIcon(std::make_shared<MainIconWidget>())
    , m_pTitleText(std::make_shared<TitleTextWidget>())
    , m_pMinimizeButton(std::make_shared< HideButtonWidget >())
    , m_pMaximizeButton(std::make_shared< MaximizeButtonWidget>())
    , m_pCloseButton(std::make_shared< CloseButtonWidget >())
    , m_fAbsPrevX(-1.0f)
    , m_fAbsPrevY(-1.0f)
{
    SetDraggable(true);
    SetClickable(true);
    SetDefaultHeight(DefaultTitleBarHeight);
    SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kFixed);


    m_pIcon->SetPropParentLeft(true);
    m_pTitleText->SetPropParentCenter(true);
    m_pTitleText->Freeze();

    // NOTE: 일부 sysbtn만 제거하려는 경우가 안되서 우선 이걸로
    m_pCloseButton->SetPropParentRight(true);
    m_pCloseButton->SetMarginRight(TitleBar::SysButton::kMarginRightMost);
    m_pMaximizeButton->SetPropParentRight(true);
    m_pMaximizeButton->SetMarginRight(TitleBar::SysButton::kBGWidth + TitleBar::SysButton::kMarginRight + TitleBar::SysButton::kMarginRightMost);
    m_pMinimizeButton->SetPropParentRight(true);
    m_pMinimizeButton->SetMarginRight(2.0f * (TitleBar::SysButton::kBGWidth + TitleBar::SysButton::kMarginRight) + TitleBar::SysButton::kMarginRightMost);
    //m_pMaximizeButton->SetPropToLeftOf(m_pCloseButton->GetRuntimeID());
    //m_pMinimizeButton->SetPropToLeftOf(m_pMaximizeButton->GetRuntimeID());

    AddSubWidget(m_pIcon);
    AddSubWidget(m_pTitleText);

    // Order is important
    AddSubWidget(m_pCloseButton);
    AddSubWidget(m_pMaximizeButton);
    AddSubWidget(m_pMinimizeButton);
}

AUIWindowTitleBarWidget::~AUIWindowTitleBarWidget()
{

}

bool AUIWindowTitleBarWidget::OnMouseLBtnDown(MAUIMouseEvent::EventFlag flag)
{
    SuperWidget::OnMouseLBtnDown(flag);

    //m_fAbsPrevX = GetMouseAbsPosX();
    //m_fAbsPrevY = GetMouseAbsPosY();

    DragPressSignal.Send(this);

    return true;
}

bool AUIWindowTitleBarWidget::OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag)
{
    SuperWidget::OnMouseLBtnUp(flag);

    DragReleaseSignal.Send(this);

    return true;
}

bool AUIWindowTitleBarWidget::OnDragging()
{
    SuperWidget::OnDragging();

    //const auto curAbsX = GetMouseAbsPosX();
    //const auto curAbsY = GetMouseAbsPosY();

    //if (m_fAbsPrevX < 0.0f)
    //    m_fAbsPrevX = curAbsX;
    //if (m_fAbsPrevY < 0.0f)
    //    m_fAbsPrevY = curAbsY;
    //const auto diffX = curAbsX - m_fAbsPrevX;
    //const auto diffY = curAbsY - m_fAbsPrevY;

    //m_fAbsPrevX = curAbsX;
    //m_fAbsPrevY = curAbsY;

    //DragMoveSignal.Send(this, diffX, diffY);
    DragMoveSignal.Send(this);

    return true;
}
