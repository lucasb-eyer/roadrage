#pragma once

#include <sstream>

namespace RoadRage {

template <class T>
std::string to_s(const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template <class T>
T to(const std::string& s)
{
    T t;
    std::stringstream ss(s);
    ss >> t;
    return t;
}

}
