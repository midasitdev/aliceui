#pragma once


#include "../MIT_alice/AUIColorDef.h"
#include "../MIT_alice/AUIBasicEnumDef.h"

namespace TitleBar
{
    constexpr SkScalar kWidth = 100.0f;
    constexpr SkScalar kHeight = 28.0f;

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
        constexpr SkScalar kWidth = 213.0f;
        constexpr SkScalar kHeight = 28.0f;

        constexpr wchar_t kBackground[] = L"ui_frame/title/ttl_qa_bg.9.png";

    }

    namespace QAButton
    {
        constexpr SkScalar kWidth = 22.0f;
        constexpr SkScalar kHeight = 22.0f;

        constexpr wchar_t kBackground[] = L"ui_frame/title/ttl_qa_icon_bg.json";

        constexpr wchar_t kUndoIcon[] = L"ui_frame/title/ico_qa_undo.json";
        constexpr wchar_t kRedoIcon[] = L"ui_frame/title/ico_qa_redo.json";
        constexpr wchar_t kNewIcon[] = L"ui_frame/title/ico_qa_new.json";
        constexpr wchar_t kOpenIcon[] = L"ui_frame/title/ico_qa_dummy01.json";
        constexpr wchar_t kSaveIcon[] = L"ui_frame/title/ico_qa_dummy02.json";

        constexpr SkScalar kMarginLeftMost = 7.0f;
        constexpr SkScalar kMarginRightMost = 9.0f;

        constexpr SkScalar kMarginLeft = 0.0f;
        constexpr SkScalar kMarginTop = 3.0f;
        constexpr SkScalar kMarginRight = 13.0f;
        constexpr SkScalar kMarginBottom = 3.0f;
    }

    namespace SysButton
    {
        constexpr SkScalar kWidth = 22.0f;
        constexpr SkScalar kHeight = 22.0f;
        constexpr AUISizePolicy kWidthPolicy = AUISizePolicy::kFixed;
        constexpr AUISizePolicy kHeightPolicy = AUISizePolicy::kFixed;

        constexpr wchar_t kBackground[] = L"ui_frame/title/ttl_win_icon_bg.json";

        constexpr wchar_t kMinimizeIcon[] = L"ui_frame/title/ico_win_min_nor.png";
        constexpr wchar_t kMaximizeIcon[] = L"ui_frame/title/ico_win_full_nor.png";
        constexpr wchar_t kRestoreIcon[] = L"ui_frame/title/ico_win_win_nor.png";
        constexpr wchar_t kCloseIcon[] = L"ui_frame/title/ico_win_close_nor.png";

        constexpr SkScalar kMarginRightMost = 13.0f;

        constexpr SkScalar kMarginLeft = 0.0f;
        constexpr SkScalar kMarginTop = 3.0f;
        constexpr SkScalar kMarginRight = 14.0f;
        constexpr SkScalar kMarginBottom = 3.0f;
    }
}
