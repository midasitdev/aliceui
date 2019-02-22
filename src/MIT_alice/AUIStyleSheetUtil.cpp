#include "pch.h"
#include "AUIStyleSheetUtil.h"
#include "AUIColor.h"
#include "AUIStringUtil.h"

bool AUIStyleSheetUtil::SearchText( const std::wstring& text, const std::wregex& re, std::wsmatch& m )
{
    return std::regex_search( text, m, re );
}

std::wstring AUIStyleSheetUtil::Trim(const std::wstring& str, const std::wstring& whitespace )
{
    const auto start = str.find_first_not_of( whitespace );
    if ( start == std::wstring::npos )
        return L"";

    const auto end = str.find_last_not_of( whitespace );
    const auto range = end - start + 1;
    return str.substr( start, range );
}

std::vector< std::wstring > AUIStyleSheetUtil::Split(const std::wstring& str, wchar_t delim )
{
    std::vector< std::wstring > sub;
    std::wistringstream buf( str );
    for ( std::wstring token ; std::getline( buf, token, L',' ) ; )
        sub.emplace_back( token );
    return sub;
}

bool AUIStyleSheetUtil::ToColorValue( const std::wstring& text, SkColor& color )
{
    if ( text.empty() )
        return false;

    // Named color
    if ( AUIColor::FindNamed( text, color ) )
        return true;

    std::wsmatch m;

    // Hexadecimal : #RRGGBB
    static const std::wregex reHexRGB( L"^#([A-Fa-f0-9]{6})" );
    const auto foundHexRGB = AUIStyleSheetUtil::SearchText( text, reHexRGB, m );
    if ( foundHexRGB )
    {
        AUIAssert( m.size() == 2 );
        std::wstringstream ss;
        ss << std::hex << m[1];
        ss >> color;
        color = SkColorSetA( color, 0xFF );
        return true;
    }

    // rgb() : rgb( 0~255, 0~255, 0~255 )
    static const std::wregex reRGB( L"rgb\\(\\s*(\\d+)(%?)\\s*,\\s*(\\d+)(\\2)\\s*,\\s*(\\d+)(\\2)\\s*\\)" );
    const auto foundRGB = AUIStyleSheetUtil::SearchText( text, reRGB, m );
    if ( foundRGB )
    {
        AUIAssert( m.size() == 7 );
        const auto r = std::clamp( std::stoi( m[1] ), 0x00, 0xFF );
        const auto g = std::clamp( std::stoi( m[3] ), 0x00, 0xFF );
        const auto b = std::clamp( std::stoi( m[5] ), 0x00, 0xFF );
        color = SkColorSetRGB( r, g, b );
        return true;
    }

    // rgba() : rgba( 0~255, 0~255, 0~255, 0.0~1.0 )
    static const std::wregex reRGBA( L"rgba\\(\\s*(\\d+)(%?)\\s*,\\s*(\\d+)(\\2)\\s*,\\s*(\\d+)(\\2)\\s*,\\s*(\\d+|\\d*.\\d+)\\s*\\)" );
    const auto foundRGBA = AUIStyleSheetUtil::SearchText( text, reRGBA, m );
    if ( foundRGBA )
    {
        AUIAssert( m.size() == 8 );
        const auto r = std::clamp( std::stoi( m[1] ), 0x00, 0xFF );
        const auto g = std::clamp( std::stoi( m[3] ), 0x00, 0xFF );
        const auto b = std::clamp( std::stoi( m[5] ), 0x00, 0xFF );
        const auto a = std::clamp( int( 255.0f * std::stof( m[7] ) ), 0x00, 0xFF );
        color = SkColorSetARGB( a, r, g, b );
        return true;
    }

    // hsl() : hsl( 0~360, 0%~100%, 0%~100% )
    static const std::wregex reHSL( L"hsl\\(\\s*(\\d+)\\s*,\\s*(\\d+)%\\s*,\\s*(\\d+)%\\s*\\)" );
    const auto foundHSL = AUIStyleSheetUtil::SearchText( text, reHSL, m );
    if ( foundHSL )
    {
        AUIAssert( m.size() == 4 );
        const auto h = std::clamp( std::stof( m[1] ), 0.0f, 360.0f );
        const auto s = std::clamp( std::stof( m[2] ) / 100.0f, 0.0f, 1.0f );
        const auto l = std::clamp( std::stof( m[3] ) / 100.0f, 0.0f, 1.0f );
        const SkScalar hsl[3] = { h, s, l };
        color = SkHSVToColor( hsl );
        return true;
    }

    // hsla() : hsla( 0~360, 0%~100%, 0%~100%, 0.0~1.0 )
    static const std::wregex reHSLA( L"hsla\\(\\s*(\\d+)%?\\s*,\\s*(\\d+)%\\s*,\\s*(\\d+)%\\s*,\\s*(\\d+|\\d*.\\d+)\\s*\\)" );
    const auto foundHSLA = AUIStyleSheetUtil::SearchText( text, reHSLA, m );
    if ( foundHSLA )
    {
        AUIAssert( m.size() == 5 );
        const auto h = std::clamp( std::stof( m[1] ), 0.0f, 360.0f );
        const auto s = std::clamp( std::stof( m[2] ) / 100.0f, 0.0f, 1.0f );
        const auto l = std::clamp( std::stof( m[3] ) / 100.0f, 0.0f, 1.0f );
        const auto a = std::clamp( int( 255.0f * std::stof( m[4] ) ), 0x00, 0xFF );
        const SkScalar hsl[3] = { h, s, l };
        color = SkHSVToColor( a, hsl );
        return true;
    }

    AUIAssertFailReason("Invalid color text");
    return false;
}

