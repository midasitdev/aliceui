#pragma once

#include "AUICommonDef.h"

class ALICEUI_API AUIStringFilter
{
public:
    AUIStringFilter();
    virtual ~AUIStringFilter();


    //////////////////////////////////////////////////////////////////////////
    // Filter method
public:
    virtual std::wstring Filter(const std::wstring& strOrigin);
};
