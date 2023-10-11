#include <logger.h>

namespace m2 {

/************************************ FileCustomLogOutput ************************************/

bool FileCustomLogOutput::OnLog(const char *log)
{
    return false;
}

void FileCustomLogOutput::OnFlush()
{
}

FileCustomLogOutput::FileCustomLogOutput(const char *strFileName, bool bAppend,
                                             bool ShowInConsole)
{
}

/************************************ LogStream ************************************/

Logger::LogStream::LogStream(const LogStream &rhs) : m_Log(rhs.m_Log)
{
}

Logger::LogStream::LogStream(Logger &log, LogLevel l, bool bEnable)
    : m_Log(log), m_nLevel(l), m_bEnable(bEnable)
{
}

Logger::LogStream::~LogStream()
{
}


/************************************ Logger ************************************/


Logger::Logger()
{
}

Logger::Logger(const char *strLogName)
{
}

void Logger::AddGlobalLogger(Logger *logger, unsigned long long nUniqueKey, bool bManagePointer)
{
}

Logger &Logger::GlobalLogger(unsigned long long nUniqueKey)
{
    // TODO: insert return statement here
}

Logger *Logger::RemoveGlobalLogger(unsigned long long nUniqueKey)
{
    return nullptr;
}

bool Logger::IsDebuging()
{
    return false;
}

String Logger::LastError()
{
    return String();
}

LogLevel Logger::LogLevel(LogLevel l)
{
    return LogLevel();
}

LogLevel Logger::LogLevel()
{
    return LogLevel();
}

CustomLogOutput *Logger::CustomOutput(CustomLogOutput *pOutput)
{
    return nullptr;
}

CustomLogOutput *Logger::CustomOutput()
{
    return nullptr;
}

String Logger::Name() const
{
    return String();
}

Logger::~Logger()
{
}

bool Logger::AutoFlush()
{
    return false;
}

void Logger::AutoFlush(bool b)
{
}

void Logger::Log(LogLevel l, const char *log)
{
}

Logger &Logger::Default()
{
    // TODO: insert return statement here
}

Logger::LogStream Logger::operator<<(const LogLevel &l) const
{
    return LogStream(std::remove_cv_t<Logger &>(*this), l, true);
}


}// namespace m2
