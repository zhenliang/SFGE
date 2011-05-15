#include "file.h"

#include <iostream>
#include <fstream>

#include "logger.h"

namespace util
{
  void BackupFile(const std::string& src, const std::string& dst /*= ""*/)
  {
    std::ifstream ifs(src.c_str());
    std::string backupPath = dst.empty() ? src + ".bak" : dst;
    std::ofstream ofs(backupPath.c_str());
    ofs << ifs.rdbuf();
    Logger::GetInstance().Log("ok backup " + src);
  }

  void CopyFile_(const std::string& src, const std::string& dst)
  {
    std::ifstream ifs(src.c_str(), std::fstream::binary | std::fstream::in);
    std::ofstream ofs(dst.c_str(), std::fstream::binary | std::fstream::out);
    ofs << ifs.rdbuf();
    Logger::GetInstance().Log("ok copy " + src);
  }
}