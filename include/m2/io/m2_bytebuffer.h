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

#ifndef M2_BYTEBUFFER_H_
#define M2_BYTEBUFFER_H_

#include <m2_string.h>

namespace m2 {

class M2_API ByteBuffer
{
public:
    ByteBuffer() noexcept;
    ByteBuffer(const char *, uint64_t size = -1);
    ByteBuffer(uint64_t size, char c);
    ByteBuffer(const ByteBuffer &rhs);
    ByteBuffer(ByteBuffer &&rhs) noexcept;
    ByteBuffer &operator=(const ByteBuffer &) noexcept;
    ByteBuffer &operator=(const char *str);
    inline ByteBuffer(ByteBuffer &&other) noexcept = default;
    ~ByteBuffer();

    void swap(ByteBuffer &other) noexcept;

    bool isEmpty() const noexcept;
    void resize(uint64_t size);
    void resize(uint64_t size, char c);
    inline uint64_t size() const noexcept;

    ByteBuffer &fill(char c, uint64_t size = -1);

    inline uint64_t capacity() const;
    inline void reserve(uint64_t size);
    inline void squeeze();

    inline char *data();
    inline const char *data() const noexcept;
    const char *constData() const noexcept { return data(); }
    inline void detach();
    inline char at(uint64_t i) const;
    inline char operator[](uint64_t i) const;
    [[nodiscard]] inline char &operator[](uint64_t i);
    [[nodiscard]] char front() const;
    [[nodiscard]] inline char &front();
    [[nodiscard]] char back() const;
    [[nodiscard]] inline char &back();

    ByteBuffer &prepend(char c);
    inline ByteBuffer &prepend(uint64_t count, char c);
    ByteBuffer &prepend(const char *s);
    ByteBuffer &prepend(const char *s, uint64_t len);
    ByteBuffer &prepend(const ByteBuffer &a);

    ByteBuffer &append(char c);
    inline ByteBuffer &append(uint64_t count, char c);
    ByteBuffer &append(const char *s) { return append(s, -1); }
    ByteBuffer &append(const char *s, uint64_t len);
    ByteBuffer &append(const ByteBuffer &a);

    inline ByteBuffer &insert(uint64_t i, const char *s);
    inline ByteBuffer &insert(uint64_t i, const ByteBuffer &data);
    ByteBuffer &insert(uint64_t i, uint64_t count, char c);
    ByteBuffer &insert(uint64_t i, char c);
    ByteBuffer &insert(uint64_t i, const char *s, uint64_t len);

    ByteBuffer &remove(uint64_t index, uint64_t len);

    ByteBuffer &replace(uint64_t index, uint64_t len, const char *s,
                        uint64_t alen);
    ByteBuffer &replace(const char *before, uint64_t bsize, const char *after,
                        uint64_t asize);
    ByteBuffer &replace(char before, char after);

    ByteBuffer toBase64() const;
    ByteBuffer toHex() const;

    template<class T>
    uint64_t sizeT() const;
    template<class T>
    T *dataT() const;

