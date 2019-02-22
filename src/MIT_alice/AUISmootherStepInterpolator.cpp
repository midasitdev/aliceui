#include "pch.h"
#include "AUISmootherStepInterpolator.h"

float AUISmootherStepInterpolator::GetValue( float input ) const 
{
    float x= GetClamp( input );
    return x * x * x * ( x * ( x * 6.0f - 15.0f ) + 10.0f );
}
