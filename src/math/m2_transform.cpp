#include <m2_point.h>
#include <m2_transform.h>

namespace m2 {

#define Q_NEAR_CLIP (sizeof(double) == sizeof(double) ? 0.000001 : 0.0001)

#ifdef MAP
#undef MAP
#endif

#define MAP(x, y, nx, ny)                                                     \
    do {                                                                      \
        double FX_ = x;                                                       \
        double FY_ = y;                                                       \
        switch (t)                                                            \
        {                                                                     \
            case TxNone:                                                      \
                nx = FX_;                                                     \
                ny = FY_;                                                     \
                break;                                                        \
            case TxTranslate:                                                 \
                nx = FX_ + m_matrix[2][0];                                    \
                ny = FY_ + m_matrix[2][1];                                    \
                break;                                                        \
            case TxScale:                                                     \
                nx = m_matrix[0][0] * FX_ + m_matrix[2][0];                   \
                ny = m_matrix[1][1] * FY_ + m_matrix[2][1];                   \
                break;                                                        \
            case TxRotate:                                                    \
            case TxShear:                                                     \
            case TxProject:                                                   \
                nx = m_matrix[0][0] * FX_ + m_matrix[1][0] * FY_ +            \
                     m_matrix[2][0];                                          \
                ny = m_matrix[0][1] * FX_ + m_matrix[1][1] * FY_ +            \
                     m_matrix[2][1];                                          \
                if (t == TxProject)                                           \
                {                                                             \
                    double w = (m_matrix[0][2] * FX_ + m_matrix[1][2] * FY_ + \
                                m_matrix[2][2]);                              \
                    if (w < double(Q_NEAR_CLIP)) w = double(Q_NEAR_CLIP);     \
                    w = 1. / w;                                               \
                    nx *= w;                                                  \
                    ny *= w;                                                  \
                }                                                             \
        }                                                                     \
    } while (0)

const double inv_dist_to_plane = 1. / 1024.;

Transform::Transform() : m_matrix{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }
        , m_type(TxNone), m_dirty(TxNone)
{
}

Transform::Transform(double h11, double h12, double h13, double h21, double h22,
                     double h23, double h31, double h32, double h33)                     
                     : m_matrix{ {h11, h12, h13}, {h21, h22, h23}, {h31, h32, h33} }
        , m_type(TxNone), m_dirty(TxProject)
{
}

Transform::Transform(double h11, double h12, double h21, double h22, double dx,
                     double dy): m_matrix{ {h11, h12, 0}, {h21, h22, 0}, {dx, dy, 1} }
        , m_type(TxNone), m_dirty(TxShear)
{
}

bool Transform::isAffine() const { return inline_type() < TxProject; }

bool Transform::isIdentity() const { return inline_type() == TxNone; }

bool Transform::isInvertible() const { return !qFuzzyIsNull(determinant()); }

bool Transform::isScaling() const { return type() >= TxScale; }

bool Transform::isRotating() const { return inline_type() >= TxRotate; }

bool Transform::isTranslating() const { return inline_type() >= TxTranslate; }

Transform::TransformationType Transform::type() const
{
    return TransformationType();
}

double Transform::determinant() const
{
    return m_matrix[0][0] * (m_matrix[2][2] * m_matrix[1][1] -
                             m_matrix[2][1] * m_matrix[1][2]) -
           m_matrix[1][0] * (m_matrix[2][2] * m_matrix[0][1] -
                             m_matrix[2][1] * m_matrix[0][2]) +
           m_matrix[2][0] * (m_matrix[1][2] * m_matrix[0][1] -
                             m_matrix[1][1] * m_matrix[0][2]);
}

double Transform::m11() const { return m_matrix[0][0]; }

double Transform::m12() const { return m_matrix[0][1]; }

double Transform::m13() const { return m_matrix[0][2]; }

double Transform::m21() const { return m_matrix[1][0]; }

double Transform::m22() const { return m_matrix[1][1]; }

double Transform::m23() const { return m_matrix[1][2]; }

double Transform::m31() const { return m_matrix[2][0]; }

double Transform::m32() const { return m_matrix[2][1]; }

double Transform::m33() const { return m_matrix[2][2]; }

void Transform::setMatrix(double m11, double m12, double m13, double m21,
                          double m22, double m23, double m31, double m32,
                          double m33)
{
    m_matrix[0][0] = m11;
    m_matrix[0][1] = m12;
    m_matrix[0][2] = m13;
    m_matrix[1][0] = m21;
    m_matrix[1][1] = m22;
    m_matrix[1][2] = m23;
    m_matrix[2][0] = m31;
    m_matrix[2][1] = m32;
    m_matrix[2][2] = m33;
    m_type = TxNone;
    m_dirty = TxProject;
}

Transform Transform::inverted(bool *invertible) const
{
    Transform invert;
    bool inv = true;

    switch (inline_type())
    {
        case TxNone:
            break;
        case TxTranslate:
            invert.m_matrix[2][0] = -m_matrix[2][0];
            invert.m_matrix[2][1] = -m_matrix[2][1];
            break;
        case TxScale:
            inv = !qFuzzyIsNull(m_matrix[0][0]);
            inv &= !qFuzzyIsNull(m_matrix[1][1]);
            if (inv)
            {
                invert.m_matrix[0][0] = 1. / m_matrix[0][0];
                invert.m_matrix[1][1] = 1. / m_matrix[1][1];
                invert.m_matrix[2][0] = -m_matrix[2][0] * invert.m_matrix[0][0];
                invert.m_matrix[2][1] = -m_matrix[2][1] * invert.m_matrix[1][1];
            }
            break;
        default:
            // general case
            double det = determinant();
            inv = !qFuzzyIsNull(det);
            if (inv) invert = adjoint() / det;
            break;
    }

    if (invertible) *invertible = inv;

    if (inv)
    {
        // inverting doesn't change the type
        invert.m_type = m_type;
        invert.m_dirty = m_dirty;
    }

    return invert;
}

Transform Transform::adjoint() const
{
    double h11, h12, h13, h21, h22, h23, h31, h32, h33;
    h11 = m_matrix[1][1] * m_matrix[2][2] - m_matrix[1][2] * m_matrix[2][1];
    h21 = m_matrix[1][2] * m_matrix[2][0] - m_matrix[1][0] * m_matrix[2][2];
    h31 = m_matrix[1][0] * m_matrix[2][1] - m_matrix[1][1] * m_matrix[2][0];
    h12 = m_matrix[0][2] * m_matrix[2][1] - m_matrix[0][1] * m_matrix[2][2];
    h22 = m_matrix[0][0] * m_matrix[2][2] - m_matrix[0][2] * m_matrix[2][0];
    h32 = m_matrix[0][1] * m_matrix[2][0] - m_matrix[0][0] * m_matrix[2][1];
    h13 = m_matrix[0][1] * m_matrix[1][2] - m_matrix[0][2] * m_matrix[1][1];
    h23 = m_matrix[0][2] * m_matrix[1][0] - m_matrix[0][0] * m_matrix[1][2];
    h33 = m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];

