#include "pch.h"
#include "AUIDecelerateInterpolator.h"

AUIDecelerateInterpolator::AUIDecelerateInterpolator( float factor /*= 1.0f */ ) noexcept
    : m_fFactor( factor )
{

}

float AUIDecelerateInterpolator::GetValue( float input ) const 
{
    float x = GetClamp( input );
    return 1.0f - std::pow( 1.0f - x, 2.0f * m_fFactor );
}
