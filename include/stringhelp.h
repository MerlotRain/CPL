/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file stringhelp.h
 * @brief 在应用程序中，凡是加载到内存中的，或程序主动创建的字符串变量
 *        统一使用utf-8编码
 *        中文字符也以utf-8的格式保存在GsString中，在特定的需求下，使用Converter
 *        转换为utf-16的GsWString操作
 *       
 *        当文件输出时，再将utf-8编码转换为文件所需的编码格式
 *        编码统一会带来很多便利，同时使用utf-8编码也更方便和应用层交互
 * @details 
 * @date 2023-07-03
 * @author
 *
 ******************************************************************************/

#pragma once

#include "stlhelp.h"

namespace Lite {
namespace Utility {

/// @brief Bool数值格式化文本内容
enum GsBoolFormat
{
    eFalseAndTrue,
    eYesAndNo,
    eOnAndOff,
};

class GsStringList;

/// @brief 单字节字符串
/// @details 所有写入GsString的字符串都应该是UTF-8编码
/// @details 程序内部创建的字符串必须是UTF-8，外部读入的数据应该主动转换为UTF-8
/// @details 数据写出时再主动转换为需要的编码格式
class UTILITY_EXPORT GsString : public GsStlString
{
public:
    /// @brief 缺省构造
    GsString() noexcept;
    /// @brief 拷贝构造
    GsString(const GsString &str) noexcept;
    /// @brief stl字符串拷贝构造
    GsString(const GsStlString &str) noexcept;
    /// @brief 由指针构造
    /// @param str
    GsString(GsString *str) noexcept;
    /// @brief 标准std::string构造
    template<class STD>
    GsString(const STD &str) noexcept
    {
        operator=(str.c_str());
    }
    /// @brief 单字节字符串构造
    GsString(const char *str) noexcept;
    /// @brief 单字节字符串构造
    GsString(char *str) noexcept;
    /// @brief 单字节字符串构造，偏移和长度
    GsString(const char *str, int off, int count) noexcept;
    /// @brief 单字节字符串构造，指定长度
    GsString(const char *str, int count) noexcept;
    /// @brief 根据字符串头尾指针构造
    GsString(const char *start, const char *end) noexcept;
    /// @brief 根据任意内存构造
    GsString(const unsigned char *start, const unsigned char *end) noexcept;
    /// @brief 重复字节
    GsString(int count, char e) noexcept;
    /// @brief 根据迭代器构造
    GsString(GsString::const_iterator first, GsString::const_iterator last) noexcept;
    /// @brief 根据迭代器构造
    GsString(GsString::iterator first, GsString::iterator last) noexcept;
    /// @brief 根据迭代器构造
    GsString(GsString::reverse_iterator first, GsString::reverse_iterator last) noexcept;
    /// @brief 根据迭代器构造
    GsString(GsString::const_reverse_iterator first, GsString::const_reverse_iterator last) noexcept;
    ~GsString();

    /// @brief 赋值操作符
    GsString &operator=(const char *str);
    /// @brief 赋值操作符
    GsString &operator=(const GsStlString &str);
    /// @brief 赋值操作符
    GsString &operator=(const GsString &str);
    /// @brief 取值操作符
    reference operator[](int index);
    /// @brief 取值操作符
    const_reference operator[](int index) const;
    /// @brief bool重载操作符，判断字符串是否为空
    operator bool() const;
    /// @brief const char* 重载操作符
    operator const char *() const;

