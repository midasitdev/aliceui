#pragma once
#include "../MIT_alice/AUIColorDef.h"

namespace CALENDAR
{
    constexpr SkScalar kDefaultWidth = 228.0f;
    constexpr SkScalar kDefaultHeight = 195.0f;
    
    namespace HEADER
    {
        constexpr SkScalar kDefaultWidth = 218.0f;
        constexpr SkScalar kDefaultHeight = 20.0f;
        constexpr SkScalar kMarginLeft = 5.0f;
        constexpr SkScalar kMarginTop = 3.0f;
        constexpr SkScalar kMarginRight = 5.0f;
        constexpr SkScalar kMarginBottom = 3.0f;

        namespace QUICKBTN
        {
            constexpr SkScalar kDefaultWidth = 100.0f;
            constexpr SkScalar kDefaultHeight = 20.0f;
            constexpr SkScalar kMarginRight = 55.0f;
            constexpr wchar_t kBackground[] = L"ui_frame/calendar/quickbtn.json";
        }

        namespace CHANGEBTN
        {
            constexpr SkScalar kDefaultWidth = 30.0f;
            constexpr SkScalar kDefaultHeight = 20.0f;
            constexpr SkScalar kMarginRight = 1.0f;
            constexpr wchar_t kBackground[] = L"ui_frame/calendar/changebtn.json";
            constexpr wchar_t kDownBtn[] = L"ui_frame/calendar/down.json";
            constexpr wchar_t kUpBtn[] = L"ui_frame/calendar/up.json";
        }
    }
    namespace FOLD
    {
        constexpr SkScalar kPopupPosX = 0.0f;
        constexpr SkScalar kPopupPosY = 25.0f;
        constexpr wchar_t kBackground[] = L"ui_frame/calendar/foldbtn.json";
    }

    namespace TABLE
    {
        constexpr SkScalar kMarginLeft = 5.0f;
        constexpr SkScalar kSmallBtnMarginBottom = 1.0f;
        constexpr SkScalar kLargeBtnMarginBottom = 4.0f;
    }

    namespace ELEMENT
    {
        constexpr SkScalar kSmallBtnDefaultWidth = 30.0f;
        constexpr SkScalar kSmallBtnDefaultHeight = 20.0f;
        constexpr SkScalar kLargeBtnDefaultWidth = 50.0f;
        constexpr SkScalar kLargeBtnDefaultHeight = 45.0f;

        constexpr SkScalar kSmallBtnMarginRight = 1.0f;
        constexpr SkScalar kLargeBtnMarginRight = 6.0f;

        constexpr wchar_t kDayOfTheWeekBackground[] = L"ui_frame/calendar/dayoftheweek.9.png";
        constexpr wchar_t kSmallBtnBackground[] = L"ui_frame/calendar/smallbtn.json";
        constexpr wchar_t kLargeBtnBackground[] = L"ui_frame/calendar/largebtn.json";
        constexpr wchar_t kDisabledBackground[] = L"ui_frame/calendar/bg_noimage.9.png";
    }
}
