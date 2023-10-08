#include "jsonfile.h"
#include "jsonheader.h"
#include <logger.h>
#include <stringtokenizer.h>

namespace m2 {

#define TO_JSONOBJ(x) static_cast<json_object *>(x)

static const char *JSON_PATH_DELIMITER = "/";

static const char *INVALID_OBJ_KEY = "__INVALID_OBJ_KEY__";

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


GsJsonArray::const_iterator::const_iterator(const GsJsonArray &array, bool bStart)
    : m_Array(array), m_nIndex(bStart ? 0 : array.Size())
{
}

GsJsonObject &GsJsonArray::const_iterator::operator*() const
{
    m_Object = m_Array[m_nIndex];
    return m_Object;
}

GsJsonArray::const_iterator &GsJsonArray::const_iterator::operator++()
{
    m_nIndex++;
    return *this;
}

bool GsJsonArray::const_iterator::operator==(const const_iterator &it) const
{
    m_nIndex == it.m_nIndex;
}

bool GsJsonArray::const_iterator::operator!=(const const_iterator &it) const
{
    m_nIndex != it.m_nIndex;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

GsJsonArray::GsJsonArray(const char *name, void *pJsonObject)
    : GsJsonObject(name, pJsonObject)
{
}


GsJsonArray::GsJsonArray()
{
    json_object_put(TO_JSONOBJ(m_pJsonObject));
    m_pJsonObject = json_object_new_array();
}

GsJsonArray::GsJsonArray(const char *name)
    : GsJsonObject(name, json_object_new_array())
{
    json_object_put(TO_JSONOBJ(m_pJsonObject));
}

GsJsonArray::GsJsonArray(const GsJsonObject &other)
    : GsJsonObject(other)
{
}

int GsJsonArray::Size() const
{
    if (m_pJsonObject)
        return static_cast<int>(json_object_array_length(TO_JSONOBJ(m_pJsonObject)));
    return 0;
}

void GsJsonArray::Add(const GsJsonObject &oValue)
{
    if (m_pJsonObject && oValue.m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject),
                              json_object_get(TO_JSONOBJ(oValue.m_pJsonObject)));
}

void GsJsonArray::Add(const GsString &strValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject),
                              json_object_new_string(strValue.c_str()));
}

void GsJsonArray::Add(const char *pszValue)
{
    if (nullptr == pszValue)
        return;

    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject),
                              json_object_new_string(pszValue));
}

void GsJsonArray::Add(double dfValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject),
                              json_object_new_double(dfValue));
}

void GsJsonArray::Add(int nValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject), json_object_new_int(nValue));
}

void GsJsonArray::Add(long long nValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject), json_object_new_int64(nValue));
}

void GsJsonArray::Add(bool bValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject), json_object_new_boolean(bValue));
}

GsJsonObject GsJsonArray::operator[](int nIndex)
{
    return GsJsonObject(GsString::Format("id:%d", nIndex).c_str(),
                        json_object_array_get_idx(TO_JSONOBJ(m_pJsonObject), nIndex));
}

const GsJsonObject GsJsonArray::operator[](int nIndex) const
{
    return GsJsonObject(GsString::Format("id:%d", nIndex).c_str(),
                        json_object_array_get_idx(TO_JSONOBJ(m_pJsonObject), nIndex));
}

GsJsonArray::const_iterator GsJsonArray::begin() const
{
    return GsJsonArray::const_iterator(*this, true);
}

