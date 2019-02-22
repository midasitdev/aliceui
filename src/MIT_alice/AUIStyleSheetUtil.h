#pragma once

#include "AUIAPIDef.h"
#include "AUIScalar.h"
#include "AUIBasicEnumDef.h"
#include "AUIProperty.h"

#include <regex>
#include <vector>
#include <string>


class ALICEUI_API AUIStyleSheetUtil final
{
    //////////////////////////////////////////////////////////////////////////
    // String parsing utillity
public:
    static bool SearchText(const std::wstring& text, const std::wregex& re, std::wsmatch& m);
    static std::wstring Trim(const std::wstring& str, const std::wstring& whitespace = L"\r\n \t");
    static std::vector< std::wstring > Split(const std::wstring& str, wchar_t delim = L',');

    //////////////////////////////////////////////////////////////////////////
    // Color parsing
public:
    static bool ToColorValue(const std::wstring& text, SkColor& color);
    static bool ToColorText(const SkColor color, std::wstring& text);

    //////////////////////////////////////////////////////////////////////////
    // Opacity parsing
public:
    static bool ToOpacityValue(const std::wstring& text, SkScalar& opacity);
    static bool ToOpacityText(const SkScalar opacity, std::wstring& text);

    //////////////////////////////////////////////////////////////////////////
    // Boolean parsing
public:
    static bool ToBoolValue(const std::wstring& text, bool& val);
    static bool ToBoolText(const bool val, std::wstring& text);

    //////////////////////////////////////////////////////////////////////////
    // Size parsing ( px, dp, ... )
public:
    static bool ToSizeValue(const std::wstring& text, SkScalar& val);
    static bool ToSizeText(const SkScalar val, std::wstring& text);

    //////////////////////////////////////////////////////////////////////////
    // SizePolicy parsing
public:
    static bool ToSizePolicyValue(const std::wstring& text, AUISizePolicy& policy);
    static bool ToSizePolicyText(const AUISizePolicy policy, std::wstring& text);

    //////////////////////////////////////////////////////////////////////////
    // Gravity parsing
public:
    static std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt > ToGravityOptionValue(const std::wstring& text, std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt >& arrOpt);
    static bool ToGravityOptionText(const std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt >& arrHasOpt, const std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt >& arrOpt, std::wstring& text);

    //////////////////////////////////////////////////////////////////////////
    // Align parsing
public:
    static std::array< bool, AUIProperty::kParentOptTotal_ParentOpt > ToAlignParentOptionValue(const std::wstring& text, std::array< bool, AUIProperty::kParentOptTotal_ParentOpt >& arrOpt);
    static bool ToAlignParentOptionText(const std::array< bool, AUIProperty::kParentOptTotal_ParentOpt >& arrHasOpt, const std::array< bool, AUIProperty::kParentOptTotal_ParentOpt >& arrOpt, std::wstring& text);


    //////////////////////////////////////////////////////////////////////////
    // Text Align
public:
    static bool ToTextHorzAlignValue(const std::wstring& text, AUITextHorzAlign& align);
    static bool ToTextVertAlignValue(const std::wstring& text, AUITextVertAlign& align);
    static bool ToTextHorzAlignText(const AUITextHorzAlign& align, std::wstring& text);
    static bool ToTextVertAlignText(const AUITextVertAlign& align, std::wstring& text);

    //////////////////////////////////////////////////////////////////////////
    // Font size
public:
    static bool ToFontSizeValue(const std::wstring& text, SkScalar val);
    static bool ToFontSizeText(const SkScalar& val, std::wstring& text);

    //////////////////////////////////////////////////////////////////////////
    // Font Family
public:
    static bool ToFontFamilyValue(const std::wstring& text, std::vector< std::wstring >& arrFontFamily);
    static bool ToFontFamilyText(const std::vector< std::wstring >& arrFontFamily, std::wstring& text);
    static bool ToFontStyleValue(const std::wstring& text, SkFontStyle& style);
    static bool ToFontStyleText(const SkFontStyle& style, std::wstring& text);

public:

    static bool ToURIValue(const std::wstring& text, std::wstring& url);

};
