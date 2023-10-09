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

/// @brief Json数组对象
class M2_API JsonArray : public JsonObject
{
    friend class JsonObject;
    friend class JsonDocument;

    JsonArray(const char *name, void *pJsonObject);
    class const_iterator
    {
        const JsonArray &m_Array;
        int m_nIndex;
        mutable JsonObject m_Object;

    public:
        const_iterator(const JsonArray &array, bool bStart);
        ~const_iterator() = default;
        JsonObject &operator*() const;
        const_iterator &operator++();
        bool operator==(const const_iterator &it) const;
        bool operator!=(const const_iterator &it) const;
    };

public:
    JsonArray();
    JsonArray(const char *name);
    JsonArray(const JsonObject &other);

    int Size() const;
    void Add(const JsonObject &objValue);
    void Add(const String &strValue);
    void Add(const char *pszValue);
    void Add(double dfValue);
    void Add(int nValue);
    void Add(long long nValue);
    void Add(bool bValue);
    JsonObject operator[](int nIndex);
    const JsonObject operator[](int nIndex) const;
    const_iterator begin() const;
    const_iterator end() const;
};
