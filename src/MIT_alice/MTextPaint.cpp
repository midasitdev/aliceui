#include "stdafx.h"
#include "MTextPaint.h"


using namespace mit::alice;

static const SkColor DefaultBGColor = 0xFFFFFFFF;
static const SkColor DefaultLinkColor = 0xFF7F7FFF;
static const SkColor DefaultUnderlineColor = 0x00000000;
static const float DefaultBaselineShift = 0.0f;
static const float DefaultUnderlineThickness = 1.0f;
static const MStatedColor::State DefaultState = MStatedColor::S_Default;

MTextPaint::MTextPaint()
    : m_ColorBG( DefaultBGColor )
    , m_ColorLink( DefaultLinkColor )
    , m_ColorUnderline( DefaultUnderlineColor )
    , m_fBaselineShift( DefaultBaselineShift )
    , m_fUnderlineThickness( DefaultUnderlineThickness )
    , m_eState( DefaultState )
{

}

MTextPaint::MTextPaint( const SkPaint& paint )
    : SkPaint( paint )
    , m_ColorBG( DefaultBGColor )
    , m_ColorLink( DefaultLinkColor )
    , m_ColorUnderline( DefaultUnderlineColor )
    , m_fBaselineShift( DefaultBaselineShift )
    , m_fUnderlineThickness( DefaultUnderlineThickness )
    , m_eState( DefaultState )
{

}

MTextPaint::~MTextPaint()
{

}

