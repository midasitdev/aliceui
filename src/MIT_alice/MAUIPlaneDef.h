#pragma once

#include "AUICommonDef.h"

namespace mit
{
	namespace alice
	{
		struct Plane
        {
            enum PLANE_DRAWING_TYPE
            {
                PLANE_DRAWING_TYPE_FACE = 0,
                PLANE_DRAWING_TYPE_LINE,
                PLANE_DRAWING_TYPE_FACE_AND_LINE 
            };
			glm::vec3 vCenter;
			glm::vec3 vNorm;
			glm::vec3 vRef;
            float arMargin[2] = { 0.0f, }; // width, height half
			float fAlpha;
            SkColor faceColor;
            SkColor lineColor;
            float fLineThickness;
            PLANE_DRAWING_TYPE type;
			
            Plane() : vCenter(0,0,0), vNorm(0,0,1), vRef(1,0,0), fAlpha( 0.8f), fLineThickness(4.0f), type(PLANE_DRAWING_TYPE_FACE){arMargin[0] = 20; arMargin[1] = 20; }

			static Plane Make() { return Plane(); }

			void SetNorm( glm::vec3 _Norm ) { vNorm = _Norm; }
			void SetRef( glm::vec3 _Ref ) { vRef = _Ref; }
			void SetCenter( glm::vec3 _Pos ) { vCenter = _Pos; }
            void SetFaceColor( const SkColor& c ) { faceColor = c; }
            void SetLineColor( const SkColor& c ) { lineColor = c; }
            void SetDrawingType( PLANE_DRAWING_TYPE type ) { this->type = type; }
            
            glm::vec4 GetEquation() const
            {
                return glm::vec4(vNorm, -glm::dot(vCenter, vNorm));
            }
		};
	}
}
