#pragma once

#include <map>
#include <string>

namespace RoadRage {
    typedef std::map<std::string, std::string> Options;

    class DefaultOptions
    {
    public:
        virtual ~DefaultOptions();
        const Options& getDefaults() const {return m_defOpt; }
        void add(const std::string& name, const std::string& value);

    protected:
        DefaultOptions();

    private:
        Options m_defOpt;
    };
}