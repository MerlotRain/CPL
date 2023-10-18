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

#ifndef M2_RECT_H_
#define M2_RECT_H_

#include <m2_margins.h>
#include <m2_point.h>
#include <m2_size.h>

namespace m2 {

class RectF;
class M2_API Rect
{
public:
    constexpr Rect() noexcept : x1(0), y1(0), x2(-1), y2(-1) {}
    constexpr Rect(const Point &topleft, const Point &bottomright) noexcept;
    constexpr Rect(const Point &topleft, const Size &size) noexcept;
    constexpr Rect(int left, int top, int width, int height) noexcept;

    constexpr inline bool isNull() const noexcept;
    constexpr inline bool isEmpty() const noexcept;
    constexpr inline bool isValid() const noexcept;

    constexpr inline int left() const noexcept;
    constexpr inline int top() const noexcept;
    constexpr inline int right() const noexcept;
    constexpr inline int bottom() const noexcept;
    [[nodiscard]] Rect normalized() const noexcept;

    constexpr inline int x() const noexcept;
    constexpr inline int y() const noexcept;
    constexpr inline void setLeft(int pos) noexcept;
    constexpr inline void setTop(int pos) noexcept;
    constexpr inline void setRight(int pos) noexcept;
    constexpr inline void setBottom(int pos) noexcept;
    constexpr inline void setX(int x) noexcept;
    constexpr inline void setY(int y) noexcept;

    constexpr inline void setTopLeft(const Point &p) noexcept;
    constexpr inline void setBottomRight(const Point &p) noexcept;
    constexpr inline void setTopRight(const Point &p) noexcept;
    constexpr inline void setBottomLeft(const Point &p) noexcept;

    constexpr inline Point topLeft() const noexcept;
    constexpr inline Point bottomRight() const noexcept;
    constexpr inline Point topRight() const noexcept;
    constexpr inline Point bottomLeft() const noexcept;
    constexpr inline Point center() const noexcept;

    constexpr inline void moveLeft(int pos) noexcept;
    constexpr inline void moveTop(int pos) noexcept;
    constexpr inline void moveRight(int pos) noexcept;
    constexpr inline void moveBottom(int pos) noexcept;
    constexpr inline void moveTopLeft(const Point &p) noexcept;
    constexpr inline void moveBottomRight(const Point &p) noexcept;
    constexpr inline void moveTopRight(const Point &p) noexcept;
    constexpr inline void moveBottomLeft(const Point &p) noexcept;
    constexpr inline void moveCenter(const Point &p) noexcept;

    constexpr inline void translate(int dx, int dy) noexcept;
    constexpr inline void translate(const Point &p) noexcept;
    [[nodiscard]] constexpr inline Rect translated(int dx,
                                                   int dy) const noexcept;
    [[nodiscard]] constexpr inline Rect
    translated(const Point &p) const noexcept;
    [[nodiscard]] constexpr inline Rect transposed() const noexcept;

    constexpr inline void moveTo(int x, int t) noexcept;
    constexpr inline void moveTo(const Point &p) noexcept;

    constexpr inline void setRect(int x, int y, int w, int h) noexcept;
    constexpr inline void getRect(int *x, int *y, int *w, int *h) const;

    constexpr inline void setCoords(int x1, int y1, int x2, int y2) noexcept;
    constexpr inline void getCoords(int *x1, int *y1, int *x2, int *y2) const;

    constexpr inline void adjust(int x1, int y1, int x2, int y2) noexcept;
    [[nodiscard]] constexpr inline Rect adjusted(int x1, int y1, int x2,
                                                 int y2) const noexcept;

    constexpr inline Size size() const noexcept;
    constexpr inline int width() const noexcept;
    constexpr inline int height() const noexcept;
    constexpr inline void setWidth(int w) noexcept;
    constexpr inline void setHeight(int h) noexcept;
    constexpr inline void setSize(const Size &s) noexcept;

    Rect operator|(const Rect &r) const noexcept;
    Rect operator&(const Rect &r) const noexcept;
    inline Rect &operator|=(const Rect &r) noexcept;
    inline Rect &operator&=(const Rect &r) noexcept;

    bool contains(const Rect &r, bool proper = false) const noexcept;
    bool contains(const Point &p, bool proper = false) const noexcept;
    inline bool contains(int x, int y) const noexcept;
    inline bool contains(int x, int y, bool proper) const noexcept;
    [[nodiscard]] inline Rect united(const Rect &other) const noexcept;
    [[nodiscard]] inline Rect intersected(const Rect &other) const noexcept;
    bool intersects(const Rect &r) const noexcept;

