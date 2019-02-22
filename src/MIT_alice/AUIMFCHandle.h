#pragma once

#include "AUIHandle.h"

class CWnd;

class ALICEUI_API AUIMFCHandle : public AUIHandle
{
    using SuperClass = AUIHandle;
public:
    AUIMFCHandle(CWnd* const pWnd) noexcept;
    ~AUIMFCHandle() noexcept override = default;


    //////////////////////////////////////////////////////////////////////////
    // Title
public:
    void SetTitle(const std::wstring& title) override;


    //////////////////////////////////////////////////////////////////////////
    // Activate / Deactivate
public:
    void Activate(AUIHandle* const pParent) override;
    void ActivateModal(AUIHandle* const pParent) override;
    void Deactivate() override;
    bool IsActivated() const override;
    void DoShowMinimized() override;
    void DoShowMaximized() override;
    void DoShowDefault() override;
private:
    void ActivateWnd(AUIHandle* const pParent);


    //////////////////////////////////////////////////////////////////////////
    // Invalidate
public:
    void Invalidate() override;
    void UpdateWindow() override;

    //////////////////////////////////////////////////////////////////////////
    // Visible
public:
    void SetVisible(bool state) override;

    //////////////////////////////////////////////////////////////////////////
    // Focus
public:
    void SetFocus() override;


    //////////////////////////////////////////////////////////////////////////
    // Mouse Event Capture
public:
    void CaptureMouseEvent() override;
    void ReleaseMouseEvent() override;


    //////////////////////////////////////////////////////////////////////////
    // Opacity
public:
    void SetOpacity(const SkAlpha alpha) override;
private:
    bool MakeTransparent();

    //////////////////////////////////////////////////////////////////////////
    // State
public:
    bool IsZoomed() const override;
    bool IsIconic() const override;

    //////////////////////////////////////////////////////////////////////////
    // Size / Position
public:
    void SetResizeable(bool val) override;
    bool IsResizeable() const override;
    void SetSize(int sx, int sy) override;
    void SetPosition(int x, int y) override;
    void SetPositionAndSize(int x, int y, int sx, int sy) override;
    void GetSize(int& sx, int& sy) override;
    void GetPosition(int& x, int& y) override;
    void GetPositionAndSize(int& x, int& y, int& sx, int& sy) override;
private:
    bool m_bUseDefaultPos;


    //////////////////////////////////////////////////////////////////////////
    // Modal Loop
public:
    void BeginModal() override;
    void EndModal(int result) override;

    //////////////////////////////////////////////////////////////////////////
    // MUIWnd
public:
    void SetWndClassName(const std::wstring& wndclassname) {
        m_strWndClassName = wndclassname;
    }
    CWnd* const GetWnd() const { return m_pWnd; }
protected:
    std::wstring m_strWndClassName;
private:
    CWnd* const m_pWnd;
};
