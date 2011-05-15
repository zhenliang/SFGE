#include "logger.h"

#include <iostream>
#include <string>

namespace
{
  const std::string kDefaultFile = "log.txt";
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
