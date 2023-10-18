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
    Rect() noexcept : x1(0), y1(0), x2(-1), y2(-1) {}
    Rect(const Point &topleft, const Point &bottomright) noexcept;
    Rect(const Point &topleft, const Size &size) noexcept;
    Rect(int left, int top, int width, int height) noexcept;

    bool isNull() const noexcept;
    bool isEmpty() const noexcept;
    bool isValid() const noexcept;

    int left() const noexcept;
    int top() const noexcept;
    int right() const noexcept;
    int bottom() const noexcept;
    [[nodiscard]] Rect normalized() const noexcept;

    int x() const noexcept;
    int y() const noexcept;
    void setLeft(int pos) noexcept;
    void setTop(int pos) noexcept;
    void setRight(int pos) noexcept;
    void setBottom(int pos) noexcept;
    void setX(int x) noexcept;
    void setY(int y) noexcept;

    void setTopLeft(const Point &p) noexcept;
    void setBottomRight(const Point &p) noexcept;
    void setTopRight(const Point &p) noexcept;
    void setBottomLeft(const Point &p) noexcept;

    Point topLeft() const noexcept;
    Point bottomRight() const noexcept;
    Point topRight() const noexcept;
    Point bottomLeft() const noexcept;
    Point center() const noexcept;

    void moveLeft(int pos) noexcept;
    void moveTop(int pos) noexcept;
    void moveRight(int pos) noexcept;
    void moveBottom(int pos) noexcept;
    void moveTopLeft(const Point &p) noexcept;
    void moveBottomRight(const Point &p) noexcept;
    void moveTopRight(const Point &p) noexcept;
    void moveBottomLeft(const Point &p) noexcept;
    void moveCenter(const Point &p) noexcept;

    void translate(int dx, int dy) noexcept;
    void translate(const Point &p) noexcept;
    [[nodiscard]] Rect translated(int dx, int dy) const noexcept;
    [[nodiscard]] Rect translated(const Point &p) const noexcept;
    [[nodiscard]] Rect transposed() const noexcept;

    void moveTo(int x, int t) noexcept;
    void moveTo(const Point &p) noexcept;

    void setRect(int x, int y, int w, int h) noexcept;
    void getRect(int *x, int *y, int *w, int *h) const;

    void setCoords(int x1, int y1, int x2, int y2) noexcept;
    void getCoords(int *x1, int *y1, int *x2, int *y2) const;

    void adjust(int x1, int y1, int x2, int y2) noexcept;
    [[nodiscard]] Rect adjusted(int x1, int y1, int x2, int y2) const noexcept;

    Size size() const noexcept;
    int width() const noexcept;
    int height() const noexcept;
    void setWidth(int w) noexcept;
    void setHeight(int h) noexcept;
    void setSize(const Size &s) noexcept;

    Rect operator|(const Rect &r) const noexcept;
    Rect operator&(const Rect &r) const noexcept;
    Rect &operator|=(const Rect &r) noexcept;
    Rect &operator&=(const Rect &r) noexcept;

    bool contains(const Rect &r, bool proper = false) const noexcept;
    bool contains(const Point &p, bool proper = false) const noexcept;
    bool contains(int x, int y) const noexcept;
    bool contains(int x, int y, bool proper) const noexcept;
    [[nodiscard]] Rect united(const Rect &other) const noexcept;
    [[nodiscard]] Rect intersected(const Rect &other) const noexcept;
    bool intersects(const Rect &r) const noexcept;

    Rect marginsAdded(const Margins &margins) const noexcept;
    Rect marginsRemoved(const Margins &margins) const noexcept;
    Rect &operator+=(const Margins &margins) noexcept;
    Rect &operator-=(const Margins &margins) noexcept;

    [[nodiscard]] static Rect span(const Point &p1, const Point &p2) noexcept;

    friend inline bool operator==(const Rect &r1, const Rect &r2) noexcept
    {
        return r1.x1 == r2.x1 && r1.x2 == r2.x2 && r1.y1 == r2.y1 &&
               r1.y2 == r2.y2;
    }
    friend inline bool operator!=(const Rect &r1, const Rect &r2) noexcept
    {
        return r1.x1 != r2.x1 || r1.x2 != r2.x2 || r1.y1 != r2.y1 ||
               r1.y2 != r2.y2;
    }
    [[nodiscard]] RectF toRectF() const noexcept;

    friend inline Rect operator+(const Rect &rectangle,
                                 const Margins &margins) noexcept
    {
        return Rect(Point(rectangle.left() - margins.left(),
                          rectangle.top() - margins.top()),
                    Point(rectangle.right() + margins.right(),
                          rectangle.bottom() + margins.bottom()));
    }
    friend inline Rect operator+(const Margins &margins,
                                 const Rect &rectangle) noexcept
    {
        return Rect(Point(rectangle.left() - margins.left(),
                          rectangle.top() - margins.top()),
                    Point(rectangle.right() + margins.right(),
                          rectangle.bottom() + margins.bottom()));
    }
    friend inline Rect operator-(const Rect &lhs, const Margins &rhs) noexcept
    {
        return Rect(
                Point(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
                Point(lhs.right() - rhs.right(), lhs.bottom() - rhs.bottom()));
    }

private:
    int x1;
    int y1;
    int x2;
    int y2;
};

class M2_API RectF
{
public:
    RectF() noexcept : xp(0.), yp(0.), w(0.), h(0.) {}
    RectF(const PointF &topleft, const SizeF &size) noexcept;
    RectF(const PointF &topleft, const PointF &bottomRight) noexcept;
    RectF(double left, double top, double width, double height) noexcept;
    RectF(const Rect &rect) noexcept;

