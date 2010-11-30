/*
 * \file Configuration.cpp
 * \author Klaus Beyer
 * \brief Implementation file for the configuration
 */

#include "Configuration.h"

#include "Utilities/Path.h"

#include <stdexcept>

using namespace RoadRage;

Configuration::Configuration(const Options& in_options)
{
    m_opts = in_options;
}

Configuration::Configuration(const DefaultOptions& in_defaults)
{
    m_opts = in_defaults.getDefaults();
}

Configuration::Configuration(const std::string& in_fileName, const DefaultOptions& in_defaults)
{
    m_confFileName = in_fileName;
    m_opts = in_defaults.getDefaults();

    TiXmlDocument docConf(m_confFileName.c_str());
    if(docConf.LoadFile()) {
        parse(docConf);
    }
}

void Configuration::parse(TiXmlDocument& doc)
{
    TiXmlHandle h(&doc);

    TiXmlHandle rootHandle = h.FirstChild();
    TiXmlNode* node = rootHandle.Node();

    while(node && node->Type() != TiXmlNode::TINYXML_ELEMENT) {
        node = node->NextSibling();
    }

    assert(node);
    TiXmlElement* root = node->ToElement();
    assert(root);

    for(auto i = m_opts.begin() ; i != m_opts.end() ; ++i) {
        TiXmlElement* elem= root->FirstChildElement(i->first.c_str());
        if(!elem) continue; // the option doesn't exist in the file therefore keep the default.

        const char* value = elem->Attribute("value");
        if(value) {
            i->second = value;
        }
    }
}

std::string Configuration::get(const std::string& in_optName) const
{
    return m_opts.at(in_optName);
}

Configuration& Configuration::set(const std::string& in_optName, const std::string& value)
{
    m_opts[in_optName] = value;
    return *this;
}

void Configuration::save()
{
    if(m_confFileName.empty())
        return;

    TiXmlDocument doc(m_confFileName.c_str());
    TiXmlHandle h(&doc);
    TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "");
    doc.LinkEndChild(declaration);
    TiXmlElement* root = new TiXmlElement("Config");

    for(auto i = m_opts.begin() ; i != m_opts.end() ; ++i) {
        TiXmlElement* element = new TiXmlElement(i->first.c_str());
        element->SetAttribute("value", i->second.c_str());
        /*TiXmlNode* node = */root->LinkEndChild(element);
    }

    /*TiXmlNode* node = */doc.LinkEndChild(root);

    if(!doc.SaveFile()) {
        throw std::runtime_error(doc.ErrorDesc());
    }
}
