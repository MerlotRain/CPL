/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file unitsconverter.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "preconfig.h"

namespace Lite {
namespace Utility {


/// @brief 长度单位
enum class GsLengthUnits
{
    eKilometer,   //!< 千米
    eMeter,       //!< 米
    eDecimetre,   //!< 分米
    eCentimeter,  //!< 厘米
    eMillimeter,  //!< 毫米
    eMicron,      //!< 微米
    eNanometer,   //!< 纳米
    eInche,       //!< 英寸
    eMile,        //!< 英里
    eFeet,        //!< 英尺
    eYard,        //!< 码
    eNauticalMile,//!< 海里
    eZhang,       //!< 中国长度单位丈，≈3.33米
    eChi,         //!< 中国长度单位尺，≈3.33分米
    eCun,         //!< 中国长度单位寸，≈3.33厘米
    eFen,         //!< 中国长度单位分，≈3.33毫米
#ifdef SPATIAL_FEATURE
    eDegrees,//!< 度，用于空间参考测量使用，仅提供经验值，准确计算空间坐标换算相关模块处理
#endif
};


/// @brief 长度单位换算
struct UTILITY_EXPORT GsLength
{
    double Length = 0.0;
    GsLengthUnits Unit = GsLengthUnits::eMeter;

    /// @brief 默认构造
    GsLength() noexcept;
    /// @brief 拷贝构造
    /// @param rhs
    GsLength(const GsLength &rhs) noexcept;
    /// @brief 赋值复制构造
    /// @param
    /// @return
    GsLength &operator=(const GsLength &) noexcept;
    /// @brief 使用长度和单位构造
    /// @param len
    /// @param unit
    GsLength(double len, GsLengthUnits unit) noexcept;

    /// @brief 移动构造
    /// @param len
    GsLength(GsLength &&len) noexcept;
    /// @brief 赋值移动构造
    /// @param
    /// @return
    GsLength &operator=(GsLength &&) noexcept;
    /// @brief 交换
    /// @param l
    void Swap(GsLength &l) noexcept;

    /// @brief 重载==操作符
    /// @param
    /// @return
    bool operator==(const GsLength &) const noexcept;
    /// @brief 重载!=操作符
    /// @param
    /// @return
    bool operator!=(const GsLength &) const noexcept;
    /// @brief 重载<操作符
    /// @param
    /// @return
    bool operator<(const GsLength &) const noexcept;
    /// @brief 重载<=操作符
    /// @param
    /// @return
    bool operator<=(const GsLength &) const noexcept;
    /// @brief 重载>操作符
    /// @param
    /// @return
    bool operator>(const GsLength &) const noexcept;
    /// @brief 重载>=操作符
    /// @param
    /// @return
    bool operator>=(const GsLength &) const noexcept;

    /// @brief 重载-操作符
    /// @param
    /// @return
    GsLength operator-(const GsLength &) const noexcept;
    /// @brief 重载+操作符
    /// @param
    /// @return
    GsLength operator+(const GsLength &) const noexcept;
    /// @brief 重载+=操作符
    /// @param
    /// @return
    GsLength &operator+=(const GsLength &) noexcept;
    /// @brief 重载-=操作符
    /// @param
    /// @return
    GsLength &operator-=(const GsLength &) noexcept;

    /// @brief 重载 double 操作符
    operator double() const;

    /// @brief 转换成米单位
    /// @return
    inline GsLength ToMeter() const
    {
        return GsLength::ToMeter(Length, Unit);
    }
    /// @brief 转换成米单位
    /// @param len
    /// @param units
    /// @return
    static GsLength ToMeter(double len, GsLengthUnits units);
    /// @brief 单位换算
    /// @param units
    /// @return
    inline GsLength ConvertTo(GsLengthUnits units) const
    {
        return GsLength::ConvertTo(Length, Unit, units);
    }
    /// @brief 将一段长度从一个单位换算成另一个单位
    /// @param len
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static GsLength ConvertTo(double len, GsLengthUnits srcUnit, GsLengthUnits tagUnit);
    /// @brief 从一个长度单位转换到另一个长度单位的转换比率
    /// @param from
    /// @param to
    /// @return
    static double ConvertScale(GsLengthUnits from, GsLengthUnits to);
};


/// @brief 面积单位换算
enum class GsAreaUnits
{
    eKilometer2, //!< 平方千米km²
    eMeter2,     //!< 平方米m²
    ehm2,        //!< 公顷hm²
    eAre,        //!< 公亩
    eDecimetre2, //!< 平方分米dm²
    eCentimeter2,//!< 平方厘米cm²
    eMillimeter2,//!< 平方毫米mm²
    eAcre,       //!< 英亩
    eMile2,      //!< 平方英里mile²
    eYard2,      //!< 平方码yd²
    eFeet2,      //!< 平方英尺ft²
    eInche2,     //!< 平方英寸in²
    eRd2,        //!< 平方竿
    eQing,       //!< 中国面积单位顷
    eMu,         //!< 中国面积单位亩
    eFen,        //!< 中国面积单位分
#ifdef SPATIAL_FEATURE
    eDegrees,//!< 平方度，用于空间参考测量使用，仅提供经验值，准确计算空间坐标换算相关模块处理
#endif
};


/// @brief 面积单位换算
struct UTILITY_EXPORT GsArea
{
    double Area = 0.0;
    GsAreaUnits Unit = GsAreaUnits::eMeter2;

