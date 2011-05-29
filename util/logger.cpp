#include "logger.h"

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

namespace
{
  const std::string kDefaultFile = "log.txt";

  void PrintTime(std::ostream& os)
  {
    time_t rawtime;
    time(&rawtime);
    tm* timeinfo = localtime(&rawtime);
    os << std::setfill('0');
    os << "[" 
      << std::setw(4) << timeinfo->tm_year + 1900 << "-"
      << std::setw(2) << timeinfo->tm_mon + 1<< "-"
      << std::setw(2) << timeinfo->tm_mday << " "
      << std::setw(2) << timeinfo->tm_hour << ":"
      << std::setw(2) << timeinfo->tm_min << ":"
      << std::setw(2) << timeinfo->tm_sec << "] ";
    os << std::setfill(' ');
  }

  void PrintLoglevel(std::ostream& os, int loglevel)
  {
    switch (loglevel)
    {
    case util::Logger::LL_INFO: os << "[INFO] "; break;
    case util::Logger::LL_WARNING: os << "[WARNING] "; break;
    case util::Logger::LL_ERROR: os << "[ERROR] "; break;
    case util::Logger::LL_NONE: os << "[NONE] "; break;
    default: os << "[UNKNOWN] "; break;
    }
  }
}

namespace util
{
  Logger::Logger()
    : logMode_(LM_ALL)
    , loglevel_(LL_INFO)
    , logfile_(kDefaultFile)
    , outstream_()
    , logbuf_()
  {

  }

  void Logger::Log(const std::string& text, int loglevel /*= LL_INFO*/)
  {
    if (loglevel < GetLoglevel())
      return;

    if (!outstream_.is_open())
      outstream_.open(logfile_.c_str());

    PrintTime(outstream_);
    PrintLoglevel(outstream_, loglevel);

    if ((logMode_ & LM_FILE) && outstream_.is_open() && outstream_.good())
      outstream_ << text << std::endl;

    if (logMode_ & LM_STDERR)
      std::cout << text << std::endl;
  }  

  void Logger::SetLogfile(const std::string& val)
  {
    if (logfile_ == val)
      return;

    logfile_ = val;

    if (outstream_.is_open())
      outstream_.close();

    outstream_.open(logfile_.c_str());
    assert(outstream_.is_open());

    Log("set logfile: " + val);
  }

  void Logger::SetLogMode(int val)
  {
    logMode_ = val & LM_ALL;
    assert(logMode_ & LM_ALL);

    LogBegin();
    (*this) << "set log mode: " << logMode_;
    LogEnd();
  }

  void Logger::SetLoglevel(int val)
  {
    loglevel_ = val;
    
    LogBegin();
    (*this) << "set log level: " << loglevel_;
    LogEnd();
  }
}
