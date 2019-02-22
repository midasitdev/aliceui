#pragma once

#include "AUIAPIDef.h"

#include <string>

class ALICEUI_API AUIStringConvert
{
public:
    static std::string ACPToUTF8(const char* str, size_t len = size_t(-1));
    static std::string ACPToUTF8(const std::string& str);

    static std::wstring ACPToWCS(const char* str, size_t len = size_t(-1));
    static std::wstring ACPToWCS(const std::string& str);

    static std::string WCSToACP(const wchar_t* str, size_t len = size_t(-1));
    static std::string WCSToACP(const std::wstring& str);

    static std::string WCSToUTF8(const wchar_t* str, size_t len = size_t(-1));
    static std::string WCSToUTF8(const std::wstring& str);

    static std::wstring UTF8ToWCS(const char* str, size_t len = size_t(-1));
    static std::wstring UTF8ToWCS(const std::string& str);
};