bool AUIStyleSheetUtil::ToColorText( const SkColor color, std::wstring& text )
{
    const auto a = SkColorGetA( color );
    const auto r = SkColorGetR( color );
    const auto g = SkColorGetG( color );
    const auto b = SkColorGetB( color );


    std::wstringstream ss;
    if ( a == kAUIAlpha100 )
    {
        ss << L"rgb( " << r << L", " << g << L", " << b << L" );";
    }
    else
    {
        ss << L"rgba( " << r << L", " << g << L", " << b << L", " << std::clamp( float( a ) / 255.0f, 0.0f, 1.0f ) << L" );";
    }
    text = ss.str();

    return true;
}

bool AUIStyleSheetUtil::ToBoolValue( const std::wstring& text, bool& val )
{
    std::wstring lower_text = text;
    std::transform( lower_text.begin(), lower_text.end(), lower_text.begin(), ::tolower );
    if ( L"true" == lower_text )
    {
        val = true;
        return true;
    }
    else if ( L"false" == lower_text )
    {
        val = false;
        return true;
    }
    else if ( L"1" == lower_text )
    {
        val = true;
        return true;
    }
    else if ( L"0" == lower_text )
    {
        val = false;
        return true;
    }

    AUIAssertFailReason("Invalid boolean text");
    return false;
}

bool AUIStyleSheetUtil::ToBoolText( const bool val, std::wstring& text )
{
    if ( val )
        text = L"true";
    else
        text = L"false";
    return true;
}

bool AUIStyleSheetUtil::ToSizeValue( const std::wstring& text, SkScalar& val )
{
    static const std::wregex re( L"^[-+]?[0-9]*\\.?[0-9]+([?[eE][-+]?[0-9]+|[.|eE])?" );
    std::wsmatch m;
    std::regex_search( text, m, re );

    if ( m.size() == 0 )
    {
        val = SkScalar( 0 );
        return false;
    }

    std::wsmatch mscale;
    std::regex_search( text, mscale, std::wregex( L"px$" ) );
    SkScalar weight = 1.0f;
    if ( mscale.size() > 0 )
    {
        if ( mscale[0] == L"px" )
            weight = 1.0f;
    }

    try
    {
        if constexpr ( std::is_same< float, SkScalar >::value )
        {
            val = static_cast< SkScalar >( std::stof( m[0] ) * weight );
        }
        else if constexpr ( std::is_same< double, SkScalar >::value )
        {
            val = static_cast< SkScalar >( std::stod( m[0] ) * weight );
        }
        else
        {
            val = static_cast< SkScalar >( std::stod( text ) ) * weight;
        }
    }
    catch ( std::exception& )
    {
        val = SkScalar( 0 );
        return false;
    }
    return true;
}

bool AUIStyleSheetUtil::ToSizeText( const SkScalar val, std::wstring& text )
{
    text = std::to_wstring( val ) + L"px";
    return true;
}

