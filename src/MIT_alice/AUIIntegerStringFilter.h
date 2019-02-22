#pragma once

#include "AUIStringFilter.h"

class ALICEUI_API AUIIntegerStringFilter : public AUIStringFilter
{
public:
    AUIIntegerStringFilter();
    virtual ~AUIIntegerStringFilter();


    //////////////////////////////////////////////////////////////////////////
    // Filter method
public:
    virtual std::wstring Filter(const std::wstring& strOrigin) override;
protected:
    std::wstring FilterInteger(const std::wstring& strOrigin);
};