GsJsonArray::const_iterator GsJsonArray::end() const
{
    return GsJsonArray::const_iterator(*this, false);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


GsJsonObject::GsJsonObject()
    : m_pJsonObject(json_object_new_object())
{
}

GsJsonObject::GsJsonObject(const char *name, const GsJsonObject &parent)
    : m_pJsonObject(json_object_get(json_object_new_object())), m_strKey(name)
{
    json_object_object_add(TO_JSONOBJ(parent.m_pJsonObject), name, TO_JSONOBJ(m_pJsonObject));
}

GsJsonObject::~GsJsonObject()
{
    if (m_pJsonObject)
    {
        json_object_put(TO_JSONOBJ(m_pJsonObject));
        m_pJsonObject = nullptr;
    }
}

GsJsonObject::GsJsonObject(const GsJsonObject &other)
    : m_pJsonObject(json_object_get(TO_JSONOBJ(other.m_pJsonObject))), m_strKey(other.m_strKey)
{
}

GsJsonObject::GsJsonObject(GsJsonObject &&other) noexcept
    : m_pJsonObject(other.m_pJsonObject), m_strKey(std::move(other.m_strKey))
{
    other.m_pJsonObject = nullptr;
}

GsJsonObject &GsJsonObject::operator=(const GsJsonObject &other)
{
    if (this == &other)
        return *this;

    m_strKey = other.m_strKey;
    if (m_pJsonObject)
        json_object_put(TO_JSONOBJ(m_pJsonObject));
    m_pJsonObject = json_object_get(TO_JSONOBJ(other.m_pJsonObject));
    return *this;
}

GsJsonObject &GsJsonObject::operator=(GsJsonObject &&other) noexcept
{
    if (this == &other)
        return *this;

    m_strKey = std::move(other.m_strKey);
    if (m_pJsonObject)
        json_object_put(TO_JSONOBJ(m_pJsonObject));
    m_pJsonObject = other.m_pJsonObject;
    other.m_pJsonObject = nullptr;
    return *this;
}

GsJsonObject GsJsonObject::Clone() const
{
    GsJsonObject oRet;
    if (IsValid())
    {
        GsJsonDocument oTmpDoc;
        oTmpDoc.Root(*this);
        GsString osStr = oTmpDoc.ToString();
        oTmpDoc.Load(osStr);
        oRet = oTmpDoc.Root();
    }
    return oRet;
}

GsJsonObject::ObjectType GsJsonObject::Type() const
{
    if (nullptr == m_pJsonObject)
    {
        if (m_strKey == INVALID_OBJ_KEY)
            return GsJsonObject::ObjectType::Unknown;
        return GsJsonObject::ObjectType::Null;
    }
    auto jsonObj(TO_JSONOBJ(m_pJsonObject));
    switch (json_object_get_type(jsonObj))
    {
        case json_type_boolean:
            return GsJsonObject::ObjectType::Boolean;
        case json_type_double:
            return GsJsonObject::ObjectType::Double;
        case json_type_int:
            {
                if ((static_cast<long long>(static_cast<int>(json_object_get_int64(jsonObj))) ==
                     json_object_get_int64(jsonObj)))
                    return GsJsonObject::ObjectType::Integer;
                else
                    return GsJsonObject::ObjectType::Long;
            }
        case json_type_object:
            return GsJsonObject::ObjectType::Object;
        case json_type_array:
            return GsJsonObject::ObjectType::Array;
        case json_type_string:
            return GsJsonObject::ObjectType::String;
        default:
            break;
    }
    return GsJsonObject::ObjectType::Unknown;
}

GsString GsJsonObject::Name() const
{
    return m_strKey;
}

void GsJsonObject::Add(const char *name, const GsString &strValue)
{
    if (nullptr == name)
        return;

    GsString objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *pVal = json_object_new_string(strValue.c_str());
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), pVal);
    }
}

void GsJsonObject::Add(const char *name, const char *pszValue)
{
    if (nullptr == name || nullptr == pszValue)
        return;

    GsString objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_string(pszValue);
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), poVal);
    }
}

void GsJsonObject::Add(const char *name, double dfValue)
{
    if (nullptr == name)
        return;

    GsString objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_double(dfValue);
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), poVal);
    }
}

void GsJsonObject::Add(const char *name, int nValue)
{
    if (nullptr == name)
        return;

    GsString objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_int(nValue);
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), poVal);
    }
}

void GsJsonObject::Add(const char *name, long long nValue)
{
    if (nullptr == name)
        return;

    GsString objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_int64(static_cast<int64_t>(nValue));
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), poVal);
    }
}

