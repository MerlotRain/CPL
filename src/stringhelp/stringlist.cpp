#include <stringhelp.h>

namespace m2 {

GsStringList::GsStringList() noexcept
{
}

GsStringList::GsStringList(const GsString &str) noexcept
{
    emplace_back(str);
}

GsStringList::GsStringList(const std::list<GsString> &l) noexcept : std::list<GsString>(l)
{
}

GsStringList::GsStringList(std::list<GsString> &&l) noexcept : std::list<GsString>(l)
{
}

GsStringList::GsStringList(std::initializer_list<GsString> args) noexcept : std::list<GsString>(args)
{
}

GsStringList &GsStringList::operator=(const std::list<GsString> &rhs)
{
    std::list<GsString>::operator=(rhs);
    return *this;
}

GsStringList &GsStringList::operator=(std::list<GsString> &&rhs) noexcept
{
    std::list<GsString>::operator=(rhs);
    return *this;
}

bool GsStringList::Contains(const GsString &str)
{
    for (auto it = this->cbegin(); it != this->cend(); ++it)
    {
        if (it->compare(str.c_str()) == 0)
        {
            return true;
        }
    }
    return false;
}

GsString GsStringList::operator[](size_t i)
{
    if (i >= size())
        throw std::out_of_range("out off stringlist max size");
    std::list<GsString>::iterator it = this->begin();
    std::advance(it, i);
    return *it;
}

const GsString &GsStringList::operator[](size_t i) const
{
    if (i >= size())
        throw std::out_of_range("out off stringlist max size");
    std::list<GsString>::const_iterator it = this->cbegin();
    std::advance(it, i);
    return *it;
}

}// namespace m2
