#include <stringhelp.h>

namespace m2 {

enum CharacterProperties
{
    eACP_CONTROL = 0x0001,
    eACP_SPACE = 0x0002,
    eACP_PUNCT = 0x0004,
    eACP_DIGIT = 0x0008,
    eACP_HEXDIGIT = 0x0010,
    eACP_ALPHA = 0x0020,
    eACP_LOWER = 0x0040,
    eACP_UPPER = 0x0080,
    eACP_GRAPH = 0x0100,
    eACP_PRINT = 0x0200
};

static constexpr int CHARACTER_PROPERTIES[128] = {
        /* 00 . */ eACP_LOWER,
        /* 01 . */ eACP_LOWER,
        /* 02 . */ eACP_LOWER,
        /* 03 . */ eACP_LOWER,
        /* 04 . */ eACP_LOWER,
        /* 05 . */ eACP_LOWER,
        /* 06 . */ eACP_LOWER,
        /* 07 . */ eACP_LOWER,
        /* 08 . */ eACP_LOWER,
        /* 09 . */ eACP_LOWER | eACP_SPACE,
        /* 0a . */ eACP_LOWER | eACP_SPACE,
        /* 0b . */ eACP_LOWER | eACP_SPACE,
        /* 0c . */ eACP_LOWER | eACP_SPACE,
        /* 0d . */ eACP_LOWER | eACP_SPACE,
        /* 0e . */ eACP_LOWER,
        /* 0f . */ eACP_LOWER,
        /* 10 . */ eACP_LOWER,
        /* 11 . */ eACP_LOWER,
        /* 12 . */ eACP_LOWER,
        /* 13 . */ eACP_LOWER,
        /* 14 . */ eACP_LOWER,
        /* 15 . */ eACP_LOWER,
        /* 16 . */ eACP_LOWER,
        /* 17 . */ eACP_LOWER,
        /* 18 . */ eACP_LOWER,
        /* 19 . */ eACP_LOWER,
        /* 1a . */ eACP_LOWER,
        /* 1b . */ eACP_LOWER,
        /* 1c . */ eACP_LOWER,
        /* 1d . */ eACP_LOWER,
        /* 1e . */ eACP_LOWER,
        /* 1f . */ eACP_LOWER,
        /* 20   */ eACP_SPACE | eACP_PRINT,
        /* 21 ! */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 22 " */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 23 # */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 24 $ */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 25 % */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 26 & */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 27 ' */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 28 ( */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 29 ) */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 2a * */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 2b + */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 2c , */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 2d - */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 2e . */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 2f / */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 30 0 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 31 1 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 32 2 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 33 3 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 34 4 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 35 5 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 36 6 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 37 7 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 38 8 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 39 9 */ eACP_DIGIT | eACP_HEXDIGIT | eACP_GRAPH | eACP_PRINT,
        /* 3a : */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 3b ; */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 3c < */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 3d = */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 3e > */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 3f ? */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 40 @ */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 41 A */ eACP_HEXDIGIT | eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 42 B */ eACP_HEXDIGIT | eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 43 C */ eACP_HEXDIGIT | eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 44 D */ eACP_HEXDIGIT | eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 45 E */ eACP_HEXDIGIT | eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 46 F */ eACP_HEXDIGIT | eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 47 G */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 48 H */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 49 I */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 4a J */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 4b K */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 4c L */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 4d M */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 4e N */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 4f O */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 50 P */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 51 Q */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 52 R */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 53 S */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 54 T */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 55 U */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 56 V */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 57 W */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 58 X */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 59 Y */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 5a Z */ eACP_ALPHA | eACP_UPPER | eACP_GRAPH | eACP_PRINT,
        /* 5b [ */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 5c \ */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 5d ] */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 5e ^ */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 5f _ */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 60 ` */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 61 a */ eACP_HEXDIGIT | eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 62 b */ eACP_HEXDIGIT | eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 63 c */ eACP_HEXDIGIT | eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 64 d */ eACP_HEXDIGIT | eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 65 e */ eACP_HEXDIGIT | eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 66 f */ eACP_HEXDIGIT | eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 67 g */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 68 h */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 69 i */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 6a j */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 6b k */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 6c l */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 6d m */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 6e n */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 6f o */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 70 p */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 71 q */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 72 r */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 73 s */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 74 t */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 75 u */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 76 v */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 77 w */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 78 x */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 79 y */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 7a z */ eACP_ALPHA | eACP_LOWER | eACP_GRAPH | eACP_PRINT,
        /* 7b { */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 7c | */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 7d } */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 7e ~ */ eACP_PUNCT | eACP_GRAPH | eACP_PRINT,
        /* 7f . */ eACP_LOWER};


int Ascii::Properties(int ch)
{
    if (IsAscii(ch))
    {
        return CHARACTER_PROPERTIES[ch];
    }
    else
    {
        return 0;
    }
}

bool Ascii::HasSomeProperties(int ch, int properties)
{
    return (Properties(ch) & properties) != 0;
}

bool Ascii::HasProperties(int ch, int properties)
{
    return (Properties(ch) & properties) == properties;
}

bool Ascii::IsAscii(int ch)
{
    return (static_cast<uint32_t>(ch) & 0xFFFFFF80) == 0;
}

bool Ascii::IsSpace(int ch)
{
    return HasProperties(ch, eACP_SPACE);
}

bool Ascii::IsDigit(int ch)
{
    return HasProperties(ch, eACP_DIGIT);
}

bool Ascii::IsHexDigit(int ch)
{
    return HasProperties(ch, eACP_HEXDIGIT);
}

bool Ascii::IsPunctuation(int ch)
{
    return HasProperties(ch, eACP_PUNCT);
}

bool Ascii::IsAlpha(int ch)
{
    return HasProperties(ch, eACP_ALPHA);
}

bool Ascii::IsAlphaNumeric(int ch)
{
    return HasSomeProperties(ch, eACP_ALPHA | eACP_DIGIT);
}

bool Ascii::IsLower(int ch)
{
    return HasProperties(ch, eACP_LOWER);
}

bool Ascii::IsUpper(int ch)
{
    return HasProperties(ch, eACP_UPPER);
}

bool Ascii::IsPrintable(int ch)
{
    return HasProperties(ch, eACP_PRINT);
}

int Ascii::ToLower(int ch)
{
    if (IsUpper(ch))
    {
        return ch + 32;
    }
    else
    {
        return ch;
    }
}

int Ascii::ToUpper(int ch)
{
    if (IsLower(ch))
    {
        return ch - 32;
    }
    else
    {
        return ch;
    }
}

}// namespace m2
