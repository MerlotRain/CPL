#include "image.h"
#include "mathhelp.h"

namespace m2 {

/*****************************************************************************
  GsPT inline functions
 *****************************************************************************/
inline GsPT::GsPT() : X(0), Y(0) {}

inline GsPT::GsPT(int xpos, int ypos) : X(xpos), Y(ypos) {}

inline bool GsPT::IsNull() const
{
    return X == 0 && Y == 0;
}

inline int GsPT::ManhattanLength() const
{
    return Math::Abs(X) + Math::Abs(Y);
}

inline GsPT &GsPT::operator+=(const GsPT &p)
{
    X += p.X;
    Y += p.Y;
    return *this;
}

inline GsPT &GsPT::operator-=(const GsPT &p)
{
    X -= p.X;
    Y -= p.Y;
    return *this;
}

inline GsPT &GsPT::operator*=(float factor)
{
    X = Math::Round(X * factor);
    Y = Math::Round(Y * factor);
    return *this;
}

inline GsPT &GsPT::operator*=(int factor)
{
    X = X * factor;
    Y = Y * factor;
    return *this;
}

inline bool operator==(const GsPT &p1, const GsPT &p2)
{
    return p1.X == p2.X && p1.Y == p2.Y;
}

inline bool operator!=(const GsPT &p1, const GsPT &p2)
{
    return p1.X != p2.X || p1.Y != p2.Y;
}

inline const GsPT operator+(const GsPT &p1, const GsPT &p2)
{
    return GsPT(p1.X + p2.X, p1.Y + p2.Y);
}

inline const GsPT operator-(const GsPT &p1, const GsPT &p2)
{
    return GsPT(p1.X - p2.X, p1.Y - p2.Y);
}

inline const GsPT operator*(const GsPT &p, float factor)
{
    return GsPT(Math::Round(p.X * factor), Math::Round(p.Y * factor));
}

inline const GsPT operator*(const GsPT &p, int factor)
{
    return GsPT(p.X * factor, p.Y * factor);
}

inline const GsPT operator*(float factor, const GsPT &p)
{
    return GsPT(Math::Round(p.X * factor), Math::Round(p.Y * factor));
}

inline const GsPT operator*(int factor, const GsPT &p)
{
    return GsPT(p.X * factor, p.Y * factor);
}

inline const GsPT operator+(const GsPT &p)
{
    return p;
}

inline const GsPT operator-(const GsPT &p)
{
    return GsPT(-p.X, -p.Y);
}

inline GsPT &GsPT::operator/=(float c)
{
    X = Math::Round(X / c);
    Y = Math::Round(Y / c);
    return *this;
}

inline int GsPT::DotProduct(const GsPT &p1, const GsPT &p2)
{
    return p1.X * p2.X + p1.Y * p2.Y;
}

inline const GsPT operator/(const GsPT &p, float c)
{
    return GsPT(Math::Round(p.X / c), Math::Round(p.Y / c));
}


/*****************************************************************************
  GsPTF inline functions
 *****************************************************************************/
inline GsPTF::GsPTF() : X(0), Y(0) {}

inline GsPTF::GsPTF(float xpos, float ypos) : X(xpos), Y(ypos) {}

inline GsPTF::GsPTF(const GsPT &p) : X(p.X), Y(p.Y) {}

inline float GsPTF::ManhattanLength() const
{
    return Math::Abs(X) + Math::Abs(Y);
}

inline bool GsPTF::IsNull() const
{
    return Math::IsNull(X) && Math::IsNull(Y);
}

inline GsPTF &GsPTF::operator+=(const GsPTF &p)
{
    X += p.X;
    Y += p.Y;
    return *this;
}

inline GsPTF &GsPTF::operator-=(const GsPTF &p)
{
    X -= p.X;
    Y -= p.Y;
    return *this;
}

inline GsPTF &GsPTF::operator*=(float c)
{
    X *= c;
    Y *= c;
    return *this;
}

inline bool operator==(const GsPTF &p1, const GsPTF &p2)
{
    return ((!p1.X || !p2.X) ? Math::FuzzyIsNull(p1.X - p2.X) : Math::FuzzyCompare(p1.X, p2.X)) && ((!p1.Y || !p2.Y) ? Math::FuzzyIsNull(p1.Y - p2.Y) : Math::FuzzyCompare(p1.Y, p2.Y));
}

inline bool operator!=(const GsPTF &p1, const GsPTF &p2)
{
    return !(p1 == p2);
}

inline const GsPTF operator+(const GsPTF &p1, const GsPTF &p2)
{
    return GsPTF(p1.X + p2.X, p1.Y + p2.Y);
}

inline const GsPTF operator-(const GsPTF &p1, const GsPTF &p2)
{
    return GsPTF(p1.X - p2.X, p1.Y - p2.Y);
}

inline const GsPTF operator*(const GsPTF &p, float c)
{
    return GsPTF(p.X * c, p.Y * c);
}

inline const GsPTF operator*(float c, const GsPTF &p)
{
    return GsPTF(p.X * c, p.Y * c);
}

inline const GsPTF operator+(const GsPTF &p)
{
    return p;
}

inline const GsPTF operator-(const GsPTF &p)
{
    return GsPTF(-p.X, -p.Y);
}

inline GsPTF &GsPTF::operator/=(float divisor)
{
    X /= divisor;
    Y /= divisor;
    return *this;
}

inline float GsPTF::DotProduct(const GsPTF &p1, const GsPTF &p2)
{
    return p1.X * p2.X + p1.Y * p2.Y;
}

inline const GsPTF operator/(const GsPTF &p, float divisor)
{
    return GsPTF(p.X / divisor, p.Y / divisor);
}

inline GsPT GsPTF::ToPoint() const
{
    return GsPT(Math::Round(X), Math::Round(Y));
}


/*****************************************************************************
  GsSize inline functions
 *****************************************************************************/
inline GsSize::GsSize() noexcept : Width(-1), Height(-1) {}

inline GsSize::GsSize(int w, int h) noexcept : Width(w), Height(h) {}

inline bool GsSize::IsNull() const noexcept
{
    return Width == 0 && Height == 0;
}

inline bool GsSize::IsEmpty() const noexcept
{
    return Width < 1 || Height < 1;
}

inline bool GsSize::IsValid() const noexcept
{
    return Width >= 0 && Height >= 0;
}

inline GsSize GsSize::Transposed() const noexcept
{
    return GsSize(Height, Width);
}

inline void GsSize::Scale(int w, int h, GsAspectRatioMode mode) noexcept
{
    Scale(GsSize(w, h), mode);
}

inline void GsSize::Scale(const GsSize &s, GsAspectRatioMode mode) noexcept
{
    *this = Scaled(s, mode);
}

inline GsSize GsSize::Scaled(int w, int h, GsAspectRatioMode mode) const noexcept
{
    return Scaled(GsSize(w, h), mode);
}

inline GsSize &GsSize::operator+=(const GsSize &s) noexcept
{
    Width += s.Width;
    Height += s.Height;
    return *this;
}

inline GsSize &GsSize::operator-=(const GsSize &s) noexcept
{
    Width -= s.Width;
    Height -= s.Height;
    return *this;
}

inline GsSize &GsSize::operator*=(float c) noexcept
{
    Width = Math::Round(Width * c);
    Height = Math::Round(Height * c);
    return *this;
}

inline bool operator==(const GsSize &s1, const GsSize &s2) noexcept
{
    return s1.Width == s2.Width && s1.Height == s2.Height;
}

inline bool operator!=(const GsSize &s1, const GsSize &s2) noexcept
{
    return s1.Width != s2.Width || s1.Height != s2.Height;
}

inline const GsSize operator+(const GsSize &s1, const GsSize &s2) noexcept
{
    return GsSize(s1.Width + s2.Width, s1.Height + s2.Height);
}

inline const GsSize operator-(const GsSize &s1, const GsSize &s2) noexcept
{
    return GsSize(s1.Width - s2.Width, s1.Height - s2.Height);
}

inline const GsSize operator*(const GsSize &s, float c) noexcept
{
    return GsSize(Math::Round(s.Width * c), Math::Round(s.Height * c));
}

inline const GsSize operator*(float c, const GsSize &s) noexcept
{
    return GsSize(Math::Round(s.Width * c), Math::Round(s.Height * c));
}

inline GsSize &GsSize::operator/=(float c)
{
    assert(!Math::FuzzyIsNull(c));
    Width = Math::Round(Width / c);
    Height = Math::Round(Height / c);
    return *this;
}

inline const GsSize operator/(const GsSize &s, float c)
{
    assert(!Math::FuzzyIsNull(c));
    return GsSize(Math::Round(s.Width / c), Math::Round(s.Height / c));
}

inline GsSize GsSize::ExpandedTo(const GsSize &otherSize) const noexcept
{
    return GsSize(Math::Max(Width, otherSize.Width), Math::Max(Height, otherSize.Height));
}

inline GsSize GsSize::BoundedTo(const GsSize &otherSize) const noexcept
{
    return GsSize(Math::Min(Width, otherSize.Width), Math::Min(Height, otherSize.Height));
}

inline GsSize GsSize::GrownBy(GsMargins m) const noexcept
{
    return {Width + m.Left + m.Right, Height + m.Top + m.Bottom};
}

inline GsSize GsSize::ShrunkBy(GsMargins m) const noexcept
{
    return {Width - m.Left - m.Right, Height - m.Top - m.Bottom};
}


/*****************************************************************************
  GsSizeF inline functions
 *****************************************************************************/
inline GsSizeF::GsSizeF() noexcept : Width(-1.), Height(-1.) {}

inline GsSizeF::GsSizeF(const GsSize &sz) noexcept : Width(sz.Width), Height(sz.Height) {}

inline GsSizeF::GsSizeF(float w, float h) noexcept : Width(w), Height(h) {}

inline bool GsSizeF::IsNull() const noexcept
{
    return Math::IsNull(Width) && Math::IsNull(Height);
}

inline bool GsSizeF::IsEmpty() const noexcept
{
    return Width <= 0. || Height <= 0.;
}

inline bool GsSizeF::IsValid() const noexcept
{
    return Width >= 0. && Height >= 0.;
}

inline GsSizeF GsSizeF::Transposed() const noexcept
{
    return GsSizeF(Height, Width);
}

inline void GsSizeF::Scale(float w, float h, GsAspectRatioMode mode) noexcept
{
    Scale(GsSizeF(w, h), mode);
}

inline void GsSizeF::Scale(const GsSizeF &s, GsAspectRatioMode mode) noexcept
{
    *this = Scaled(s, mode);
}

inline GsSizeF GsSizeF::Scaled(float w, float h, GsAspectRatioMode mode) const noexcept
{
    return Scaled(GsSizeF(w, h), mode);
}

inline GsSizeF &GsSizeF::operator+=(const GsSizeF &s) noexcept
{
    Width += s.Width;
    Height += s.Height;
    return *this;
}

inline GsSizeF &GsSizeF::operator-=(const GsSizeF &s) noexcept
{
    Width -= s.Width;
    Height -= s.Height;
    return *this;
}

inline GsSizeF &GsSizeF::operator*=(float c) noexcept
{
    Width *= c;
    Height *= c;
    return *this;
}

inline bool operator==(const GsSizeF &s1, const GsSizeF &s2) noexcept
{
    return Math::FuzzyCompare(s1.Width, s2.Width) && Math::FuzzyCompare(s1.Height, s2.Height);
}

inline bool operator!=(const GsSizeF &s1, const GsSizeF &s2) noexcept
{
    return !Math::FuzzyCompare(s1.Width, s2.Width) || !Math::FuzzyCompare(s1.Height, s2.Height);
}

inline const GsSizeF operator+(const GsSizeF &s1, const GsSizeF &s2) noexcept
{
    return GsSizeF(s1.Width + s2.Width, s1.Height + s2.Height);
}

inline const GsSizeF operator-(const GsSizeF &s1, const GsSizeF &s2) noexcept
{
    return GsSizeF(s1.Width - s2.Width, s1.Height - s2.Height);
}

inline const GsSizeF operator*(const GsSizeF &s, float c) noexcept
{
    return GsSizeF(s.Width * c, s.Height * c);
}

inline const GsSizeF operator*(float c, const GsSizeF &s) noexcept
{
    return GsSizeF(s.Width * c, s.Height * c);
}

inline GsSizeF &GsSizeF::operator/=(float c)
{
    assert(!Math::FuzzyIsNull(c));
    Width = Width / c;
    Height = Height / c;
    return *this;
}

inline const GsSizeF operator/(const GsSizeF &s, float c)
{
    assert(!Math::FuzzyIsNull(c));
    return GsSizeF(s.Width / c, s.Height / c);
}

inline GsSizeF GsSizeF::ExpandedTo(const GsSizeF &otherSize) const noexcept
{
    return GsSizeF(Math::Max(Width, otherSize.Width), Math::Max(Height, otherSize.Height));
}

inline GsSizeF GsSizeF::BoundedTo(const GsSizeF &otherSize) const noexcept
{
    return GsSizeF(Math::Min(Width, otherSize.Width), Math::Min(Height, otherSize.Height));
}

inline GsSizeF GsSizeF::GrownBy(GsMarginsF m) const noexcept
{
    return {Width + m.Left + m.Right, Height + m.Top + m.Bottom};
}

inline GsSizeF GsSizeF::ShrunkBy(GsMarginsF m) const noexcept
{
    return {Width - m.Left - m.Right, Height - m.Top - m.Bottom};
}

inline GsSize GsSizeF::toSize() const noexcept
{
    return GsSize(Math::Round(Width), Math::Round(Height));
}


/*****************************************************************************
  GsMargins inline functions
 *****************************************************************************/
inline GsMargins::GsMargins() noexcept : Left(0), Top(0), Right(0), Bottom(0) {}

inline GsMargins::GsMargins(int aleft, int atop, int aright, int abottom) noexcept
    : Left(aleft), Top(atop), Right(aright), Bottom(abottom) {}

inline bool GsMargins::IsNull() const noexcept
{
    return Left == 0 && Top == 0 && Right == 0 && Bottom == 0;
}

inline bool operator==(const GsMargins &m1, const GsMargins &m2) noexcept
{
    return m1.Left == m2.Left &&
           m1.Top == m2.Top &&
           m1.Right == m2.Right &&
           m1.Bottom == m2.Bottom;
}

inline bool operator!=(const GsMargins &m1, const GsMargins &m2) noexcept
{
    return m1.Left != m2.Left ||
           m1.Top != m2.Top ||
           m1.Right != m2.Right ||
           m1.Bottom != m2.Bottom;
}

inline GsMargins operator+(const GsMargins &m1, const GsMargins &m2) noexcept
{
    return GsMargins(m1.Left + m2.Left, m1.Top + m2.Top,
                     m1.Right + m2.Right, m1.Bottom + m2.Bottom);
}

inline GsMargins operator-(const GsMargins &m1, const GsMargins &m2) noexcept
{
    return GsMargins(m1.Left - m2.Left, m1.Top - m2.Top,
                     m1.Right - m2.Right, m1.Bottom - m2.Bottom);
}

inline GsMargins operator+(const GsMargins &lhs, int rhs) noexcept
{
    return GsMargins(lhs.Left + rhs, lhs.Top + rhs,
                     lhs.Right + rhs, lhs.Bottom + rhs);
}

inline GsMargins operator+(int lhs, const GsMargins &rhs) noexcept
{
    return GsMargins(rhs.Left + lhs, rhs.Top + lhs,
                     rhs.Right + lhs, rhs.Bottom + lhs);
}

inline GsMargins operator-(const GsMargins &lhs, int rhs) noexcept
{
    return GsMargins(lhs.Left - rhs, lhs.Top - rhs,
                     lhs.Right - rhs, lhs.Bottom - rhs);
}

inline GsMargins operator*(const GsMargins &margins, int factor) noexcept
{
    return GsMargins(margins.Left * factor, margins.Top * factor,
                     margins.Right * factor, margins.Bottom * factor);
}

inline GsMargins operator*(int factor, const GsMargins &margins) noexcept
{
    return GsMargins(margins.Left * factor, margins.Top * factor,
                     margins.Right * factor, margins.Bottom * factor);
}

inline GsMargins operator*(const GsMargins &margins, float factor) noexcept
{
    return GsMargins(Math::Round(margins.Left * factor), Math::Round(margins.Top * factor),
                     Math::Round(margins.Right * factor), Math::Round(margins.Bottom * factor));
}

inline GsMargins operator*(float factor, const GsMargins &margins) noexcept
{
    return GsMargins(Math::Round(margins.Left * factor), Math::Round(margins.Top * factor),
                     Math::Round(margins.Right * factor), Math::Round(margins.Bottom * factor));
}

inline GsMargins operator/(const GsMargins &margins, int divisor)
{
    return GsMargins(margins.Left / divisor, margins.Top / divisor,
                     margins.Right / divisor, margins.Bottom / divisor);
}

inline GsMargins operator/(const GsMargins &margins, float divisor)
{
    return GsMargins(Math::Round(margins.Left / divisor), Math::Round(margins.Top / divisor),
                     Math::Round(margins.Right / divisor), Math::Round(margins.Bottom / divisor));
}

inline GsMargins &GsMargins::operator+=(const GsMargins &margins) noexcept
{
    return *this = *this + margins;
}

inline GsMargins &GsMargins::operator-=(const GsMargins &margins) noexcept
{
    return *this = *this - margins;
}

inline GsMargins &GsMargins::operator+=(int margin) noexcept
{
    Left += margin;
    Top += margin;
    Right += margin;
    Bottom += margin;
    return *this;
}

inline GsMargins &GsMargins::operator-=(int margin) noexcept
{
    Left -= margin;
    Top -= margin;
    Right -= margin;
    Bottom -= margin;
    return *this;
}

inline GsMargins &GsMargins::operator*=(int factor) noexcept
{
    return *this = *this * factor;
}

inline GsMargins &GsMargins::operator/=(int divisor)
{
    return *this = *this / divisor;
}

inline GsMargins &GsMargins::operator*=(float factor) noexcept
{
    return *this = *this * factor;
}

inline GsMargins &GsMargins::operator/=(float divisor)
{
    return *this = *this / divisor;
}

inline GsMargins operator+(const GsMargins &margins) noexcept
{
    return margins;
}

inline GsMargins operator-(const GsMargins &margins) noexcept
{
    return GsMargins(-margins.Left, -margins.Top, -margins.Right, -margins.Bottom);
}


/*****************************************************************************
  GsMarginsF inline functions
 *****************************************************************************/
inline GsMarginsF::GsMarginsF() noexcept
    : Left(0), Top(0), Right(0), Bottom(0) {}

inline GsMarginsF::GsMarginsF(float aleft, float atop, float aright, float abottom) noexcept
    : Left(aleft), Top(atop), Right(aright), Bottom(abottom) {}

inline GsMarginsF::GsMarginsF(const GsMargins &margins) noexcept
    : Left(margins.Left), Top(margins.Top), Right(margins.Right), Bottom(margins.Bottom) {}

inline bool GsMarginsF::IsNull() const noexcept
{
    return Math::FuzzyIsNull(Left) && Math::FuzzyIsNull(Top) && Math::FuzzyIsNull(Right) && Math::FuzzyIsNull(Bottom);
}

inline bool operator==(const GsMarginsF &lhs, const GsMarginsF &rhs) noexcept
{
    return Math::FuzzyCompare(lhs.Left, rhs.Left) && Math::FuzzyCompare(lhs.Top, rhs.Top) && Math::FuzzyCompare(lhs.Right, rhs.Right) && Math::FuzzyCompare(lhs.Bottom, rhs.Bottom);
}

inline bool operator!=(const GsMarginsF &lhs, const GsMarginsF &rhs) noexcept
{
    return !operator==(lhs, rhs);
}

inline GsMarginsF operator+(const GsMarginsF &lhs, const GsMarginsF &rhs) noexcept
{
    return GsMarginsF(lhs.Left + rhs.Left, lhs.Top + rhs.Top,
                      lhs.Right + rhs.Right, lhs.Bottom + rhs.Bottom);
}

inline GsMarginsF operator-(const GsMarginsF &lhs, const GsMarginsF &rhs) noexcept
{
    return GsMarginsF(lhs.Left - rhs.Left, lhs.Top - rhs.Top,
                      lhs.Right - rhs.Right, lhs.Bottom - rhs.Bottom);
}

inline GsMarginsF operator+(const GsMarginsF &lhs, float rhs) noexcept
{
    return GsMarginsF(lhs.Left + rhs, lhs.Top + rhs,
                      lhs.Right + rhs, lhs.Bottom + rhs);
}

inline GsMarginsF operator+(float lhs, const GsMarginsF &rhs) noexcept
{
    return GsMarginsF(rhs.Left + lhs, rhs.Top + lhs,
                      rhs.Right + lhs, rhs.Bottom + lhs);
}

inline GsMarginsF operator-(const GsMarginsF &lhs, float rhs) noexcept
{
    return GsMarginsF(lhs.Left - rhs, lhs.Top - rhs,
                      lhs.Right - rhs, lhs.Bottom - rhs);
}

inline GsMarginsF operator*(const GsMarginsF &lhs, float rhs) noexcept
{
    return GsMarginsF(lhs.Left * rhs, lhs.Top * rhs,
                      lhs.Right * rhs, lhs.Bottom * rhs);
}

inline GsMarginsF operator*(float lhs, const GsMarginsF &rhs) noexcept
{
    return GsMarginsF(rhs.Left * lhs, rhs.Top * lhs,
                      rhs.Right * lhs, rhs.Bottom * lhs);
}

inline GsMarginsF operator/(const GsMarginsF &lhs, float divisor)
{
    return GsMarginsF(lhs.Left / divisor, lhs.Top / divisor,
                      lhs.Right / divisor, lhs.Bottom / divisor);
}

inline GsMarginsF &GsMarginsF::operator+=(const GsMarginsF &margins) noexcept
{
    return *this = *this + margins;
}

inline GsMarginsF &GsMarginsF::operator-=(const GsMarginsF &margins) noexcept
{
    return *this = *this - margins;
}

inline GsMarginsF &GsMarginsF::operator+=(float addend) noexcept
{
    Left += addend;
    Top += addend;
    Right += addend;
    Bottom += addend;
    return *this;
}

inline GsMarginsF &GsMarginsF::operator-=(float subtrahend) noexcept
{
    Left -= subtrahend;
    Top -= subtrahend;
    Right -= subtrahend;
    Bottom -= subtrahend;
    return *this;
}

inline GsMarginsF &GsMarginsF::operator*=(float factor) noexcept
{
    return *this = *this * factor;
}

inline GsMarginsF &GsMarginsF::operator/=(float divisor)
{
    return *this = *this / divisor;
}

inline GsMarginsF operator+(const GsMarginsF &margins) noexcept
{
    return margins;
}

inline GsMarginsF operator-(const GsMarginsF &margins) noexcept
{
    return GsMarginsF(-margins.Left, -margins.Top, -margins.Right, -margins.Bottom);
}

inline GsMargins GsMarginsF::toMargins() const noexcept
{
    return GsMargins(Math::Round(Left), Math::Round(Top), Math::Round(Right), Math::Round(Bottom));
}


/*****************************************************************************
  GsRect inline member functions
 *****************************************************************************/

inline GsRect::GsRect() noexcept
    : Left(0), Top(0), Right(-1), Bottom(-1) {}

inline GsRect::GsRect(int aleft, int atop, int awidth, int aheight) noexcept
    : Left(aleft), Top(atop), Right(aleft + awidth - 1), Bottom(atop + aheight - 1) {}

inline GsRect::GsRect(const GsPT &atopLeft, const GsPT &abottomRight) noexcept
    : Left(atopLeft.X), Top(atopLeft.Y), Right(abottomRight.X), Bottom(abottomRight.Y) {}

inline GsRect::GsRect(const GsPT &atopLeft, const GsSize &asize) noexcept
    : Left(atopLeft.X), Top(atopLeft.Y), Right(atopLeft.X + asize.Width - 1), Bottom(atopLeft.Y + asize.Height - 1) {}

inline bool GsRect::IsNull() const noexcept
{
    return Right == Left - 1 && Bottom == Top - 1;
}

inline bool GsRect::IsEmpty() const noexcept
{
    return Left > Right || Top > Bottom;
}

inline bool GsRect::IsValid() const noexcept
{
    return Left <= Right && Top <= Bottom;
}

inline void GsRect::TopLeft(const GsPT &p) noexcept
{
    Left = p.X;
    Top = p.Y;
}

inline void GsRect::BottomRight(const GsPT &p) noexcept
{
    Right = p.X;
    Bottom = p.Y;
}

inline void GsRect::TopRight(const GsPT &p) noexcept
{
    Right = p.X;
    Top = p.Y;
}

inline void GsRect::BottomLeft(const GsPT &p) noexcept
{
    Left = p.X;
    Bottom = p.Y;
}


inline GsPT GsRect::TopLeft() const noexcept
{
    return GsPT(Left, Top);
}

inline GsPT GsRect::BottomRight() const noexcept
{
    return GsPT(Right, Bottom);
}

inline GsPT GsRect::TopRight() const noexcept
{
    return GsPT(Right, Top);
}

inline GsPT GsRect::BottomLeft() const noexcept
{
    return GsPT(Left, Bottom);
}

inline GsPT GsRect::Center() const noexcept
{
    return GsPT(int((int64_t(Left) + Right) / 2), int((int64_t(Top) + Bottom) / 2));
}

inline int GsRect::Width() const noexcept
{
    return Right - Left + 1;
}

inline int GsRect::Height() const noexcept
{
    return Bottom - Top + 1;
}

inline GsSize GsRect::Size() const noexcept
{
    return GsSize(Width(), Height());
}

inline void GsRect::Translate(int dx, int dy) noexcept
{
    Left += dx;
    Top += dy;
    Right += dx;
    Bottom += dy;
}

inline void GsRect::Translate(const GsPT &p) noexcept
{
    Left += p.X;
    Top += p.Y;
    Right += p.X;
    Bottom += p.Y;
}

inline GsRect GsRect::Translated(int dx, int dy) const noexcept
{
    return GsRect(GsPT(Left + dx, Top + dy), GsPT(Right + dx, Bottom + dy));
}

inline GsRect GsRect::Translated(const GsPT &p) const noexcept
{
    return GsRect(GsPT(Left + p.X, Top + p.Y), GsPT(Right + p.X, Bottom + p.Y));
}

inline GsRect GsRect::Transposed() const noexcept
{
    return GsRect(TopLeft(), Size().Transposed());
}

inline void GsRect::MoveTo(int ax, int ay) noexcept
{
    Right += ax - Left;
    Bottom += ay - Top;
    Left = ax;
    Top = ay;
}

inline void GsRect::MoveTo(const GsPT &p) noexcept
{
    Right += p.X - Left;
    Bottom += p.Y - Top;
    Left = p.X;
    Top = p.Y;
}

inline void GsRect::MoveLeft(int pos) noexcept
{
    Right += (pos - Left);
    Left = pos;
}

inline void GsRect::MoveTop(int pos) noexcept
{
    Bottom += (pos - Top);
    Top = pos;
}

inline void GsRect::MoveRight(int pos) noexcept
{
    Left += (pos - Right);
    Right = pos;
}

inline void GsRect::MoveBottom(int pos) noexcept
{
    Top += (pos - Bottom);
    Bottom = pos;
}

inline void GsRect::MoveTopLeft(const GsPT &p) noexcept
{
    MoveLeft(p.X);
    MoveTop(p.Y);
}

inline void GsRect::MoveBottomRight(const GsPT &p) noexcept
{
    MoveRight(p.X);
    MoveBottom(p.Y);
}

inline void GsRect::MoveTopRight(const GsPT &p) noexcept
{
    MoveRight(p.X);
    MoveTop(p.Y);
}

inline void GsRect::MoveBottomLeft(const GsPT &p) noexcept
{
    MoveLeft(p.X);
    MoveBottom(p.Y);
}

inline void GsRect::MoveCenter(const GsPT &p) noexcept
{
    int w = Right - Left;
    int h = Bottom - Top;
    Left = p.X - w / 2;
    Top = p.Y - h / 2;
    Right = Left + w;
    Bottom = Top + h;
}

inline void GsRect::Rect(int *ax, int *ay, int *aw, int *ah) const
{
    *ax = Left;
    *ay = Top;
    *aw = Right - Left + 1;
    *ah = Bottom - Top + 1;
}

inline void GsRect::Rect(int ax, int ay, int aw, int ah) noexcept
{
    Left = ax;
    Top = ay;
    Right = (ax + aw - 1);
    Bottom = (ay + ah - 1);
}

inline void GsRect::Coords(int *xp1, int *yp1, int *xp2, int *yp2) const
{
    *xp1 = Left;
    *yp1 = Top;
    *xp2 = Right;
    *yp2 = Bottom;
}

inline void GsRect::Coords(int xp1, int yp1, int xp2, int yp2) noexcept
{
    Left = xp1;
    Top = yp1;
    Right = xp2;
    Bottom = yp2;
}

inline GsRect GsRect::Adjusted(int xp1, int yp1, int xp2, int yp2) const noexcept
{
    return GsRect(GsPT(Left + xp1, Top + yp1), GsPT(Right + xp2, Bottom + yp2));
}

inline void GsRect::Adjust(int dLeft, int dTop, int dRight, int dBottom) noexcept
{
    Left += dLeft;
    Top += dTop;
    Right += dRight;
    Bottom += dBottom;
}

inline void GsRect::Width(int w) noexcept
{
    Right = (Left + w - 1);
}

inline void GsRect::Height(int h) noexcept
{
    Bottom = (Top + h - 1);
}

inline void GsRect::Size(const GsSize &s) noexcept
{
    Right = (s.Width + Left - 1);
    Bottom = (s.Height + Top - 1);
}

inline bool GsRect::Contains(int ax, int ay, bool aproper) const noexcept
{
    return Contains(GsPT(ax, ay), aproper);
}

inline bool GsRect::Contains(int ax, int ay) const noexcept
{
    return Contains(GsPT(ax, ay), false);
}

inline GsRect &GsRect::operator|=(const GsRect &r) noexcept
{
    *this = *this | r;
    return *this;
}

inline GsRect &GsRect::operator&=(const GsRect &r) noexcept
{
    *this = *this & r;
    return *this;
}

inline GsRect GsRect::Intersected(const GsRect &other) const noexcept
{
    return *this & other;
}

inline GsRect GsRect::United(const GsRect &r) const noexcept
{
    return *this | r;
}

inline bool operator==(const GsRect &r1, const GsRect &r2) noexcept
{
    return r1.Left == r2.Left && r1.Right == r2.Right && r1.Top == r2.Top && r1.Bottom == r2.Bottom;
}

inline bool operator!=(const GsRect &r1, const GsRect &r2) noexcept
{
    return r1.Left != r2.Left || r1.Right != r2.Right || r1.Top != r2.Top || r1.Bottom != r2.Bottom;
}

inline GsRect operator+(const GsRect &rectangle, const GsMargins &margins) noexcept
{
    return GsRect(GsPT(rectangle.Left - margins.Left, rectangle.Top - margins.Top),
                  GsPT(rectangle.Right + margins.Right, rectangle.Bottom + margins.Bottom));
}

inline GsRect operator+(const GsMargins &margins, const GsRect &rectangle) noexcept
{
    return GsRect(GsPT(rectangle.Left - margins.Left, rectangle.Top - margins.Top),
                  GsPT(rectangle.Right + margins.Right, rectangle.Bottom + margins.Bottom));
}

inline GsRect operator-(const GsRect &lhs, const GsMargins &rhs) noexcept
{
    return GsRect(GsPT(lhs.Left + rhs.Left, lhs.Top + rhs.Top),
                  GsPT(lhs.Right - rhs.Right, lhs.Bottom - rhs.Bottom));
}

inline GsRect GsRect::MarginsAdded(const GsMargins &margins) const noexcept
{
    return GsRect(GsPT(Left - margins.Left, Top - margins.Top),
                  GsPT(Right + margins.Right, Bottom + margins.Bottom));
}

inline GsRect GsRect::MarginsRemoved(const GsMargins &margins) const noexcept
{
    return GsRect(GsPT(Left + margins.Left, Top + margins.Top),
                  GsPT(Right - margins.Right, Bottom - margins.Bottom));
}

inline GsRect &GsRect::operator+=(const GsMargins &margins) noexcept
{
    *this = MarginsAdded(margins);
    return *this;
}

inline GsRect &GsRect::operator-=(const GsMargins &margins) noexcept
{
    *this = MarginsRemoved(margins);
    return *this;
}


/*****************************************************************************
  GsRectF inline member functions
 *****************************************************************************/
inline GsRectF::GsRectF() noexcept
    : Left(0.0), Top(0.0), Right(-1.0), Bottom(-1.0) {}

inline GsRectF::GsRectF(float aleft, float atop, float awidth, float aheight) noexcept
    : Left(aleft), Top(atop), Right(aleft + awidth - 1), Bottom(atop + aheight - 1) {}


inline GsRectF::GsRectF(const GsPTF &atopLeft, const GsPTF &abottomRight) noexcept
    : Left(atopLeft.X), Top(atopLeft.Y), Right(abottomRight.X), Bottom(abottomRight.Y) {}

inline GsRectF::GsRectF(const GsPTF &atopLeft, const GsSizeF &asize) noexcept
    : Left(atopLeft.X), Top(atopLeft.Y), Right(atopLeft.X + asize.Width - 1), Bottom(atopLeft.Y + asize.Height - 1) {}

inline GsRectF::GsRectF(const GsRect &rect) noexcept
    : Left(rect.Left), Top(rect.Top), Right(rect.Right), Bottom(rect.Bottom) {}

inline bool GsRectF::IsNull() const noexcept
{
    return Right == Left - 1 && Bottom == Top - 1;
}

inline bool GsRectF::IsEmpty() const noexcept
{
    return Left > Right || Top > Bottom;
}

inline bool GsRectF::IsValid() const noexcept
{
    return Left <= Right && Top <= Bottom;
}

inline void GsRectF::TopLeft(const GsPTF &p) noexcept
{
    Left = p.X;
    Top = p.Y;
}

inline void GsRectF::BottomRight(const GsPTF &p) noexcept
{
    Right = p.X;
    Bottom = p.Y;
}

inline void GsRectF::TopRight(const GsPTF &p) noexcept
{
    Right = p.X;
    Top = p.Y;
}

inline void GsRectF::BottomLeft(const GsPTF &p) noexcept
{
    Left = p.X;
    Bottom = p.Y;
}


inline GsPTF GsRectF::TopLeft() const noexcept
{
    return GsPTF(Left, Top);
}

inline GsPTF GsRectF::BottomRight() const noexcept
{
    return GsPTF(Right, Bottom);
}

inline GsPTF GsRectF::TopRight() const noexcept
{
    return GsPTF(Right, Top);
}

inline GsPTF GsRectF::BottomLeft() const noexcept
{
    return GsPTF(Left, Bottom);
}

inline GsPTF GsRectF::Center() const noexcept
{
    return GsPTF((Left + Right) / 2.0, (Top + Bottom) / 2);
}

inline float GsRectF::Width() const noexcept
{
    return Right - Left + 1;
}

inline float GsRectF::Height() const noexcept
{
    return Bottom - Top + 1;
}

inline GsSizeF GsRectF::Size() const noexcept
{
    return GsSizeF(Width(), Height());
}

inline void GsRectF::Translate(float dx, float dy) noexcept
{
    Left += dx;
    Top += dy;
    Right += dx;
    Bottom += dy;
}

inline void GsRectF::Translate(const GsPTF &p) noexcept
{
    Left += p.X;
    Top += p.Y;
    Right += p.X;
    Bottom += p.Y;
}

inline GsRectF GsRectF::Translated(float dx, float dy) const noexcept
{
    return GsRectF(GsPTF(Left + dx, Top + dy), GsPTF(Right + dx, Bottom + dy));
}

inline GsRectF GsRectF::Translated(const GsPTF &p) const noexcept
{
    return GsRectF(GsPTF(Left + p.X, Top + p.Y), GsPTF(Right + p.X, Bottom + p.Y));
}

inline GsRectF GsRectF::Transposed() const noexcept
{
    return GsRectF(TopLeft(), Size().Transposed());
}

inline void GsRectF::MoveTo(float ax, float ay) noexcept
{
    Right += ax - Left;
    Bottom += ay - Top;
    Left = ax;
    Top = ay;
}

inline void GsRectF::MoveTo(const GsPTF &p) noexcept
{
    Right += p.X - Left;
    Bottom += p.Y - Top;
    Left = p.X;
    Top = p.Y;
}

inline void GsRectF::MoveLeft(float pos) noexcept
{
    Right += (pos - Left);
    Left = pos;
}

inline void GsRectF::MoveTop(float pos) noexcept
{
    Bottom += (pos - Top);
    Top = pos;
}

inline void GsRectF::MoveRight(float pos) noexcept
{
    Left += (pos - Right);
    Right = pos;
}

inline void GsRectF::MoveBottom(float pos) noexcept
{
    Top += (pos - Bottom);
    Bottom = pos;
}

inline void GsRectF::MoveTopLeft(const GsPTF &p) noexcept
{
    MoveLeft(p.X);
    MoveTop(p.Y);
}

inline void GsRectF::MoveBottomRight(const GsPTF &p) noexcept
{
    MoveRight(p.X);
    MoveBottom(p.Y);
}

inline void GsRectF::MoveTopRight(const GsPTF &p) noexcept
{
    MoveRight(p.X);
    MoveTop(p.Y);
}

inline void GsRectF::MoveBottomLeft(const GsPTF &p) noexcept
{
    MoveLeft(p.X);
    MoveBottom(p.Y);
}

inline void GsRectF::MoveCenter(const GsPTF &p) noexcept
{
    float w = Right - Left;
    float h = Bottom - Top;
    Left = p.X - w / 2;
    Top = p.Y - h / 2;
    Right = Left + w;
    Bottom = Top + h;
}

inline void GsRectF::Rect(float *ax, float *ay, float *aw, float *ah) const
{
    *ax = Left;
    *ay = Top;
    *aw = Right - Left + 1;
    *ah = Bottom - Top + 1;
}

inline void GsRectF::Rect(float ax, float ay, float aw, float ah) noexcept
{
    Left = ax;
    Top = ay;
    Right = (ax + aw - 1);
    Bottom = (ay + ah - 1);
}

inline void GsRectF::Coords(float *xp1, float *yp1, float *xp2, float *yp2) const
{
    *xp1 = Left;
    *yp1 = Top;
    *xp2 = Right;
    *yp2 = Bottom;
}

inline void GsRectF::Coords(float xp1, float yp1, float xp2, float yp2) noexcept
{
    Left = xp1;
    Top = yp1;
    Right = xp2;
    Bottom = yp2;
}

inline GsRectF GsRectF::Adjusted(float xp1, float yp1, float xp2, float yp2) const noexcept
{
    return GsRectF(GsPTF(Left + xp1, Top + yp1), GsPTF(Right + xp2, Bottom + yp2));
}

inline void GsRectF::Adjust(float dLeft, float dTop, float dRight, float dBottom) noexcept
{
    Left += dLeft;
    Top += dTop;
    Right += dRight;
    Bottom += dBottom;
}

inline void GsRectF::Width(float w) noexcept
{
    Right = (Left + w - 1);
}

inline void GsRectF::Height(float h) noexcept
{
    Bottom = (Top + h - 1);
}

inline void GsRectF::Size(const GsSizeF &s) noexcept
{
    Right = (s.Width + Left - 1);
    Bottom = (s.Height + Top - 1);
}

inline bool GsRectF::Contains(float ax, float ay) const noexcept
{
    return Contains(GsPTF(ax, ay));
}

inline GsRectF &GsRectF::operator|=(const GsRectF &r) noexcept
{
    *this = *this | r;
    return *this;
}

inline GsRectF &GsRectF::operator&=(const GsRectF &r) noexcept
{
    *this = *this & r;
    return *this;
}

inline GsRectF GsRectF::Intersected(const GsRectF &other) const noexcept
{
    return *this & other;
}

inline GsRectF GsRectF::United(const GsRectF &r) const noexcept
{
    return *this | r;
}

inline bool operator==(const GsRectF &r1, const GsRectF &r2) noexcept
{
    return r1.Left == r2.Left && r1.Right == r2.Right && r1.Top == r2.Top && r1.Bottom == r2.Bottom;
}

inline bool operator!=(const GsRectF &r1, const GsRectF &r2) noexcept
{
    return r1.Left != r2.Left || r1.Right != r2.Right || r1.Top != r2.Top || r1.Bottom != r2.Bottom;
}

inline GsRectF operator+(const GsRectF &rectangle, const GsMarginsF &margins) noexcept
{
    return GsRectF(GsPTF(rectangle.Left - margins.Left, rectangle.Top - margins.Top),
                   GsPTF(rectangle.Right + margins.Right, rectangle.Bottom + margins.Bottom));
}

inline GsRectF operator+(const GsMarginsF &margins, const GsRectF &rectangle) noexcept
{
    return GsRectF(GsPTF(rectangle.Left - margins.Left, rectangle.Top - margins.Top),
                   GsPTF(rectangle.Right + margins.Right, rectangle.Bottom + margins.Bottom));
}

inline GsRectF operator-(const GsRectF &lhs, const GsMarginsF &rhs) noexcept
{
    return GsRectF(GsPTF(lhs.Left + rhs.Left, lhs.Top + rhs.Top),
                   GsPTF(lhs.Right - rhs.Right, lhs.Bottom - rhs.Bottom));
}

inline GsRectF GsRectF::MarginsAdded(const GsMarginsF &margins) const noexcept
{
    return GsRectF(GsPTF(Left - margins.Left, Top - margins.Top),
                   GsPTF(Right + margins.Right, Bottom + margins.Bottom));
}

inline GsRectF GsRectF::MarginsRemoved(const GsMarginsF &margins) const noexcept
{
    return GsRectF(GsPTF(Left + margins.Left, Top + margins.Top),
                   GsPTF(Right - margins.Right, Bottom - margins.Bottom));
}

inline GsRectF &GsRectF::operator+=(const GsMarginsF &margins) noexcept
{
    *this = MarginsAdded(margins);
    return *this;
}

inline GsRectF &GsRectF::operator-=(const GsMarginsF &margins) noexcept
{
    *this = MarginsRemoved(margins);
    return *this;
}

inline GsRect GsRectF::ToRect() const noexcept
{
    return GsRect(GsPT(Math::Round(Left), Math::Round(Top)), GsPT(Math::Round(Right), Math::Round(Bottom)));
}


}// namespace m2
