#pragma once

#include "AUIStringFilter.h"

class ALICEUI_API AUIFloatStringFilter : public AUIStringFilter
{
public:
    AUIFloatStringFilter();
    virtual ~AUIFloatStringFilter();


    //////////////////////////////////////////////////////////////////////////
    // Filter method
public:
    virtual std::wstring Filter(const std::wstring& strOrigin) override;
protected:
    std::wstring FilterFloat(const std::wstring& strOrigin);


    //////////////////////////////////////////////////////////////////////////
    // Format option
public:
    enum Format
    {
        kDefault_Format,
        kFixed_Format,
        kScientific_Format
    };
    explicit AUIFloatStringFilter(unsigned int precision);
    explicit AUIFloatStringFilter(Format format);
    AUIFloatStringFilter(Format format, unsigned int precision);
    void SetPrecision(unsigned int precision) { m_uiPrecision = precision; }
    void SetFormat(const Format& fmt) { m_eFormat = fmt; }
protected:
    unsigned int GetPrecision() const { return m_uiPrecision; }
    Format GetFormat() const { return m_eFormat; }
private:
    unsigned int m_uiPrecision;
    Format m_eFormat;

};
