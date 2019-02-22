#pragma once

#include "AUIAPIDef.h"

#include <string>
#include <memory>

class ALICEUI_API AUIClipboard final
{
private:
    AUIClipboard();
    ~AUIClipboard();
public:
    static AUIClipboard& Instance();


    //////////////////////////////////////////////////////////////////////////
    // Plain Text
public:
    std::wstring GetText() const;
    void SetText(const std::wstring& text);


    //////////////////////////////////////////////////////////////////////////
    // Impl
private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
    Impl* GetImpl() const {
        return m_pImpl.get();
    }
};

