#include <m2_vector.h>

namespace m2 {

/*******************************************************************************
 * class Vector2D functions
 *******************************************************************************/

float Vector2D::length() const noexcept
{
    double len = double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]);
    return float(std::sqrt(len));
}

/*******************************************************************************
 * class Vector3D functions
 *******************************************************************************/

float Vector3D::length() const noexcept
{
    double len = double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]) +
                 double(v[2]) * double(v[2]);
    return float(std::sqrt(len));
}

}// namespace m2
