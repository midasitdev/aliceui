#include "stdafx.h"
#include "MUILineCircleWidget.h"
#include "MUILineCircleVisual.h"

using namespace mit::ui;

MRUNTIME_IMPL_KINDOF( MUILineCircleWidget, MUIWidget );

MUILineCircleWidget::MUILineCircleWidget()
    : MUIWidget( new MUILineCircleVisual() )
    , m_fLineWidth( 1.0f )
    , m_LineColor( ColorBlack )
{
    SetRootTargetCoord( CoordSpace::World );
}

MUILineCircleWidget::~MUILineCircleWidget()
{

}
