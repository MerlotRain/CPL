#include <variant.h>


namespace Lite {
namespace Utility {

GsVariant::~GsVariant()
{
}

GsVariant::GsVariant()
{
}

GsVariant::GsVariant(char v)
{
}

GsVariant::GsVariant(unsigned char v)
{
}

GsVariant::GsVariant(short v)
{
}

GsVariant::GsVariant(unsigned short v)
{
}

GsVariant::GsVariant(int v)
{
}

GsVariant::GsVariant(unsigned int v)
{
}

GsVariant::GsVariant(long long v, bool bDateTime)
{
}

GsVariant::GsVariant(unsigned long long v)
{
}

GsVariant::GsVariant(float v)
{
}

GsVariant::GsVariant(double v)
{
}

GsVariant::GsVariant(bool v)
{
}

GsVariant::GsVariant(GsRefObject *v)
{
}

GsVariant::GsVariant(const char *v)
{
}

GsVariant::GsVariant(const GsString &str)
{
}

GsVariant::GsVariant(const unsigned char *v, int nLen)
{
}

GsVariant::GsVariant(const GsVariant &rhs)
{
}

GsVariant::GsVariant(GsVariant &&rhs)
{
}

GsVariant::GsVariant(GsVarType type)
{
}

GsVariant &GsVariant::operator=(const GsVariant &rhs)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(char v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(unsigned char v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(short v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(unsigned short v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(int v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(unsigned int v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(long long v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(unsigned long long v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(float v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(double v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(bool v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(const char *v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(const GsString &str)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(GsRefObject *v)
{
    // TODO: insert return statement here
}

GsVariant &GsVariant::operator=(GsVariant &&v)
{
    // TODO: insert return statement here
}

bool GsVariant::operator==(const GsVariant &o) const
{
    return false;
}

bool GsVariant::operator!=(const GsVariant &o) const
{
    return false;
}

void GsVariant::Clear()
{
}

char GsVariant::AsChar() const
{
    return 0;
}

unsigned char GsVariant::AsUChar() const
{
    return 0;
}

short GsVariant::AsShort() const
{
    return 0;
}

unsigned short GsVariant::AsUShort() const
{
    return 0;
}

int GsVariant::AsInt() const
{
    return 0;
}

unsigned int GsVariant::AsUInt() const
{
    return 0;
}

long long GsVariant::AsLongLong() const
{
    return 0;
}

unsigned long long GsVariant::AsULongLong() const
{
    return 0;
}

float GsVariant::AsFloat() const
{
    return 0.0f;
}

double GsVariant::AsDouble() const
{
    return 0.0;
}

bool GsVariant::AsBool() const
{
    return false;
}

GsRefObject *GsVariant::AsObject() const
{
    return nullptr;
}

char *GsVariant::AsString() const
{
    return nullptr;
}

int GsVariant::AsBlob(unsigned char *bBlob) const
{
    return 0;
}

GsVariant::operator char() const
{
}

GsVariant::operator unsigned char() const
{
}

GsVariant::operator short() const
{
}

GsVariant::operator unsigned short() const
{
}

GsVariant::operator int() const
{
}

GsVariant::operator unsigned int() const
{
}

GsVariant::operator long long() const
{
}

GsVariant::operator unsigned long long() const
{
}

GsVariant::operator bool() const
{
}

GsVariant::operator float() const
{
}

GsVariant::operator double() const
{
}

GsVariant::operator const char *() const
{
}

GsVariant::operator GsRefObject *()
{
}

void GsVariant::Set(const unsigned char *bBlob, int nLen)
{
}

void GsVariant::Set(const char *str, int nLen)
{
}

unsigned char *GsVariant::AllocBlob(int nLen)
{
    return nullptr;
}

int GsVariant::ValueSize() const
{
    return 0;
}

const void *GsVariant::ValuePtr() const
{
    return nullptr;
}

unsigned long long GsVariant::HashCode() const
{
    return 0;
}

GsString GsVariant::ToString() const
{
    return GsString();
}

void GsVariant::Swap(GsVariant &rhs)
{
}

const GsVariant &GsVariant::Empty()
{
    // TODO: insert return statement here
}


}// namespace Utility
}// namespace Lite
