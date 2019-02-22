#include "pch.h"
#include "AUIToggleWidget.h"
#include "AUIToggleDrawable.h"

namespace
{
    constexpr SkScalar DefaultWidth = 40.0f;
    constexpr SkScalar DefaultHeight = 20.0f;
}

AUIToggleWidget::AUIToggleWidget()
{
    SetDefaultSize( DefaultWidth, DefaultHeight );
    SetCheckAnimDrawable( std::make_shared< AUIToggleDrawable >() );

}

AUIToggleWidget::AUIToggleWidget( bool state )
	: AUICheckboxWidget( state )
{

    SetDefaultSize( DefaultWidth, DefaultHeight );
    SetCheckAnimDrawable( std::make_shared< AUIToggleDrawable >() );
}

AUIToggleWidget::~AUIToggleWidget()
{

}
