#pragma once

#include <string>

#include "util.h"

namespace util
{
  UTIL_API void BackupFile(const std::string& source, const std::string& destination = "");
  UTIL_API void CopyFile_(const std::string& source, const std::string& destination);
}