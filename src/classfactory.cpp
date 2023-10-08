#include "stringhelp.h"
#include <map>
#include <mutex>
#include <object.h>

namespace m2 {

#define DEFAULT_CLASS_CATEGORY "Lite"

static std::map<GsString, std::map<GsString, GsClassFactory::FactoryCreateFun>> g_RegisterClasses;

void GsClassFactory::RegisterFactoryCreate(FactoryCreateFun fun,
                                           const char *className,
                                           const char *category)
{
    if (!className || !fun)
    {
        return;
    }

    static std::mutex mutex;
    std::lock_guard<std::mutex> l(mutex);

    if (!category)
    {
        category = DEFAULT_CLASS_CATEGORY;
    }

    auto categoryFind = g_RegisterClasses.find(category);
    if (categoryFind == g_RegisterClasses.end())
    {
        g_RegisterClasses.insert(
                {category, std::map<GsString, FactoryCreateFun>()});
    }

    auto &classFun = g_RegisterClasses[category];
    auto funFind = classFun.find(className);
    if (funFind == classFun.end())
    {
        classFun.insert({className, fun});
    }
}

std::vector<std::string>
GsClassFactory::GetClassNamesByCategory(const char *category)
{
    if (!category)
    {
        category = DEFAULT_CLASS_CATEGORY;
    }

    std::vector<std::string> classNames;
    auto it = g_RegisterClasses.find(category);
    if (it != g_RegisterClasses.end())
    {
        for (auto classIt = it->second.begin(); classIt != it->second.end();
             ++classIt)
        {
            classNames.emplace_back(classIt->first);
        }
    }

    return classNames;
}

GsRefObject *GsClassFactory::CreateInstancePrivate(const char *className)
{
    auto it = g_RegisterClasses.begin();
    while (it != g_RegisterClasses.end())
    {
        auto itFind = it->second.find(className);
        if (itFind != it->second.end())
        {
            GsRefObject *obj = itFind->second();
            return obj;
        }
        ++it;
    }

    return nullptr;
}

}// namespace m2