    return Transform(h11, h12, h13, h21, h22, h23, h31, h32, h33);
}

Transform Transform::transposed() const
{
    Transform t(m_matrix[0][0], m_matrix[1][0], m_matrix[2][0], m_matrix[0][1],
                m_matrix[1][1], m_matrix[2][1], m_matrix[0][2], m_matrix[1][2],
                m_matrix[2][2]);
    return t;
}

Transform &Transform::translate(double dx, double dy)
{
    if (dx == 0 && dy == 0) return *this;
    switch (inline_type())
    {
        case TxNone:
            m_matrix[2][0] = dx;
            m_matrix[2][1] = dy;
            break;
        case TxTranslate:
            m_matrix[2][0] += dx;
            m_matrix[2][1] += dy;
            break;
        case TxScale:
            m_matrix[2][0] += dx * m_matrix[0][0];
            m_matrix[2][1] += dy * m_matrix[1][1];
            break;
        case TxProject:
            m_matrix[2][2] += dx * m_matrix[0][2] + dy * m_matrix[1][2];
            M2_FALLTHROUGH();
        case TxShear:
        case TxRotate:
            m_matrix[2][0] += dx * m_matrix[0][0] + dy * m_matrix[1][0];
            m_matrix[2][1] += dy * m_matrix[1][1] + dx * m_matrix[0][1];
            break;
    }
    if (m_dirty < TxTranslate) m_dirty = TxTranslate;
    return *this;
}

Transform &Transform::scale(double sx, double sy)
{
    if (sx == 1 && sy == 1) return *this;
    switch (inline_type())
    {
        case TxNone:
        case TxTranslate:
            m_matrix[0][0] = sx;
            m_matrix[1][1] = sy;
            break;
        case TxProject:
            m_matrix[0][2] *= sx;
            m_matrix[1][2] *= sy;
            M2_FALLTHROUGH();
        case TxRotate:
        case TxShear:
            m_matrix[0][1] *= sx;
            m_matrix[1][0] *= sy;
            M2_FALLTHROUGH();
        case TxScale:
            m_matrix[0][0] *= sx;
            m_matrix[1][1] *= sy;
            break;
    }
    if (m_dirty < TxScale) m_dirty = TxScale;
    return *this;
}

