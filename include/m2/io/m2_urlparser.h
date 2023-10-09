/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#pragma once

#include "bytebuffer.h"
#include "flags.h"
#include "stringhelp.h"

namespace m2 {


/// @brief Url解析类
class M2_API Url
{
public:
    using QueryParameters = std::vector<std::pair<String, String>>;

    /// @brief 默认构造
    Url();
    /// @brief 根据字符串构造
    /// @param url
    Url(const String &url);
    /// @brief 根据字符串构造
    /// @param url
    Url(const char *url);
    /// @brief
    /// @param scheme
    /// @param pathEtc
    Url(const String &scheme, const String &pathEtc);
    /// @brief
    /// @param scheme
    /// @param authority
    /// @param pathEtc
    Url(const String &scheme, const String &authority, const String &pathEtc);
    /// @brief
    /// @param scheme
    /// @param authority
    /// @param path
    /// @param query
    Url(const String &scheme, const String &authority, const String &path, const String &query);
    /// @brief
    /// @param scheme
    /// @param authority
    /// @param path
    /// @param query
    /// @param fragment
    Url(const String &scheme, const String &authority, const String &path, const String &query, const String &fragment);
    /// @brief 拷贝构造
    /// @param url
    Url(const Url &url);
    /// @brief 移动构造
    /// @param url
    Url(Url &&url) noexcept;
    /// @brief
    /// @param baseURL
    /// @param relativeURL
    Url(const Url &baseURL, const String &relativeURL);
    /// @brief 默认析构
    ~Url();

    /// @brief
    /// @param url
    /// @return
    Url &operator=(const Url &url);
    /// @brief
    /// @param url
    /// @return
    Url &operator=(Url &&url) noexcept;
    /// @brief
    /// @param url
    /// @return
    Url &operator=(const String &url);
    /// @brief
    /// @param url
    /// @return
    Url &operator=(const char *url);
    /// @brief
    /// @param url
    void Swap(Url &url) noexcept;
    /// @brief
    void Clear();

    /// @brief
    /// @return
    String ToString() const;

    /// @brief
    /// @return
    const String &Scheme() const;
    /// @brief
    /// @param scheme
    void Scheme(const char *scheme);

    /// @brief
    /// @return
    const String &UserInfo() const;
    /// @brief
    /// @param userInfo
    void UserInfo(const char *userInfo);

    /// @brief
    /// @return
    const String &Host() const;
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
    String Authority() const;
    /// @brief
    /// @param authority
    void Authority(const char *authority);

    /// @brief
    /// @return
    const String &Path() const;
    /// @brief
    /// @param path
    void Path(const char *path);

    /// @brief
    /// @return
    String Query() const;
    /// @brief
    /// @param query
    void Query(const char *query);

    /// @brief
    /// @param param
    /// @param val
    void AddQueryParameter(const String &param, const String &val = "");

    /// @brief
    /// @return
    const String &RawQuery() const;
    /// @brief
    /// @param query
    void RawQuery(const char *query);

    /// @brief
    /// @param plusIsSpace
    /// @return
    QueryParameters QueryParameters(bool plusIsSpace = true) const;
    /// @brief
    /// @param params
    void QueryParameters(const QueryParameters &params);

    /// @brief
    /// @return
    String Fragment() const;
    /// @brief
    /// @param fragment
    void Fragment(const char *fragment);

    /// @brief
    /// @return
    String RawFragment() const;
    /// @brief
    /// @param fragment
    void RawFragment(const char *fragment);

    /// @brief
    /// @return
    String PathEtc() const;
    /// @brief
    /// @param pathEtc
    void PathEtc(const char *pathEtc);

    /// @brief
    /// @return
    String PathAndQuery() const;
    /// @brief
    /// @param relativeURL
    void Resolve(const char *relativeURL);
    /// @brief
    /// @param relativeURL
    void Resolve(const Url &relativeURL);
    /// @brief
    /// @return
    bool IsRelative() const;


    /// @brief
    /// @return
    bool Empty() const;
    /// @brief
    /// @param url
    /// @return
    bool operator==(const Url &url) const;
    /// @brief
    /// @param url
    /// @return
    bool operator==(const String &url) const;
    /// @brief
    /// @param url
    /// @return
    bool operator!=(const Url &url) const;
    /// @brief
    /// @param url
    /// @return
    bool operator!=(const String &url) const;

    /// @brief
    void Normalize();

    /// @brief
    /// @param segments
    void PathSegments(std::vector<String> &segments) const;

    /// @brief
    /// @param str
    /// @param reserved
    /// @param encodedStr
    static void Encode(const String &str, const String &reserved, String &encodedStr);
    /// @brief
    /// @param str
    /// @param decodedStr
    /// @param plusAsSpace
    static void Decode(const String &str, String &decodedStr, bool plusAsSpace = false);

protected:
    /// @brief
    /// @param url
    /// @return
    bool Equals(const Url &url) const;
    /// @brief
    /// @return
    bool IsWellKnownPort() const;
    /// @brief
    /// @return
    unsigned short WellKnownPort() const;
    /// @brief
    /// @param url
    void Parse(const String &url);
    /// @brief
    /// @param begin
    /// @param end
    void ParseAuthority(String::const_iterator &begin, const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParseHostAndPort(String::const_iterator &begin, const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParsePath(String::const_iterator &begin, const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParsePathEtc(String::const_iterator &begin, const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParseQuery(String::const_iterator &begin, const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParseFragment(String::const_iterator &begin, const String::const_iterator &end);
    /// @brief
    /// @param path
    void MergePath(const String &path);
    /// @brief
    /// @param removeLeading
    void RemoveDotSegments(bool removeLeading = true);
    /// @brief
    /// @param path
    /// @param segments
    static void PathSegments(const String &path, std::vector<String> &segments);
    /// @brief
    /// @param segments
    /// @param leadingSlash
    /// @param trailingSlash
    void BuildPath(const std::vector<String> &segments, bool leadingSlash, bool trailingSlash);

private:
    /// @brief
    String m_strScheme;
    /// @brief
    String m_strUserInfo;
    /// @brief
    String m_strHost;
    /// @brief
    unsigned short m_nPort;
    /// @brief
    String m_strPath;
    /// @brief
    String m_strQuery;
    /// @brief
    String m_strFragment;
};


}// namespace m2
