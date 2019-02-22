#include "pch.h"
#include "AUIStringConvert.h"

std::string AUIStringConvert::ACPToUTF8(const char* str, size_t len)
{
    return AUIStringConvert::WCSToUTF8(AUIStringConvert::ACPToWCS(str, len));
}

std::string AUIStringConvert::ACPToUTF8(const std::string& str)
{
    return AUIStringConvert::ACPToUTF8(str.c_str(), str.size());
}

std::wstring AUIStringConvert::ACPToWCS(const char* str, size_t len)
{
#if defined(_WIN32)
    const UINT codePage = CP_THREAD_ACP;
    const DWORD flag = 0;
    const auto bufSize = ::MultiByteToWideChar(codePage, flag, str, static_cast<int>(len), nullptr, 0);

    auto strSize = bufSize;
    if (len < 0)
        strSize = bufSize - 1;
    if (bufSize <= 0)
        return {};

    std::wstring out;
    out.resize(bufSize);
    if (0 == ::MultiByteToWideChar(codePage, flag, str, static_cast<int>(len), out.data(), bufSize))
        return {};
    out.resize(strSize);
    return out;
#else
    // TODO : remove deprecated codecvt
    std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter;
    return converter.from_bytes(str);
#endif
}

std::wstring AUIStringConvert::ACPToWCS(const std::string& str)
{
    return AUIStringConvert::ACPToWCS(str.c_str(), str.size());
}

std::string AUIStringConvert::WCSToACP(const wchar_t* str, size_t len)
{
#if defined(_WIN32)
    const UINT codePage = CP_THREAD_ACP;
    const DWORD flag = 0;
    const auto bufSize = ::WideCharToMultiByte(codePage, flag, str, static_cast<int>(len), NULL, 0, nullptr, nullptr);
    auto strSize = bufSize;

    if (len < 0)
        strSize = bufSize - 1;
    if (bufSize <= 0)
        return {};

    std::string out;
    out.resize(bufSize);
    if (0 == ::WideCharToMultiByte(codePage, flag, str, static_cast<int>(len), out.data(), bufSize, nullptr, nullptr))
        return {};
    out.resize(strSize);
    return out;
#else
    // TODO : remove deprecated codecvt
    std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter;
    return converter.to_bytes(str);
#endif
}

std::string AUIStringConvert::WCSToACP(const std::wstring& str)
{
    return AUIStringConvert::WCSToACP(str.c_str(), str.size());
}

std::string AUIStringConvert::WCSToUTF8(const wchar_t* str, size_t len)
{
#if defined(_WIN32)
    const UINT codePage = CP_UTF8;
    const DWORD flag = 0;
    const auto bufSize = ::WideCharToMultiByte(codePage, flag, str, static_cast<int>(len), NULL, 0, nullptr, nullptr);
    auto strSize = bufSize;

    if (len < 0)
        strSize = bufSize - 1;
    if (bufSize <= 0)
        return {};

    std::string out;
    out.resize(bufSize);
    if (0 == ::WideCharToMultiByte(codePage, flag, str, static_cast<int>(len), out.data(), bufSize, nullptr, nullptr))
        return {};
    out.resize(strSize);
    return out;
#else
    // TODO : remove deprecated codecvt
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(str);
#endif
}

std::string AUIStringConvert::WCSToUTF8(const std::wstring& str)
{
    return AUIStringConvert::WCSToUTF8(str.c_str(), str.size());
}

std::wstring AUIStringConvert::UTF8ToWCS(const char* str, size_t len)
{
#if defined(_WIN32)
    const UINT codePage = CP_UTF8;
    const DWORD flag = 0;
    const auto bufSize = ::MultiByteToWideChar(codePage, flag, str, static_cast<int>(len), nullptr, 0);
    auto strSize = bufSize;

    if (len < 0)
        strSize = bufSize - 1;
    if (bufSize <= 0)
        return {};

    std::wstring out;
    out.resize(bufSize);
    if (0 == ::MultiByteToWideChar(codePage, flag, str, static_cast<int>(len), out.data(), bufSize))
        return {};
    out.resize(strSize);
    return out;
#else
    // TODO : remove deprecated codecvt
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
#endif
}

std::wstring AUIStringConvert::UTF8ToWCS(const std::string& str)
{
    return AUIStringConvert::UTF8ToWCS(str.c_str(), str.size());
}
