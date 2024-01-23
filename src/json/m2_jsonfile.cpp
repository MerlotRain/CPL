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


JsonArray::const_iterator::const_iterator(const JsonArray &array, bool bStart)
    : m_Array(array), m_nIndex(bStart ? 0 : array.Size())
{
}

JsonObject &JsonArray::const_iterator::operator*() const
{
    m_Object = m_Array[m_nIndex];
    return m_Object;
}

JsonArray::const_iterator &JsonArray::const_iterator::operator++()
{
    m_nIndex++;
    return *this;
}

bool JsonArray::const_iterator::operator==(const const_iterator &it) const
{
    m_nIndex == it.m_nIndex;
}

bool JsonArray::const_iterator::operator!=(const const_iterator &it) const
{
    m_nIndex != it.m_nIndex;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

JsonArray::JsonArray(const char *name, void *pJsonObject)
    : JsonObject(name, pJsonObject)
{
}


JsonArray::JsonArray()
{
    json_object_put(TO_JSONOBJ(m_pJsonObject));
    m_pJsonObject = json_object_new_array();
}

JsonArray::JsonArray(const char *name)
    : JsonObject(name, json_object_new_array())
{
    json_object_put(TO_JSONOBJ(m_pJsonObject));
}

JsonArray::JsonArray(const JsonObject &other)
    : JsonObject(other)
{
}

int JsonArray::Size() const
{
    if (m_pJsonObject)
        return static_cast<int>(json_object_array_length(TO_JSONOBJ(m_pJsonObject)));
    return 0;
}

void JsonArray::Add(const JsonObject &oValue)
{
    if (m_pJsonObject && oValue.m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject),
                              json_object_get(TO_JSONOBJ(oValue.m_pJsonObject)));
}

void JsonArray::Add(const String &strValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject),
                              json_object_new_string(strValue.c_str()));
}

void JsonArray::Add(const char *pszValue)
{
    if (nullptr == pszValue)
        return;

    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject),
                              json_object_new_string(pszValue));
}

void JsonArray::Add(double dfValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject),
                              json_object_new_double(dfValue));
}

void JsonArray::Add(int nValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject), json_object_new_int(nValue));
}

void JsonArray::Add(long long nValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject), json_object_new_int64(nValue));
}

void JsonArray::Add(bool bValue)
{
    if (m_pJsonObject)
        json_object_array_add(TO_JSONOBJ(m_pJsonObject), json_object_new_boolean(bValue));
}

JsonObject JsonArray::operator[](int nIndex)
{
    return JsonObject(String::Format("id:%d", nIndex).c_str(),
                        json_object_array_get_idx(TO_JSONOBJ(m_pJsonObject), nIndex));
}

const JsonObject JsonArray::operator[](int nIndex) const
{
    return JsonObject(String::Format("id:%d", nIndex).c_str(),
                        json_object_array_get_idx(TO_JSONOBJ(m_pJsonObject), nIndex));
}

JsonArray::const_iterator JsonArray::begin() const
{
    return JsonArray::const_iterator(*this, true);
}

