/*

          -[ Simple Logger Lib ]-

                version 0.1

  https://github.com/ShnurD6/SimpleLoggerLib

 */


#pragma once
#include <string>
#include <fstream>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/format.hpp>

using namespace std::string_literals;

struct Logger
{
    enum class LogType
    {
        Debug, ///< Message go to std::cout if Target=OutputStream
        Error  ///< Message prefixed by '[!]' and go to std::cerr if Target=OutputStream
    };

    /// Simple log with type /see LogType
    void Log(const std::string& aComponentName,
             const std::string& aNewLog,
             LogType aLogType);

    Logger();
    ~Logger();

private:

    static constexpr auto mTargetEnvVar = "SWS_LOG_TARGET";

    enum class Target
    {
        File,        ///< Logging to a file log.txt
        OutputStream ///< Logging to std::cout/std::cerr
    };

    Target mTarget{Target::File};

    void SetTargetFromEnv();

    std::fstream mLogFile;
};

static Logger& GetLogger()
{
    static Logger object;
    return object;
}

/// Use
struct LoggerInstance
{
    template <typename T>
    LoggerInstance(T&& aComponentName)
        : mComponentName(std::forward<T>(aComponentName))
        , mLogger(GetLogger())
    {
    }

    /// Call Log with LogType=Debug /see Logger::LogType
    void DebugLog(const std::string& aNewLog) const;

    /// Call Log with LogType=Error /see Logger::LogType
    void ErrorLog(const std::string& aNewLog) const;

private:
    std::string mComponentName;
    Logger& mLogger;
};
