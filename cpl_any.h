/**
 * CPL - Common Portability Library
 *
 * Copyright (C) 2024 Merlot.Rain
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "cpl_datetime.h"
#include "cpl_stringhelp.h"
#include <cpl_exports.h>

namespace CPL {

class RefObject;

/// \brief Data type for the Any object.
enum VarType
{
    /// \brief Unknown data type.
    eUnknownVarType = -2,
    /// \brief Empty data.
    eEmpty = -1,
    /// \brief char type.
    eI1 = 0,
    /// \brief short type.
    eI2,
    /// \brief int type.
    eI4,
    /// \brief long long type.
    eI8,
    /// \brief unsigned char type.
    eUI1,
    /// \brief unsigned short type.
    eUI2,
    /// \brief unsigned int type.
    eUI4,
    /// \brief unsigned long long type.
    eUI8,
    /// \brief float type.
    eR4,
    /// \brief double type.
    eR8,
    /// \brief const char* type.
    eString,
    /// \brief bool type.
    eBool,
    /// \brief RefObject* type.
    eObject,
    /// \brief Binary data type.
    eBlob,
    /// \brief Binary data type (alias for eBlob).
    eBinary = eBlob,

    /// \brief DateTime type.
    eDateTime,
};

/// \brief A class to store data of various types.
class CPL_API Any
{
public:
    /// \brief Data type of the stored value.
    VarType Type;

    /// \brief A union to store the value.
    union
    {
        char cVal;
        unsigned char ucVal;
        short sVal;
        unsigned short usVal;
        int iVal;
        unsigned int uiVal;
        long long llVal;
        unsigned long long ullVal;
        float fltVal;
        double dblVal;
        bool boolVal;
        RefObject *objVal;
        char *strVal;
        unsigned char *blbVal;
        DateTime dateVal;
    };

    /// \brief Destructor.
    virtual ~Any();

    /// \brief Default constructor.
    Any();

    /// \brief Constructor for a single char value.
    /// \param v The char value.
    Any(char v);

    /// \brief Constructor for an unsigned char value.
    /// \param v The unsigned char value.
    Any(unsigned char v);

    /// \brief Constructor for a short value.
    /// \param v The short value.
    Any(short v);

    /// \brief Constructor for an unsigned short value.
    /// \param v The unsigned short value.
    Any(unsigned short v);

    /// \brief Constructor for an int value.
    /// \param v The int value.
    Any(int v);

    /// \brief Constructor for an unsigned int value.
    /// \param v The unsigned int value.
    Any(unsigned int v);

    /// \brief Constructor for a long long value.
    /// \param v The long long value.
    Any(long long v);

    /// \brief Constructor for an unsigned long long value.
    /// \param v The unsigned long long value.
    Any(unsigned long long v);

    /// \brief Constructor for a float value.
    /// \param v The float value.
    Any(float v);

    /// \brief Constructor for a double value.
    /// \param v The double value.
    Any(double v);

    /// \brief Constructor for a bool value.
    /// \param v The bool value.
    Any(bool v);

    /// \brief Constructor for a RefObject pointer.
    /// \param v The RefObject pointer.
    Any(RefObject *v);

    /// \brief Constructor for a string constant (char*).
    /// \param v The string constant.
    Any(const char *v);

    /// \brief Constructor for a string constant (std::string).
    /// \param str The string constant.
    Any(const std::string &str);

    /// \brief Constructor for a DateTime value.
    /// \param v The DateTime value.
    Any(const DateTime &v);

    /// \brief Constructor for binary data (unsigned char*).
    /// \param v The binary data.
    /// \param nLen The length of the data.
    Any(const unsigned char *v, int nLen);

    /// \brief Copy constructor.
    /// \param rhs The object to copy from.
    Any(const Any &rhs);

    /// \brief Move constructor.
    /// \param rhs The object to move from.
    Any(Any &&rhs) noexcept;

    /// \brief Constructor to initialize with a specific type.
    /// \param type The type of the data.
    Any(VarType type);

    /// \brief Assignment operator to copy data.
    /// \param rhs The object to copy from.
    /// \return The reference to the current object.
    Any &operator=(const Any &rhs);

    /// \brief Assignment operator for char type.
    /// \param v The char value.
    /// \return The reference to the current object.
    Any &operator=(char v);

    /// \brief Assignment operator for unsigned char type.
    /// \param v The unsigned char value.
    /// \return The reference to the current object.
    Any &operator=(unsigned char v);

    /// \brief Assignment operator for short type.
    /// \param v The short value.
    /// \return The reference to the current object.
    Any &operator=(short v);

    /// \brief Assignment operator for unsigned short type.
    /// \param v The unsigned short value.
    /// \return The reference to the current object.
    Any &operator=(unsigned short v);

    /// \brief Assignment operator for int type.
    /// \param v The int value.
    /// \return The reference to the current object.
    Any &operator=(int v);

    /// \brief Assignment operator for unsigned int type.
    /// \param v The unsigned int value.
    /// \return The reference to the current object.
    Any &operator=(unsigned int v);

    /// \brief Assignment operator for long long type.
    /// \param v The long long value.
    /// \return The reference to the current object.
    Any &operator=(long long v);

    /// \brief Assignment operator for unsigned long long type.
    /// \param v The unsigned long long value.
    /// \return The reference to the current object.
    Any &operator=(unsigned long long v);

    /// \brief Assignment operator for float type.
    /// \param v The float value.
    /// \return The reference to the current object.
    Any &operator=(float v);

    /// \brief Assignment operator for double type.
    /// \param v The double value.
    /// \return The reference to the current object.
    Any &operator=(double v);

    /// \brief Assignment operator for bool type.
    /// \param v The bool value.
    /// \return The reference to the current object.
    Any &operator=(bool v);

    /// \brief Assignment operator for string constant (char*).
    /// \param v The string constant.
    /// \return The reference to the current object.
    Any &operator=(const char *v);

    /// \brief Assignment operator for string constant (std::string).
    /// \param str The string constant.
    /// \return The reference to the current object.
    Any &operator=(const std::string &str);

    /// \brief Assignment operator for RefObject pointer.
    /// \param v The RefObject pointer.
    /// \return The reference to the current object.
    Any &operator=(RefObject *v);

    /// \brief Move assignment operator.
    /// \param v The object to move from.
    /// \return The reference to the current object.
    Any &operator=(Any &&v);

    /// \brief Equality operator.
    /// \param o The object to compare.
    /// \return True if equal, otherwise false.
    bool operator==(const Any &o) const;

    /// \brief Inequality operator.
    /// \param o The object to compare.
    /// \return True if not equal, otherwise false.
    bool operator!=(const Any &o) const;

    /// \brief Clears the stored data.
    void Clear();

    /// \brief Retrieves the stored char value.
    /// \return The stored char value.
    char AsChar() const;

    /// \brief Retrieves the stored unsigned char value.
    /// \return The stored unsigned char value.
    unsigned char AsUChar() const;

    /// \brief Retrieves the stored short value.
    /// \return The stored short value.
    short AsShort() const;

    /// \brief Retrieves the stored unsigned short value.
    /// \return The stored unsigned short value.
    unsigned short AsUShort() const;

    /// \brief Retrieves the stored int value.
    /// \return The stored int value.
    int AsInt() const;

    /// \brief Retrieves the stored unsigned int value.
    /// \return The stored unsigned int value.
    unsigned int AsUInt() const;

    /// \brief Retrieves the stored long long value.
    /// \return The stored long long value.
    long long AsLongLong() const;

    /// \brief Retrieves the stored unsigned long long value.
    /// \return The stored unsigned long long value.
    unsigned long long AsULongLong() const;

    /// \brief Retrieves the stored float value.
    /// \return The stored float value.
    float AsFloat() const;

    /// \brief Retrieves the stored double value.
    /// \return The stored double value.
    double AsDouble() const;

    /// \brief Retrieves the stored bool value.
    /// \return The stored bool value.
    bool AsBool() const;

    /// \brief Retrieves the stored RefObject pointer.
    /// \return The stored RefObject pointer.
    RefObject *AsObj() const;

    /// \brief Retrieves the stored string (char*).
    /// \return The stored string.
    char *AsString() const;

    /// \brief Retrieves the stored DateTime value.
    /// \return The stored DateTime value.
    DateTime AsDateTime() const;

    /// \brief Retrieves the stored binary data.
    /// \param bBlob The buffer to store the data.
    /// \return The length of the binary data.
    int AsBlob(unsigned char *bBlob) const;

    /// \brief Type conversion to char.
    /// \return The stored value as char.
    operator char() const;

    /// \brief Type conversion to unsigned char.
    /// \return The stored value as unsigned char.
    operator unsigned char() const;

    /// \brief Type conversion to short.
    /// \return The stored value as short.
    operator short() const;

    /// \brief Type conversion to unsigned short.
    /// \return The stored value as unsigned short.
    operator unsigned short() const;

    /// \brief Type conversion to int.
    /// \return The stored value as int.
    operator int() const;

    /// \brief Type conversion to unsigned int.
    /// \return The stored value as unsigned int.
    operator unsigned int() const;

    /// \brief Type conversion to long long.
    /// \return The stored value as long long.
    operator long long() const;

    /// \brief Type conversion to unsigned long long.
    /// \return The stored value as unsigned long long.
    operator unsigned long long() const;

    /// \brief Type conversion to bool.
    /// \return The stored value as bool.
    operator bool() const;

    /// \brief Type conversion to float.
    /// \return The stored value as float.
    operator float() const;

    /// \brief Type conversion to double.
    /// \return The stored value as double.
    operator double() const;

    /// \brief Type conversion to const char*.
    /// \return The stored value as const char*.
    operator const char *() const;

    /// \brief Type conversion to RefObject*.
    /// \return The stored value as RefObject*.
    operator RefObject *();

    /// \brief Sets the binary data.
    /// \param bBlob The binary data.
    /// \param nLen The length of the data.
    void Set(const unsigned char *bBlob, int nLen);

    /// \brief Sets the string data (char*).
    /// \param str The string data.
    /// \param nLen The length of the string.
    void Set(const char *str, int nLen);

    /// \brief Allocates space for binary data and sets the type to blob.
    /// \param nLen The size of the data.
    /// \return The allocated buffer.
    unsigned char *AllocBlob(int nLen);

    /// \brief Returns the size of the stored data.
    /// \return The size of the data in bytes.
    int ValueSize() const;

    /// \brief Returns a pointer to the stored data.
    /// \return A pointer to the stored data.
    const void *ValuePtr() const;

    /// \brief Calculates and returns the hash code for the object.
    /// \return The hash code.
    unsigned long long HashCode() const;

    /// \brief Converts the stored data to a string.
    /// \return The string representation of the data.
    std::string ToString() const;

    /// \brief Swaps the data with another object.
    /// \param rhs The object to swap with.
    void Swap(Any &rhs);

    /// \brief Returns an empty object.
    /// \return A reference to an empty object.
    static const Any &Empty();
};

}// namespace CPL