JsonArray::const_iterator JsonArray::end() const
{
    return JsonArray::const_iterator(*this, false);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


JsonObject::JsonObject()
    : m_pJsonObject(json_object_new_object())
{
}

JsonObject::JsonObject(const char *name, const JsonObject &parent)
    : m_pJsonObject(json_object_get(json_object_new_object())), m_strKey(name)
{
    json_object_object_add(TO_JSONOBJ(parent.m_pJsonObject), name, TO_JSONOBJ(m_pJsonObject));
}

JsonObject::~JsonObject()
{
    if (m_pJsonObject)
    {
        json_object_put(TO_JSONOBJ(m_pJsonObject));
        m_pJsonObject = nullptr;
    }
}

JsonObject::JsonObject(const JsonObject &other)
    : m_pJsonObject(json_object_get(TO_JSONOBJ(other.m_pJsonObject))), m_strKey(other.m_strKey)
{
}

JsonObject::JsonObject(JsonObject &&other) noexcept
    : m_pJsonObject(other.m_pJsonObject), m_strKey(std::move(other.m_strKey))
{
    other.m_pJsonObject = nullptr;
}

JsonObject &JsonObject::operator=(const JsonObject &other)
{
    if (this == &other)
        return *this;

    m_strKey = other.m_strKey;
    if (m_pJsonObject)
        json_object_put(TO_JSONOBJ(m_pJsonObject));
    m_pJsonObject = json_object_get(TO_JSONOBJ(other.m_pJsonObject));
    return *this;
}

JsonObject &JsonObject::operator=(JsonObject &&other) noexcept
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

JsonObject JsonObject::Clone() const
{
    JsonObject oRet;
    if (IsValid())
    {
        JsonDocument oTmpDoc;
        oTmpDoc.Root(*this);
        String osStr = oTmpDoc.ToString();
        oTmpDoc.Load(osStr);
        oRet = oTmpDoc.Root();
    }
    return oRet;
}

JsonObject::ObjectType JsonObject::Type() const
{
    if (nullptr == m_pJsonObject)
    {
        if (m_strKey == INVALID_OBJ_KEY)
            return JsonObject::ObjectType::Unknown;
        return JsonObject::ObjectType::Null;
    }
    auto jsonObj(TO_JSONOBJ(m_pJsonObject));
    switch (json_object_get_type(jsonObj))
    {
        case json_type_boolean:
            return JsonObject::ObjectType::Boolean;
        case json_type_double:
            return JsonObject::ObjectType::Double;
        case json_type_int:
            {
                if ((static_cast<long long>(static_cast<int>(json_object_get_int64(jsonObj))) ==
                     json_object_get_int64(jsonObj)))
                    return JsonObject::ObjectType::Integer;
                else
                    return JsonObject::ObjectType::Long;
            }
        case json_type_object:
            return JsonObject::ObjectType::Object;
        case json_type_array:
            return JsonObject::ObjectType::Array;
        case json_type_string:
            return JsonObject::ObjectType::String;
        default:
            break;
    }
    return JsonObject::ObjectType::Unknown;
}

String JsonObject::Name() const
{
    return m_strKey;
}

void JsonObject::Add(const char *name, const String &strValue)
{
    if (nullptr == name)
        return;

    String objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *pVal = json_object_new_string(strValue.c_str());
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), pVal);
    }
}

void JsonObject::Add(const char *name, const char *pszValue)
{
    if (nullptr == name || nullptr == pszValue)
        return;

    String objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_string(pszValue);
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), poVal);
    }
}

void JsonObject::Add(const char *name, double dfValue)
{
    if (nullptr == name)
        return;

    String objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_double(dfValue);
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), poVal);
    }
}

void JsonObject::Add(const char *name, int nValue)
{
    if (nullptr == name)
        return;

    String objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_int(nValue);
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), poVal);
    }
}

void JsonObject::Add(const char *name, long long nValue)
{
    if (nullptr == name)
        return;

    String objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_int64(static_cast<int64_t>(nValue));
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(), poVal);
    }
}

void JsonObject::Add(const char *name, const JsonArray &objValue)
{
    if (nullptr == name)
        return;

    String objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(),
                               json_object_get(TO_JSONOBJ(objValue.m_pJsonObject)));
    }
}

void JsonObject::Add(const char *name, const JsonObject &objValue)
{
    String objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();

    if (nullptr == name)
    {
        json_object_object_add(TO_JSONOBJ(m_pJsonObject), "",
                               json_object_get(TO_JSONOBJ(objValue.m_pJsonObject)));
        return;
    }

    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) == json_type_object)
    {
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject), objectName.c_str(),
                               json_object_get(TO_JSONOBJ(objValue.m_pJsonObject)));
    }
}

void JsonObject::AddNoSplitName(const char *name, const JsonObject &objValue)
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

void JsonObject::Add(const char *name, bool bValue)
{
    if (nullptr == name)
        return;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    String objectName;
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(
                                    object.m_pJsonObject)) == json_type_object)
    {
        json_object *poVal = json_object_new_boolean(bValue);
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject),
                               objectName.c_str(), poVal);
    }
}

void JsonObject::AddNull(const char *name)
{
    if (nullptr == name)
        return;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    String objectName;
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid() && json_object_get_type(TO_JSONOBJ(
                                    object.m_pJsonObject)) == json_type_object)
    {
        json_object_object_add(TO_JSONOBJ(object.m_pJsonObject),
                               objectName.c_str(), nullptr);
    }
}

void JsonObject::Set(const char *name, const String &osValue)
{
    Delete(name);
    Add(name, osValue);
}

void JsonObject::Set(const char *name, const char *pszValue)
{
    if (nullptr == pszValue)
        return;
    Delete(name);
    Add(name, pszValue);
}

void JsonObject::Set(const char *name, double dfValue)
{
    Delete(name);
    Add(name, dfValue);
}

void JsonObject::Set(const char *name, int nValue)
{
    Delete(name);
    Add(name, nValue);
}

