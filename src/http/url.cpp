#include <urlparser.h>

namespace Lite {
namespace Utility {

GsUrl::GsUrl()
{
}

GsUrl::GsUrl(const GsString &url)
{
}

GsUrl::GsUrl(const char *url)
{
}

GsUrl::GsUrl(const GsString &scheme, const GsString &pathEtc)
{
}

GsUrl::GsUrl(const GsString &scheme, const GsString &authority, const GsString &pathEtc)
{
}

GsUrl::GsUrl(const GsString &scheme, const GsString &authority, const GsString &path, const GsString &query)
{
}

GsUrl::GsUrl(const GsString &scheme, const GsString &authority, const GsString &path, const GsString &query, const GsString &fragment)
{
}

GsUrl::GsUrl(const GsUrl &url)
{
}

GsUrl::GsUrl(GsUrl &&url) noexcept
{
}

GsUrl::GsUrl(const GsUrl &baseURL, const GsString &relativeURL)
{
}

GsUrl::~GsUrl()
{
}

GsUrl &GsUrl::operator=(const GsUrl &url)
{
    // TODO: insert return statement here
}

GsUrl &GsUrl::operator=(GsUrl &&url) noexcept
{
    // TODO: insert return statement here
}

GsUrl &GsUrl::operator=(const GsString &url)
{
    // TODO: insert return statement here
}

GsUrl &GsUrl::operator=(const char *url)
{
    // TODO: insert return statement here
}

void GsUrl::Swap(GsUrl &url) noexcept
{
}

void GsUrl::Clear()
{
}

GsString GsUrl::ToString() const
{
    return GsString();
}

const GsString &GsUrl::Scheme() const
{
    // TODO: insert return statement here
}

void GsUrl::Scheme(const char *scheme)
{
}

const GsString &GsUrl::UserInfo() const
{
    // TODO: insert return statement here
}

void GsUrl::UserInfo(const char *userInfo)
{
}

const GsString &GsUrl::Host() const
{
    // TODO: insert return statement here
}

void GsUrl::Host(const char *host)
{
}

unsigned short GsUrl::Port() const
{
    return 0;
}

void GsUrl::Port(unsigned short port)
{
}

unsigned short GsUrl::SpecifiedPort() const
{
    return 0;
}

GsString GsUrl::Authority() const
{
    return GsString();
}

void GsUrl::Authority(const char *authority)
{
}

const GsString &GsUrl::Path() const
{
    // TODO: insert return statement here
}

void GsUrl::Path(const char *path)
{
}

GsString GsUrl::Query() const
{
    return GsString();
}

void GsUrl::Query(const char *query)
{
}

void GsUrl::AddQueryParameter(const GsString &param, const GsString &val)
{
}

const GsString &GsUrl::RawQuery() const
{
    // TODO: insert return statement here
}

void GsUrl::RawQuery(const char *query)
{
}

GsUrl::GsQueryParameters GsUrl::QueryParameters(bool plusIsSpace) const
{
    return GsQueryParameters();
}

void GsUrl::QueryParameters(const GsQueryParameters &params)
{
}

GsString GsUrl::Fragment() const
{
    return GsString();
}

void GsUrl::Fragment(const char *fragment)
{
}

GsString GsUrl::RawFragment() const
{
    return GsString();
}

void GsUrl::RawFragment(const char *fragment)
{
}

GsString GsUrl::PathEtc() const
{
    return GsString();
}

void GsUrl::PathEtc(const char *pathEtc)
{
}

GsString GsUrl::PathAndQuery() const
{
    return GsString();
}

void GsUrl::Resolve(const char *relativeURL)
{
}

void GsUrl::Resolve(const GsUrl &relativeURL)
{
}

bool GsUrl::IsRelative() const
{
    return false;
}

bool GsUrl::Empty() const
{
    return false;
}

bool GsUrl::operator==(const GsUrl &url) const
{
    return false;
}

bool GsUrl::operator==(const GsString &url) const
{
    return false;
}

bool GsUrl::operator!=(const GsUrl &url) const
{
    return false;
}

bool GsUrl::operator!=(const GsString &url) const
{
    return false;
}

void GsUrl::Normalize()
{
}

void GsUrl::PathSegments(std::vector<GsString> &segments) const
{
}

void GsUrl::Encode(const GsString &str, const GsString &reserved, GsString &encodedStr)
{
}

void GsUrl::Decode(const GsString &str, GsString &decodedStr, bool plusAsSpace)
{
}

bool GsUrl::Equals(const GsUrl &url) const
{
    return false;
}

bool GsUrl::IsWellKnownPort() const
{
    return false;
}

unsigned short GsUrl::WellKnownPort() const
{
    return 0;
}

void GsUrl::Parse(const GsString &url)
{
}

void GsUrl::ParseAuthority(GsString::const_iterator &begin, const GsString::const_iterator &end)
{
}

void GsUrl::ParseHostAndPort(GsString::const_iterator &begin, const GsString::const_iterator &end)
{
}

void GsUrl::ParsePath(GsString::const_iterator &begin, const GsString::const_iterator &end)
{
}

void GsUrl::ParsePathEtc(GsString::const_iterator &begin, const GsString::const_iterator &end)
{
}

void GsUrl::ParseQuery(GsString::const_iterator &begin, const GsString::const_iterator &end)
{
}

void GsUrl::ParseFragment(GsString::const_iterator &begin, const GsString::const_iterator &end)
{
}

void GsUrl::MergePath(const GsString &path)
{
}

void GsUrl::RemoveDotSegments(bool removeLeading)
{
}

void GsUrl::PathSegments(const GsString &path, std::vector<GsString> &segments)
{
}

void GsUrl::BuildPath(const std::vector<GsString> &segments, bool leadingSlash, bool trailingSlash)
{
}


}// namespace Utility
}// namespace Lite
