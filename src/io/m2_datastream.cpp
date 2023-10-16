#include <m2_datastream.h>

namespace m2 {

DataStream::DataStream() {}

DataStream::DataStream(IODevice *device) {}

DataStream::DataStream(ByteArray *array, IODevice *device) {}

DataStream::DataStream(const ByteArray &) {}

DataStream::~DataStream() {}

bool DataStream::atEnd() const { return false; }

Status DataStream::status() const { return Status(); }

void DataStream::setStatus(Status status) {}

void DataStream::resetStatus() {}

IODevice *DataStream::device() const { return nullptr; }

void DataStream::setDevice(IODevice *) {}

Endian DataStream::byteOrder() const { return Endian(); }

void DataStream::setByteOrder(Endian) {}

DataStream &DataStream::operator>>(int8_t &i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(uint8_t &i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(int16_t &i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(uint16_t &i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(int32_t &i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(uint32_t &i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(int64_t &i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(uint64_t &i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(std::nullptr_t &ptr)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(bool &i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(float &f)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(double &f)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(char *&str)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(char16_t &c)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator>>(char32_t &c)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(int8_t i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(uint8_t i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(int16_t i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(uint16_t i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(int32_t i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(uint32_t i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(int64_t i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(uint64_t i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(bool i)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(float f)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(double f)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(const char *str)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(char16_t c)
{
    // TODO: insert return statement here
}

DataStream &DataStream::operator<<(char32_t c)
{
    // TODO: insert return statement here
}

DataStream &DataStream::readBytes(char *&, uint32_t &len)
{
    // TODO: insert return statement here
}

int DataStream::readRawData(char *, int len) { return 0; }

DataStream &DataStream::writeBytes(const char *, uint32_t len)
{
    // TODO: insert return statement here
}

int DataStream::writeRawData(const char *, int len) { return 0; }

int DataStream::skipRawData(int len) { return 0; }

}// namespace m2