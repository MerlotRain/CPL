/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
  Based on the public domain implementation of the SHA-1 algorithm
  Copyright (C) Dominik Reichl <dominik.reichl@t-online.de>
*/

#include "endian.h"
#include "preconfig.h"

#ifdef _MSC_VER
#include <stdlib.h>
#endif


// Test Vectors (from FIPS PUB 180-1)
//
//  SHA1("abc") =
//      A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
//
//  SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") =
//      84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
//
//  SHA1(A million repetitions of "a") =
//      34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
//


// #define or #undef this, if you want the to wipe all
// temporary variables after processing
#define SHA1_WIPE_VARIABLES


struct Sha1State
{
    uint32_t h0;
    uint32_t h1;
    uint32_t h2;
    uint32_t h3;
    uint32_t h4;

    uint64_t messageSize;
    unsigned char buffer[64];
};


typedef union
{
    uint8_t bytes[64];
    uint32_t words[16];
} Sha1Chunk;

static inline uint32_t rol32(uint32_t value, unsigned int shift)
{
#ifdef _MSC_VER
    return _rotl(value, shift);
#else
    return ((value << shift) | (value >> (32 - shift)));
#endif
}

static inline uint32_t sha1Word(Sha1Chunk *chunk, const unsigned int position)
{
    return (chunk->words[position & 0xf] = rol32(chunk->words[(position + 13) & 0xf] ^ chunk->words[(position + 8) & 0xf] ^ chunk->words[(position + 2) & 0xf] ^ chunk->words[(position) &0xf], 1));
}

static inline void sha1Round0(Sha1Chunk *chunk, const unsigned int position,
                              uint32_t &v, uint32_t &w, uint32_t &x, uint32_t &y, uint32_t &z)
{
    z += (((w & (x ^ y)) ^ y) + chunk->words[position] + 0x5A827999 + rol32(v, 5));
    w = rol32(w, 30);
}

static inline void sha1Round1(Sha1Chunk *chunk, const unsigned int position,
                              uint32_t &v, uint32_t &w, uint32_t &x, uint32_t &y, uint32_t &z)
{
    z += (((w & (x ^ y)) ^ y) + sha1Word(chunk, position) + 0x5A827999 + rol32(v, 5));
    w = rol32(w, 30);
}

static inline void sha1Round2(Sha1Chunk *chunk, const unsigned int position,
                              uint32_t &v, uint32_t &w, uint32_t &x, uint32_t &y, uint32_t &z)
{
    z += ((w ^ x ^ y) + sha1Word(chunk, position) + 0x6ED9EBA1 + rol32(v, 5));
    w = rol32(w, 30);
}

static inline void sha1Round3(Sha1Chunk *chunk, const unsigned int position,
                              uint32_t &v, uint32_t &w, uint32_t &x, uint32_t &y, uint32_t &z)
{
    z += ((((w | x) & y) | (w & x)) + sha1Word(chunk, position) + 0x8F1BBCDC + rol32(v, 5));
    w = rol32(w, 30);
}

static inline void sha1Round4(Sha1Chunk *chunk, const unsigned int position,
                              uint32_t &v, uint32_t &w, uint32_t &x, uint32_t &y, uint32_t &z)
{
    z += ((w ^ x ^ y) + sha1Word(chunk, position) + 0xCA62C1D6 + rol32(v, 5));
    w = rol32(w, 30);
}

