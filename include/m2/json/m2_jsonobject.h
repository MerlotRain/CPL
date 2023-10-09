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

/// @brief Json对象
class M2_API JsonObject
{
public:
    enum class ObjectType
    {
        Unknown,
        Null,
        Object,
        Array,
        Boolean,
        String,
        Integer,
        Long,
        Double
    };

    enum class PrettyFormat
    {
        Plain, ///< No extra whitespace or formatting applied
        Spaced,///< Minimal whitespace inserted
        Pretty ///< Formatted output
    };

public:
    JsonObject();
    explicit JsonObject(const char *name, const JsonObject &parent);
    ~JsonObject();
    JsonObject(const JsonObject &other);
    JsonObject(JsonObject &&other) noexcept;
    JsonObject &operator=(const JsonObject &other);
    JsonObject &operator=(JsonObject &&other) noexcept;
    JsonObject Clone() const;

    ObjectType Type() const;
    String Name() const;

    void Add(const char *name, const String &strValue);
    void Add(const char *name, const char *pszValue);
    void Add(const char *name, double dfValue);
    void Add(const char *name, int nValue);
    void Add(const char *name, long long nValue);
    void Add(const char *name, const JsonArray &objValue);
    void Add(const char *name, const JsonObject &objValue);
    void AddNoSplitName(const char *name, const JsonObject &objValue);
    void Add(const char *name, bool bValue);
    void AddNull(const char *name);

    void Set(const char *name, const String &osValue);
    void Set(const char *name, const char *pszValue);
    void Set(const char *name, double dfValue);
    void Set(const char *name, int nValue);
    void Set(const char *name, long long nValue);
    void Set(const char *name, bool bValue);
    void SetNull(const char *name);


    String AsString(const char *name, const String &osDefault = "") const;
    double AsDouble(const char *name, double dfDefault = 0.0) const;
    int AsInteger(const char *name, int nDefault = 0) const;
    long long AsLongLong(const char *name, long long nDefault = 0) const;
    JsonArray AsArray(const char *name) const;
    JsonObject AsObject(const char *name) const;
    bool AsBoolean(const char *name, bool defValue = false) const;

    String ToString(const String &defValue = "") const;
    double ToDouble(double defValue = 0.0) const;
    int ToInteger(int defValue = 0) const;
    long long ToLongLong(long long defValue = 0) const;
    bool ToBoolean(bool defValue = false) const;
    JsonArray ToArray() const;
    String Format(PrettyFormat eFormat) const;

    void Delete(const char *name);
    void DeleteNoSplitName(const char *name);

    JsonObject operator[](const char *name) const;

    std::vector<JsonObject> Children() const;
    bool IsValid() const;
    void Deinit();

protected:
    explicit JsonObject(const char *name, void *pObject);
    JsonObject GetObjectByPath(const String &path, String &name) const;

private:
    void *m_pJsonObject = nullptr;
    String m_strKey;
    friend class JsonArray;
    friend class JsonDocument;
};
