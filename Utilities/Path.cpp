#include "Path.h"

std::string getUserDir()
{
    std::string path;
#if defined(_MSC_VER)
    path = getenv("APPDATA");
    path += "/roadrage";
#else
    path = getenv("HOME");
    path += "/.roadrage";
#endif
    return path;
}