    /// @brief 是否为空
    /// @return
    inline bool IsNullOrEmpty() const
    {
        return GsString::IsNullOrEmpty(this->data());
    }
    using GsStlString::operator+=;
    /// @brief +=操作符
    template<class STD>
    GsString &operator+=(const STD &str)
    {
        GsStlString::operator+=(str.c_str());
        return *this;
    }
    /// @brief +=操作符
    GsString &operator+=(const char *str);
    /// @brief +=操作符
    GsString &operator+=(int ch);
    /// @brief +=操作符
    GsString &operator+=(char ch);
    /// @brief +=操作符
    GsString &operator+=(const GsString &str);
    /// @brief +操作符
    GsString operator+(const char *str) const;
    /// @brief +操作符
    GsString operator+(const GsString &str) const;
    /// @brief +操作符
    GsString operator+(const GsStlString &str) const;
    /// @brief 获取UTF8格式的长度
    /// @return
    int Length() const;
    /// @brief Convert the string to uppercase
    GsString &ToUpper();
    /// @brief Convert the string to lowercase
    GsString &ToLower();
    /// @brief Reverse the string
    GsString &Reverse();
    /// @brief Remove all trailing whitespace
    GsString &TrimRight();
    /// @brief Remove all leading whitespace
    GsString &TrimLeft();
    /// @brief Remove all leading and trailing whitespace
    GsString &Trimmed();
    /// @brief 分割自身得到字串
    GsStringList Split(const char *strSep);
    /// @brief 分割自身得到字串
    void Split(const char *strSep, GsStringList &vecStr);

    /// @brief 字符替换
    /// @param from
    /// @param to
    /// @param start
    /// @return
    GsString &Replace(char from, char to, size_type start = 0);

    /// @brief 字符串替换
    /// @param from
    /// @param to
    /// @param start
    /// @return
    GsString &Replace(const char *from, const char *to, size_type start = 0);
    GsString &Replace(const GsString &from, const GsString &to, size_type start = 0);

    /// @brief 字符串是否以某个子串开头
    /// @param strHead
    /// @param bIgnoringCase
    /// @return
    inline bool StartWith(const char *strHead, bool bIgnoringCase = false) const
    {
        return GsString::StartWith(this->data(), strHead, bIgnoringCase);
    }
    /// @brief 字符串是否以某个子串结尾
    /// @param strEnd
    /// @param bIgnoringCase
    /// @return
    inline bool EndWith(const char *strEnd, bool bIgnoringCase = false) const
    {
        return GsString::EndWith(this->data(), strEnd, bIgnoringCase);
    }

    /// @brief 字符串格式化，字符串本身就是format串，生成一个新的字符串
    /// @tparam T
    /// @tparam ...Args
    /// @param t
    /// @param ...args
    /// @return
    template<typename T, typename... Args>
    inline GsString Format(T &&t, Args &&...args)
    {
        return GsString::Format(this->data(), t, std::forward<Args>(args)...);
    }

    /// @brief 字符串是否包含某个字符
    /// @param c
    /// @param bIgnoringCase
    /// @return
    inline bool Contains(char c, bool bIgnoringCase = false) const
    {
        return GsString::Contains(this->data(), c, bIgnoringCase);
    }

    /// @brief 字符串是否包含某个子串
    /// @param c
    /// @param bIgnoringCase
    /// @return
    inline bool Contains(const char *c, bool bIgnoringCase = false) const
    {
        return GsString::Contains(this->data(), c, bIgnoringCase);
    }

    /// @brief 删除字符
    /// @param ch
    /// @return
    GsString &Remove(char ch);
    /// @brief 删除字符串
    /// @param src
    /// @return
    GsString &Remove(const char *src);

    /// @brief 判断字符串是否为空
    static bool IsNullOrEmpty(const char *str);

    /// @brief 字符串是否以某个子串开头
    /// @param str
    /// @param strHead
    /// @param bIgnoringCase
    /// @return
    static bool StartWith(const char *str, const char *strHead, bool bIgnoringCase = false);

    /// @brief 字符串是否以某个子串结束
    /// @param str
    /// @param strTail
    /// @param bIgnoringCase
    /// @return
    static bool EndWith(const char *str, const char *strTail, bool bIgnoringCase = false);

    /// @brief 字符串是否包含某个字符
    /// @param str
    /// @param c
    /// @param bIgnoringCase
    /// @return
    static bool Contains(const char *str, char c, bool bIgnoringCase = false);

    /// @brief 字符串是否包含某个子串
    /// @param str
    /// @param c
    /// @param bIgnoringCase
    /// @return
    static bool Contains(const char *str, const char *c, bool bIgnoringCase = false);

    /// @brief 删除字符串中规则匹配成功的子串
    /// @param str
    /// @param c
    /// @return
    static GsString Remove(const char *str, const char *c);