    /// @brief 默认构造
    GsArea() noexcept;
    /// @brief 拷贝构造
    /// @param rhs
    GsArea(const GsArea &rhs) noexcept;
    /// @brief 赋值复制构造
    /// @param
    /// @return
    GsArea &operator=(const GsArea &) noexcept;
    /// @brief 根据面积和单位构造
    /// @param a
    /// @param uint
    GsArea(double a, GsAreaUnits uint) noexcept;
    /// @brief 移动构造
    /// @param rhs
    GsArea(GsArea &&rhs) noexcept;
    /// @brief 复制移动构造
    /// @param rhs
    /// @return
    GsArea &operator=(GsArea &&rhs) noexcept;

    /// @brief 交换
    /// @param rhs
    void Swap(GsArea &rhs) noexcept;

    /// @brief 重载==操作符
    /// @param rhs
    /// @return
    bool operator==(const GsArea &rhs) const noexcept;
    /// @brief 重载!=操作符
    /// @param rhs
    /// @return
    bool operator!=(const GsArea &rhs) const noexcept;
    /// @brief 重载<操作符
    /// @param
    /// @return
    bool operator<(const GsArea &) const noexcept;
    /// @brief 重载<=操作符
    /// @param
    /// @return
    bool operator<=(const GsArea &) const noexcept;
    /// @brief 重载>操作符
    /// @param
    /// @return
    bool operator>(const GsArea &) const noexcept;
    /// @brief 重载>=操作符
    /// @param
    /// @return
    bool operator>=(const GsArea &) const noexcept;

    /// @brief 重载-操作符
    /// @param
    /// @return
    GsArea operator-(const GsArea &) const noexcept;
    /// @brief 重载+操作符
    /// @param
    /// @return
    GsArea operator+(const GsArea &) const noexcept;
    /// @brief 重载+=操作符
    /// @param
    /// @return
    GsArea &operator+=(const GsArea &) noexcept;
    /// @brief 重载-=操作符
    /// @param
    /// @return
    GsArea &operator-=(const GsArea &) noexcept;

    /// @brief 重载double操作符
    operator double() const;

    /// @brief 转化为平方米单位
    /// @return
    GsArea ToMeter2() const
    {
        return GsArea::ToMeter2(Area, Unit);
    }
    /// @brief 转换为平方米单位
    /// @param a
    /// @param units
    /// @return
    static GsArea ToMeter2(double a, GsAreaUnits units);
    /// @brief 转换为特定单位的面积
    /// @param units
    /// @return
    inline GsArea ConvertTo(GsAreaUnits units) const
    {
        return GsArea::ConvertTo(Area, Unit, units);
    }
    /// @brief 转换为特定单位的面积
    /// @param a
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static GsArea ConvertTo(double a, GsAreaUnits srcUnit, GsAreaUnits tagUnit);
    /// @brief 平方米的面积
    /// @return
    inline double Meter2Area() const
    {
        return GsArea::Meter2Area(Area, Unit, GsAreaUnits::eMeter2);
    }
    /// @brief 平方米的面积
    /// @param a
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static double Meter2Area(double a, GsAreaUnits srcUnit, GsAreaUnits tagUnit);

