#include <m2_math.h>
#include <m2_unitsconvertor.h>

namespace m2 {

/*******************************************************************************
 * class Length functions
 *******************************************************************************/

static constexpr auto MeterToKilometer = 0.001;
static constexpr auto MeterToDecimetre = 10;
static constexpr auto MeterToCentimeter = 100;
static constexpr auto MeterToMillimeter = 1000;
static constexpr auto MeterToMicron = 1000000;
static constexpr auto MeterToNanometer = 1000000000;
static constexpr auto MeterToInche = 39.3700787;
static constexpr auto MeterToMile = 0.0006214;
static constexpr auto MeterToFeet = 3.2808;
static constexpr auto MeterToYard = 1.0936;
static constexpr auto MeterToNauticalMile = 0.00054;
static constexpr auto MeterToZhang = 0.3;
static constexpr auto MeterToChi = 3;
static constexpr auto MeterToCun = 30;
static constexpr auto MeterToFen = 300;
static constexpr auto MeterToDegree = 1.0 / 111319.49079327358;

static constexpr auto KilometerToMeter = 1000;
static constexpr auto DecimetreToMeter = 0.1;
static constexpr auto CentimeterToMeter = 0.01;
static constexpr auto MillimeterToMeter = 0.001;
static constexpr auto MicronToMeter = 0.000001;
static constexpr auto NanometerToMeter = 0.000000001;
static constexpr auto IncheToMeter = 0.0254;
static constexpr auto MileToMeter = 1609.344;
static constexpr auto FeetToMeter = 0.3048;
static constexpr auto YardToMeter = 0.9144;
static constexpr auto NauticalMileToMeter = 1852;
static constexpr auto ZhangToMeter = 3.3333;
static constexpr auto ChiToMeter = 0.3333;
static constexpr auto CunToMeter = 0.0333;
static constexpr auto FenToMeter = 0.0033;
static constexpr auto DegreeToMeter = 111319.49079327358;

/**
 * @brief Construct a new Length:: Length object
 */
Length::Length() noexcept {}

/**
 * @brief Construct a new Length:: Length object
 * @param  rhs              
 */
Length::Length(const Length &rhs) noexcept : length(rhs.length), unit(rhs.unit)
{
}

/**
 * @brief 
 * @param  rhs              
 * @return Length& 
 */
Length &Length::operator=(const Length &rhs) noexcept
{
    length = rhs.length;
    unit = rhs.unit;
    return *this;
}

/**
 * @brief Construct a new Length:: Length object
 * @param  len              
 * @param  uints            
 */
Length::Length(double len, LengthUnits uints) noexcept
    : length(len), unit(uints)
{
}

/**
 * @brief Construct a new Length:: Length object
 * @param  rhs              
 */
Length::Length(Length &&rhs) noexcept
{
    length = std::move(rhs.length);
    unit = std::move(rhs.unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return Length& 
 */
Length &Length::operator=(Length &&rhs) noexcept
{
    length = std::move(rhs.length);
    unit = std::move(rhs.unit);
    return *this;
}

/**
 * @brief 
 * @param  rhs              
 */
void Length::swap(Length &rhs) noexcept
{
    std::swap(length, rhs.length);
    std::swap(unit, rhs.unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Length::operator==(const Length &rhs) const noexcept
{
    return qFuzzyCompare(length,
                         rhs.length * Length::convertScale(rhs.unit, unit));
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Length::operator!=(const Length &rhs) const noexcept
{
    return !(*this == rhs);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Length::operator<(const Length &rhs) const noexcept
{
    return length < rhs.length * Length::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Length::operator<=(const Length &rhs) const noexcept
{
    return length <= rhs.length * Length::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Length::operator>(const Length &rhs) const noexcept
{
    return length > rhs.length * Length::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Length::operator>=(const Length &rhs) const noexcept
{
    return length >= rhs.length * Length::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return Length 
 */
Length Length::operator-(const Length &rhs) const noexcept
{
    Length other;
    other.length = length - rhs.length * Length::convertScale(rhs.unit, unit);
    other.unit = unit;
    return other;
}

/**
 * @brief 
 * @param  rhs              
 * @return Length 
 */
Length Length::operator+(const Length &rhs) const noexcept
{
    Length other;
    other.length = length + rhs.length * Length::convertScale(rhs.unit, unit);
    other.unit = unit;
    return other;
}

/**
 * @brief 
 * @param  rhs              
 * @return Length& 
 */
Length &Length::operator+=(const Length &rhs) noexcept
{
    length += rhs.length * Length::convertScale(rhs.unit, unit);
    return *this;
}

/**
 * @brief 
 * @param  rhs              
 * @return Length& 
 */
Length &Length::operator-=(const Length &rhs) noexcept
{
    length -= rhs.length * Length::convertScale(rhs.unit, unit);
    return *this;
}

/**
 * @brief 
 * @return double 
 */
Length::operator double() const { return length; }

/**
 * @brief 
 * @param  l                
 * @param  units            
 * @return Length 
 */
Length Length::toMeter(double l, LengthUnits units)
{
    Length other;
    other.length = l * Length::convertScale(units, LengthUnits::eMeter);
    other.unit = LengthUnits::eMeter;
    return other;
}

/**
 * @brief 
 * @param  l                
 * @param  srcUnit          
 * @param  tagUnit          
 * @return Length 
 */
Length Length::convertTo(double l, LengthUnits srcUnit, LengthUnits tagUnit)
{
    Length other;
    other.length = l * Length::convertScale(srcUnit, tagUnit);
    other.unit = tagUnit;
    return other;
}

/**
 * @brief 
 * @param  from             
 * @param  to               
 * @return double 
 */
double Length::convertScale(LengthUnits from, LengthUnits to)
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

/*******************************************************************************
 * class Area functions
 *******************************************************************************/

static constexpr auto Meter2ToKilemeter2 = 0.000001;
static constexpr auto Meter2ToHm2 = 0.0001;
static constexpr auto Meter2ToAre = 0.01;
static constexpr auto Meter2ToDecimetre2 = 100.0;
static constexpr auto Meter2ToCentimeter2 = 10000.0;
static constexpr auto Meter2ToMillimeter2 = 1000000.0;
static constexpr auto Meter2ToAcre = 0.00025;
static constexpr auto Meter2ToMile2 = 0.00000039;
static constexpr auto Meter2ToYard2 = 1.196;
static constexpr auto Meter2ToFeet2 = 10.7639;
static constexpr auto Meter2ToInche2 = 1550.0031;
static constexpr auto Meter2ToRd2 = 0.0395;
static constexpr auto Meter2Toqing = 0.000015;
static constexpr auto Meter2Tomu = 0.0015;
static constexpr auto Meter2Tofen = 0.015;
static constexpr auto Meter2TofenDegrees = 1.0 / 12392029030.5;


static constexpr auto Kilemeter2ToMeter2 = 1000000.0;
static constexpr auto Hm2ToMeter2 = 10000.0;
static constexpr auto AreToMeter2 = 100.0;
static constexpr auto Decimetre2ToMeter2 = 0.01;
static constexpr auto Centimeter2ToMeter2 = 0.0001;
static constexpr auto Millimeter2ToMeter2 = 0.000001;
static constexpr auto AcreToMeter2 = 4046.8648;
static constexpr auto Mile2ToMeter2 = 2589988.1103;
static constexpr auto Yard2ToMeter2 = 0.8361;
static constexpr auto Feet2ToMeter2 = 0.0929;
static constexpr auto Inche2ToMeter2 = 0.00065;
static constexpr auto Rd2ToMeter2 = 25.2929;
static constexpr auto qingToMeter2 = 66666.6667;
static constexpr auto muToMeter2 = 666.6667;
static constexpr auto fenToMeter2 = 66.6667;
static constexpr auto DegreesToMeter2 = 12392029030.5;

/**
 * @brief Construct a new Area:: Area object
 */
Area::Area() noexcept {}

/**
 * @brief Construct a new Area:: Area object
 * @param  rhs              
 */
Area::Area(const Area &rhs) noexcept : area(rhs.area), unit(rhs.unit) {}

/**
 * @brief 
 * @param  rhs              
 * @return Area& 
 */
Area &Area::operator=(const Area &rhs) noexcept
{
    area = rhs.area;
    unit = rhs.unit;
    return *this;
}

/**
 * @brief Construct a new Area:: Area object
 * @param  a                
 * @param  unit             
 */
Area::Area(double a, AreaUnits unit) noexcept : area(a), unit(unit) {}

/**
 * @brief Construct a new Area:: Area object
 * @param  rhs              
 */
Area::Area(Area &&rhs) noexcept
{
    area = std::move(rhs.area);
    unit = std::move(rhs.unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return Area& 
 */
Area &Area::operator=(Area &&rhs) noexcept
{
    area = std::move(rhs.area);
    unit = std::move(rhs.unit);
    return *this;
}

/**
 * @brief 
 * @param  rhs              
 */
void Area::swap(Area &rhs) noexcept
{
    std::swap(area, rhs.area);
    std::swap(unit, rhs.unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Area::operator==(const Area &rhs) const noexcept
{
    return qFuzzyCompare(area, rhs.area * Area::convertScale(rhs.unit, unit));
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Area::operator!=(const Area &rhs) const noexcept
{
    return !(*this == rhs);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Area::operator<(const Area &rhs) const noexcept
{
    return area < rhs.area * Area::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Area::operator<=(const Area &rhs) const noexcept
{
    return area <= rhs.area * Area::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Area::operator>(const Area &rhs) const noexcept
{
    return area > rhs.area * Area::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Area::operator>=(const Area &rhs) const noexcept
{
    return area >= rhs.area * Area::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return Area 
 */
Area Area::operator-(const Area &rhs) const noexcept
{
    Area other;
    other.area = area - rhs.area * Area::convertScale(rhs.unit, unit);
    other.unit = unit;
    return other;
}

/**
 * @brief 
 * @param  rhs              
 * @return Area 
 */
Area Area::operator+(const Area &rhs) const noexcept
{
    Area other;
    other.area = area + rhs.area * Area::convertScale(rhs.unit, unit);
    other.unit = unit;
    return other;
}

/**
 * @brief 
 * @param  rhs              
 * @return Area& 
 */
Area &Area::operator+=(const Area &rhs) noexcept
{
    area += rhs.area * Area::convertScale(rhs.unit, unit);
    return *this;
}

/**
 * @brief 
 * @param  rhs              
 * @return Area& 
 */
Area &Area::operator-=(const Area &rhs) noexcept
{
    area -= rhs.area * Area::convertScale(rhs.unit, unit);
    return *this;
}

/**
 * @brief 
 * @return double 
 */
Area::operator double() const { return area; }

/**
 * @brief 
 * @param  a                
 * @param  units            
 * @return Area 
 */
Area Area::toMeter2(double a, AreaUnits units)
{
    Area area;
    area.area = a * Area::convertScale(units, AreaUnits::eMeter2);
    area.unit = AreaUnits::eMeter2;
    return area;
}

/**
 * @brief 
 * @param  a                
 * @param  srcUnit          
 * @param  tagUnit          
 * @return Area 
 */
Area Area::convertTo(double a, AreaUnits srcUnit, AreaUnits tagUnit)
{
    Area area;
    area.area = a * Area::convertScale(srcUnit, tagUnit);
    area.unit = tagUnit;
    return area;
}

/**
 * @brief 
 * @param  a                
 * @param  srcUnit          
 * @param  tagUnit          
 * @return double 
 */
double Area::meter2Area(double a, AreaUnits srcUnit, AreaUnits tagUnit)
{
    return convertTo(a, srcUnit, tagUnit).area;
}

/**
 * @brief 
 * @param  from             
 * @param  to               
 * @return double 
 */
double Area::convertScale(AreaUnits from, AreaUnits to)
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

/*******************************************************************************
 * class Volume functions
 *******************************************************************************/

static constexpr auto CubicMeterToCubicKilometers = 0;
static constexpr auto CubicMeterToCubicDecimeter = 0;
static constexpr auto CubicMeterToCubicCentimeter = 0;
static constexpr auto CubicMeterToCubicMillimeter = 0;
static constexpr auto CubicMeterToLiter = 0;
static constexpr auto CubicMeterToDeciLiter = 0;
static constexpr auto CubicMeterToMillLiter = 0;
static constexpr auto CubicMeterToAcreFoot = 0;
static constexpr auto CubicMeterToCubicYard = 0;
static constexpr auto CubicMeterToCubicFeet = 0;
static constexpr auto CubicMeterToCubicInch = 0;
static constexpr auto CubicMeterToBarrel = 0;
static constexpr auto CubicMeterToGallonUS = 0;

static constexpr auto CubicKilometersToCubicMeter = 0;
static constexpr auto CubicDecimeterToCubicMeter = 0;
static constexpr auto CubicCentimeterToCubicMeter = 0;
static constexpr auto CubicMillimeterToCubicMeter = 0;
static constexpr auto LiterToCubicMeter = 0;
static constexpr auto DeciLiterToCubicMeter = 0;
static constexpr auto MillLiterToCubicMeter = 0;
static constexpr auto AcreFootToCubicMeter = 0;
static constexpr auto CubicYardToCubicMeter = 0;
static constexpr auto CubicFeetToCubicMeter = 0;
static constexpr auto CubicInchToCubicMeter = 0;
static constexpr auto BarrelToCubicMeter = 0;
static constexpr auto GallonUSToCubicMeter = 0;

/**
 * @brief Construct a new Volume:: Volume object
 */
Volume::Volume() noexcept {}

/**
 * @brief Construct a new Volume:: Volume object
 * @param  rhs              
 */
Volume::Volume(const Volume &rhs) noexcept : volume(rhs.volume), unit(rhs.unit)
{
}

/**
 * @brief 
 * @param  rhs              
 * @return Volume& 
 */
Volume &Volume::operator=(const Volume &rhs) noexcept
{
    volume = rhs.volume;
    unit = rhs.unit;
    return *this;
}

/**
 * @brief Construct a new Volume:: Volume object
 * @param  vol              
 * @param  uints            
 */
Volume::Volume(double vol, VolumeUnits uints) noexcept
    : volume(vol), unit(uints)
{
}

/**
 * @brief Construct a new Volume:: Volume object
 * @param  rhs              
 */
Volume::Volume(Volume &&rhs) noexcept
{
    volume = std::move(rhs.volume);
    unit = std::move(rhs.unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return Volume& 
 */
Volume &Volume::operator=(Volume &&rhs) noexcept
{
    volume = std::move(rhs.volume);
    unit = std::move(rhs.unit);
    return *this;
}

/**
 * @brief 
 * @param  rhs              
 */
void Volume::swap(Volume &rhs) noexcept
{
    std::swap(volume, rhs.volume);
    std::swap(unit, rhs.unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Volume::operator==(const Volume &rhs) const noexcept
{
    return qFuzzyCompare(volume,
                         rhs.volume * Volume::convertScale(rhs.unit, unit));
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Volume::operator!=(const Volume &rhs) const noexcept
{
    return !(*this == rhs);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Volume::operator<(const Volume &rhs) const noexcept
{
    return volume < rhs.volume * Volume::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Volume::operator<=(const Volume &rhs) const noexcept
{
    return volume <= rhs.volume * Volume::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Volume::operator>(const Volume &rhs) const noexcept
{
    return volume > rhs.volume * Volume::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool Volume::operator>=(const Volume &rhs) const noexcept
{
    return volume >= rhs.volume * Volume::convertScale(rhs.unit, unit);
}

/**
 * @brief 
 * @param  rhs              
 * @return Volume 
 */
Volume Volume::operator-(const Volume &rhs) const noexcept
{
    Volume other;
    other.volume = volume - rhs.volume * Volume::convertScale(rhs.unit, unit);
    other.unit = unit;
    return other;
}

/**
 * @brief 
 * @param  rhs              
 * @return Volume 
 */
Volume Volume::operator+(const Volume &rhs) const noexcept
{
    Volume other;
    other.volume = volume + rhs.volume * Volume::convertScale(rhs.unit, unit);
    other.unit = unit;
    return other;
}

/**
 * @brief 
 * @param  rhs              
 * @return Volume& 
 */
Volume &Volume::operator+=(const Volume &rhs) noexcept
{
    volume += rhs.volume * Volume::convertScale(rhs.unit, unit);
    return *this;
}

/**
 * @brief 
 * @param  rhs              
 * @return Volume& 
 */
Volume &Volume::operator-=(const Volume &rhs) noexcept
{
    volume -= rhs.volume * Volume::convertScale(rhs.unit, unit);
    return *this;
}

/**
 * @brief 
 * @return double 
 */
Volume::operator double() const { return volume; }

/**
 * @brief 
 * @param  vol              
 * @param  units            
 * @return Volume 
 */
Volume Volume::toCubicMeters(double vol, VolumeUnits units)
{
    Volume other;
    other.volume = vol * Volume::convertScale(units, VolumeUnits::eCubicMeters);
    other.unit = VolumeUnits::eCubicMeters;
    return other;
}

/**
 * @brief 
 * @param  vol              
 * @param  srcUnit          
 * @param  tagUnit          
 * @return Volume 
 */
Volume Volume::convertTo(double vol, VolumeUnits srcUnit, VolumeUnits tagUnit)
{
    Volume other;
    other.volume = vol * Volume::convertScale(srcUnit, tagUnit);
    other.unit = tagUnit;
    return other;
}

/**
 * @brief 
 * @param  a                
 * @param  srcUnit          
 * @param  tagUnit          
 * @return double 
 */
double Volume::meter3Volume(double a, VolumeUnits srcUnit, VolumeUnits tagUnit)
{
    return convertTo(a, srcUnit, tagUnit).volume;
}

/**
 * @brief 
 * @param  from             
 * @param  to               
 * @return double 
 */
double Volume::convertScale(VolumeUnits from, VolumeUnits to)
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
