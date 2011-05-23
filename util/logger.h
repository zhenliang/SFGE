#pragma once

// 特性：
// 1 能同时写入控制台和文件
// 2 能设置输出级别
// 3 线程安全（我们需要）// 未来特性

// 注意：当前尽量在同一个线程使用，否则不小心就出错

#include <fstream>
#include <sstream>

#include "i_get_instance.h"

namespace util
{
  class Logger : public util::IGetInstance<Logger>
  {
  public:
    enum LogMode
    {
      LM_FILE = 1 << 0,
      LM_STDERR = 1 << 1,

      LM_ALL = 0xffffffff,
    };

    enum Loglevel
    {
      LL_INFO = 1,
      LL_WARNING = 2,
      LL_ERROR = 3,

      LL_NONE = 0x7fffffff,
    };

    Logger();

    void Log(const std::string& text, int loglevel = LL_INFO);

    void LogBegin() { logbuf_.str(""); }
    template <class T> 
    Logger& operator<<(const T& val);
    void LogEnd(int loglevel = LL_INFO) { Log(logbuf_.str(), loglevel); logbuf_.str(""); }

    int GetLogMode() const { return logMode_; }
    int GetLoglevel() const { return loglevel_; }
    std::string GetLogfile() const { return logfile_; }

    void SetLogMode(int val);
    void SetLoglevel(int val);
    void SetLogfile(const std::string& val);

  private:
    int logMode_;
    int loglevel_;
    std::string logfile_;
    std::ofstream outstream_;
    std::stringstream logbuf_;
  };

  template <class T>
  Logger& Logger::operator<<(const T& val)
  {
    logbuf_ << val;
    return *this;
  }
}

