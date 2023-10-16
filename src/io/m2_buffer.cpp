#include <m2_buffer.h>
#include <m2_bytearray.h>

namespace m2 {

/**
 * @brief Construct a new Buffer:: Buffer object
 * 
 */
Buffer::Buffer() : IODevice() {}

/**
 * @brief Construct a new Buffer:: Buffer object
 * 
 * @param buf 
 */
Buffer::Buffer(ByteArray *buf) : IODevice() {}

/**
 * @brief Destroy the Buffer:: Buffer object
 * 
 */
Buffer::~Buffer() {}

/**
 * @brief 
 * 
 * @return ByteArray& 
 */
ByteArray &Buffer::buffer()
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @return const ByteArray& 
 */
const ByteArray &Buffer::buffer() const
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param a 
 */
void Buffer::setBuffer(ByteArray *a) {}

/**
 * @brief 
 * 
 * @param data 
 */
void Buffer::setData(const ByteArray &data) {}

/**
 * @brief 
 * 
 * @param data 
 * @param len 
 */
void Buffer::setData(const char *data, uint64_t len) {}

/**
 * @brief 
 * 
 * @return const ByteArray& 
 */
const ByteArray &Buffer::data() const
{
    // TODO: insert return statement here
}

/**
 * @brief 
 * 
 * @param openMode 
 * @return true 
 * @return false 
 */
bool Buffer::open(OpenModes openMode) { return false; }

/**
 * @brief 
 * 
 */
void Buffer::close() {}

/**
 * @brief 
 * 
 * @return int64_t 
 */
int64_t Buffer::size() const { return 0; }

/**
 * @brief 
 * 
 * @return int64_t 
 */
int64_t Buffer::pos() const { return 0; }

/**
 * @brief 
 * 
 * @param off 
 * @return true 
 * @return false 
 */
bool Buffer::seek(int64_t off) { return false; }

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Buffer::atEnd() const { return false; }

}// namespace m2