Transform &Transform::shear(double sh, double sv)
{
    if (sh == 0 && sv == 0) return *this;
    switch (inline_type())
    {
        case TxNone:
        case TxTranslate:
            m_matrix[0][1] = sv;
            m_matrix[1][0] = sh;
            break;
        case TxScale:
            m_matrix[0][1] = sv * m_matrix[1][1];
            m_matrix[1][0] = sh * m_matrix[0][0];
            break;
        case TxProject:
            {
                double tm13 = sv * m_matrix[1][2];
                double tm23 = sh * m_matrix[0][2];
                m_matrix[0][2] += tm13;
                m_matrix[1][2] += tm23;
            }
            M2_FALLTHROUGH();
        case TxRotate:
        case TxShear:
            {
                double tm11 = sv * m_matrix[1][0];
                double tm22 = sh * m_matrix[0][1];
                double tm12 = sv * m_matrix[1][1];
                double tm21 = sh * m_matrix[0][0];
                m_matrix[0][0] += tm11;
                m_matrix[0][1] += tm12;
                m_matrix[1][0] += tm21;
                m_matrix[1][1] += tm22;
                break;
            }
    }
    if (m_dirty < TxShear) m_dirty = TxShear;
    return *this;
}

Transform &Transform::rotate(double a)
{
    if (a == 0) return *this;

    double sina = 0;
    double cosa = 0;
    if (a == 90. || a == -270.) sina = 1.;
    else if (a == 270. || a == -90.)
        sina = -1.;
    else if (a == 180.)
        cosa = -1.;
    else
    {
        double b = degreesToRadians(a);
        sina = qSin(b);// fast and convenient
        cosa = qCos(b);
    }
    switch (inline_type())
    {
        case TxNone:
        case TxTranslate:
            m_matrix[0][0] = cosa;
            m_matrix[0][1] = sina;
            m_matrix[1][0] = -sina;
            m_matrix[1][1] = cosa;
            break;
        case TxScale:
            {
                double tm11 = cosa * m_matrix[0][0];
                double tm12 = sina * m_matrix[1][1];
                double tm21 = -sina * m_matrix[0][0];
                double tm22 = cosa * m_matrix[1][1];
                m_matrix[0][0] = tm11;
                m_matrix[0][1] = tm12;
                m_matrix[1][0] = tm21;
                m_matrix[1][1] = tm22;
                break;
            }
        case TxProject:
            {
                double tm13 = cosa * m_matrix[0][2] + sina * m_matrix[1][2];
                double tm23 = -sina * m_matrix[0][2] + cosa * m_matrix[1][2];
                m_matrix[0][2] = tm13;
                m_matrix[1][2] = tm23;
                M2_FALLTHROUGH();
            }
        case TxRotate:
        case TxShear:
            {
                double tm11 = cosa * m_matrix[0][0] + sina * m_matrix[1][0];
                double tm12 = cosa * m_matrix[0][1] + sina * m_matrix[1][1];
                double tm21 = -sina * m_matrix[0][0] + cosa * m_matrix[1][0];
                double tm22 = -sina * m_matrix[0][1] + cosa * m_matrix[1][1];
                m_matrix[0][0] = tm11;
                m_matrix[0][1] = tm12;
                m_matrix[1][0] = tm21;
                m_matrix[1][1] = tm22;
                break;
            }
    }
    if (m_dirty < TxRotate) m_dirty = TxRotate;

    return *this;
}

Transform &Transform::rotateRadians(double a)
{
    double sina = qSin(a);
    double cosa = qCos(a);


    switch (inline_type())
    {
        case TxNone:
        case TxTranslate:
            m_matrix[0][0] = cosa;
            m_matrix[0][1] = sina;
            m_matrix[1][0] = -sina;
            m_matrix[1][1] = cosa;
            break;
        case TxScale:
            {
                double tm11 = cosa * m_matrix[0][0];
                double tm12 = sina * m_matrix[1][1];
                double tm21 = -sina * m_matrix[0][0];
                double tm22 = cosa * m_matrix[1][1];
                m_matrix[0][0] = tm11;
                m_matrix[0][1] = tm12;
                m_matrix[1][0] = tm21;
                m_matrix[1][1] = tm22;
                break;
            }
        case TxProject:
            {
                double tm13 = cosa * m_matrix[0][2] + sina * m_matrix[1][2];
                double tm23 = -sina * m_matrix[0][2] + cosa * m_matrix[1][2];
                m_matrix[0][2] = tm13;
                m_matrix[1][2] = tm23;
                M2_FALLTHROUGH();
            }
        case TxRotate:
        case TxShear:
            {
                double tm11 = cosa * m_matrix[0][0] + sina * m_matrix[1][0];
                double tm12 = cosa * m_matrix[0][1] + sina * m_matrix[1][1];
                double tm21 = -sina * m_matrix[0][0] + cosa * m_matrix[1][0];
                double tm22 = -sina * m_matrix[0][1] + cosa * m_matrix[1][1];
                m_matrix[0][0] = tm11;
                m_matrix[0][1] = tm12;
                m_matrix[1][0] = tm21;
                m_matrix[1][1] = tm22;
                break;
            }
    }
    if (m_dirty < TxRotate) m_dirty = TxRotate;

    return *this;
}

