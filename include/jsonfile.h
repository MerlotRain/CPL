/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file json.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "stringhelp.h"

namespace Lite {
namespace Utility {

class GsJsonArray;

/// @brief Json对象
class UTILITY_EXPORT GsJsonObject
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
    GsJsonObject();
    explicit GsJsonObject(const char *name, const GsJsonObject &parent);
    ~GsJsonObject();
    GsJsonObject(const GsJsonObject &other);
    GsJsonObject(GsJsonObject &&other) noexcept;
    GsJsonObject &operator=(const GsJsonObject &other);
    GsJsonObject &operator=(GsJsonObject &&other) noexcept;
    GsJsonObject Clone() const;

    ObjectType Type() const;
    GsString Name() const;

    void Add(const char *name, const GsString &strValue);
    void Add(const char *name, const char *pszValue);
    void Add(const char *name, double dfValue);
    void Add(const char *name, int nValue);
    void Add(const char *name, long long nValue);
    void Add(const char *name, const GsJsonArray &objValue);
    void Add(const char *name, const GsJsonObject &objValue);
    void AddNoSplitName(const char *name, const GsJsonObject &objValue);
    void Add(const char *name, bool bValue);
    void AddNull(const char *name);

    void Set(const char *name, const GsString &osValue);
    void Set(const char *name, const char *pszValue);
    void Set(const char *name, double dfValue);
    void Set(const char *name, int nValue);
    void Set(const char *name, long long nValue);
    void Set(const char *name, bool bValue);
    void SetNull(const char *name);


    GsString AsString(const char *name, const GsString &osDefault = "") const;
    double AsDouble(const char *name, double dfDefault = 0.0) const;
    int AsInteger(const char *name, int nDefault = 0) const;
    long long AsLongLong(const char *name, long long nDefault = 0) const;
    GsJsonArray AsArray(const char *name) const;
    GsJsonObject AsObject(const char *name) const;
    bool AsBoolean(const char *name, bool defValue = false) const;

    GsString ToString(const GsString &defValue = "") const;
    double ToDouble(double defValue = 0.0) const;
    int ToInteger(int defValue = 0) const;
    long long ToLongLong(long long defValue = 0) const;
    bool ToBoolean(bool defValue = false) const;
    GsJsonArray ToArray() const;
    GsString Format(PrettyFormat eFormat) const;

    void Delete(const char *name);
    void DeleteNoSplitName(const char *name);

    GsJsonObject operator[](const char *name) const;

    std::vector<GsJsonObject> Children() const;
    bool IsValid() const;
    void Deinit();

protected:
    explicit GsJsonObject(const char *name, void *pObject);
    GsJsonObject GetObjectByPath(const GsString &path, GsString &name) const;

private:
    void *m_pJsonObject = nullptr;
    GsString m_strKey;
    friend class GsJsonArray;
    friend class GsJsonDocument;
};


/// @brief Json数组对象
class UTILITY_EXPORT GsJsonArray : public GsJsonObject
{
    friend class GsJsonObject;
    friend class GsJsonDocument;

    GsJsonArray(const char *name, void *pJsonObject);
    class const_iterator
    {
        const GsJsonArray &m_Array;
        int m_nIndex;
        mutable GsJsonObject m_Object;

    public:
        const_iterator(const GsJsonArray &array, bool bStart);
        ~const_iterator() = default;
        GsJsonObject &operator*() const;
        const_iterator &operator++();
        bool operator==(const const_iterator &it) const;
        bool operator!=(const const_iterator &it) const;
    };

public:
    GsJsonArray();
    GsJsonArray(const char *name);
    GsJsonArray(const GsJsonObject &other);

    int Size() const;
    void Add(const GsJsonObject &objValue);
    void Add(const GsString &strValue);
    void Add(const char *pszValue);
    void Add(double dfValue);
    void Add(int nValue);
    void Add(long long nValue);
    void Add(bool bValue);
    GsJsonObject operator[](int nIndex);
    const GsJsonObject operator[](int nIndex) const;
    const_iterator begin() const;
    const_iterator end() const;
};


/// @brief Json文档
class UTILITY_EXPORT GsJsonDocument
{
public:
    GsJsonDocument();
    ~GsJsonDocument();
    GsJsonDocument(const GsJsonDocument &other);
    GsJsonDocument &operator=(const GsJsonDocument &other);
    GsJsonDocument(GsJsonDocument &&other) noexcept;
    GsJsonDocument &operator=(GsJsonDocument &&other) noexcept;

    bool Save(const GsString &path) const;
    GsString ToString() const;

    GsJsonObject Root();
    const GsJsonObject Root() const;
    void Root(const GsJsonObject &oRoot);
    bool Load(const GsString &path);

private:
    mutable void *m_pRootJsonObject;
};


}// namespace Utility
}// namespace Lite
