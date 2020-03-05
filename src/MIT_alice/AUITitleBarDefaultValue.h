#pragma once


#include "../MIT_alice/AUIColorDef.h"
#include "../MIT_alice/AUIBasicEnumDef.h"

namespace TitleBar
{
    constexpr SkScalar kWidth = 100.0f;
    constexpr SkScalar kHeight = 29.0f;
    constexpr SkScalar kPaddingTop = 5.0f;

    constexpr wchar_t kBackground[] = L"ui_frame/title/ttl_qa_bg.9.png";


    namespace Caption
    {
        constexpr SkScalar kTextSize = 14.0f;
        constexpr AUITextHorzAlign kTextHorzAlign = AUITextHorzAlign::kCenter;
        constexpr AUITextVertAlign kTextVertAlign = AUITextVertAlign::kCenter;
        constexpr SkColor kTextColor = SkColorSetRGB(255, 255, 255);
        constexpr wchar_t kTextFontFamily[] = L"Poppins";
        constexpr SkFontStyle kTextFontStyle = SkFontStyle::Normal();
    }

    namespace QAGroup
    {
        constexpr SkScalar kWidth = 237.0f;
        constexpr SkScalar kHeight = 29.0f;
        constexpr wchar_t kBackground[] = L"ui_frame/title/ttl_qa_bg.9.png";
    }

    namespace QAButton
    {
        constexpr SkScalar kWidth = 22.0f;
        constexpr SkScalar kHeight = 22.0f;

        constexpr wchar_t kBackground[] = L"ui_frame/title/ttl_icon_bg.json";

        constexpr wchar_t kNewIcon[] = L"ui_frame/title/ico_qa_new.json";
        constexpr wchar_t kOpenIcon[] = L"ui_frame/title/ico_qa_open.json";
        constexpr wchar_t kSaveIcon[] = L"ui_frame/title/ico_qa_save.json";
        constexpr wchar_t kCloseIcon[] = L"ui_frame/title/ico_qa_close.json";
        constexpr wchar_t kUndoIcon[] = L"ui_frame/title/ico_qa_undo.json";
        constexpr wchar_t kRedoIcon[] = L"ui_frame/title/ico_qa_redo.json";

        constexpr SkScalar kMarginLeftMost = 10.0f;
        constexpr SkScalar kMarginRightMost = 0.0f;

        constexpr SkScalar kMarginLeft = 0.0f;
        constexpr SkScalar kMarginTop = 3.0f;
        constexpr SkScalar kMarginRight = 19.0f;
        constexpr SkScalar kMarginBottom = 4.0f;
    }

    namespace SysButton
    {
        constexpr SkScalar kBGWidth = 22.0f;
        constexpr SkScalar kBGHeight = 22.0f;

        constexpr SkScalar kMarginRightMost = 14.0f;

        constexpr SkScalar kMarginLeft = 0.0f;
        constexpr SkScalar kMarginTop = 3.0f;
        constexpr SkScalar kMarginRight = 14.0f;
        constexpr SkScalar kMarginBottom = 4.0f;

        constexpr AUISizePolicy kWidthPolicy = AUISizePolicy::kFixed;
        constexpr AUISizePolicy kHeightPolicy = AUISizePolicy::kFixed;

        constexpr wchar_t kBackground[] = L"ui_frame/title/ttl_icon_bg.json";

        constexpr wchar_t kMinimizeIcon[] = L"ui_frame/title/ico_win_min_nor.png";
        constexpr wchar_t kMaximizeIcon[] = L"ui_frame/title/ico_win_full_nor.png";
        constexpr wchar_t kRestoreIcon[] = L"ui_frame/title/ico_win_win_nor.png";
        constexpr wchar_t kCloseIcon[] = L"ui_frame/title/ico_win_close_nor.png";

        constexpr SkScalar kIconMarginLeft = 0.0f;
        constexpr SkScalar kIconMarginTop = 0.0f;
        constexpr SkScalar kIconMarginRight = 0.0f;
        constexpr SkScalar kIconMarginBottom = 0.0f;
    }
}
