#pragma once

#include "AUIAPIDef.h"

#include <string>

enum class AUIUnitType : unsigned int
{
    kNone = 0,

    // SI Distance
    kKilometer,
    kMeter,
    kCentimeter,
    kMillimeter,
    kMicrometer,
    kNanometer,

    // Non-SI Distance
    kYard,
    kInch,
    kFoot,
    kAngstrom,

    // SI Area
    kSquaremeter,

    // Non-SI Area
    kHectare,
    kAcre,

    // SI Mass
    kKilogram,
    kGram,
    kMilligram,

    // Non-SI Mass
    kTon,
    kPound,
    kOunce,

    // Time
    kHour,
    kMinute,
    kSecond,

    // Electro-magnetic
    kVolt,
    kWatt,
    kTesla,
    kCoulomb,
    kHenry,
    kWeber,
    kAmpere,

    // Force
    kKilogramforce,
    kGramforce,
    kNewton,
    kPascal,

    // Frequency
    kHertz,

    // Energy
    kKilojoule,
    kJoule,
    kKilocalorie,
    kCalorie,

    // Angle
    kDegree,
    kRadian,

    // Temperature
    kCelsius,
    kFahrenheit,

    // Percent
    kPercent,
};

class ALICEUI_API AUIUnitString
{
public:
    static std::wstring ToString(const AUIUnitType& type);
};

