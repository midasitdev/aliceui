#pragma once

#include "AUICommonDef.h"

namespace mit
{
    namespace alice
    {
        struct Ellipsoid
        {
            float posX;
            float posY;
            float posZ;
            float radiusX;
            float radiusY;
            float radiusZ;
            SkColor color;

            //////////////////////////////////////////////////////////////////////////
            // Basic constructor
            Ellipsoid() : posX( 0.0f ), posY( 0.0f ), posZ( 0.0f ), radiusX( 1.0f ), radiusY( 1.0f ), radiusZ( 1.0f ), color(kAUIColorWhite ) { }


            //////////////////////////////////////////////////////////////////////////
            // Make
            static Ellipsoid Make() { return Ellipsoid(); }
            static Ellipsoid MakeRadius( float rx, float ry, float rz ) { Ellipsoid e; e.SetRadius( rx, ry, rz ); return e; }
            static Ellipsoid MakePos( float x, float y, float z ) { Ellipsoid e; e.SetPos( x, y, z ); return e; }
            static Ellipsoid MakePosRadius( float x, float y, float z, float rx, float ry, float rz ) { Ellipsoid e; e.SetPos( x, y, z ); e.SetRadius( rx, ry, rz ); return e; }


            //////////////////////////////////////////////////////////////////////////
            // Setter
            void SetRadius( float rx, float ry, float rz ) { radiusX = rx; radiusY = ry; radiusZ = rz; }
            void SetPos( float x, float y, float z ) { posX = x; posY = y; posZ = z; }
            void SetColor( const SkColor& c ) { color = c; }
        };
    }
}
