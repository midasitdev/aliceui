#include "pch.h"
#include "AUIRadioboxWidget.h"
#include "AUIRadioboxDrawable.h"

AUIRadioboxWidget::AUIRadioboxWidget()
{
    SetCheckAnimDrawable( std::make_shared< AUIRadioboxDrawable >() );
}

AUIRadioboxWidget::AUIRadioboxWidget( bool state )
    : AUICheckboxWidget( state )
{
    SetCheckAnimDrawable( std::make_shared< AUIRadioboxDrawable >() );
}

AUIRadioboxWidget::~AUIRadioboxWidget()
{

}

