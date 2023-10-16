#include <m2_circle.h>
#include <m2_triangle.h>

namespace m2 {

/**
 * @brief Construct a new Triangle:: Triangle object
 * 
 */
Triangle::Triangle() {}

/**
 * @brief Construct a new Triangle:: Triangle object
 * 
 * @param p1 
 * @param p2 
 * @param p3 
 */
Triangle::Triangle(const PointF &p1, const PointF &p2, const PointF &p3) {}

/**
 * @brief Construct a new Triangle:: Triangle object
 * 
 * @param other 
 */
Triangle::Triangle(const Triangle &other) {}

/**
 * @brief 
 * 
 * @param other 
 * @return Triangle& 
 */
Triangle &Triangle::operator=(const Triangle &other)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Triangle::operator==(const Triangle &other) const { return false; }

/**
 * @brief 
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Triangle::operator!=(const Triangle &other) const { return false; }

/**
 * @brief 
 * 
 * @return std::vector<double> 
 */
std::vector<double> Triangle::lengths() const { return std::vector<double>(); }

/**
 * @brief 
 * 
 * @return std::vector<double> 
 */
std::vector<double> Triangle::angles() const { return std::vector<double>(); }

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Triangle::isDegenerate() const { return false; }

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return true 
 * @return false 
 */
bool Triangle::isIsocele(double lengthTolerance) const { return false; }

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return true 
 * @return false 
 */
bool Triangle::isEquilateral(double lengthTolerance) const { return false; }

/**
 * @brief 
 * 
 * @param angleTolerance 
 * @return true 
 * @return false 
 */
bool Triangle::isRight(double angleTolerance) const { return false; }

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return true 
 * @return false 
 */
bool Triangle::isScalene(double lengthTolerance) const { return false; }

/**
 * @brief 
 * 
 * @return std::vector<LineF> 
 */
std::vector<LineF> Triangle::altitudes() const { return std::vector<LineF>(); }

/**
 * @brief 
 * 
 * @return std::vector<LineF> 
 */
std::vector<LineF> Triangle::medians() const { return std::vector<LineF>(); }

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return std::vector<LineF> 
 */
std::vector<LineF> Triangle::bisectors(double lengthTolerance) const
{
    return std::vector<LineF>();
}

/**
 * @brief 
 * 
 * @return Triangle 
 */
Triangle Triangle::medial() const { return Triangle(); }

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return PointF 
 */
PointF Triangle::orthocenter(double lengthTolerance) const { return PointF(); }

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Triangle::circumscribedCenter() const { return PointF(); }

/**
 * @brief 
 * 
 * @return double 
 */
double Triangle::circumscribedRadius() const { return 0.0; }

/**
 * @brief 
 * 
 * @return Circle 
 */
Circle Triangle::circumscribedCircle() const { return Circle(); }

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Triangle::inscribedCenter() const { return PointF(); }

/**
 * @brief 
 * 
 * @return double 
 */
double Triangle::inscribedRadius() const { return 0.0; }

/**
 * @brief 
 * 
 * @return Circle 
 */
Circle Triangle::inscribedCircle() const { return Circle(); }

}// namespace m2