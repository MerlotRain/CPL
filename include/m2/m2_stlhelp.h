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

#include "preconfig.h"

namespace m2 {

class UTILITY_EXPORT GsByteAllocator
{
public:
    static void *Allocate(size_t size);
    static void Deallocate(void *p, size_t n);
};


template<typename T>
class UTILITY_EXPORT GsAllocator : public GsByteAllocator
{
public:
    GsAllocator()
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
    GsAllocator(const GsAllocator<U> &)
    {
    }
    template<typename U>
    struct rebind
    {
        typedef GsAllocator<U> other;
    };
};


template<typename T, typename U>
bool operator==(const GsAllocator<T> &, const GsAllocator<U> &)
{
    return true;
}

template<typename T, typename U>
bool operator!=(const GsAllocator<T> &, const GsAllocator<U> &)
{
    return false;
}

typedef std::basic_string<char, std::char_traits<char>, Lite::Utility::GsAllocator<char>> GsStlString;
typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, Lite::Utility::GsAllocator<wchar_t>> GsStlWString;
typedef std::basic_stringstream<char, std::char_traits<char>, Lite::Utility::GsAllocator<char>> GsStlSStream;
typedef std::basic_ostringstream<char, std::char_traits<char>, Lite::Utility::GsAllocator<char>> GsStlOSStream;
typedef std::basic_istringstream<char, std::char_traits<char>, Lite::Utility::GsAllocator<char>> GsStlISStream;


template<class _Ty1, class _Ty2>
struct GsPair
{
    _Ty1 first;
    _Ty2 second;

    GsPair() : first(0), second(0)
    {
    }
    explicit GsPair(const _Ty1 &_Val1, const _Ty2 &_Val2) : first(_Val1), second(_Val2)
    {
    }
    GsPair(const GsPair &p) : first(p.first), second(p.second)
    {
    }
    explicit GsPair(const std::pair<_Ty1, _Ty2> &_Right) : first(_Right.first), second(_Right.second)
    {// construct from compatible pair
    }
    GsPair<_Ty1, _Ty2> &operator=(const GsPair<_Ty1, _Ty2> &_Right)
    {// assign from compatible pair
        first = _Right.first;
        second = _Right.second;
        return (*this);
    }
    GsPair<_Ty1, _Ty2> &operator=(const std::pair<_Ty1, _Ty2> &_Right)
    {// assign from compatible pair
        first = _Right.first;
        second = _Right.second;
        return (*this);
    }
    bool operator<(const GsPair<_Ty1, _Ty2> &_Right) const
    {
        return (first != _Right.first) ? (first < _Right.first) : (second < _Right.second);
    }
    void swap(GsPair<_Ty1, _Ty2> &_Right)
    {// exchange contents with _Right
        if (this != &_Right)
        {// different, worth swapping
            _Ty1 f = first;
            first = _Right.first;
            _Right.first = f;

            _Ty2 s = second;
            second = _Right.second;
            _Right.second = s;
        }
    }
};


template<class _Ty1, class _Ty2>
inline constexpr bool operator==(const GsPair<_Ty1, _Ty2> &_Left, const GsPair<_Ty1, _Ty2> &_Right)
{// test for pair equality
    return (_Left.first == _Right.first && _Left.second == _Right.second);
}
template<class _Ty1, class _Ty2>
inline constexpr bool operator!=(const GsPair<_Ty1, _Ty2> &_Left, const GsPair<_Ty1, _Ty2> &_Right)
{// test for pair inequality
    return (!(_Left == _Right));
}

template<class _Ty1, class _Ty2>
inline constexpr bool operator<(const GsPair<_Ty1, _Ty2> &_Left, const GsPair<_Ty1, _Ty2> &_Right)
{// test if _Left < _Right for pairs
    return (_Left.first < _Right.first ||
            (!(_Right.first < _Left.first) && _Left.second < _Right.second));
}

template<class _Ty1, class _Ty2>
inline constexpr bool operator>(const GsPair<_Ty1, _Ty2> &_Left, const GsPair<_Ty1, _Ty2> &_Right)
{// test if _Left > _Right for pairs
    return (_Right < _Left);
}

template<class _Ty1, class _Ty2>
inline constexpr bool operator<=(const GsPair<_Ty1, _Ty2> &_Left, const GsPair<_Ty1, _Ty2> &_Right)
{// test if _Left <= _Right for pairs
    return (!(_Right < _Left));
}

template<class _Ty1, class _Ty2>
inline constexpr bool operator>=(const GsPair<_Ty1, _Ty2> &_Left, const GsPair<_Ty1, _Ty2> &_Right)
{// test if _Left >= _Right for pairs
    return (!(_Left < _Right));
}


template<class _Ty1, class _Ty2>
inline constexpr GsPair<_Ty1, _Ty2> Make_GsPair(_Ty1 &&_Val1, _Ty2 &&_Val2)
{// return pair composed from arguments
    typedef GsPair<_Ty1, _Ty2> _Mypair;
    return (_Mypair((_Val1), (_Val2)));
}

}// namespace m2
