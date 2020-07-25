#include "Logger.hpp"

void Logger::Log(const std::string &aComponentName, const std::string &aNewLog, Logger::LogType aLogType)
{
    const auto log = (boost::format("%s:%s [%s] %s\n")
        % boost::posix_time::second_clock::local_time()
        % (aLogType == LogType::Error ? " [!]" : "")
        % aComponentName
        % aNewLog);

    switch (mTarget)
    {
        case Target::File:
            mLogFile << log;
            break;
        case Target::OutputStream:
        {
            switch (aLogType)
            {
                case LogType::Debug:
                    std::cout << log;
                    break;
                case LogType::Error:
                    std::cerr << log;
                    break;
                default:
                    assert(false && "Unknown LogType");
                    break;
            }
            break;
        }
        default:
            assert(false && "Unknown logTarget");
            break;
    }
}

void LoggerInstance::DebugLog(const std::string &aNewLog) const
{
    mLogger.Log(mComponentName, aNewLog, Logger::LogType::Debug);
}

void LoggerInstance::ErrorLog(const std::string &aNewLog) const
{
    mLogger.Log(mComponentName, aNewLog, Logger::LogType::Error);
}

Logger::Logger()
{
    SetVarsFromEnv();

    bool needLineBreak = mTarget == Target::File;

    const auto initialLog = (boost::format("%s=== Begin session %s ===\n")
        % (needLineBreak ? "\n" : "")
        % boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time())).str();

    switch (mTarget)
    {
        case Target::File:
            mLogFile.open(mFileName, std::fstream::app);
            mLogFile << initialLog;
            break;
        case Target::OutputStream:
            std::cout << initialLog;
            break;
        default:
            assert(false && "Unknown logTarget");
            break;
    }
}

Logger::~Logger()
{
    switch (mTarget)
    {
        case Target::File:
            mLogFile.close();
            break;
        case Target::OutputStream:
            break;
        default:
            assert(false && "Unknown logTarget");
            break;
    }
}

void Logger::SetVarsFromEnv()
{
    const auto targetStr = std::getenv(mTargetEnvVar);
    const auto fileNameStr = std::getenv(mFileNameEnvVar);

    if (fileNameStr)
        mFileName = fileNameStr;

    if (targetStr)
    {
        if (targetStr == "File"s)
            mTarget = Target::File;
        else if (targetStr == "OutputStream"s)
            mTarget = Target::OutputStream;
    }
}