#pragma once


#include "MITAliceDef.h"
#include "AUIResourceManager.h"

namespace mit
{
    namespace alice
    {
        class MITALICE_API MAUIResourceLoader : public AUIResourceLoader
        {
        public:
            MAUIResourceLoader() = default;
            ~MAUIResourceLoader() override = default;

            sk_sp<SkImage> LoadImage(const std::wstring& path) override;
            std::wstring LoadText(const std::wstring& path) override;
        };
    }
}
