/*
 *  Created on: March 9, 2022
 *      Author: Alexander Ksenofontov
 */

#include <algorithm>
#include <unordered_map>
#include "log.h"
#include "format.h"

const char* Logger::LogLevelStr(const LogLevel& logLevel) {
    switch(logLevel) {
    case LogLevel::Nolog: return "NOLOG";
    case LogLevel::Trace: return "TRACE";
    case LogLevel::Debug: return "DEBUG";
    case LogLevel::Info: return "INFO";
    case LogLevel::Warning: return "WARNING";
    case LogLevel::Error: return "ERROR";
    case LogLevel::Panic: return "PANIC";
    case LogLevel::Always: return "***";
    default: return "UNKNOWN-LEVEL";
    }
}

Logger WrapLogger(const LogLevel& level, const char* funcname) {
    if (level == LogLevel::Trace || level == LogLevel::Debug)
        return Logger(level, funcname);
    else
        return Logger(level);
}


Logger::Logger(const LogLevel& level, const char* funcName) {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_stringstream << LogLevelStr(level) << ":";
    if(funcName)
        m_stringstream << funcName << ": ";
    else
        m_stringstream << " ";
}

std::string LoggerFactory::GetFilename(const char* argv0) {
   std::string pathname(argv0);

   struct MatchPathSeparator {
   bool operator()( char ch ) const {
        return ch == '\\' || ch == '/';
   }
   };

   return std::string( 
       std::find_if( pathname.rbegin(), pathname.rend(),
                     MatchPathSeparator() ).base(),
       pathname.end() );
}

void LoggerFactory::SetLevelByString(std::string name) {
    const static std::unordered_map<std::string, LogLevel> m = {
        { "NOLOG", LogLevel::Nolog },
        { "TRACE", LogLevel::Trace },
        { "DEBUG", LogLevel::Debug },
        { "INFO", LogLevel::Info },
        { "WARNING", LogLevel::Warning },
        { "ERROR", LogLevel::Error },
        { "PANIC", LogLevel::Panic },
        { "ALWAYS", LogLevel::Always }
    };

    std::for_each(name.begin(), name.end(), ::toupper);
    auto it = m.find(name);

    if (it == m.end())
        throw std::runtime_error(format("Invalid option %1", name));
    else
        SetLevel(it->second);
}