bool Transform::squareToQuad(const PolygonF &square, Transform &trans)
{
    if (square.size() != 4) return false;

    double dx0 = square[0].x();
    double dx1 = square[1].x();
    double dx2 = square[2].x();
    double dx3 = square[3].x();

    double dy0 = square[0].y();
    double dy1 = square[1].y();
    double dy2 = square[2].y();
    double dy3 = square[3].y();

    double ax = dx0 - dx1 + dx2 - dx3;
    double ay = dy0 - dy1 + dy2 - dy3;

    if (!ax && !ay)
    {//afine transform
        trans.setMatrix(dx1 - dx0, dy1 - dy0, 0, dx2 - dx1, dy2 - dy1, 0, dx0,
                        dy0, 1);
    }
    else
    {
        double ax1 = dx1 - dx2;
        double ax2 = dx3 - dx2;
        double ay1 = dy1 - dy2;
        double ay2 = dy3 - dy2;

        /*determinants */
        double gtop = ax * ay2 - ax2 * ay;
        double htop = ax1 * ay - ax * ay1;
        double bottom = ax1 * ay2 - ax2 * ay1;

        double a, b, c, d, e, f, g, h; /*i is always 1*/

        if (!bottom) return false;

        g = gtop / bottom;
        h = htop / bottom;

        a = dx1 - dx0 + g * dx1;
        b = dx3 - dx0 + h * dx3;
        c = dx0;
        d = dy1 - dy0 + g * dy1;
        e = dy3 - dy0 + h * dy3;
        f = dy0;

        trans.setMatrix(a, d, g, b, e, h, c, f, 1.0);
    }

    return true;
}

bool Transform::quadToSquare(const PolygonF &quad, Transform &trans)
{
    if (!squareToQuad(quad, trans)) return false;

    bool invertible = false;
    trans = trans.inverted(&invertible);

    return invertible;
}

bool Transform::quadToQuad(const PolygonF &one, const PolygonF &two,
                           Transform &trans)
{
    Transform stq;
    if (!quadToSquare(one, trans)) return false;
    if (!squareToQuad(two, stq)) return false;
    trans *= stq;
    //qDebug()<<"Final = "<<trans;
    return true;
}

bool Transform::operator==(const Transform &o) const
{
    return m_matrix[0][0] == o.m_matrix[0][0] &&
           m_matrix[0][1] == o.m_matrix[0][1] &&
           m_matrix[1][0] == o.m_matrix[1][0] &&
           m_matrix[1][1] == o.m_matrix[1][1] &&
           m_matrix[2][0] == o.m_matrix[2][0] &&
           m_matrix[2][1] == o.m_matrix[2][1] &&
           m_matrix[0][2] == o.m_matrix[0][2] &&
           m_matrix[1][2] == o.m_matrix[1][2] &&
           m_matrix[2][2] == o.m_matrix[2][2];
}

bool Transform::operator!=(const Transform &o) const { return !operator==(o); }

