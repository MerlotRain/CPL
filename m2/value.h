#ifndef M2_VARIANT_H_
#define M2_VARIANT_H_

#include <cstdint>
#include <string>
#include <variant>

namespace m2 {

class Value
{
public:
    enum VarType
    {
        eUnknownVarType = -2,
        eEmpty = -1,
        eI1 = 0,
        eI2,
        eI4,
        eI8,
        eUI1,
        eUI2,
        eUI4,
        eUI8,
        eR4,
        eR8,
        eString,
        eBool,
        eBlob,
        eDateTime,
    };

    VarType Type;

    Value();
    Value(char v);
    Value(unsigned char v);
    Value(short v);
    Value(unsigned short v);
    Value(int v);
    Value(unsigned int v);
    Value(long long v, bool bDateTime = false);
    Value(const time_t &dt);
    Value(unsigned long long v);
    Value(float v);
    Value(double v);
    Value(bool v);
    Value(const char *v);
    Value(const std::string &str);
    Value(const unsigned char *v, int nLen);
    Value(const Value &rhs);
    Value(Value &&rhs);
    Value(VarType type);
    virtual ~Value();

    Value &operator=(const Value &);
    Value &operator=(Value &&);
    Value &operator=(char v);
    Value &operator=(unsigned char v);
    Value &operator=(short v);
    Value &operator=(unsigned short v);
    Value &operator=(int v);
    Value &operator=(unsigned int v);
    Value &operator=(long long v);
    Value &operator=(unsigned long long v);
    Value &operator=(float v);
    Value &operator=(double v);
    Value &operator=(bool v);
    Value &operator=(const char *v);
    Value &operator=(const std::string &str);

    bool operator==(const Value &o) const;
    bool operator!=(const Value &o) const;

    void swap(Value &rhs);
    void clear();

    char toChar() const;
    unsigned char toUChar() const;
    short toShort() const;
    unsigned short toUShort() const;
    int toInt() const;
    unsigned int toUInt() const;
    long long toLongLong() const;
    unsigned long long toULongLong() const;
    float toFloat() const;
    double toDouble() const;
    bool toBool() const;
    std::string toString() const;
    int toBlob(unsigned char *bBlob) const;

    operator char() const;
    operator unsigned char() const;
    operator short() const;
    operator unsigned short() const;
    operator int() const;
    operator unsigned int() const;
    operator long long() const;
    operator unsigned long long() const;
    operator bool() const;
    operator float() const;
    operator double() const;
    operator const char *() const;


    void setBlob(const unsigned char *bBlob, int nLen);
    void setBlob(const char *str, int nLen);
    unsigned char *allocBlob(int nLen);
    int valueSize() const;
    const void *valuePtr() const;
    unsigned long long hashCode() const;

    static const Value &empty();

private:
    struct Blob
    {
        uint8_t *data;
        int len;
    };

    std::variant<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t,
                 uint64_t, float, double, std::string, bool, Blob, time_t>
            value_;
};

}// namespace m2

#endif//M2_VARIANT_H_