bool AUIStyleSheetUtil::ToSizePolicyValue( const std::wstring& text, AUISizePolicy& policy )
{
    bool ret = false;
    if (AUIStringUtil::IsEqualIgnoreCase( text, L"parent" ) )
    {
        policy = AUISizePolicy::kParent;
        ret = true;
    }
    else if (AUIStringUtil::IsEqualIgnoreCase( text, L"content" ) )
    {
        policy = AUISizePolicy::kContent;
        ret = true;
    }
    else if (AUIStringUtil::IsEqualIgnoreCase( text, L"fixed" ) )
    {
        policy = AUISizePolicy::kFixed;
        ret = true;
    }
    return ret;
}

bool AUIStyleSheetUtil::ToSizePolicyText( const AUISizePolicy policy, std::wstring& text )
{
    bool ret = false;
    if ( AUISizePolicy::kParent == policy )
    {
        text = L"parent";
        ret = true;
    }
    else if ( AUISizePolicy::kContent == policy )
    {
        text = L"content";
        ret = true;
    }
    else if ( AUISizePolicy::kFixed == policy )
    {
        text = L"fixed";
        ret = true;
    }
    return ret;
}

std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt > AUIStyleSheetUtil::ToGravityOptionValue( const std::wstring& text, std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt >& arrOpt )
{
    std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt > arrHasOpt;
    arrHasOpt.fill( false );

    std::vector< std::wstring > arrParams;

    const wchar_t WhiteSpaces[] = L"\r\n\t\v\f ";
    std::wstring tmpParams = text;
    while ( tmpParams.size() > 0 )
    {
        const auto foundStart = tmpParams.find_first_not_of( WhiteSpaces );
        if ( std::wstring::npos == foundStart )
            break;
        const auto foundEnd = tmpParams.find_first_of( WhiteSpaces, foundStart + 1 );
        if ( std::wstring::npos == foundEnd )
        {
            arrParams.emplace_back( tmpParams.substr( foundStart ) );
            break;
        }
        arrParams.emplace_back( tmpParams.substr( foundStart, foundEnd - foundStart ) );
        tmpParams = tmpParams.substr( foundEnd );
    }

    if ( arrParams.size() == 0 )
        return arrHasOpt;

    for ( auto idx = 0 ; idx < arrParams.size() ; idx++ )
    {
        const auto param = arrParams[idx];
        if (AUIStringUtil::IsEqualIgnoreCase( L"center", param ) )
        {
            arrHasOpt[AUIProperty::kGravityCenter_GravityOpt] = true;
            arrOpt[AUIProperty::kGravityCenter_GravityOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"center-horizontal", param ) )
        {
            arrHasOpt[AUIProperty::kGravityCenterHorizontal_GravityOpt] = true;
            arrOpt[AUIProperty::kGravityCenterHorizontal_GravityOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"center-vertical", param ) )
        {
            arrHasOpt[AUIProperty::kGravityCenterVertical_GravityOpt] = true;
            arrOpt[AUIProperty::kGravityCenterVertical_GravityOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"left", param ) )
        {
            arrHasOpt[AUIProperty::kGravityLeft_GravityOpt] = true;
            arrOpt[AUIProperty::kGravityLeft_GravityOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"top", param ) )
        {
            arrHasOpt[AUIProperty::kGravityTop_GravityOpt] = true;
            arrOpt[AUIProperty::kGravityTop_GravityOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"right", param ) )
        {
            arrHasOpt[AUIProperty::kGravityRight_GravityOpt] = true;
            arrOpt[AUIProperty::kGravityRight_GravityOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"bottom", param ) )
        {
            arrHasOpt[AUIProperty::kGravityBottom_GravityOpt] = true;
            arrOpt[AUIProperty::kGravityBottom_GravityOpt] = true;
        }
    }
    return arrHasOpt;
}

bool AUIStyleSheetUtil::ToGravityOptionText( const std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt >& arrHasOpt, const std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt >& arrOpt, std::wstring& text )
{
    bool once = false;
    auto funcGetDelim = [&once]()->std::wstring {
        if ( once )
            return L" ";
        once = true;
        return L"";
    };

    text.clear();
    if ( arrHasOpt[AUIProperty::kGravityCenter_GravityOpt] && arrOpt[AUIProperty::kGravityCenter_GravityOpt] )
        text += L"center" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kGravityCenterHorizontal_GravityOpt] && arrOpt[AUIProperty::kGravityCenterHorizontal_GravityOpt] )
        text += L"center-horizontal" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kGravityCenterVertical_GravityOpt] && arrOpt[AUIProperty::kGravityCenterVertical_GravityOpt] )
        text += L"center-vertical" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kGravityLeft_GravityOpt] && arrOpt[AUIProperty::kGravityLeft_GravityOpt] )
        text += L"left" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kGravityTop_GravityOpt] && arrOpt[AUIProperty::kGravityTop_GravityOpt] )
        text += L"top" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kGravityRight_GravityOpt] && arrOpt[AUIProperty::kGravityRight_GravityOpt] )
        text += L"right" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kGravityBottom_GravityOpt] && arrOpt[AUIProperty::kGravityBottom_GravityOpt] )
        text += L"bottom" + funcGetDelim();

    return true;
}