void GsJsonObject::Add(const char *name, const GsJsonArray &objValue)
{
    if (nullptr == name)
        return;

    GsString objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(),
                               json_object_get(TO_JSONOBJ(objValue.m_pJsonObject)));
    }
}

void GsJsonObject::Add(const char *name, const GsJsonObject &objValue)
{
    GsString objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();

    if (nullptr == name)
    {
        json_object_object_add(TO_JSONOBJ(m_pJsonObject), "",
                               json_object_get(TO_JSONOBJ(objValue.m_pJsonObject)));
        return;
    }

    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(),
                               json_object_get(TO_JSONOBJ(objValue.m_pJsonObject)));
    }
}

void GsJsonObject::AddNoSplitName(const char *name, const GsJsonObject &objValue)
{
    if (nullptr == name)
        return;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();

    if (IsValid() && json_object_get_type(TO_JSONOBJ(m_pJsonObject)) == json_type_object)
    {
        json_object_object_add(TO_JSONOBJ(m_pJsonObject), name,
                               json_object_get(TO_JSONOBJ(objValue.m_pJsonObject)));
    }
}

void GsJsonObject::Add(const char *name, bool bValue)
{
    if (nullptr == name)
        return;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    GsString objectName;
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(
                                    object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_boolean(bValue);
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject),
                               objectName.c_str(), poVal);
    }
}

void GsJsonObject::AddNull(const char *name)
{
    if (nullptr == name)
        return;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    GsString objectName;
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(
                                    object.m_pJsonObject)) == json_type_object)
    {
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject),
                               objectName.c_str(), nullptr);
    }
}

void GsJsonObject::Set(const char *name, const GsString &osValue)
{
    Delete(name);
    Add(name, osValue);
}

void GsJsonObject::Set(const char *name, const char *pszValue)
{
    if (nullptr == pszValue)
        return;
    Delete(name);
    Add(name, pszValue);
}

void GsJsonObject::Set(const char *name, double dfValue)
{
    Delete(name);
    Add(name, dfValue);
}

void GsJsonObject::Set(const char *name, int nValue)
{
    Delete(name);
    Add(name, nValue);
}

void GsJsonObject::Set(const char *name, long long nValue)
{
    Delete(name);
    Add(name, nValue);
}

void GsJsonObject::Set(const char *name, bool bValue)
{
    Delete(name);
    Add(name, bValue);
}

void GsJsonObject::SetNull(const char *name)
{
    Delete(name);
    AddNull(name);
}

GsString GsJsonObject::AsString(const char *name, const GsString &defValue) const
{
    GsJsonObject object = AsObject(name);
    return object.ToString(defValue);
}

double GsJsonObject::AsDouble(const char *name, double defValue) const
{
    GsJsonObject object = AsObject(name);
    return object.ToDouble(defValue);
}

int GsJsonObject::AsInteger(const char *name, int defValue) const
{
    GsJsonObject object = AsObject(name);
    return object.ToInteger(defValue);
}

long long GsJsonObject::AsLongLong(const char *name, long long defValue) const
{
    GsJsonObject object = AsObject(name);
    return object.ToLongLong(defValue);
}

GsJsonArray GsJsonObject::AsArray(const char *name) const
{
    if (nullptr == name)
        return;
    GsString objectName;
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid())
    {
        json_object *poVal = nullptr;
        if (json_object_object_get_ex(TO_JSONOBJ(object.m_pJsonObject),
                                      objectName.c_str(), &poVal))
        {
            if (poVal && json_object_get_type(poVal) == json_type_array)
            {
                return GsJsonArray(objectName.c_str(), poVal);
            }
        }
    }
    return GsJsonArray(INVALID_OBJ_KEY, nullptr);
}

