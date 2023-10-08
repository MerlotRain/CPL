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

#pragma once

#include <preconfig.h>

namespace m2 {

class M2_API ByteAllocator
{
public:
    static void *Allocate(size_t size);
    static void Deallocate(void *p, size_t n);
};


template<typename T>
class Allocator : public ByteAllocator
{
public:
    Allocator()
    {
    }
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    pointer allocate(size_type n)
    {
        return static_cast<pointer>(Allocate(n * sizeof(T)));
    }

    void deallocate(pointer p, size_type n)
    {
        Deallocate(p, n * sizeof(T));
    }


    size_type max_size() const
    {
        return size_t(-1) / sizeof(T);
    }

    pointer address(reference x) const
    {
        return std::addressof(x);
    }

    const_pointer address(const_reference x) const
    {
        return std::addressof(x);
    }

    template<typename... Args>
    void construct(pointer p, Args &&...args)
    {
        ::new (static_cast<void *>(p)) T(std::forward<Args>(args)...);
    }
    void destroy(pointer p)
    {
        p->~T();
    }

    template<typename U>
    Allocator(const Allocator<U> &)
    {
    }
    template<typename U>
    struct rebind
    {
        typedef Allocator<U> other;
    };
};


template<typename T, typename U>
bool operator==(const Allocator<T> &, const Allocator<U> &)
{
    return true;
}

template<typename T, typename U>
bool operator!=(const Allocator<T> &, const Allocator<U> &)
{
    return false;
}

typedef std::basic_string<char, std::char_traits<char>, m2::Allocator<char>> StlString;
typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, m2::Allocator<wchar_t>> StlWString;
typedef std::basic_stringstream<char, std::char_traits<char>, m2::Allocator<char>> StlSStream;
typedef std::basic_ostringstream<char, std::char_traits<char>, m2::Allocator<char>> StlOSStream;
typedef std::basic_istringstream<char, std::char_traits<char>, m2::Allocator<char>> StlISStream;


}// namespace m2
