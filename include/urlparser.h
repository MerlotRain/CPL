
/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file urlparser.h
 * @brief
 * @details
 * @date 2023-08-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "bytebuffer.h"
#include "flags.h"
#include "stringhelp.h"

namespace Lite {
namespace Utility {


/// @brief Url解析类
class UTILITY_EXPORT GsUrl
{
public:
    using GsQueryParameters = std::vector<std::pair<GsString, GsString>>;

    /// @brief 默认构造
    GsUrl();
    /// @brief 根据字符串构造
    /// @param url
    GsUrl(const GsString &url);
    /// @brief 根据字符串构造
    /// @param url
    GsUrl(const char *url);
    /// @brief
    /// @param scheme
    /// @param pathEtc
    GsUrl(const GsString &scheme, const GsString &pathEtc);
    /// @brief
    /// @param scheme
    /// @param authority
    /// @param pathEtc
    GsUrl(const GsString &scheme, const GsString &authority, const GsString &pathEtc);
    /// @brief
    /// @param scheme
    /// @param authority
    /// @param path
    /// @param query
    GsUrl(const GsString &scheme, const GsString &authority, const GsString &path, const GsString &query);
    /// @brief
    /// @param scheme
    /// @param authority
    /// @param path
    /// @param query
    /// @param fragment
    GsUrl(const GsString &scheme, const GsString &authority, const GsString &path, const GsString &query, const GsString &fragment);
    /// @brief 拷贝构造
    /// @param url
    GsUrl(const GsUrl &url);
    /// @brief 移动构造
    /// @param url
    GsUrl(GsUrl &&url) noexcept;
    /// @brief
    /// @param baseURL
    /// @param relativeURL
    GsUrl(const GsUrl &baseURL, const GsString &relativeURL);
    /// @brief 默认析构
    ~GsUrl();

    /// @brief
    /// @param url
    /// @return
    GsUrl &operator=(const GsUrl &url);
    /// @brief
    /// @param url
    /// @return
    GsUrl &operator=(GsUrl &&url) noexcept;
    /// @brief
    /// @param url
    /// @return
    GsUrl &operator=(const GsString &url);
    /// @brief
    /// @param url
    /// @return
    GsUrl &operator=(const char *url);
    /// @brief
    /// @param url
    void Swap(GsUrl &url) noexcept;
    /// @brief
    void Clear();

    /// @brief
    /// @return
    GsString ToString() const;

    /// @brief
    /// @return
    const GsString &Scheme() const;
    /// @brief
    /// @param scheme
    void Scheme(const char *scheme);

    /// @brief
    /// @return
    const GsString &UserInfo() const;
    /// @brief
    /// @param userInfo
    void UserInfo(const char *userInfo);

    /// @brief
    /// @return
    const GsString &Host() const;
    /// @brief
    /// @param host
    void Host(const char *host);

    /// @brief
    /// @return
    unsigned short Port() const;
    /// @brief
    /// @param port
    void Port(unsigned short port);

    /// @brief
    /// @return
    unsigned short SpecifiedPort() const;

    /// @brief
    /// @return
    GsString Authority() const;
    /// @brief
    /// @param authority
    void Authority(const char *authority);

    /// @brief
    /// @return
    const GsString &Path() const;
    /// @brief
    /// @param path
    void Path(const char *path);

    /// @brief
    /// @return
    GsString Query() const;
    /// @brief
    /// @param query
    void Query(const char *query);

    /// @brief
    /// @param param
    /// @param val
    void AddQueryParameter(const GsString &param, const GsString &val = "");

    /// @brief
    /// @return
    const GsString &RawQuery() const;
    /// @brief
    /// @param query
    void RawQuery(const char *query);

    /// @brief
    /// @param plusIsSpace
    /// @return
    GsQueryParameters QueryParameters(bool plusIsSpace = true) const;
    /// @brief
    /// @param params
    void QueryParameters(const GsQueryParameters &params);

    /// @brief
    /// @return
    GsString Fragment() const;
    /// @brief
    /// @param fragment
    void Fragment(const char *fragment);

    /// @brief
    /// @return
    GsString RawFragment() const;
    /// @brief
    /// @param fragment
    void RawFragment(const char *fragment);

    /// @brief
    /// @return
    GsString PathEtc() const;
    /// @brief
    /// @param pathEtc
    void PathEtc(const char *pathEtc);

    /// @brief
    /// @return
    GsString PathAndQuery() const;
    /// @brief
    /// @param relativeURL
    void Resolve(const char *relativeURL);
    /// @brief
    /// @param relativeURL
    void Resolve(const GsUrl &relativeURL);
    /// @brief
    /// @return
    bool IsRelative() const;


    /// @brief
    /// @return
    bool Empty() const;
    /// @brief
    /// @param url
    /// @return
    bool operator==(const GsUrl &url) const;
    /// @brief
    /// @param url
    /// @return
    bool operator==(const GsString &url) const;
    /// @brief
    /// @param url
    /// @return
    bool operator!=(const GsUrl &url) const;
    /// @brief
    /// @param url
    /// @return
    bool operator!=(const GsString &url) const;

    /// @brief
    void Normalize();

    /// @brief
    /// @param segments
    void PathSegments(std::vector<GsString> &segments) const;

    /// @brief
    /// @param str
    /// @param reserved
    /// @param encodedStr
    static void Encode(const GsString &str, const GsString &reserved, GsString &encodedStr);
    /// @brief
    /// @param str
    /// @param decodedStr
    /// @param plusAsSpace
    static void Decode(const GsString &str, GsString &decodedStr, bool plusAsSpace = false);

protected:
    /// @brief
    /// @param url
    /// @return
    bool Equals(const GsUrl &url) const;
    /// @brief
    /// @return
    bool IsWellKnownPort() const;
    /// @brief
    /// @return
    unsigned short WellKnownPort() const;
    /// @brief
    /// @param url
    void Parse(const GsString &url);
    /// @brief
    /// @param begin
    /// @param end
    void ParseAuthority(GsString::const_iterator &begin, const GsString::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParseHostAndPort(GsString::const_iterator &begin, const GsString::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParsePath(GsString::const_iterator &begin, const GsString::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParsePathEtc(GsString::const_iterator &begin, const GsString::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParseQuery(GsString::const_iterator &begin, const GsString::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParseFragment(GsString::const_iterator &begin, const GsString::const_iterator &end);
    /// @brief
    /// @param path
    void MergePath(const GsString &path);
    /// @brief
    /// @param removeLeading
    void RemoveDotSegments(bool removeLeading = true);
    /// @brief
    /// @param path
    /// @param segments
    static void PathSegments(const GsString &path, std::vector<GsString> &segments);
    /// @brief
    /// @param segments
    /// @param leadingSlash
    /// @param trailingSlash
    void BuildPath(const std::vector<GsString> &segments, bool leadingSlash, bool trailingSlash);

private:
    /// @brief
    GsString m_strScheme;
    /// @brief
    GsString m_strUserInfo;
    /// @brief
    GsString m_strHost;
    /// @brief
    unsigned short m_nPort;
    /// @brief
    GsString m_strPath;
    /// @brief
    GsString m_strQuery;
    /// @brief
    GsString m_strFragment;
};


}// namespace Utility
}// namespace Lite
