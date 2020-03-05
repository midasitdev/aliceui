#pragma once

#include "AUICommonDef.h"
#include "AUIForm.h"
#include "AUISignal.h"
#include "AUISlotPool.h"

class AUIDrawable;
class AUIWindowWidget;
class AUIWidget;

class ALICEUI_API AUIWindow : public std::enable_shared_from_this<AUIWindow>
{
public:
    AUIWindow();
    AUIWindow(const std::shared_ptr<AUIWindowWidget>& pWindowWidget);
    virtual ~AUIWindow();


    //////////////////////////////////////////////////////////////////////////
    // Content Widget
public:
    void SetContent(const std::shared_ptr<AUIWidget>& pWidget);
private:
    std::shared_ptr<AUIWidget> m_pContent;


    //////////////////////////////////////////////////////////////////////////
    // Title Bar
public:
    void SetIgnoreSysButton(bool ignore);
    void SetIgnoreTitleBar(bool ignore);

    //////////////////////////////////////////////////////////////////////////
    // Window Title
public:
    void SetTitle(const std::wstring& title);
    void SetTitleColor(SkColor titleColor);
    void SetTitleStyle(SkFontStyle titleStyle);
    void SetTitleFontName(std::wstring fontName);

    std::wstring GetTitle() const;


    //////////////////////////////////////////////////////////////////////////
    // Show
public:
    bool IsActivated() const;
    void Activate();
    void Activate(const std::shared_ptr< AUIWindow >& pParent);
    void ActivateWithHandle(AUIHandle* const pHandle);
    void ActivateModal();
    void ActivateModal(const std::shared_ptr< AUIWindow >& pParent);
    void Deactivate();


    //////////////////////////////////////////////////////////////////////////
    // Size / Position
public:
    void SetSize(int width, int height);
    void SetPosition(int x, int y);
    void SetPositionAndSize(int x, int y, int width, int height);
    void GetSize(int& width, int& height);
    void GetPosition(int& x, int& y);
    void SetMinSize(int width, int height);
    void SetMaxSize(int width, int height);
    void SetResizeable(bool val);
    bool IsResizeable() const;


    //////////////////////////////////////////////////////////////////////////
    // Form
private:
    AUIForm m_Form;


    //////////////////////////////////////////////////////////////////////////
    // System button action
public:
    AUISignal<void(AUIWindow*)> ClickCloseSignal;
    AUISignal<void(AUIWindow*)> ClickMinimizeSignal;
private:
    void OnClickMinimize(AUIWidget*);
    void OnClickClose(AUIWidget*);


    //////////////////////////////////////////////////////////////////////////
    // Title Dragging
private:
    void OnDragStart(AUIWidget*);
    void OnDragEnd(AUIWidget*);
    void OnDragging(AUIWidget*);
    int m_iPrevMouseX;
    int m_iPrevMouseY;

    //////////////////////////////////////////////////////////////////////////
    // Window Widget
public:
    // NOTE : milestone 
    void SetTitleBarDrawable(const std::shared_ptr< AUIDrawable >& pDrawable);
    void SetBackgroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable);
private:
    AUISlotPool m_spoolWindow;
    std::shared_ptr< AUIWindowWidget > m_pWindow;


    //////////////////////////////////////////////////////////////////////////
    // Transparency
public:
    void SetTransparent(bool val);
    bool IsTransparent() const;
};
