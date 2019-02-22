#pragma once


#include "AUIAPIDef.h"
#include "AUIBasicEnumDef.h"

#include <string>
#include <optional>
#include <memory>

class AUIDrawable;

class ALICEUI_API AUIJsonDrawableParser
{
public:
    AUIJsonDrawableParser();
    virtual ~AUIJsonDrawableParser();

public:
    std::optional<std::shared_ptr<AUIDrawable>> LoadFromPath(const std::wstring& json_path) {
        if (auto ret = LoadFromPathByFile(json_path))
            return ret;
        else if (auto ret = LoadFromPathByResource(json_path))
            return ret;
        return {};
    }
    std::optional<std::shared_ptr<AUIDrawable>> LoadFromPathByFile(const std::wstring& input_path) {
        return LoadFromPath_Private(input_path, true);
    }
    std::optional<std::shared_ptr<AUIDrawable>> LoadFromPathByResource(const std::wstring& input_path) {
        return LoadFromPath_Private(input_path, false);
    }

    struct OptParam
    {
        AUIImageStretch fDefaultImageStretch = AUIImageStretch::kFill;
    };
    void SetDefaultImageStretch(AUIImageStretch stretch);
    void SetOptParam(const OptParam& optParam);
private:
    std::optional<std::shared_ptr<AUIDrawable>> LoadFromPath_Private(const std::wstring& input_path, bool isFromFile);
    std::optional<std::shared_ptr<AUIDrawable>> LoadFromPathJson(const std::wstring& json_path, bool isFromFile);
    OptParam m_OptParam;
};
