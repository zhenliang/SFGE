#pragma once

#include <sstream>

#include "util.h"

namespace util
{

#define UTIL_STRINGLIZE(text) (#text)

std::string UTIL_API WS2S(const std::wstring& ws);
std::wstring UTIL_API S2WS(const std::string& s);

template <class T>
inline std::string ToStr(const T& val)
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

template <class T>
inline void ToRaw(const std::string& val, T& out)
{
    std::stringstream ss(val);
    ss >> out;
}

template <class T>
inline T ToRaw(const std::string& val)
{
    static T temp;
    ToRaw(val, temp);
    return temp;
}

}