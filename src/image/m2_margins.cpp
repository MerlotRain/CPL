#include <m2_margins.h>

namespace m2 {

/*****************************************************************************
  Margins  functions
 *****************************************************************************/

Margins::Margins() noexcept : m_left(0), m_top(0), m_right(0), m_bottom(0) {}

Margins::Margins(int aleft, int atop, int aright, int abottom) noexcept
    : m_left(aleft), m_top(atop), m_right(aright), m_bottom(abottom)
{
}

bool Margins::isNull() const noexcept
{
    return m_left == 0 && m_top == 0 && m_right == 0 && m_bottom == 0;
}

int Margins::left() const noexcept { return m_left; }

int Margins::top() const noexcept { return m_top; }

int Margins::right() const noexcept { return m_right; }

int Margins::bottom() const noexcept { return m_bottom; }


void Margins::setLeft(int aleft) noexcept { m_left = aleft; }

void Margins::setTop(int atop) noexcept { m_top = atop; }

void Margins::setRight(int aright) noexcept { m_right = aright; }

void Margins::setBottom(int abottom) noexcept { m_bottom = abottom; }

Margins operator+(const Margins &m1, const Margins &m2) noexcept
{
    return Margins(m1.left() + m2.left(), m1.top() + m2.top(),
                   m1.right() + m2.right(), m1.bottom() + m2.bottom());
}

Margins operator-(const Margins &m1, const Margins &m2) noexcept
{
    return Margins(m1.left() - m2.left(), m1.top() - m2.top(),
                   m1.right() - m2.right(), m1.bottom() - m2.bottom());
}

Margins operator+(const Margins &lhs, int rhs) noexcept
{
    return Margins(lhs.left() + rhs, lhs.top() + rhs, lhs.right() + rhs,
                   lhs.bottom() + rhs);
}

Margins operator+(int lhs, const Margins &rhs) noexcept
{
    return Margins(rhs.left() + lhs, rhs.top() + lhs, rhs.right() + lhs,
                   rhs.bottom() + lhs);
}

Margins operator-(const Margins &lhs, int rhs) noexcept
{
    return Margins(lhs.left() - rhs, lhs.top() - rhs, lhs.right() - rhs,
                   lhs.bottom() - rhs);
}

Margins operator*(const Margins &margins, int factor) noexcept
{
    return Margins(margins.left() * factor, margins.top() * factor,
                   margins.right() * factor, margins.bottom() * factor);
}

Margins operator*(int factor, const Margins &margins) noexcept
{
    return Margins(margins.left() * factor, margins.top() * factor,
                   margins.right() * factor, margins.bottom() * factor);
}

Margins operator*(const Margins &margins, double factor) noexcept
{
    return Margins(qRound(margins.left() * factor),
                   qRound(margins.top() * factor),
                   qRound(margins.right() * factor),
                   qRound(margins.bottom() * factor));
}

Margins operator*(double factor, const Margins &margins) noexcept
{
    return Margins(qRound(margins.left() * factor),
                   qRound(margins.top() * factor),
                   qRound(margins.right() * factor),
                   qRound(margins.bottom() * factor));
}

Margins operator/(const Margins &margins, int divisor)
{
    return Margins(margins.left() / divisor, margins.top() / divisor,
                   margins.right() / divisor, margins.bottom() / divisor);
}

Margins operator/(const Margins &margins, double divisor)
{
    return Margins(qRound(margins.left() / divisor),
                   qRound(margins.top() / divisor),
                   qRound(margins.right() / divisor),
                   qRound(margins.bottom() / divisor));
}

Margins operator|(const Margins &m1, const Margins &m2) noexcept
{
    return Margins(qMax(m1.left(), m2.left()), qMax(m1.top(), m2.top()),
                   qMax(m1.right(), m2.right()),
                   qMax(m1.bottom(), m2.bottom()));
}

Margins &Margins::operator+=(const Margins &margins) noexcept
{
    return *this = *this + margins;
}

Margins &Margins::operator-=(const Margins &margins) noexcept
{
    return *this = *this - margins;
}

Margins &Margins::operator+=(int margin) noexcept
{
    m_left += margin;
    m_top += margin;
    m_right += margin;
    m_bottom += margin;
    return *this;
}

Margins &Margins::operator-=(int margin) noexcept
{
    m_left -= margin;
    m_top -= margin;
    m_right -= margin;
    m_bottom -= margin;
    return *this;
}

Margins &Margins::operator*=(int factor) noexcept
{
    return *this = *this * factor;
}

Margins &Margins::operator/=(int divisor) { return *this = *this / divisor; }

Margins &Margins::operator*=(double factor) noexcept
{
    return *this = *this * factor;
}

Margins &Margins::operator/=(double divisor) { return *this = *this / divisor; }

Margins operator+(const Margins &margins) noexcept { return margins; }

Margins operator-(const Margins &margins) noexcept
{
    return Margins(-margins.left(), -margins.top(), -margins.right(),
                   -margins.bottom());
}


/*****************************************************************************
  MarginsF  functions
 *****************************************************************************/

MarginsF::MarginsF() noexcept : m_left(0), m_top(0), m_right(0), m_bottom(0) {}

MarginsF::MarginsF(double aleft, double atop, double aright,
                   double abottom) noexcept
    : m_left(aleft), m_top(atop), m_right(aright), m_bottom(abottom)
{
}

MarginsF::MarginsF(const Margins &margins) noexcept
    : m_left(margins.left()), m_top(margins.top()), m_right(margins.right()),
      m_bottom(margins.bottom())
{
}

bool MarginsF::isNull() const noexcept
{
    return qFuzzyIsNull(m_left) && qFuzzyIsNull(m_top) &&
           qFuzzyIsNull(m_right) && qFuzzyIsNull(m_bottom);
}

double MarginsF::left() const noexcept { return m_left; }

double MarginsF::top() const noexcept { return m_top; }

double MarginsF::right() const noexcept { return m_right; }

double MarginsF::bottom() const noexcept { return m_bottom; }


void MarginsF::setLeft(double aleft) noexcept { m_left = aleft; }

void MarginsF::setTop(double atop) noexcept { m_top = atop; }

void MarginsF::setRight(double aright) noexcept { m_right = aright; }

void MarginsF::setBottom(double abottom) noexcept { m_bottom = abottom; }

MarginsF operator+(const MarginsF &lhs, const MarginsF &rhs) noexcept
{
    return MarginsF(lhs.left() + rhs.left(), lhs.top() + rhs.top(),
                    lhs.right() + rhs.right(), lhs.bottom() + rhs.bottom());
}

MarginsF operator-(const MarginsF &lhs, const MarginsF &rhs) noexcept
{
    return MarginsF(lhs.left() - rhs.left(), lhs.top() - rhs.top(),
                    lhs.right() - rhs.right(), lhs.bottom() - rhs.bottom());
}

MarginsF operator+(const MarginsF &lhs, double rhs) noexcept
{
    return MarginsF(lhs.left() + rhs, lhs.top() + rhs, lhs.right() + rhs,
                    lhs.bottom() + rhs);
}

MarginsF operator+(double lhs, const MarginsF &rhs) noexcept
{
    return MarginsF(rhs.left() + lhs, rhs.top() + lhs, rhs.right() + lhs,
                    rhs.bottom() + lhs);
}

MarginsF operator-(const MarginsF &lhs, double rhs) noexcept
{
    return MarginsF(lhs.left() - rhs, lhs.top() - rhs, lhs.right() - rhs,
                    lhs.bottom() - rhs);
}

MarginsF operator*(const MarginsF &lhs, double rhs) noexcept
{
    return MarginsF(lhs.left() * rhs, lhs.top() * rhs, lhs.right() * rhs,
                    lhs.bottom() * rhs);
}

MarginsF operator*(double lhs, const MarginsF &rhs) noexcept
{
    return MarginsF(rhs.left() * lhs, rhs.top() * lhs, rhs.right() * lhs,
                    rhs.bottom() * lhs);
}

MarginsF operator/(const MarginsF &lhs, double divisor)
{
    assert(divisor < 0 || divisor > 0);
    return MarginsF(lhs.left() / divisor, lhs.top() / divisor,
                    lhs.right() / divisor, lhs.bottom() / divisor);
}

MarginsF operator|(const MarginsF &m1, const MarginsF &m2) noexcept
{
    return MarginsF(qMax(m1.left(), m2.left()), qMax(m1.top(), m2.top()),
                    qMax(m1.right(), m2.right()),
                    qMax(m1.bottom(), m2.bottom()));
}

MarginsF &MarginsF::operator+=(const MarginsF &margins) noexcept
{
    return *this = *this + margins;
}

MarginsF &MarginsF::operator-=(const MarginsF &margins) noexcept
{
    return *this = *this - margins;
}

MarginsF &MarginsF::operator+=(double addend) noexcept
{
    m_left += addend;
    m_top += addend;
    m_right += addend;
    m_bottom += addend;
    return *this;
}

MarginsF &MarginsF::operator-=(double subtrahend) noexcept
{
    m_left -= subtrahend;
    m_top -= subtrahend;
    m_right -= subtrahend;
    m_bottom -= subtrahend;
    return *this;
}

MarginsF &MarginsF::operator*=(double factor) noexcept
{
    return *this = *this * factor;
}

MarginsF &MarginsF::operator/=(double divisor)
{
    return *this = *this / divisor;
}

MarginsF operator+(const MarginsF &margins) noexcept { return margins; }

MarginsF operator-(const MarginsF &margins) noexcept
{
    return MarginsF(-margins.left(), -margins.top(), -margins.right(),
                    -margins.bottom());
}

MarginsF Margins::toMarginsF() const noexcept { return *this; }

Margins MarginsF::toMargins() const noexcept
{
    return Margins(qRound(m_left), qRound(m_top), qRound(m_right),
                   qRound(m_bottom));
}


}// namespace m2