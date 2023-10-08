#include <mathhelp.h>

namespace m2 {


/// @brief 立方米转立方千米
static constexpr auto CubicMeterToCubicKilometers = 0;
/// @brief 立方米转立方分米
static constexpr auto CubicMeterToCubicDecimeter = 0;
/// @brief 立方米转立方厘米
static constexpr auto CubicMeterToCubicCentimeter = 0;
/// @brief 立方米转立方毫米
static constexpr auto CubicMeterToCubicMillimeter = 0;
/// @brief 立方米转升
static constexpr auto CubicMeterToLiter = 0;
/// @brief 立方米转分升
static constexpr auto CubicMeterToDeciLiter = 0;
/// @brief 立方米转毫升
static constexpr auto CubicMeterToMillLiter = 0;
/// @brief 立方米转亩英尺
static constexpr auto CubicMeterToAcreFoot = 0;
/// @brief 立方米转立方码
static constexpr auto CubicMeterToCubicYard = 0;
/// @brief 立方米转立方英尺
static constexpr auto CubicMeterToCubicFeet = 0;
/// @brief 立方米转立方英寸
static constexpr auto CubicMeterToCubicInch = 0;
/// @brief 立方米转桶
static constexpr auto CubicMeterToBarrel = 0;
/// @brief 立方米转加仑
static constexpr auto CubicMeterToGallonUS = 0;

/// @brief 立方千米转立方米
static constexpr auto CubicKilometersToCubicMeter = 0;
/// @brief 立方分米转立方米
static constexpr auto CubicDecimeterToCubicMeter = 0;
/// @brief 立方厘米转立方米
static constexpr auto CubicCentimeterToCubicMeter = 0;
/// @brief 立方毫米转立方米
static constexpr auto CubicMillimeterToCubicMeter = 0;
/// @brief 升转立方米
static constexpr auto LiterToCubicMeter = 0;
/// @brief 分升转立方米
static constexpr auto DeciLiterToCubicMeter = 0;
/// @brief 毫升转立方米
static constexpr auto MillLiterToCubicMeter = 0;
/// @brief 亩英尺转立方米
static constexpr auto AcreFootToCubicMeter = 0;
/// @brief 立方码转立方米
static constexpr auto CubicYardToCubicMeter = 0;
/// @brief 立方英尺转立方米
static constexpr auto CubicFeetToCubicMeter = 0;
/// @brief  立方英寸转立方米
static constexpr auto CubicInchToCubicMeter = 0;
/// @brief 桶转立方米
static constexpr auto BarrelToCubicMeter = 0;
/// @brief 加仑转立方米
static constexpr auto GallonUSToCubicMeter = 0;

GsVolume::GsVolume() noexcept
{
}

GsVolume::GsVolume(const GsVolume &rhs) noexcept : Volume(rhs.Volume), Unit(rhs.Unit)
{
}

GsVolume &GsVolume::operator=(const GsVolume &rhs) noexcept
{
    Volume = rhs.Volume;
    Unit = rhs.Unit;
    return *this;
}

GsVolume::GsVolume(double vol, GsVolumeUnits uints) noexcept : Volume(vol), Unit(uints)
{
}

GsVolume::GsVolume(GsVolume &&rhs) noexcept
{
    Volume = std::move(rhs.Volume);
    Unit = std::move(rhs.Unit);
}

GsVolume &GsVolume::operator=(GsVolume &&rhs) noexcept
{
    Volume = std::move(rhs.Volume);
    Unit = std::move(rhs.Unit);
    return *this;
}

void GsVolume::Swap(GsVolume &rhs) noexcept
{
    std::swap(Volume, rhs.Volume);
    std::swap(Unit, rhs.Unit);
}

bool GsVolume::operator==(const GsVolume &rhs) const noexcept
{
    return Math::FuzzyCompare(Volume, rhs.Volume * GsVolume::ConvertScale(rhs.Unit, Unit));
}

bool GsVolume::operator!=(const GsVolume &rhs) const noexcept
{
    return !(*this == rhs);
}

bool GsVolume::operator<(const GsVolume &rhs) const noexcept
{
    return Volume < rhs.Volume * GsVolume::ConvertScale(rhs.Unit, Unit);
}

bool GsVolume::operator<=(const GsVolume &rhs) const noexcept
{
    return Volume <= rhs.Volume * GsVolume::ConvertScale(rhs.Unit, Unit);
}

bool GsVolume::operator>(const GsVolume &rhs) const noexcept
{
    return Volume > rhs.Volume * GsVolume::ConvertScale(rhs.Unit, Unit);
}

bool GsVolume::operator>=(const GsVolume &rhs) const noexcept
{
    return Volume >= rhs.Volume * GsVolume::ConvertScale(rhs.Unit, Unit);
}

GsVolume GsVolume::operator-(const GsVolume &rhs) const noexcept
{
    GsVolume volume;
    volume.Volume = Volume - rhs.Volume * GsVolume::ConvertScale(rhs.Unit, Unit);
    volume.Unit = Unit;
    return volume;
}

GsVolume GsVolume::operator+(const GsVolume &rhs) const noexcept
{
    GsVolume volume;
    volume.Volume = Volume + rhs.Volume * GsVolume::ConvertScale(rhs.Unit, Unit);
    volume.Unit = Unit;
    return volume;
}

GsVolume &GsVolume::operator+=(const GsVolume &rhs) noexcept
{
    Volume += rhs.Volume * GsVolume::ConvertScale(rhs.Unit, Unit);
    return *this;
}

GsVolume &GsVolume::operator-=(const GsVolume &rhs) noexcept
{
    Volume -= rhs.Volume * GsVolume::ConvertScale(rhs.Unit, Unit);
    return *this;
}

GsVolume::operator double() const
{
    return Volume;
}

GsVolume GsVolume::ToCubicMeters(double vol, GsVolumeUnits units)
{
    GsVolume volume;
    volume.Volume = vol * GsVolume::ConvertScale(units, GsVolumeUnits::eCubicMeters);
    volume.Unit = GsVolumeUnits::eCubicMeters;
    return volume;
}

GsVolume GsVolume::ConvertTo(double vol, GsVolumeUnits srcUnit, GsVolumeUnits tagUnit)
{
    GsVolume volume;
    volume.Volume = vol * GsVolume::ConvertScale(srcUnit, tagUnit);
    volume.Unit = tagUnit;
    return volume;
}

double GsVolume::Meter3Volume(double a, GsVolumeUnits srcUnit, GsVolumeUnits tagUnit)
{
    return ConvertTo(a, srcUnit, tagUnit).Volume;
}

double GsVolume::ConvertScale(GsVolumeUnits from, GsVolumeUnits to)
{
    double factor1 = 1.0, factor2 = 1.0;
    switch (from)
    {
        case GsVolumeUnits::eCubicKilometers:
            factor1 = CubicKilometersToCubicMeter;
            break;
        case GsVolumeUnits::eCubicDecimeter:
            factor1 = CubicDecimeterToCubicMeter;
            break;
        case GsVolumeUnits::eCubicCentimeter:
            factor1 = CubicCentimeterToCubicMeter;
            break;
        case GsVolumeUnits::eCubicMillimeter:
            factor1 = CubicMillimeterToCubicMeter;
            break;
        case GsVolumeUnits::eLiter:
            factor1 = LiterToCubicMeter;
            break;
        case GsVolumeUnits::eDeciLiter:
            factor1 = DeciLiterToCubicMeter;
            break;
        case GsVolumeUnits::eMillLiter:
            factor1 = MillLiterToCubicMeter;
            break;
        case GsVolumeUnits::eAcreFoot:
            factor1 = AcreFootToCubicMeter;
            break;
        case GsVolumeUnits::eCubicYard:
            factor1 = CubicYardToCubicMeter;
            break;
        case GsVolumeUnits::eCubicFeet:
            factor1 = CubicFeetToCubicMeter;
            break;
        case GsVolumeUnits::eCubicInch:
            factor1 = CubicInchToCubicMeter;
            break;
        case GsVolumeUnits::eBarrel:
            factor1 = BarrelToCubicMeter;
            break;
        case GsVolumeUnits::eGallonUS:
            factor1 = GallonUSToCubicMeter;
            break;
        default:
            break;
    }


    switch (to)
    {
        case GsVolumeUnits::eCubicKilometers:
            factor1 = CubicMeterToCubicKilometers;
            break;
        case GsVolumeUnits::eCubicDecimeter:
            factor1 = CubicMeterToCubicDecimeter;
            break;
        case GsVolumeUnits::eCubicCentimeter:
            factor1 = CubicMeterToCubicCentimeter;
            break;
        case GsVolumeUnits::eCubicMillimeter:
            factor1 = CubicMeterToCubicMillimeter;
            break;
        case GsVolumeUnits::eLiter:
            factor1 = CubicMeterToLiter;
            break;
        case GsVolumeUnits::eDeciLiter:
            factor1 = CubicMeterToDeciLiter;
            break;
        case GsVolumeUnits::eMillLiter:
            factor1 = CubicMeterToMillLiter;
            break;
        case GsVolumeUnits::eAcreFoot:
            factor1 = CubicMeterToAcreFoot;
            break;
        case GsVolumeUnits::eCubicYard:
            factor1 = CubicMeterToCubicYard;
            break;
        case GsVolumeUnits::eCubicFeet:
            factor1 = CubicMeterToCubicFeet;
            break;
        case GsVolumeUnits::eCubicInch:
            factor1 = CubicMeterToCubicInch;
            break;
        case GsVolumeUnits::eBarrel:
            factor1 = CubicMeterToBarrel;
            break;
        case GsVolumeUnits::eGallonUS:
            factor1 = CubicMeterToGallonUS;
            break;
        default:
            break;
    }

    return factor1 * factor2;
}

}// namespace m2