Transform &Transform::operator*=(const Transform &o)
{
    const TransformationType otherType = o.inline_type();
    if (otherType == TxNone) return *this;

    const TransformationType thisType = inline_type();
    if (thisType == TxNone) return operator=(o);

    TransformationType t = qMax(thisType, otherType);
    switch (t)
    {
        case TxNone:
            break;
        case TxTranslate:
            m_matrix[2][0] += o.m_matrix[2][0];
            m_matrix[2][1] += o.m_matrix[2][1];
            break;
        case TxScale:
            {
                double m11 = m_matrix[0][0] * o.m_matrix[0][0];
                double m22 = m_matrix[1][1] * o.m_matrix[1][1];

                double m31 =
                        m_matrix[2][0] * o.m_matrix[0][0] + o.m_matrix[2][0];
                double m32 =
                        m_matrix[2][1] * o.m_matrix[1][1] + o.m_matrix[2][1];

                m_matrix[0][0] = m11;
                m_matrix[1][1] = m22;
                m_matrix[2][0] = m31;
                m_matrix[2][1] = m32;
                break;
            }
        case TxRotate:
        case TxShear:
            {
                double m11 = m_matrix[0][0] * o.m_matrix[0][0] +
                             m_matrix[0][1] * o.m_matrix[1][0];
                double m12 = m_matrix[0][0] * o.m_matrix[0][1] +
                             m_matrix[0][1] * o.m_matrix[1][1];

                double m21 = m_matrix[1][0] * o.m_matrix[0][0] +
                             m_matrix[1][1] * o.m_matrix[1][0];
                double m22 = m_matrix[1][0] * o.m_matrix[0][1] +
                             m_matrix[1][1] * o.m_matrix[1][1];

                double m31 = m_matrix[2][0] * o.m_matrix[0][0] +
                             m_matrix[2][1] * o.m_matrix[1][0] +
                             o.m_matrix[2][0];
                double m32 = m_matrix[2][0] * o.m_matrix[0][1] +
                             m_matrix[2][1] * o.m_matrix[1][1] +
                             o.m_matrix[2][1];

                m_matrix[0][0] = m11;
                m_matrix[0][1] = m12;
                m_matrix[1][0] = m21;
                m_matrix[1][1] = m22;
                m_matrix[2][0] = m31;
                m_matrix[2][1] = m32;
                break;
            }
        case TxProject:
            {
                double m11 = m_matrix[0][0] * o.m_matrix[0][0] +
                             m_matrix[0][1] * o.m_matrix[1][0] +
                             m_matrix[0][2] * o.m_matrix[2][0];
                double m12 = m_matrix[0][0] * o.m_matrix[0][1] +
                             m_matrix[0][1] * o.m_matrix[1][1] +
                             m_matrix[0][2] * o.m_matrix[2][1];
                double m13 = m_matrix[0][0] * o.m_matrix[0][2] +
                             m_matrix[0][1] * o.m_matrix[1][2] +
                             m_matrix[0][2] * o.m_matrix[2][2];

                double m21 = m_matrix[1][0] * o.m_matrix[0][0] +
                             m_matrix[1][1] * o.m_matrix[1][0] +
                             m_matrix[1][2] * o.m_matrix[2][0];
                double m22 = m_matrix[1][0] * o.m_matrix[0][1] +
                             m_matrix[1][1] * o.m_matrix[1][1] +
                             m_matrix[1][2] * o.m_matrix[2][1];
                double m23 = m_matrix[1][0] * o.m_matrix[0][2] +
                             m_matrix[1][1] * o.m_matrix[1][2] +
                             m_matrix[1][2] * o.m_matrix[2][2];

                double m31 = m_matrix[2][0] * o.m_matrix[0][0] +
                             m_matrix[2][1] * o.m_matrix[1][0] +
                             m_matrix[2][2] * o.m_matrix[2][0];
                double m32 = m_matrix[2][0] * o.m_matrix[0][1] +
                             m_matrix[2][1] * o.m_matrix[1][1] +
                             m_matrix[2][2] * o.m_matrix[2][1];
                double m33 = m_matrix[2][0] * o.m_matrix[0][2] +
                             m_matrix[2][1] * o.m_matrix[1][2] +
                             m_matrix[2][2] * o.m_matrix[2][2];

                m_matrix[0][0] = m11;
                m_matrix[0][1] = m12;
                m_matrix[0][2] = m13;
                m_matrix[1][0] = m21;
                m_matrix[1][1] = m22;
                m_matrix[1][2] = m23;
                m_matrix[2][0] = m31;
                m_matrix[2][1] = m32;
                m_matrix[2][2] = m33;
            }
    }

    m_dirty = t;
    m_type = t;

    return *this;
}

