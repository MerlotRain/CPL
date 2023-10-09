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


Area::Area() noexcept
{
}

Area::Area(const Area &rhs) noexcept : Area(rhs.Area), Unit(rhs.Unit)
{
}

Area &Area::operator=(const Area &rhs) noexcept
{
    Area = rhs.Area;
    Unit = rhs.Unit;
    return *this;
}

Area::Area(double a, AreaUnits unit) noexcept : Area(a), Unit(unit)
{
}

Area::Area(Area &&rhs) noexcept
{
    Area = std::move(rhs.Area);
    Unit = std::move(rhs.Unit);
}

Area &Area::operator=(Area &&rhs) noexcept
{
    Area = std::move(rhs.Area);
    Unit = std::move(rhs.Unit);
    return *this;
}

void Area::Swap(Area &rhs) noexcept
{
    std::swap(Area, rhs.Area);
    std::swap(Unit, rhs.Unit);
}

bool Area::operator==(const Area &rhs) const noexcept
{
    return Math::FuzzyCompare(Area, rhs.Area * Area::ConvertScale(rhs.Unit, Unit));
}

bool Area::operator!=(const Area &rhs) const noexcept
{
    return !(*this == rhs);
}

bool Area::operator<(const Area &rhs) const noexcept
{
    return Area < rhs.Area * Area::ConvertScale(rhs.Unit, Unit);
}

bool Area::operator<=(const Area &rhs) const noexcept
{
    return Area <= rhs.Area * Area::ConvertScale(rhs.Unit, Unit);
}

bool Area::operator>(const Area &rhs) const noexcept
{
    return Area > rhs.Area * Area::ConvertScale(rhs.Unit, Unit);
}

bool Area::operator>=(const Area &rhs) const noexcept
{
    return Area >= rhs.Area * Area::ConvertScale(rhs.Unit, Unit);
}

Area Area::operator-(const Area &rhs) const noexcept
{
    Area area;
    area.Area = Area - rhs.Area * Area::ConvertScale(rhs.Unit, Unit);
    area.Unit = Unit;
    return area;
}

Area Area::operator+(const Area &rhs) const noexcept
{
    Area area;
    area.Area = Area + rhs.Area * Area::ConvertScale(rhs.Unit, Unit);
    area.Unit = Unit;
    return area;
}

Area &Area::operator+=(const Area &rhs) noexcept
{
    Area += rhs.Area * Area::ConvertScale(rhs.Unit, Unit);
    return *this;
}

Area &Area::operator-=(const Area &rhs) noexcept
{
    Area -= rhs.Area * Area::ConvertScale(rhs.Unit, Unit);
    return *this;
}

Area::operator double() const
{
    return Area;
}

Area Area::ToMeter2(double a, AreaUnits units)
{
    Area area;
    area.Area = a * Area::ConvertScale(units, AreaUnits::eMeter2);
    area.Unit = AreaUnits::eMeter2;
    return area;
}

Area Area::ConvertTo(double a, AreaUnits srcUnit, AreaUnits tagUnit)
{
    Area area;
    area.Area = a * Area::ConvertScale(srcUnit, tagUnit);
    area.Unit = tagUnit;
    return area;
}

double Area::Meter2Area(double a, AreaUnits srcUnit, AreaUnits tagUnit)
{
    return ConvertTo(a, srcUnit, tagUnit).Area;
}

double Area::ConvertScale(AreaUnits from, AreaUnits to)
{
    double fromToMeter2 = 1.0;
    double Meter2ToTo = 1.0;
    switch (from)
    {
        case AreaUnits::eKilometer2:
            fromToMeter2 = Kilemeter2ToMeter2;
            break;
        case AreaUnits::ehm2:
            fromToMeter2 = Hm2ToMeter2;
            break;
        case AreaUnits::eAre:
            fromToMeter2 = AreToMeter2;
            break;
        case AreaUnits::eDecimetre2:
            fromToMeter2 = Decimetre2ToMeter2;
            break;
        case AreaUnits::eCentimeter2:
            fromToMeter2 = Centimeter2ToMeter2;
            break;
        case AreaUnits::eMillimeter2:
            fromToMeter2 = Millimeter2ToMeter2;
            break;
        case AreaUnits::eAcre:
            fromToMeter2 = AcreToMeter2;
            break;
        case AreaUnits::eMile2:
            fromToMeter2 = Mile2ToMeter2;
            break;
        case AreaUnits::eYard2:
            fromToMeter2 = Yard2ToMeter2;
            break;
        case AreaUnits::eFeet2:
            fromToMeter2 = Feet2ToMeter2;
            break;
        case AreaUnits::eInche2:
            fromToMeter2 = Inche2ToMeter2;
            break;
        case AreaUnits::eRd2:
            fromToMeter2 = Rd2ToMeter2;
            break;
        case AreaUnits::eQing:
            fromToMeter2 = qingToMeter2;
            break;
        case AreaUnits::eMu:
            fromToMeter2 = muToMeter2;
            break;
        case AreaUnits::eFen:
            fromToMeter2 = fenToMeter2;
            break;
#ifdef SPATIAL_FEATURE
        case AreaUnits::eDegrees:
            fromToMeter2 = DegreesToMeter2;
            break;
#endif
        default:
            break;
    }

    switch (to)
    {
        case AreaUnits::eKilometer2:
            Meter2ToTo = Meter2ToKilemeter2;
            break;
        case AreaUnits::ehm2:
            Meter2ToTo = Meter2ToHm2;
            break;
        case AreaUnits::eAre:
            Meter2ToTo = Meter2ToAre;
            break;
        case AreaUnits::eDecimetre2:
            Meter2ToTo = Meter2ToDecimetre2;
            break;
        case AreaUnits::eCentimeter2:
            Meter2ToTo = Meter2ToCentimeter2;
            break;
        case AreaUnits::eMillimeter2:
            Meter2ToTo = Meter2ToMillimeter2;
            break;
        case AreaUnits::eAcre:
            Meter2ToTo = Meter2ToAcre;
            break;
        case AreaUnits::eMile2:
            Meter2ToTo = Meter2ToMile2;
            break;
        case AreaUnits::eYard2:
            Meter2ToTo = Meter2ToYard2;
            break;
        case AreaUnits::eFeet2:
            Meter2ToTo = Meter2ToFeet2;
            break;
        case AreaUnits::eInche2:
            Meter2ToTo = Meter2ToInche2;
            break;
        case AreaUnits::eRd2:
            Meter2ToTo = Meter2ToRd2;
            break;
        case AreaUnits::eQing:
            Meter2ToTo = Meter2Toqing;
            break;
        case AreaUnits::eMu:
            Meter2ToTo = Meter2Tomu;
            break;
        case AreaUnits::eFen:
            Meter2ToTo = Meter2Tofen;
            break;
#ifdef SPATIAL_FEATURE
        case AreaUnits::eDegrees:
            Meter2ToTo = Meter2ToDegrees;
            break;
#endif
        default:
            break;
    }

    return fromToMeter2 * Meter2ToTo;
}


}// namespace m2
