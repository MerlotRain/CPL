#include "bitset.h"

namespace m2 {

Bitset::Reference::Reference(const Reference &) {}

Bitset::Reference::~Reference() {}

Bitset::Reference &Bitset::Reference::operator=(bool x) noexcept
{
    // TODO: insert return statement here
}

Bitset::Reference &
Bitset::Reference::operator=(const Reference &) noexcept
{
    // TODO: insert return statement here
}

bool Bitset::Reference::operator~() const noexcept { return false; }

Bitset::Reference::operator bool() const noexcept {}

Bitset::Reference &Bitset::Reference::Flip() noexcept
{
    // TODO: insert return statement here
}

/****************************** Bitset ******************************/

Bitset::Bitset(unsigned int nSize) {}

Bitset::Bitset(const char *str) {}

Bitset::Bitset(const Bitset &r) {}

Bitset::Bitset(Bitset &&rr) noexcept {}

Bitset &Bitset::operator=(const Bitset &r)
{
    // TODO: insert return statement here
}

Bitset &Bitset::operator=(Bitset &&r) noexcept
{
    // TODO: insert return statement here
}

void Bitset::Swap(Bitset &bit) {}

bool Bitset::operator==(const Bitset &r) { return false; }

bool Bitset::operator!=(const Bitset &r) { return false; }

bool Bitset::Empty() const { return false; }

Bitset &Bitset::operator&=(const Bitset &r)
{
    // TODO: insert return statement here
}

Bitset &Bitset::operator|=(const Bitset &r)
{
    // TODO: insert return statement here
}

Bitset &Bitset::operator^=(const Bitset &r)
{
    // TODO: insert return statement here
}

Bitset &Bitset::operator<<=(size_t pos) noexcept
{
    // TODO: insert return statement here
}

Bitset &Bitset::operator>>=(size_t pos) noexcept
{
    // TODO: insert return statement here
}

Bitset Bitset::operator<<(size_t pos) const noexcept { return Bitset(); }

Bitset Bitset::operator>>(size_t pos) const noexcept { return Bitset(); }

Bitset &Bitset::Set() noexcept
{
    // TODO: insert return statement here
}

Bitset &Bitset::Set(size_t pos, bool val)
{
    // TODO: insert return statement here
}

Bitset &Bitset::Reset() noexcept
{
    // TODO: insert return statement here
}

Bitset &Bitset::Reset(size_t pos)
{
    // TODO: insert return statement here
}

Bitset Bitset::operator~() const noexcept { return Bitset(); }

Bitset &Bitset::Flip() noexcept
{
    // TODO: insert return statement here
}

Bitset &Bitset::Flip(size_t pos)
{
    // TODO: insert return statement here
}

bool Bitset::operator[](size_t pos) const { return false; }

Bitset::Reference Bitset::operator[](size_t pos) {}

unsigned int Bitset::Size() { return 0; }

Bitset &Bitset::PushBack(bool bit)
{
    // TODO: insert return statement here
}

Bitset &Bitset::Resize(int size)
{
    // TODO: insert return statement here
}

Bitset &Bitset::Reverse(int size)
{
    // TODO: insert return statement here
}

bool Bitset::Test(unsigned int n) { return false; }

bool Bitset::None() { return false; }

bool Bitset::Any() { return false; }

bool Bitset::All() { return false; }

bool Bitset::Count() const { return false; }

String Bitset::ToString() const { return String(); }

}// namespace m2