GsJsonObject GsJsonObject::AsObject(const char *name) const
{
    if (nullptr == name)
        return;
    GsString objectName;
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid())
    {
        json_object *poVal = nullptr;
        if (json_object_object_get_ex(TO_JSONOBJ(object.m_pJsonObject),
                                      objectName.c_str(), &poVal))
        {
            return GsJsonObject(objectName, poVal);
        }
    }
    return GsJsonObject(INVALID_OBJ_KEY, nullptr);
}

bool GsJsonObject::AsBoolean(const char *name, bool defValue) const
{
    GsJsonObject object = AsObject(name);
    return object.ToBoolean(defValue);
}

GsString GsJsonObject::ToString(const GsString &defValue) const
{
    if (m_pJsonObject)
    {
        const char *pszString = json_object_get_string(TO_JSONOBJ(m_pJsonObject));
        if (!pszString)
        {
            return pszString;
        }
    }
    return defValue;
}

double GsJsonObject::ToDouble(double defValue) const
{
    if (m_pJsonObject)
        return json_object_get_double(TO_JSONOBJ(m_pJsonObject));
    return defValue;
}

int GsJsonObject::ToInteger(int defValue) const
{
    if (m_pJsonObject)
        return json_object_get_int(TO_JSONOBJ(m_pJsonObject));
    return defValue;
}

long long GsJsonObject::ToLongLong(long long defValue) const
{
    if (m_pJsonObject)
        return json_object_get_int64(TO_JSONOBJ(m_pJsonObject));
    return defValue;
}

bool GsJsonObject::ToBoolean(bool defValue) const
{
    if (m_pJsonObject)
        return json_object_get_boolean(TO_JSONOBJ(m_pJsonObject));
    return defValue;
}

GsJsonArray GsJsonObject::ToArray() const
{
    if (m_pJsonObject &&
        json_object_get_type(TO_JSONOBJ(m_pJsonObject)) == json_type_array)
        return GsJsonArray("", TO_JSONOBJ(m_pJsonObject));
    return GsJsonArray(INVALID_OBJ_KEY, nullptr);
}

GsString GsJsonObject::Format(PrettyFormat eFormat) const
{
    if (m_pJsonObject)
    {
        const char *pszFormatString = nullptr;
        switch (eFormat)
        {
            case PrettyFormat::Spaced:
                pszFormatString = json_object_to_json_string_ext(
                        TO_JSONOBJ(m_pJsonObject), JSON_C_TO_STRING_SPACED);
                break;
            case PrettyFormat::Pretty:
                pszFormatString = json_object_to_json_string_ext(
                        TO_JSONOBJ(m_pJsonObject), JSON_C_TO_STRING_PRETTY);
                break;
            default:
                pszFormatString = json_object_to_json_string_ext(
                        TO_JSONOBJ(m_pJsonObject), JSON_C_TO_STRING_PLAIN);
        }
        if (nullptr != pszFormatString)
        {
            return pszFormatString;
        }
    }
    return "";
}

void GsJsonObject::Delete(const char *name)
{
    GsString objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    GsJsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid())
    {
        json_object_object_del(TO_JSONOBJ(object.m_pJsonObject),
                               objectName.c_str());
    }
}

void GsJsonObject::DeleteNoSplitName(const char *name)
{
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    if (m_pJsonObject)
    {
        json_object_object_del(TO_JSONOBJ(m_pJsonObject), name);
    }
}

GsJsonObject GsJsonObject::operator[](const char *name) const
{
    return AsObject(name);
}

std::vector<GsJsonObject> GsJsonObject::Children() const
{
    std::vector<GsJsonObject> children;
    if (nullptr == m_pJsonObject ||
        json_object_get_type(TO_JSONOBJ(m_pJsonObject)) != json_type_object)
    {
        return children;
    }

    json_object_iter it;
    it.key = nullptr;
    it.val = nullptr;
    it.entry = nullptr;
    json_object_object_foreachC(TO_JSONOBJ(m_pJsonObject), it)
    {
        children.push_back(GsJsonObject(it.key, it.val));
    }

    return children;
}

bool GsJsonObject::IsValid() const
{
    return m_strKey != INVALID_OBJ_KEY;
}

