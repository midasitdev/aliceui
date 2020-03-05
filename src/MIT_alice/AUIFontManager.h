#pragma once

#include "AUICommonDef.h"
#include "AUISkiaConfig.h"
#include "AUITypeface.h"
#include "AUIApplication.h"
#include "AUIStringUtil.h"

class FontStyleSet final : public SkFontStyleSet
{
public:
    FontStyleSet(const char* familyName) : fFamilyName(familyName) {}
    struct TypefaceEntry
    {
        TypefaceEntry(sk_sp<SkTypeface> typeface, SkFontStyle style, const char* styleName)
            : fTypeface(std::move(typeface)), fStyle(style), fStyleName(styleName) {}
        sk_sp<SkTypeface> fTypeface;
        SkFontStyle       fStyle;
        const char*       fStyleName;
    };

    int count() override { return (int)fTypefaces.size(); }

    void getStyle(int index, SkFontStyle* style, SkString* name) override
    {
        if (style) {
            *style = fTypefaces[index].fStyle;
        }
        if (name) {
            *name = fTypefaces[index].fStyleName;
        }
    }

    SkTypeface* createTypeface(int index) override {
        return SkRef(fTypefaces[index].fTypeface.get());
    }

    SkTypeface* matchStyle(const SkFontStyle& pattern) override {
        return this->matchStyleCSS3(pattern);
    }

    SkString getFamilyName() { return fFamilyName; }

    std::vector<TypefaceEntry> fTypefaces;
    SkString                   fFamilyName;
};

class AUIFontManager final : public SkFontMgr
{
public:
    AUIFontManager();

    int onCountFamilies() const override { return (int)fFamilies.size(); }

    void add(sk_sp<SkTypeface> zz)
    {
        SkString zzz;
        zz->getFamilyName(&zzz);
        fFamilies.emplace_back(sk_make_sp<FontStyleSet>(zzz.c_str()));
            fFamilies.back()->fTypefaces.emplace_back(
                std::move(zz),
                zz->fontStyle(),
                "Normal");
    }
    void onGetFamilyName(int index, SkString* familyName) const override {
        *familyName = fFamilies[index]->getFamilyName();
    }

    SkFontStyleSet* onCreateStyleSet(int index) const override {
        sk_sp<SkFontStyleSet> ref = fFamilies[index];
        return ref.release();
    }

    SkFontStyleSet* onMatchFamily(const char familyName[]) const override {
        if (familyName) {
            if (strstr(familyName, "ono")) {
                return this->createStyleSet(0);
            }
            if (strstr(familyName, "ans")) {
                return this->createStyleSet(1);
            }
            if (strstr(familyName, "erif")) {
                return this->createStyleSet(2);
            }
        }
        return nullptr;
    }

    SkTypeface* onMatchFamilyStyle(const char familyName[], const SkFontStyle& style) const override
    {
        sk_sp<SkFontStyleSet> styleSet(this->matchFamily(familyName));
        return styleSet->matchStyle(style);
    }

    SkTypeface* onMatchFamilyStyleCharacter(const char familyName[],
        const SkFontStyle& style,
        const char*        bcp47[],
        int                bcp47Count,
        SkUnichar          character) const override
    {
        (void)bcp47;
        (void)bcp47Count;
        (void)character;
        return this->matchFamilyStyle(familyName, style);
    }

    SkTypeface* onMatchFaceStyle(const SkTypeface* tf, const SkFontStyle& style) const override
    {
        SkString familyName;
        tf->getFamilyName(&familyName);
        return this->matchFamilyStyle(familyName.c_str(), style);
    }

    sk_sp<SkTypeface> onMakeFromData(sk_sp<SkData>, int ttcIndex) const override { return nullptr; }
    sk_sp<SkTypeface> onMakeFromStreamIndex(std::unique_ptr<SkStreamAsset>,
        int ttcIndex) const override {
        return nullptr;
    }
    sk_sp<SkTypeface> onMakeFromFile(const char path[], int ttcIndex) const override {
        return nullptr;
    }

    sk_sp<SkTypeface> onLegacyMakeTypeface(const char  familyName[],
        SkFontStyle style) const override {
        if (familyName == nullptr) {
            return sk_sp<SkTypeface>(fDefaultFamily->matchStyle(style));
        }
        sk_sp<SkTypeface> typeface = sk_sp<SkTypeface>(this->matchFamilyStyle(familyName, style));
        if (!typeface) {
            typeface = fDefaultTypeface;
        }
        return typeface;
    }

private:
    std::vector<sk_sp<FontStyleSet>> fFamilies;
    sk_sp<FontStyleSet>              fDefaultFamily;
    sk_sp<SkTypeface>                fDefaultTypeface;
};
