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


Length::Length() noexcept
{
}

Length::Length(const Length &rhs) noexcept : Length(rhs.Length), Unit(rhs.Unit)
{
}

Length &Length::operator=(const Length &rhs) noexcept
{
    Length = rhs.Length;
    Unit = rhs.Unit;
    return *this;
}

Length::Length(double len, LengthUnits uints) noexcept : Length(len), Unit(uints)
{
}

Length::Length(Length &&rhs) noexcept
{
    Length = std::move(rhs.Length);
    Unit = std::move(rhs.Unit);
}

Length &Length::operator=(Length &&rhs) noexcept
{
    Length = std::move(rhs.Length);
    Unit = std::move(rhs.Unit);
    return *this;
}

void Length::Swap(Length &rhs) noexcept
{
    std::swap(Length, rhs.Length);
    std::swap(Unit, rhs.Unit);
}

bool Length::operator==(const Length &rhs) const noexcept
{
    return Math::FuzzyCompare(Length, rhs.Length * Length::ConvertScale(rhs.Unit, Unit));
}

bool Length::operator!=(const Length &rhs) const noexcept
{
    return !(*this == rhs);
}

bool Length::operator<(const Length &rhs) const noexcept
{
    return Length < rhs.Length * Length::ConvertScale(rhs.Unit, Unit);
}

bool Length::operator<=(const Length &rhs) const noexcept
{
    return Length <= rhs.Length * Length::ConvertScale(rhs.Unit, Unit);
}

bool Length::operator>(const Length &rhs) const noexcept
{
    return Length > rhs.Length * Length::ConvertScale(rhs.Unit, Unit);
}

bool Length::operator>=(const Length &rhs) const noexcept
{
    return Length >= rhs.Length * Length::ConvertScale(rhs.Unit, Unit);
}

Length Length::operator-(const Length &rhs) const noexcept
{
    Length area;
    area.Length = Length - rhs.Length * Length::ConvertScale(rhs.Unit, Unit);
    area.Unit = Unit;
    return area;
}

Length Length::operator+(const Length &rhs) const noexcept
{
    Length area;
    area.Length = Length + rhs.Length * Length::ConvertScale(rhs.Unit, Unit);
    area.Unit = Unit;
    return area;
}

Length &Length::operator+=(const Length &rhs) noexcept
{
    Length += rhs.Length * Length::ConvertScale(rhs.Unit, Unit);
    return *this;
}

Length &Length::operator-=(const Length &rhs) noexcept
{
    Length -= rhs.Length * Length::ConvertScale(rhs.Unit, Unit);
    return *this;
}

Length::operator double() const
{
    return Length;
}

Length Length::ToMeter(double l, LengthUnits units)
{
    Length length;
    length.Length = l * Length::ConvertScale(units, LengthUnits::eMeter);
    length.Unit = LengthUnits::eMeter;
    return length;
}

Length Length::ConvertTo(double l, LengthUnits srcUnit, LengthUnits tagUnit)
{
    Length length;
    length.Length = l * Length::ConvertScale(srcUnit, tagUnit);
    length.Unit = tagUnit;
    return length;
}

double Length::ConvertScale(LengthUnits from, LengthUnits to)
{
    double factor1 = 1.0, factor2 = 1.0;
    switch (from)
    {
        case LengthUnits::eKilometer:
            factor1 = KilometerToMeter;
            break;
        case LengthUnits::eDecimetre:
            factor1 = DecimetreToMeter;
            break;
        case LengthUnits::eCentimeter:
            factor1 = CentimeterToMeter;
            break;
        case LengthUnits::eMillimeter:
            factor1 = MillimeterToMeter;
            break;
        case LengthUnits::eMicron:
            factor1 = MicronToMeter;
            break;
        case LengthUnits::eNanometer:
            factor1 = NanometerToMeter;
            break;
        case LengthUnits::eInche:
            factor1 = IncheToMeter;
            break;
        case LengthUnits::eMile:
            factor1 = MileToMeter;
            break;
        case LengthUnits::eFeet:
            factor1 = FeetToMeter;
            break;
        case LengthUnits::eYard:
            factor1 = YardToMeter;
            break;
        case LengthUnits::eNauticalMile:
            factor1 = NauticalMileToMeter;
            break;
        case LengthUnits::eZhang:
            factor1 = ZhangToMeter;
            break;
        case LengthUnits::eChi:
            factor1 = ChiToMeter;
            break;
        case LengthUnits::eCun:
            factor1 = CunToMeter;
            break;
        case LengthUnits::eFen:
            factor1 = FenToMeter;
            break;
#ifdef SPATIAL_FEATURE
        case LengthUnits::eDegree:
            factor1 = DegreeToMeter;
            break;
#endif
        default:
            break;
    }

    switch (to)
    {
        case LengthUnits::eKilometer:
            factor2 = MeterToKilometer;
            break;
        case LengthUnits::eDecimetre:
            factor2 = MeterToDecimetre;
            break;
        case LengthUnits::eCentimeter:
            factor2 = MeterToCentimeter;
            break;
        case LengthUnits::eMillimeter:
            factor2 = MeterToMillimeter;
            break;
        case LengthUnits::eMicron:
            factor2 = MeterToMicron;
            break;
        case LengthUnits::eNanometer:
            factor2 = MeterToNanometer;
            break;
        case LengthUnits::eInche:
            factor2 = MeterToInche;
            break;
        case LengthUnits::eMile:
            factor2 = MeterToMile;
            break;
        case LengthUnits::eFeet:
            factor2 = MeterToFeet;
            break;
        case LengthUnits::eYard:
            factor2 = MeterToYard;
            break;
        case LengthUnits::eNauticalMile:
            factor2 = MeterToNauticalMile;
            break;
        case LengthUnits::eZhang:
            factor2 = MeterToZhang;
            break;
        case LengthUnits::eChi:
            factor2 = MeterToChi;
            break;
        case LengthUnits::eCun:
            factor2 = MeterToCun;
            break;
        case LengthUnits::eFen:
            factor2 = MeterToFen;
            break;
#ifdef SPATIAL_FEATURE
        case LengthUnits::eDegree:
            factor2 = MeterToDegree;
            break;
#endif
        default:
            break;
    }
    return factor1 * factor2;
}


}// namespace m2
