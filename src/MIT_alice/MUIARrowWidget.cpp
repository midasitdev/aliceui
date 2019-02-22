#include "stdafx.h"
#include "MUIArrowWidget.h"
#include "MUIArrowVisual.h"

using namespace mit::ui;

MRUNTIME_IMPL_KINDOF( MUIArrowWidget, MUIWidget );


MUIArrowWidget::MUIArrowWidget( bool moveitself )
    : MUIWidget( new MUIArrowVisual() )
    , m_v3Direction( 1.0f, 0.0f, 0.0f )
    , m_Color( ColorWhite )
    , m_bMoveItself( moveitself )
{
    SetDraggable( true );
}

MUIArrowWidget::MUIArrowWidget( const glm::vec3& dir, bool moveitself )
    : MUIWidget( new MUIArrowVisual() )
    , m_v3Direction( dir )
    , m_Color( ColorWhite )
    , m_bMoveItself( moveitself )
{
    assert( m_v3Direction.length() != 0.0f );
}

MUIArrowWidget::~MUIArrowWidget()
{

}
