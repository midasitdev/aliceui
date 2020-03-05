#pragma once

#include <codecvt>
#include <array>
#include <string>


//////////////////////////////////////////////////////////////////////////
// Coordinate space
enum class AUICoordSpace
{
    kWorld = 0,     // 3D
    kWorldPanel,    // 3D with front facing
    kSteadyScale,   // 3D with scale preserved
    kScreenSpace,   // 2D screen space
};
#define AUICoordSpaceNum 4

//////////////////////////////////////////////////////////////////////////
// Size policy
enum class AUIMeasureSpec
{
    kUnspecified = 0,
    kExactly,
    kAtMost
};

//////////////////////////////////////////////////////////////////////////
// Popup Option
enum class AUIPopupPos
{
    kUnchanged = 0,
    kOptimal,
    kParentOptimalBottom,
    kParentOptimalAbove,
};

//////////////////////////////////////////////////////////////////////////
// Text alignment
enum class AUITextHorzAlign
{
    kLeft = 0,
    kCenter,
    kRight
};
enum class AUITextVertAlign
{
    kTop = 0,
    kCenter,
    kBottom
};
enum class AUITextLineFeed
{
    kNone = 0,          // No multiline
    kNewline,           // Split by newline
    kNewlineCharBreak,  // Split by newline or character
    kNewlineWordBreak,  // Split by newline or word
};

//////////////////////////////////////////////////////////////////////////
// GUI Handle mode
enum class AUIHandleMode
{
    kPopup = 0,
    kChild
};

//////////////////////////////////////////////////////////////////////////
// Image stretch
enum class AUIImageStretch
{
    kOriginal = 0,
    kUniform,
    kUniformToFill,
    kFill
};

//////////////////////////////////////////////////////////////////////////
// Image Caption style
enum class AUIImageCaptionStyle
{
    kNothing = 0,
    kImageOnly,
    kTextOnly,
    kImageAndText,
    kImageAndTextAndImage
};

//////////////////////////////////////////////////////////////////////////
// Constants
constexpr size_t kAUIChildPosEnd = size_t(-1);

#include <cstdint>

#define AUIEnableEnumClassOperatorImpl(T, UnderlyingType) \
    enum class T; \
    inline T operator &(const T x, const T y) noexcept { return static_cast<T>(static_cast<UnderlyingType>(x) & static_cast<UnderlyingType>(y)); }; \
    inline T operator |(const T x, const T y) noexcept { return static_cast<T>(static_cast<UnderlyingType>(x) | static_cast<UnderlyingType>(y)); }; \
    inline T operator ^(const T x, const T y) noexcept { return static_cast<T>(static_cast<UnderlyingType>(x) ^ static_cast<UnderlyingType>(y)); }; \
    inline T operator ~(const T x) noexcept { return static_cast<T>( ~static_cast<UnderlyingType>(x)); }; \
    inline T& operator &=(T& x, const T y) noexcept { x = x & y; return x; }; \
    inline T& operator |=(T& x, const T y) noexcept { x = x | y; return x; }; \
    inline T& operator ^=(T& x, const T y) noexcept { x = x ^ y; return x; }; \
    inline bool AUICheckEnumFlag(const T v) noexcept { return !!static_cast<UnderlyingType>(v); };

#define AUIEnableEnumClassOperator(EnumType) AUIEnableEnumClassOperatorImpl(EnumType, uint32_t)