std::array< bool, AUIProperty::kParentOptTotal_ParentOpt > AUIStyleSheetUtil::ToAlignParentOptionValue( const std::wstring& text, std::array< bool, AUIProperty::kParentOptTotal_ParentOpt >& arrOpt )
{
    std::array< bool, AUIProperty::kParentOptTotal_ParentOpt > arrHasOpt;
    arrHasOpt.fill( false );

    std::vector< std::wstring > arrParams;

    const wchar_t WhiteSpaces[] = L"\r\n\t\v\f ";
    std::wstring tmpParams = text;
    while ( tmpParams.size() > 0 )
    {
        const auto foundStart = tmpParams.find_first_not_of( WhiteSpaces );
        if ( std::wstring::npos == foundStart )
            break;
        const auto foundEnd = tmpParams.find_first_of( WhiteSpaces, foundStart + 1 );
        if ( std::wstring::npos == foundEnd )
        {
            arrParams.emplace_back( tmpParams.substr( foundStart ) );
            break;
        }
        arrParams.emplace_back( tmpParams.substr( foundStart, foundEnd - foundStart ) );
        tmpParams = tmpParams.substr( foundEnd );
    }

    if ( arrParams.size() == 0 )
        return arrHasOpt;

    for ( auto idx = 0 ; idx < arrParams.size() ; idx++ )
    {
        const auto param = arrParams[idx];
        if (AUIStringUtil::IsEqualIgnoreCase( L"left", param ) )
        {
            arrHasOpt[AUIProperty::kParentLeft_ParentOpt] = true;
            arrOpt[AUIProperty::kParentLeft_ParentOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"top", param ) )
        {
            arrHasOpt[AUIProperty::kParentTop_ParentOpt] = true;
            arrOpt[AUIProperty::kParentTop_ParentOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"right", param ) )
        {
            arrHasOpt[AUIProperty::kParentRight_ParentOpt] = true;
            arrOpt[AUIProperty::kParentRight_ParentOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"bottom", param ) )
        {
            arrHasOpt[AUIProperty::kParentBottom_ParentOpt] = true;
            arrOpt[AUIProperty::kParentBottom_ParentOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"center-horizontal", param ) )
        {
            arrHasOpt[AUIProperty::kParentCenterHorizontal_ParentOpt] = true;
            arrOpt[AUIProperty::kParentCenterHorizontal_ParentOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"center-vertical", param ) )
        {
            arrHasOpt[AUIProperty::kParentCenterVertical_ParentOpt] = true;
            arrOpt[AUIProperty::kParentCenterVertical_ParentOpt] = true;
        }
        else if (AUIStringUtil::IsEqualIgnoreCase( L"center", param ) )
        {
            arrHasOpt[AUIProperty::kParentCenter_ParentOpt] = true;
            arrOpt[AUIProperty::kParentCenter_ParentOpt] = true;
        }
    }
    return arrHasOpt;
}

bool AUIStyleSheetUtil::ToAlignParentOptionText( const std::array< bool, AUIProperty::kParentOptTotal_ParentOpt >& arrHasOpt, const std::array< bool, AUIProperty::kParentOptTotal_ParentOpt >& arrOpt, std::wstring& text )
{
    bool once = false;
    auto funcGetDelim = [&once]()->std::wstring {
        if ( once )
            return L" ";
        once = true;
        return L"";
    };

    text.clear();
    if ( arrHasOpt[AUIProperty::kParentLeft_ParentOpt] && arrOpt[AUIProperty::kParentLeft_ParentOpt] )
        text += L"left" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kParentTop_ParentOpt] && arrOpt[AUIProperty::kParentTop_ParentOpt] )
        text += L"top" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kParentRight_ParentOpt] && arrOpt[AUIProperty::kParentRight_ParentOpt] )
        text += L"right" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kParentBottom_ParentOpt] && arrOpt[AUIProperty::kParentBottom_ParentOpt] )
        text += L"bottom" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kParentCenterHorizontal_ParentOpt] && arrOpt[AUIProperty::kParentCenterHorizontal_ParentOpt] )
        text += L"center-horizontal" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kParentCenterVertical_ParentOpt] && arrOpt[AUIProperty::kParentCenterVertical_ParentOpt] )
        text += L"center-vertical" + funcGetDelim();
    if ( arrHasOpt[AUIProperty::kParentCenter_ParentOpt] && arrOpt[AUIProperty::kParentCenter_ParentOpt] )
        text += L"center" + funcGetDelim();

    return true;
}

