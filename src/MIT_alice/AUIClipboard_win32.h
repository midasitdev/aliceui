#pragma once

#include "AUIClipboard.h"

class AUIClipboard::Impl final
{
public:
    Impl() = default;
    ~Impl() = default;

    //////////////////////////////////////////////////////////////////////////
    // Plain Text
public:
    std::wstring GetText() const;
    void SetText(const std::wstring& text);
};
