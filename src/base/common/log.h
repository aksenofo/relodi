/*
 *  Created on: March 9, 2022
 *      Author: Alexander Ksenofontov
 */

#pragma once

#include <atomic>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <singleton.h>
#include <sstream>
#include <string>
#include <timehelp.h>

using log_level_t = uint8_t;

/*!
     \brief Log level

    Used for restrict log level
 */

enum class LogLevel : log_level_t {
    Nolog = 0x00,
    Trace = 0x01,
    Debug = 0x02,
    Info = 0x04,
    Warning = 0x08,
    Error = 0x10,
    Panic = 0x20,
    Always = 0x40,

};


/*!
     \brief LoggerFactory tmp

    Not implemented correctly
 */

class LoggerFactory
{
public:
    LoggerFactory() {}

    template<typename Args>
    void SetLevel(Args lt)
    {
        m_logLevel |= static_cast<log_level_t>(lt);
    }

    void SetLevelByString(std::string name);

    template<typename T, typename... Args>
    void SetLevel(T first, Args... args)
    {
        SetLevel(first);
        SetLevel(args...);
    }
    //! Verify if log level has been set
    bool IsLevel(const LogLevel& level) const
    {
        return (m_logLevel & static_cast<log_level_t>(level)) == static_cast<log_level_t>(level);
    }

    //! Print log
    void Print(const std::stringstream& ss)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        PrintSave(ss);
    }

    void SetPrintTimeStamp(bool flag = true)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_printTimestamp = flag;
    }

    void SetAppPrefix(const char* argv0)
    {
        m_prefixText = GetFilename(argv0);
        m_prefixText += ":";
    }

private:
    std::string GetFilename(const char* argv0);

    //! Print exactly to ...
    virtual void PrintSave(const std::stringstream& ss)
    {
        if (m_printTimestamp)
            std::cout << ToIso8601(std::chrono::system_clock::now()) << ">> " << m_prefixText << ss.str() << std::endl;
        else
            std::cout << m_prefixText << ss.str() << std::endl;
    }

    std::mutex m_mutex;                                                              //! Protect mutex
    std::atomic<log_level_t> m_logLevel = static_cast<log_level_t>(LogLevel::Nolog); //! log level of application

    bool m_printTimestamp = false;

    std::string m_prefixText;
};

/*!
     \brief Logger itself

    Not public class
 */

class Logger
{

    static const char* LogLevelStr(const LogLevel& logLevel);

public:
    Logger(const LogLevel& level, const char* funcName = nullptr);

    template<typename Type>
    Logger& operator<<(const Type& val)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_stringstream << val;
        return *this;
    }

    Logger& operator<<(const std::string& val)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_stringstream << val;
        return *this;
    }

    Logger& operator<<(const char* val)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_stringstream << val;
        return *this;
    }

    Logger& operator<<(std::ios_base& (*val)(std::ios_base&))
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_stringstream << val;
        return *this;
    }

    virtual ~Logger()
    {
        auto& logger = singleton<LoggerFactory>::rinstance();
        std::lock_guard<std::mutex> guard(m_mutex);
        logger.Print(m_stringstream);
    }

private:
    std::mutex m_mutex;
    std::stringstream m_stringstream;
};

Logger WrapLogger(const LogLevel& level, const char* funcname);


#define LOG(TYPE) \
    if (singleton<LoggerFactory>::instance()->IsLevel(LogLevel::TYPE)) \
    WrapLogger(LogLevel::TYPE, __FUNCTION__)
