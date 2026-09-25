/*
 * CMCDParameters.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "CMCDParameters.h"

using namespace dash::mpd;

CMCDParameters::CMCDParameters  ()  :
                    version(1),
                    mode("query"),
                    contentID(""),
                    sessionID("")
{
    this->includeInRequests.push_back("segment");
}
CMCDParameters::~CMCDParameters ()
{
}

uint32_t                        CMCDParameters::GetVersion              ()  const
{
    return this->version;
}
void                            CMCDParameters::SetVersion              (uint32_t version)
{
    this->version = version;
}
const std::string&              CMCDParameters::GetMode                 ()  const
{
    return this->mode;
}
void                            CMCDParameters::SetMode                 (const std::string& mode)
{
    this->mode = mode;
}
const std::vector<std::string>& CMCDParameters::GetIncludeInRequests    ()  const
{
    return this->includeInRequests;
}
void                            CMCDParameters::SetIncludeInRequests    (const std::string& includeInRequests)
{
    SplitWhitespace(includeInRequests, this->includeInRequests);
}
const std::vector<std::string>& CMCDParameters::GetKeys                 ()  const
{
    return this->keys;
}
void                            CMCDParameters::SetKeys                 (const std::string& keys)
{
    SplitWhitespace(keys, this->keys);
}
const std::string&              CMCDParameters::GetContentID            ()  const
{
    return this->contentID;
}
void                            CMCDParameters::SetContentID            (const std::string& contentID)
{
    this->contentID = contentID;
}
const std::string&              CMCDParameters::GetSessionID            ()  const
{
    return this->sessionID;
}
void                            CMCDParameters::SetSessionID            (const std::string& sessionID)
{
    this->sessionID = sessionID;
}
void                            CMCDParameters::SplitWhitespace         (const std::string& value, std::vector<std::string>& entries)
{
    std::istringstream stream(value);
    std::string        entry;

    entries.clear();
    while (stream >> entry)
        entries.push_back(entry);
}
