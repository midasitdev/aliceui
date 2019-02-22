#include "pch.h"
#include "AUIExpandHeaderTextWidget.h"
#include "AUIColor.h"
#include "AUIColorDrawable.h"

AUIExpandHeaderTextWidget::AUIExpandHeaderTextWidget()
{
    SetSizePolicy(AUISizePolicy::kContent, AUISizePolicy::kContent);
    SetDefaultSize(20.0f, 20.0f);

    // TEST
    SetCaption(L"Hello, World!");

    //SetBackgroundDrawable(std::make_shared<MAUIColorDrawable>(MAUIColor::GetRandomColor(0.1f)));
}

AUIExpandHeaderTextWidget::~AUIExpandHeaderTextWidget()
{

}
