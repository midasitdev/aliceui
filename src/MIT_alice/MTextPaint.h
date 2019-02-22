/*
 * This part is based on Android Open Source Project
 * Original source code is licensed under Apache License, Version 2.0
 * Reference Link : https://github.com/android/platform_frameworks_base
 */
#pragma once
#define MIDAS_SDK
#include "MStatedColorDef.h"
#include "MAUICommonDef.h"

#include "HeaderPre.h"
namespace mit
{
    namespace alice
    {
        class __MY_EXT_CLASS__ MTextPaint : public SkPaint
        {
        public:
            MTextPaint();
            MTextPaint( const SkPaint& paint );
            virtual ~MTextPaint();



            //////////////////////////////////////////////////////////////////////////
            // Text specified data
        public:
            void SetBGColor( const SkColor& color ) { m_ColorBG = color; }
            void SetLinkColor( const SkColor& color ) { m_ColorLink = color; }
            void SetUnderlineColor( const SkColor& color ) { m_ColorUnderline = color; }
            void SetBaselineShift( float val ) { m_fBaselineShift = val; }
            void SetUnderlineThickness( float val ) { m_fUnderlineThickness = val; }
            void SetState( MStatedColor::State state ) { m_eState = state; }
            SkColor GetBGColor() const { return m_ColorBG; }
            SkColor GetLinkColor() const { return m_ColorLink; }
            SkColor GetUnderlineColor() const { return m_ColorUnderline; }
            float GetBaselineShift() const { return m_fBaselineShift; }
            float GetUnderlineThickness() const { return m_fUnderlineThickness; }
            MStatedColor::State GetState() const { return m_eState; }
        private:
            SkColor m_ColorBG;
            SkColor m_ColorLink;
            SkColor m_ColorUnderline;
            float m_fBaselineShift;
            float m_fUnderlineThickness;
            MStatedColor::State m_eState;
        };
    }
}
#include "HeaderPost.h"