bool AUIStyleSheetUtil::ToTextHorzAlignValue( const std::wstring& text, AUITextHorzAlign& align )
{
    if ( text.empty() )
        return false;

    bool hasValue = false;
    if (AUIStringUtil::IsEqualIgnoreCase( L"left", text ) )
    {
        align = AUITextHorzAlign::kLeft;
        hasValue = true;
    }
    else if (AUIStringUtil::IsEqualIgnoreCase( L"center", text ) )
    {
        align = AUITextHorzAlign::kCenter;
        hasValue = true;
    }
    else if (AUIStringUtil::IsEqualIgnoreCase( L"right", text ) )
    {
        align = AUITextHorzAlign::kRight;
        hasValue = true;
    }

    return hasValue;
}

bool AUIStyleSheetUtil::ToTextVertAlignValue( const std::wstring& text, AUITextVertAlign& align )
{
    if ( text.empty() )
        return false;

    bool hasValue = false;
    if (AUIStringUtil::IsEqualIgnoreCase( L"top", text ) )
    {
        align = AUITextVertAlign::kTop;
        hasValue = true;
    }
    else if (AUIStringUtil::IsEqualIgnoreCase( L"center", text ) )
    {
        align = AUITextVertAlign::kCenter;
        hasValue = true;
    }
    else if (AUIStringUtil::IsEqualIgnoreCase( L"bottom", text ) )
    {
        align = AUITextVertAlign::kBottom;
        hasValue = true;
    }

    return hasValue;
}

bool AUIStyleSheetUtil::ToTextHorzAlignText( const AUITextHorzAlign& align, std::wstring& text )
{
    switch ( align )
    {
    case AUITextHorzAlign::kRight:
        text = L"right";
        break;
    case AUITextHorzAlign::kCenter:
        text = L"center";
        break;
    case AUITextHorzAlign::kLeft:
    default:
        text = L"left";
        break;
    }
    return true;
}

bool AUIStyleSheetUtil::ToTextVertAlignText( const AUITextVertAlign& align, std::wstring& text )
{
    switch ( align )
    {
    case AUITextVertAlign::kTop:
        text = L"top";
        break;
    case AUITextVertAlign::kBottom:
        text = L"bottom";
        break;
    case AUITextVertAlign::kCenter:
    default:
        text = L"center";
        break;
    }
    return true;

    return true;
}

bool AUIStyleSheetUtil::ToFontSizeValue( const std::wstring& text, SkScalar val )
{
    if ( text.empty() )
        return false;

    static const std::wregex re( L"^[-+]?[0-9]*\\.?[0-9]+([?[eE][-+]?[0-9]+|[.|eE])?" );
    std::wsmatch m;
    std::regex_search( text, m, re );

    if ( m.size() == 0 )
    {
        val = SkScalar( 0 );
        return false;
    }

    std::wsmatch mscale;
    std::regex_search( text, mscale, std::wregex( L"px$" ) );
    SkScalar weight = 1.0f;
    if ( mscale.size() > 0 )
    {
        if ( L"px" == mscale[0] )
            weight = 1.0f;
    }

    try
    {
        if constexpr ( std::is_same< float, SkScalar >::value )
        {
            val = static_cast< SkScalar >( std::stof( m[0] ) * weight );
        }
        else if constexpr ( std::is_same< double, SkScalar >::value )
        {
            val = static_cast< SkScalar >( std::stod( m[0] ) * weight );
        }
        else
        {
            val = static_cast< SkScalar >( std::stod( text ) ) * weight;
        }
    }
    catch ( std::exception& )
    {
        val = SkScalar( 0 );
        return false;
    }
    return true;
}

bool AUIStyleSheetUtil::ToFontSizeText( const SkScalar& val, std::wstring& text )
{
    text = std::to_wstring( val ) + L"pt";
    return true;
}

