/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#ifndef M2_UNITSCONVERTOR_H
#define M2_UNITSCONVERTOR_H

#include <preconfig.h>

namespace m2 {

class M2_API Length
{
public:
    enum LengthUnits
    {
        eKilometer,
        eMeter,
        eDecimetre,
        eCentimeter,
        eMillimeter,
        eMicron,
        eNanometer,
        eInche,
        eMile,
        eFeet,
        eYard,
        eNauticalMile,
        eZhang,
        eChi,
        eCun,
        eFen,
#ifdef SPATIAL_FEATURE
        eDegrees,
#endif
    };

    constexpr Length() noexcept;
    constexpr Length(const Length &rhs) noexcept;
    constexpr Length &operator=(const Length &) noexcept;
    constexpr Length(Length &&) noexcept;
    constexpr Length &operator=(Length &&) noexcept;
    constexpr Length(double len, LengthUnits unit) noexcept;
    void swap(Length &l) noexcept;

    constexpr inline bool operator==(const Length &) const noexcept;
    constexpr inline bool operator!=(const Length &) const noexcept;
    constexpr inline bool operator<(const Length &) const noexcept;
    constexpr inline bool operator<=(const Length &) const noexcept;
    constexpr inline bool operator>(const Length &) const noexcept;
    constexpr inline bool operator>=(const Length &) const noexcept;
    constexpr inline Length operator-(const Length &) const noexcept;
    constexpr inline Length operator+(const Length &) const noexcept;
    constexpr inline Length &operator+=(const Length &) noexcept;
    constexpr inline Length &operator-=(const Length &) noexcept;

    operator double() const;

    inline Length toMeter() const;
    static Length toMeter(double len, LengthUnits units);
    inline Length convertTo(LengthUnits units) const;
    static Length convertTo(double len, LengthUnits srcUnit, LengthUnits tagUnit);
    static double convertScale(LengthUnits from, LengthUnits to);

private:
    double length = 0.0;
    LengthUnits unit;
};

class M2_API Area
{
public:
    enum AreaUnits
    {
        eKilometer2,
        eMeter2,
        ehm2,
        eAre,
        eDecimetre2,
        eCentimeter2,
        eMillimeter2,
        eAcre,
        eMile2,
        eYard2,
        eFeet2,
        eInche2,
        eRd2,
        eQing,
        eMu,
        eFen,
#ifdef SPATIAL_FEATURE
        eDegree2,
#endif
    };

    constexpr Area() noexcept;
    constexpr Area(const Area &rhs) noexcept;
    constexpr Area &operator=(const Area &) noexcept;
    constexpr Area(double a, AreaUnits uint) noexcept;
    constexpr Area(Area &&rhs) noexcept;
    constexpr Area &operator=(Area &&rhs) noexcept;
    void swap(Area &rhs) noexcept;
    constexpr inline bool operator==(const Area &rhs) const noexcept;
    constexpr inline bool operator!=(const Area &rhs) const noexcept;
    constexpr inline bool operator<(const Area &) const noexcept;
    constexpr inline bool operator<=(const Area &) const noexcept;
    constexpr inline bool operator>(const Area &) const noexcept;
    constexpr inline bool operator>=(const Area &) const noexcept;

    constexpr inline Area operator-(const Area &) const noexcept;
    constexpr inline Area operator+(const Area &) const noexcept;
    constexpr inline Area &operator+=(const Area &) noexcept;
    constexpr inline Area &operator-=(const Area &) noexcept;

    operator double() const;

    inline Area toMeter2() const;
    inline Area convertTo(AreaUnits units) const;
    inline double meter2Area() const;

    static Area toMeter2(double a, AreaUnits units);
    static Area convertTo(double a, AreaUnits srcUnit, AreaUnits tagUnit);
    static double meter2Area(double a, AreaUnits srcUnit, AreaUnits tagUnit);
    static double convertScale(AreaUnits from, AreaUnits to);

private:
    double area = 0.0;
    AreaUnits unit;
};

class M2_API Volume
{
public:
    enum VolumeUnits
    {
        eCubicKilometers,
        eCubicMeters,
        eCubicDecimeter,
        eCubicCentimeter,
        eCubicMillimeter,
        eLiter,
        eDeciLiter,
        eMillLiter,
        eAcreFoot,
        eCubicYard,
        eCubicFeet,
        eCubicInch,
        eBarrel,
        eGallonUS,
    };

    constexpr Volume() noexcept;
    constexpr Volume(const Volume &rhs) noexcept;
    constexpr Volume &operator=(const Volume &) noexcept;
    constexpr Volume(double vol, VolumeUnits uints) noexcept;
    constexpr Volume(Volume &&vol) noexcept;
    constexpr Volume &operator=(Volume &&) noexcept;
    void swap(Volume &l) noexcept;

    constexpr inline bool operator==(const Volume &) const noexcept;
    constexpr inline bool operator!=(const Volume &) const noexcept;
    constexpr inline bool operator<(const Volume &) const noexcept;
    constexpr inline bool operator<=(const Volume &) const noexcept;
    constexpr inline bool operator>(const Volume &) const noexcept;
    constexpr inline bool operator>=(const Volume &) const noexcept;
    constexpr inline Volume operator-(const Volume &) const noexcept;
    constexpr inline Volume operator+(const Volume &) const noexcept;
    constexpr inline Volume &operator+=(const Volume &) noexcept;
    constexpr inline Volume &operator-=(const Volume &) noexcept;

    operator double() const;

    inline Volume toCubicMeters() const;
    inline Volume convertTo(VolumeUnits units) const;
    inline double meter3Volume() const;

    static Volume toCubicMeters(double vol, VolumeUnits units);
    static Volume convertTo(double vol, VolumeUnits srcUnit, VolumeUnits tagUnit);
    static double meter3Volume(double a, VolumeUnits srcUnit, VolumeUnits tagUnit);
    static double convertScale(VolumeUnits from, VolumeUnits to);

private:
    double volume = 0.0;
    VolumeUnits unit;
};

/*****************************************************************************
  Length inline functions
 *****************************************************************************/

inline Length Length::toMeter() const
{
    return Length::toMeter(length, unit);
}

inline Length Length::convertTo(LengthUnits units) const
{
    return Length::convertTo(length, unit, units);
}

/*****************************************************************************
  Area inline functions
 *****************************************************************************/

inline Area Area::toMeter2() const
{
    return Area::toMeter2(area, unit);
}

inline Area Area::convertTo(AreaUnits units) const
{
    return Area::convertTo(area, unit, units);
}

inline double Area::meter2Area() const
{
    return Area::meter2Area(area, unit, AreaUnits::eMeter2);
}

/*****************************************************************************
  Volume inline functions
 *****************************************************************************/

inline Volume Volume::toCubicMeters() const
{
    return Volume::toCubicMeters(volume, unit);
}

inline Volume Volume::convertTo(VolumeUnits units) const
{
    return Volume::convertTo(volume, unit, units);
}

inline double Volume::meter3Volume() const
{
    return Volume::meter3Volume(volume, unit, VolumeUnits::eCubicMeters);
}

}// namespace m2

#endif//M2_UNITSCONVERTOR_H