﻿/****************************************************************************
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

#pragma once

#include "preconfig.h"
#include "stringhelp.h"
#include <fstream>

namespace m2 {

/// @brief 日志级别
enum GsLogLevel
{
    eLOGALL = -99999,//!< 所有日志全部记录
    eLOGNONE = 99999,//!< 所有日志都不记录
    eLOGTRACE = -100,//!< 记录追踪日志
    eLOGDEBUG = 0,   //!< 记录调试日志
    eLOGINFO = 100,  //!< 记录基本信息
    eLOGWARN = 200,  //!< 记录警告
    eLOGERROR = 300, //!< 记录普通错误
    eLOGFATAL = 400, //!< 记录致命错误

};

/// @brief 自定义的输出管道
class M2_API GsCustomLogOutput
{
public:
    ~GsCustomLogOutput() {}

    /// @brief
    /// @param log
    /// @return
    virtual bool OnLog(const char *log) = 0;
    /// @brief
    virtual void OnFlush(){};
};

/// @brief 将日志输出到文件
class M2_API GsFileCustomLogOutput : public GsCustomLogOutput
{
    std::ofstream m_file;
    bool m_ShowInConsole;

public:
    /// @brief
    /// @param log
    /// @return
    virtual bool OnLog(const char *log);
    /// @brief
    virtual void OnFlush();
    /// @brief
    /// @param strFileName
    /// @param bAppend
    /// @param ShowInConsole
    GsFileCustomLogOutput(const char *strFileName, bool bAppend = false, bool ShowInConsole = false);
};

/// @brief 创建日志
class M2_API GsLogger
{
    GsString m_strName;
    GsCustomLogOutput *m_pHook;
    volatile bool m_AutoFlush;

    volatile GsLogLevel m_nLevel;
    /// @brief 日志流操作
    class M2_API GsLogStream : public Utility::GsStringStream
    {
        GsLogger &m_Log;
        bool m_bEnable;
        GsLogLevel m_nLevel;

    public:
        GsLogStream(const GsLogStream &rhs);
        GsLogStream(GsLogger &log, GsLogLevel l, bool bEnable);
        virtual ~GsLogStream();
    };


public:
    /// @brief 构造函数
    GsLogger();
    /// @brief
    /// @param strLogName
    GsLogger(const char *strLogName);


    /// @brief 以数字型的唯一Key添加一个全局日志
    /// @param logger 要添加的日志指针
    /// @param nUniqueKey 日志的唯一Key，用于获取日志的标识
    /// @param bManagePointer 是否系统管理日志指针，如果为true,那么系统退出时会自动删除日志
    static void AddGlobalLogger(GsLogger *logger, unsigned long long nUniqueKey, bool bManagePointer = false);

    /// @brief 获取全局日志，如果根据key无法获取，那么返回缺省日志
    /// @param nUniqueKey
    /// @return
    static GsLogger &GlobalLogger(unsigned long long nUniqueKey);

    /// @brief 从全局换从移除日志，返回日志的指针
    /// @param nUniqueKey
    /// @return
    static GsLogger *RemoveGlobalLogger(unsigned long long nUniqueKey);

    /// @brief 判断当前程序是否运行在调试状态
    /// @details 仅仅对于windows平台下Visual Studio中调试状态有效，其他情况下一律返回false
    /// @return
    static bool IsDebuging();

    /// @brief 最后报告的错误
    /// @return
    GsString LastError();
    /// @brief 设置日志级别
    /// @param l
    /// @return
    GsLogLevel LogLevel(GsLogLevel l);
    /// @brief 获得日志级别
    /// @return
    GsLogLevel LogLevel();
    /// @brief 自定义输出
    /// @param pOutput
    /// @return
    GsCustomLogOutput *CustomOutput(GsCustomLogOutput *pOutput);
    /// @brief
    /// @return
    GsCustomLogOutput *CustomOutput();
    /// @brief 获取日志名
    /// @return
    GsString Name() const;
    /// @brief 虚析构函数
    virtual ~GsLogger();
    /// @brief 日志操作后输出流是否刷新
    /// @return 返回true表示刷新，否则，不刷新
    bool AutoFlush();

    /// @brief 日志操作后输出流是否刷新
    /// @return 返回true表示刷新，否则，不刷新
    /// @param b
    void AutoFlush(bool b);


    /// @brief 报告一段日志
    /// @param l
    /// @param log
    void Log(GsLogLevel l, const char *log);
    /// @brief 缺省的日志对象
    static GsLogger &Default();
    /// @brief 输出日志
    GsLogStream operator<<(const GsLogLevel &l) const;
};

// clang-format off

/// @brief 全局日志对象各级别宏定义
#define GSLOG				Lite::Utility::GsLogger::Default()
#define GS_FILE_LINE_FUNCTION " [" << __FILE__ << ":" << __LINE__ << "](" << __FUNCTION__ << ") "

#define GSLOG_ERROR			Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGERROR << GS_FILE_LINE_FUNCTION
#define GS_E				Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGERROR << GS_FILE_LINE_FUNCTION

#define GSLOG_TRACE			Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGTRACE << GS_FILE_LINE_FUNCTION
#define GS_T				Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGTRACE << GS_FILE_LINE_FUNCTION

#define GSLOG_DEBUG			Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGDEBUG << GS_FILE_LINE_FUNCTION
#define GS_D				Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGDEBUG << GS_FILE_LINE_FUNCTION

#define GSLOG_INFO			Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGINFO
#define GS_I				Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGINFO

#define GSLOG_WARN			Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGWARN
#define GS_W				Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGWARN

#define GSLOG_FATAL			Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGFATAL
#define GS_F				Lite::Utility::GsLogger::Default()<<Lite::Utility::eLOGFATAL


// clang-format on


}// namespace m2