    /// @brief 从一个面积单位转换到另一个面积单位的转换比率
    /// @param from
    /// @param to
    /// @return
    static double ConvertScale(GsAreaUnits from, GsAreaUnits to);
};


/// @brief 常见体积单位
enum class GsVolumeUnits
{
    eCubicKilometers,//!< 立方千米
    eCubicMeters,    //!< 立方米
    eCubicDecimeter, //!< 立方分米
    eCubicCentimeter,//!< 立方厘米
    eCubicMillimeter,//!< 立方毫米
    eLiter,          //!< 升
    eDeciLiter,      //!< 分升
    eMillLiter,      //!< 毫升
    eAcreFoot,       //!< 亩英尺
    eCubicYard,      //!< 立方码
    eCubicFeet,      //!< 立方英尺
    eCubicInch,      //!< 立方英寸
    eBarrel,         //!< 桶
    eGallonUS,       //!< 加仑
};

/// @brief 体积
struct UTILITY_EXPORT GsVolume
{
    double Volume = 0.0;
    GsVolumeUnits Unit = GsVolumeUnits::eCubicMeters;

    /// @brief 默认构造
    GsVolume() noexcept;
    /// @brief 拷贝构造
    /// @param rhs
    GsVolume(const GsVolume &rhs) noexcept;
    /// @brief 赋值复制构造
    /// @param
    /// @return
    GsVolume &operator=(const GsVolume &) noexcept;
    /// @brief 根据体积和单位构造
    /// @param vol
    /// @param uints
    GsVolume(double vol, GsVolumeUnits uints) noexcept;
    /// @brief 移动构造
    /// @param vol
    GsVolume(GsVolume &&vol) noexcept;
    /// @brief 赋值移动构造
    /// @param
    /// @return
    GsVolume &operator=(GsVolume &&) noexcept;
    /// @brief 交换
    /// @param l
    void Swap(GsVolume &l) noexcept;

    /// @brief 重载==操作符
    /// @param
    /// @return
    bool operator==(const GsVolume &) const noexcept;
    /// @brief 重载!=操作符
    /// @param
    /// @return
    bool operator!=(const GsVolume &) const noexcept;
    /// @brief 重载<操作符
    /// @param
    /// @return
    bool operator<(const GsVolume &) const noexcept;
    /// @brief 重载<=操作符
    /// @param
    /// @return
    bool operator<=(const GsVolume &) const noexcept;
    /// @brief 重载>操作符
    /// @param
    /// @return
    bool operator>(const GsVolume &) const noexcept;
    /// @brief 重载>=操作符
    /// @param
    /// @return
    bool operator>=(const GsVolume &) const noexcept;

    /// @brief 重载-操作符
    /// @param
    /// @return
    GsVolume operator-(const GsVolume &) const noexcept;
    /// @brief 重载+操作符
    /// @param
    /// @return
    GsVolume operator+(const GsVolume &) const noexcept;
    /// @brief 重载+=操作符
    /// @param
    /// @return
    GsVolume &operator+=(const GsVolume &) noexcept;
    /// @brief 重载-=操作符
    /// @param
    /// @return
    GsVolume &operator-=(const GsVolume &) noexcept;

    /// @brief 重载double操作符
    operator double() const;
    /// @brief 转换成立方体单位
    /// @return
    GsVolume ToCubicMeters() const
    {
        return GsVolume::ToCubicMeters(Volume, Unit);
    }
    /// @brief 转换成立方体单位
    /// @param vol
    /// @param units
    /// @return
    static GsVolume ToCubicMeters(double vol, GsVolumeUnits units);

    /// @brief 从当前单位转换为指定单位
    /// @param units
    /// @return
    inline GsVolume ConvertTo(GsVolumeUnits units) const
    {
        return GsVolume::ConvertTo(Volume, Unit, units);
    }
    /// @brief 从当前单位转换为指定单位
    /// @param vol
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static GsVolume ConvertTo(double vol, GsVolumeUnits srcUnit, GsVolumeUnits tagUnit);

    /// @brief 转换成立方米的体积
    /// @return
    inline double Meter3Volume() const
    {
        return GsVolume::Meter3Volume(Volume, Unit, GsVolumeUnits::eCubicMeters);
    }
    /// @brief 转换成立方米的体积
    /// @param a
    /// @param srcUnit
    /// @param tagUnit
    /// @return
    static double Meter3Volume(double a, GsVolumeUnits srcUnit, GsVolumeUnits tagUnit);
    /// @brief 从一个体积单位转换到另一个体积单位的转换比率
    /// @param from
    /// @param to
    /// @return
    static double ConvertScale(GsVolumeUnits from, GsVolumeUnits to);
};


}// namespace Utility
}// namespace Lite
