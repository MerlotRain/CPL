#include <mathhelp.h>

namespace m2 {

/// @brief 平方米转平方公里
static constexpr auto Meter2ToKilemeter2 = 0.000001;
/// @brief 平方米转公顷
static constexpr auto Meter2ToHm2 = 0.0001;
/// @brief 平方米转公亩
static constexpr auto Meter2ToAre = 0.01;
/// @brief 平方米转平方分米
static constexpr auto Meter2ToDecimetre2 = 100.0;
/// @brief 平方米转平方厘米
static constexpr auto Meter2ToCentimeter2 = 10000.0;
/// @brief 平方米转平方毫米
static constexpr auto Meter2ToMillimeter2 = 1000000.0;
/// @brief 平方米转平方英亩
static constexpr auto Meter2ToAcre = 0.00025;
/// @brief 平方米转平方英里
static constexpr auto Meter2ToMile2 = 0.00000039;
/// @brief 平方米转平方码
static constexpr auto Meter2ToYard2 = 1.196;
/// @brief 平方米转平方英尺
static constexpr auto Meter2ToFeet2 = 10.7639;
/// @brief 平方米转平方英寸
static constexpr auto Meter2ToInche2 = 1550.0031;
/// @brief 平方米转平方竿
static constexpr auto Meter2ToRd2 = 0.0395;
/// @brief 平方米转中国顷
static constexpr auto Meter2Toqing = 0.000015;
/// @brief 平方米转中国亩
static constexpr auto Meter2Tomu = 0.0015;
/// @brief 平方米转中国分
static constexpr auto Meter2Tofen = 0.015;
/// @brief 空间平方米转平方度
static constexpr auto Meter2TofenDegrees = 1.0 / 12392029030.5;


/// @brief 平方公里转平方米
static constexpr auto Kilemeter2ToMeter2 = 1000000.0;
/// @brief 公顷转平方米
static constexpr auto Hm2ToMeter2 = 10000.0;
/// @brief 公亩转平方米
static constexpr auto AreToMeter2 = 100.0;
/// @brief 平方分米转平方米
static constexpr auto Decimetre2ToMeter2 = 0.01;
/// @brief 平方厘米转平方米
static constexpr auto Centimeter2ToMeter2 = 0.0001;
/// @brief 平方毫米转平方米
static constexpr auto Millimeter2ToMeter2 = 0.000001;
/// @brief 平方英亩转平方米
static constexpr auto AcreToMeter2 = 4046.8648;
/// @brief 平方英里转平方米
static constexpr auto Mile2ToMeter2 = 2589988.1103;
/// @brief 平方码转平方米
static constexpr auto Yard2ToMeter2 = 0.8361;
/// @brief 平方英尺转平方米
static constexpr auto Feet2ToMeter2 = 0.0929;
/// @brief 平方英寸转平方米
static constexpr auto Inche2ToMeter2 = 0.00065;
/// @brief 平方竿转平方米
static constexpr auto Rd2ToMeter2 = 25.2929;
/// @brief 中国顷转平方米
static constexpr auto qingToMeter2 = 66666.6667;
/// @brief 中国亩转平方米
static constexpr auto muToMeter2 = 666.6667;
/// @brief 中国分转平方米
static constexpr auto fenToMeter2 = 66.6667;
/// @brief 空间平方度转平方米
static constexpr auto DegreesToMeter2 = 12392029030.5;


GsArea::GsArea() noexcept
{
}

GsArea::GsArea(const GsArea &rhs) noexcept : Area(rhs.Area), Unit(rhs.Unit)
{
}

GsArea &GsArea::operator=(const GsArea &rhs) noexcept
{
    Area = rhs.Area;
    Unit = rhs.Unit;
    return *this;
}

GsArea::GsArea(double a, GsAreaUnits unit) noexcept : Area(a), Unit(unit)
{
}

GsArea::GsArea(GsArea &&rhs) noexcept
{
    Area = std::move(rhs.Area);
    Unit = std::move(rhs.Unit);
}

GsArea &GsArea::operator=(GsArea &&rhs) noexcept
{
    Area = std::move(rhs.Area);
    Unit = std::move(rhs.Unit);
    return *this;
}

void GsArea::Swap(GsArea &rhs) noexcept
{
    std::swap(Area, rhs.Area);
    std::swap(Unit, rhs.Unit);
}

bool GsArea::operator==(const GsArea &rhs) const noexcept
{
    return Math::FuzzyCompare(Area, rhs.Area * GsArea::ConvertScale(rhs.Unit, Unit));
}

bool GsArea::operator!=(const GsArea &rhs) const noexcept
{
    return !(*this == rhs);
}

bool GsArea::operator<(const GsArea &rhs) const noexcept
{
    return Area < rhs.Area * GsArea::ConvertScale(rhs.Unit, Unit);
}

bool GsArea::operator<=(const GsArea &rhs) const noexcept
{
    return Area <= rhs.Area * GsArea::ConvertScale(rhs.Unit, Unit);
}

bool GsArea::operator>(const GsArea &rhs) const noexcept
{
    return Area > rhs.Area * GsArea::ConvertScale(rhs.Unit, Unit);
}

bool GsArea::operator>=(const GsArea &rhs) const noexcept
{
    return Area >= rhs.Area * GsArea::ConvertScale(rhs.Unit, Unit);
}

GsArea GsArea::operator-(const GsArea &rhs) const noexcept
{
    GsArea area;
    area.Area = Area - rhs.Area * GsArea::ConvertScale(rhs.Unit, Unit);
    area.Unit = Unit;
    return area;
}

GsArea GsArea::operator+(const GsArea &rhs) const noexcept
{
    GsArea area;
    area.Area = Area + rhs.Area * GsArea::ConvertScale(rhs.Unit, Unit);
    area.Unit = Unit;
    return area;
}

GsArea &GsArea::operator+=(const GsArea &rhs) noexcept
{
    Area += rhs.Area * GsArea::ConvertScale(rhs.Unit, Unit);
    return *this;
}

GsArea &GsArea::operator-=(const GsArea &rhs) noexcept
{
    Area -= rhs.Area * GsArea::ConvertScale(rhs.Unit, Unit);
    return *this;
}

GsArea::operator double() const
{
    return Area;
}

GsArea GsArea::ToMeter2(double a, GsAreaUnits units)
{
    GsArea area;
    area.Area = a * GsArea::ConvertScale(units, GsAreaUnits::eMeter2);
    area.Unit = GsAreaUnits::eMeter2;
    return area;
}

GsArea GsArea::ConvertTo(double a, GsAreaUnits srcUnit, GsAreaUnits tagUnit)
{
    GsArea area;
    area.Area = a * GsArea::ConvertScale(srcUnit, tagUnit);
    area.Unit = tagUnit;
    return area;
}

double GsArea::Meter2Area(double a, GsAreaUnits srcUnit, GsAreaUnits tagUnit)
{
    return ConvertTo(a, srcUnit, tagUnit).Area;
}

double GsArea::ConvertScale(GsAreaUnits from, GsAreaUnits to)
{
    double fromToMeter2 = 1.0;
    double Meter2ToTo = 1.0;
    switch (from)
    {
        case GsAreaUnits::eKilometer2:
            fromToMeter2 = Kilemeter2ToMeter2;
            break;
        case GsAreaUnits::ehm2:
            fromToMeter2 = Hm2ToMeter2;
            break;
        case GsAreaUnits::eAre:
            fromToMeter2 = AreToMeter2;
            break;
        case GsAreaUnits::eDecimetre2:
            fromToMeter2 = Decimetre2ToMeter2;
            break;
        case GsAreaUnits::eCentimeter2:
            fromToMeter2 = Centimeter2ToMeter2;
            break;
        case GsAreaUnits::eMillimeter2:
            fromToMeter2 = Millimeter2ToMeter2;
            break;
        case GsAreaUnits::eAcre:
            fromToMeter2 = AcreToMeter2;
            break;
        case GsAreaUnits::eMile2:
            fromToMeter2 = Mile2ToMeter2;
            break;
        case GsAreaUnits::eYard2:
            fromToMeter2 = Yard2ToMeter2;
            break;
        case GsAreaUnits::eFeet2:
            fromToMeter2 = Feet2ToMeter2;
            break;
        case GsAreaUnits::eInche2:
            fromToMeter2 = Inche2ToMeter2;
            break;
        case GsAreaUnits::eRd2:
            fromToMeter2 = Rd2ToMeter2;
            break;
        case GsAreaUnits::eQing:
            fromToMeter2 = qingToMeter2;
            break;
        case GsAreaUnits::eMu:
            fromToMeter2 = muToMeter2;
            break;
        case GsAreaUnits::eFen:
            fromToMeter2 = fenToMeter2;
            break;
#ifdef SPATIAL_FEATURE
        case GsAreaUnits::eDegrees:
            fromToMeter2 = DegreesToMeter2;
            break;
#endif
        default:
            break;
    }

    switch (to)
    {
        case GsAreaUnits::eKilometer2:
            Meter2ToTo = Meter2ToKilemeter2;
            break;
        case GsAreaUnits::ehm2:
            Meter2ToTo = Meter2ToHm2;
            break;
        case GsAreaUnits::eAre:
            Meter2ToTo = Meter2ToAre;
            break;
        case GsAreaUnits::eDecimetre2:
            Meter2ToTo = Meter2ToDecimetre2;
            break;
        case GsAreaUnits::eCentimeter2:
            Meter2ToTo = Meter2ToCentimeter2;
            break;
        case GsAreaUnits::eMillimeter2:
            Meter2ToTo = Meter2ToMillimeter2;
            break;
        case GsAreaUnits::eAcre:
            Meter2ToTo = Meter2ToAcre;
            break;
        case GsAreaUnits::eMile2:
            Meter2ToTo = Meter2ToMile2;
            break;
        case GsAreaUnits::eYard2:
            Meter2ToTo = Meter2ToYard2;
            break;
        case GsAreaUnits::eFeet2:
            Meter2ToTo = Meter2ToFeet2;
            break;
        case GsAreaUnits::eInche2:
            Meter2ToTo = Meter2ToInche2;
            break;
        case GsAreaUnits::eRd2:
            Meter2ToTo = Meter2ToRd2;
            break;
        case GsAreaUnits::eQing:
            Meter2ToTo = Meter2Toqing;
            break;
        case GsAreaUnits::eMu:
            Meter2ToTo = Meter2Tomu;
            break;
        case GsAreaUnits::eFen:
            Meter2ToTo = Meter2Tofen;
            break;
#ifdef SPATIAL_FEATURE
        case GsAreaUnits::eDegrees:
            Meter2ToTo = Meter2ToDegrees;
            break;
#endif
        default:
            break;
    }

    return fromToMeter2 * Meter2ToTo;
}


}// namespace m2