void GsJsonObject::Deinit()
{
    if (m_pJsonObject)
    {
        json_object_put(TO_JSONOBJ(m_pJsonObject));
        m_pJsonObject = nullptr;
    }
    m_strKey = INVALID_OBJ_KEY;
}

GsJsonObject::GsJsonObject(const char *name, void *pJsonObject)
    : m_pJsonObject(json_object_get(TO_JSONOBJ(pJsonObject))), m_strKey(name)
{
}


static GsStringList Tokenize(const char *pszString, const char *pszDelimiters,
                             int nCSLTFlags)
{
    if (pszString == nullptr)
        return static_cast<char **>(calloc(sizeof(char *), 1));

    GsStringList oRetList;
    const bool bHonourStrings = (nCSLTFlags & 0x0001) != 0;
    const bool bAllowEmptyTokens = (nCSLTFlags & 0x0002) != 0;
    const bool bStripLeadSpaces = (nCSLTFlags & 0x0010) != 0;
    const bool bStripEndSpaces = (nCSLTFlags & 0x0020) != 0;

    char *pszToken = static_cast<char *>(calloc(10, 1));
    size_t nTokenMax = 10;

    while (*pszString != '\0')
    {
        bool bInString = false;
        bool bStartString = true;
        size_t nTokenLen = 0;
        for (; *pszString != '\0'; ++pszString)
        {
            if (nTokenLen >= nTokenMax - 3)
            {
                if (nTokenMax > std::numeric_limits<size_t>::max() / 2)
                {
                    free(pszToken);
                    return static_cast<char **>(calloc(sizeof(char *), 1));
                }
                nTokenMax = nTokenMax * 2;
                char *pszNewToken = static_cast<char *>(realloc(pszToken, nTokenMax));
                if (pszNewToken == nullptr)
                {
                    free(pszToken);
                    return static_cast<char **>(calloc(sizeof(char *), 1));
                }
                pszToken = pszNewToken;
            }

            if (!bInString && strchr(pszDelimiters, *pszString) != nullptr)
            {
                ++pszString;
                break;
            }
            if (bHonourStrings && *pszString == '"')
            {
                if (nCSLTFlags & 0x0004)
                {
                    pszToken[nTokenLen] = *pszString;
                    ++nTokenLen;
                }

                bInString = !bInString;
                continue;
            }
            if (bInString && pszString[0] == '\\')
            {
                if (pszString[1] == '"' || pszString[1] == '\\')
                {
                    if (nCSLTFlags & 0x0008)
                    {
                        pszToken[nTokenLen] = *pszString;
                        ++nTokenLen;
                    }
                    ++pszString;
                }
            }

            if (!bInString && bStripLeadSpaces && bStartString &&
                isspace(static_cast<unsigned char>(*pszString)))
                continue;

            bStartString = false;

            pszToken[nTokenLen] = *pszString;
            ++nTokenLen;
        }

        if (!bInString && bStripEndSpaces)
        {
            while (nTokenLen &&
                   isspace(static_cast<unsigned char>(pszToken[nTokenLen - 1])))
                nTokenLen--;
        }

        pszToken[nTokenLen] = '\0';

        // Add the token.
        if (pszToken[0] != '\0' || bAllowEmptyTokens)
            oRetList.push_back(pszToken);
    }

    if (*pszString == '\0' && bAllowEmptyTokens && oRetList.size() > 0 &&
        strchr(pszDelimiters, *(pszString - 1)) != nullptr)
    {
        oRetList.push_back("");
    }

    free(pszToken);
    return oRetList;
}

