#pragma once


#include "AUIRasterBase.h"
#include "AUISlotPool.h"

enum class SUB_WINDOW_TYPE
{
    WND_MSGPRINTER,
    WND_CONTEXTMENU,
    NONE
};

class ALICEUI_API AUIWnd : public CWnd, public AUIRasterBase
{
    using SuperClass = CWnd;
    DECLARE_DYNCREATE(AUIWnd);
public:
    AUIWnd();
    ~AUIWnd() override;


    //////////////////////////////////////////////////////////////////////////
    // Register class
public:
    static const wchar_t kWndClassName[];
private:
    bool RegisterWndClass();

    //////////////////////////////////////////////////////////////////////////
    // Layered window

public:
    void SetSubWindowType(const SUB_WINDOW_TYPE& type) { m_eSubWndType = type; }
    const SUB_WINDOW_TYPE& GetSubWindowType() const { return m_eSubWndType; }
    void SetLayeredWindow(bool val);
    bool IsLayeredWindow() const;
private:
    SUB_WINDOW_TYPE m_eSubWndType = SUB_WINDOW_TYPE::NONE;
    bool m_bLayeredWindow = false;

    //////////////////////////////////////////////////////////////////////////
    // Surface
private:
    sk_sp<SkSurface> m_pSurface;

    //////////////////////////////////////////////////////////////////////////
    // Refresh Tick
private:
    AUISlotPool m_RefreshPool;
    bool m_bInDrawCall;
    BOOL m_bTrackMouse;

    //////////////////////////////////////////////////////////////////////////
    // Min Max
public:
    void SetMinSize(int width, int height);
    void SetMaxSize(int width, int height);
    static constexpr int kNoMinMaxSizeValue = -1;
private:
    int m_MinWidth = kNoMinMaxSizeValue;
    int m_MinHeight = kNoMinMaxSizeValue;
    int m_MaxWidth = kNoMinMaxSizeValue;
    int m_MaxHeight = kNoMinMaxSizeValue;

    //////////////////////////////////////////////////////////////////////////
    // Message
protected:
    virtual BOOL PreTranslateMessage(MSG* pMsg) override;

    //////////////////////////////////////////////////////////////////////////
    // Pre Create
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

    //////////////////////////////////////////////////////////////////////////
    // Message Map
    DECLARE_MESSAGE_MAP();
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpcs);
    afx_msg void OnDestroy();
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnMouseLeave();
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg LRESULT OnIMEStart(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnIMEComposition(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnIMEEnd(WPARAM wParam, LPARAM lParam);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    afx_msg void OnNcPaint();
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg BOOL OnNcActivate(BOOL bActive);
};