static inline void sha1ProcessChunk(Sha1State *state, const unsigned char *buffer)
{
    // Copy state[] to working vars
    uint32_t a = state->h0;
    uint32_t b = state->h1;
    uint32_t c = state->h2;
    uint32_t d = state->h3;
    uint32_t e = state->h4;

    uint8_t chunkBuffer[64];
    memcpy(chunkBuffer, buffer, 64);

    Sha1Chunk *chunk = reinterpret_cast<Sha1Chunk *>(&chunkBuffer);

    for (int i = 0; i < 16; ++i)
        chunk->words[i] = Lite::Utility::EndianConverter::FromBigEndian(chunk->words[i]);

    sha1Round0(chunk, 0, a, b, c, d, e);
    sha1Round0(chunk, 1, e, a, b, c, d);
    sha1Round0(chunk, 2, d, e, a, b, c);
    sha1Round0(chunk, 3, c, d, e, a, b);
    sha1Round0(chunk, 4, b, c, d, e, a);
    sha1Round0(chunk, 5, a, b, c, d, e);
    sha1Round0(chunk, 6, e, a, b, c, d);
    sha1Round0(chunk, 7, d, e, a, b, c);
    sha1Round0(chunk, 8, c, d, e, a, b);
    sha1Round0(chunk, 9, b, c, d, e, a);
    sha1Round0(chunk, 10, a, b, c, d, e);
    sha1Round0(chunk, 11, e, a, b, c, d);
    sha1Round0(chunk, 12, d, e, a, b, c);
    sha1Round0(chunk, 13, c, d, e, a, b);
    sha1Round0(chunk, 14, b, c, d, e, a);
    sha1Round0(chunk, 15, a, b, c, d, e);
    sha1Round1(chunk, 16, e, a, b, c, d);
    sha1Round1(chunk, 17, d, e, a, b, c);
    sha1Round1(chunk, 18, c, d, e, a, b);
    sha1Round1(chunk, 19, b, c, d, e, a);
    sha1Round2(chunk, 20, a, b, c, d, e);
    sha1Round2(chunk, 21, e, a, b, c, d);
    sha1Round2(chunk, 22, d, e, a, b, c);
    sha1Round2(chunk, 23, c, d, e, a, b);
    sha1Round2(chunk, 24, b, c, d, e, a);
    sha1Round2(chunk, 25, a, b, c, d, e);
    sha1Round2(chunk, 26, e, a, b, c, d);
    sha1Round2(chunk, 27, d, e, a, b, c);
    sha1Round2(chunk, 28, c, d, e, a, b);
    sha1Round2(chunk, 29, b, c, d, e, a);
    sha1Round2(chunk, 30, a, b, c, d, e);
    sha1Round2(chunk, 31, e, a, b, c, d);
    sha1Round2(chunk, 32, d, e, a, b, c);
    sha1Round2(chunk, 33, c, d, e, a, b);
    sha1Round2(chunk, 34, b, c, d, e, a);
    sha1Round2(chunk, 35, a, b, c, d, e);
    sha1Round2(chunk, 36, e, a, b, c, d);
    sha1Round2(chunk, 37, d, e, a, b, c);
    sha1Round2(chunk, 38, c, d, e, a, b);
    sha1Round2(chunk, 39, b, c, d, e, a);
    sha1Round3(chunk, 40, a, b, c, d, e);
    sha1Round3(chunk, 41, e, a, b, c, d);
    sha1Round3(chunk, 42, d, e, a, b, c);
    sha1Round3(chunk, 43, c, d, e, a, b);
    sha1Round3(chunk, 44, b, c, d, e, a);
    sha1Round3(chunk, 45, a, b, c, d, e);
    sha1Round3(chunk, 46, e, a, b, c, d);
    sha1Round3(chunk, 47, d, e, a, b, c);
    sha1Round3(chunk, 48, c, d, e, a, b);
    sha1Round3(chunk, 49, b, c, d, e, a);
    sha1Round3(chunk, 50, a, b, c, d, e);
    sha1Round3(chunk, 51, e, a, b, c, d);
    sha1Round3(chunk, 52, d, e, a, b, c);
    sha1Round3(chunk, 53, c, d, e, a, b);
    sha1Round3(chunk, 54, b, c, d, e, a);
    sha1Round3(chunk, 55, a, b, c, d, e);
    sha1Round3(chunk, 56, e, a, b, c, d);
    sha1Round3(chunk, 57, d, e, a, b, c);
    sha1Round3(chunk, 58, c, d, e, a, b);
    sha1Round3(chunk, 59, b, c, d, e, a);
    sha1Round4(chunk, 60, a, b, c, d, e);
    sha1Round4(chunk, 61, e, a, b, c, d);
    sha1Round4(chunk, 62, d, e, a, b, c);
    sha1Round4(chunk, 63, c, d, e, a, b);
    sha1Round4(chunk, 64, b, c, d, e, a);
    sha1Round4(chunk, 65, a, b, c, d, e);
    sha1Round4(chunk, 66, e, a, b, c, d);
    sha1Round4(chunk, 67, d, e, a, b, c);
    sha1Round4(chunk, 68, c, d, e, a, b);
    sha1Round4(chunk, 69, b, c, d, e, a);
    sha1Round4(chunk, 70, a, b, c, d, e);
    sha1Round4(chunk, 71, e, a, b, c, d);
    sha1Round4(chunk, 72, d, e, a, b, c);
    sha1Round4(chunk, 73, c, d, e, a, b);
    sha1Round4(chunk, 74, b, c, d, e, a);
    sha1Round4(chunk, 75, a, b, c, d, e);
    sha1Round4(chunk, 76, e, a, b, c, d);
    sha1Round4(chunk, 77, d, e, a, b, c);
    sha1Round4(chunk, 78, c, d, e, a, b);
    sha1Round4(chunk, 79, b, c, d, e, a);

    // Add the working vars back into state
    state->h0 += a;
    state->h1 += b;
    state->h2 += c;
    state->h3 += d;
    state->h4 += e;

    // Wipe variables
#ifdef SHA1_WIPE_VARIABLES
    a = b = c = d = e = 0;
    memset(chunkBuffer, 0, 64);
#endif
}

