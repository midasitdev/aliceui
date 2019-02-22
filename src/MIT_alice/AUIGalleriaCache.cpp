#include "pch.h"
#include "AUIGalleriaCache.h"
#include "AUIGalleria.h"

AUIGalleriaCache::AUIGalleriaCache()
{

}

AUIGalleriaCache::~AUIGalleriaCache()
{

}

sk_sp<SkImage> AUIGalleriaCache::Get( const std::wstring& key ) const
{
    std::lock_guard< std::mutex > guard( m_mtxKey2Image );
    const auto found = m_mapKey2Image.find( key );
    if ( found == m_mapKey2Image.end() )
    {
        return nullptr;
    }
    return found->second;
}

sk_sp<SkImage> AUIGalleriaCache::GetCopy( const std::wstring& key ) const
{
    auto pOriginal = this->Get( key );
    if ( nullptr == pOriginal )
        return nullptr;
    SkPixmap pixmap;
    if (!pOriginal->peekPixels(&pixmap))
        return nullptr;
    return SkImage::MakeRasterCopy(pixmap);
}

void AUIGalleriaCache::Set( const std::wstring& key, const sk_sp<SkImage>& pImage )
{
    std::lock_guard< std::mutex > guard( m_mtxKey2Image );
    m_mapKey2Image[key] = pImage->makeRasterImage();
}

void AUIGalleriaCache::ClearKeyPrefix( const std::wstring& keyPrefix )
{
    std::vector< std::wstring > arrDelKeys;
    std::lock_guard< std::mutex > guard( m_mtxKey2Image );
    for ( auto key2image : m_mapKey2Image )
    {
        const auto found = key2image.first.find( keyPrefix );
        if ( 0 == found )
        {
            arrDelKeys.emplace_back( key2image.first );
        }
    }

    for ( auto key : arrDelKeys )
    {
        const auto found = m_mapKey2Image.find( key );
        if ( m_mapKey2Image.end() != found )
            m_mapKey2Image.erase( found );
    }
}

void AUIGalleriaCache::ClearAll()
{
    std::lock_guard< std::mutex > guard( m_mtxKey2Image );
    m_mapKey2Image.clear();
}

bool AUIGalleriaCache::Has( const std::wstring& key ) const
{
    std::lock_guard< std::mutex > guard( m_mtxKey2Image );
    return m_mapKey2Image.end() != m_mapKey2Image.find( key );
}

std::wstring AUIGalleriaCache::GetStatistics() const
{
    std::wstringstream wss;
    wss << L"---------------Galleria cache data information--------------\n";
    wss << L" - Cache object size : " << sizeof(AUIGalleriaCache) << L" bytes\n";
    wss << L" - Record count : " << m_mapKey2Image.size()  << L'\n';
    size_t imageDataSize = 0;
    for (const auto& itrData : m_mapKey2Image)
    {
        AUIAssert(itrData.second);
        SkPixmap pixmap;
        if (!itrData.second->peekPixels(&pixmap))
            continue;
        imageDataSize += pixmap.height() * pixmap.rowBytes();
    }
    wss << L" - Image cache data size : " << imageDataSize << L" bytes\n";
    wss << L"------------------------------------------------------------\n";
    return wss.str();
}
