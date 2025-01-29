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

#include "cpl_any.h"
#include "cpl_stringhelp.h"
#include <sstream>
#include <stdexcept>

namespace CPL {

Any::~Any()
{
    switch (Type)
    {
        case eString:
            delete[] strVal;
            break;
        case eBinary:
            delete[] blbVal;
            break;
        case eObject:
            delete objVal;
            break;
        default:
            break;
    }
}

Any::Any() : Type(eEmpty)
{
    std::memset(&this->dateVal, 0, sizeof(this->dateVal));
}

Any::Any(char v) : Type(eI1) { cVal = v; }

Any::Any(unsigned char v) : Type(eUI1) { ucVal = v; }

Any::Any(short v) : Type(eI2) { sVal = v; }

Any::Any(unsigned short v) : Type(eUI2) { usVal = v; }

Any::Any(int v) : Type(eI4) { iVal = v; }

Any::Any(unsigned int v) : Type(eUI4) { uiVal = v; }

Any::Any(long long v) : Type(eI8) { llVal = v; }

Any::Any(unsigned long long v) : Type(eUI8) { ullVal = v; }

Any::Any(float v) : Type(eR4) { fltVal = v; }

Any::Any(double v) : Type(eR8) { dblVal = v; }

Any::Any(bool v) : Type(eBool) { boolVal = v; }

Any::Any(RefObject *v) : Type(eObject) { objVal = v; }

Any::Any(const char *v) : Type(eString)
{
    strVal = new char[std::strlen(v) + 1];
    std::strcpy(strVal, v);
}

Any::Any(const std::string &str) : Type(eString)
{
    strVal = new char[str.size() + 1];
    std::strcpy(strVal, str.c_str());
}

Any::Any(const DateTime &v) : Type(eDateTime) { dateVal = v; }

Any::Any(const unsigned char *v, int nLen) : Type(eBinary)
{
    blbVal = new unsigned char[nLen];
    std::memcpy(blbVal, v, nLen);
}

Any::Any(const Any &rhs) : Type(rhs.Type)
{
    switch (rhs.Type)
    {
        case eI1:
            cVal = rhs.cVal;
            break;
        case eUI1:
            ucVal = rhs.ucVal;
            break;
        case eI2:
            sVal = rhs.sVal;
            break;
        case eUI2:
            usVal = rhs.usVal;
            break;
        case eI4:
            iVal = rhs.iVal;
            break;
        case eUI4:
            uiVal = rhs.uiVal;
            break;
        case eI8:
            llVal = rhs.llVal;
            break;
        case eUI8:
            ullVal = rhs.ullVal;
            break;
        case eR4:
            fltVal = rhs.fltVal;
            break;
        case eR8:
            dblVal = rhs.dblVal;
            break;
        case eBool:
            boolVal = rhs.boolVal;
            break;
        case eObject:
            objVal = rhs.objVal;
            break;
        case eString:
            strVal = new char[std::strlen(rhs.strVal) + 1];
            std::strcpy(strVal, rhs.strVal);
            break;
        case eBinary:
            {
                int len =
                        std::strlen(reinterpret_cast<const char *>(rhs.blbVal));
                blbVal = new unsigned char[len];
                std::memcpy(blbVal, rhs.blbVal, len);
                break;
            }
        case eDateTime:
            dateVal = rhs.dateVal;
            break;
        default:
            break;
    }
}

Any::Any(Any &&rhs) noexcept : Type(rhs.Type), cVal(rhs.cVal)
{
    // Move the data from rhs to this object
    rhs.Type = eEmpty;
}

Any::Any(VarType type) : Type(type)
{
    switch (type)
    {
        case eI1:
        case eUI1:
        case eI2:
        case eUI2:
        case eI4:
        case eUI4:
        case eI8:
        case eUI8:
        case eR4:
        case eR8:
        case eBool:
        case eObject:
        case eString:
        case eDateTime:
            std::memset(&this->dateVal, 0,
                        sizeof(this->dateVal));// Initialize memory
            break;
        case eBinary:
            blbVal = nullptr;
            break;
        default:
            break;
    }
}

// Operator Overload
Any &Any::operator=(const Any &rhs)
{
    if (this != &rhs)
    {
        this->Clear();
        new (this) Any(rhs);// Placement new
    }
    return *this;
}

Any &Any::operator=(Any &&rhs) noexcept
{
    if (this != &rhs)
    {
        this->Clear();
        Type = rhs.Type;
        rhs.Type = eEmpty;
        std::memcpy(this, &rhs, sizeof(Any));
    }
    return *this;
}

Any &Any::operator=(char v)
{
    Clear();
    Type = eI1;
    cVal = v;
    return *this;
}

Any &Any::operator=(unsigned char v)
{
    Clear();
    Type = eUI1;
    ucVal = v;
    return *this;
}

Any &Any::operator=(short v)
{
    Clear();
    Type = eI2;
    sVal = v;
    return *this;
}

Any &Any::operator=(unsigned short v)
{
    Clear();
    Type = eUI2;
    usVal = v;
    return *this;
}

Any &Any::operator=(int v)
{
    Clear();
    Type = eI4;
    iVal = v;
    return *this;
}

Any &Any::operator=(unsigned int v)
{
    Clear();
    Type = eUI4;
    uiVal = v;
    return *this;
}

Any &Any::operator=(long long v)
{
    Clear();
    Type = eI8;
    llVal = v;
    return *this;
}

Any &Any::operator=(unsigned long long v)
{
    Clear();
    Type = eUI8;
    ullVal = v;
    return *this;
}

Any &Any::operator=(float v)
{
    Clear();
    Type = eR4;
    fltVal = v;
    return *this;
}

Any &Any::operator=(double v)
{
    Clear();
    Type = eR8;
    dblVal = v;
    return *this;
}

Any &Any::operator=(bool v)
{
    Clear();
    Type = eBool;
    boolVal = v;
    return *this;
}

Any &Any::operator=(const char *v)
{
    Clear();
    Type = eString;
    strVal = new char[std::strlen(v) + 1];
    std::strcpy(strVal, v);
    return *this;
}

Any &Any::operator=(const std::string &str)
{
    Clear();
    Type = eString;
    strVal = new char[str.size() + 1];
    std::strcpy(strVal, str.c_str());
    return *this;
}

Any &Any::operator=(RefObject *v)
{
    Clear();
    Type = eObject;
    objVal = v;
    return *this;
}

bool Any::operator==(const Any &o) const
{
    if (Type != o.Type) { return false; }
    switch (Type)
    {
        case eI1:
            return cVal == o.cVal;
        case eUI1:
            return ucVal == o.ucVal;
        case eI2:
            return sVal == o.sVal;
        case eUI2:
            return usVal == o.usVal;
        case eI4:
            return iVal == o.iVal;
        case eUI4:
            return uiVal == o.uiVal;
        case eI8:
            return llVal == o.llVal;
        case eUI8:
            return ullVal == o.ullVal;
        case eR4:
            return fltVal == o.fltVal;
        case eR8:
            return dblVal == o.dblVal;
        case eBool:
            return boolVal == o.boolVal;
        case eString:
            return std::strcmp(strVal, o.strVal) == 0;
        case eObject:
            return objVal == o.objVal;
        case eDateTime:
            return dateVal == o.dateVal;
        default:
            return false;
    }
}

bool Any::operator!=(const Any &o) const { return !(*this == o); }

// Getters (AsType functions)
char Any::AsChar() const
{
    if (Type != eI1) { throw std::invalid_argument("Type is not char."); }
    return cVal;
}

unsigned char Any::AsUChar() const
{
    if (Type != eUI1)
    {
        throw std::invalid_argument("Type is not unsigned char.");
    }
    return ucVal;
}

short Any::AsShort() const
{
    if (Type != eI2) { throw std::invalid_argument("Type is not short."); }
    return sVal;
}

unsigned short Any::AsUShort() const
{
    if (Type != eUI2)
    {
        throw std::invalid_argument("Type is not unsigned short.");
    }
    return usVal;
}

int Any::AsInt() const
{
    if (Type != eI4) { throw std::invalid_argument("Type is not int."); }
    return iVal;
}

unsigned int Any::AsUInt() const
{
    if (Type != eUI4)
    {
        throw std::invalid_argument("Type is not unsigned int.");
    }
    return uiVal;
}

long long Any::AsLongLong() const
{
    if (Type != eI8) { throw std::invalid_argument("Type is not long long."); }
    return llVal;
}

unsigned long long Any::AsULongLong() const
{
    if (Type != eUI8)
    {
        throw std::invalid_argument("Type is not unsigned long long.");
    }
    return ullVal;
}

float Any::AsFloat() const
{
    if (Type != eR4) { throw std::invalid_argument("Type is not float."); }
    return fltVal;
}

double Any::AsDouble() const
{
    if (Type != eR8) { throw std::invalid_argument("Type is not double."); }
    return dblVal;
}

bool Any::AsBool() const
{
    if (Type != eBool) { throw std::invalid_argument("Type is not bool."); }
    return boolVal;
}

RefObject *Any::AsObj() const
{
    if (Type != eObject) { throw std::invalid_argument("Type is not object."); }
    return objVal;
}

char *Any::AsString() const
{
    if (Type != eString) { throw std::invalid_argument("Type is not string."); }
    return strVal;
}

DateTime Any::AsDateTime() const
{
    if (Type != eDateTime)
    {
        throw std::invalid_argument("Type is not DateTime.");
    }
    return dateVal;
}

int Any::AsBlob(unsigned char *blob) const
{
    if (Type != eBinary) { throw std::invalid_argument("Type is not binary."); }
    std::memcpy(blob, blbVal,
                std::strlen(reinterpret_cast<const char *>(blbVal)));
    return std::strlen(reinterpret_cast<const char *>(blbVal));
}

Any::operator char() const
{
    if (Type != eI1) { throw std::invalid_argument("Type is not char."); }
    return cVal;
}

Any::operator unsigned char() const
{
    if (Type != eUI1)
    {
        throw std::invalid_argument("Type is not unsigned char.");
    }
    return ucVal;
}

Any::operator short() const
{
    if (Type != eI2) { throw std::invalid_argument("Type is not short."); }
    return sVal;
}

Any::operator unsigned short() const
{
    if (Type != eUI2)
    {
        throw std::invalid_argument("Type is not unsigned short.");
    }
    return usVal;
}

Any::operator int() const
{
    if (Type != eI4) { throw std::invalid_argument("Type is not int."); }
    return iVal;
}

Any::operator unsigned int() const
{
    if (Type != eUI4)
    {
        throw std::invalid_argument("Type is not unsigned int.");
    }
    return uiVal;
}

Any::operator long long() const
{
    if (Type != eI8) { throw std::invalid_argument("Type is not long long."); }
    return llVal;
}

Any::operator unsigned long long() const
{
    if (Type != eUI8)
    {
        throw std::invalid_argument("Type is not unsigned long long.");
    }
    return ullVal;
}

Any::operator bool() const
{
    if (Type != eBool) { throw std::invalid_argument("Type is not bool."); }
    return boolVal;
}

Any::operator float() const
{
    if (Type != eR4) { throw std::invalid_argument("Type is not float."); }
    return fltVal;
}

Any::operator double() const
{
    if (Type != eR8) { throw std::invalid_argument("Type is not double."); }
    return dblVal;
}

Any::operator const char *() const
{
    if (Type != eString) { throw std::invalid_argument("Type is not string."); }
    return strVal;
}

Any::operator RefObject *()
{
    if (Type != eObject) { throw std::invalid_argument("Type is not object."); }
    return objVal;
}

void Any::Set(const unsigned char *bBlob, int nLen)
{
    if (Type != eBinary) { throw std::invalid_argument("Type is not binary."); }
    std::memcpy(blbVal, bBlob, nLen);
}

void Any::Set(const char *str, int nLen)
{
    if (Type != eString) { throw std::invalid_argument("Type is not string."); }
    std::memcpy(strVal, str, nLen);
}

unsigned char *Any::AllocBlob(int nLen)
{
    if (Type != eBinary) { throw std::invalid_argument("Type is not binary."); }
    return blbVal;
}

int Any::ValueSize() const
{
    switch (Type)
    {
        case eString:
            return std::strlen(strVal);
        case eBinary:
            return std::strlen(reinterpret_cast<const char *>(blbVal));
        default:
            return 0;
    }
}

const void *Any::ValuePtr() const
{
    switch (Type)
    {
        case eString:
            return strVal;
        case eBinary:
            return blbVal;
        default:
            return nullptr;
    }
}

unsigned long long Any::HashCode() const
{
    unsigned long long hash = Type;
    switch (Type)
    {
        case eI1:
            hash ^= cVal;
            break;
        case eUI1:
            hash ^= ucVal;
            break;
        case eI2:
            hash ^= sVal;
            break;
        case eUI2:
            hash ^= usVal;
            break;
        case eI4:
            hash ^= iVal;
            break;
        case eUI4:
            hash ^= uiVal;
            break;
        case eI8:
            hash ^= llVal;
            break;
        case eUI8:
            hash ^= ullVal;
            break;
        case eR4:
            hash ^= *(reinterpret_cast<const unsigned int *>(&fltVal));
            break;
        case eR8:
            hash ^= *(reinterpret_cast<const unsigned long long *>(&dblVal));
            break;
        case eBool:
            hash ^= boolVal;
            break;
        case eObject:
            hash ^= reinterpret_cast<unsigned long long>(objVal);
            break;
        case eString:
            for (size_t i = 0; strVal[i] != '\0'; ++i) { hash ^= strVal[i]; }
            break;
        case eBinary:
            for (int i = 0;
                 i < std::strlen(reinterpret_cast<const char *>(blbVal)); ++i)
            {
                hash ^= blbVal[i];
            }
            break;
        case eDateTime:
            //hash ^= dateVal.HashCode();
            break;
        default:
            break;
    }
    return hash;
}

// ToString Implementation
std::string Any::ToString() const
{
    std::ostringstream oss;
    switch (Type)
    {
        case eString:
            oss << strVal;
            break;
        case eI1:
            oss << cVal;
            break;
        case eUI1:
            oss << (int) ucVal;
            break;
        case eI2:
            oss << sVal;
            break;
        case eUI2:
            oss << usVal;
            break;
        case eI4:
            oss << iVal;
            break;
        case eUI4:
            oss << uiVal;
            break;
        case eI8:
            oss << llVal;
            break;
        case eUI8:
            oss << ullVal;
            break;
        case eR4:
            oss << fltVal;
            break;
        case eR8:
            oss << dblVal;
            break;
        case eBool:
            oss << (boolVal ? "true" : "false");
            break;
        case eObject:
            oss << "Object";
            break;// For object, you might want a custom string representation
        case eDateTime:
            //oss << dateVal.ToString();
            break;
        default:
            oss << "Unknown";
            break;
    }
    return oss.str();
}

// Clear function to reset data
void Any::Clear()
{
    switch (Type)
    {
        case eString:
            delete[] strVal;
            break;
        case eBinary:
            delete[] blbVal;
            break;
        default:
            break;
    }
    Type = eEmpty;
}

void Any::Swap(Any &rhs)
{
    std::swap(Type, rhs.Type);
    std::swap(cVal, rhs.cVal);
    std::swap(strVal, rhs.strVal);
    std::swap(blbVal, rhs.blbVal);
    std::swap(objVal, rhs.objVal);
    std::swap(dateVal, rhs.dateVal);
}

const Any &Any::Empty()
{
    static const Any emptyAny(eEmpty);
    return emptyAny;
}

}// namespace CPL
