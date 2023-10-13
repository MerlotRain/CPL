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

#include "flags.h"
#include "memorymanager.h"
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
    Url(const String &scheme, const String &authority, const String &path,
        const String &query);
    /// @brief
    /// @param scheme
    /// @param authority
    /// @param path
    /// @param query
    /// @param fragment
    Url(const String &scheme, const String &authority, const String &path,
        const String &query, const String &fragment);
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
    static void Encode(const String &str, const String &reserved,
                       String &encodedStr);
    /// @brief
    /// @param str
    /// @param decodedStr
    /// @param plusAsSpace
    static void Decode(const String &str, String &decodedStr,
                       bool plusAsSpace = false);

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
    void ParseAuthority(String::const_iterator &begin,
                        const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParseHostAndPort(String::const_iterator &begin,
                          const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParsePath(String::const_iterator &begin,
                   const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParsePathEtc(String::const_iterator &begin,
                      const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParseQuery(String::const_iterator &begin,
                    const String::const_iterator &end);
    /// @brief
    /// @param begin
    /// @param end
    void ParseFragment(String::const_iterator &begin,
                       const String::const_iterator &end);
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
    void BuildPath(const std::vector<String> &segments, bool leadingSlash,
                   bool trailingSlash);

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


/// @brief HTTP 响应状态码
/// @details https://developer.mozilla.org/zh-CN/docs/Web/HTTP/Status
enum class HttpStatus
{
    /// @brief 这个临时响应表明，迄今为止的所有内容都是可行的，客户端应该继续请求，如果已经完成，则忽略它。
    eCONTINUE = 100,
    /// @brief 该代码是响应客户端的 Upgrade (en-US) 请求头发送的，指明服务器即将切换的协议。
    eSWITCHING_PROTOCOLS = 101,
    /// @brief 此代码表示服务器已收到并正在处理该请求，但当前没有响应可用。
    ePROCESSING = 102,

    /// @brief 指示请求成功，且请求的信息包含在响应中。
    eOK = 200,
    /// @brief 指示请求导致在响应被发送前创建新资源。
    eCREATED = 201,
    /// @brief 指示已接受请求做进一步处理。
    eACCEPTED = 202,
    /// @brief 指示返回的元信息来自缓存副本而不是原始服务器，因此可能不正确。
    eNON_AUTHORITATIVE_INFORMATION = 203,
    /// @brief 指示已成功处理请求并且响应已被设定为无内容。
    eNO_CONTENT = 204,
    /// @brief 指示客户端应重置（而非重新加载）当前资源。
    eRESET_CONTENT = 205,
    /// @brief 指示响应是包括字节范围的 GET 请求所请求的部分响应。
    ePARTIAL_CONTENT = 206,
    /// @brief 指示之后的消息体将是一个XML消息，并且可能依照之前子请求数量的不同，包含一系列独立的响应代码。
    eMULTI_STATUS = 207,
    /// @brief 服务器已经完成了对资源的GET请求，并且响应是对当前实例应用的一个或多个实例操作结果的表示。
    eIM_USED = 226,

    /// @brief 请求拥有多个可能的响应。用户代理或者用户应当从中选择一个。（没有标准化的方法来选择其中一个响应，但是建议使用指向可能性的 HTML 链接，以便用户可以选择。）
    eMULTIPLE_CHOICES = 300,
    /// @brief 请求资源的 URL 已永久更改。在响应中给出了新的 URL。
    eMOVED_PERMANENTLY = 301,
    /// @brief 此响应代码表示所请求资源的 URI 已 暂时 更改。未来可能会对 URI 进行进一步的改变。因此，客户机应该在将来的请求中使用这个相同的 URI。
    eFOUND = 302,
    /// @brief 服务器发送此响应，以指示客户端通过一个 GET 请求在另一个 URI 中获取所请求的资源。
    eSEE_OTHER = 303,
    /// @brief 这是用于缓存的目的。它告诉客户端响应还没有被修改，因此客户端可以继续使用相同的缓存版本的响应。
    eNOT_MODIFIED = 304,
    /// @brief 在 HTTP 规范中定义，以指示请求的响应必须被代理访问。由于对代理的带内配置的安全考虑，它已被弃用。
    eUSE_PROXY = 305,
    /// @brief 此响应代码不再使用；它只是保留。它曾在 HTTP/1.1 规范的早期版本中使用过。
    eUNUSED = 306,
    /// @brief 服务器发送此响应，以指示客户端使用在前一个请求中使用的相同方法在另一个 URI 上获取所请求的资源。
    /// @details 302 Found HTTP 响应代码具有相同的语义，但用户代理 不能 更改所使用的 HTTP 方法：如果在第一个请求中使用了 POST，则在第二个请求中必须使用 POST
    eTEMPORARY_REDIRECT = 307,

    /// @brief 这意味着资源现在永久位于由Location: HTTP Response 标头指定的另一个 URI。
    /// @details 这与 301 Moved Permanently HTTP 响应代码具有相同的语义，但用户代理不能更改所使用的 HTTP 方法：如果在第一个请求中使用 POST，则必须在第二个请求中使用 POST。
    eTERMANENT_REDIRECT = 308,


    /// @brief 指示服务器未能识别请求。 如果没有其他适用的错误，或者不知道准确的错误或错误没有自己的错误代码，则发送 BadRequest。
    eBAD_REQUEST = 400,
    /// @brief 指示请求的资源要求身份验证。 WWW-Authenticate 标头包含如何执行身份验证的详细信息。
    eUNAUTHORIZED = 401,
    /// @brief 保留 PaymentRequired 以供将来使用。
    ePAYMENT_REQUIRED = 402,
    /// @brief 指示服务器拒绝满足请求。
    eFORBIDDEN = 403,
    /// @brief 指示请求的资源不在服务器上
    eNOT_FOUND = 404,
    /// @brief 指示请求的资源上不允许请求方法（POST 或 GET）。
    eMETHOD_NOT_ALLOWED = 405,
    /// @brief 指示客户端已用 Accept 标头指示将不接受资源的任何可用表示形式。
    eNOT_ACCEPTABLE = 406,
    /// @brief 指示请求的代理要求身份验证。 Proxy-authenticate 标头包含如何执行身份验证的详细信息。
    ePROXY_AUTHENTICATION_REQUIRED = 407,
    /// @brief 指示客户端没有在服务器期望请求的时间内发送请求。
    eREQUEST_TIMEOUT = 408,
    /// @brief 指示由于服务器上的冲突而未能执行请求。
    eCONFLICT = 409,
    /// @brief 指示请求的资源不再可用。
    eGONE = 410,
    /// @brief 指示缺少必需的 Content-length 标头。
    eLENGTH_REQUIRED = 411,
    /// @brief 指示此请求的条件集失败，并且无法执行该请求。使用条件请求标头设置添加，如：If-Match、If-None-Match 或 If-Unmodified-Since。
    ePRECONDITION_FAILED = 412,
    /// @brief 指示请求太大，服务器无法处理。
    eREQUEST_ENTITY_TOO_LARGE = 413,
    /// @brief 指示 URI 太长。
    eREQUEST_URI_TOO_LONG = 414,
    /// @brief 指示请求是不受支持的类型。
    eUNSUPPORTED_MEDIA_TYPE = 415,
    /// @brief 指示无法返回从资源请求的数据范围，因为范围的开头在资源的开头之前，或因为范围的结尾在资源的结尾之后。
    eREQUESTED_RANGE_NOT_SATISFIABLE = 416,
    /// @brief 指示服务器未能符合 Expect 标头中给定的预期值。
    eEXPECTATION_FAILED = 417,
    /// @brief 服务端拒绝用茶壶煮咖啡。笑话，典故来源茶壶冲泡咖啡
    eI_M_A_TEAPOT = 418,
    /// @brief 请求格式正确，但由于语义错误而无法遵循。
    eUNPROCESSABLE_ENTITY = 422,
    /// @brief 正在访问的资源已锁定。
    eLOCKED = 423,
    /// @brief 由于前一个请求失败，请求失败。
    eFAILED_DEPENDENCY = 424,
    /// @brief 表示服务器不愿意冒险处理可能被重播的请求。
    eTOO_EARLY = 425,
    /// @brief 服务器拒绝使用当前协议执行请求，但在客户端升级到其他协议后可能愿意这样做。 服务端发送带有Upgrade (en-US) 字段的 426 响应 来表明它所需的协议（们）。
    eUPGRADE_REQUIRED = 426,

    /// @brief 指示服务器上发生了一般错误。
    eINTERNAL_SERVER_ERROR = 500,
    /// @brief 指示服务器不支持请求的函数。
    eNOT_IMPLEMENTED = 501,
    /// @brief 指示中间代理服务器从另一代理或原始服务器接收到错误响应。
    eBAD_GATEWAY = 502,
    /// @brief 指示服务器暂时不可用，通常是由于过多加载或维护。
    eSERVICE_UNAVAILABLE = 503,
    /// @brief 指示中间代理服务器在等待来自另一个代理或原始服务器的响应时已超时。
    eGATEWAY_TIMEOUT = 504,
    /// @brief 指示服务器不支持请求的 HTTP 版本。
    eHTTP_VERSION_NOT_SUPPORTED = 505,
    eINSUFFICIENT_STORAGE = 507,
    eNOT_EXTENDED = 510,
};

/// @brief  http状态码分类
enum class HttpStatusClasses
{
    /// @brief 无效分类
    eUnknown = 0,
    /// @brief 1** 信息，服务器收到请求，需要请求者继续执行操作
    eInformational = 100,
    e1XX = 100,
    /// @brief 2** 成功，操作被成功接收并处理
    eSuccessful = 200,
    e2XX = 200,
    /// @brief 3** 重定向，需要进一步的操作以完成请求
    eRedirects = 300,
    e3XX = 300,
    /// @brief 4** 客户端错误，请求包含语法错误或无法完成请求
    eClientErrors = 400,
    e4XX = 400,
    /// @brief 5** 服务器错误，服务器在处理请求的过程中发生了错误
    eServerErrors = 500,
    e5XX = 500,
};


/// @brief HTTP请求的的方法
enum HttpMethod
{
    /// @brief 未知方法或自定义方法。
    eUNKNOWNMETHOD = -1,
    /// @brief 请求指定的页面信息，并返回实体主体。
    eGET,
    /// @brief 类似于get请求，只不过返回的响应中没有具体的内容，用于获取报头
    eHEAD,
    /// @brief 向指定资源提交数据进行处理请求（例如提交表单或者上传文件）。数据被包含在请求体中。POST请求可能会导致新的资源的建立和 / 或已有资源的修改。
    ePOST,
    /// @brief 从客户端向服务器传送的数据取代指定的文档的内容。
    ePUT,
    /// @brief 从客户端向服务器传送的数据取代指定的文档的内容。
    eDELETE,
    /// @brief HTTP / 1.1协议中预留给能够将连接改为管道方式的代理服务器。
    eCONNECT,
    /// @brief 允许客户端查看服务器的性能。
    eOPTIONS,
    /// @brief 回显服务器收到的请求，主要用于测试或诊断。
    eTRACE,
    /// @brief 实体中包含一个表，表中说明与该URI所表示的原内容的区别。
    ePATCH,
    /// @brief 请求服务器将指定的页面移至另一个网络地址。
    eMOVE,
    /// @brief 请求服务器将指定的页面拷贝至另一个网络地址。
    eCOPY,
    /// @brief 请求服务器建立链接关系。
    eLINK,
    /// @brief 断开链接关系
    eUNLINK,
    /// @brief 允许客户端发送经过封装的请求。
    eWRAPPED,
};


/// @brief Http Cookie 属性
/// @details 防止 Web 应用程序遭受跨站点请求伪造 (CSRF) 攻击
enum class HttpSameSite
{
    /// @brief 默认
    eDefault,
    /// @brief
    eNone,
    /// @brief
    eLax,
    /// @brief
    eStrict,
};


struct Cookie;
struct MediaType;


class CookieContainer;
class HttpRequest;
class HttpResponse;
class HttpServer;
class HttpSession;
class HttpMessage;
class DNS;
class FTPClientSession;


/// @brief Cookie 对象
struct M2_API Cookie
{
    int Version;
    String Name;
    String Value;
    String Comment;
    String Domain;
    String Path;
    String Priority;
    bool Secure;
    int MaxAge;
    bool HttpOnly;
    HttpSameSite SameSite;


    Cookie();
    Cookie(const char *cookieHeader);
    Cookie(const char *name, const char *value, const char *path = NULL,
           const char *domain = NULL);
    Cookie(const Cookie &cookie);
    Cookie(Cookie &&cookie) noexcept;
    operator bool() const;
    Cookie &operator=(const Cookie &cookie);
    Cookie &operator=(Cookie &&cookie) noexcept;
    bool operator==(const Cookie &cookie) const;
    void Swap(Cookie &cookie);

    String ToString() const;

    static std::string Escape(const std::string &str);
    static std::string Unescape(const std::string &str);
};


/// @brief Media Type 对象
/// @details https://www.iana.org/assignments/media-types/media-types.xhtml
struct M2_API MediaType
{
    String Type;
    String SubType;
};


class M2_API CookiesContainer
{
};

class M2_API HttpRequest
{
};

class M2_API HttpResponse
{
};

class HttpServer
{
};

class HttpMessage
{
};

class DNS
{
};

}// namespace m2
