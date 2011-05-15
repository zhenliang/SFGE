#pragma once

#include <string>

#include "util.h"

namespace util
{
  UTIL_API void BackupFile(const std::string& src, const std::string& dst = "");
  UTIL_API void CopyFile_(const std::string& src, const std::string& dst);
}