void JsonObject::Set(const char *name, long long nValue)
{
    Delete(name);
    Add(name, nValue);
}

void JsonObject::Set(const char *name, bool bValue)
{
    Delete(name);
    Add(name, bValue);
}

void JsonObject::SetNull(const char *name)
{
    Delete(name);
    AddNull(name);
}

String JsonObject::AsString(const char *name, const String &defValue) const
{
    JsonObject object = AsObject(name);
    return object.ToString(defValue);
}

double JsonObject::AsDouble(const char *name, double defValue) const
{
    JsonObject object = AsObject(name);
    return object.ToDouble(defValue);
}

int JsonObject::AsInteger(const char *name, int defValue) const
{
    JsonObject object = AsObject(name);
    return object.ToInteger(defValue);
}

long long JsonObject::AsLongLong(const char *name, long long defValue) const
{
    JsonObject object = AsObject(name);
    return object.ToLongLong(defValue);
}

JsonArray JsonObject::AsArray(const char *name) const
{
    if (nullptr == name)
        return;
    String objectName;
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid())
    {
        json_object *poVal = nullptr;
        if (json_object_object_get_ex(TO_JSONOBJ(object.m_pJsonObject),
                                      objectName.c_str(), &poVal))
        {
            if (poVal && json_object_get_type(poVal) == json_type_array)
            {
                return JsonArray(objectName.c_str(), poVal);
            }
        }
    }
    return JsonArray(INVALID_OBJ_KEY, nullptr);
}

JsonObject JsonObject::AsObject(const char *name) const
{
    if (nullptr == name)
        return;
    String objectName;
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid())
    {
        json_object *poVal = nullptr;
        if (json_object_object_get_ex(TO_JSONOBJ(object.m_pJsonObject),
                                      objectName.c_str(), &poVal))
        {
            return JsonObject(objectName, poVal);
        }
    }
    return JsonObject(INVALID_OBJ_KEY, nullptr);
}

bool JsonObject::AsBoolean(const char *name, bool defValue) const
{
    JsonObject object = AsObject(name);
    return object.ToBoolean(defValue);
}

String JsonObject::ToString(const String &defValue) const
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

double JsonObject::ToDouble(double defValue) const
{
    if (m_pJsonObject)
        return json_object_get_double(TO_JSONOBJ(m_pJsonObject));
    return defValue;
}

int JsonObject::ToInteger(int defValue) const
{
    if (m_pJsonObject)
        return json_object_get_int(TO_JSONOBJ(m_pJsonObject));
    return defValue;
}

long long JsonObject::ToLongLong(long long defValue) const
{
    if (m_pJsonObject)
        return json_object_get_int64(TO_JSONOBJ(m_pJsonObject));
    return defValue;
}

bool JsonObject::ToBoolean(bool defValue) const
{
    if (m_pJsonObject)
        return json_object_get_boolean(TO_JSONOBJ(m_pJsonObject));
    return defValue;
}

JsonArray JsonObject::ToArray() const
{
    if (m_pJsonObject &&
        json_object_get_type(TO_JSONOBJ(m_pJsonObject)) == json_type_array)
        return JsonArray("", TO_JSONOBJ(m_pJsonObject));
    return JsonArray(INVALID_OBJ_KEY, nullptr);
}

String JsonObject::Format(PrettyFormat eFormat) const
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

void JsonObject::Delete(const char *name)
{
    String objectName;
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    JsonObject object = GetObjectByPath(name, objectName);
    if (object.IsValid())
    {
        json_object_object_del(TO_JSONOBJ(object.m_pJsonObject),
                               objectName.c_str());
    }
}

void JsonObject::DeleteNoSplitName(const char *name)
{
    if (m_strKey == INVALID_OBJ_KEY)
        m_strKey.clear();
    if (m_pJsonObject)
    {
        json_object_object_del(TO_JSONOBJ(m_pJsonObject), name);
    }
}

JsonObject JsonObject::operator[](const char *name) const
{
    return AsObject(name);
}

std::vector<JsonObject> JsonObject::Children() const
{
    std::vector<JsonObject> children;
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
        children.push_back(JsonObject(it.key, it.val));
    }

    return children;
}

bool JsonObject::IsValid() const
{
    return m_strKey != INVALID_OBJ_KEY;
}

void JsonObject::Deinit()
{
    if (m_pJsonObject)
    {
        json_object_put(TO_JSONOBJ(m_pJsonObject));
        m_pJsonObject = nullptr;
    }
    m_strKey = INVALID_OBJ_KEY;
}

JsonObject::JsonObject(const char *name, void *pJsonObject)
    : m_pJsonObject(json_object_get(TO_JSONOBJ(pJsonObject))), m_strKey(name)
{
}


