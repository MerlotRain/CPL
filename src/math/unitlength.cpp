#include <mathhelp.h>

namespace m2 {


/// @brief 米转千米
static constexpr auto MeterToKilometer = 0.001;
/// @brief 米转分米
static constexpr auto MeterToDecimetre = 10;
/// @brief 米转厘米
static constexpr auto MeterToCentimeter = 100;
/// @brief 米转毫米
static constexpr auto MeterToMillimeter = 1000;
/// @brief 米转微米
static constexpr auto MeterToMicron = 1000000;
/// @brief 米转纳米
static constexpr auto MeterToNanometer = 1000000000;
/// @brief 米转英寸
static constexpr auto MeterToInche = 39.3700787;
/// @brief 米转英里
static constexpr auto MeterToMile = 0.0006214;
/// @brief 米转英尺
static constexpr auto MeterToFeet = 3.2808;
/// @brief 米转码
static constexpr auto MeterToYard = 1.0936;
/// @brief 米转海里
static constexpr auto MeterToNauticalMile = 0.00054;
/// @brief 米转中国单位丈
static constexpr auto MeterToZhang = 0.3;
/// @brief 米转中国单位尺
static constexpr auto MeterToChi = 3;
/// @brief 米转中国单位寸
static constexpr auto MeterToCun = 30;
/// @brief 米转中国单位分
static constexpr auto MeterToFen = 300;
/// @brief 米转空间度
static constexpr auto MeterToDegree = 1.0 / 111319.49079327358;

/// @brief 千米转米
static constexpr auto KilometerToMeter = 1000;
/// @brief 分米转米
static constexpr auto DecimetreToMeter = 0.1;
/// @brief 厘米转米
static constexpr auto CentimeterToMeter = 0.01;
/// @brief 毫米转米
static constexpr auto MillimeterToMeter = 0.001;
/// @brief 微米转米
static constexpr auto MicronToMeter = 0.000001;
/// @brief 纳米转米
static constexpr auto NanometerToMeter = 0.000000001;
/// @brief 英寸转米
static constexpr auto IncheToMeter = 0.0254;
/// @brief 英里转米
static constexpr auto MileToMeter = 1609.344;
/// @brief 英尺转米
static constexpr auto FeetToMeter = 0.3048;
/// @brief 码转米
static constexpr auto YardToMeter = 0.9144;
/// @brief 海里转米
static constexpr auto NauticalMileToMeter = 1852;
/// @brief 中国单位丈转米
static constexpr auto ZhangToMeter = 3.3333;
/// @brief 中国单位尺转米
static constexpr auto ChiToMeter = 0.3333;
/// @brief 中国单位寸转米
static constexpr auto CunToMeter = 0.0333;
/// @brief 中国单位分转米
static constexpr auto FenToMeter = 0.0033;
/// @brief 空间度转米
static constexpr auto DegreeToMeter = 111319.49079327358;


GsLength::GsLength() noexcept
{
}

GsLength::GsLength(const GsLength &rhs) noexcept : Length(rhs.Length), Unit(rhs.Unit)
{
}

GsLength &GsLength::operator=(const GsLength &rhs) noexcept
{
    Length = rhs.Length;
    Unit = rhs.Unit;
    return *this;
}

GsLength::GsLength(double len, GsLengthUnits uints) noexcept : Length(len), Unit(uints)
{
}

GsLength::GsLength(GsLength &&rhs) noexcept
{
    Length = std::move(rhs.Length);
    Unit = std::move(rhs.Unit);
}

GsLength &GsLength::operator=(GsLength &&rhs) noexcept
{
    Length = std::move(rhs.Length);
    Unit = std::move(rhs.Unit);
    return *this;
}

void GsLength::Swap(GsLength &rhs) noexcept
{
    std::swap(Length, rhs.Length);
    std::swap(Unit, rhs.Unit);
}

bool GsLength::operator==(const GsLength &rhs) const noexcept
{
    return Math::FuzzyCompare(Length, rhs.Length * GsLength::ConvertScale(rhs.Unit, Unit));
}

bool GsLength::operator!=(const GsLength &rhs) const noexcept
{
    return !(*this == rhs);
}

bool GsLength::operator<(const GsLength &rhs) const noexcept
{
    return Length < rhs.Length * GsLength::ConvertScale(rhs.Unit, Unit);
}

bool GsLength::operator<=(const GsLength &rhs) const noexcept
{
    return Length <= rhs.Length * GsLength::ConvertScale(rhs.Unit, Unit);
}

bool GsLength::operator>(const GsLength &rhs) const noexcept
{
    return Length > rhs.Length * GsLength::ConvertScale(rhs.Unit, Unit);
}

bool GsLength::operator>=(const GsLength &rhs) const noexcept
{
    return Length >= rhs.Length * GsLength::ConvertScale(rhs.Unit, Unit);
}

GsLength GsLength::operator-(const GsLength &rhs) const noexcept
{
    GsLength area;
    area.Length = Length - rhs.Length * GsLength::ConvertScale(rhs.Unit, Unit);
    area.Unit = Unit;
    return area;
}

GsLength GsLength::operator+(const GsLength &rhs) const noexcept
{
    GsLength area;
    area.Length = Length + rhs.Length * GsLength::ConvertScale(rhs.Unit, Unit);
    area.Unit = Unit;
    return area;
}

GsLength &GsLength::operator+=(const GsLength &rhs) noexcept
{
    Length += rhs.Length * GsLength::ConvertScale(rhs.Unit, Unit);
    return *this;
}

GsLength &GsLength::operator-=(const GsLength &rhs) noexcept
{
    Length -= rhs.Length * GsLength::ConvertScale(rhs.Unit, Unit);
    return *this;
}

GsLength::operator double() const
{
    return Length;
}

GsLength GsLength::ToMeter(double l, GsLengthUnits units)
{
    GsLength length;
    length.Length = l * GsLength::ConvertScale(units, GsLengthUnits::eMeter);
    length.Unit = GsLengthUnits::eMeter;
    return length;
}

GsLength GsLength::ConvertTo(double l, GsLengthUnits srcUnit, GsLengthUnits tagUnit)
{
    GsLength length;
    length.Length = l * GsLength::ConvertScale(srcUnit, tagUnit);
    length.Unit = tagUnit;
    return length;
}

double GsLength::ConvertScale(GsLengthUnits from, GsLengthUnits to)
{
    double factor1 = 1.0, factor2 = 1.0;
    switch (from)
    {
        case GsLengthUnits::eKilometer:
            factor1 = KilometerToMeter;
            break;
        case GsLengthUnits::eDecimetre:
            factor1 = DecimetreToMeter;
            break;
        case GsLengthUnits::eCentimeter:
            factor1 = CentimeterToMeter;
            break;
        case GsLengthUnits::eMillimeter:
            factor1 = MillimeterToMeter;
            break;
        case GsLengthUnits::eMicron:
            factor1 = MicronToMeter;
            break;
        case GsLengthUnits::eNanometer:
            factor1 = NanometerToMeter;
            break;
        case GsLengthUnits::eInche:
            factor1 = IncheToMeter;
            break;
        case GsLengthUnits::eMile:
            factor1 = MileToMeter;
            break;
        case GsLengthUnits::eFeet:
            factor1 = FeetToMeter;
            break;
        case GsLengthUnits::eYard:
            factor1 = YardToMeter;
            break;
        case GsLengthUnits::eNauticalMile:
            factor1 = NauticalMileToMeter;
            break;
        case GsLengthUnits::eZhang:
            factor1 = ZhangToMeter;
            break;
        case GsLengthUnits::eChi:
            factor1 = ChiToMeter;
            break;
        case GsLengthUnits::eCun:
            factor1 = CunToMeter;
            break;
        case GsLengthUnits::eFen:
            factor1 = FenToMeter;
            break;
#ifdef SPATIAL_FEATURE
        case GsLengthUnits::eDegree:
            factor1 = DegreeToMeter;
            break;
#endif
        default:
            break;
    }

    switch (to)
    {
        case GsLengthUnits::eKilometer:
            factor2 = MeterToKilometer;
            break;
        case GsLengthUnits::eDecimetre:
            factor2 = MeterToDecimetre;
            break;
        case GsLengthUnits::eCentimeter:
            factor2 = MeterToCentimeter;
            break;
        case GsLengthUnits::eMillimeter:
            factor2 = MeterToMillimeter;
            break;
        case GsLengthUnits::eMicron:
            factor2 = MeterToMicron;
            break;
        case GsLengthUnits::eNanometer:
            factor2 = MeterToNanometer;
            break;
        case GsLengthUnits::eInche:
            factor2 = MeterToInche;
            break;
        case GsLengthUnits::eMile:
            factor2 = MeterToMile;
            break;
        case GsLengthUnits::eFeet:
            factor2 = MeterToFeet;
            break;
        case GsLengthUnits::eYard:
            factor2 = MeterToYard;
            break;
        case GsLengthUnits::eNauticalMile:
            factor2 = MeterToNauticalMile;
            break;
        case GsLengthUnits::eZhang:
            factor2 = MeterToZhang;
            break;
        case GsLengthUnits::eChi:
            factor2 = MeterToChi;
            break;
        case GsLengthUnits::eCun:
            factor2 = MeterToCun;
            break;
        case GsLengthUnits::eFen:
            factor2 = MeterToFen;
            break;
#ifdef SPATIAL_FEATURE
        case GsLengthUnits::eDegree:
            factor2 = MeterToDegree;
            break;
#endif
        default:
            break;
    }
    return factor1 * factor2;
}


}// namespace m2
