#include "pch.h"
#include "AUIAccelDecelInterpolator.h"

static const float PI_Value = std::acos( -1.0f );

AUIAccelDecelInterpolator::AUIAccelDecelInterpolator( float factor /*= 1.0f */ ) noexcept
    : m_fFactor( factor )
{

}

float AUIAccelDecelInterpolator::GetValue( float input ) const 
{
    float x = GetClamp( input );
    return std::cos( ( x + 1.0f ) * PI_Value ) * 0.5f + 0.5f;
}
