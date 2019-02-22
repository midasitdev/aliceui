#pragma once


#include "MITAliceDef.h"
#include "MAUIRulerDrawableDef.h"

namespace mit
{
    namespace alice
    {
        class MITALICE_API MAUIRulerDrawable : public AUIDrawable
        {
        public:
            MAUIRulerDrawable();
            virtual ~MAUIRulerDrawable();

            //////////////////////////////////////////////////////////////////////////
            // Location
        public:
            void SetLocation( AUIRulerLocation location ) { m_Location = location; }
            AUIRulerLocation GetLocation() const { return m_Location; }
        private:
            AUIRulerLocation m_Location;


            //////////////////////////////////////////////////////////////////////////
            // Reference Position
        public:
            void SetRefPos( SkScalar pos ) { m_RefPos = pos; }
            SkScalar GetRefPos() const { return m_RefPos; }
        private:
            SkScalar m_RefPos;


            //////////////////////////////////////////////////////////////////////////
            // Paint
        public:
            SkPaint& RefLinePaint() { return m_LinePaint; }
            SkPaint& RefTextPaint() { return m_TextPaint; }
        private:
            SkPaint m_LinePaint;
            SkPaint m_TextPaint;


            //////////////////////////////////////////////////////////////////////////
            // Basis & Scale
        public:
			void SetScale( SkScalar val ) { m_Scale = val; }
            void SetBasis( SkScalar val ) { m_Basis = val; }
            void SetGradationSize( SkScalar val ) { m_GradationSize = val; }
			SkScalar GetScale() const { return m_Scale; }
            SkScalar GetBasis() const { return m_Basis; }
            SkScalar GetGradationSize() const { return m_GradationSize; }
        private:
			SkScalar m_Scale = 1.0f;
            SkScalar m_Basis = 1.0f;
            SkScalar m_GradationSize = 1.0f;


            //////////////////////////////////////////////////////////////////////////
            // Text
        public:
            void SetMaxTextWidth( SkScalar val ) { m_MaxTextWidth = val; }
            void SetMaxTextHeight( SkScalar val ) { m_MaxTextHeight = val; }
            SkScalar GetMaxTextWidth() const { return m_MaxTextWidth; }
            SkScalar GetMaxTextHeight() const { return m_MaxTextHeight; }
        private:
            SkScalar m_MaxTextWidth;
            SkScalar m_MaxTextHeight;


            //////////////////////////////////////////////////////////////////////////
            // Draw
        protected:
            void OnDraw( SkCanvas* const canvas ) override;
            void OnDrawLeft( SkCanvas* const canvas );
            void OnDrawTop( SkCanvas* const canvas );
            void OnDrawRight( SkCanvas* const canvas );
            void OnDrawBottom( SkCanvas* const canvas );


            // Marking
        public:
            void SetUseMarking(bool val) {
                m_UseMarking = val;
            }
            bool IsUseMarking() const {
                return m_UseMarking;
            }
        private:
            bool m_UseMarking = true;
        };
    }
}

