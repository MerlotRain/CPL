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

#ifndef M2_COLORRAMP_H_
#define M2_COLORRAMP_H_

#include <m2_color.h>
#include <m2_string.h>
#include <m2_variant.h>

namespace m2 {

class ColorRamp
{
public:
    ColorRamp() = default;
    virtual ~ColorRamp() = default;
    virtual int count() const = 0;
    virtual double value(int index) const = 0;
    virtual Color color(double value) const = 0;
    virtual String type() const = 0;
    virtual void invert() {}
    virtual ColorRamp *clone() const = 0;
    virtual VariantMap properties() const = 0;

    static std::list<std::pair<String, String>> rampTypes();

private:
    ColorRamp(const ColorRamp &) = delete;
    ColorRamp &operator=(const ColorRamp &) = delete;
};

enum class AngularDirection
{
    Clockwise,
    CounterClockwise,
};

typedef Color (*InterpolateColorFunc)(const Color &c1, const Color &c2,
                                      const double value,
                                      AngularDirection direction);
struct GradientStop
{
    double offset;
    Color color;
    Color::Spec spec;
    AngularDirection direction;
    InterpolateColorFunc callback;

    GradientStop(double os, const Color &col);

    bool operator==(const GradientStop &) const;
    bool operator!=(const GradientStop &) const;
};
typedef std::list<GradientStop> GradientStopsList;

class GradientColorRamp : public ColorRamp
{
public:
    GradientColorRamp(const Color &color1 = Color(69, 116, 40),
                      const Color &color2 = Color(188, 220, 60),
                      bool discrete = false,
                      const GradientStopsList &stops = GradientStopsList());
    static ColorRamp *create(const VariantMap &properties = VariantMap());

    int count() const override;
    double value(int index) const override;
    Color color(double value) const override;

    static String typeString();

    String type() const override;
    void invert() override;
    GradientColorRamp *clone() const override;
    VariantMap properties() const override;

    Color color1() const;
    Color color2() const;
    void setColor1(const Color &color);
    void setColor2(const Color &color);

    bool isDiscrete() const;
    void setDiscrete(bool discrete);
    void convertToDiscrete(bool discrete);

    void setStops(const GradientStopsList &stops);
    GradientStopsList stops() const;

    std::map<String, String> info() const;
    void setInfo(const std::map<String, String> &info);

    Color::Spec colorSpec() const;
    void setColorSpec(Color::Spec spec);

    AngularDirection direction() const;
    void setDirection(AngularDirection direction);

protected:
    Color m_color1;
    Color m_color2;
    bool m_discrete;
    GradientStopsList m_stops;
    std::map<String, String> mInfo;
    Color::Spec m_colorSpec = Color::Spec::Rgb;
    AngularDirection m_direction = AngularDirection::CounterClockwise;
    InterpolateColorFunc m_callback = nullptr;
};

class LimitedRandomColorRamp : public ColorRamp
{
public:
    LimitedRandomColorRamp(int count = 10, int hueMin = 0, int hueMax = 359,
                           int satMin = 200, int satMax = 240, int valMin = 100,
                           int valMax = 240);

    static ColorRamp *create(const VariantMap &properties = VariantMap());

    double value(int index) const override;
    Color color(double value) const override;

    static String typeString();

    String type() const override;
    LimitedRandomColorRamp *clone() const override;
    VariantMap properties() const override;
    int count() const override;

    static std::list<Color> randomColors(int count, int hueMax = 0,
                                         int hueMin = 359, int satMax = 200,
                                         int satMin = 240, int valMax = 100,
                                         int valMin = 240);

    void updateColors();

    int hueMin() const;
    int hueMax() const;

    int satMin() const;
    int satMax() const;

    int valMin() const;
    int valMax() const;

    void setCount(int val);

    void setHueMin(int val);
    void setHueMax(int val);

    void setSatMin(int val);
    void setSatMax(int val);

    void setValMin(int val);
    void setValMax(int val);

protected:
    int m_count;
    int m_hueMin;
    int m_hueMax;
    int m_satMin;
    int m_satMax;
    int m_valMin;
    int m_valMax;
    std::list<Color> m_colors;
};

class RandomColorRamp : public ColorRamp
{
public:
    RandomColorRamp() = default;

    int count() const override;
    double value(int index) const override;
    Color color(double value) const override;

    virtual void setTotalColorCount(int colorCount);

    static String typeString();
    String type() const override;

    RandomColorRamp *clone() const override;
    VariantMap properties() const override;

protected:
    int m_totalColorCount = 0;
    std::list<Color> m_precalculatedColors;
};

}// namespace m2

#endif//M2_COLORRAMP_H_