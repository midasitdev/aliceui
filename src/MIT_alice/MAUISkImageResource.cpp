#include "pch.h"
#include "MAUISkImageResource.h"
#include "../MIT_lib/MResourceLoader.h"

using namespace mit::alice;

struct _ResourceInstantiator
{
    _ResourceInstantiator() {
        AUIResourceManager::Instance().SetupAssetResourceLoader(std::make_unique<MAUIResourceLoader>());
    }
};
static _ResourceInstantiator _ResourceInstantiate;

class MAUISkImageVisitor final : public mit::lib::MResourceLoader::Visitor
{
public:
    MAUISkImageVisitor(sk_sp<SkImage>* pImage) : m_pImage(pImage) {}
    ~MAUISkImageVisitor() override = default;
private:
    sk_sp<SkImage>* m_pImage = nullptr;
public:
    void OnReceiveData(const void* pData, const size_t size) override
    {
        if (m_pImage)
        {
            auto pImageData = SkData::MakeWithoutCopy(pData, size);
            *m_pImage = SkImage::MakeFromEncoded(pImageData);
        }
    }
};

sk_sp<SkImage> MAUIResourceLoader::LoadImage(const std::wstring& path)
{
    sk_sp<SkImage> pImage;
    MAUISkImageVisitor visitor(&pImage);
    mit::lib::MResourceLoader::Instance().LoadByVisitor(&visitor, path);
    if (pImage)
        return pImage->makeRasterImage();   // Make sure it is raster
    else
        return {};
}

std::wstring MAUIResourceLoader::LoadText(const std::wstring& path)
{
    std::wstring text;
    if (mit::lib::MResourceLoader::Instance().LoadText(text, path))
        return text;
    return {};
}
