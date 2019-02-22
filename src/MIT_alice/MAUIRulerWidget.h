#pragma once

#include "AUIDrawableWidget.h"
#include "MAUIRulerDrawableDef.h"
#include "MAUIRulerDrawableDef.h"

namespace mit
{
    namespace alice
    {
        class MAUIRulerDrawable;
        class ALICEUI_API MAUIRulerWidget : public AUIDrawableWidget
        {
            using SuperWidget = AUIDrawableWidget;
        public:
            MAUIRulerWidget();
            ~MAUIRulerWidget() override;




            //////////////////////////////////////////////////////////////////////////
            // Drawable
        protected:
            MAUIRulerDrawable* const GetRulerDrawable() const;
        private:
            std::shared_ptr< MAUIRulerDrawable > m_pRulerDrawable;


            //////////////////////////////////////////////////////////////////////////
            // Ruler Padding
        public:
            void SetRulerPadding( SkScalar l, SkScalar t, SkScalar r, SkScalar b );


            //////////////////////////////////////////////////////////////////////////
            // Location
        public:
            void SetLocation( AUIRulerLocation location );
            AUIRulerLocation GetLocation() const;


            //////////////////////////////////////////////////////////////////////////
            // Ref Position
        public:
            void SetRefPos( SkScalar pos );
            SkScalar GetRefPos() const;


            //////////////////////////////////////////////////////////////////////////
            // Basis & Scale
        public:
			void SetScale( SkScalar val);
            void SetBasis( SkScalar val );
			void SetGradationSize( SkScalar val );
			SkScalar GetScale() const;
            SkScalar GetBasis() const;
            SkScalar GetGradationSize() const;


            //////////////////////////////////////////////////////////////////////////
            // Text
        public:
            void SetMaxTextWidth( SkScalar val );
            void SetMaxTextHeight( SkScalar val );
            void SetTextSize( SkScalar size );
            SkScalar GetMaxTextWidth() const;
            SkScalar GetMaxTextHeight() const;
            SkScalar GetTextSize() const;


            //////////////////////////////////////////////////////////////////////////
            // Color Option
        public:
            void SetLineColor( SkColor color );
            void SetTextColor( SkColor color );
            SkColor GetLineColor() const;
            SkColor GetTextColor() const;

            // Marking
        public:
            void SetUseMarking(bool val);
            bool IsUseMarking() const;

        };
    }
}