GsJsonObject GsJsonObject::GetObjectByPath(const GsString &path, GsString &name) const
{
    json_object *poVal = nullptr;

    if (json_object_object_get_ex(TO_JSONOBJ(m_pJsonObject),
                                  path.c_str(), &poVal))
    {
        name = path;
        return *this;
    }

    GsStringList pathPortions = Tokenize(path.c_str(), JSON_PATH_DELIMITER, 0);
    int portionsCount = pathPortions.size();
    if (portionsCount > 100)
    {
        return GsJsonObject(INVALID_OBJ_KEY, nullptr);
    }
    if (0 == portionsCount)
        return GsJsonObject(INVALID_OBJ_KEY, nullptr);
    GsJsonObject object = *this;
    for (int i = 0; i < portionsCount - 1; ++i)
    {
        if (json_object_object_get_ex(TO_JSONOBJ(object.m_pJsonObject),
                                      pathPortions[i], &poVal))
        {
            object = GsJsonObject(pathPortions[i], poVal);
        }
        else
        {
            if (json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) !=
                json_type_object)
            {
                return GsJsonObject(INVALID_OBJ_KEY, nullptr);
            }
            object = GsJsonObject(pathPortions[i], object);
        }
    }

    name = pathPortions[portionsCount - 1];
    return object;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

GsJsonDocument::GsJsonDocument()
    : m_pRootJsonObject(nullptr)
{
}

GsJsonDocument::~GsJsonDocument()
{
    if (m_pRootJsonObject)
        json_object_put(TO_JSONOBJ(m_pRootJsonObject));
}

GsJsonDocument::GsJsonDocument(const GsJsonDocument &other)
    : m_pRootJsonObject(json_object_get(TO_JSONOBJ(other.m_pRootJsonObject)))
{
}

GsJsonDocument &GsJsonDocument::operator=(const GsJsonDocument &other)
{
    if (this == &other)
        return *this;

    if (m_pRootJsonObject)
        json_object_put(TO_JSONOBJ(m_pRootJsonObject));
    m_pRootJsonObject = json_object_get(TO_JSONOBJ(other.m_pRootJsonObject));

    return *this;
}

GsJsonDocument::GsJsonDocument(GsJsonDocument &&other) noexcept
    : m_pRootJsonObject(other.m_pRootJsonObject)
{
    other.m_pRootJsonObject = nullptr;
}

GsJsonDocument &GsJsonDocument::operator=(GsJsonDocument &&other) noexcept
{
    if (this == &other)
        return *this;

    if (m_pRootJsonObject)
        json_object_put(TO_JSONOBJ(m_pRootJsonObject));
    m_pRootJsonObject = other.m_pRootJsonObject;
    other.m_pRootJsonObject = nullptr;

    return *this;
}

bool GsJsonDocument::Save(const GsString &path) const
{
    FILE *fp = fopen(path.c_str(), "wt");
    if (nullptr == fp)
    {
        GS_E << GsString::Format("Open file %s to write failed", path.c_str()).c_str();
        return false;
    }

    const char *pabyData = json_object_to_json_string_ext(
            TO_JSONOBJ(m_pRootJsonObject), JSON_C_TO_STRING_PRETTY);

    return true;
}

GsString GsJsonDocument::ToString() const
{
    return json_object_to_json_string_ext(TO_JSONOBJ(m_pRootJsonObject),
                                          JSON_C_TO_STRING_PRETTY);
}

GsJsonObject GsJsonDocument::Root()
{
    return const_cast<GsJsonDocument *>(this)->Root();
}

const GsJsonObject GsJsonDocument::Root() const
{
    if (nullptr == m_pRootJsonObject)
    {
        m_pRootJsonObject = json_object_new_object();
    }

    if (json_object_get_type(TO_JSONOBJ(m_pRootJsonObject)) == json_type_array)
    {
        return GsJsonArray("", m_pRootJsonObject);
    }
    else
    {
        return GsJsonObject("", m_pRootJsonObject);
    }
}

void GsJsonDocument::Root(const GsJsonObject &pRoot)
{
    if (m_pRootJsonObject)
        json_object_put(TO_JSONOBJ(m_pRootJsonObject));
    m_pRootJsonObject = json_object_get(TO_JSONOBJ(pRoot.m_pJsonObject));
}

bool GsJsonDocument::Load(const GsString &path)
{
    return false;
}


}// namespace m2
