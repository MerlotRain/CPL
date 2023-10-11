#include <variant.h>


namespace m2 {

Variant::~Variant()
{
}

Variant::Variant()
{
}

Variant::Variant(char v)
{
}

Variant::Variant(unsigned char v)
{
}

Variant::Variant(short v)
{
}

Variant::Variant(unsigned short v)
{
}

Variant::Variant(int v)
{
}

Variant::Variant(unsigned int v)
{
}

Variant::Variant(long long v, bool bDateTime)
{
}

Variant::Variant(unsigned long long v)
{
}

Variant::Variant(float v)
{
}

Variant::Variant(double v)
{
}

Variant::Variant(bool v)
{
}

Variant::Variant(RefObject *v)
{
}

Variant::Variant(const char *v)
{
}

Variant::Variant(const String &str)
{
}

Variant::Variant(const unsigned char *v, int nLen)
{
}

Variant::Variant(const Variant &rhs)
{
}

Variant::Variant(Variant &&rhs)
{
}

Variant::Variant(VarType type)
{
}

Variant &Variant::operator=(const Variant &rhs)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(char v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(unsigned char v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(short v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(unsigned short v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(int v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(unsigned int v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(long long v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(unsigned long long v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(float v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(double v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(bool v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(const char *v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(const String &str)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(RefObject *v)
{
    // TODO: insert return statement here
}

Variant &Variant::operator=(Variant &&v)
{
    // TODO: insert return statement here
}

bool Variant::operator==(const Variant &o) const
{
    return false;
}

bool Variant::operator!=(const Variant &o) const
{
    return false;
}

void Variant::Clear()
{
}

char Variant::AsChar() const
{
    return 0;
}

unsigned char Variant::AsUChar() const
{
    return 0;
}

short Variant::AsShort() const
{
    return 0;
}

unsigned short Variant::AsUShort() const
{
    return 0;
}

int Variant::AsInt() const
{
    return 0;
}

unsigned int Variant::AsUInt() const
{
    return 0;
}

long long Variant::AsLongLong() const
{
    return 0;
}

unsigned long long Variant::AsULongLong() const
{
    return 0;
}

float Variant::AsFloat() const
{
    return 0.0f;
}

double Variant::AsDouble() const
{
    return 0.0;
}

bool Variant::AsBool() const
{
    return false;
}

RefObject *Variant::AsObject() const
{
    return nullptr;
}

char *Variant::AsString() const
{
    return nullptr;
}

int Variant::AsBlob(unsigned char *bBlob) const
{
    return 0;
}

Variant::operator char() const
{
}

Variant::operator unsigned char() const
{
}

Variant::operator short() const
{
}

Variant::operator unsigned short() const
{
}

Variant::operator int() const
{
}

Variant::operator unsigned int() const
{
}

Variant::operator long long() const
{
}

Variant::operator unsigned long long() const
{
}

Variant::operator bool() const
{
}

Variant::operator float() const
{
}

Variant::operator double() const
{
}

Variant::operator const char *() const
{
}

Variant::operator RefObject *()
{
}

void Variant::Set(const unsigned char *bBlob, int nLen)
{
}

void Variant::Set(const char *str, int nLen)
{
}

unsigned char *Variant::AllocBlob(int nLen)
{
    return nullptr;
}

int Variant::ValueSize() const
{
    return 0;
}

const void *Variant::ValuePtr() const
{
    return nullptr;
}

unsigned long long Variant::HashCode() const
{
    return 0;
}

String Variant::ToString() const
{
    return String();
}

void Variant::Swap(Variant &rhs)
{
}

const Variant &Variant::Empty()
{
    // TODO: insert return statement here
}


}// namespace m2