bool AUIStyleSheetUtil::ToFontFamilyValue( const std::wstring& text, std::vector< std::wstring >& arrFontFamily )
{
    if ( text.empty() )
        return false;

    arrFontFamily.clear();

    std::vector< std::wstring > arrParams;
    const wchar_t Comma[] = L",";

    std::wstring tmpParams = text;
    while ( tmpParams.size() > 0 )
    {
        const auto foundStart = tmpParams.find_first_not_of( Comma );
        if ( std::wstring::npos == foundStart )
            break;
        const auto foundEnd = tmpParams.find_first_of( Comma, foundStart + 1 );
        if ( std::wstring::npos == foundEnd )
        {
            arrParams.emplace_back( tmpParams.substr( foundStart ) );
            break;
        }
        arrParams.emplace_back( tmpParams.substr( foundStart, foundEnd - foundStart ) );
        tmpParams = tmpParams.substr( foundEnd );
    }

    if ( arrParams.size() == 0 )
        return false;

    for ( auto& p : arrParams )
    {
        std::wstring fontname;
        fontname.resize( p.size() );
        std::transform( p.begin(), p.end(), fontname.begin(), []( const wchar_t ch )->wchar_t {
            if ( ch == L'\'' || ch == L'\"' )
                return L' ';
            return ch;
        } );
        arrFontFamily.emplace_back( fontname );
    }

    return true;
}

bool AUIStyleSheetUtil::ToFontFamilyText( const std::vector< std::wstring >& arrFontFamily, std::wstring& text )
{
    text.clear();
    if ( arrFontFamily.size() == 0 )
        return false;

    const wchar_t WhiteSpaces[] = L"\r\n\t\v\f ";
    for ( auto idx = 0 ; idx < arrFontFamily.size() ; idx++ )
    {
        const auto f = arrFontFamily[idx];
        if ( std::wstring::npos != f.find( WhiteSpaces ) )
        {
            text += L'\"' + f + L'\"';
        }
        else
        {
            text += f;
        }
        if ( idx + 1 != arrFontFamily.size() )
            text += L", ";
    }
    return true;
}

bool AUIStyleSheetUtil::ToFontStyleValue( const std::wstring& text, SkFontStyle& style )
{
    if ( text.empty() )
        return false;

    if (AUIStringUtil::IsEqualIgnoreCase(L"normal", text))
        style = SkFontStyle::Normal();
    else if (AUIStringUtil::IsEqualIgnoreCase(L"bold", text))
        style = SkFontStyle::Bold();
    else if (AUIStringUtil::IsEqualIgnoreCase(L"italic", text))
        style = SkFontStyle::Italic();
    else if (AUIStringUtil::IsEqualIgnoreCase(L"bold-italic", text))
        style = SkFontStyle::BoldItalic();
    else
        return false;

    return true;
}

bool AUIStyleSheetUtil::ToFontStyleText( const SkFontStyle& style, std::wstring& text )
{
    if (SkFontStyle::Normal() == style)
    {
        text = L"normal";
    }
    else if (SkFontStyle::Bold() == style)
    {
        text = L"bold";
    }
    else if (SkFontStyle::Italic() == style)
    {
        text = L"italic";
    }
    else if (SkFontStyle::BoldItalic() == style)
    {
        text = L"bold-italic";
    }
    else
    {
        return false;
    }

    return true;
}

bool AUIStyleSheetUtil::ToOpacityValue( const std::wstring& text, SkScalar& opacity )
{
    bool ret = true;
    try
    {
        std::wstring::size_type sz;
        opacity = std::stof( text, &sz );
    }
    catch ( std::invalid_argument& )
    {
        opacity = 1.0f;
        ret = false;
    }
    opacity = std::clamp( opacity, 0.0f, 1.0f );
    return ret;
}

bool AUIStyleSheetUtil::ToOpacityText( const SkScalar opacity, std::wstring& text )
{
    text = std::to_wstring( opacity );
    return true;
}

bool AUIStyleSheetUtil::ToURIValue(const std::wstring& text, std::wstring& url)
{
	url= text;
	auto pos = url.find(L"\"");
	if( pos == std::wstring::npos)
		return false;
	url.replace(pos,1,L"");
	pos = url.rfind(L"\"");
	if( pos == std::wstring::npos)
		return false;
	url.replace(pos,1,L"");
	return true;
}
