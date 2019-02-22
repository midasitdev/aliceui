#pragma once

#include "AUIImageCaptionButtonWidget.h"


class AUITab;
class ALICEUI_API AUITabButtonWidget : public AUIImageCaptionButtonWidget
{
public:
    AUITabButtonWidget();
    ~AUITabButtonWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Tab
public:
    void InitializeTab(const std::shared_ptr< AUITab >& pTab);
    AUITab* const GetTab() const { return m_pTab.lock().get(); }
protected:
	virtual void OnInitializeTab(const std::shared_ptr< AUITab >& pTab);
	void OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value) override;
private:
    std::weak_ptr< AUITab > m_pTab;
};
