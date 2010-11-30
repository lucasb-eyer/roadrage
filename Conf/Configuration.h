/*
 * \file Configuration.h
 * \author Klaus Beyer
 * \brief Interface file for the configuration
 */

#pragma once

#include "DefaultOptions.h"

#include <tinyxml/tinyxml.h>

namespace RoadRage {

    class Configuration
    {
    public:
        Configuration(const std::string& in_fileName, const DefaultOptions& in_defaults);
        Configuration(const Options& in_options);
        Configuration(const DefaultOptions& in_defaults);

        std::string get(const std::string& in_optName) const;
        Configuration& set(const std::string& in_optName, const std::string& value);

        void save();

    private:
        void parse(TiXmlDocument& doc);
        std::string m_confFileName;
        Options m_opts;
    };
};
