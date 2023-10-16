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

#ifndef M2_URLPARSER_H_
#define M2_URLPARSER_H_

#include <m2_string.h>

namespace m2 {

class M2_API Url
{
public:
    using QueryParameters = std::vector<std::pair<String, String>>;

    Url();
    explicit Url(const String &url);
    explicit Url(const char *url);
    Url(const String &scheme, const String &pathEtc);
    Url(const String &scheme, const String &authority, const String &pathEtc);
    Url(const String &scheme, const String &authority, const String &path,
        const String &query);
    Url(const String &scheme, const String &authority, const String &path,
        const String &query, const String &fragment);
    Url(const Url &baseURL, const String &relativeURL);
    Url(const Url &url);
    Url(Url &&url) noexcept;
    Url &operator=(const Url &url);
    Url &operator=(Url &&url) noexcept;
    Url &operator=(const String &url);
    Url &operator=(const char *url);
    ~Url();

    void swap(Url &url) noexcept;
    void clear();
    String toString() const;

    const String &scheme() const;
    void setScheme(const char *scheme);

    const String &userInfo() const;
    void setUserInfo(const char *userInfo);

    const String &host() const;
    void setHost(const char *host);

    unsigned short port() const;
    void setPort(unsigned short port);

    unsigned short specifiedPort() const;

    String authority() const;
    void setAuthority(const char *authority);

    const String &path() const;
    void setPath(const char *path);

    String query() const;
    void setQuery(const char *query);

    void addQueryParameter(const String &param, const String &val = "");

    const String &rawQuery() const;
    void setRawQuery(const char *query);

    QueryParameters queryParameters(bool plusIsSpace = true) const;
    void setQueryParameters(const QueryParameters &params);

    String fragment() const;
    void setFragment(const char *fragment);

    String rawFragment() const;
    void setRawFragment(const char *fragment);

    String pathEtc() const;
    void setPathEtc(const char *pathEtc);

    String pathAndQuery() const;
    void setResolve(const char *relativeURL);
    void setResolve(const Url &relativeURL);
    bool isRelative() const;

    bool isEmpty() const;

    bool operator==(const Url &url) const;
    bool operator==(const String &url) const;
    bool operator!=(const Url &url) const;
    bool operator!=(const String &url) const;

    void normalize();

    void pathSegments(std::vector<String> &segments) const;
    static void encode(const String &str, const String &reserved,
                       String &encodedStr);
    static void decode(const String &str, String &decodedStr,
                       bool plusAsSpace = false);

protected:
    bool isEquals(const Url &url) const;
    bool isWellKnownPort() const;
    unsigned short wellKnownPort() const;
    void parse(const String &url);
    void parseAuthority(String::const_iterator &begin,
                        const String::const_iterator &end);
    void parseHostAndPort(String::const_iterator &begin,
                          const String::const_iterator &end);
    void parsePath(String::const_iterator &begin,
                   const String::const_iterator &end);
    void parsePathEtc(String::const_iterator &begin,
                      const String::const_iterator &end);

    void parseQuery(String::const_iterator &begin,
                    const String::const_iterator &end);
    void parseFragment(String::const_iterator &begin,
                       const String::const_iterator &end);
    void mergePath(const String &path);
    void removeDotSegments(bool removeLeading = true);
    static void pathSegments(const String &path, std::vector<String> &segments);
    void buildPath(const std::vector<String> &segments, bool leadingSlash,
                   bool trailingSlash);

private:
    String m_strScheme;
    String m_strUserInfo;
    String m_strHost;
    unsigned short m_nPort;
    String m_strPath;
    String m_strQuery;
    String m_strFragment;
};

}// namespace m2

#endif//M2_URLPARSER_H_