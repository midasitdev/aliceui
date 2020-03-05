#pragma once

#include "../MIT_alice/AUIColorDef.h"
#include "../MIT_alice/AUIBasicEnumDef.h"

namespace COMBO
{
    constexpr SkScalar kDefaultWidth = 100.0f;
    constexpr SkScalar kDefaultHeight = 23.0f;

    namespace POPUP
    {
        constexpr wchar_t kComboPopupBackground[] = L"drawable/mp_combo_listbg.9.png";
        constexpr SkScalar kComboPopupPaddingLeft = 7.0f;
        constexpr SkScalar kComboPopupPaddingTop = 4.0f;
        constexpr SkScalar kComboPopupPaddingRight = 9.0f;
        constexpr SkScalar kComboPopupPaddingBottom = 5.0f;
    }

    namespace ITEM
    {
        constexpr wchar_t kComboItemBackground[] = L"drawable/mp_combo_list.json";
        constexpr SkScalar kComboItemDefaultHeight = 23.0f;
        constexpr SkScalar kComboItemMinWidth = 219.0f;
        constexpr SkScalar kComboItemMinHeight = 16.0f;
        constexpr SkScalar kComboItemMarginLeft = 0.0f;
        constexpr SkScalar kComboItemMarginTop = 1.0f;
        constexpr SkScalar kComboItemMarginRight = 0.0f;
        constexpr SkScalar kComboItemMarginBottom = 1.0f;
    }

    namespace ARROW
    {
        constexpr SkScalar kComboArrowOffset = 5.0f;
        constexpr SkScalar kComboArrowSize = 5.0f;
        constexpr SkColor kComboArrowColor = SkColorSetRGB(160, 166, 182);
    }
}