Transform Transform::operator*(const Transform &o) const
{
    const TransformationType otherType = o.inline_type();
    if (otherType == TxNone) return *this;

    const TransformationType thisType = inline_type();
    if (thisType == TxNone) return o;

    Transform t;
    TransformationType type = qMax(thisType, otherType);
    switch (type)
    {
        case TxNone:
            break;
        case TxTranslate:
            t.m_matrix[2][0] = m_matrix[2][0] + o.m_matrix[2][0];
            t.m_matrix[2][1] = m_matrix[2][1] + o.m_matrix[2][1];
            break;
        case TxScale:
            {
                double m11 = m_matrix[0][0] * o.m_matrix[0][0];
                double m22 = m_matrix[1][1] * o.m_matrix[1][1];

                double m31 =
                        m_matrix[2][0] * o.m_matrix[0][0] + o.m_matrix[2][0];
                double m32 =
                        m_matrix[2][1] * o.m_matrix[1][1] + o.m_matrix[2][1];

                t.m_matrix[0][0] = m11;
                t.m_matrix[1][1] = m22;
                t.m_matrix[2][0] = m31;
                t.m_matrix[2][1] = m32;
                break;
            }
        case TxRotate:
        case TxShear:
            {
                double m11 = m_matrix[0][0] * o.m_matrix[0][0] +
                             m_matrix[0][1] * o.m_matrix[1][0];
                double m12 = m_matrix[0][0] * o.m_matrix[0][1] +
                             m_matrix[0][1] * o.m_matrix[1][1];

                double m21 = m_matrix[1][0] * o.m_matrix[0][0] +
                             m_matrix[1][1] * o.m_matrix[1][0];
                double m22 = m_matrix[1][0] * o.m_matrix[0][1] +
                             m_matrix[1][1] * o.m_matrix[1][1];

                double m31 = m_matrix[2][0] * o.m_matrix[0][0] +
                             m_matrix[2][1] * o.m_matrix[1][0] +
                             o.m_matrix[2][0];
                double m32 = m_matrix[2][0] * o.m_matrix[0][1] +
                             m_matrix[2][1] * o.m_matrix[1][1] +
                             o.m_matrix[2][1];

                t.m_matrix[0][0] = m11;
                t.m_matrix[0][1] = m12;
                t.m_matrix[1][0] = m21;
                t.m_matrix[1][1] = m22;
                t.m_matrix[2][0] = m31;
                t.m_matrix[2][1] = m32;
                break;
            }
        case TxProject:
            {
                double m11 = m_matrix[0][0] * o.m_matrix[0][0] +
                             m_matrix[0][1] * o.m_matrix[1][0] +
                             m_matrix[0][2] * o.m_matrix[2][0];
                double m12 = m_matrix[0][0] * o.m_matrix[0][1] +
                             m_matrix[0][1] * o.m_matrix[1][1] +
                             m_matrix[0][2] * o.m_matrix[2][1];
                double m13 = m_matrix[0][0] * o.m_matrix[0][2] +
                             m_matrix[0][1] * o.m_matrix[1][2] +
                             m_matrix[0][2] * o.m_matrix[2][2];

                double m21 = m_matrix[1][0] * o.m_matrix[0][0] +
                             m_matrix[1][1] * o.m_matrix[1][0] +
                             m_matrix[1][2] * o.m_matrix[2][0];
                double m22 = m_matrix[1][0] * o.m_matrix[0][1] +
                             m_matrix[1][1] * o.m_matrix[1][1] +
                             m_matrix[1][2] * o.m_matrix[2][1];
                double m23 = m_matrix[1][0] * o.m_matrix[0][2] +
                             m_matrix[1][1] * o.m_matrix[1][2] +
                             m_matrix[1][2] * o.m_matrix[2][2];

                double m31 = m_matrix[2][0] * o.m_matrix[0][0] +
                             m_matrix[2][1] * o.m_matrix[1][0] +
                             m_matrix[2][2] * o.m_matrix[2][0];
                double m32 = m_matrix[2][0] * o.m_matrix[0][1] +
                             m_matrix[2][1] * o.m_matrix[1][1] +
                             m_matrix[2][2] * o.m_matrix[2][1];
                double m33 = m_matrix[2][0] * o.m_matrix[0][2] +
                             m_matrix[2][1] * o.m_matrix[1][2] +
                             m_matrix[2][2] * o.m_matrix[2][2];

                t.m_matrix[0][0] = m11;
                t.m_matrix[0][1] = m12;
                t.m_matrix[0][2] = m13;
                t.m_matrix[1][0] = m21;
                t.m_matrix[1][1] = m22;
                t.m_matrix[1][2] = m23;
                t.m_matrix[2][0] = m31;
                t.m_matrix[2][1] = m32;
                t.m_matrix[2][2] = m33;
            }
    }

    t.m_dirty = type;
    t.m_type = type;

    return t;
}

void Transform::reset() { *this = Transform(); }

Point Transform::map(const Point &p) const
{
    double fx = p.x();
    double fy = p.y();

    double x = 0, y = 0;

    TransformationType t = inline_type();
    switch (t)
    {
        case TxNone:
            x = fx;
            y = fy;
            break;
        case TxTranslate:
            x = fx + m_matrix[2][0];
            y = fy + m_matrix[2][1];
            break;
        case TxScale:
            x = m_matrix[0][0] * fx + m_matrix[2][0];
            y = m_matrix[1][1] * fy + m_matrix[2][1];
            break;
        case TxRotate:
        case TxShear:
        case TxProject:
            x = m_matrix[0][0] * fx + m_matrix[1][0] * fy + m_matrix[2][0];
            y = m_matrix[0][1] * fx + m_matrix[1][1] * fy + m_matrix[2][1];
            if (t == TxProject)
            {
                double w = 1. / (m_matrix[0][2] * fx + m_matrix[1][2] * fy +
                                 m_matrix[2][2]);
                x *= w;
                y *= w;
            }
    }
    return Point(qRound(x), qRound(y));
}