static inline void sha1InitState(Sha1State *state)
{
    state->h0 = 0x67452301;
    state->h1 = 0xEFCDAB89;
    state->h2 = 0x98BADCFE;
    state->h3 = 0x10325476;
    state->h4 = 0xC3D2E1F0;

    state->messageSize = 0;
}

static inline void sha1Update(Sha1State *state, const unsigned char *data, int64_t len)
{
    uint32_t rest = static_cast<uint32_t>(state->messageSize & GS_UINT64_C(63));

    uint64_t availableData = static_cast<uint64_t>(len) + static_cast<uint64_t>(rest);
    state->messageSize += len;

    if (availableData < GS_UINT64_C(64))
    {
        memcpy(&state->buffer[rest], &data[0], len);
    }
    else
    {
        int64_t i = static_cast<int64_t>(64 - rest);
        memcpy(&state->buffer[rest], &data[0], static_cast<int32_t>(i));
        sha1ProcessChunk(state, state->buffer);

        int64_t lastI = len - ((len + rest) & GS_UINT64_C(63));
        for (; i < lastI; i += 64)
            sha1ProcessChunk(state, &data[i]);

        memcpy(&state->buffer[0], &data[i], len - i);
    }
}

static inline void sha1FinalizeState(Sha1State *state)
{
    uint64_t messageSize = state->messageSize;
    unsigned char sizeInBits[8];
    Lite::Utility::EndianConverter::ToBigEndian(messageSize << 3, sizeInBits);

    sha1Update(state, (const unsigned char *) "\200", 1);

    unsigned char zero[64];
    memset(zero, 0, 64);
    if (static_cast<int>(messageSize & 63) > 56 - 1)
    {
        sha1Update(state, zero, 64 - 1 - static_cast<int>(messageSize & 63));
        sha1Update(state, zero, 64 - 8);
    }
    else
    {
        sha1Update(state, zero, 64 - 1 - 8 - static_cast<int>(messageSize & 63));
    }

    sha1Update(state, sizeInBits, 8);
#ifdef SHA1_WIPE_VARIABLES
    memset(state->buffer, 0, 64);
    memset(zero, 0, 64);
    state->messageSize = 0;
#endif
}

static inline void sha1ToHash(Sha1State *state, unsigned char *buffer)
{
    Lite::Utility::EndianConverter::ToBigEndian(state->h0, buffer);
    Lite::Utility::EndianConverter::ToBigEndian(state->h1, buffer + 4);
    Lite::Utility::EndianConverter::ToBigEndian(state->h2, buffer + 8);
    Lite::Utility::EndianConverter::ToBigEndian(state->h3, buffer + 12);
    Lite::Utility::EndianConverter::ToBigEndian(state->h4, buffer + 16);
}
