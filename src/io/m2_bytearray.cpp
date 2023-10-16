#include <m2_bytearray.h>

namespace m2 {

/****************************************************************************
ByteArray functions
****************************************************************************/

/**
 * @brief Construct a new Byte Buffer:: Byte Buffer object
 * 
 */
ByteArray::ByteArray() {}

/**
 * @brief Construct a new Byte Buffer:: Byte Buffer object
 * 
 * @param size 
 */
ByteArray::ByteArray(const char *, uint64_t size) {}

/**
 * @brief Construct a new Byte Buffer:: Byte Buffer object
 * 
 * @param size 
 * @param c 
 */
ByteArray::ByteArray(uint64_t size, char c) {}

/**
 * @brief Construct a new Byte Buffer:: Byte Buffer object
 * 
 * @param rhs 
 */
ByteArray::ByteArray(const ByteArray &rhs) {}

/**
 * @brief Construct a new Byte Buffer:: Byte Buffer object
 * 
 * @param rhs 
 */
ByteArray::ByteArray(ByteArray &&rhs) noexcept {}

/**
 * @brief 
 * 
 * @return ByteArray& 
 */
ByteArray &ByteArray::operator=(const ByteArray &) noexcept
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param str 
 * @return ByteArray& 
 */
ByteArray &ByteArray::operator=(const char *str)
{
    // TODO: insert return statement here
}

/**
 * @brief Destroy the Byte Buffer:: Byte Buffer object
 * 
 */
ByteArray::~ByteArray() {}

/**
 * @brief 
 * 
 * @param other 
 */
void ByteArray::swap(ByteArray &other) noexcept {}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool ByteArray::isNull() const noexcept { return false; }

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool ByteArray::isEmpty() const noexcept { return false; }

/**
 * @brief 
 * 
 * @param size 
 */
void ByteArray::resize(uint64_t size) {}

/**
 * @brief 
 * 
 * @param size 
 * @param c 
 */
void ByteArray::resize(uint64_t size, char c) {}

/**
 * @brief 
 * 
 * @param c 
 * @param size 
 * @return ByteArray& 
 */
ByteArray &ByteArray::fill(char c, uint64_t size)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param size 
 */
void ByteArray::reserve(uint64_t size) {}

/**
 * @brief 
 * 
 */
void ByteArray::squeeze() {}

/**
 * @brief 
 * 
 */
void ByteArray::detach() {}

/**
 * @brief 
 */
void ByteArray::clear() {}

/**
 * @brief 
 * 
 * @param i 
 * @return char 
 */
char ByteArray::at(uint64_t i) const { return 0; }

/**
 * @brief 
 * 
 * @param i 
 * @return char 
 */
char ByteArray::operator[](uint64_t i) const { return 0; }

/**
 * @brief 
 * 
 * @param i 
 * @return char& 
 */
char &ByteArray::operator[](uint64_t i)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @return char 
 */
char ByteArray::front() const { return 0; }

/**
 * @brief 
 * 
 * @return char& 
 */
char &ByteArray::front()
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @return char 
 */
char ByteArray::back() const { return 0; }

/**
 * @brief 
 * 
 * @return char& 
 */
char &ByteArray::back()
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param c 
 * @return ByteArray& 
 */
ByteArray &ByteArray::prepend(char c)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param count 
 * @param c 
 * @return ByteArray& 
 */
ByteArray &ByteArray::prepend(uint64_t count, char c)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param s 
 * @return ByteArray& 
 */
ByteArray &ByteArray::prepend(const char *s)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param s 
 * @param len 
 * @return ByteArray& 
 */
ByteArray &ByteArray::prepend(const char *s, uint64_t len)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param a 
 * @return ByteArray& 
 */
ByteArray &ByteArray::prepend(const ByteArray &a)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param a 
 * @return ByteArray& 
 */
ByteArray &ByteArray::prepend(const ByteArrayView &a)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param c 
 * @return ByteArray& 
 */
ByteArray &ByteArray::append(char c)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param count 
 * @param c 
 * @return ByteArray& 
 */
ByteArray &ByteArray::append(uint64_t count, char c)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param s 
 * @param len 
 * @return ByteArray& 
 */
ByteArray &ByteArray::append(const char *s, uint64_t len)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param a 
 * @return ByteArray& 
 */
ByteArray &ByteArray::append(const ByteArray &a)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param a 
 * @return ByteArray& 
 */
ByteArray &ByteArray::append(const ByteArrayView &a)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param i 
 * @param a 
 * @return ByteArray& 
 */
ByteArray &ByteArray::insert(uint64_t i, const ByteArrayView &a)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param i 
 * @param s 
 * @return ByteArray& 
 */
ByteArray &ByteArray::insert(uint64_t i, const char *s)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param i 
 * @param data 
 * @return ByteArray& 
 */
ByteArray &ByteArray::insert(uint64_t i, const ByteArray &data)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param i 
 * @param count 
 * @param c 
 * @return ByteArray& 
 */
ByteArray &ByteArray::insert(uint64_t i, uint64_t count, char c)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param i 
 * @param c 
 * @return ByteArray& 
 */
ByteArray &ByteArray::insert(uint64_t i, char c)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param i 
 * @param s 
 * @param len 
 * @return ByteArray& 
 */
ByteArray &ByteArray::insert(uint64_t i, const char *s, uint64_t len)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param index 
 * @param len 
 * @return ByteArray& 
 */
ByteArray &ByteArray::remove(uint64_t index, uint64_t len)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param index 
 * @param len 
 * @param s 
 * @param alen 
 * @return ByteArray& 
 */
ByteArray &ByteArray::replace(uint64_t index, uint64_t len, const char *s,
                              uint64_t alen)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param before 
 * @param bsize 
 * @param after 
 * @param asize 
 * @return ByteArray& 
 */
ByteArray &ByteArray::replace(const char *before, uint64_t bsize,
                              const char *after, uint64_t asize)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param before 
 * @param after 
 * @return ByteArray& 
 */
ByteArray &ByteArray::replace(char before, char after)
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @return ByteArray 
 */
ByteArray ByteArray::toBase64() const { return ByteArray(); }

/**
 * @brief 
 * 
 * @return ByteArray 
 */
ByteArray ByteArray::toHex() const { return ByteArray(); }

/**
 * @brief 
 * 
 * @return unsigned char * 
 */
ByteArray::operator unsigned char *() const {}

/**
 * @brief 
 * 
 * @return short * 
 */
ByteArray::operator short *() const {}

/**
 * @brief 
 * 
 * @return unsigned short * 
 */
ByteArray::operator unsigned short *() const {}

/**
 * @brief 
 * 
 * @return int * 
 */
ByteArray::operator int *() const {}

/**
 * @brief 
 * 
 * @return unsigned int * 
 */
ByteArray::operator unsigned int *() const {}

/**
 * @brief 
 * 
 * @return long long * 
 */
ByteArray::operator long long *() const {}

/**
 * @brief 
 * 
 * @return unsigned long long * 
 */
ByteArray::operator unsigned long long *() const {}

/**
 * @brief 
 * 
 * @return double * 
 */
ByteArray::operator double *() const {}

/**
 * @brief 
 * 
 * @return float * 
 */
ByteArray::operator float *() const {}

/**
 * @brief 
 * 
 * @param first 
 * @param last 
 * @return ByteArray::iterator 
 */
ByteArray::iterator ByteArray::erase(const_iterator first, const_iterator last)
{
    return iterator();
}

/****************************************************************************
ByteArray functions
****************************************************************************/

/**
 * @brief 
 * 
 * @param data 
 * @param nbytes 
 * @param compressionLevel 
 * @return ByteArray 
 */
ByteArray compress(const uint8_t *data, uint64_t nbytes, int compressionLevel)
{
    return ByteArray();
}

/**
 * @brief 
 * 
 * @param data 
 * @param nbytes 
 * @return ByteArray 
 */
ByteArray uncompress(const uint8_t *data, uint64_t nbytes)
{
    return ByteArray();
}

/**
 * @brief 
 * 
 * @param data 
 * @param compressionLevel 
 * @return ByteArray 
 */
ByteArray compress(const ByteArray &data, int compressionLevel)
{
    return ByteArray();
}

/**
 * @brief 
 * 
 * @param data 
 * @return ByteArray 
 */
ByteArray uncompress(const ByteArray &data) { return ByteArray(); }

/**
 * @brief 
 * @param  str1             
 * @param  str2             
 * @return int 
 */
int bacompare(const char *str1, const char *str2) { return 0; }

/**
 * @brief 
 * @param  str1             
 * @param  str2             
 * @return int 
 */
int bacompare(const ByteArray &str1, const ByteArray &str2) { return 0; }

/**
 * @brief 
 * @param  str1             
 * @param  str2             
 * @return int 
 */
int bacompare(const ByteArray &str1, const char *str2) { return 0; }

/**
 * @brief 
 * @param  str1             
 * @param  str2             
 * @return int 
 */
int bacompare(const char *str1, const ByteArray &str2) { return 0; }

}// namespace m2
// namespace m2
