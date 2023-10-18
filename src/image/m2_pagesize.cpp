#include <m2_pagesize.h>

namespace m2 {

// clang-format off

// http://msdn.microsoft.com/en-us/library/windows/desktop/dd319099.aspx
enum WindowsDMPaper
{
    DMPAPER_NONE                          = 0,// Not a DMPAPER, use for sizes without a DMPAPER value
    DMPAPER_LETTER                        = 1,
    DMPAPER_LETTERSMALL                   = 2,
    DMPAPER_TABLOID                       = 3,
    DMPAPER_LEDGER                        = 4,
    DMPAPER_LEGAL                         = 5,
    DMPAPER_STATEMENT                     = 6,
    DMPAPER_EXECUTIVE                     = 7,
    DMPAPER_A3                            = 8,
    DMPAPER_A4                            = 9,
    DMPAPER_A4SMALL                       = 10,
    DMPAPER_A5                            = 11,
    DMPAPER_B4                            = 12,
    DMPAPER_B5                            = 13,
    DMPAPER_FOLIO                         = 14,
    DMPAPER_QUARTO                        = 15,
    DMPAPER_10X14                         = 16,
    DMPAPER_11X17                         = 17,
    DMPAPER_NOTE                          = 18,
    DMPAPER_ENV_9                         = 19,
    DMPAPER_ENV_10                        = 20,
    DMPAPER_ENV_11                        = 21,
    DMPAPER_ENV_12                        = 22,
    DMPAPER_ENV_14                        = 23,
    DMPAPER_CSHEET                        = 24,
    DMPAPER_DSHEET                        = 25,
    DMPAPER_ESHEET                        = 26,
    DMPAPER_ENV_DL                        = 27,
    DMPAPER_ENV_C5                        = 28,
    DMPAPER_ENV_C3                        = 29,
    DMPAPER_ENV_C4                        = 30,
    DMPAPER_ENV_C6                        = 31,
    DMPAPER_ENV_C65                       = 32,
    DMPAPER_ENV_B4                        = 33,
    DMPAPER_ENV_B5                        = 34,
    DMPAPER_ENV_B6                        = 35,
    DMPAPER_ENV_ITALY                     = 36,
    DMPAPER_ENV_MONARCH                   = 37,
    DMPAPER_ENV_PERSONAL                  = 38,
    DMPAPER_FANFOLD_US                    = 39,
    DMPAPER_FANFOLD_STD_GERMAN            = 40,
    DMPAPER_FANFOLD_LGL_GERMAN            = 41,
    DMPAPER_ISO_B4                        = 42,
    DMPAPER_JAPANESE_POSTCARD             = 43,
    DMPAPER_9X11                          = 44,
    DMPAPER_10X11                         = 45,
    DMPAPER_15X11                         = 46,
    DMPAPER_ENV_INVITE                    = 47,
    DMPAPER_RESERVED_48                   = 48,
    DMPAPER_RESERVED_49                   = 49,
    DMPAPER_LETTER_EXTRA                  = 50,
    DMPAPER_LEGAL_EXTRA                   = 51,
    DMPAPER_TABLOID_EXTRA                 = 52,
    DMPAPER_A4_EXTRA                      = 53,
    DMPAPER_LETTER_TRANSVERSE             = 54,
    DMPAPER_A4_TRANSVERSE                 = 55,
    DMPAPER_LETTER_EXTRA_TRANSVERSE       = 56,
    DMPAPER_A_PLUS                        = 57,
    DMPAPER_B_PLUS                        = 58,
    DMPAPER_LETTER_PLUS                   = 59,
    DMPAPER_A4_PLUS                       = 60,
    DMPAPER_A5_TRANSVERSE                 = 61,
    DMPAPER_B5_TRANSVERSE                 = 62,
    DMPAPER_A3_EXTRA                      = 63,
    DMPAPER_A5_EXTRA                      = 64,
    DMPAPER_B5_EXTRA                      = 65,
    DMPAPER_A2                            = 66,
    DMPAPER_A3_TRANSVERSE                 = 67,
    DMPAPER_A3_EXTRA_TRANSVERSE           = 68,
    DMPAPER_DBL_JAPANESE_POSTCARD         = 69,
    DMPAPER_A6                            = 70,
    DMPAPER_JENV_KAKU2                    = 71,
    DMPAPER_JENV_KAKU3                    = 72,
    DMPAPER_JENV_CHOU3                    = 73,
    DMPAPER_JENV_CHOU4                    = 74,
    DMPAPER_LETTER_ROTATED                = 75,
    DMPAPER_A3_ROTATED                    = 76,
    DMPAPER_A4_ROTATED                    = 77,
    DMPAPER_A5_ROTATED                    = 78,
    DMPAPER_B4_JIS_ROTATED                = 79,
    DMPAPER_B5_JIS_ROTATED                = 80,
    DMPAPER_JAPANESE_POSTCARD_ROTATED     = 81,
    DMPAPER_DBL_JAPANESE_POSTCARD_ROTATED = 82,
    DMPAPER_A6_ROTATED                    = 83,
    DMPAPER_JENV_KAKU2_ROTATED            = 84,
    DMPAPER_JENV_KAKU3_ROTATED            = 85,
    DMPAPER_JENV_CHOU3_ROTATED            = 86,
    DMPAPER_JENV_CHOU4_ROTATED            = 87,
    DMPAPER_B6_JIS                        = 88,
    DMPAPER_B6_JIS_ROTATED                = 89,
    DMPAPER_12X11                         = 90,
    DMPAPER_JENV_YOU4                     = 91,
    DMPAPER_JENV_YOU4_ROTATED             = 92,
    DMPAPER_P16K                          = 93,
    DMPAPER_P32K                          = 94,
    DMPAPER_P32KBIG                       = 95,
    DMPAPER_PENV_1                        = 96,
    DMPAPER_PENV_2                        = 97,
    DMPAPER_PENV_3                        = 98,
    DMPAPER_PENV_4                        = 99,
    DMPAPER_PENV_5                        = 100,
    DMPAPER_PENV_6                        = 101,
    DMPAPER_PENV_7                        = 102,
    DMPAPER_PENV_8                        = 103,
    DMPAPER_PENV_9                        = 104,
    DMPAPER_PENV_10                       = 105,
    DMPAPER_P16K_ROTATED                  = 106,
    DMPAPER_P32K_ROTATED                  = 107,
    DMPAPER_P32KBIG_ROTATED               = 108,
    DMPAPER_PENV_1_ROTATED                = 109,
    DMPAPER_PENV_2_ROTATED                = 110,
    DMPAPER_PENV_3_ROTATED                = 111,
    DMPAPER_PENV_4_ROTATED                = 112,
    DMPAPER_PENV_5_ROTATED                = 113,
    DMPAPER_PENV_6_ROTATED                = 114,
    DMPAPER_PENV_7_ROTATED                = 115,
    DMPAPER_PENV_8_ROTATED                = 116,
    DMPAPER_PENV_9_ROTATED                = 117,
    DMPAPER_PENV_10_ROTATED               = 118,
    DMPAPER_LAST                          = DMPAPER_PENV_10_ROTATED,
    DMPAPER_USER                          = 256
};

static const int windowsConversion[][2] = {
        {                        DMPAPER_11X17,               DMPAPER_TABLOID}, // = DMPAPER_LEDGER rotated
        {          DMPAPER_A3_EXTRA_TRANSVERSE,              DMPAPER_A3_EXTRA},
        {                   DMPAPER_A3_ROTATED,                    DMPAPER_A3},
        {                DMPAPER_A3_TRANSVERSE,                    DMPAPER_A3},
        {                   DMPAPER_A4_ROTATED,                    DMPAPER_A4},
        {                DMPAPER_A4_TRANSVERSE,                    DMPAPER_A4},
        {                   DMPAPER_A5_ROTATED,                    DMPAPER_A5},
        {                DMPAPER_A5_TRANSVERSE,                    DMPAPER_A5},
        {                   DMPAPER_A6_ROTATED,                    DMPAPER_A6},
        {               DMPAPER_B4_JIS_ROTATED,                    DMPAPER_B4},
        {               DMPAPER_B5_JIS_ROTATED,                    DMPAPER_B5},
        {                DMPAPER_B5_TRANSVERSE,                    DMPAPER_B5},
        {               DMPAPER_B6_JIS_ROTATED,                DMPAPER_B6_JIS},
        {DMPAPER_DBL_JAPANESE_POSTCARD_ROTATED, DMPAPER_DBL_JAPANESE_POSTCARD},
        {    DMPAPER_JAPANESE_POSTCARD_ROTATED,     DMPAPER_JAPANESE_POSTCARD},
        {           DMPAPER_JENV_CHOU3_ROTATED,            DMPAPER_JENV_CHOU3},
        {           DMPAPER_JENV_CHOU4_ROTATED,            DMPAPER_JENV_CHOU4},
        {           DMPAPER_JENV_KAKU2_ROTATED,            DMPAPER_JENV_KAKU2},
        {           DMPAPER_JENV_KAKU3_ROTATED,            DMPAPER_JENV_KAKU3},
        {            DMPAPER_JENV_YOU4_ROTATED,             DMPAPER_JENV_YOU4},
        {      DMPAPER_LETTER_EXTRA_TRANSVERSE,          DMPAPER_LETTER_EXTRA},
        {               DMPAPER_LETTER_ROTATED,                DMPAPER_LETTER},
        {            DMPAPER_LETTER_TRANSVERSE,                DMPAPER_LETTER},
        {                 DMPAPER_P16K_ROTATED,                  DMPAPER_P16K},
        {                 DMPAPER_P32K_ROTATED,                  DMPAPER_P32K},
        {              DMPAPER_P32KBIG_ROTATED,               DMPAPER_P32KBIG},
        {               DMPAPER_PENV_1_ROTATED,                DMPAPER_PENV_1},
        {               DMPAPER_PENV_2_ROTATED,                DMPAPER_PENV_2},
        {               DMPAPER_PENV_3_ROTATED,                DMPAPER_PENV_3},
        {               DMPAPER_PENV_4_ROTATED,                DMPAPER_PENV_4},
        {               DMPAPER_PENV_5_ROTATED,                DMPAPER_PENV_5},
        {               DMPAPER_PENV_6_ROTATED,                DMPAPER_PENV_6},
        {               DMPAPER_PENV_7_ROTATED,                DMPAPER_PENV_7},
        {               DMPAPER_PENV_8_ROTATED,                DMPAPER_PENV_8},
        {               DMPAPER_PENV_9_ROTATED,                DMPAPER_PENV_9},
        {              DMPAPER_PENV_10_ROTATED,               DMPAPER_PENV_10}  // Is = DMPAPER_LAST, use as loop terminator
};

struct StandardPageSize
{
    PageSize::PageSizeId id : 8;
    int windowsId : 16;                // Windows DMPAPER value
    PageSize::Unit definitionUnits : 8;// Standard definition size, e.g. ISO uses mm, ANSI uses inches
    int widthPoints : 16;
    int heightPoints : 16;
    double widthMillimeters;
    double heightMillimeters;
    double widthInches;
    double heightInches;
    const char mediaOption[20];
};

static const StandardPageSize m2_pageSizes[] = {
        {            PageSize::Letter,                DMPAPER_LETTER,       PageSize::Inch,  612,  792, 215.9, 279.4,    8.5,     11,             "Letter"},
        {             PageSize::Legal,                 DMPAPER_LEGAL,       PageSize::Inch,  612, 1008, 215.9, 355.6,    8.5,     14,              "Legal"},
        {         PageSize::Executive,                  DMPAPER_NONE,       PageSize::Inch,  540,  720, 190.5,   254,    7.5,     10, "Executive.7.5x10in"},
        {                PageSize::A0,                  DMPAPER_NONE, PageSize::Millimeter, 2384, 3370,   841,  1189,  33.11,  46.81,                 "A0"},
        {                PageSize::A1,                  DMPAPER_NONE, PageSize::Millimeter, 1684, 2384,   594,   841,  23.39,  33.11,                 "A1"},
        {                PageSize::A2,                    DMPAPER_A2, PageSize::Millimeter, 1191, 1684,   420,   594,  16.54,  23.39,                 "A2"},
        {                PageSize::A3,                    DMPAPER_A3, PageSize::Millimeter,  842, 1191,   297,   420,  11.69,  16.54,                 "A3"},
        {                PageSize::A4,                    DMPAPER_A4, PageSize::Millimeter,  595,  842,   210,   297,   8.27,  11.69,                 "A4"},
        {                PageSize::A5,                    DMPAPER_A5, PageSize::Millimeter,  420,  595,   148,   210,   5.83,   8.27,                 "A5"},
        {                PageSize::A6,                    DMPAPER_A6, PageSize::Millimeter,  297,  420,   105,   148,   4.13,   5.83,                 "A6"},
        {                PageSize::A7,                  DMPAPER_NONE, PageSize::Millimeter,  210,  297,    74,   105,   2.91,   4.13,                 "A7"},
        {                PageSize::A8,                  DMPAPER_NONE, PageSize::Millimeter,  148,  210,    52,    74,   2.05,   2.91,                 "A8"},
        {                PageSize::A9,                  DMPAPER_NONE, PageSize::Millimeter,  105,  148,    37,    52,   1.46,   2.05,                 "A9"},
        {               PageSize::A10,                  DMPAPER_NONE, PageSize::Millimeter,   73,  105,    26,    37,   1.02,   1.46,                "A10"},
        {                PageSize::B0,                  DMPAPER_NONE, PageSize::Millimeter, 2835, 4008,  1000,  1414,  39.37,  55.67,              "ISOB0"},
        {                PageSize::B1,                  DMPAPER_NONE, PageSize::Millimeter, 2004, 2835,   707,  1000,  27.83,  39.37,              "ISOB1"},
        {                PageSize::B2,                  DMPAPER_NONE, PageSize::Millimeter, 1417, 2004,   500,   707,  19.68,  27.83,              "ISOB2"},
        {                PageSize::B3,                  DMPAPER_NONE, PageSize::Millimeter, 1001, 1417,   353,   500,   13.9,  19.68,              "ISOB3"},
        {                PageSize::B4,                DMPAPER_ISO_B4, PageSize::Millimeter,  709, 1001,   250,   353,   9.84,   13.9,              "ISOB4"},
        {                PageSize::B5,                  DMPAPER_NONE, PageSize::Millimeter,  499,  709,   176,   250,    6.9,    9.8,              "ISOB5"},
        {                PageSize::B6,                  DMPAPER_NONE, PageSize::Millimeter,  354,  499,   125,   176,   4.92,   6.93,              "ISOB6"},
        {                PageSize::B7,                  DMPAPER_NONE, PageSize::Millimeter,  249,  354,    88,   125,   3.46,   4.92,              "ISOB7"},
        {                PageSize::B8,                  DMPAPER_NONE, PageSize::Millimeter,  176,  249,    62,    88,   2.44,   3.46,              "ISOB8"},
        {                PageSize::B9,                  DMPAPER_NONE, PageSize::Millimeter,  125,  176,    44,    62,   1.73,   2.44,              "ISOB9"},
        {               PageSize::B10,                  DMPAPER_NONE, PageSize::Millimeter,   88,  125,    31,    44,   1.22,   1.73,             "ISOB10"},
        {               PageSize::C5E,                DMPAPER_ENV_C5, PageSize::Millimeter,  459,  649,   162,   229,   6.38,   9.02,              "EnvC5"},
        {           PageSize::Comm10E,                DMPAPER_ENV_10,       PageSize::Inch,  297,  684, 104.8, 241.3,   4.12,    9.5,              "Env10"},
        {               PageSize::DLE,                DMPAPER_ENV_DL, PageSize::Millimeter,  312,  624,   110,   220,   4.33,   8.66,              "EnvDL"},
        {             PageSize::Folio,                  DMPAPER_NONE, PageSize::Millimeter,  595,  935,   210,   330,   8.27,     13,              "Folio"},
        {            PageSize::Ledger,                DMPAPER_LEDGER,       PageSize::Inch, 1224,  792, 431.8, 279.4,     17,     11,             "Ledger"},
        {           PageSize::Tabloid,               DMPAPER_TABLOID,       PageSize::Inch,  792, 1224, 279.4, 431.8,     11,     17,            "Tabloid"},
        {            PageSize::Custom,                  DMPAPER_USER, PageSize::Millimeter,   -1,   -1,   -1.,    -1,     -1,     -1,             "Custom"}, 

  // ISO Standard Sizes
        {           PageSize::A3Extra,              DMPAPER_A3_EXTRA, PageSize::Millimeter,  913, 1262,   322,   445,  12.67,  17.52,            "A3Extra"},
        {           PageSize::A4Extra,              DMPAPER_A4_EXTRA, PageSize::Millimeter,  667,  914, 235.5, 322.3,   9.27,  12.69,            "A4Extra"},
        {            PageSize::A4Plus,               DMPAPER_A4_PLUS, PageSize::Millimeter,  595,  936,   210,   330,   8.27,     13,             "A4Plus"},
        {           PageSize::A4Small,               DMPAPER_A4SMALL, PageSize::Millimeter,  595,  842,   210,   297,   8.27,  11.69,            "A4Small"},
        {           PageSize::A5Extra,              DMPAPER_A5_EXTRA, PageSize::Millimeter,  492,  668,   174,   235,   6.85,   9.25,            "A5Extra"},
        {           PageSize::B5Extra,              DMPAPER_B5_EXTRA, PageSize::Millimeter,  570,  782,   201,   276,    7.9,   10.8,         "ISOB5Extra"},

 // JIS Standard Sizes
        {             PageSize::JisB0,                  DMPAPER_NONE, PageSize::Millimeter, 2920, 4127,  1030,  1456,  40.55,  57.32,                 "B0"},
        {             PageSize::JisB1,                  DMPAPER_NONE, PageSize::Millimeter, 2064, 2920,   728,  1030,  28.66,  40.55,                 "B1"},
        {             PageSize::JisB2,                  DMPAPER_NONE, PageSize::Millimeter, 1460, 2064,   515,   728,  20.28,  28.66,                 "B2"},
        {             PageSize::JisB3,                  DMPAPER_NONE, PageSize::Millimeter, 1032, 1460,   364,   515,  14.33,  20.28,                 "B3"},
        {             PageSize::JisB4,                    DMPAPER_B4, PageSize::Millimeter,  729, 1032,   257,   364,  10.12,  14.33,                 "B4"},
        {             PageSize::JisB5,                    DMPAPER_B5, PageSize::Millimeter,  516,  729,   182,   257,   7.17,  10.12,                 "B5"},
        {             PageSize::JisB6,                DMPAPER_B6_JIS, PageSize::Millimeter,  363,  516,   128,   182,   5.04,   7.17,                 "B6"},
        {             PageSize::JisB7,                  DMPAPER_NONE, PageSize::Millimeter,  258,  363,    91,   128,   3.58,   5.04,                 "B7"},
        {             PageSize::JisB8,                  DMPAPER_NONE, PageSize::Millimeter,  181,  258,    64,    91,   2.52,   3.58,                 "B8"},
        {             PageSize::JisB9,                  DMPAPER_NONE, PageSize::Millimeter,  127,  181,    45,    64,   1.77,   2.52,                 "B9"},
        {            PageSize::JisB10,                  DMPAPER_NONE, PageSize::Millimeter,   91,  127,    32,    45,   1.26,   1.77,                "B10"},

 // ANSI / US Standard sizes
        {             PageSize::AnsiC,                  DMPAPER_NONE,       PageSize::Inch, 1224, 1584, 431.8, 558.8,     17,     22,              "AnsiC"},
        {             PageSize::AnsiD,                  DMPAPER_NONE,       PageSize::Inch, 1584, 2448, 558.8, 863.6,     22,     34,              "AnsiD"},
        {             PageSize::AnsiE,                  DMPAPER_NONE,       PageSize::Inch, 2448, 3168, 863.6,  1118,     34,     44,              "AnsiE"},
        {        PageSize::LegalExtra,           DMPAPER_LEGAL_EXTRA,       PageSize::Inch,  684, 1080, 241.3,   381,    9.5,     15,         "LegalExtra"},
        {       PageSize::LetterExtra,          DMPAPER_LETTER_EXTRA,       PageSize::Inch,  684,  864, 241.3, 304.8,    9.5,     12,        "LetterExtra"},
        {        PageSize::LetterPlus,           DMPAPER_LETTER_PLUS,       PageSize::Inch,  612,  914, 215.9, 322.3,    8.5,  12.69,         "LetterPlus"},
        {       PageSize::LetterSmall,           DMPAPER_LETTERSMALL,       PageSize::Inch,  612,  792, 215.9, 279.4,    8.5,     11,        "LetterSmall"},
        {      PageSize::TabloidExtra,         DMPAPER_TABLOID_EXTRA,       PageSize::Inch,  864, 1296, 304.8, 457.2,     12,     18,       "TabloidExtra"},

 // Architectural sizes
        {             PageSize::ArchA,                  DMPAPER_NONE,       PageSize::Inch,  648,  864, 228.6, 304.8,      9,     12,              "ARCHA"},
        {             PageSize::ArchB,                  DMPAPER_NONE,       PageSize::Inch,  864, 1296, 304.8, 457.2,     12,     18,              "ARCHB"},
        {             PageSize::ArchC,                DMPAPER_CSHEET,       PageSize::Inch, 1296, 1728, 457.2, 609.6,     18,     24,              "ARCHC"},
        {             PageSize::ArchD,                DMPAPER_DSHEET,       PageSize::Inch, 1728, 2592, 609.6, 914.4,     24,     36,              "ARCHD"},
        {             PageSize::ArchE,                DMPAPER_ESHEET,       PageSize::Inch, 2592, 3456, 914.4,  1219,     36,     48,              "ARCHE"},

 // Inch-based Sizes
        {       PageSize::Imperial7x9,                  DMPAPER_NONE,       PageSize::Inch,  504,  648, 177.8, 228.6,      7,      9,                "7x9"},
        {      PageSize::Imperial8x10,                  DMPAPER_NONE,       PageSize::Inch,  576,  720, 203.2,   254,      8,     10,               "8x10"},
        {      PageSize::Imperial9x11,                  DMPAPER_9X11,       PageSize::Inch,  648,  792, 228.6, 279.4,      9,     11,               "9x11"},
        {      PageSize::Imperial9x12,                  DMPAPER_NONE,       PageSize::Inch,  648,  864, 228.6, 304.8,      9,     12,               "9x12"},
        {     PageSize::Imperial10x11,                 DMPAPER_10X11,       PageSize::Inch,  720,  792,   254, 279.4,     10,     11,              "10x11"},
        {     PageSize::Imperial10x13,                  DMPAPER_NONE,       PageSize::Inch,  720,  936,   254, 330.2,     10,     13,              "10x13"},
        {     PageSize::Imperial10x14,                 DMPAPER_10X14,       PageSize::Inch,  720, 1008,   254, 355.6,     10,     14,              "10x14"},
        {     PageSize::Imperial12x11,                 DMPAPER_12X11,       PageSize::Inch,  864,  792, 304.8, 279.4,     12,     11,              "12x11"},
        {     PageSize::Imperial15x11,                 DMPAPER_15X11,       PageSize::Inch, 1080,  792,   381, 279.4,     15,     11,              "15x11"},

 // Other Page Sizes
        { PageSize::ExecutiveStandard,             DMPAPER_EXECUTIVE,       PageSize::Inch,  522,  756, 184.2, 266.7,   7.25,   10.5,          "Executive"},
        {              PageSize::Note,                  DMPAPER_NOTE,       PageSize::Inch,  612,  792, 215.9, 279.4,    8.5,     11,               "Note"},
        {            PageSize::Quarto,                DMPAPER_QUARTO,       PageSize::Inch,  610,  780, 215.9, 275.1,    8.5,  10.83,             "Quarto"},
        {         PageSize::Statement,             DMPAPER_STATEMENT,       PageSize::Inch,  396,  612, 139.7, 215.9,    5.5,    8.5,          "Statement"},
        {            PageSize::SuperA,                DMPAPER_A_PLUS, PageSize::Millimeter,  643, 1009,   227,   356,   8.94,     14,             "SuperA"},
        {            PageSize::SuperB,                DMPAPER_B_PLUS, PageSize::Millimeter,  864, 1380,   305,   487,     12,  19.17,             "SuperB"},
        {          PageSize::Postcard,     DMPAPER_JAPANESE_POSTCARD, PageSize::Millimeter,  284,  419,   100,   148,   3.94,   5.83,           "Postcard"},
        {    PageSize::DoublePostcard, DMPAPER_DBL_JAPANESE_POSTCARD, PageSize::Millimeter,  567,  419,   200,   148,   7.87,   5.83,     "DoublePostcard"},
        {            PageSize::Prc16K,                  DMPAPER_P16K, PageSize::Millimeter,  414,  610,   146,   215,   5.75,    8.5,             "PRC16K"},
        {            PageSize::Prc32K,                  DMPAPER_P32K, PageSize::Millimeter,  275,  428,    97,   151,   3.82,   5.95,             "PRC32K"},
        {         PageSize::Prc32KBig,               DMPAPER_P32KBIG, PageSize::Millimeter,  275,  428,    97,   151,   3.82,   5.95,          "PRC32KBig"},

 // Fan Fold Sizes
        {         PageSize::FanFoldUS,            DMPAPER_FANFOLD_US,       PageSize::Inch, 1071,  792, 377.8, 279.4, 14.875,     11,          "FanFoldUS"},
        {     PageSize::FanFoldGerman,    DMPAPER_FANFOLD_STD_GERMAN,       PageSize::Inch,  612,  864, 215.9, 304.8,    8.5,     12,      "FanFoldGerman"},
        {PageSize::FanFoldGermanLegal,    DMPAPER_FANFOLD_LGL_GERMAN,       PageSize::Inch,  612,  936, 215.9,   330,    8.5,     13, "FanFoldGermanLegal"},

 // ISO Envelopes
        {        PageSize::EnvelopeB4,                DMPAPER_ENV_B4, PageSize::Millimeter,  708, 1001,   250,   353,   9.84,   13.9,           "EnvISOB4"},
        {        PageSize::EnvelopeB5,                DMPAPER_ENV_B5, PageSize::Millimeter,  499,  709,   176,   250,    6.9,    9.8,           "EnvISOB5"},
        {        PageSize::EnvelopeB6,                DMPAPER_ENV_B6, PageSize::Millimeter,  499,  354,   176,   125,    6.9,    4.9,           "EnvISOB6"},
        {        PageSize::EnvelopeC0,                  DMPAPER_NONE, PageSize::Millimeter, 2599, 3676,   917,  1297,   36.1,  51.06,              "EnvC0"},
        {        PageSize::EnvelopeC1,                  DMPAPER_NONE, PageSize::Millimeter, 1837, 2599,   648,   917,  25.51,   36.1,              "EnvC1"},
        {        PageSize::EnvelopeC2,                  DMPAPER_NONE, PageSize::Millimeter, 1298, 1837,   458,   648,  18.03,  25.51,              "EnvC2"},
        {        PageSize::EnvelopeC3,                DMPAPER_ENV_C3, PageSize::Millimeter,  918, 1296,   324,   458,  12.75,  18.03,              "EnvC3"},
        {        PageSize::EnvelopeC4,                DMPAPER_ENV_C4, PageSize::Millimeter,  649,  918,   229,   324,   9.02,  12.75,              "EnvC4"},
        {        PageSize::EnvelopeC6,                DMPAPER_ENV_C6, PageSize::Millimeter,  323,  459,   114,   162,   4.49,   6.38,              "EnvC6"},
        {       PageSize::EnvelopeC65,               DMPAPER_ENV_C65, PageSize::Millimeter,  324,  648,   114,   229,    4.5,      9,             "EnvC65"},
        {        PageSize::EnvelopeC7,                  DMPAPER_NONE, PageSize::Millimeter,  230,  323,    81,   114,   3.19,   4.49,              "EnvC7"},

 // US Envelopes
        {         PageSize::Envelope9,                 DMPAPER_ENV_9,       PageSize::Inch,  279,  639,  98.4, 225.4,  3.875,  8.875,               "Env9"},
        {        PageSize::Envelope11,                DMPAPER_ENV_11,       PageSize::Inch,  324,  747, 114.3, 263.5,    4.5, 10.375,              "Env11"},
        {        PageSize::Envelope12,                DMPAPER_ENV_12,       PageSize::Inch,  342,  792, 120.7, 279.4,   4.75,     11,              "Env12"},
        {        PageSize::Envelope14,                DMPAPER_ENV_14,       PageSize::Inch,  360,  828,   127, 292.1,      5,   11.5,              "Env14"},
        {   PageSize::EnvelopeMonarch,           DMPAPER_ENV_MONARCH,       PageSize::Inch,  279,  540, 98.43, 190.5,  3.875,    7.5,         "EnvMonarch"},
        {  PageSize::EnvelopePersonal,          DMPAPER_ENV_PERSONAL,       PageSize::Inch,  261,  468, 92.08, 165.1,  3.625,    6.5,        "EnvPersonal"},

 // Other Envelopes
        {     PageSize::EnvelopeChou3,            DMPAPER_JENV_CHOU3, PageSize::Millimeter,  340,  666,   120,   235,   4.72,   9.25,           "EnvChou3"},
        {     PageSize::EnvelopeChou4,            DMPAPER_JENV_CHOU4, PageSize::Millimeter,  255,  581,    90,   205,   3.54,      8,           "EnvChou4"},
        {    PageSize::EnvelopeInvite,            DMPAPER_ENV_INVITE, PageSize::Millimeter,  624,  624,   220,   220,   8.66,   8.66,          "EnvInvite"},
        {   PageSize::EnvelopeItalian,             DMPAPER_ENV_ITALY, PageSize::Millimeter,  312,  652,   110,   230,   4.33,      9,         "EnvItalian"},
        {     PageSize::EnvelopeKaku2,            DMPAPER_JENV_KAKU2, PageSize::Millimeter,  680,  941,   240,   332,   9.45,     13,           "EnvKaku2"},
        {     PageSize::EnvelopeKaku3,            DMPAPER_JENV_KAKU3, PageSize::Millimeter,  612,  785,   216,   277,    8.5,   10.9,           "EnvKaku3"},
        {      PageSize::EnvelopePrc1,                DMPAPER_PENV_1, PageSize::Millimeter,  289,  468,   102,   165,      4,    6.5,            "EnvPRC1"},
        {      PageSize::EnvelopePrc2,                DMPAPER_PENV_2, PageSize::Millimeter,  289,  499,   102,   176,      4,    6.9,            "EnvPRC2"},
        {      PageSize::EnvelopePrc3,                DMPAPER_PENV_3, PageSize::Millimeter,  354,  499,   125,   176,    4.9,    6.9,            "EnvPRC3"},
        {      PageSize::EnvelopePrc4,                DMPAPER_PENV_4, PageSize::Millimeter,  312,  590,   110,   208,   4.33,    8.2,            "EnvPRC4"},
        {      PageSize::EnvelopePrc5,                DMPAPER_PENV_5, PageSize::Millimeter,  312,  624,   110,   220,   4.33,   8.66,            "EnvPRC5"},
        {      PageSize::EnvelopePrc6,                DMPAPER_PENV_6, PageSize::Millimeter,  340,  652,   120,   230,    4.7,      9,            "EnvPRC6"},
        {      PageSize::EnvelopePrc7,                DMPAPER_PENV_7, PageSize::Millimeter,  454,  652,   160,   230,    6.3,      9,            "EnvPRC7"},
        {      PageSize::EnvelopePrc8,                DMPAPER_PENV_8, PageSize::Millimeter,  340,  876,   120,   309,    4.7,   12.2,            "EnvPRC8"},
        {      PageSize::EnvelopePrc9,                DMPAPER_PENV_9, PageSize::Millimeter,  649,  918,   229,   324,      9,  12.75,            "EnvPRC9"},
        {     PageSize::EnvelopePrc10,               DMPAPER_PENV_10, PageSize::Millimeter,  918, 1298,   324,   458,  12.75,     18,           "EnvPRC10"},
        {      PageSize::EnvelopeYou4,             DMPAPER_JENV_YOU4, PageSize::Millimeter,  298,  666,   105,   235,   4.13,   9.25,            "EnvYou4"}
};

// clang-format on

/*******************************************************************************
 * PageSize static functions
 *******************************************************************************/

static const int pageSizesCount =
        int(sizeof(m2_pageSizes) / sizeof(m2_pageSizes[0]));
static_assert(pageSizesCount == PageSize::LastPageSize + 1);
static_assert(PageSize::LastPageSize < 256);

static String m2_keyForPageSizeId(PageSize::PageSizeId id);

static PageSize::PageSizeId m2_idForPpdKey(const String &ppdKey,
                                           Size *match = nullptr);

static PageSize::PageSizeId m2_idForWindowsID(int windowsId,
                                              Size *match = nullptr);

static String m2_keyForCustomSize(const SizeF &size, PageSize::Unit units);

static String m2_nameForCustomSize(const SizeF &size, PageSize::Unit units);

static double m2_pointMultiplier(PageSize::Unit unit);

double m2_pixelMultiplier(int resolution);

static SizeF m2_definitionSize(PageSize::PageSizeId pageSizeId);

static SizeF m2_convertUnits(const SizeF &size, PageSize::Unit fromUnits,
                             PageSize::Unit toUnits);

static Size m2_convertUnitsToPoints(const SizeF &size, PageSize::Unit units);

static Size m2_convertPointsToPixels(const Size &size, int resolution);

static SizeF m2_convertPointsToUnits(const Size &size, PageSize::Unit units);

static SizeF m2_unitSize(PageSize::PageSizeId pageSizeId, PageSize::Unit units);

static PageSize::PageSizeId
m2_idForPointSize(const Size &size, PageSize::SizeMatchPolicy matchPolicy,
                  Size *match);

static PageSize::PageSizeId m2_idForSize(const SizeF &size,
                                         PageSize::Unit units,
                                         PageSize::SizeMatchPolicy matchPolicy,
                                         Size *match);


/*******************************************************************************
 * class PageSizePrivate
 *******************************************************************************/

class PageSizePrivate
{
public:
    PageSizePrivate();
    explicit PageSizePrivate(PageSize::PageSizeId pageSizeId);
    PageSizePrivate(const Size &pointSize, const String &name,
                    PageSize::SizeMatchPolicy matchPolicy);
    PageSizePrivate(const SizeF &size, PageSize::Unit units, const String &name,
                    PageSize::SizeMatchPolicy matchPolicy);
    PageSizePrivate(const String &key, const Size &size, const String &name);
    PageSizePrivate(int windowsId, const Size &pointSize, const String &name);
    ~PageSizePrivate();

