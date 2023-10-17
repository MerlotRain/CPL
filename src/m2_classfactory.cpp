#include <m2_object.h>
#include <m2_string.h>
#include <m2_stringlist.h>
#include <map>
#include <mutex>

namespace m2 {

#define DEFAULT_CLASS_CATEGORY "m2"

static std::map<String, std::map<String, ClassFactory::FactoryCreateFun>>
        g_RegisterClasses;

void ClassFactory::registerFactoryCreate(FactoryCreateFun fun,
                                         const char *className,
                                         const char *category)
{
    if (!className || !fun) { return; }

    static std::mutex mutex;
    std::lock_guard<std::mutex> l(mutex);

    if (!category) { category = DEFAULT_CLASS_CATEGORY; }

    auto categoryFind = g_RegisterClasses.find(category);
    if (categoryFind == g_RegisterClasses.end())
    {
        g_RegisterClasses.insert(
                {category, std::map<String, FactoryCreateFun>()});
    }

    auto &classFun = g_RegisterClasses[category];
    auto funFind = classFun.find(className);
    if (funFind == classFun.end()) { classFun.insert({className, fun}); }
}

StringList ClassFactory::classNamesByCategory(const char *category)
{
    if (!category) { category = DEFAULT_CLASS_CATEGORY; }

    StringList classNames;
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

RefObject *ClassFactory::createInstancePrivate(const char *className)
{
    auto it = g_RegisterClasses.begin();
    while (it != g_RegisterClasses.end())
    {
        auto itFind = it->second.find(className);
        if (itFind != it->second.end())
        {
            RefObject *obj = itFind->second();
            return obj;
        }
        ++it;
    }

    return nullptr;
}

}// namespace m2
