#include "pch.h"
#include "MAUICry2DMaterial.h"

using namespace mit::render;
using namespace mit::alice;

MRUNTIME_IMPL_KINDOF( MAUICry2DMaterial, MGlossyMaterial);

MAUICry2DMaterial::MAUICry2DMaterial( MMaterialGearBox* pGearBox )
    : MGlossyMaterial( pGearBox )
{

}

MAUICry2DMaterial::~MAUICry2DMaterial()
{

}

