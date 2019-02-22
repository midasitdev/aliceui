#include "pch.h"
#include "AUIClipboard.h"

#if defined(_WIN32)
#include "AUIClipboard_win32.h"
#else
#   error Implement clipboard
#endif

AUIClipboard::AUIClipboard()
    : m_pImpl(new Impl())
{

}

AUIClipboard::~AUIClipboard()
{

}

AUIClipboard& AUIClipboard::Instance()
{
    static AUIClipboard sClipboard;
    return sClipboard;
}

std::wstring AUIClipboard::GetText() const
{
    return GetImpl()->GetText();
}

void AUIClipboard::SetText(const std::wstring& text)
{
    GetImpl()->SetText( text );
}
