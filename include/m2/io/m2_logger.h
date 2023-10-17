/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#ifndef M2_LOGGER_H_
#define M2_LOGGER_H_

#include <fstream>
#include <m2_string.h>

namespace m2 {

enum LogLevel
{
    eLOGALL = -99999,
    eLOGNONE = 99999,
    eLOGTRACE = -100,
    eLOGDEBUG = 0,
    eLOGINFO = 100,
    eLOGWARN = 200,
    eLOGERROR = 300,
    eLOGFATAL = 400,

};

class M2_API LogOutput
{
public:
    ~LogOutput() {}
    virtual bool OnLog(const char *log) = 0;
    virtual void OnFlush() {}
};

class M2_API FileLogOutput : public LogOutput
{
    std::ofstream m_file;
    bool m_ShowInConsole;

public:
    virtual bool OnLog(const char *log);
    virtual void OnFlush();
    FileLogOutput(const char *strFileName, bool bAppend = false,
                  bool ShowInConsole = false);
};

class M2_API Logger
{
    String m_strName;
    LogOutput *m_pHook;
    volatile bool m_AutoFlush;
    volatile LogLevel m_nLevel;

    class M2_API LogStream : public std::stringstream
    {
        Logger &m_Log;
        bool m_bEnable;
        LogLevel m_nLevel;

    public:
        LogStream(const LogStream &rhs);
        LogStream(Logger &log, LogLevel l, bool bEnable);
        virtual ~LogStream();
    };

public:
    Logger();
    Logger(const char *strLogName);
    static void addGlobalLogger(Logger *logger, unsigned long long nUniqueKey,
                                bool bManagePointer = false);
    static Logger &globalLogger(unsigned long long nUniqueKey);
    static Logger *removeGlobalLogger(unsigned long long nUniqueKey);
    static bool isDebuging();

    String lastError();
    LogLevel logLevel(LogLevel l);
    LogLevel logLevel();
    LogOutput *CustomOutput(LogOutput *pOutput);
    LogOutput *CustomOutput();
    String mame() const;
    virtual ~Logger();
    bool autoFlush();
    void setAutoFlush(bool b);
    void log(LogLevel l, const char *log);
    static Logger &instance();
    LogStream operator<<(const LogLevel &l) const;
};

// clang-format off

/// @brief 全局日志对象各级别宏定义
#define GSLOG				m2::Logger::instance()
#define GS_FILE_LINE_FUNCTION " [" << __FILE__ << ":" << __LINE__ << "](" << __FUNCTION__ << ") "

#define GSLOG_ERROR			m2::Logger::instance() << m2::eLOGERROR << GS_FILE_LINE_FUNCTION
#define GS_E				m2::Logger::instance() << m2::eLOGERROR << GS_FILE_LINE_FUNCTION

#define GSLOG_TRACE			m2::Logger::instance() << m2::eLOGTRACE << GS_FILE_LINE_FUNCTION
#define GS_T				m2::Logger::instance() << m2::eLOGTRACE << GS_FILE_LINE_FUNCTION

#define GSLOG_DEBUG			m2::Logger::instance() << m2::eLOGDEBUG << GS_FILE_LINE_FUNCTION
#define GS_D				m2::Logger::instance() << m2::eLOGDEBUG << GS_FILE_LINE_FUNCTION

#define GSLOG_INFO			m2::Logger::instance() << m2::eLOGINFO
#define GS_I				m2::Logger::instance() << m2::eLOGINFO

#define GSLOG_WARN			m2::Logger::instance() << m2::eLOGWARN
#define GS_W				m2::Logger::instance() << m2::eLOGWARN

#define GSLOG_FATAL			m2::Logger::instance() << m2::eLOGFATAL
#define GS_F				m2::Logger::instance() << m2::eLOGFATAL

// clang-format on

}// namespace m2

#endif//M2_LOGGER_H_