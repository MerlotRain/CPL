#include <m2_colorramp.h>

namespace m2 {

/*******************************************************************************
 * class ColorRamp functions
 *******************************************************************************/

/**
 * @brief 
 * @return std::list<std::pair<String, String>> 
 */
std::list<std::pair<String, String>> ColorRamp::rampTypes()
{
    return std::list<std::pair<String, String>>();
}

/*******************************************************************************
 * class LimitedRandomColorRamp functions
 *******************************************************************************/

/**
 * @brief Construct a new Gradient Color Ramp:: Gradient Color Ramp object
 * @param  color1           
 * @param  color2           
 * @param  discrete         
 * @param  stops            
 */
GradientColorRamp::GradientColorRamp(const Color &color1, const Color &color2,
                                     bool discrete,
                                     const GradientStopsList &stops)
{
}

/**
 * @brief 
 * @param  properties       
 * @return ColorRamp* 
 */
ColorRamp *GradientColorRamp::create(const VariantMap &properties)
{
    return nullptr;
}

/**
 * @brief 
 * @return int 
 */
int GradientColorRamp::count() const { return 0; }

/**
 * @brief 
 * @param  index            
 * @return double 
 */
double GradientColorRamp::value(int index) const { return 0.0; }

/**
 * @brief 
 * @param  value            
 * @return Color 
 */
Color GradientColorRamp::color(double value) const { return Color(); }

/**
 * @brief 
 * @return String 
 */
String GradientColorRamp::typeString() { return String(); }

/**
 * @brief 
 * @return String 
 */
String GradientColorRamp::type() const { return String(); }

/**
 * @brief 
 */
void GradientColorRamp::invert() {}

/**
 * @brief 
 * @return GradientColorRamp* 
 */
GradientColorRamp *GradientColorRamp::clone() const { return nullptr; }

/**
 * @brief 
 * @return VariantMap 
 */
VariantMap GradientColorRamp::properties() const { return VariantMap(); }

/**
 * @brief 
 * @return Color 
 */
Color GradientColorRamp::color1() const { return Color(); }

/**
 * @brief 
 * @return Color 
 */
Color GradientColorRamp::color2() const { return Color(); }

/**
 * @brief 
 * @param  color            
 */
void GradientColorRamp::setColor1(const Color &color) {}

/**
 * @brief 
 * @param  color            
 */
void GradientColorRamp::setColor2(const Color &color) {}

/**
 * @brief 
 * @return true 
 * @return false 
 */
bool GradientColorRamp::isDiscrete() const { return false; }

/**
 * @brief 
 * @param  discrete         
 */
void GradientColorRamp::setDiscrete(bool discrete) {}

/**
 * @brief 
 * @param  discrete         
 */
void GradientColorRamp::convertToDiscrete(bool discrete) {}

/**
 * @brief 
 * @param  stops            
 */
void GradientColorRamp::setStops(const GradientStopsList &stops) {}

/**
 * @brief 
 * @return GradientStopsList 
 */
GradientStopsList GradientColorRamp::stops() const
{
    return GradientStopsList();
}

/**
 * @brief 
 * @return std::map<String, String> 
 */
std::map<String, String> GradientColorRamp::info() const
{
    return std::map<String, String>();
}

/**
 * @brief 
 * @param  info             
 */
void GradientColorRamp::setInfo(const std::map<String, String> &info) {}

/**
 * @brief 
 * @return Color::Spec 
 */
Color::Spec GradientColorRamp::colorSpec() const { return Color::Spec(); }

/**
 * @brief 
 * @param  spec             
 */
void GradientColorRamp::setColorSpec(Color::Spec spec) {}

/**
 * @brief 
 * @return AngularDirection 
 */
AngularDirection GradientColorRamp::direction() const
{
    return AngularDirection();
}

/**
 * @brief 
 * @param  direction        
 */
void GradientColorRamp::setDirection(AngularDirection direction) {}

/*******************************************************************************
 * class LimitedRandomColorRamp functions
 *******************************************************************************/

/**
 * @brief Construct a new Limited Random Color Ramp:: Limited Random Color Ramp object
 * @param  count            
 * @param  hueMin           
 * @param  hueMax           
 * @param  satMin           
 * @param  satMax           
 * @param  valMin           
 * @param  valMax           
 */
LimitedRandomColorRamp::LimitedRandomColorRamp(int count, int hueMin,
                                               int hueMax, int satMin,
                                               int satMax, int valMin,
                                               int valMax)
{
}

/**
 * @brief 
 * @param  properties       
 * @return ColorRamp* 
 */
ColorRamp *LimitedRandomColorRamp::create(const VariantMap &properties)
{
    return nullptr;
}

/**
 * @brief 
 * @param  index            
 * @return double 
 */
double LimitedRandomColorRamp::value(int index) const { return 0.0; }

/**
 * @brief 
 * @param  value            
 * @return Color 
 */
Color LimitedRandomColorRamp::color(double value) const { return Color(); }

/**
 * @brief 
 * @return String 
 */
String LimitedRandomColorRamp::typeString() { return String(); }

/**
 * @brief 
 * @return String 
 */
String LimitedRandomColorRamp::type() const { return String(); }

/**
 * @brief 
 * @return LimitedRandomColorRamp* 
 */
LimitedRandomColorRamp *LimitedRandomColorRamp::clone() const
{
    return nullptr;
}

/**
 * @brief 
 * @return VariantMap 
 */
VariantMap LimitedRandomColorRamp::properties() const { return VariantMap(); }

/**
 * @brief 
 * @return int 
 */
int LimitedRandomColorRamp::count() const { return 0; }

/**
 * @brief 
 * @param  count            
 * @param  hueMax           
 * @param  hueMin           
 * @param  satMax           
 * @param  satMin           
 * @param  valMax           
 * @param  valMin           
 * @return std::list<Color> 
 */
std::list<Color> LimitedRandomColorRamp::randomColors(int count, int hueMax,
                                                      int hueMin, int satMax,
                                                      int satMin, int valMax,
                                                      int valMin)
{
    return std::list<Color>();
}

/**
 * @brief 
 */
void LimitedRandomColorRamp::updateColors() {}

/**
 * @brief 
 * @return int 
 */
int LimitedRandomColorRamp::hueMin() const { return 0; }

/**
 * @brief 
 * @return int 
 */
int LimitedRandomColorRamp::hueMax() const { return 0; }

/**
 * @brief 
 * @return int 
 */
int LimitedRandomColorRamp::satMin() const { return 0; }

/**
 * @brief 
 * @return int 
 */
int LimitedRandomColorRamp::satMax() const { return 0; }

/**
 * @brief 
 * @return int 
 */
int LimitedRandomColorRamp::valMin() const { return 0; }

/**
 * @brief 
 * @return int 
 */
int LimitedRandomColorRamp::valMax() const { return 0; }

/**
 * @brief 
 * @param  val              
 */
void LimitedRandomColorRamp::setCount(int val) {}

/**
 * @brief 
 * @param  val              
 */
void LimitedRandomColorRamp::setHueMin(int val) {}

/**
 * @brief 
 * @param  val              
 */
void LimitedRandomColorRamp::setHueMax(int val) {}

/**
 * @brief 
 * @param  val              
 */
void LimitedRandomColorRamp::setSatMin(int val) {}

/**
 * @brief 
 * @param  val              
 */
void LimitedRandomColorRamp::setSatMax(int val) {}

/**
 * @brief 
 * @param  val              
 */
void LimitedRandomColorRamp::setValMin(int val) {}

/**
 * @brief 
 * @param  val              
 */
void LimitedRandomColorRamp::setValMax(int val) {}

/*******************************************************************************
 * class RandomColorRamp functions
 *******************************************************************************/

/**
 * @brief 
 * @return int 
 */
int RandomColorRamp::count() const { return 0; }

/**
 * @brief 
 * @param  index            
 * @return double 
 */
double RandomColorRamp::value(int index) const { return 0.0; }

/**
 * @brief 
 * @param  colorCount       
 */
void RandomColorRamp::setTotalColorCount(int colorCount) {}

/**
 * @brief 
 * @return String 
 */
String RandomColorRamp::typeString() { return String(); }

/**
 * @brief 
 * @return String 
 */
String RandomColorRamp::type() const { return String(); }

/**
 * @brief 
 * @return RandomColorRamp* 
 */
RandomColorRamp *RandomColorRamp::clone() const { return nullptr; }

/**
 * @brief 
 * @return VariantMap 
 */
VariantMap RandomColorRamp::properties() const { return VariantMap(); }

}// namespace m2