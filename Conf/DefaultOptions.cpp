#include "DefaultOptions.h"

using namespace RoadRage;

DefaultOptions::DefaultOptions()
{
}

DefaultOptions::~DefaultOptions()
{
}

void DefaultOptions::add(const std::string& name, const std::string& value)
{
    m_defOpt[name] = value;
}
