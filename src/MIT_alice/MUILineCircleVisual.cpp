#include "stdafx.h"
#include "MUILineCircleVisual.h"
#include "MUILineCircleWidget.h"

using namespace mit::ui;

MRUNTIME_IMPL_KINDOF( MUILineCircleVisual, MUILinesVisual );

MUILineCircleVisual::MUILineCircleVisual()
{

}

MUILineCircleVisual::~MUILineCircleVisual()
{

}

const std::vector< mit::ui::Circle >& MUILineCircleVisual::GetCircles() const
{
    return GetWidgetCast< MUILineCircleWidget >()->GetCircles();
}

float MUILineCircleVisual::GetLineWidth() const
{
    return GetWidgetCast< MUILineCircleWidget >()->GetLineWidth();
}

SkColor MUILineCircleVisual::GetLineColor() const
{
    return GetWidgetCast< MUILineCircleWidget >()->GetLineColor();
}
