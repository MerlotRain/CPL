#include <m2_iodevice.h>

namespace m2 {

IODevice::IODevice() {}

IODevice::IODevice(OpenModes mode) {}

OpenModes IODevice::openMode() const { return OpenModes(); }

bool IODevice::open(OpenModes mode) { return false; }

void IODevice::close() {}

bool IODevice::isOpen() const { return false; }

bool IODevice::isReadable() const { return false; }

bool IODevice::isWritable() const { return false; }

int64_t IODevice::pos() const { return 0; }

int64_t IODevice::size() const { return 0; }

bool IODevice::seek(int64_t pos) { return false; }

bool IODevice::atEnd() const { return false; }

bool IODevice::reset() { return false; }

int64_t IODevice::read(char *data, int64_t maxlen) { return 0; }

ByteArray IODevice::read(int64_t maxlen) { return ByteArray(); }

ByteArray IODevice::readAll() { return ByteArray(); }

int64_t IODevice::readLine(char *data, int64_t maxlen) { return 0; }

ByteArray IODevice::readLine(int64_t maxlen) { return ByteArray(); }

void IODevice::ungetChar(char c) {}

bool IODevice::putChar(char c) { return false; }

bool IODevice::getChar(char *c) { return false; }

int64_t IODevice::write(const char *data, int64_t len) { return 0; }

int64_t IODevice::write(const char *data) { return 0; }

int64_t IODevice::write(const ByteArray &data) { return 0; }

int64_t IODevice::peek(char *data, int64_t maxlen) { return 0; }

ByteArray IODevice::peek(int64_t maxlen) { return ByteArray(); }

int64_t IODevice::skip(int64_t maxSize) { return 0; }

String IODevice::errorMessage() const { return String(); }

}// namespace m2
