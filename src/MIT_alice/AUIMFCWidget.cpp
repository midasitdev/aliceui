#include "pch.h"
#include "AUIMFCWidget.h"
#include "AUIStringConvert.h"

namespace {
    constexpr float DefaultWidth = 70.0f;
    constexpr float DefaultHeight = 20.0f;
}

AUIMFCWidget::AUIMFCWidget()
{
    SetDefaultSize( DefaultWidth, DefaultHeight );
    SetFreeze(true);
}

AUIMFCWidget::AUIMFCWidget(CWnd* pWnd)
    : m_pWnd(pWnd)
{
    AUIAssert(GetWnd());
    SetDefaultSize(DefaultWidth, DefaultHeight);
    SetFreeze(true);
}

AUIMFCWidget::~AUIMFCWidget()
{
    if (m_pWnd && ::IsWindow(m_pWnd->GetSafeHwnd()))
        m_pWnd->DestroyWindow();
}

void AUIMFCWidget::OnSetVisible(bool state)
{

}

void AUIMFCWidget::OnSetIgnored(bool state)
{

}


std::wstring AUIMFCWidget::GetRuntimeClassName() const
{
    if ( GetWnd() == nullptr )
        return {};

    return AUIStringConvert::ACPToWCS(GetWnd()->GetRuntimeClass()->m_lpszClassName);
}
