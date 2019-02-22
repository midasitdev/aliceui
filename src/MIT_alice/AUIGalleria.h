#pragma once

#include "AUICommonDef.h"

#include "AUIGalleriaParam.h"

class AUIGalleriaCache;

class ALICEUI_API AUIGalleria final
{
public:
    AUIGalleria();
    ~AUIGalleria();
    static AUIGalleria Make();
    static AUIGalleria Make(const AUIGalleriaParam& request);


    //////////////////////////////////////////////////////////////////////////
    // Get Bitmap
public:
    bool Has(const std::wstring& key) const;
    sk_sp<SkImage> GetFromFile(const std::wstring& path) const;
    sk_sp<SkImage> GetFromResource(const std::wstring& path) const;
    sk_sp<SkImage> Get(const std::wstring& key) const;

    //////////////////////////////////////////////////////////////////////////
    // Clear cache
public:
    void ClearCacheByKey(const std::wstring& key);

    //////////////////////////////////////////////////////////////////////////
    // Register
public:
    void Register(const std::wstring& key, const sk_sp<SkImage>& pBitmap);


    //////////////////////////////////////////////////////////////////////////
    // Param
public:
    void SetParam(const AUIGalleriaParam& param);
private:
    AUIGalleriaParam GetFinalParam(const std::wstring key) const;
    AUIGalleriaParam m_Param;

    //////////////////////////////////////////////////////////////////////////
    // Image
private:
    static sk_sp<SkImage> AppyImageProcessing(const AUIGalleriaParam& param, const sk_sp<SkImage>& pImage);

    //////////////////////////////////////////////////////////////////////////
    // Key
public:
    static std::wstring ToBaseKey(const std::wstring& key);
    static std::wstring ToParamKey(const AUIGalleriaParam& param, const std::wstring& key);

    //////////////////////////////////////////////////////////////////////////
    // Cache
private:
    const std::shared_ptr<AUIGalleriaCache> m_pCache;


    //////////////////////////////////////////////////////////////////////////
    // Statistics
public:
    std::wstring GetCacheStatistics() const;
};
