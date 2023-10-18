#include <m2_rect.h>

namespace m2 {

/*******************************************************************************
 * class Rect functions
 *******************************************************************************/

Rect Rect::normalized() const noexcept
{
    Rect r(*this);
    if (x2 < x1)
    {// swap bad x values
        r.x1 = x2 + 1;
        r.x2 = x1 - 1;
    }
    if (y2 < y1)
    {// swap bad y values
        r.y1 = y2 + 1;
        r.y2 = y1 - 1;
    }
    return r;
}

Rect Rect::operator|(const Rect &r) const noexcept
{
    if (isNull()) return r;
    if (r.isNull()) return *this;

    int l1 = x1;
    int r1 = x1 - 1;
    if (x2 < x1 - 1) l1 = x2 + 1;
    else
        r1 = x2;

    int l2 = r.x1;
    int r2 = r.x1 - 1;
    if (r.x2 < r.x1 - 1) l2 = r.x2 + 1;
    else
        r2 = r.x2;

    int t1 = y1;
    int b1 = y1 - 1;
    if (y2 < y1 - 1) t1 = y2 + 1;
    else
        b1 = y2;

    int t2 = r.y1;
    int b2 = r.y1 - 1;
    if (r.y2 < r.y1 - 1) t2 = r.y2 + 1;
    else
        b2 = r.y2;

    Rect tmp;
    tmp.x1 = qMin(l1, l2);
    tmp.x2 = qMax(r1, r2);
    tmp.y1 = qMin(t1, t2);
    tmp.y2 = qMax(b1, b2);
    return tmp;
}

Rect Rect::operator&(const Rect &r) const noexcept
{
    if (isNull() || r.isNull()) return Rect();

    int l1 = x1;
    int r1 = x2;
    if (x2 < x1 - 1)
    {
        l1 = x2 + 1;
        r1 = x1 - 1;
    }

    int l2 = r.x1;
    int r2 = r.x2;
    if (r.x2 < r.x1 - 1)
    {
        l2 = r.x2 + 1;
        r2 = r.x1 - 1;
    }

    if (l1 > r2 || l2 > r1) return Rect();

    int t1 = y1;
    int b1 = y2;
    if (y2 < y1 - 1)
    {
        t1 = y2 + 1;
        b1 = y1 - 1;
    }

    int t2 = r.y1;
    int b2 = r.y2;
    if (r.y2 < r.y1 - 1)
    {
        t2 = r.y2 + 1;
        b2 = r.y1 - 1;
    }

    if (t1 > b2 || t2 > b1) return Rect();

    Rect tmp;
    tmp.x1 = qMax(l1, l2);
    tmp.x2 = qMin(r1, r2);
    tmp.y1 = qMax(t1, t2);
    tmp.y2 = qMin(b1, b2);
    return tmp;
}

bool Rect::contains(const Rect &r, bool proper) const noexcept
{
    if (isNull() || r.isNull()) return false;

    int l1 = x1;
    int r1 = x1 - 1;
    if (x2 < x1 - 1) l1 = x2 + 1;
    else
        r1 = x2;

    int l2 = r.x1;
    int r2 = r.x1 - 1;
    if (r.x2 < r.x1 - 1) l2 = r.x2 + 1;
    else
        r2 = r.x2;

    if (proper)
    {
        if (l2 <= l1 || r2 >= r1) return false;
    }
    else
    {
        if (l2 < l1 || r2 > r1) return false;
    }

    int t1 = y1;
    int b1 = y1 - 1;
    if (y2 < y1 - 1) t1 = y2 + 1;
    else
        b1 = y2;

    int t2 = r.y1;
    int b2 = r.y1 - 1;
    if (r.y2 < r.y1 - 1) t2 = r.y2 + 1;
    else
        b2 = r.y2;

    if (proper)
    {
        if (t2 <= t1 || b2 >= b1) return false;
    }
    else
    {
        if (t2 < t1 || b2 > b1) return false;
    }

    return true;
}

bool Rect::contains(const Point &p, bool proper) const noexcept
{
    int l, r;
    if (x2 < x1 - 1)
    {
        l = x2 + 1;
        r = x1 - 1;
    }
    else
    {
        l = x1;
        r = x2;
    }
    if (proper)
    {
        if (p.x() <= l || p.x() >= r) return false;
    }
    else
    {
        if (p.x() < l || p.x() > r) return false;
    }
    int t, b;
    if (y2 < y1 - 1)
    {
        t = y2 + 1;
        b = y1 - 1;
    }
    else
    {
        t = y1;
        b = y2;
    }
    if (proper)
    {
        if (p.y() <= t || p.y() >= b) return false;
    }
    else
    {
        if (p.y() < t || p.y() > b) return false;
    }
    return true;
}

bool Rect::intersects(const Rect &r) const noexcept
{
    if (isNull() || r.isNull()) return false;

    int l1 = x1;
    int r1 = x2;
    if (x2 < x1 - 1)
    {
        l1 = x2 + 1;
        r1 = x1 - 1;
    }

    int l2 = r.x1;
    int r2 = r.x2;
    if (r.x2 < r.x1 - 1)
    {
        l2 = r.x2 + 1;
        r2 = r.x1 - 1;
    }

    if (l1 > r2 || l2 > r1) return false;

    int t1 = y1;
    int b1 = y2;
    if (y2 < y1 - 1)
    {
        t1 = y2 + 1;
        b1 = y1 - 1;
    }

    int t2 = r.y1;
    int b2 = r.y2;
    if (r.y2 < r.y1 - 1)
    {
        t2 = r.y2 + 1;
        b2 = r.y1 - 1;
    }

    if (t1 > b2 || t2 > b1) return false;

    return true;
}

/*******************************************************************************
 * class RectF functions
 *******************************************************************************/

RectF RectF::normalized() const noexcept
{
    RectF r = *this;
    if (r.w < 0)
    {
        r.xp += r.w;
        r.w = -r.w;
    }
    if (r.h < 0)
    {
        r.yp += r.h;
        r.h = -r.h;
    }
    return r;
}

RectF RectF::operator|(const RectF &r) const noexcept
{
    if (isNull()) return r;
    if (r.isNull()) return *this;

    double left = xp;
    double right = xp;
    if (w < 0) left += w;
    else
        right += w;

    if (r.w < 0)
    {
        left = qMin(left, r.xp + r.w);
        right = qMax(right, r.xp);
    }
    else
    {
        left = qMin(left, r.xp);
        right = qMax(right, r.xp + r.w);
    }

    double top = yp;
    double bottom = yp;
    if (h < 0) top += h;
    else
        bottom += h;

    if (r.h < 0)
    {
        top = qMin(top, r.yp + r.h);
        bottom = qMax(bottom, r.yp);
    }
    else
    {
        top = qMin(top, r.yp);
        bottom = qMax(bottom, r.yp + r.h);
    }

    return RectF(left, top, right - left, bottom - top);
}

RectF RectF::operator&(const RectF &r) const noexcept
{
    double l1 = xp;
    double r1 = xp;
    if (w < 0) l1 += w;
    else
        r1 += w;
    if (l1 == r1)// null rect
        return RectF();

    double l2 = r.xp;
    double r2 = r.xp;
    if (r.w < 0) l2 += r.w;
    else
        r2 += r.w;
    if (l2 == r2)// null rect
        return RectF();

    if (l1 >= r2 || l2 >= r1) return RectF();

    double t1 = yp;
    double b1 = yp;
    if (h < 0) t1 += h;
    else
        b1 += h;
    if (t1 == b1)// null rect
        return RectF();

    double t2 = r.yp;
    double b2 = r.yp;
    if (r.h < 0) t2 += r.h;
    else
        b2 += r.h;
    if (t2 == b2)// null rect
        return RectF();

    if (t1 >= b2 || t2 >= b1) return RectF();

    RectF tmp;
    tmp.xp = qMax(l1, l2);
    tmp.yp = qMax(t1, t2);
    tmp.w = qMin(r1, r2) - tmp.xp;
    tmp.h = qMin(b1, b2) - tmp.yp;
    return tmp;
}

bool RectF::contains(const RectF &r) const noexcept
{
    double l1 = xp;
    double r1 = xp;
    if (w < 0) l1 += w;
    else
        r1 += w;
    if (l1 == r1)// null rect
        return false;

    double l2 = r.xp;
    double r2 = r.xp;
    if (r.w < 0) l2 += r.w;
    else
        r2 += r.w;
    if (l2 == r2)// null rect
        return false;

    if (l2 < l1 || r2 > r1) return false;

    double t1 = yp;
    double b1 = yp;
    if (h < 0) t1 += h;
    else
        b1 += h;
    if (t1 == b1)// null rect
        return false;

    double t2 = r.yp;
    double b2 = r.yp;
    if (r.h < 0) t2 += r.h;
    else
        b2 += r.h;
    if (t2 == b2)// null rect
        return false;

    if (t2 < t1 || b2 > b1) return false;

    return true;
}

bool RectF::contains(const PointF &p) const noexcept
{
    double l = xp;
    double r = xp;
    if (w < 0) l += w;
    else
        r += w;
    if (l == r)// null rect
        return false;

    if (p.x() < l || p.x() > r) return false;

    double t = yp;
    double b = yp;
    if (h < 0) t += h;
    else
        b += h;
    if (t == b)// null rect
        return false;

    if (p.y() < t || p.y() > b) return false;

    return true;
}

bool RectF::intersects(const RectF &r) const noexcept
{
    double l1 = xp;
    double r1 = xp;
    if (w < 0) l1 += w;
    else
        r1 += w;
    if (l1 == r1)// null rect
        return false;

    double l2 = r.xp;
    double r2 = r.xp;
    if (r.w < 0) l2 += r.w;
    else
        r2 += r.w;
    if (l2 == r2)// null rect
        return false;

    if (l1 >= r2 || l2 >= r1) return false;

    double t1 = yp;
    double b1 = yp;
    if (h < 0) t1 += h;
    else
        b1 += h;
    if (t1 == b1)// null rect
        return false;

    double t2 = r.yp;
    double b2 = r.yp;
    if (r.h < 0) t2 += r.h;
    else
        b2 += r.h;
    if (t2 == b2)// null rect
        return false;

    if (t1 >= b2 || t2 >= b1) return false;

    return true;
}

Rect RectF::toAlignedRect() const noexcept
{
    int xmin = int(qFloor(xp));
    int xmax = int(qCeil(xp + w));
    int ymin = int(qFloor(yp));
    int ymax = int(qCeil(yp + h));
    return Rect(xmin, ymin, xmax - xmin, ymax - ymin);
}

}// namespace m2
