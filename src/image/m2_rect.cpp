#include <m2_rect.h>

namespace m2 {


/*****************************************************************************
  Rect  member functions
 *****************************************************************************/

Rect::Rect(int aleft, int atop, int awidth, int aheight) noexcept
    : x1(aleft), y1(atop), x2(aleft + awidth - 1), y2(atop + aheight - 1)
{
}

Rect::Rect(const Point &atopLeft, const Point &abottomRight) noexcept
    : x1(atopLeft.x()), y1(atopLeft.y()), x2(abottomRight.x()),
      y2(abottomRight.y())
{
}

Rect::Rect(const Point &atopLeft, const Size &asize) noexcept
    : x1(atopLeft.x()), y1(atopLeft.y()), x2(atopLeft.x() + asize.width() - 1),
      y2(atopLeft.y() + asize.height() - 1)
{
}

bool Rect::isNull() const noexcept { return x2 == x1 - 1 && y2 == y1 - 1; }

bool Rect::isEmpty() const noexcept { return x1 > x2 || y1 > y2; }

bool Rect::isValid() const noexcept { return x1 <= x2 && y1 <= y2; }

int Rect::left() const noexcept { return x1; }

int Rect::top() const noexcept { return y1; }

int Rect::right() const noexcept { return x2; }

int Rect::bottom() const noexcept { return y2; }

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

int Rect::x() const noexcept { return x1; }

int Rect::y() const noexcept { return y1; }

void Rect::setLeft(int pos) noexcept { x1 = pos; }

void Rect::setTop(int pos) noexcept { y1 = pos; }

void Rect::setRight(int pos) noexcept { x2 = pos; }

void Rect::setBottom(int pos) noexcept { y2 = pos; }

void Rect::setTopLeft(const Point &p) noexcept
{
    x1 = p.x();
    y1 = p.y();
}

void Rect::setBottomRight(const Point &p) noexcept
{
    x2 = p.x();
    y2 = p.y();
}

void Rect::setTopRight(const Point &p) noexcept
{
    x2 = p.x();
    y1 = p.y();
}

void Rect::setBottomLeft(const Point &p) noexcept
{
    x1 = p.x();
    y2 = p.y();
}

void Rect::setX(int ax) noexcept { x1 = ax; }

void Rect::setY(int ay) noexcept { y1 = ay; }

Point Rect::topLeft() const noexcept { return Point(x1, y1); }

Point Rect::bottomRight() const noexcept { return Point(x2, y2); }

Point Rect::topRight() const noexcept { return Point(x2, y1); }

Point Rect::bottomLeft() const noexcept { return Point(x1, y2); }

Point Rect::center() const noexcept
{
    return Point(int((int64_t(x1) + x2) / 2), int((int64_t(y1) + y2) / 2));
}

int Rect::width() const noexcept { return x2 - x1 + 1; }

int Rect::height() const noexcept { return y2 - y1 + 1; }

Size Rect::size() const noexcept { return Size(width(), height()); }

void Rect::translate(int dx, int dy) noexcept
{
    x1 += dx;
    y1 += dy;
    x2 += dx;
    y2 += dy;
}

void Rect::translate(const Point &p) noexcept
{
    x1 += p.x();
    y1 += p.y();
    x2 += p.x();
    y2 += p.y();
}

Rect Rect::translated(int dx, int dy) const noexcept
{
    return Rect(Point(x1 + dx, y1 + dy), Point(x2 + dx, y2 + dy));
}

Rect Rect::translated(const Point &p) const noexcept
{
    return Rect(Point(x1 + p.x(), y1 + p.y()), Point(x2 + p.x(), y2 + p.y()));
}

Rect Rect::transposed() const noexcept
{
    return Rect(topLeft(), size().transposed());
}

void Rect::moveTo(int ax, int ay) noexcept
{
    x2 += ax - x1;
    y2 += ay - y1;
    x1 = ax;
    y1 = ay;
}

void Rect::moveTo(const Point &p) noexcept
{
    x2 += p.x() - x1;
    y2 += p.y() - y1;
    x1 = p.x();
    y1 = p.y();
}

void Rect::moveLeft(int pos) noexcept
{
    x2 += (pos - x1);
    x1 = pos;
}

void Rect::moveTop(int pos) noexcept
{
    y2 += (pos - y1);
    y1 = pos;
}

void Rect::moveRight(int pos) noexcept
{
    x1 += (pos - x2);
    x2 = pos;
}

void Rect::moveBottom(int pos) noexcept
{
    y1 += (pos - y2);
    y2 = pos;
}

void Rect::moveTopLeft(const Point &p) noexcept
{
    moveLeft(p.x());
    moveTop(p.y());
}

void Rect::moveBottomRight(const Point &p) noexcept
{
    moveRight(p.x());
    moveBottom(p.y());
}

void Rect::moveTopRight(const Point &p) noexcept
{
    moveRight(p.x());
    moveTop(p.y());
}

void Rect::moveBottomLeft(const Point &p) noexcept
{
    moveLeft(p.x());
    moveBottom(p.y());
}

void Rect::moveCenter(const Point &p) noexcept
{
    int w = x2 - x1;
    int h = y2 - y1;
    x1 = p.x() - w / 2;
    y1 = p.y() - h / 2;
    x2 = x1 + w;
    y2 = y1 + h;
}

void Rect::getRect(int *ax, int *ay, int *aw, int *ah) const
{
    *ax = x1;
    *ay = y1;
    *aw = x2 - x1 + 1;
    *ah = y2 - y1 + 1;
}

void Rect::setRect(int ax, int ay, int aw, int ah) noexcept
{
    x1 = ax;
    y1 = ay;
    x2 = (ax + aw - 1);
    y2 = (ay + ah - 1);
}

void Rect::getCoords(int *xp1, int *yp1, int *xp2, int *yp2) const
{
    *xp1 = x1;
    *yp1 = y1;
    *xp2 = x2;
    *yp2 = y2;
}

void Rect::setCoords(int xp1, int yp1, int xp2, int yp2) noexcept
{
    x1 = xp1;
    y1 = yp1;
    x2 = xp2;
    y2 = yp2;
}

Rect Rect::adjusted(int xp1, int yp1, int xp2, int yp2) const noexcept
{
    return Rect(Point(x1 + xp1, y1 + yp1), Point(x2 + xp2, y2 + yp2));
}

void Rect::adjust(int dx1, int dy1, int dx2, int dy2) noexcept
{
    x1 += dx1;
    y1 += dy1;
    x2 += dx2;
    y2 += dy2;
}

void Rect::setWidth(int w) noexcept { x2 = (x1 + w - 1); }

void Rect::setHeight(int h) noexcept { y2 = (y1 + h - 1); }

void Rect::setSize(const Size &s) noexcept
{
    x2 = (s.width() + x1 - 1);
    y2 = (s.height() + y1 - 1);
}

bool Rect::contains(int ax, int ay, bool aproper) const noexcept
{
    return contains(Point(ax, ay), aproper);
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
    return false;
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

bool Rect::contains(int x, int y) const noexcept
{
    return contains(Point(x, y), false);
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

Rect &Rect::operator|=(const Rect &r) noexcept
{
    *this = *this | r;
    return *this;
}

Rect &Rect::operator&=(const Rect &r) noexcept
{
    *this = *this & r;
    return *this;
}

Rect Rect::intersected(const Rect &other) const noexcept
{
    return *this & other;
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

Rect Rect::united(const Rect &r) const noexcept { return *this | r; }

Rect Rect::marginsAdded(const Margins &margins) const noexcept
{
    return Rect(Point(x1 - margins.left(), y1 - margins.top()),
                Point(x2 + margins.right(), y2 + margins.bottom()));
}

Rect Rect::marginsRemoved(const Margins &margins) const noexcept
{
    return Rect(Point(x1 + margins.left(), y1 + margins.top()),
                Point(x2 - margins.right(), y2 - margins.bottom()));
}

Rect &Rect::operator+=(const Margins &margins) noexcept
{
    *this = marginsAdded(margins);
    return *this;
}

Rect &Rect::operator-=(const Margins &margins) noexcept
{
    *this = marginsRemoved(margins);
    return *this;
}

Rect Rect::span(const Point &p1, const Point &p2) noexcept
{
    return Rect(Point(qMin(p1.x(), p2.x()), qMin(p1.y(), p2.y())),
                Point(qMax(p1.x(), p2.x()), qMax(p1.y(), p2.y())));
}

/*****************************************************************************
  RectF  member functions
 *****************************************************************************/

RectF::RectF(double aleft, double atop, double awidth, double aheight) noexcept
    : xp(aleft), yp(atop), w(awidth), h(aheight)
{
}

RectF::RectF(const PointF &atopLeft, const SizeF &asize) noexcept
    : xp(atopLeft.x()), yp(atopLeft.y()), w(asize.width()), h(asize.height())
{
}


RectF::RectF(const PointF &atopLeft, const PointF &abottomRight) noexcept
    : xp(atopLeft.x()), yp(atopLeft.y()), w(abottomRight.x() - atopLeft.x()),
      h(abottomRight.y() - atopLeft.y())
{
}

RectF::RectF(const Rect &r) noexcept
    : xp(r.x()), yp(r.y()), w(r.width()), h(r.height())
{
}

bool RectF::isNull() const noexcept { return w == 0. && h == 0.; }

bool RectF::isEmpty() const noexcept { return w <= 0. || h <= 0.; }

bool RectF::isValid() const noexcept { return w > 0. && h > 0.; }

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

double RectF::x() const noexcept { return xp; }

double RectF::y() const noexcept { return yp; }

void RectF::setLeft(double pos) noexcept
{
    double diff = pos - xp;
    xp += diff;
    w -= diff;
}

void RectF::setRight(double pos) noexcept { w = pos - xp; }

void RectF::setTop(double pos) noexcept
{
    double diff = pos - yp;
    yp += diff;
    h -= diff;
}

void RectF::setBottom(double pos) noexcept { h = pos - yp; }

void RectF::setTopLeft(const PointF &p) noexcept
{
    setLeft(p.x());
    setTop(p.y());
}

void RectF::setTopRight(const PointF &p) noexcept
{
    setRight(p.x());
    setTop(p.y());
}

void RectF::setBottomLeft(const PointF &p) noexcept
{
    setLeft(p.x());
    setBottom(p.y());
}

void RectF::setBottomRight(const PointF &p) noexcept
{
    setRight(p.x());
    setBottom(p.y());
}

PointF RectF::center() const noexcept { return PointF(xp + w / 2, yp + h / 2); }

void RectF::moveLeft(double pos) noexcept { xp = pos; }

void RectF::moveTop(double pos) noexcept { yp = pos; }

void RectF::moveRight(double pos) noexcept { xp = pos - w; }

void RectF::moveBottom(double pos) noexcept { yp = pos - h; }

void RectF::moveTopLeft(const PointF &p) noexcept
{
    moveLeft(p.x());
    moveTop(p.y());
}

void RectF::moveTopRight(const PointF &p) noexcept
{
    moveRight(p.x());
    moveTop(p.y());
}

void RectF::moveBottomLeft(const PointF &p) noexcept
{
    moveLeft(p.x());
    moveBottom(p.y());
}

void RectF::moveBottomRight(const PointF &p) noexcept
{
    moveRight(p.x());
    moveBottom(p.y());
}

void RectF::moveCenter(const PointF &p) noexcept
{
    xp = p.x() - w / 2;
    yp = p.y() - h / 2;
}

double RectF::width() const noexcept { return w; }

double RectF::height() const noexcept { return h; }

SizeF RectF::size() const noexcept { return SizeF(w, h); }

void RectF::translate(double dx, double dy) noexcept
{
    xp += dx;
    yp += dy;
}

void RectF::translate(const PointF &p) noexcept
{
    xp += p.x();
    yp += p.y();
}

void RectF::moveTo(double ax, double ay) noexcept
{
    xp = ax;
    yp = ay;
}

void RectF::moveTo(const PointF &p) noexcept
{
    xp = p.x();
    yp = p.y();
}

RectF RectF::translated(double dx, double dy) const noexcept
{
    return RectF(xp + dx, yp + dy, w, h);
}

RectF RectF::translated(const PointF &p) const noexcept
{
    return RectF(xp + p.x(), yp + p.y(), w, h);
}

RectF RectF::transposed() const noexcept
{
    return RectF(topLeft(), size().transposed());
}

void RectF::getRect(double *ax, double *ay, double *aaw, double *aah) const
{
    *ax = this->xp;
    *ay = this->yp;
    *aaw = this->w;
    *aah = this->h;
}

void RectF::setRect(double ax, double ay, double aaw, double aah) noexcept
{
    this->xp = ax;
    this->yp = ay;
    this->w = aaw;
    this->h = aah;
}

void RectF::getCoords(double *xp1, double *yp1, double *xp2, double *yp2) const
{
    *xp1 = xp;
    *yp1 = yp;
    *xp2 = xp + w;
    *yp2 = yp + h;
}

void RectF::setCoords(double xp1, double yp1, double xp2, double yp2) noexcept
{
    xp = xp1;
    yp = yp1;
    w = xp2 - xp1;
    h = yp2 - yp1;
}

void RectF::adjust(double xp1, double yp1, double xp2, double yp2) noexcept
{
    xp += xp1;
    yp += yp1;
    w += xp2 - xp1;
    h += yp2 - yp1;
}

RectF RectF::adjusted(double xp1, double yp1, double xp2,
                      double yp2) const noexcept
{
    return RectF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1);
}

void RectF::setWidth(double aw) noexcept { this->w = aw; }

void RectF::setHeight(double ah) noexcept { this->h = ah; }

void RectF::setSize(const SizeF &s) noexcept
{
    w = s.width();
    h = s.height();
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

bool RectF::contains(double ax, double ay) const noexcept
{
    return contains(PointF(ax, ay));
}

RectF &RectF::operator|=(const RectF &r) noexcept
{
    *this = *this | r;
    return *this;
}

RectF &RectF::operator&=(const RectF &r) noexcept
{
    *this = *this & r;
    return *this;
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

RectF RectF::intersected(const RectF &r) const noexcept { return *this & r; }

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

RectF RectF::united(const RectF &r) const noexcept { return *this | r; }

RectF Rect::toRectF() const noexcept { return *this; }

Rect RectF::toRect() const noexcept
{
    const int nxp = qRound(xp);
    const int nyp = qRound(yp);
    const int nw = qRound(w + (xp - nxp) / 2);
    const int nh = qRound(h + (yp - nyp) / 2);
    return Rect(nxp, nyp, nw, nh);
}

Rect RectF::toAlignedRect() const noexcept
{
    int xmin = int(qFloor(xp));
    int xmax = int(qCeil(xp + w));
    int ymin = int(qFloor(yp));
    int ymax = int(qCeil(yp + h));
    return Rect(xmin, ymin, xmax - xmin, ymax - ymin);
}

RectF RectF::marginsAdded(const MarginsF &margins) const noexcept
{
    return RectF(PointF(xp - margins.left(), yp - margins.top()),
                 SizeF(w + margins.left() + margins.right(),
                       h + margins.top() + margins.bottom()));
}

RectF RectF::marginsRemoved(const MarginsF &margins) const noexcept
{
    return RectF(PointF(xp + margins.left(), yp + margins.top()),
                 SizeF(w - margins.left() - margins.right(),
                       h - margins.top() - margins.bottom()));
}

RectF &RectF::operator+=(const MarginsF &margins) noexcept
{
    *this = marginsAdded(margins);
    return *this;
}

RectF &RectF::operator-=(const MarginsF &margins) noexcept
{
    *this = marginsRemoved(margins);
    return *this;
}

}// namespace m2
