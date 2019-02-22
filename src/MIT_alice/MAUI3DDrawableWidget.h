#pragma once


#include "AUIDrawableWidget.h"

namespace mit
{
    namespace alice
    {
        class ALICEUI_API MAUI3DDrawableWidget : public AUIDrawableWidget
        {
        public:
            MAUI3DDrawableWidget();
            virtual ~MAUI3DDrawableWidget();


            //////////////////////////////////////////////////////////////////////////
            // Matrix
        public:
            void SetMatrix( const glm::mat4& mat ) { m_matModel = mat; }
            const glm::mat4& GetMatrix() { return m_matModel; }
        private:
            glm::mat4 m_matModel;
        };
    }
}
