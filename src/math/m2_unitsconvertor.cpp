#include <m2_unitsconvertor.h>

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


Area::Area() noexcept {}

Area::Area(const Area &rhs) noexcept : Area(rhs.Area), Unit(rhs.Unit) {}

Area &Area::operator=(const Area &rhs) noexcept
{
    Area = rhs.Area;
    Unit = rhs.Unit;
    return *this;
}

Area::Area(double a, AreaUnits unit) noexcept : Area(a), Unit(unit) {}

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
    return Math::FuzzyCompare(Area,
                              rhs.Area * Area::ConvertScale(rhs.Unit, Unit));
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

Area::operator double() const { return Area; }

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


Length::Length() noexcept {}

Length::Length(const Length &rhs) noexcept : Length(rhs.Length), Unit(rhs.Unit)
{
}

Length &Length::operator=(const Length &rhs) noexcept
{
    Length = rhs.Length;
    Unit = rhs.Unit;
    return *this;
}

Length::Length(double len, LengthUnits uints) noexcept
    : Length(len), Unit(uints)
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
    return Math::FuzzyCompare(
            Length, rhs.Length * Length::ConvertScale(rhs.Unit, Unit));
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

Length::operator double() const { return Length; }

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

Volume::Volume() noexcept {}

Volume::Volume(const Volume &rhs) noexcept : Volume(rhs.Volume), Unit(rhs.Unit)
{
}

Volume &Volume::operator=(const Volume &rhs) noexcept
{
    Volume = rhs.Volume;
    Unit = rhs.Unit;
    return *this;
}

Volume::Volume(double vol, VolumeUnits uints) noexcept
    : Volume(vol), Unit(uints)
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
    return Math::FuzzyCompare(
            Volume, rhs.Volume * Volume::ConvertScale(rhs.Unit, Unit));
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

Volume::operator double() const { return Volume; }

Volume Volume::ToCubicMeters(double vol, VolumeUnits units)
{
    Volume volume;
    volume.Volume =
            vol * Volume::ConvertScale(units, VolumeUnits::eCubicMeters);
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
