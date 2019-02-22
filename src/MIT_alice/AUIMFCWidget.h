#pragma once

#include "AUIDrawableWidget.h"

class CWnd;

class ALICEUI_API AUIMFCWidget : public AUIDrawableWidget
{
public:
    AUIMFCWidget();
    AUIMFCWidget(CWnd* pWnd);
    ~AUIMFCWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // CWnd
public:
    void SetWnd(CWnd* pWnd) noexcept {
        m_pWnd = pWnd;
    }
    CWnd* GetWnd() const noexcept {
        return m_pWnd;
    }
private:
    CWnd* m_pWnd = nullptr;

    // Visible
protected:
    void OnSetVisible(bool state) override;
    void OnSetIgnored(bool state) override;



    //////////////////////////////////////////////////////////////////////////
    // Runtime Class Name
protected:
    std::wstring GetRuntimeClassName() const;


    //////////////////////////////////////////////////////////////////////////
    // Title
public:
    void SetTitle(const std::wstring& title) {
        m_strTitle = title;
    }
    std::wstring GetTitle() const {
        return m_strTitle;
    }
private:
    std::wstring m_strTitle;
};
