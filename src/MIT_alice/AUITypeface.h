#pragma once

#include "AUISkiaConfig.h"

struct AUIFontData {
    const SkScalar*      fPoints;
    const unsigned char* fVerbs;
    const SkUnichar*     fCharCodes;
    const size_t         fCharCodesCount;
    const int32_t*       fWidths;
    const char*          fName;
    SkFontStyle          fStyle;
};

class AUIFont : public SkRefCnt {
public:
    AUIFont(const AUIFontData&);
    virtual ~AUIFont();
    SkGlyphID glyphForUnichar(SkUnichar charCode) const;
    void      init(const SkScalar* pts, const unsigned char* verbs);

private:
    const SkUnichar*     fCharCodes;
    const size_t         fCharCodesCount;
    const int32_t*       fWidths;
    const char*          fName;
    SkPath**             fPaths;
    friend class AUITypeface;
    typedef SkRefCnt INHERITED;
};

class AUITypeface : public SkTypeface {
public:
    AUITypeface(sk_sp<AUIFont>, const SkFontStyle& style);

protected:
    sk_sp<SkTypeface> onMakeClone(const SkFontArguments& args) const override {
        return sk_ref_sp(this);
    }

    SkScalerContext* onCreateScalerContext(const SkScalerContextEffects& effects,
        const SkDescriptor* desc) const override;
    void onFilterRec(SkScalerContextRec* rec) const override;
    friend class SkScalerContext;  // onFilterRec

    int onCharsToGlyphs(const void* chars, Encoding, SkGlyphID glyphs[], int glyphCount) const override;

    int onCountGlyphs() const override { return (int)fTestFont->fCharCodesCount; }

    int onGetUPEM() const override { return 2048; }

    void onGetFamilyName(SkString* familyName) const override;

    int onGetVariationDesignPosition(SkFontArguments::VariationPosition::Coordinate coordinates[],
        int coordinateCount) const override {
        return 0;
    }

    SkStreamAsset* onOpenStream(int* ttcIndex) const override { return nullptr; }

    void onGetFontDescriptor(SkFontDescriptor* desc, bool* isLocal) const override;

    /** Returns an iterator over the family names in the font. */
    LocalizedStrings* onCreateFamilyNameIterator() const override;

    int onGetTableTags(SkFontTableTag tags[]) const override { return 0; }

    size_t onGetTableData(SkFontTableTag tag,
        size_t         offset,
        size_t         length,
        void*          data) const override {
        return 0;
    }

private:
    sk_sp<AUIFont> fTestFont;
};