    bool operator==(const PageSizePrivate &other) const;
    bool isEquivalentTo(const PageSizePrivate &other) const;

    bool isValid() const;

    SizeF size(PageSize::Unit units) const;
    Size sizePixels(int resolution) const;

private:
    friend class PageSize;

    void init(PageSize::PageSizeId id, const String &name);
    void init(const Size &size, const String &name);
    void init(const SizeF &size, PageSize::Unit units, const String &name);

    String m_key;
    PageSize::PageSizeId m_id;
    Size m_pointSize;
    String m_name;
    int m_windowsId;
    SizeF m_size;
    PageSize::Unit m_units;
};

/*******************************************************************************
 * class PageSizePrivate functions
 *******************************************************************************/

PageSizePrivate::PageSizePrivate() {}

PageSizePrivate::PageSizePrivate(PageSize::PageSizeId pageSizeId) {}

PageSizePrivate::PageSizePrivate(const Size &pointSize, const String &name,
                                 PageSize::SizeMatchPolicy matchPolicy)
{
}

PageSizePrivate::PageSizePrivate(const SizeF &size, PageSize::Unit units,
                                 const String &name,
                                 PageSize::SizeMatchPolicy matchPolicy)
{
}

PageSizePrivate::PageSizePrivate(const String &key, const Size &size,
                                 const String &name)
{
}

PageSizePrivate::PageSizePrivate(int windowsId, const Size &pointSize,
                                 const String &name)
{
}

PageSizePrivate::~PageSizePrivate() {}

bool PageSizePrivate::operator==(const PageSizePrivate &other) const
{
    return false;
}

bool PageSizePrivate::isEquivalentTo(const PageSizePrivate &other) const
{
    return false;
}

bool PageSizePrivate::isValid() const { return false; }

SizeF PageSizePrivate::size(PageSize::Unit units) const { return SizeF(); }

Size PageSizePrivate::sizePixels(int resolution) const { return Size(); }

void PageSizePrivate::init(PageSize::PageSizeId id, const String &name) {}

void PageSizePrivate::init(const Size &size, const String &name) {}

void PageSizePrivate::init(const SizeF &size, PageSize::Unit units,
                           const String &name)
{
}

/*******************************************************************************
 * class PageSize functions
 *******************************************************************************/

PageSize::PageSize() {}

PageSize::PageSize(PageSizeId pageSizeId) {}

PageSize::PageSize(const Size &pointSize, const String &name,
                   SizeMatchPolicy matchPolicy)
{
}

PageSize::PageSize(const SizeF &size, Unit units, const String &name,
                   SizeMatchPolicy matchPolicy)
{
}

PageSize::PageSize(const PageSize &other) {}

PageSize &PageSize::operator=(const PageSize &other)
{
    // TODO: insert return statement here
}

PageSize::~PageSize() {}

void PageSize::swap(PageSize &other) noexcept {}

bool PageSize::isEquivalentTo(const PageSize &other) const { return false; }

bool PageSize::isValid() const { return false; }

String PageSize::key() const { return String(); }

String PageSize::name() const { return String(); }

PageSize::PageSizeId PageSize::id() const { return PageSizeId(); }

int PageSize::windowsId() const { return 0; }

SizeF PageSize::definitionSize() const { return SizeF(); }

PageSize::Unit PageSize::definitionUnits() const { return Unit(); }

SizeF PageSize::size(Unit units) const { return SizeF(); }

Size PageSize::sizePoints() const { return Size(); }

Size PageSize::sizePixels(int resolution) const { return Size(); }

String PageSize::key(PageSizeId pageSizeId) { return String(); }

String PageSize::name(PageSizeId pageSizeId) { return String(); }

PageSize::PageSizeId PageSize::id(const Size &pointSize,
                                  SizeMatchPolicy matchPolicy)
{
    return PageSizeId();
}

PageSize::PageSizeId PageSize::id(const SizeF &size, Unit units,
                                  SizeMatchPolicy matchPolicy)
{
    return PageSizeId();
}

PageSize::PageSizeId PageSize::id(int windowsId) { return PageSizeId(); }

int PageSize::windowsId(PageSizeId pageSizeId) { return 0; }

SizeF PageSize::definitionSize(PageSizeId pageSizeId) { return SizeF(); }

PageSize::Unit PageSize::definitionUnits(PageSizeId pageSizeId)
{
    return Unit();
}

SizeF PageSize::size(PageSizeId pageSizeId, Unit units) { return SizeF(); }

Size PageSize::sizePoints(PageSizeId pageSizeId) { return Size(); }

Size PageSize::sizePixels(PageSizeId pageSizeId, int resolution)
{
    return Size();
}

bool PageSize::equals(const PageSize &other) const { return false; }


/*******************************************************************************
 * PageSize static function definations
 *******************************************************************************/

String m2_keyForPageSizeId(PageSize::PageSizeId id) { return String(); }

PageSize::PageSizeId m2_idForPpdKey(const String &ppdKey, Size *match)
{
    return PageSize::PageSizeId();
}

PageSize::PageSizeId m2_idForWindowsID(int windowsId, Size *match)
{
    return PageSize::PageSizeId();
}

String m2_keyForCustomSize(const SizeF &size, PageSize::Unit units)
{
    return String();
}

String m2_nameForCustomSize(const SizeF &size, PageSize::Unit units)
{
    return String();
}

double m2_pointMultiplier(PageSize::Unit unit) { return 0.0; }

double m2_pixelMultiplier(int resolution) { return 0.0; }

SizeF m2_definitionSize(PageSize::PageSizeId pageSizeId) { return SizeF(); }

SizeF m2_convertUnits(const SizeF &size, PageSize::Unit fromUnits,
                      PageSize::Unit toUnits)
{
    return SizeF();
}

Size m2_convertUnitsToPoints(const SizeF &size, PageSize::Unit units)
{
    return Size();
}

Size m2_convertPointsToPixels(const Size &size, int resolution)
{
    return Size();
}

SizeF m2_convertPointsToUnits(const Size &size, PageSize::Unit units)
{
    return SizeF();
}

SizeF m2_unitSize(PageSize::PageSizeId pageSizeId, PageSize::Unit units)
{
    return SizeF();
}

PageSize::PageSizeId m2_idForPointSize(const Size &size,
                                       PageSize::SizeMatchPolicy matchPolicy,
                                       Size *match)
{
    return PageSize::PageSizeId();
}

PageSize::PageSizeId m2_idForSize(const SizeF &size, PageSize::Unit units,
                                  PageSize::SizeMatchPolicy matchPolicy,
                                  Size *match)
{
    return PageSize::PageSizeId();
}

}// namespace m2