    constexpr inline Rect marginsAdded(const Margins &margins) const noexcept;
    constexpr inline Rect marginsRemoved(const Margins &margins) const noexcept;
    constexpr inline Rect &operator+=(const Margins &margins) noexcept;
    constexpr inline Rect &operator-=(const Margins &margins) noexcept;

    [[nodiscard]] static constexpr inline Rect span(const Point &p1,
                                                    const Point &p2) noexcept;

    friend constexpr inline bool operator==(const Rect &r1,
                                            const Rect &r2) noexcept
    {
        return r1.x1 == r2.x1 && r1.x2 == r2.x2 && r1.y1 == r2.y1 &&
               r1.y2 == r2.y2;
    }
    friend constexpr inline bool operator!=(const Rect &r1,
                                            const Rect &r2) noexcept
    {
        return r1.x1 != r2.x1 || r1.x2 != r2.x2 || r1.y1 != r2.y1 ||
               r1.y2 != r2.y2;
    }
    [[nodiscard]] constexpr inline RectF toRectF() const noexcept;

private:
    int x1;
    int y1;
    int x2;
    int y2;
};

class M2_API RectF
{
public:
    constexpr RectF() noexcept : xp(0.), yp(0.), w(0.), h(0.) {}
    constexpr RectF(const PointF &topleft, const SizeF &size) noexcept;
    constexpr RectF(const PointF &topleft, const PointF &bottomRight) noexcept;
    constexpr RectF(double left, double top, double width,
                    double height) noexcept;
    constexpr RectF(const Rect &rect) noexcept;

    constexpr inline bool isNull() const noexcept;
    constexpr inline bool isEmpty() const noexcept;
    constexpr inline bool isValid() const noexcept;
    [[nodiscard]] RectF normalized() const noexcept;

    constexpr inline double left() const noexcept { return xp; }
    constexpr inline double top() const noexcept { return yp; }
    constexpr inline double right() const noexcept { return xp + w; }
    constexpr inline double bottom() const noexcept { return yp + h; }

    constexpr inline double x() const noexcept;
    constexpr inline double y() const noexcept;
    constexpr inline void setLeft(double pos) noexcept;
    constexpr inline void setTop(double pos) noexcept;
    constexpr inline void setRight(double pos) noexcept;
    constexpr inline void setBottom(double pos) noexcept;
    constexpr inline void setX(double pos) noexcept { setLeft(pos); }
    constexpr inline void setY(double pos) noexcept { setTop(pos); }

    constexpr inline PointF topLeft() const noexcept { return PointF(xp, yp); }
    constexpr inline PointF bottomRight() const noexcept
    {
        return PointF(xp + w, yp + h);
    }
    constexpr inline PointF topRight() const noexcept
    {
        return PointF(xp + w, yp);
    }
    constexpr inline PointF bottomLeft() const noexcept
    {
        return PointF(xp, yp + h);
    }
    constexpr inline PointF center() const noexcept;

    constexpr inline void setTopLeft(const PointF &p) noexcept;
    constexpr inline void setBottomRight(const PointF &p) noexcept;
    constexpr inline void setTopRight(const PointF &p) noexcept;
    constexpr inline void setBottomLeft(const PointF &p) noexcept;

    constexpr inline void moveLeft(double pos) noexcept;
    constexpr inline void moveTop(double pos) noexcept;
    constexpr inline void moveRight(double pos) noexcept;
    constexpr inline void moveBottom(double pos) noexcept;
    constexpr inline void moveTopLeft(const PointF &p) noexcept;
    constexpr inline void moveBottomRight(const PointF &p) noexcept;
    constexpr inline void moveTopRight(const PointF &p) noexcept;
    constexpr inline void moveBottomLeft(const PointF &p) noexcept;
    constexpr inline void moveCenter(const PointF &p) noexcept;

    constexpr inline void translate(double dx, double dy) noexcept;
    constexpr inline void translate(const PointF &p) noexcept;

    [[nodiscard]] constexpr inline RectF translated(double dx,
                                                    double dy) const noexcept;
    [[nodiscard]] constexpr inline RectF
    translated(const PointF &p) const noexcept;

    [[nodiscard]] constexpr inline RectF transposed() const noexcept;