PointF Transform::map(const PointF &p) const
{
    double fx = p.x();
    double fy = p.y();

    double x = 0, y = 0;

    TransformationType t = inline_type();
    switch (t)
    {
        case TxNone:
            x = fx;
            y = fy;
            break;
        case TxTranslate:
            x = fx + m_matrix[2][0];
            y = fy + m_matrix[2][1];
            break;
        case TxScale:
            x = m_matrix[0][0] * fx + m_matrix[2][0];
            y = m_matrix[1][1] * fy + m_matrix[2][1];
            break;
        case TxRotate:
        case TxShear:
        case TxProject:
            x = m_matrix[0][0] * fx + m_matrix[1][0] * fy + m_matrix[2][0];
            y = m_matrix[0][1] * fx + m_matrix[1][1] * fy + m_matrix[2][1];
            if (t == TxProject)
            {
                double w = 1. / (m_matrix[0][2] * fx + m_matrix[1][2] * fy +
                                 m_matrix[2][2]);
                x *= w;
                y *= w;
            }
    }
    return PointF(x, y);
}

Line Transform::map(const Line &l) const
{
    double fx1 = l.x1();
    double fy1 = l.y1();
    double fx2 = l.x2();
    double fy2 = l.y2();

    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    TransformationType t = inline_type();
    switch (t)
    {
        case TxNone:
            x1 = fx1;
            y1 = fy1;
            x2 = fx2;
            y2 = fy2;
            break;
        case TxTranslate:
            x1 = fx1 + m_matrix[2][0];
            y1 = fy1 + m_matrix[2][1];
            x2 = fx2 + m_matrix[2][0];
            y2 = fy2 + m_matrix[2][1];
            break;
        case TxScale:
            x1 = m_matrix[0][0] * fx1 + m_matrix[2][0];
            y1 = m_matrix[1][1] * fy1 + m_matrix[2][1];
            x2 = m_matrix[0][0] * fx2 + m_matrix[2][0];
            y2 = m_matrix[1][1] * fy2 + m_matrix[2][1];
            break;
        case TxRotate:
        case TxShear:
        case TxProject:
            x1 = m_matrix[0][0] * fx1 + m_matrix[1][0] * fy1 + m_matrix[2][0];
            y1 = m_matrix[0][1] * fx1 + m_matrix[1][1] * fy1 + m_matrix[2][1];
            x2 = m_matrix[0][0] * fx2 + m_matrix[1][0] * fy2 + m_matrix[2][0];
            y2 = m_matrix[0][1] * fx2 + m_matrix[1][1] * fy2 + m_matrix[2][1];
            if (t == TxProject)
            {
                double w = 1. / (m_matrix[0][2] * fx1 + m_matrix[1][2] * fy1 +
                                 m_matrix[2][2]);
                x1 *= w;
                y1 *= w;
                w = 1. / (m_matrix[0][2] * fx2 + m_matrix[1][2] * fy2 +
                          m_matrix[2][2]);
                x2 *= w;
                y2 *= w;
            }
    }
    return Line(qRound(x1), qRound(y1), qRound(x2), qRound(y2));
}

LineF Transform::map(const LineF &l) const
{
    double fx1 = l.x1();
    double fy1 = l.y1();
    double fx2 = l.x2();
    double fy2 = l.y2();

    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    TransformationType t = inline_type();
    switch (t)
    {
        case TxNone:
            x1 = fx1;
            y1 = fy1;
            x2 = fx2;
            y2 = fy2;
            break;
        case TxTranslate:
            x1 = fx1 + m_matrix[2][0];
            y1 = fy1 + m_matrix[2][1];
            x2 = fx2 + m_matrix[2][0];
            y2 = fy2 + m_matrix[2][1];
            break;
        case TxScale:
            x1 = m_matrix[0][0] * fx1 + m_matrix[2][0];
            y1 = m_matrix[1][1] * fy1 + m_matrix[2][1];
            x2 = m_matrix[0][0] * fx2 + m_matrix[2][0];
            y2 = m_matrix[1][1] * fy2 + m_matrix[2][1];
            break;
        case TxRotate:
        case TxShear:
        case TxProject:
            x1 = m_matrix[0][0] * fx1 + m_matrix[1][0] * fy1 + m_matrix[2][0];
            y1 = m_matrix[0][1] * fx1 + m_matrix[1][1] * fy1 + m_matrix[2][1];
            x2 = m_matrix[0][0] * fx2 + m_matrix[1][0] * fy2 + m_matrix[2][0];
            y2 = m_matrix[0][1] * fx2 + m_matrix[1][1] * fy2 + m_matrix[2][1];
            if (t == TxProject)
            {
                double w = 1. / (m_matrix[0][2] * fx1 + m_matrix[1][2] * fy1 +
                                 m_matrix[2][2]);
                x1 *= w;
                y1 *= w;
                w = 1. / (m_matrix[0][2] * fx2 + m_matrix[1][2] * fy2 +
                          m_matrix[2][2]);
                x2 *= w;
                y2 *= w;
            }
    }
    return LineF(x1, y1, x2, y2);
}