    bool isNull() const noexcept;
    bool isEmpty() const noexcept;
    bool isValid() const noexcept;
    [[nodiscard]] RectF normalized() const noexcept;

    double left() const noexcept { return xp; }
    double top() const noexcept { return yp; }
    double right() const noexcept { return xp + w; }
    double bottom() const noexcept { return yp + h; }

    double x() const noexcept;
    double y() const noexcept;
    void setLeft(double pos) noexcept;
    void setTop(double pos) noexcept;
    void setRight(double pos) noexcept;
    void setBottom(double pos) noexcept;
    void setX(double pos) noexcept { setLeft(pos); }
    void setY(double pos) noexcept { setTop(pos); }

    PointF topLeft() const noexcept { return PointF(xp, yp); }
    PointF bottomRight() const noexcept { return PointF(xp + w, yp + h); }
    PointF topRight() const noexcept { return PointF(xp + w, yp); }
    PointF bottomLeft() const noexcept { return PointF(xp, yp + h); }
    PointF center() const noexcept;

    void setTopLeft(const PointF &p) noexcept;
    void setBottomRight(const PointF &p) noexcept;
    void setTopRight(const PointF &p) noexcept;
    void setBottomLeft(const PointF &p) noexcept;

    void moveLeft(double pos) noexcept;
    void moveTop(double pos) noexcept;
    void moveRight(double pos) noexcept;
    void moveBottom(double pos) noexcept;
    void moveTopLeft(const PointF &p) noexcept;
    void moveBottomRight(const PointF &p) noexcept;
    void moveTopRight(const PointF &p) noexcept;
    void moveBottomLeft(const PointF &p) noexcept;
    void moveCenter(const PointF &p) noexcept;

    void translate(double dx, double dy) noexcept;
    void translate(const PointF &p) noexcept;

    [[nodiscard]] RectF translated(double dx, double dy) const noexcept;
    [[nodiscard]] RectF translated(const PointF &p) const noexcept;

    [[nodiscard]] RectF transposed() const noexcept;

    void moveTo(double x, double y) noexcept;
    void moveTo(const PointF &p) noexcept;

    void setRect(double x, double y, double w, double h) noexcept;
    void getRect(double *x, double *y, double *w, double *h) const;

    void setCoords(double x1, double y1, double x2, double y2) noexcept;
    void getCoords(double *x1, double *y1, double *x2, double *y2) const;

    void adjust(double x1, double y1, double x2, double y2) noexcept;
    [[nodiscard]] RectF adjusted(double x1, double y1, double x2,
                                 double y2) const noexcept;

    SizeF size() const noexcept;
    double width() const noexcept;
    double height() const noexcept;
    void setWidth(double w) noexcept;
    void setHeight(double h) noexcept;
    void setSize(const SizeF &s) noexcept;

    RectF operator|(const RectF &r) const noexcept;
    RectF operator&(const RectF &r) const noexcept;
    RectF &operator|=(const RectF &r) noexcept;
    RectF &operator&=(const RectF &r) noexcept;

    bool contains(const RectF &r) const noexcept;
    bool contains(const PointF &p) const noexcept;
    bool contains(double x, double y) const noexcept;
    [[nodiscard]] RectF united(const RectF &other) const noexcept;
    [[nodiscard]] RectF intersected(const RectF &other) const noexcept;
    bool intersects(const RectF &r) const noexcept;

    RectF marginsAdded(const MarginsF &margins) const noexcept;
    RectF marginsRemoved(const MarginsF &margins) const noexcept;
    RectF &operator+=(const MarginsF &margins) noexcept;
    RectF &operator-=(const MarginsF &margins) noexcept;

    friend inline bool operator==(const RectF &r1, const RectF &r2) noexcept
    {
        return r1.topLeft() == r2.topLeft() && r1.size() == r2.size();
    }
    friend inline bool operator!=(const RectF &r1, const RectF &r2) noexcept
    {
        return r1.topLeft() != r2.topLeft() || r1.size() != r2.size();
    }

    [[nodiscard]] Rect toRect() const noexcept;
    [[nodiscard]] Rect toAlignedRect() const noexcept;

    friend inline RectF operator+(const RectF &lhs,
                                  const MarginsF &rhs) noexcept
    {
        return RectF(PointF(lhs.left() - rhs.left(), lhs.top() - rhs.top()),
                     SizeF(lhs.width() + rhs.left() + rhs.right(),
                           lhs.height() + rhs.top() + rhs.bottom()));
    }
    friend inline RectF operator+(const MarginsF &lhs,
                                  const RectF &rhs) noexcept
    {
        return RectF(PointF(rhs.left() - lhs.left(), rhs.top() - lhs.top()),
                     SizeF(rhs.width() + lhs.left() + lhs.right(),
                           rhs.height() + lhs.top() + lhs.bottom()));
    }
    friend inline RectF operator-(const RectF &lhs,
                                  const MarginsF &rhs) noexcept
    {
        return RectF(PointF(lhs.left() + rhs.left(), lhs.top() + rhs.top()),
                     SizeF(lhs.width() - rhs.left() - rhs.right(),
                           lhs.height() - rhs.top() - rhs.bottom()));
    }

private:
    double xp;
    double yp;
    double w;
    double h;
};

}// namespace m2

#endif//M2_RECT_H_