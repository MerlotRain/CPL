#include <stringhelp.h>

namespace m2 {


StringStream::StringStream()
{
}

StringStream::StringStream(const String &str)
    : StlSStream(str.c_str(), std::ios_base::in | std::ios_base::out)
{
}

StringStream::~StringStream()
{
}

String StringStream::Str()
{
    m_str = str();
    return m_str;
}

const char *StringStream::CStr()
{
    m_str = str();
    return m_str.c_str();
}

StringStream::operator String()
{
    m_str = str();
    return m_str;
}


StringStream::operator const char *()
{
    m_str = str();
    return m_str.c_str();
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
OStringStream::OStringStream()
{
}

OStringStream::~OStringStream()
{
}

String OStringStream::Str()
{
    return m_str;
}

const char *OStringStream::CStr()
{
    return m_str.c_str();
}

OStringStream::operator String()
{
    return m_str;
}

OStringStream::operator const char *()
{
    return m_str.c_str();
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
IStringStream::IStringStream()
{
}

IStringStream::IStringStream(const String &str)
{
}

IStringStream::~IStringStream()
{
}

String IStringStream::Str()
{
    return m_str;
}

const char *IStringStream::CStr()
{

    return m_str.c_str();
}

IStringStream::operator String()
{
    return m_str;
}

IStringStream::operator const char *()
{
    return m_str.c_str();
}

}// namespace m2
