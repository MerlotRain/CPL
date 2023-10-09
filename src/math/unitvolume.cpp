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

Volume::Volume() noexcept
{
}

Volume::Volume(const Volume &rhs) noexcept : Volume(rhs.Volume), Unit(rhs.Unit)
{
}

Volume &Volume::operator=(const Volume &rhs) noexcept
{
    Volume = rhs.Volume;
    Unit = rhs.Unit;
    return *this;
}

Volume::Volume(double vol, VolumeUnits uints) noexcept : Volume(vol), Unit(uints)
{
}

Volume::Volume(Volume &&rhs) noexcept
{
    Volume = std::move(rhs.Volume);
    Unit = std::move(rhs.Unit);
}

Volume &Volume::operator=(Volume &&rhs) noexcept
{
    Volume = std::move(rhs.Volume);
    Unit = std::move(rhs.Unit);
    return *this;
}

void Volume::Swap(Volume &rhs) noexcept
{
    std::swap(Volume, rhs.Volume);
    std::swap(Unit, rhs.Unit);
}

bool Volume::operator==(const Volume &rhs) const noexcept
{
    return Math::FuzzyCompare(Volume, rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit));
}

bool Volume::operator!=(const Volume &rhs) const noexcept
{
    return !(*this == rhs);
}

bool Volume::operator<(const Volume &rhs) const noexcept
{
    return Volume < rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit);
}

bool Volume::operator<=(const Volume &rhs) const noexcept
{
    return Volume <= rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit);
}

bool Volume::operator>(const Volume &rhs) const noexcept
{
    return Volume > rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit);
}

bool Volume::operator>=(const Volume &rhs) const noexcept
{
    return Volume >= rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit);
}

Volume Volume::operator-(const Volume &rhs) const noexcept
{
    Volume volume;
    volume.Volume = Volume - rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit);
    volume.Unit = Unit;
    return volume;
}

Volume Volume::operator+(const Volume &rhs) const noexcept
{
    Volume volume;
    volume.Volume = Volume + rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit);
    volume.Unit = Unit;
    return volume;
}

Volume &Volume::operator+=(const Volume &rhs) noexcept
{
    Volume += rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit);
    return *this;
}

Volume &Volume::operator-=(const Volume &rhs) noexcept
{
    Volume -= rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit);
    return *this;
}

Volume::operator double() const
{
    return Volume;
}

Volume Volume::ToCubicMeters(double vol, VolumeUnits units)
{
    Volume volume;
    volume.Volume = vol * Volume::ConvertScale(units, VolumeUnits::eCubicMeters);
    volume.Unit = VolumeUnits::eCubicMeters;
    return volume;
}

Volume Volume::ConvertTo(double vol, VolumeUnits srcUnit, VolumeUnits tagUnit)
{
    Volume volume;
    volume.Volume = vol * Volume::ConvertScale(srcUnit, tagUnit);
    volume.Unit = tagUnit;
    return volume;
}

double Volume::Meter3Volume(double a, VolumeUnits srcUnit, VolumeUnits tagUnit)
{
    return ConvertTo(a, srcUnit, tagUnit).Volume;
}

double Volume::ConvertScale(VolumeUnits from, VolumeUnits to)
{
    double factor1 = 1.0, factor2 = 1.0;
    switch (from)
    {
        case VolumeUnits::eCubicKilometers:
            factor1 = CubicKilometersToCubicMeter;
            break;
        case VolumeUnits::eCubicDecimeter:
            factor1 = CubicDecimeterToCubicMeter;
            break;
        case VolumeUnits::eCubicCentimeter:
            factor1 = CubicCentimeterToCubicMeter;
            break;
        case VolumeUnits::eCubicMillimeter:
            factor1 = CubicMillimeterToCubicMeter;
            break;
        case VolumeUnits::eLiter:
            factor1 = LiterToCubicMeter;
            break;
        case VolumeUnits::eDeciLiter:
            factor1 = DeciLiterToCubicMeter;
            break;
        case VolumeUnits::eMillLiter:
            factor1 = MillLiterToCubicMeter;
            break;
        case VolumeUnits::eAcreFoot:
            factor1 = AcreFootToCubicMeter;
            break;
        case VolumeUnits::eCubicYard:
            factor1 = CubicYardToCubicMeter;
            break;
        case VolumeUnits::eCubicFeet:
            factor1 = CubicFeetToCubicMeter;
            break;
        case VolumeUnits::eCubicInch:
            factor1 = CubicInchToCubicMeter;
            break;
        case VolumeUnits::eBarrel:
            factor1 = BarrelToCubicMeter;
            break;
        case VolumeUnits::eGallonUS:
            factor1 = GallonUSToCubicMeter;
            break;
        default:
            break;
    }


    switch (to)
    {
        case VolumeUnits::eCubicKilometers:
            factor1 = CubicMeterToCubicKilometers;
            break;
        case VolumeUnits::eCubicDecimeter:
            factor1 = CubicMeterToCubicDecimeter;
            break;
        case VolumeUnits::eCubicCentimeter:
            factor1 = CubicMeterToCubicCentimeter;
            break;
        case VolumeUnits::eCubicMillimeter:
            factor1 = CubicMeterToCubicMillimeter;
            break;
        case VolumeUnits::eLiter:
            factor1 = CubicMeterToLiter;
            break;
        case VolumeUnits::eDeciLiter:
            factor1 = CubicMeterToDeciLiter;
            break;
        case VolumeUnits::eMillLiter:
            factor1 = CubicMeterToMillLiter;
            break;
        case VolumeUnits::eAcreFoot:
            factor1 = CubicMeterToAcreFoot;
            break;
        case VolumeUnits::eCubicYard:
            factor1 = CubicMeterToCubicYard;
            break;
        case VolumeUnits::eCubicFeet:
            factor1 = CubicMeterToCubicFeet;
            break;
        case VolumeUnits::eCubicInch:
            factor1 = CubicMeterToCubicInch;
            break;
        case VolumeUnits::eBarrel:
            factor1 = CubicMeterToBarrel;
            break;
        case VolumeUnits::eGallonUS:
            factor1 = CubicMeterToGallonUS;
            break;
        default:
            break;
    }

    return factor1 * factor2;
}

}// namespace m2
