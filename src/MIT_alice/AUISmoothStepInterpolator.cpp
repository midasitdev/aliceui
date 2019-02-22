#include "pch.h"
#include "AUISmoothStepInterpolator.h"

float AUISmoothStepInterpolator::GetValue( float input ) const 
{
    float x = GetClamp( input );

    return x * x * ( 3.0f - 2.0f * x );
}
