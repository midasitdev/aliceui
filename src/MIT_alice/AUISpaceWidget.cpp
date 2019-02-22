#include "pch.h"
#include "AUISpaceWidget.h"

AUISpaceWidget::AUISpaceWidget()
{
    SetSizePolicy(AUISizePolicy::kFixed, AUISizePolicy::kFixed);
    SetDefaultSize( 1.0f, 1.0f );
}

AUISpaceWidget::~AUISpaceWidget()
{

}
