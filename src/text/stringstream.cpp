#include <stringhelp.h>

namespace Lite {
namespace Utility {


GsStringStream::GsStringStream()
{
}

GsStringStream::GsStringStream(const GsString &str)
    : GsStlSStream(str.c_str(), std::ios_base::in | std::ios_base::out)
{
}

GsStringStream::~GsStringStream()
{
}

GsString GsStringStream::Str()
{
    m_str = str();
    return m_str;
}

const char *GsStringStream::CStr()
{
    m_str = str();
    return m_str.c_str();
}

GsStringStream::operator GsString()
{
    m_str = str();
    return m_str;
}


GsStringStream::operator const char *()
{
    m_str = str();
    return m_str.c_str();
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
GsOStringStream::GsOStringStream()
{
}

GsOStringStream::~GsOStringStream()
{
}

GsString GsOStringStream::Str()
{
    return m_str;
}

const char *GsOStringStream::CStr()
{
    return m_str.c_str();
}

GsOStringStream::operator GsString()
{
    return m_str;
}

GsOStringStream::operator const char *()
{
    return m_str.c_str();
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
GsIStringStream::GsIStringStream()
{
}

GsIStringStream::GsIStringStream(const GsString &str)
{
}

GsIStringStream::~GsIStringStream()
{
}

GsString GsIStringStream::Str()
{
    return m_str;
}

const char *GsIStringStream::CStr()
{

    return m_str.c_str();
}

GsIStringStream::operator GsString()
{
    return m_str;
}

GsIStringStream::operator const char *()
{
    return m_str.c_str();
}

}// namespace Utility
}// namespace Lite
