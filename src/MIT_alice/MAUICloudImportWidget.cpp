#include "pch.h"
#include "MAUICloudImportWidget.h"

using namespace mit::alice;

namespace
{
    constexpr SkScalar DefaultWidth = 150.0f;
    constexpr SkScalar DefaultHeight = 180.0f;
}

MAUICloudImportWidget::MAUICloudImportWidget()
	: AUILinearLayoutWidget(false)
{
	SetDefaultSize(DefaultWidth, DefaultHeight);
}

MAUICloudImportWidget::~MAUICloudImportWidget()
{

}
