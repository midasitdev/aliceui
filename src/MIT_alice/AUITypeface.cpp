#include "pch.h"
#include "AUITypeface.h"

AUIFont::AUIFont(const AUIFontData& fontData)
    : INHERITED()
    , fCharCodes(fontData.fCharCodes)
    , fCharCodesCount(fontData.fCharCodes ? fontData.fCharCodesCount : 0)
    , fWidths(fontData.fWidths)
    , fName(fontData.fName)
    , fPaths(nullptr) {
    init(fontData.fPoints, fontData.fVerbs);
}

AUIFont::~AUIFont() {
    for (unsigned index = 0; index < fCharCodesCount; ++index) {
        delete fPaths[index];
    }
    delete[] fPaths;
}

SkGlyphID AUIFont::glyphForUnichar(SkUnichar charCode) const {
    for (size_t index = 0; index < fCharCodesCount; ++index) {
        if (fCharCodes[index] == charCode) {
            return SkTo<SkGlyphID>(index);
        }
    }
    return 0;
}

void AUIFont::init(const SkScalar* pts, const unsigned char* verbs) {
    fPaths = new SkPath*[fCharCodesCount];
    for (unsigned index = 0; index < fCharCodesCount; ++index) {
        SkPath*      path = new SkPath;
        SkPath::Verb verb;
        while ((verb = (SkPath::Verb)*verbs++) != SkPath::kDone_Verb) {
            switch (verb) {
            case SkPath::kMove_Verb:
                path->moveTo(pts[0], pts[1]);
                pts += 2;
                break;
            case SkPath::kLine_Verb:
                path->lineTo(pts[0], pts[1]);
                pts += 2;
                break;
            case SkPath::kQuad_Verb:
                path->quadTo(pts[0], pts[1], pts[2], pts[3]);
                pts += 4;
                break;
            case SkPath::kCubic_Verb:
                path->cubicTo(pts[0], pts[1], pts[2], pts[3], pts[4], pts[5]);
                pts += 6;
                break;
            case SkPath::kClose_Verb: path->close(); break;
            default: SkDEBUGFAIL("bad verb"); return;
            }
        }
        // This should make SkPath::getBounds() queries threadsafe.
        path->updateBoundsCache();
        fPaths[index] = path;
    }
}

AUITypeface::AUITypeface(sk_sp<AUIFont> testFont, const SkFontStyle& style)
    : SkTypeface(style, false), fTestFont(std::move(testFont)) {}

void AUITypeface::onGetFamilyName(SkString* familyName) const { *familyName = fTestFont->fName; }

void AUITypeface::onGetFontDescriptor(SkFontDescriptor* desc, bool* isLocal) const
{
   /* desc->setFamilyName(fTestFont->fName);
    desc->setStyle(this->fontStyle());
    *isLocal = false;*/
}

SkTypeface::LocalizedStrings* AUITypeface::onCreateFamilyNameIterator() const
{
    //SkString familyName(fTestFont->fName);
    //SkString language("und");  // undetermined
    //return new SkOTUtils::LocalizedStrings_SingleName(familyName, language);
    return nullptr;
}

SkScalerContext* AUITypeface::onCreateScalerContext(const SkScalerContextEffects& effects, const SkDescriptor* desc) const
{
    return nullptr;
//    return new SkScalerContext(sk_ref_sp(const_cast<AUITypeface*>(this)), effects, desc);
}

void AUITypeface::onFilterRec(SkScalerContextRec* rec) const
{
    //rec->setHinting(SkFontHinting::kNone);
}

int AUITypeface::onCharsToGlyphs(const void* chars, Encoding, SkGlyphID glyphs[], int glyphCount) const
{
    return 1;
}
