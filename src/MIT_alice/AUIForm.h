#pragma once

#include "AUICommonDef.h"
#include "AUIWnd.h"

class AUIHandle;
class AUIWidget;

class ALICEUI_API AUIForm
{
public:
    AUIForm();
    AUIForm(AUIForm&& form);
    virtual ~AUIForm();
private:
    AUIForm(const AUIForm&) = delete;


    //////////////////////////////////////////////////////////////////////////
    // Option
public:
    bool IsNonActivate() const;
    void SetNonActivate(bool val);
    bool IsTopMost() const;
    void SetTopMost(bool val);


    //////////////////////////////////////////////////////////////////////////
    // Widget
public:
    void SetRootWidget(const std::shared_ptr< AUIWidget >& pWidget);


    //////////////////////////////////////////////////////////////////////////
    // Title
public:
    void SetTitle(const std::wstring& title);
    std::wstring GetTitle() const;


    //////////////////////////////////////////////////////////////////////////
    // Set Handle Mode
public:
    void SetMode(AUIHandleMode mode);


    //////////////////////////////////////////////////////////////////////////
    // Visible
public:
    void SetVisible(bool state);
    void SetFocus();
    void Invalidate();
    void UpdateWindow();

    //////////////////////////////////////////////////////////////////////////
    // Activate / Deactivate
public:
    void Activate();
    void Activate(AUIForm* const pParent);
    void Activate(AUIHandle* const pHandle);
    void Deactivate();
    bool IsActivated() const;
    void ActivateModal();
    void ActivateModal(AUIForm* const pParent);
    void ActivateModal(AUIHandle* const pHandle);
protected:
    virtual void OnActivate();
    virtual void OnDeactivate();


    //////////////////////////////////////////////////////////////////////////
    // Mouse Event Capture
public:
    void CaptureMouseEvent();
    void ReleaseMouseEvent();


    //////////////////////////////////////////////////////////////////////////
    // Size / Position
public:
    bool IsResizeable() const;
    void SetResizeable(bool val);
    void SetSize(int width, int height);
    void SetPosition(int x, int y);
    void SetPositionAndSize(int x, int y, int width, int height);
    void SetMinSize(int width, int height);
    void SetMaxSize(int width, int height);
    void GetSize(int& width, int& height);
    void GetPosition(int& x, int& y);
    void DoShowMinimized();
    void DoShowMaximized();
    void DoShowDefault();



    //////////////////////////////////////////////////////////////////////////
    // Handle
protected:
    AUIHandle* const GetHandle() const { return m_pHandle.get(); }
private:
    std::shared_ptr< AUIHandle > m_pHandle;


    //////////////////////////////////////////////////////////////////////////
    // Transparency
public:
    void SetSubWindowType(const SUB_WINDOW_TYPE& type);
    SUB_WINDOW_TYPE GetSubWindowType() const;
    void SetTransparent(bool val);
    bool IsTransparent() const;
};