    constexpr inline void moveTo(double x, double y) noexcept;
    constexpr inline void moveTo(const PointF &p) noexcept;

    constexpr inline void setRect(double x, double y, double w,
                                  double h) noexcept;
    constexpr inline void getRect(double *x, double *y, double *w,
                                  double *h) const;

    constexpr inline void setCoords(double x1, double y1, double x2,
                                    double y2) noexcept;
    constexpr inline void getCoords(double *x1, double *y1, double *x2,
                                    double *y2) const;

    constexpr inline void adjust(double x1, double y1, double x2,
                                 double y2) noexcept;
    [[nodiscard]] constexpr inline RectF
    adjusted(double x1, double y1, double x2, double y2) const noexcept;

    constexpr inline SizeF size() const noexcept;
    constexpr inline double width() const noexcept;
    constexpr inline double height() const noexcept;
    constexpr inline void setWidth(double w) noexcept;
    constexpr inline void setHeight(double h) noexcept;
    constexpr inline void setSize(const SizeF &s) noexcept;

    RectF operator|(const RectF &r) const noexcept;
    RectF operator&(const RectF &r) const noexcept;
    inline RectF &operator|=(const RectF &r) noexcept;
    inline RectF &operator&=(const RectF &r) noexcept;

    bool contains(const RectF &r) const noexcept;
    bool contains(const PointF &p) const noexcept;
    inline bool contains(double x, double y) const noexcept;
    [[nodiscard]] inline RectF united(const RectF &other) const noexcept;
    [[nodiscard]] inline RectF intersected(const RectF &other) const noexcept;
    bool intersects(const RectF &r) const noexcept;

    constexpr inline RectF marginsAdded(const MarginsF &margins) const noexcept;
    constexpr inline RectF
    marginsRemoved(const MarginsF &margins) const noexcept;
    constexpr inline RectF &operator+=(const MarginsF &margins) noexcept;
    constexpr inline RectF &operator-=(const MarginsF &margins) noexcept;

    friend constexpr inline bool operator==(const RectF &r1,
                                            const RectF &r2) noexcept
    {
        return r1.topLeft() == r2.topLeft() && r1.size() == r2.size();
    }
    friend constexpr inline bool operator!=(const RectF &r1,
                                            const RectF &r2) noexcept
    {
        return r1.topLeft() != r2.topLeft() || r1.size() != r2.size();
    }

