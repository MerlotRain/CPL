#include <m2_regularpolygon.h>

namespace m2 {


/**
 * @fn inline RegularPolygon()
 * @brief Construct a new Regular Polygon object
 */

/**
 * @fn inline RegularPolygon(const PointF &center, double radius, double azimuth, 
 *                  ConstructionOption circle)
 * @brief Construct a new Regular Polygon object
 * @param  center           
 * @param  radius           
 * @param  azimuth          
 * @param  circle           
 */

/**
 * @fn inline RegularPolygon(const PointF &center, const PointF &pt1,
                      ConstructionOption circle)
 * @brief Construct a new Regular Polygon object
 * @param  center           
 * @param  pt1              
 * @param  circle           
 */

/**
 * @fn inline RegularPolygon(const PointF &pt1, const PointF &pt2)
 * @brief Construct a new Regular Polygon object
 * @param  pt1              
 * @param  pt2              
 */

/**
 * @fn bool operator==(const RegularPolygon &rp) const
 * @brief 
 * @param  rp               
 * @return true 
 * @return false 
 */

/**
 * @fn bool operator!=(const RegularPolygon &rp) const
 * @brief 
 * @param  rp               
 * @return true 
 * @return false 
 */

/**
 * @fn bool isEmpty() const
 * @brief 
 * @return true 
 * @return false 
 */

/**
 * @fn PointF center() const
 * @brief 
 * @return PointF 
 */

/**
 * @fn double radius() const
 * @brief 
 * @return double 
 */

/**
 * @fn PointF firstVertex() const
 * @brief 
 * @return PointF 
 */

/**
 * @fn double apothem() const
 * @brief 
 * @return double 
 */

/**
 * @fn unsigned int numberSides() const
 * @brief 
 * @return unsigned int 
 */

/**
 * @fn void setCenter(const PointF &center)
 * @brief Set the Center object
 * @param  center           
 */

/**
 * @fn void setRadius(double radius)
 * @brief Set the Radius object
 * @param  radius           
 */

/**
 * @fn void setFirstVertex(const PointF &firstVertex)
 * @brief Set the First Vertex object
 * @param  firstVertex      
 */

/**
 * @fn PointSequence points() const
 * @brief 
 * @return PointSequence 
 */

/**
 * @fn Triangle toTriangle() const
 * @brief 
 * @return Triangle 
 */

/**
 * @fn std::vector<Triangle> triangulate() const
 * @brief 
 * @return std::vector<Triangle> 
 */

/**
 * @fn Circle inscribedCircle() const
 * @brief 
 * @return Circle 
 */

/**
 * @fn Circle circumscribedCircle() const
 * @brief 
 * @return Circle 
 */

/**
 * @fn double interiorAngle() const
 * @brief 
 * @return double 
 */

/**
 * @fn double centralAngle() const
 * @brief 
 * @return double 
 */

/**
 * @fn double area() const
 * @brief 
 * @return double 
 */

/**
 * @fn double perimeter() const
 * @brief 
 * @return double 
 */

/**
 * @fn double length() const
 * @brief 
 * @return double 
 */

/**
 * @fn double apothemToRadius(double apothem) const
 * @brief 
 * @param  apothem          
 * @return double 
 */

}// namespace m2
