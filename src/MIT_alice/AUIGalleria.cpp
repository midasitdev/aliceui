#include "pch.h"
#include "AUIGalleria.h"
#include "AUIGalleriaCache.h"
#include "AUIGalleriaImgProc.h"
#include "AUIAsyncTask.h"
#include "AUIImageWidget.h"
#include "AUIResourceManager.h"

namespace
{
    const auto sCacheInstance = std::make_shared<AUIGalleriaCache>();
    const auto sNullImage = SkImage::MakeFromBitmap(SkBitmap());
}

AUIGalleria::AUIGalleria()
    : m_pCache( sCacheInstance )
{

}

AUIGalleria::~AUIGalleria()
{

}

AUIGalleria AUIGalleria::Make()
{
    AUIGalleria galleria; return galleria;
}

AUIGalleria AUIGalleria::Make(const AUIGalleriaParam& request)
{
    AUIGalleria galleria; galleria.SetParam(request); return galleria;
}

void AUIGalleria::Register( const std::wstring& key, const sk_sp<SkImage>& pBitmap )
{
    const auto baseKey = ToBaseKey( key );
    m_pCache->ClearKeyPrefix( baseKey );
    m_pCache->Set( baseKey, pBitmap );
}

sk_sp<SkImage> AUIGalleria::Get( const std::wstring& key ) const
{
    const auto finalParam = GetFinalParam( key );
    const auto paramKey = AUIGalleria::ToParamKey( finalParam, key );
    if ( m_pCache->Has( paramKey ) )
    {
        return m_pCache->Get( paramKey );
    }

    if ( this->Has( finalParam.GetFallbackPath() ) )
    {
        return this->Get( finalParam.GetFallbackPath() );
    }

    if (finalParam.IsNoOp())
    {
        const auto baseKey = AUIGalleria::ToBaseKey(key);
        auto pImage = m_pCache->Get(baseKey);
        return pImage;
    }
    else
    {
        const auto baseKey = AUIGalleria::ToBaseKey(key);
        auto pImage = m_pCache->GetCopy(baseKey);
        if (pImage)
        {
            if (auto pNewImage = AppyImageProcessing(finalParam, pImage))
            {
                m_pCache->Set(paramKey, pNewImage);
                return pNewImage;
            }
            // Fallback
        }
        return pImage;
    }
}

bool AUIGalleria::Has( const std::wstring& key ) const
{
    const auto paramKey = AUIGalleria::ToParamKey( m_Param, key );
    return m_pCache->Has( paramKey );
}

sk_sp<SkImage> AUIGalleria::GetFromResource( const std::wstring& path ) const
{
    const auto finalParam = GetFinalParam( path );
    const auto paramKey = AUIGalleria::ToParamKey( finalParam, path );
    if ( m_pCache->Has( paramKey ) )
    {
        return m_pCache->Get( paramKey );
    }

    if (finalParam.IsNoOp())
    {
        const auto baseKey = AUIGalleria::ToBaseKey(path);
        auto pImage = m_pCache->GetCopy(baseKey);
        if (nullptr == pImage)
        {
            auto pTmpImage = AUIResourceManager::Instance().LoadImageFromAsset(path);
            if (!pTmpImage)
            {
                const auto fallbackpath = finalParam.GetFallbackPath();
                if (false == fallbackpath.empty())
                    pTmpImage = AUIResourceManager::Instance().LoadImage(fallbackpath);
            }
            if (pTmpImage)
            {
                m_pCache->Set(baseKey, pTmpImage);
            }
            pImage = m_pCache->Get(baseKey);
        }
        return pImage;
    }
    else
    {
        const auto baseKey = AUIGalleria::ToBaseKey(path);
        auto pImage = m_pCache->GetCopy(baseKey);
        if (nullptr == pImage)
        {
            auto pTmpImage = AUIResourceManager::Instance().LoadImageFromAsset(path);
            if (!pTmpImage)
            {
                const auto fallbackpath = finalParam.GetFallbackPath();
                if (false == fallbackpath.empty())
                    pTmpImage = AUIResourceManager::Instance().LoadImage(fallbackpath);
            }
            if (pTmpImage)
            {
                m_pCache->Set(baseKey, pTmpImage);
            }
            pImage = m_pCache->GetCopy(baseKey);
        }
        if (pImage)
        {
            AppyImageProcessing(finalParam, pImage);
            m_pCache->Set(paramKey, pImage);
        }
        return pImage;
    }
}

