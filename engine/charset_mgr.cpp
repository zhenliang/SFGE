#include "charset_mgr.h"

#include <fstream>

#include <util\container.h>
#include <util\string.h>

bool CharsetManager::AddCharset(const std::string& key, const std::string& charset)
{	
  // 提取非重复字符

  std::wstring wcharset = util::S2WS(charset); // 转宽字符
  std::sort(wcharset.begin(), wcharset.end()); // 排序
  std::wstring::iterator i = std::unique(wcharset.begin(), wcharset.end()); // 剔除重复字符
  wcharset.erase(i, wcharset.end()); // 删除废弃字符

  // 输出提取出来的字符串（注意 std::wcout<<wcharset 是无法输出汉字的，待研究）

  std::cout<<util::WS2S(wcharset)<<std::endl;

  // 存入管理器

  return util::Insert(charsets_, std::make_pair(key, Unicode::Text(wcharset)));
}

bool CharsetManager::AddCharsetFromFile(const std::string& key, const std::string& path)
{
  assert(!path.empty());

  std::ifstream ifs(path.c_str());
  if (ifs.is_open())
  {	
    std::string charset;

    const size_t MAX_LEN = 255;
    char line[MAX_LEN + 1] = {};

    while (ifs.getline(line, MAX_LEN))
      charset += line;

    return AddCharset(key, charset);
  }

  return false;
}

const Unicode::Text& CharsetManager::GetCharset(const std::string& key)
{
  return util::Get(charsets_, key);
}
