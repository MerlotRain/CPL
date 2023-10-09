#include <shape.h>

namespace m2 {

Rect Rect::Normalized() const noexcept
{
    Rect r;
    if (Right < Left - 1)
    {// swap bad x values
        r.Left = Right;
        r.Right = Left;
    }
    else
    {
        r.Left = Left;
        r.Right = Right;
    }
    if (Bottom < Top - 1)
    {// swap bad y values
        r.Top = Bottom;
        r.Bottom = Top;
    }
    else
    {
        r.Top = Top;
        r.Bottom = Bottom;
    }
    return r;
}

bool Rect::Intersects(const Rect &r) const noexcept
{
    if (IsNull() || r.IsNull())
        return false;

    int l1 = Left;
    int r1 = Left;
    if (Right - Left + 1 < 0)
        l1 = Right;
    else
        r1 = Right;

    int l2 = r.Left;
    int r2 = r.Left;
    if (r.Right - r.Left + 1 < 0)
        l2 = r.Right;
    else
        r2 = r.Right;

    if (l1 > r2 || l2 > r1)
        return false;

    int t1 = Top;
    int b1 = Top;
    if (Bottom - Top + 1 < 0)
        t1 = Bottom;
    else
        b1 = Bottom;

    int t2 = r.Top;
    int b2 = r.Top;
    if (r.Bottom - r.Top + 1 < 0)
        t2 = r.Bottom;
    else
        b2 = r.Bottom;

    if (t1 > b2 || t2 > b1)
        return false;

    return true;
}

bool Rect::Contains(const Rect &r, bool proper) const noexcept
{
    return Contains(r.TopLeft(), proper) && Contains(r.BottomRight(), proper);
}

bool Rect::Contains(const PT &p, bool proper) const noexcept
{
    int l, r;
    if (Right < Left - 1)
    {
        l = Right;
        r = Left;
    }
    else
    {
        l = Left;
        r = Right;
    }
    if (proper)
    {
        if (p.X <= l || p.X >= r)
            return false;
    }
    else
    {
        if (p.X < l || p.X > r)
            return false;
    }
    int t, b;
    if (Bottom < Top - 1)
    {
        t = Bottom;
        b = Top;
    }
    else
    {
        t = Top;
        b = Bottom;
    }
    if (proper)
    {
        if (p.Y <= t || p.Y >= b)
            return false;
    }
    else
    {
        if (p.Y < t || p.Y > b)
            return false;
    }
    return true;
}

Rect Rect::operator|(const Rect &r) const noexcept
{
    if (IsNull())
        return r;
    if (r.IsNull())
        return *this;

    int l1 = Left;
    int r1 = Left;
    if (Right - Left + 1 < 0)
        l1 = Right;
    else
        r1 = Right;

    int l2 = r.Left;
    int r2 = r.Left;
    if (r.Right - r.Left + 1 < 0)
        l2 = r.Right;
    else
        r2 = r.Right;

    int t1 = Top;
    int b1 = Top;
    if (Bottom - Top + 1 < 0)
        t1 = Bottom;
    else
        b1 = Bottom;

    int t2 = r.Top;
    int b2 = r.Top;
    if (r.Bottom - r.Top + 1 < 0)
        t2 = r.Bottom;
    else
        b2 = r.Bottom;

    Rect tmp;
    tmp.Left = Math::Min(l1, l2);
    tmp.Right = Math::Max(r1, r2);
    tmp.Top = Math::Min(t1, t2);
    tmp.Bottom = Math::Max(b1, b2);
    return tmp;
}

Rect Rect::operator&(const Rect &r) const noexcept
{
    if (IsNull() || r.IsNull())
        return Rect();

    int l1 = Left;
    int r1 = Left;
    if (Right - Left + 1 < 0)
        l1 = Right;
    else
        r1 = Right;

    int l2 = r.Left;
    int r2 = r.Left;
    if (r.Right - r.Left + 1 < 0)
        l2 = r.Right;
    else
        r2 = r.Right;

    if (l1 > r2 || l2 > r1)
        return Rect();

    int t1 = Top;
    int b1 = Top;
    if (Bottom - Top + 1 < 0)
        t1 = Bottom;
    else
        b1 = Bottom;

    int t2 = r.Top;
    int b2 = r.Top;
    if (r.Bottom - r.Top + 1 < 0)
        t2 = r.Bottom;
    else
        b2 = r.Bottom;

    if (t1 > b2 || t2 > b1)
        return Rect();

    Rect tmp;
    tmp.Left = Math::Max(l1, l2);
    tmp.Right = Math::Min(r1, r2);
    tmp.Top = Math::Max(t1, t2);
    tmp.Bottom = Math::Min(b1, b2);
    return tmp;
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
RectF RectF::Normalized() const noexcept
{
    RectF r;
    if (Right < Left - 1)
    {// swap bad x values
        r.Left = Right;
        r.Right = Left;
    }
    else
    {
        r.Left = Left;
        r.Right = Right;
    }
    if (Bottom < Top - 1)
    {// swap bad y values
        r.Top = Bottom;
        r.Bottom = Top;
    }
    else
    {
        r.Top = Top;
        r.Bottom = Bottom;
    }
    return r;
}

bool RectF::Contains(const PTF &p) const noexcept
{
    return true;
}

bool RectF::Contains(const RectF &r) const noexcept
{
    return true;
}

RectF RectF::operator|(const RectF &r) const noexcept
{
    return RectF();
}

RectF RectF::operator&(const RectF &r) const noexcept
{

    return RectF();
}

bool RectF::Intersects(const RectF &r) const noexcept
{
    return true;
}

Rect RectF::ToAlignedRect() const noexcept
{
    int xmin = int(floor(Left));
    int xmax = int(ceil(Right));
    int ymin = int(floor(Bottom));
    int ymax = int(ceil(Top));
    return Rect(xmin, ymin, xmax - xmin, ymax - ymin);
}


}// namespace m2
