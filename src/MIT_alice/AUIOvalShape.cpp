#include "pch.h"
#include "AUIOvalShape.h"

AUIOvalShape::AUIOvalShape()
{

}

AUIOvalShape::~AUIOvalShape()
{

}

void AUIOvalShape::OnResize( float width, float height )
{
    RefRRect().setOval( SkRect::MakeWH( width, height ) );
}
