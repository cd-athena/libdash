/*
 * DOMParser.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "DOMParser.h"

using namespace dash::xml;
using namespace dash::helpers;

DOMParser::DOMParser    (std::string url) :
           url          (url),
           reader       (NULL),
           root         (NULL)
{
    this->Init();
}
DOMParser::~DOMParser   ()
{
    xmlCleanupParser();
    delete(this->root);
}

Node*   DOMParser::GetRootNode              () const
{
    return this->root;
}
bool    DOMParser::Parse                    ()
{
    this->reader = xmlReaderForFile(this->url.c_str(), NULL, 0);

    if(this->reader == NULL)
        return false;

    /* skip everything before the root element, e.g. comments or processing instructions */
    int ret = xmlTextReaderRead(this->reader);
    while(ret == 1 && xmlTextReaderNodeType(this->reader) != Start)
        ret = xmlTextReaderRead(this->reader);

    if(ret == 1)
        this->root = this->ProcessNode();

    xmlFreeTextReader(this->reader);

    if(this->root == NULL)
        return false;

    return true;
}
/*
 * Builds the node at the current reader position. Elements are read up to and including their own end tag;
 * nested elements consume their end tags in the recursive calls, so an end tag seen here always belongs to
 * this element. Comments, whitespace and processing instructions return NULL without moving the reader.
 */
Node*   DOMParser::ProcessNode              ()
{
    int type = xmlTextReaderNodeType(this->reader);

    if(type == Text || type == CData)
    {
        /* xmlTextReaderConstValue returns the content of text and CDATA nodes; xmlTextReaderReadString
         * does not return CDATA content in all libxml2 versions */
        const char* text = (const char *) xmlTextReaderConstValue(this->reader);

        if(text == NULL)
            return NULL;

        Node *node = new Node();
        node->SetType(Text);
        node->SetText(text);
        return node;
    }

    if(type != Start || xmlTextReaderConstName(this->reader) == NULL)
        return NULL;

    Node *node = new Node();
    node->SetType(type);
    node->SetMPDPath(Path::GetDirectoryPath(url));

    std::string name    = (const char *) xmlTextReaderConstName(this->reader);
    int         isEmpty = xmlTextReaderIsEmptyElement(this->reader);

    node->SetName(name);

    this->AddAttributesToNode(node);

    if(isEmpty)
        return node;

    Node    *subnode    = NULL;
    int     ret         = xmlTextReaderRead(this->reader);

    while(ret == 1)
    {
        if(xmlTextReaderNodeType(this->reader) == End)
            return node;

        subnode = this->ProcessNode();

        if(subnode != NULL)
            node->AddSubNode(subnode);

        ret = xmlTextReaderRead(this->reader);
    }

    return node;
}
void    DOMParser::AddAttributesToNode      (Node *node)
{
    if(xmlTextReaderHasAttributes(this->reader))
    {
        while(xmlTextReaderMoveToNextAttribute(this->reader))
        {
            std::string key      = (const char *) xmlTextReaderConstName(this->reader);
            std::string value    = (const char *) xmlTextReaderConstValue(this->reader);
            node->AddAttribute(key, value);
        }
    }
}
void    DOMParser::Print                    (Node *node, int offset)
{
    std::stringstream ss;
    for(int i = 0; i < offset; i++)
        ss << " ";
    ss << node->GetName();

    std::vector<std::string> keys = node->GetAttributeKeys();

    ss.clear();
    for(unsigned int i = 0; i < keys.size(); i++)
    {
        ss << " " << keys.at(i) << "=" << node->GetAttributeValue(keys.at(i));
    }

    offset++;

    for(unsigned int i = 0; i < node->GetSubNodes().size(); i++)
    {
        this->Print(node->GetSubNodes().at(i), offset);
    }
}
void    DOMParser::Init                     ()
{
    this->root      = NULL;
    this->reader    = NULL;
}
void    DOMParser::Print                    ()
{
    this->Print(this->root, 0);
}
