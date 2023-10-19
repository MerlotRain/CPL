#include <m2_stringlist.h>

namespace m2 {

StringList::StringList() noexcept {}

StringList::StringList(const String &str) noexcept { emplace_back(str); }

StringList::StringList(const std::list<String> &l) noexcept
    : std::list<String>(l)
{
}

StringList::StringList(std::list<String> &&l) noexcept : std::list<String>(l) {}

StringList::StringList(std::initializer_list<String> args) noexcept
    : std::list<String>(args)
{
}

StringList &StringList::operator=(const std::list<String> &rhs)
{
    std::list<String>::operator=(rhs);
    return *this;
}

StringList &StringList::operator=(std::list<String> &&rhs) noexcept
{
    std::list<String>::operator=(rhs);
    return *this;
}

bool StringList::contains(const String &str)
{
    for (auto it = this->cbegin(); it != this->cend(); ++it)
    {
        if (it->compare(str.c_str()) == 0) { return true; }
    }
    return false;
}

String StringList::operator[](size_t i)
{
    if (i >= size()) throw std::out_of_range("out off stringlist max size");
    std::list<String>::iterator it = this->begin();
    std::advance(it, i);
    return *it;
}

const String &StringList::operator[](size_t i) const
{
    if (i >= size()) throw std::out_of_range("out off stringlist max size");
    std::list<String>::const_iterator it = this->cbegin();
    std::advance(it, i);
    return *it;
}

}// namespace m2
