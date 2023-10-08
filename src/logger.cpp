#include <logger.h>

namespace m2 {

/************************************ GsFileCustomLogOutput ************************************/

bool GsFileCustomLogOutput::OnLog(const char *log)
{
    return false;
}

void GsFileCustomLogOutput::OnFlush()
{
}

GsFileCustomLogOutput::GsFileCustomLogOutput(const char *strFileName, bool bAppend,
                                             bool ShowInConsole)
{
}

/************************************ GsLogStream ************************************/

GsLogger::GsLogStream::GsLogStream(const GsLogStream &rhs) : m_Log(rhs.m_Log)
{
}

GsLogger::GsLogStream::GsLogStream(GsLogger &log, GsLogLevel l, bool bEnable)
    : m_Log(log), m_nLevel(l), m_bEnable(bEnable)
{
}

GsLogger::GsLogStream::~GsLogStream()
{
}


/************************************ GsLogger ************************************/


GsLogger::GsLogger()
{
}

GsLogger::GsLogger(const char *strLogName)
{
}

void GsLogger::AddGlobalLogger(GsLogger *logger, unsigned long long nUniqueKey, bool bManagePointer)
{
}

GsLogger &GsLogger::GlobalLogger(unsigned long long nUniqueKey)
{
    // TODO: insert return statement here
}

GsLogger *GsLogger::RemoveGlobalLogger(unsigned long long nUniqueKey)
{
    return nullptr;
}

bool GsLogger::IsDebuging()
{
    return false;
}

GsString GsLogger::LastError()
{
    return GsString();
}

GsLogLevel GsLogger::LogLevel(GsLogLevel l)
{
    return GsLogLevel();
}

GsLogLevel GsLogger::LogLevel()
{
    return GsLogLevel();
}

GsCustomLogOutput *GsLogger::CustomOutput(GsCustomLogOutput *pOutput)
{
    return nullptr;
}

GsCustomLogOutput *GsLogger::CustomOutput()
{
    return nullptr;
}

GsString GsLogger::Name() const
{
    return GsString();
}

GsLogger::~GsLogger()
{
}

bool GsLogger::AutoFlush()
{
    return false;
}

void GsLogger::AutoFlush(bool b)
{
}

void GsLogger::Log(GsLogLevel l, const char *log)
{
}

GsLogger &GsLogger::Default()
{
    // TODO: insert return statement here
}

GsLogger::GsLogStream GsLogger::operator<<(const GsLogLevel &l) const
{
    return GsLogStream(std::remove_cv_t<GsLogger &>(*this), l, true);
}


}// namespace m2
