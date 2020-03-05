#include "pch.h"
#include "AUIResourceManager.h"
#include "AUIStringConvert.h"

sk_sp<SkImage> AUIFileResourceLoader::LoadImage(const std::wstring& path)
{
#if defined(_WIN32)
#   pragma warning(push)
#   pragma warning(disable: 4996)
    std::unique_ptr<FILE, decltype(&fclose)> pFile(_wfopen(path.c_str(), L"rb"), &fclose);
#   pragma warning(pop)
    if (pFile)
    {
        std::vector<uint8_t> buffer;
        fseek(pFile.get(), 0, SEEK_END);
        const auto fileSize = ftell(pFile.get());
        fseek(pFile.get(), 0, SEEK_SET);
        buffer.resize(fileSize, 0);
        fread(buffer.data(), sizeof(uint8_t), fileSize, pFile.get());
        auto pData = SkData::MakeWithoutCopy(buffer.data(), buffer.size());
        auto pImage = SkImage::MakeFromEncoded(pData);
        if (pImage)
            pImage = pImage->makeRasterImage(); // Make sure it is raster
        return pImage;
    }
#else
    auto utf8Path = AUIStringConvert::WCSToUTF8(path);
    std::unique_ptr<FILE, decltype(&fclose)> pFile(fopen(utf8Path.c_str(), "rb"), &fclose);
    if (pFile)
    {
        std::vector<uint8_t> buffer;
        fseek(pFile.get(), 0, SEEK_END);
        const auto fileSize = ftell(pFile.get());
        fseek(pFile.get(), 0, SEEK_SET);
        buffer.resize(fileSize, 0);
        fread(buffer.data(), sizeof(uint8_t), fileSize, pFile.get());
        auto pData = SkData::MakeWithoutCopy(buffer.data(), buffer.size());
        auto pImage = SkImage::MakeFromEncoded(pData);
        if (pImage)
            pImage = pImage->makeRasterImage(); // Make sure it is raster
        return pImage;
    }
#endif
    return {};
}

std::wstring AUIFileResourceLoader::LoadText(const std::wstring& path)
{
#if defined(_WIN32)
#   pragma warning(push)
#   pragma warning(disable: 4996)
	// from 오르비스
	// 숫자 18이 저장될 때 1과 8의 아스키 코드값이 저장됨(49, 56)
	// text mode   -> 모든 데이터를 문자 형태로 기록, 읽을 때 if 18 -> "18" (문자열)
	// binary mode -> 메모리에 있는 내용 그대로 기록, 읽을 때 if 18 -> 49 * 256(2번째 바이트이므로) + 56 = 12600
	// text mode로 명시적으로 설정, default가 text mode인데.. 왜 binary로.. 될까.. 후..
    std::unique_ptr<FILE, decltype(&fclose)> pFile(_wfopen(path.c_str(), L"rt"), &fclose);
#   pragma warning(pop)
    if (pFile)
    {
        std::wstringstream wss;
        std::array<wchar_t, 512> buffer;
		while (!feof(pFile.get())) {
			if (fgetws(buffer.data(), static_cast<int>(buffer.size() - 1), pFile.get())) {
				wss << buffer.data();
				buffer.at(0) = L'\0';
			}
		}
        return wss.str();
    }
#else
    auto utf8Path = AUIStringConvert::WCSToUTF8(path);
    std::unique_ptr<FILE, decltype(&fclose)> pFile(fopen(utf8Path.c_str(), "rt"), &fclose);
    if (pFile)
    {
        std::wstringstream wss;
		std::array<wchar_t, 512> buffer;
		while (!feof(pFile.get())) {
			if (fgetws(buffer.data(), static_cast<int>(buffer.size() - 1), pFile.get())) {
				wss << buffer.data();
				buffer.at(0) = L'\0';
			}
		}
        return wss.str();
    }
#endif
    return {};
}

AUIResourceManager::AUIResourceManager()
    : m_pFileResoureLoader(std::make_unique<AUIFileResourceLoader>())
{

}

AUIResourceManager& AUIResourceManager::Instance()
{
    static AUIResourceManager sInstance;
    return sInstance;
}

sk_sp<SkImage> AUIResourceManager::LoadImage(const std::wstring& path)
{
    if (auto pImage = LoadImageFromAsset(path))
        return pImage;
    if (auto pImage = LoadImageFromFile(path))
        return pImage;
    return {};
}

sk_sp<SkImage> AUIResourceManager::LoadImageFromFile(const std::wstring& path)
{
    if (m_pFileResoureLoader)
        return m_pFileResoureLoader->LoadImage(path);
    return {};
}

sk_sp<SkImage> AUIResourceManager::LoadImageFromAsset(const std::wstring& path)
{
    if (m_pAssetResoureLoader)
        return m_pAssetResoureLoader->LoadImage(path);
    return {};
}

void AUIResourceManager::SetupFileResourceLoader(std::unique_ptr<AUIResourceLoader> pLoader)
{
    m_pFileResoureLoader = std::move(pLoader);
}

void AUIResourceManager::SetupAssetResourceLoader(std::unique_ptr<AUIResourceLoader> pLoader)
{
    m_pAssetResoureLoader = std::move(pLoader);
}

bool AUIResourceManager::HasFileResourceLoader() const
{
    return nullptr != m_pFileResoureLoader;
}

bool AUIResourceManager::HasAssetResourceLoader() const
{
    return nullptr != m_pAssetResoureLoader;
}

std::wstring AUIResourceManager::LoadText(const std::wstring& path)
{
    std::wstring text;
    text = LoadTextFromAsset(path);
    if (!text.empty())
        return text;
    text = LoadTextFromFile(path);
    if (!text.empty())
        return text;
    return {};
}

std::wstring AUIResourceManager::LoadTextFromFile(const std::wstring& path)
{
    if (m_pFileResoureLoader)
        return m_pFileResoureLoader->LoadText(path);
    return {};
}

std::wstring AUIResourceManager::LoadTextFromAsset(const std::wstring& path)
{
    if (m_pAssetResoureLoader)
        return m_pAssetResoureLoader->LoadText(path);
    return {};
}
