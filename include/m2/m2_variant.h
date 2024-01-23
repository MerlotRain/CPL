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
** copy of this software and associated documentation files (the "Software"), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
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

#ifndef M2_VARIANT_H_
#define M2_VARIANT_H_

#include <m2_datetime.h>
#include <m2_object.h>
#include <m2_string.h>

namespace m2 {

class Variant
{
public:
    enum VarType
    {
        eUnknownVarType = -2,
        eEmpty = -1,
        eI1 = 0,
        eI2,
        eI4,
        eI8,
        eUI1,
        eUI2,
        eUI4,
        eUI8,
        eR4,
        eR8,
        eString,
        eBool,
        eObject,
        eBlob,
        eDateTime,
    };

    VarType Type;
    union
    {
        char cVal;
        unsigned char ucVal;
        short sVal;
        unsigned short usVal;
        int iVal;
        unsigned int uiVal;
        long long llVal;
        unsigned long long ullVal;
        float fltVal;
        double dblVal;
        bool boolVal;
        RefObject *objVal;
        char *strVal;
        unsigned char *blbVal;
        long long dateVal;
    };

    Variant();
    Variant(char v);
    Variant(unsigned char v);
    Variant(short v);
    Variant(unsigned short v);
    Variant(int v);
    Variant(unsigned int v);
    Variant(long long v, bool bDateTime = false);
    Variant(const DateTime &dt);
    Variant(unsigned long long v);
    Variant(float v);
    Variant(double v);
    Variant(bool v);
    Variant(RefObject *v);
    Variant(const char *v);
    Variant(const String &str);
    Variant(const unsigned char *v, int nLen);
    Variant(const Variant &rhs);
    Variant(Variant &&rhs);
    Variant(VarType type);
    virtual ~Variant();

    Variant &operator=(const Variant &);
    Variant &operator=(Variant &&);
    Variant &operator=(char v);
    Variant &operator=(unsigned char v);
    Variant &operator=(short v);
    Variant &operator=(unsigned short v);
    Variant &operator=(int v);
    Variant &operator=(unsigned int v);
    Variant &operator=(long long v);
    Variant &operator=(unsigned long long v);
    Variant &operator=(float v);
    Variant &operator=(double v);
    Variant &operator=(bool v);
    Variant &operator=(const char *v);
    Variant &operator=(const String &str);
    Variant &operator=(RefObject *v);

    bool operator==(const Variant &o) const;
    bool operator!=(const Variant &o) const;

    void swap(Variant &rhs);
    void clear();

    char toChar() const;
    unsigned char toUChar() const;
    short toShort() const;
    unsigned short toUShort() const;
    int toInt() const;
    unsigned int toUInt() const;
    long long toLongLong() const;
    unsigned long long toULongLong() const;
    float toFloat() const;
    double toDouble() const;
    bool toBool() const;
    RefObject *toObject() const;
    String toString() const;
    int toBlob(unsigned char *bBlob) const;

    operator char() const;
    operator unsigned char() const;
    operator short() const;
    operator unsigned short() const;
    operator int() const;
    operator unsigned int() const;
    operator long long() const;
    operator unsigned long long() const;
    operator bool() const;
    operator float() const;
    operator double() const;
    operator const char *() const;
    operator RefObject *();

    void setBlob(const unsigned char *bBlob, int nLen);
    void setBlob(const char *str, int nLen);
    unsigned char *allocBlob(int nLen);
    int valueSize() const;
    const void *valuePtr() const;
    unsigned long long hashCode() const;
    String toString() const;

    static const Variant &empty();
};

typedef std::map<String, Variant> VariantMap;

}// namespace m2

#endif//M2_VARIANT_H_