#include "pch.h"
#include "AUIFontManager.h"

AUIFontManager::AUIFontManager()
{
    //const auto wsAppDir = AUIStringUtil::ToLowerCase(AUIApplication::Instance().GetApplicationDirectory());
    //std::wstring appDir;
    //appDir = appDir.assign(wsAppDir.begin(), wsAppDir.end());
    //auto tempFilePath = appDir + L"\\temp\\resource\\font\\*.ttf"; // + fontName;
    //auto FilePath = appDir + L"\\temp\\resource\\font";
    ////auto pNewfont = pFontMgr->makeFromFile(filePath.c_str());

    //CFileFind finder; // ����ã�� // �ش� �������� Ȯ���ڰ� ttf�ΰ��� ã�´�.
    //BOOL bWorking = finder.FindFile(tempFilePath.c_str());
    //while (bWorking)// ���̻� ���������� �ݺ�
    //{
    //    bWorking = finder.FindNextFile(); // ���� ó���� ������ ã�´�    // ����� �����̸� ����
    //    auto wsFontPath = FilePath + L"\\" + (LPCTSTR)finder.GetFileName();     // ��Ʈ�� ����Ѵ�.
    //    std::string sFontPath;
    //    sFontPath.assign(wsFontPath.begin(), wsFontPath.end());
    //    auto pNewfont = makeFromFile(sFontPath.c_str());
    //    auto fdfd= pNewfont->fontStyle();
    //    
    //    // �۲��� ����Ѵ�.
    //  /*  bool defaultFamily = false;
    //    bool found = false;
    //    for (const auto& family : fFamilies) {
    //        if (family->getFamilyName().equals(finder.GetFileTitle()))
    //        {
    //            family->fTypefaces.emplace_back(
    //                std::move(pNewfont), pNewfont->fontStyle());
    //            found = true;
    //            if (defaultFamily) {
    //                fDefaultFamily = family;
    //            }
    //            break;
    //        }
    //    }
    //    if (!found) {
    //        fFamilies.emplace_back(sk_make_sp<FontStyleSet>(finder.GetFileTitle()));
    //        fFamilies.back()->fTypefaces.emplace_back(
    //            std::move(pNewfont),
    //            pNewfont->fontStyle(),
    //            sub.fStyleName);
    //        if (defaultFamily) {
    //            fDefaultFamily = fFamilies.back();
    //        }
    //    }*/


    ////font_path.Empty(); // �����̸� �ʱ�ȭ
    //}

    auto dd = countFamilies();
    //for (const auto& sub : gSubFonts) {
    //    sk_sp<AUITypeface> typeface =
    //        sk_make_sp<AUITypeface>(sk_make_sp<AUIFont>(sub.fFont), sub.fStyle);
    //    bool defaultFamily = false;
    //    if (&sub - gSubFonts == gDefaultFontIndex) {
    //        defaultFamily = true;
    //        fDefaultTypeface = typeface;
    //    }
    //    bool found = false;
    //    for (const auto& family : fFamilies) {
    //        if (family->getFamilyName().equals(sub.fFamilyName)) {
    //            family->fTypefaces.emplace_back(
    //                std::move(typeface), sub.fStyle, sub.fStyleName);
    //            found = true;
    //            if (defaultFamily) {
    //                fDefaultFamily = family;
    //            }
    //            break;
    //        }
    //    }
    //    if (!found) {
    //        fFamilies.emplace_back(sk_make_sp<FontStyleSet>(sub.fFamilyName));
    //        fFamilies.back()->fTypefaces.emplace_back(
    //            // NOLINTNEXTLINE(bugprone-use-after-move)
    //            std::move(typeface),
    //            sub.fStyle,
    //            sub.fStyleName);
    //        if (defaultFamily) {
    //            fDefaultFamily = fFamilies.back();
    //        }
    //    }
    //}
}
