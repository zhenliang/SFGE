#include "file.h"

#include <iostream>
#include <fstream>

namespace util
{
    void BackupFile(const std::string& source, const std::string& destination /*= ""*/)
    {
        std::ifstream ifs(source.c_str());
        std::string backupPath = destination.empty() ? source + ".bak" : destination;
        std::ofstream ofs(backupPath.c_str());
        ofs << ifs.rdbuf();
        std::cout<<"ok backup "<<source<<std::endl;
    }
}