    /// @brief 字符串比较
    /// @param strA
    /// @param strB
    /// @return
    static int Compare(const char *strA, const char *strB);

    /// @brief 字符串转义
    /// @param str
    /// @param strictJSON
    /// @return
    static GsString Escape(const char *str, bool strictJSON = false);

    /// @brief 字符串反向转义
    /// @param str
    /// @return
    static GsString Unescape(const char *str);

    /// @brief 字符串格式化
    /// @tparam ...Args
    /// @param format
    /// @param ...args
    /// @return
    template<typename... Args>
    static GsString Format(const char *format, Args &&...args)
    {
        auto size_buf = std::snprintf(nullptr, 0, format, std::forward<Args>(args)...) + 1;
        std::unique_ptr<char[]> buf(new (std::nothrow) char[size_buf]);

        if (!buf)
        {
            return GsString("");
        }

        std::snprintf(buf.get(), size_buf, format, std::forward<Args>(args)...);
        return GsString(buf.get(), buf.get() + size_buf - 1);
    }

public:
    /// @brief boolean值转字符串
    /// @param value
    /// @param format
    /// @return
    static GsString ToString(bool value, GsBoolFormat format = eFalseAndTrue);

    /// @brief 整型数值转字符串
    /// @param value 数值
    /// @param base 进制，支持2，8，10，16进制，默认使用10进制
    /// @param width 字符串宽度 -1 : 直接使用格式化的结果； other: 使用输入值
    ///         eg GsString::Format(1)=> 1;   GsString::Format(1,10,2)=> 01;
    /// @param fill 格式化后字符串长度不足预设值，填充字符
    ///         eg GsString::Format(1, 10, 2) => 01; GsString::Format(1, 10, 2, 'X') =>  X1;
    /// @param prefix 非10进制结果是否添加相应前缀
    /// @return
    static GsString ToString(short value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 无符号16位整型转字符串
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    static GsString ToString(unsigned short value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 有符号32位整型转字符串
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    static GsString ToString(int value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 无符号32位整型转字符串
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    static GsString ToString(unsigned int value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 有符号32位整型转字符串
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    static GsString ToString(long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 无符号32位整型转字符串
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    static GsString ToString(unsigned long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 有符号64位整型转字符串
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    static GsString ToString(long long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 无符号64位整型转字符串
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    static GsString ToString(unsigned long long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 浮点数转字符串
    /// @param value
    /// @param format
    /// @param precision
    /// @return
    static GsString ToString(float value, char format = 'g', int precision = 6);
    /// @brief double转字符串
    /// @param value
    /// @param format
    /// @param precision
    /// @return
    static GsString ToString(double value, char format = 'g', int precision = 6);

    /// @brief 字符串追加字符串
    /// @param str 输入字符串
    /// @param width 输入字符串宽度 -1 : 直接使用输入字符串的宽度； other: 使用输入值
    /// @param fill 格式化后字符串长度不足预设值，填充字符
    ///         eg GsString("Hello").Arg("World") => "HelloWorld"; GsString("Hello").Arg("World", 6) => "Hello World";
    /// @return
    GsString &Arg(const GsString &str, int width = -1, char fill = ' ');
    GsString &Arg(GsString &&str, int width = -1, char fill = ' ');

    /// @brief 字符串后追加有符号16位整型数值
    /// @param value 数值
    /// @param base 进制，支持2，8，10，16进制，默认使用10进制
    /// @param width 字符串宽度 -1 : 直接使用格式化的结果； other: 使用输入值
    ///         eg GsString::Format(1)=> 1;   GsString::Format(1,10,2)=> 01;
    /// @param fill 格式化后字符串长度不足预设值，填充字符
    ///         eg GsString::Format(1, 10, 2) => 01; GsString::Format(1, 10, 2, 'X') =>  X1;
    /// @param prefix 非10进制结果是否添加相应前缀
    /// @return
    GsString &Arg(short value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 字符串后追加有符号16位整型数值
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    GsString &Arg(unsigned short value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 字符串后追加有符号32位整型数值
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    GsString &Arg(int value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 字符串后追加无符号32位整型数值
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    GsString &Arg(unsigned int value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 字符串后追加有符号32位整型数值
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    GsString &Arg(long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 字符串后追加无符号32位整型数值
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    GsString &Arg(unsigned long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 字符串后追加有符号32位整型数值
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    GsString &Arg(long long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    /// @brief 字符串后追加无符号64位整型数值
    /// @param value
    /// @param base
    /// @param width
    /// @param fill
    /// @param prefix
    /// @return
    GsString &Arg(unsigned long long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);

    /// @brief 字符串后追加浮点数
    /// @param value 数值
    /// @param format 'g' %g, 'f' %f
    /// @param precision
    /// @return
    GsString &Arg(float value, char format = 'g', int precision = 6);
    /// @brief 字符串后追加浮点数
    /// @param value
    /// @param format
    /// @param precision
    /// @return
    GsString &Arg(double value, char format = 'g', int precision = 6);

    // 字符转数值
public:
    /// @brief 字符串尝试转换16位有符号整数
    /// @param ok 是否转换成功
    /// @param base 进制
    /// @return
    short ToShort(bool *ok = nullptr, int base = 10) const noexcept;
    /// @brief 字符串尝试转换16位无符号整数
    /// @param ok
    /// @param base
    /// @return
    unsigned short ToUShort(bool *ok = nullptr, int base = 10) const noexcept;
    /// @brief 字符串尝试转换32位有符号整数
    /// @param ok
    /// @param base
    /// @return
    int ToInt(bool *ok = nullptr, int base = 10) const noexcept;
    /// @brief 字符串尝试转换32位无符号整数
    /// @param ok
    /// @param base
    /// @return
    unsigned int ToUInt(bool *ok = nullptr, int base = 10) const noexcept;
    /// @brief 字符串尝试转换为boolean值
    /// @param ok
    /// @return
    bool ToBoolean(bool *ok = nullptr) const noexcept;
    /// @brief 字符串尝试转换为64位有符号整数
    /// @param ok
    /// @param base
    /// @return
    long long ToLongLong(bool *ok = nullptr, int base = 10) const noexcept;
    /// @brief 字符串尝试转换为64位无符号整数
    /// @param ok
    /// @param base
    /// @return
    unsigned long long ToULongLong(bool *ok = nullptr, int base = 10) const noexcept;
    /// @brief 字符串尝试转换为32位浮点值
    /// @param ok
    /// @return
    float ToFloat(bool *ok = nullptr) const noexcept;
    /// @brief 字符串尝试转换为64位浮点值
    /// @param ok
    /// @return
    double ToDouble(bool *ok = nullptr) const noexcept;
};

inline GsString operator+(const GsString &a, const std::string &b)
{
    return a.operator+(b.c_str());
}
inline bool operator==(const GsString &a, const GsString &b)
{
    return GsString::Compare(a.c_str(), b.c_str());
}
inline bool operator==(const GsString &a, const std::string &b)
{
    return GsString::Compare(a.c_str(), b.c_str());
}
inline bool operator==(const GsString &a, const char *b)
{
    return GsString::Compare(a.c_str(), b);
}
inline bool operator==(const std::string &a, const GsString &b)
{
    return GsString::Compare(a.c_str(), b.c_str());
}
inline bool operator==(const char *a, const GsString &b)
{
    return GsString::Compare(a, b.c_str());
}


/// @brief 宽字节字符串
/// @details 建议使用UTF-16编码
class UTILITY_EXPORT GsWString : public GsStlWString
{
public:
    /// @brief 缺省构造
    GsWString() noexcept;
    /// @brief 拷贝构造
    GsWString(const GsWString &str) noexcept;
    /// @brief stl字符串构造
    GsWString(const GsStlWString &str) noexcept;
    /// @brief std::wstring构造字符串构造
    template<class STD>
    GsWString(const STD &str) noexcept
    {
        operator=(str.c_str());
    }
    /// @brief 宽字节构造
    GsWString(const wchar_t *str) noexcept;
    /// @brief 宽字节构造
    GsWString(wchar_t *str) noexcept;

    /// @brief 宽字节构造，偏移和长度
    GsWString(const wchar_t *str, int off, int count) noexcept;
    /// @brief 宽字节构造，指定长度
    GsWString(const wchar_t *str, int count) noexcept;
    /// @brief 宽字节构造，字符串头尾指针
    GsWString(const wchar_t *start, const wchar_t *end) noexcept;
    /// @brief 重复构造
    GsWString(int count, wchar_t e) noexcept;
    /// @brief 迭代器构造
    GsWString(GsWString::iterator first, GsWString::iterator last) noexcept;
    /// @brief 迭代器构造
    GsWString(GsWString::const_iterator first, GsWString::const_iterator last) noexcept;
    /// @brief 迭代器构造
    GsWString(GsWString::reverse_iterator first, GsWString::reverse_iterator last) noexcept;
    /// @brief 迭代器构造
    GsWString(GsWString::const_reverse_iterator first, GsWString::const_reverse_iterator last) noexcept;
    /// @brief 默认析构
    ~GsWString();
    /// @brief 等于赋值操作符
    GsWString &operator=(const wchar_t *str);
    /// @brief 等于赋值操作符
    GsWString &operator=(const GsStlWString &str);
    /// @brief 等于赋值操作符
    GsWString &operator=(const GsWString &str);

    /// @brief std::wstring操作符重载
    template<class STD>
    operator STD() const
    {
        return STD(c_str());
    }
    /// @brief bool操作符重载，标识字符串是否为空
    operator bool() const;
    using GsStlWString::operator+=;
    /// @brief +=操作符
    template<class STD>
    GsWString &operator+=(const STD &str)
    {
        GsStlWString::operator+=(str.c_str());
        return *this;
    }
    /// @brief 判断字符串是否为空
    /// @return
    inline bool IsNullOrEmpty() const
    {
        return GsWString::IsNullOrEmpty(this->data());
    }

    /// @brief +=操作符
    GsWString &
    operator+=(const GsWString &str);
    /// @brief +=操作符
    GsWString &operator+=(const wchar_t *str);
    /// @brief +操作符
    GsWString operator+(const wchar_t *str) const;
    /// @brief +操作符
    GsWString operator+(const GsStlWString &str) const;
    /// @brief +操作符
    GsWString operator+(const GsWString &str) const;
    /// @brief 判断字符串是否为空
    static bool IsNullOrEmpty(const wchar_t *str);

    /// @brief 宽字节格式化
    /// @tparam ...Args
    /// @param format
    /// @param ...args
    /// @return
    template<typename... Args>
    static GsWString Format(const wchar_t *format, Args &&...args)
    {
        auto size_buf = std::snprintf(nullptr, 0, format, std::forward<Args>(args)...) + 1;
        std::unique_ptr<char[]> buf(new (std::nothrow) char[size_buf]);

        if (!buf)
        {
            return GsWString("");
        }

        std::snprintf(buf.get(), size_buf, format, std::forward<Args>(args)...);
        return GsWString(buf.get(), buf.get() + size_buf - 1);
    }
};

inline GsWString operator+(const GsWString &a, const std::wstring &b)
{
    return a.operator+(b.c_str());
}


/// @brief 字符串链表
class UTILITY_EXPORT GsStringList : public std::list<GsString>
{
public:
    /// @brief
    GsStringList() noexcept;
    /// @brief 由单个字符串构造
    /// @param str
    GsStringList(const GsString &str) noexcept;
    /// @brief 拷贝构造
    /// @param l
    GsStringList(const std::list<GsString> &l) noexcept;
    /// @brief 移动构造
    /// @param l
    GsStringList(std::list<GsString> &&l) noexcept;
    /// @brief 由初始化列表构造
    /// @param args
    GsStringList(std::initializer_list<GsString> args) noexcept;
    /// @brief 赋值复制构造
    /// @param other
    /// @return
    GsStringList &operator=(const std::list<GsString> &rhs);
    /// @brief 赋值移动构造
    /// @param rhs
    /// @return
    GsStringList &operator=(std::list<GsString> &&rhs) noexcept;
    /// @brief 字符串链表是否存在某个字符串
    /// @param str
    /// @return
    bool Contains(const GsString &str);
    /// @brief 重载operator[]运算符
    /// @param i
    /// @return
    GsString operator[](size_t i);
    /// @brief 重载operator[]运算符
    /// @param i
    /// @return
    const GsString &operator[](size_t i) const;
};

/// @brief ASCII编码表
/// @details https://www.ascii-code.com/
class UTILITY_EXPORT GsAscii
{
public:
    /// @brief 返回具有给定ASCII值的字符的ASCII字符属性
    /// @details 输入值范围为[0,127]，超出范围返回0
    /// @param ch
    /// @return
    static int Properties(int ch);

    /// @brief 如果给定字符在ASCII范围内并且至少具有一个给定属性，则返回true
    /// @param ch
    /// @param properties
    /// @return
    static bool HasSomeProperties(int ch, int properties);

    /// @brief 如果给定字符在ASCII范围内并且具有所有给定属性，则返回true
    /// @param ch
    /// @param properties
    /// @return
    static bool HasProperties(int ch, int properties);

    /// @brief 判断输入字符代码是否是ASCII编码
    /// @param ch
    /// @return
    static bool IsAscii(int ch);
    /// @brief 如果给定字符是空白字符，则返回true。
    /// @param ch
    /// @return
    static bool IsSpace(int ch);
    /// @brief 如果给定字符是数字，则返回true。
    /// @param ch
    /// @return
    static bool IsDigit(int ch);
    /// @brief 如果给定字符是十六进制数字，则返回true。
    /// @param ch
    /// @return
    static bool IsHexDigit(int ch);
    /// @brief 如果给定字符是标点符号，则返回true。
    /// @param ch
    /// @return
    static bool IsPunctuation(int ch);
    /// @brief 如果给定字符是字母字符，则返回true。
    /// @param ch
    /// @return
    static bool IsAlpha(int ch);
    static bool IsAlphaNumeric(int ch);
    /// @brief 如果给定字符是小写字母，则返回true
    /// @param ch
    /// @return
    static bool IsLower(int ch);
    /// @brief 如果给定字符是大写字母，则返回true
    /// @param ch
    /// @return
    static bool IsUpper(int ch);
    /// @brief 如果给定字符可打印，则返回true。
    /// @param ch
    /// @return
    static bool IsPrintable(int ch);

    /// @brief 如果给定的字符是大写字符，则返回其小写对应字符，否则返回该字符。
    /// @param ch
    /// @return
    static int ToLower(int ch);
    /// @brief 如果给定的字符是小写字符，则返回其大写对应字符，否则返回该字符。
    /// @param ch
    /// @return
    static int ToUpper(int ch);
};


/// @brief 实现字符串编码相关的功能
class UTILITY_EXPORT GsTextConverter
{
public:
    /// @brief current locale encoding
    static constexpr auto ENCODING_LOCALE = "";
    /// @brief UTF-7 encoding
    static constexpr auto ENCODING_UTF7 = "UTF-7";
    /// @brief UTF-8 encoding
    static constexpr auto ENCODING_UTF8 = "UTF-8";
    /// @brief UTF-16 encoding
    static constexpr auto ENCODING_UTF16 = "UTF-16";
    /// @brief UTF-32 encoding
    static constexpr auto ENCODING_UTF32 = "UTF-32";
    /// @brief UCS-2 encoding
    static constexpr auto ENCODING_UCS2 = "UCS-2";
    /// @brief UCS-4 encoding
    static constexpr auto ENCODING_UCS4 = "UCS-4";
    /// @brief ASCII encoding
    static constexpr auto ENCODING_ASCII = "ASCII";
    /// @brief ISO-8859-1 (LATIN1) encoding
    static constexpr auto ENCODING_ISO8859_1 = "ISO-8859-1";
    /// @brief GBK encoding
    static constexpr auto ENCODING_GB2312 = "GBK";
    /// @brief GB18030 encoding
    static constexpr auto ENCODING_GB18030 = "GB18030";

public:
    /// @brief 字符串重新编码
    /// @param src 原字符串
    /// @param srcEncoding 原字符串编码
    /// @param dstEncoding 目标字符串编码
    /// @return
    static bool Convert(const char *src, const char *srcEncoding, const char *dstEncoding, GsString &dst);
    static bool Convert(const GsString &src, const char *srcEncoding, const char *dstEncoding, GsString &dst);

    /// @brief 字符串重新编码
    /// @param src 原字符串
    /// @param srcEncoding 原字符串编码
    /// @param dstEncoding 目标字符串编码
    /// @return
    static bool Convert(const wchar_t *src, const char *srcEncoding, const char *dstEncoding, GsString &dst);
    static bool Convert(const GsWString &src, const char *srcEncoding, const char *dstEncoding, GsString &dst);

    /// @brief 字符串重新编码
    /// @param src 原字符串
    /// @param srcEncoding 原字符串编码
    /// @param dstEncoding 目标字符串编码
    /// @return
    static bool Convert(const char *src, const char *srcEncoding, const char *dstEncoding, GsWString &dst);
    static bool Convert(const GsString &src, const char *srcEncoding, const char *dstEncoding, GsWString &dst);

    /// @brief UTF8转UTF16
    /// @param utf8
    /// @param utf16
    /// @return
    static bool Convert(const GsString &utf8, GsWString &utf16);
    /// @brief UTF8转UTF16
    /// @param utf8
    /// @param length
    /// @param utf16
    /// @return
    static bool Convert(const char *utf8, GsWString &utf16);

    /// @brief UTF16转UTF8
    /// @param utf16
    /// @param utf8
    /// @return
    static bool Convert(const GsWString &utf16, GsString &utf8);
    /// @brief UTF16转UTF8
    /// @param utf16
    /// @param length
    /// @param utf8
    /// @return
    static bool Convert(const wchar_t *utf16, GsString &utf8);
};


/// @brief 字符串输入输出流
class UTILITY_EXPORT GsStringStream : public GsStlSStream
{
    GsString m_str;

public:
    /// @brief 默认构造
    GsStringStream();
    /// @brief 由单字节字符串构造
    /// @param str
    GsStringStream(const GsString &str);
    /// @brief 默认析构
    virtual ~GsStringStream();
    /// @brief 获取流字符串
    /// @return
    GsString Str();
    /// @brief 获取流字符串
    /// @return
    const char *CStr();
    /// @brief GsString操作符
    operator GsString();
    /// @brief const char* 操作符
    operator const char *();
    template<class STD>
    operator STD()
    {
        return STD(CStr());
    }
};

/// @brief 字符串输出流
/// @details
class UTILITY_EXPORT GsOStringStream : public GsStlOSStream
{
    GsString m_str;

public:
    /// @brief 默认构造
    GsOStringStream();
    /// @brief 默认析构
    virtual ~GsOStringStream();
    /// @brief 获取流字符串
    /// @return
    GsString Str();
    /// @brief 获取流字符串
    /// @return
    const char *CStr();
    /// @brief String操作
    operator GsString();
    /// @brief const char*操作
    operator const char *();
    template<class STD>
    operator STD()
    {
        return STD(CStr());
    }
};

/// @brief 字符串输入流
/// @details
class UTILITY_EXPORT GsIStringStream : public GsStlISStream
{
    GsString m_str;

public:
    /// @brief 默认构造
    GsIStringStream();
    /// @brief 由单字节字符串构造
    /// @param str
    GsIStringStream(const GsString &str);
    /// @brief 默认析构
    virtual ~GsIStringStream();
    /// @brief 获取流字符串
    /// @return
    GsString Str();
    /// @brief 获取流字符串
    /// @return
    const char *CStr();
    /// @brief String操作
    operator GsString();
    /// @brief const char*操作
    operator const char *();
    template<class STD>
    operator STD()
    {
        return STD(CStr());
    }
};


/// @brief 忽略字符大小写的比较
struct UTILITY_EXPORT GsStringCompareIgnoreCase
{
    bool operator()(const GsString &l, const GsString &r) const;
};


}// namespace Utility
}// namespace Lite
