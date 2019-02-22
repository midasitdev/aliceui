#include "pch.h"
#include "AUIAccelerateInterpolator.h"


AUIAccelerateInterpolator::AUIAccelerateInterpolator( float factor /*= 1.0f */ ) noexcept
    : m_fFactor( factor )
{

}


float AUIAccelerateInterpolator::GetValue( float input ) const 
{
    float x = GetClamp( input );
    return std::pow( x, 2.0f * m_fFactor );
}
