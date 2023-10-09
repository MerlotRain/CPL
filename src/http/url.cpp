#include <urlparser.h>

namespace m2 {

Url::Url()
{
}

Url::Url(const String &url)
{
}

Url::Url(const char *url)
{
}

Url::Url(const String &scheme, const String &pathEtc)
{
}

Url::Url(const String &scheme, const String &authority, const String &pathEtc)
{
}

Url::Url(const String &scheme, const String &authority, const String &path, const String &query)
{
}

Url::Url(const String &scheme, const String &authority, const String &path, const String &query, const String &fragment)
{
}

Url::Url(const Url &url)
{
}

Url::Url(Url &&url) noexcept
{
}

Url::Url(const Url &baseURL, const String &relativeURL)
{
}

Url::~Url()
{
}

Url &Url::operator=(const Url &url)
{
    // TODO: insert return statement here
}

Url &Url::operator=(Url &&url) noexcept
{
    // TODO: insert return statement here
}

Url &Url::operator=(const String &url)
{
    // TODO: insert return statement here
}

Url &Url::operator=(const char *url)
{
    // TODO: insert return statement here
}

void Url::Swap(Url &url) noexcept
{
}

void Url::Clear()
{
}

String Url::ToString() const
{
    return String();
}

const String &Url::Scheme() const
{
    // TODO: insert return statement here
}

void Url::Scheme(const char *scheme)
{
}

const String &Url::UserInfo() const
{
    // TODO: insert return statement here
}

void Url::UserInfo(const char *userInfo)
{
}

const String &Url::Host() const
{
    // TODO: insert return statement here
}

void Url::Host(const char *host)
{
}

unsigned short Url::Port() const
{
    return 0;
}

void Url::Port(unsigned short port)
{
}

unsigned short Url::SpecifiedPort() const
{
    return 0;
}

String Url::Authority() const
{
    return String();
}

void Url::Authority(const char *authority)
{
}

const String &Url::Path() const
{
    // TODO: insert return statement here
}

void Url::Path(const char *path)
{
}

String Url::Query() const
{
    return String();
}

void Url::Query(const char *query)
{
}

void Url::AddQueryParameter(const String &param, const String &val)
{
}

const String &Url::RawQuery() const
{
    // TODO: insert return statement here
}

void Url::RawQuery(const char *query)
{
}

Url::QueryParameters Url::QueryParameters(bool plusIsSpace) const
{
    return QueryParameters();
}

void Url::QueryParameters(const QueryParameters &params)
{
}

String Url::Fragment() const
{
    return String();
}

void Url::Fragment(const char *fragment)
{
}

String Url::RawFragment() const
{
    return String();
}

void Url::RawFragment(const char *fragment)
{
}

String Url::PathEtc() const
{
    return String();
}

void Url::PathEtc(const char *pathEtc)
{
}

String Url::PathAndQuery() const
{
    return String();
}

void Url::Resolve(const char *relativeURL)
{
}

void Url::Resolve(const Url &relativeURL)
{
}

bool Url::IsRelative() const
{
    return false;
}

bool Url::Empty() const
{
    return false;
}

bool Url::operator==(const Url &url) const
{
    return false;
}

bool Url::operator==(const String &url) const
{
    return false;
}

bool Url::operator!=(const Url &url) const
{
    return false;
}

bool Url::operator!=(const String &url) const
{
    return false;
}

void Url::Normalize()
{
}

void Url::PathSegments(std::vector<String> &segments) const
{
}

void Url::Encode(const String &str, const String &reserved, String &encodedStr)
{
}

void Url::Decode(const String &str, String &decodedStr, bool plusAsSpace)
{
}

bool Url::Equals(const Url &url) const
{
    return false;
}

bool Url::IsWellKnownPort() const
{
    return false;
}

unsigned short Url::WellKnownPort() const
{
    return 0;
}

void Url::Parse(const String &url)
{
}

void Url::ParseAuthority(String::const_iterator &begin, const String::const_iterator &end)
{
}

void Url::ParseHostAndPort(String::const_iterator &begin, const String::const_iterator &end)
{
}

void Url::ParsePath(String::const_iterator &begin, const String::const_iterator &end)
{
}

void Url::ParsePathEtc(String::const_iterator &begin, const String::const_iterator &end)
{
}

void Url::ParseQuery(String::const_iterator &begin, const String::const_iterator &end)
{
}

void Url::ParseFragment(String::const_iterator &begin, const String::const_iterator &end)
{
}

void Url::MergePath(const String &path)
{
}

void Url::RemoveDotSegments(bool removeLeading)
{
}

void Url::PathSegments(const String &path, std::vector<String> &segments)
{
}

void Url::BuildPath(const std::vector<String> &segments, bool leadingSlash, bool trailingSlash)
{
}


}// namespace m2
