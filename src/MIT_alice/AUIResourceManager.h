#pragma once

#include "AUIAPIDef.h"
#include "AUISkiaConfig.h"

class ALICEUI_API AUIResourceLoader
{
protected:
    AUIResourceLoader() = default;
public:
    virtual ~AUIResourceLoader() = default;

    virtual sk_sp<SkImage> LoadImage(const std::wstring& path) = 0;
    virtual std::wstring LoadText(const std::wstring& path) = 0;
};

class ALICEUI_API AUIFileResourceLoader : public AUIResourceLoader
{
public:
    AUIFileResourceLoader() = default;
    ~AUIFileResourceLoader() override = default;

    sk_sp<SkImage> LoadImage(const std::wstring& path) override;
    std::wstring LoadText(const std::wstring& path) override;
};

class ALICEUI_API AUIResourceManager final
{
private:
    AUIResourceManager();
    ~AUIResourceManager() = default;
public:
    static AUIResourceManager& Instance();

    sk_sp<SkImage> LoadImage(const std::wstring& path);  // Fallback from Asset to File
    sk_sp<SkImage> LoadImageFromFile(const std::wstring& path);
    sk_sp<SkImage> LoadImageFromAsset(const std::wstring& path);

    std::wstring LoadText(const std::wstring& path);    // Fallback from Asset to File
    std::wstring LoadTextFromFile(const std::wstring& path);
    std::wstring LoadTextFromAsset(const std::wstring& path);

    bool HasFileResourceLoader() const;
    bool HasAssetResourceLoader() const;

    void SetupFileResourceLoader(std::unique_ptr<AUIResourceLoader> pLoader);
    void SetupAssetResourceLoader(std::unique_ptr<AUIResourceLoader> pLoader);
private:
    std::unique_ptr<AUIResourceLoader> m_pFileResoureLoader;
    std::unique_ptr<AUIResourceLoader> m_pAssetResoureLoader;
};