sk_sp<SkImage> AUIGalleria::GetFromFile( const std::wstring& path ) const
{
    const auto finalParam = GetFinalParam( path );
    const auto paramKey = AUIGalleria::ToParamKey( finalParam, path );
    if ( m_pCache->Has( paramKey ) )
    {
        return m_pCache->Get( paramKey );
    }

    if (finalParam.IsNoOp())
    {
        const auto baseKey = AUIGalleria::ToBaseKey(path);
        auto pImage = m_pCache->Get(baseKey);
        if (nullptr == pImage)
        {
            pImage = AUIResourceManager::Instance().LoadImageFromFile(path);
            if (!pImage)
            {
                const auto fallbackpath = finalParam.GetFallbackPath();
                if (false == fallbackpath.empty())
                    pImage = AUIResourceManager::Instance().LoadImage(fallbackpath);
            }
            if (pImage)
            {
                m_pCache->Set(baseKey, pImage);
            }
            pImage = m_pCache->Get(baseKey);
        }
        return pImage;
    }
    else
    {
        const auto baseKey = AUIGalleria::ToBaseKey(path);
        auto pImage = m_pCache->GetCopy(baseKey);
        if (nullptr == pImage)
        {
            pImage = AUIResourceManager::Instance().LoadImageFromFile(path);
            if (!pImage)
            {
                const auto fallbackpath = finalParam.GetFallbackPath();
                if (false == fallbackpath.empty())
                    pImage = AUIResourceManager::Instance().LoadImage(fallbackpath);
            }
            if (pImage)
            {
                m_pCache->Set(baseKey, pImage);
            }
            pImage = m_pCache->GetCopy(baseKey);
        }
        if (pImage)
        {
            AppyImageProcessing(finalParam, pImage);
            m_pCache->Set(paramKey, pImage);
        }
        return pImage;
    }
}

void AUIGalleria::ClearCacheByKey( const std::wstring& key )
{
    m_pCache->ClearKeyPrefix(key);
}

std::wstring AUIGalleria::ToBaseKey( const std::wstring& key )
{
    return AUIGalleria::ToParamKey( AUIGalleriaParam(), key );
}

std::wstring AUIGalleria::ToParamKey( const AUIGalleriaParam& param, const std::wstring& key )
{
    std::wstringstream ss;
    ss << std::setprecision( 3 ) << std::fixed;

    ss << key;
    if ( param.IsCenterCrop() )
    {
        ss << "-cc ";
    }
    else if ( param.IsCenterInside() )
    {
        ss << "-ci ";
    }

    if ( 0 <= param.GetTargetWidth() && 0 <= param.GetTargetHeight() )
    {
        ss << "-w" << param.GetTargetWidth() << " ";
        ss << "-h" << param.GetTargetHeight() << " ";
    }

    if ( 0.0f != param.GetRotateDegree() )
    {
        ss << "-r" << param.GetRotateDegree() << " ";
        if ( param.GetRotatePivotX() != 0.0f )
        {
            ss << "-rpx" << param.GetRotatePivotX() << " ";
        }
        if ( param.GetRotatePivotY() != 0.0f )
        {
            ss << "-rpy" << param.GetRotatePivotY() << " ";
        }
    }
    return ss.str();
}

void AUIGalleria::SetParam( const AUIGalleriaParam& param )
{
    m_Param = param;
}

sk_sp<SkImage> AUIGalleria::AppyImageProcessing( const AUIGalleriaParam& param, const sk_sp<SkImage>& pImage )
{
    // Generate image
    AUIGalleriaImgProc imgproc( pImage );

    // Rotate
    if ( param.GetRotateDegree() != 0.0f )
    {
        return imgproc.Rotate( param.GetRotateDegree(), param.GetRotatePivotX(), param.GetRotatePivotY() );
    }

    if ( 0 < param.GetTargetWidth() && 0 < param.GetTargetHeight() )
    {
        if ( param.IsCenterInside() )
        {
            return imgproc.ResizeCenterInside( param.GetTargetWidth(), param.GetTargetHeight() );
        }
        else if ( param.IsCenterCrop() )
        {
            return imgproc.ResizeCenterCrop( param.GetTargetWidth(), param.GetTargetHeight() );
        }
        else
        {
            return imgproc.Resize( param.GetTargetWidth(), param.GetTargetHeight() );
        }
    }

    return pImage;
}

AUIGalleriaParam AUIGalleria::GetFinalParam( const std::wstring key ) const
{
    // Generate final param
    auto finalParam = m_Param.Clone();
    if ( m_Param.IsOnlyScaleDown() )
    {
        if ( auto pOrg = m_pCache->Get( AUIGalleria::ToBaseKey( key ) ) )
        {
            if (0 <= m_Param.GetTargetWidth() && 0 <= m_Param.GetTargetHeight())
            {
                if (m_Param.GetTargetWidth() >= pOrg->width() || m_Param.GetTargetHeight() >= pOrg->height())
                {
                    // No resize
                    finalParam.ClearResize();
                }
            }
        }
    }
    return finalParam;
}

std::wstring AUIGalleria::GetCacheStatistics() const
{
    return m_pCache->GetStatistics();
}