    operator unsigned char *() const;
    operator short *() const;
    operator unsigned short *() const;
    operator int *() const;
    operator unsigned int *() const;
    operator long long *() const;
    operator unsigned long long *() const;
    operator double *() const;
    operator float *() const;

public:
    typedef char *iterator;
    typedef const char *const_iterator;
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    iterator begin() { return data(); }
    const_iterator begin() const noexcept { return data(); }
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator constBegin() const noexcept { return begin(); }
    iterator end() { return data() + size(); }
    const_iterator end() const noexcept { return data() + size(); }
    const_iterator cend() const noexcept { return end(); }
    const_iterator constEnd() const noexcept { return end(); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend() const noexcept { return rend(); }

public:
    typedef uint64_t size_type;
    typedef ptrdiff_t difference_type;
    typedef const char &const_reference;
    typedef char &reference;
    typedef char *pointer;
    typedef const char *const_pointer;
    typedef char value_type;
    void push_back(char c) { append(c); }
    void push_back(const char *s) { append(s); }
    void push_back(const ByteBuffer &a) { append(a); }
    void push_front(char c) { prepend(c); }
    void push_front(const char *c) { prepend(c); }
    void push_front(const ByteBuffer &a) { prepend(a); }
    void shrink_to_fit() { squeeze(); }
    iterator erase(const_iterator first, const_iterator last);

public:
    static ByteBuffer compress(const uint8_t *data, uint64_t nbytes,
                               int compressionLevel = -1);
    static ByteBuffer uncompress(const uint8_t *data, uint64_t nbytes);
    static ByteBuffer compress(const ByteBuffer &data,
                               int compressionLevel = -1);
    static ByteBuffer uncompress(const ByteBuffer &data);

private:
    uint64_t alloc;
    uint64_t used;
    char *d;
};

inline bool operator==(const ByteBuffer &a1, const ByteBuffer &a2) noexcept
{
    return a1 == a2;
}
inline bool operator==(const ByteBuffer &a1, const char *a2) noexcept {}
inline bool operator==(const char *a1, const ByteBuffer &a2) noexcept
{
    return false;
}
inline bool operator!=(const ByteBuffer &a1, const ByteBuffer &a2) noexcept
{
    return !(a1 == a2);
}
inline bool operator!=(const ByteBuffer &a1, const char *a2) noexcept
{
    return false;
}
inline bool operator!=(const char *a1, const ByteBuffer &a2) noexcept
{
    return false;
}
inline bool operator<(const ByteBuffer &a1, const ByteBuffer &a2) noexcept
{
    return false;
}
inline bool operator<(const ByteBuffer &a1, const char *a2) noexcept
{
    return false;
}
inline bool operator<(const char *a1, const ByteBuffer &a2) noexcept
{
    return false;
}
inline bool operator<=(const ByteBuffer &a1, const ByteBuffer &a2) noexcept
{
    return false;
}
inline bool operator<=(const ByteBuffer &a1, const char *a2) noexcept
{
    return false;
}
inline bool operator<=(const char *a1, const ByteBuffer &a2) noexcept
{
    return false;
}
inline bool operator>(const ByteBuffer &a1, const ByteBuffer &a2) noexcept
{
    return false;
}
inline bool operator>(const ByteBuffer &a1, const char *a2) noexcept
{
    return false;
}
inline bool operator>(const char *a1, const ByteBuffer &a2) noexcept
{
    return false;
}
inline bool operator>=(const ByteBuffer &a1, const ByteBuffer &a2) noexcept
{
    return false;
}
inline bool operator>=(const ByteBuffer &a1, const char *a2) noexcept
{
    return false;
}
inline bool operator>=(const char *a1, const ByteBuffer &a2) noexcept
{
    return false;
}

inline bool operator==(const ByteBuffer &a1, std::nullptr_t) noexcept
{
    return a1.isEmpty();
}
inline bool operator!=(const ByteBuffer &a1, std::nullptr_t) noexcept
{
    return !a1.isEmpty();
}
inline bool operator<(const ByteBuffer &, std::nullptr_t) noexcept
{
    return false;
}
inline bool operator>(const ByteBuffer &a1, std::nullptr_t) noexcept
{
    return !a1.isEmpty();
}
inline bool operator<=(const ByteBuffer &a1, std::nullptr_t) noexcept
{
    return a1.isEmpty();
}
inline bool operator>=(const ByteBuffer &, std::nullptr_t) noexcept
{
    return true;
}

inline bool operator==(std::nullptr_t, const ByteBuffer &a2) noexcept
{
    return a2 == nullptr;
}
inline bool operator!=(std::nullptr_t, const ByteBuffer &a2) noexcept
{
    return a2 != nullptr;
}
inline bool operator<(std::nullptr_t, const ByteBuffer &a2) noexcept
{
    return a2 > nullptr;
}
inline bool operator>(std::nullptr_t, const ByteBuffer &a2) noexcept
{
    return a2 < nullptr;
}
inline bool operator<=(std::nullptr_t, const ByteBuffer &a2) noexcept
{
    return a2 >= nullptr;
}
inline bool operator>=(std::nullptr_t, const ByteBuffer &a2) noexcept
{
    return a2 <= nullptr;
}

}// namespace m2

#endif//M2_BYTEBUFFER_H_
