#include "pch.h"
#include "AUIUnitString.h"

static const std::unordered_map< AUIUnitType, std::wstring > gMapUnitType2Str{
    { AUIUnitType::kNone,           L"" },
    { AUIUnitType::kKilometer,      L"km" },
    { AUIUnitType::kMeter,          L"m" },
    { AUIUnitType::kCentimeter,     L"cm" },
    { AUIUnitType::kMillimeter,     L"mm" },
    { AUIUnitType::kNanometer,      L"nm" },
    { AUIUnitType::kYard,           L"yd" },
    { AUIUnitType::kInch,           L"in" },
    { AUIUnitType::kFoot,           L"ft" },
    { AUIUnitType::kAngstrom,       L"（" },
    { AUIUnitType::kSquaremeter,    L"С" },
    { AUIUnitType::kHectare,        L"ha" },
    { AUIUnitType::kAcre,           L"a" },
    { AUIUnitType::kKilogram,       L"kg" },
    { AUIUnitType::kGram,           L"g" },
    { AUIUnitType::kTon,            L"t" },
    { AUIUnitType::kPound,          L"lb" },
    { AUIUnitType::kOunce,          L"oz" },
    { AUIUnitType::kHour,           L"h" },
    { AUIUnitType::kMinute,         L"m" },
    { AUIUnitType::kSecond,         L"s" },
    { AUIUnitType::kVolt,           L"V" },
    { AUIUnitType::kWatt,           L"W" },
    { AUIUnitType::kTesla,          L"T" },
    { AUIUnitType::kCoulomb,        L"C" },
    { AUIUnitType::kHenry,          L"H" },
    { AUIUnitType::kWeber,          L"Wb" },
    { AUIUnitType::kAmpere,         L"A" },
    { AUIUnitType::kKilogramforce,  L"kgf" },
    { AUIUnitType::kGramforce,      L"gf" },
    { AUIUnitType::kNewton,         L"N" },
    { AUIUnitType::kPascal,         L"Pa" },
    { AUIUnitType::kHertz,          L"Hz" },
    { AUIUnitType::kKilojoule,      L"kJ" },
    { AUIUnitType::kJoule,          L"J" },
    { AUIUnitType::kKilocalorie,    L"kcal" },
    { AUIUnitType::kCalorie,        L"cal" },
    { AUIUnitType::kDegree,         L"━" },
    { AUIUnitType::kRadian,         L"[rad," },
    { AUIUnitType::kCelsius,        L"━C" },
    { AUIUnitType::kFahrenheit,     L"━F" },
    { AUIUnitType::kPercent,        L"%" }
};

std::wstring AUIUnitString::ToString(const AUIUnitType& type)
{
    const auto found = gMapUnitType2Str.find(type);
    if (gMapUnitType2Str.end() == found)
        return {};
    return found->second;
}