static StringList Tokenize(const char *pszString, const char *pszDelimiters,
                             int nCSLTFlags)
{
    if (pszString == nullptr)
        return static_cast<char **>(calloc(sizeof(char *), 1));

    StringList oRetList;
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

JsonObject JsonObject::GetObjectByPath(const String &path, String &name) const
{
    json_object *poVal = nullptr;

    if (json_object_object_get_ex(TO_JSONOBJ(m_pJsonObject),
                                  path.c_str(), &poVal))
    {
        name = path;
        return *this;
    }

    StringList pathPortions = Tokenize(path.c_str(), JSON_PATH_DELIMITER, 0);
    int portionsCount = pathPortions.size();
    if (portionsCount > 100)
    {
        return JsonObject(INVALID_OBJ_KEY, nullptr);
    }
    if (0 == portionsCount)
        return JsonObject(INVALID_OBJ_KEY, nullptr);
    JsonObject object = *this;
    for (int i = 0; i < portionsCount - 1; ++i)
    {
        if (json_object_object_get_ex(TO_JSONOBJ(object.m_pJsonObject),
                                      pathPortions[i], &poVal))
        {
            object = JsonObject(pathPortions[i], poVal);
        }
        else
        {
            if (json_object_get_type(TO_JSONOBJ(object.m_pJsonObject)) !=
                json_type_object)
            {
                return JsonObject(INVALID_OBJ_KEY, nullptr);
            }
            object = JsonObject(pathPortions[i], object);
        }
    }

    name = pathPortions[portionsCount - 1];
    return object;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

JsonDocument::JsonDocument()
    : m_pRootJsonObject(nullptr)
{
}

JsonDocument::~JsonDocument()
{
    if (m_pRootJsonObject)
        json_object_put(TO_JSONOBJ(m_pRootJsonObject));
}

JsonDocument::JsonDocument(const JsonDocument &other)
    : m_pRootJsonObject(json_object_get(TO_JSONOBJ(other.m_pRootJsonObject)))
{
}

JsonDocument &JsonDocument::operator=(const JsonDocument &other)
{
    if (this == &other)
        return *this;

    if (m_pRootJsonObject)
        json_object_put(TO_JSONOBJ(m_pRootJsonObject));
    m_pRootJsonObject = json_object_get(TO_JSONOBJ(other.m_pRootJsonObject));

    return *this;
}

JsonDocument::JsonDocument(JsonDocument &&other) noexcept
    : m_pRootJsonObject(other.m_pRootJsonObject)
{
    other.m_pRootJsonObject = nullptr;
}

JsonDocument &JsonDocument::operator=(JsonDocument &&other) noexcept
{
    if (this == &other)
        return *this;

    if (m_pRootJsonObject)
        json_object_put(TO_JSONOBJ(m_pRootJsonObject));
    m_pRootJsonObject = other.m_pRootJsonObject;
    other.m_pRootJsonObject = nullptr;

    return *this;
}

bool JsonDocument::Save(const String &path) const
{
    FILE *fp = fopen(path.c_str(), "wt");
    if (nullptr == fp)
    {
        GS_E << String::Format("Open file %s to write failed", path.c_str()).c_str();
        return false;
    }

    const char *pabyData = json_object_to_json_string_ext(
            TO_JSONOBJ(m_pRootJsonObject), JSON_C_TO_STRING_PRETTY);

    return true;
}

String JsonDocument::ToString() const
{
    return json_object_to_json_string_ext(TO_JSONOBJ(m_pRootJsonObject),
                                          JSON_C_TO_STRING_PRETTY);
}

JsonObject JsonDocument::Root()
{
    return const_cast<JsonDocument *>(this)->Root();
}

const JsonObject JsonDocument::Root() const
{
    if (nullptr == m_pRootJsonObject)
    {
        m_pRootJsonObject = json_object_new_object();
    }

    if (json_object_get_type(TO_JSONOBJ(m_pRootJsonObject)) == json_type_array)
    {
        return JsonArray("", m_pRootJsonObject);
    }
    else
    {
        return JsonObject("", m_pRootJsonObject);
    }
}

void JsonDocument::Root(const JsonObject &pRoot)
{
    if (m_pRootJsonObject)
        json_object_put(TO_JSONOBJ(m_pRootJsonObject));
    m_pRootJsonObject = json_object_get(TO_JSONOBJ(pRoot.m_pJsonObject));
}

bool JsonDocument::Load(const String &path)
{
    return false;
}


}// namespace m2