PolygonF Transform::map(const PolygonF &a) const
{
    TransformationType t = inline_type();
    if (t <= TxTranslate) return a.translated(m_matrix[2][0], m_matrix[2][1]);

    if (t >= Transform::TxProject) return a;

    int size = a.size();
    int i;
    PolygonF p(size);
    const PointF *da = a.data();
    PointF *dp = p.data();

    for (i = 0; i < size; ++i)
    {
        MAP(da[i].x(), da[i].y(), dp[i].rx(), dp[i].ry());
    }
    return p;
}

Polygon Transform::map(const Polygon &a) const
{
    TransformationType t = inline_type();
    if (t <= TxTranslate)
        return a.translated(qRound(m_matrix[2][0]), qRound(m_matrix[2][1]));

    if (t >= Transform::TxProject) return a;

    int size = a.size();
    int i;
    Polygon p(size);
    const Point *da = a.data();
    Point *dp = p.data();

    for (i = 0; i < size; ++i)
    {
        double nx = 0, ny = 0;
        MAP(da[i].x(), da[i].y(), nx, ny);
        dp[i].setX(qRound(nx));
        dp[i].setY(qRound(ny));
    }
    return p;
}

void Transform::map(int x, int y, int *tx, int *ty) const
{
    TransformationType t = inline_type();
    double fx = 0, fy = 0;
    MAP(x, y, fx, fy);
    *tx = qRound(fx);
    *ty = qRound(fy);
}

void Transform::map(double x, double y, double *tx, double *ty) const
{
    TransformationType t = inline_type();
    MAP(x, y, *tx, *ty);
}

void Transform::map(double *coordinate, int count) const
{
    TransformationType t = inline_type();
    for (int i = 0; i < count; ++i)
    {
        double nx = 0, ny = 0;
        MAP(coordinate[i * 2], coordinate[i * 2 + 1], nx, ny);
        coordinate[i * 2] = nx;
        coordinate[i * 2 + 1] = ny;
    }
}

Transform &Transform::operator*=(double num)
{
    if (num == 1.) return *this;
    m_matrix[0][0] *= num;
    m_matrix[0][1] *= num;
    m_matrix[0][2] *= num;
    m_matrix[1][0] *= num;
    m_matrix[1][1] *= num;
    m_matrix[1][2] *= num;
    m_matrix[2][0] *= num;
    m_matrix[2][1] *= num;
    m_matrix[2][2] *= num;
    if (m_dirty < TxScale) m_dirty = TxScale;
    return *this;
}

Transform &Transform::operator/=(double div)
{
    if (div == 0) return *this;
    div = 1 / div;
    return operator*=(div);
}

Transform &Transform::operator+=(double num)
{
    if (num == 0) return *this;
    m_matrix[0][0] += num;
    m_matrix[0][1] += num;
    m_matrix[0][2] += num;
    m_matrix[1][0] += num;
    m_matrix[1][1] += num;
    m_matrix[1][2] += num;
    m_matrix[2][0] += num;
    m_matrix[2][1] += num;
    m_matrix[2][2] += num;
    m_dirty = TxProject;
    return *this;
}

Transform &Transform::operator-=(double num)
{
    if (num == 0) return *this;
    m_matrix[0][0] -= num;
    m_matrix[0][1] -= num;
    m_matrix[0][2] -= num;
    m_matrix[1][0] -= num;
    m_matrix[1][1] -= num;
    m_matrix[1][2] -= num;
    m_matrix[2][0] -= num;
    m_matrix[2][1] -= num;
    m_matrix[2][2] -= num;
    m_dirty = TxProject;
    return *this;
}

Transform Transform::fromTranslate(double dx, double dy)
{
    Transform transform(1, 0, 0, 0, 1, 0, dx, dy, 1);
    if (dx == 0 && dy == 0) transform.m_type = TxNone;
    else
        transform.m_type = TxTranslate;
    transform.m_dirty = TxNone;
    return transform;
}

Transform Transform::fromScale(double dx, double dy)
{
    Transform transform(dx, 0, 0, 0, dy, 0, 0, 0, 1);
    if (dx == 1. && dy == 1.) transform.m_type = TxNone;
    else
        transform.m_type = TxScale;
    transform.m_dirty = TxNone;
    return transform;
}

}// namespace m2