    [[nodiscard]] constexpr inline Rect toRect() const noexcept;
    [[nodiscard]] Rect toAlignedRect() const noexcept;


private:
    double xp;
    double yp;
    double w;
    double h;
};

/*****************************************************************************
  Rect inline member functions
 *****************************************************************************/

constexpr inline Rect::Rect(int aleft, int atop, int awidth,
                            int aheight) noexcept
    : x1(aleft), y1(atop), x2(aleft + awidth - 1), y2(atop + aheight - 1)
{
}

constexpr inline Rect::Rect(const Point &atopLeft,
                            const Point &abottomRight) noexcept
    : x1(atopLeft.x()), y1(atopLeft.y()), x2(abottomRight.x()),
      y2(abottomRight.y())
{
}

constexpr inline Rect::Rect(const Point &atopLeft, const Size &asize) noexcept
    : x1(atopLeft.x()), y1(atopLeft.y()), x2(atopLeft.x() + asize.width() - 1),
      y2(atopLeft.y() + asize.height() - 1)
{
}

constexpr inline bool Rect::isNull() const noexcept
{
    return x2 == x1 - 1 && y2 == y1 - 1;
}

constexpr inline bool Rect::isEmpty() const noexcept
{
    return x1 > x2 || y1 > y2;
}

constexpr inline bool Rect::isValid() const noexcept
{
    return x1 <= x2 && y1 <= y2;
}

constexpr inline int Rect::left() const noexcept { return x1; }

constexpr inline int Rect::top() const noexcept { return y1; }

constexpr inline int Rect::right() const noexcept { return x2; }

constexpr inline int Rect::bottom() const noexcept { return y2; }

constexpr inline int Rect::x() const noexcept { return x1; }

constexpr inline int Rect::y() const noexcept { return y1; }

constexpr inline void Rect::setLeft(int pos) noexcept { x1 = pos; }

constexpr inline void Rect::setTop(int pos) noexcept { y1 = pos; }

constexpr inline void Rect::setRight(int pos) noexcept { x2 = pos; }

constexpr inline void Rect::setBottom(int pos) noexcept { y2 = pos; }

constexpr inline void Rect::setTopLeft(const Point &p) noexcept
{
    x1 = p.x();
    y1 = p.y();
}

constexpr inline void Rect::setBottomRight(const Point &p) noexcept
{
    x2 = p.x();
    y2 = p.y();
}

constexpr inline void Rect::setTopRight(const Point &p) noexcept
{
    x2 = p.x();
    y1 = p.y();
}

constexpr inline void Rect::setBottomLeft(const Point &p) noexcept
{
    x1 = p.x();
    y2 = p.y();
}

constexpr inline void Rect::setX(int ax) noexcept { x1 = ax; }

constexpr inline void Rect::setY(int ay) noexcept { y1 = ay; }

constexpr inline Point Rect::topLeft() const noexcept { return Point(x1, y1); }

constexpr inline Point Rect::bottomRight() const noexcept
{
    return Point(x2, y2);
}

constexpr inline Point Rect::topRight() const noexcept { return Point(x2, y1); }

constexpr inline Point Rect::bottomLeft() const noexcept
{
    return Point(x1, y2);
}

constexpr inline Point Rect::center() const noexcept
{
    return Point(int((int64_t(x1) + x2) / 2), int((int64_t(y1) + y2) / 2));
}

constexpr inline int Rect::width() const noexcept { return x2 - x1 + 1; }

constexpr inline int Rect::height() const noexcept { return y2 - y1 + 1; }

constexpr inline Size Rect::size() const noexcept
{
    return Size(width(), height());
}

constexpr inline void Rect::translate(int dx, int dy) noexcept
{
    x1 += dx;
    y1 += dy;
    x2 += dx;
    y2 += dy;
}

constexpr inline void Rect::translate(const Point &p) noexcept
{
    x1 += p.x();
    y1 += p.y();
    x2 += p.x();
    y2 += p.y();
}

constexpr inline Rect Rect::translated(int dx, int dy) const noexcept
{
    return Rect(Point(x1 + dx, y1 + dy), Point(x2 + dx, y2 + dy));
}

constexpr inline Rect Rect::translated(const Point &p) const noexcept
{
    return Rect(Point(x1 + p.x(), y1 + p.y()), Point(x2 + p.x(), y2 + p.y()));
}

constexpr inline Rect Rect::transposed() const noexcept
{
    return Rect(topLeft(), size().transposed());
}

constexpr inline void Rect::moveTo(int ax, int ay) noexcept
{
    x2 += ax - x1;
    y2 += ay - y1;
    x1 = ax;
    y1 = ay;
}

constexpr inline void Rect::moveTo(const Point &p) noexcept
{
    x2 += p.x() - x1;
    y2 += p.y() - y1;
    x1 = p.x();
    y1 = p.y();
}

constexpr inline void Rect::moveLeft(int pos) noexcept
{
    x2 += (pos - x1);
    x1 = pos;
}

constexpr inline void Rect::moveTop(int pos) noexcept
{
    y2 += (pos - y1);
    y1 = pos;
}

constexpr inline void Rect::moveRight(int pos) noexcept
{
    x1 += (pos - x2);
    x2 = pos;
}

constexpr inline void Rect::moveBottom(int pos) noexcept
{
    y1 += (pos - y2);
    y2 = pos;
}

constexpr inline void Rect::moveTopLeft(const Point &p) noexcept
{
    moveLeft(p.x());
    moveTop(p.y());
}

constexpr inline void Rect::moveBottomRight(const Point &p) noexcept
{
    moveRight(p.x());
    moveBottom(p.y());
}

constexpr inline void Rect::moveTopRight(const Point &p) noexcept
{
    moveRight(p.x());
    moveTop(p.y());
}

constexpr inline void Rect::moveBottomLeft(const Point &p) noexcept
{
    moveLeft(p.x());
    moveBottom(p.y());
}

constexpr inline void Rect::moveCenter(const Point &p) noexcept
{
    int w = x2 - x1;
    int h = y2 - y1;
    x1 = p.x() - w / 2;
    y1 = p.y() - h / 2;
    x2 = x1 + w;
    y2 = y1 + h;
}

constexpr inline void Rect::getRect(int *ax, int *ay, int *aw, int *ah) const
{
    *ax = x1;
    *ay = y1;
    *aw = x2 - x1 + 1;
    *ah = y2 - y1 + 1;
}

constexpr inline void Rect::setRect(int ax, int ay, int aw, int ah) noexcept
{
    x1 = ax;
    y1 = ay;
    x2 = (ax + aw - 1);
    y2 = (ay + ah - 1);
}

constexpr inline void Rect::getCoords(int *xp1, int *yp1, int *xp2,
                                      int *yp2) const
{
    *xp1 = x1;
    *yp1 = y1;
    *xp2 = x2;
    *yp2 = y2;
}

constexpr inline void Rect::setCoords(int xp1, int yp1, int xp2,
                                      int yp2) noexcept
{
    x1 = xp1;
    y1 = yp1;
    x2 = xp2;
    y2 = yp2;
}

constexpr inline Rect Rect::adjusted(int xp1, int yp1, int xp2,
                                     int yp2) const noexcept
{
    return Rect(Point(x1 + xp1, y1 + yp1), Point(x2 + xp2, y2 + yp2));
}

constexpr inline void Rect::adjust(int dx1, int dy1, int dx2, int dy2) noexcept
{
    x1 += dx1;
    y1 += dy1;
    x2 += dx2;
    y2 += dy2;
}

constexpr inline void Rect::setWidth(int w) noexcept { x2 = (x1 + w - 1); }

constexpr inline void Rect::setHeight(int h) noexcept { y2 = (y1 + h - 1); }

constexpr inline void Rect::setSize(const Size &s) noexcept
{
    x2 = (s.width() + x1 - 1);
    y2 = (s.height() + y1 - 1);
}

inline bool Rect::contains(int ax, int ay, bool aproper) const noexcept
{
    return contains(Point(ax, ay), aproper);
}

inline bool Rect::contains(int ax, int ay) const noexcept
{
    return contains(Point(ax, ay), false);
}

inline Rect &Rect::operator|=(const Rect &r) noexcept
{
    *this = *this | r;
    return *this;
}

inline Rect &Rect::operator&=(const Rect &r) noexcept
{
    *this = *this & r;
    return *this;
}

inline Rect Rect::intersected(const Rect &other) const noexcept
{
    return *this & other;
}

inline Rect Rect::united(const Rect &r) const noexcept { return *this | r; }

constexpr inline Rect operator+(const Rect &rectangle,
                                const Margins &margins) noexcept
{
    return Rect(Point(rectangle.left() - margins.left(),
                      rectangle.top() - margins.top()),
                Point(rectangle.right() + margins.right(),
                      rectangle.bottom() + margins.bottom()));
}

constexpr inline Rect operator+(const Margins &margins,
                                const Rect &rectangle) noexcept
{
    return Rect(Point(rectangle.left() - margins.left(),
                      rectangle.top() - margins.top()),
                Point(rectangle.right() + margins.right(),
                      rectangle.bottom() + margins.bottom()));
}

constexpr inline Rect operator-(const Rect &lhs, const Margins &rhs) noexcept
{
    return Rect(Point(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
                Point(lhs.right() - rhs.right(), lhs.bottom() - rhs.bottom()));
}

constexpr inline Rect Rect::marginsAdded(const Margins &margins) const noexcept
{
    return Rect(Point(x1 - margins.left(), y1 - margins.top()),
                Point(x2 + margins.right(), y2 + margins.bottom()));
}

constexpr inline Rect
Rect::marginsRemoved(const Margins &margins) const noexcept
{
    return Rect(Point(x1 + margins.left(), y1 + margins.top()),
                Point(x2 - margins.right(), y2 - margins.bottom()));
}

constexpr inline Rect &Rect::operator+=(const Margins &margins) noexcept
{
    *this = marginsAdded(margins);
    return *this;
}

constexpr inline Rect &Rect::operator-=(const Margins &margins) noexcept
{
    *this = marginsRemoved(margins);
    return *this;
}

constexpr Rect Rect::span(const Point &p1, const Point &p2) noexcept
{
    return Rect(Point(qMin(p1.x(), p2.x()), qMin(p1.y(), p2.y())),
                Point(qMax(p1.x(), p2.x()), qMax(p1.y(), p2.y())));
}


/*****************************************************************************
  RectF inline member functions
 *****************************************************************************/

constexpr inline RectF::RectF(double aleft, double atop, double awidth,
                              double aheight) noexcept
    : xp(aleft), yp(atop), w(awidth), h(aheight)
{
}

constexpr inline RectF::RectF(const PointF &atopLeft,
                              const SizeF &asize) noexcept
    : xp(atopLeft.x()), yp(atopLeft.y()), w(asize.width()), h(asize.height())
{
}


constexpr inline RectF::RectF(const PointF &atopLeft,
                              const PointF &abottomRight) noexcept
    : xp(atopLeft.x()), yp(atopLeft.y()), w(abottomRight.x() - atopLeft.x()),
      h(abottomRight.y() - atopLeft.y())
{
}

constexpr inline RectF::RectF(const Rect &r) noexcept
    : xp(r.x()), yp(r.y()), w(r.width()), h(r.height())
{
}

constexpr inline bool RectF::isNull() const noexcept
{
    return w == 0. && h == 0.;
}

constexpr inline bool RectF::isEmpty() const noexcept
{
    return w <= 0. || h <= 0.;
}

constexpr inline bool RectF::isValid() const noexcept
{
    return w > 0. && h > 0.;
}

constexpr inline double RectF::x() const noexcept { return xp; }

constexpr inline double RectF::y() const noexcept { return yp; }

constexpr inline void RectF::setLeft(double pos) noexcept
{
    double diff = pos - xp;
    xp += diff;
    w -= diff;
}

constexpr inline void RectF::setRight(double pos) noexcept { w = pos - xp; }

constexpr inline void RectF::setTop(double pos) noexcept
{
    double diff = pos - yp;
    yp += diff;
    h -= diff;
}

constexpr inline void RectF::setBottom(double pos) noexcept { h = pos - yp; }

constexpr inline void RectF::setTopLeft(const PointF &p) noexcept
{
    setLeft(p.x());
    setTop(p.y());
}

constexpr inline void RectF::setTopRight(const PointF &p) noexcept
{
    setRight(p.x());
    setTop(p.y());
}

constexpr inline void RectF::setBottomLeft(const PointF &p) noexcept
{
    setLeft(p.x());
    setBottom(p.y());
}

constexpr inline void RectF::setBottomRight(const PointF &p) noexcept
{
    setRight(p.x());
    setBottom(p.y());
}

constexpr inline PointF RectF::center() const noexcept
{
    return PointF(xp + w / 2, yp + h / 2);
}

constexpr inline void RectF::moveLeft(double pos) noexcept { xp = pos; }

constexpr inline void RectF::moveTop(double pos) noexcept { yp = pos; }

constexpr inline void RectF::moveRight(double pos) noexcept { xp = pos - w; }

constexpr inline void RectF::moveBottom(double pos) noexcept { yp = pos - h; }

constexpr inline void RectF::moveTopLeft(const PointF &p) noexcept
{
    moveLeft(p.x());
    moveTop(p.y());
}

constexpr inline void RectF::moveTopRight(const PointF &p) noexcept
{
    moveRight(p.x());
    moveTop(p.y());
}

constexpr inline void RectF::moveBottomLeft(const PointF &p) noexcept
{
    moveLeft(p.x());
    moveBottom(p.y());
}

constexpr inline void RectF::moveBottomRight(const PointF &p) noexcept
{
    moveRight(p.x());
    moveBottom(p.y());
}

constexpr inline void RectF::moveCenter(const PointF &p) noexcept
{
    xp = p.x() - w / 2;
    yp = p.y() - h / 2;
}

constexpr inline double RectF::width() const noexcept { return w; }

constexpr inline double RectF::height() const noexcept { return h; }

constexpr inline SizeF RectF::size() const noexcept { return SizeF(w, h); }

constexpr inline void RectF::translate(double dx, double dy) noexcept
{
    xp += dx;
    yp += dy;
}

constexpr inline void RectF::translate(const PointF &p) noexcept
{
    xp += p.x();
    yp += p.y();
}

constexpr inline void RectF::moveTo(double ax, double ay) noexcept
{
    xp = ax;
    yp = ay;
}

constexpr inline void RectF::moveTo(const PointF &p) noexcept
{
    xp = p.x();
    yp = p.y();
}

constexpr inline RectF RectF::translated(double dx, double dy) const noexcept
{
    return RectF(xp + dx, yp + dy, w, h);
}

constexpr inline RectF RectF::translated(const PointF &p) const noexcept
{
    return RectF(xp + p.x(), yp + p.y(), w, h);
}

constexpr inline RectF RectF::transposed() const noexcept
{
    return RectF(topLeft(), size().transposed());
}

constexpr inline void RectF::getRect(double *ax, double *ay, double *aaw,
                                     double *aah) const
{
    *ax = this->xp;
    *ay = this->yp;
    *aaw = this->w;
    *aah = this->h;
}

constexpr inline void RectF::setRect(double ax, double ay, double aaw,
                                     double aah) noexcept
{
    this->xp = ax;
    this->yp = ay;
    this->w = aaw;
    this->h = aah;
}

constexpr inline void RectF::getCoords(double *xp1, double *yp1, double *xp2,
                                       double *yp2) const
{
    *xp1 = xp;
    *yp1 = yp;
    *xp2 = xp + w;
    *yp2 = yp + h;
}

constexpr inline void RectF::setCoords(double xp1, double yp1, double xp2,
                                       double yp2) noexcept
{
    xp = xp1;
    yp = yp1;
    w = xp2 - xp1;
    h = yp2 - yp1;
}

constexpr inline void RectF::adjust(double xp1, double yp1, double xp2,
                                    double yp2) noexcept
{
    xp += xp1;
    yp += yp1;
    w += xp2 - xp1;
    h += yp2 - yp1;
}

constexpr inline RectF RectF::adjusted(double xp1, double yp1, double xp2,
                                       double yp2) const noexcept
{
    return RectF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1);
}

constexpr inline void RectF::setWidth(double aw) noexcept { this->w = aw; }

constexpr inline void RectF::setHeight(double ah) noexcept { this->h = ah; }

constexpr inline void RectF::setSize(const SizeF &s) noexcept
{
    w = s.width();
    h = s.height();
}

inline bool RectF::contains(double ax, double ay) const noexcept
{
    return contains(PointF(ax, ay));
}

inline RectF &RectF::operator|=(const RectF &r) noexcept
{
    *this = *this | r;
    return *this;
}

inline RectF &RectF::operator&=(const RectF &r) noexcept
{
    *this = *this & r;
    return *this;
}

inline RectF RectF::intersected(const RectF &r) const noexcept
{
    return *this & r;
}

inline RectF RectF::united(const RectF &r) const noexcept { return *this | r; }

constexpr RectF Rect::toRectF() const noexcept { return *this; }

constexpr inline Rect RectF::toRect() const noexcept
{
    const int nxp = qRound(xp);
    const int nyp = qRound(yp);
    const int nw = qRound(w + (xp - nxp) / 2);
    const int nh = qRound(h + (yp - nyp) / 2);
    return Rect(nxp, nyp, nw, nh);
}

constexpr inline RectF operator+(const RectF &lhs, const MarginsF &rhs) noexcept
{
    return RectF(PointF(lhs.left() - rhs.left(), lhs.top() - rhs.top()),
                 SizeF(lhs.width() + rhs.left() + rhs.right(),
                       lhs.height() + rhs.top() + rhs.bottom()));
}

constexpr inline RectF operator+(const MarginsF &lhs, const RectF &rhs) noexcept
{
    return RectF(PointF(rhs.left() - lhs.left(), rhs.top() - lhs.top()),
                 SizeF(rhs.width() + lhs.left() + lhs.right(),
                       rhs.height() + lhs.top() + lhs.bottom()));
}

constexpr inline RectF operator-(const RectF &lhs, const MarginsF &rhs) noexcept
{
    return RectF(PointF(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
                 SizeF(lhs.width() - rhs.left() - rhs.right(),
                       lhs.height() - rhs.top() - rhs.bottom()));
}

constexpr inline RectF
RectF::marginsAdded(const MarginsF &margins) const noexcept
{
    return RectF(PointF(xp - margins.left(), yp - margins.top()),
                 SizeF(w + margins.left() + margins.right(),
                       h + margins.top() + margins.bottom()));
}

constexpr inline RectF
RectF::marginsRemoved(const MarginsF &margins) const noexcept
{
    return RectF(PointF(xp + margins.left(), yp + margins.top()),
                 SizeF(w - margins.left() - margins.right(),
                       h - margins.top() - margins.bottom()));
}

constexpr inline RectF &RectF::operator+=(const MarginsF &margins) noexcept
{
    *this = marginsAdded(margins);
    return *this;
}

constexpr inline RectF &RectF::operator-=(const MarginsF &margins) noexcept
{
    *this = marginsRemoved(margins);
    return *this;
}

}// namespace m2

#endif//M2_RECT_H_