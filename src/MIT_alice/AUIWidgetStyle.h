#pragma once

#include "AUIStateFeature.h"
#include "AUIStyleNotion.h"

class ALICEUI_API AUIWidgetStyle : public AUIStateFeature<AUIStyleNotion>
{
public:
    AUIWidgetStyle() {}
    virtual ~AUIWidgetStyle() {}

};

class  ALICEUI_API AUIStyleUpdator : public AUIStateFeatureUpdator<AUIStyleNotion>
{
public:
    AUIStyleUpdator(std::shared_ptr<const AUIWidgetStyle> pStyle) :AUIStateFeatureUpdator<AUIStyleNotion>(pStyle) {}
    virtual ~AUIStyleUpdator() {}
};
