/*
 * ContentSteering.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "ContentSteering.h"

using namespace dash::mpd;

ContentSteering::ContentSteering    ()  :
                    url(""),
                    defaultServiceLocation(""),
                    queryBeforeStart(false),
                    clientRequirement(true)
{
}
ContentSteering::~ContentSteering   ()
{
}

const std::string&              ContentSteering::GetUrl                         ()  const
{
    return this->url;
}
void                            ContentSteering::SetUrl                         (const std::string& url)
{
    size_t first = url.find_first_not_of(" \t\r\n");
    size_t last  = url.find_last_not_of(" \t\r\n");

    this->url = (first == std::string::npos) ? "" : url.substr(first, last - first + 1);
}
const std::string&              ContentSteering::GetDefaultServiceLocation      ()  const
{
    return this->defaultServiceLocation;
}
const std::vector<std::string>& ContentSteering::GetDefaultServiceLocations     ()  const
{
    return this->defaultServiceLocations;
}
void                            ContentSteering::SetDefaultServiceLocation      (const std::string& defaultServiceLocation)
{
    std::istringstream stream(defaultServiceLocation);
    std::string        entry;

    this->defaultServiceLocation = defaultServiceLocation;
    this->defaultServiceLocations.clear();
    while (stream >> entry)
        this->defaultServiceLocations.push_back(entry);
}
bool                            ContentSteering::IsQueryBeforeStart             ()  const
{
    return this->queryBeforeStart;
}
void                            ContentSteering::SetQueryBeforeStart            (bool queryBeforeStart)
{
    this->queryBeforeStart = queryBeforeStart;
}
bool                            ContentSteering::HasClientRequirement           ()  const
{
    return this->clientRequirement;
}
void                            ContentSteering::SetClientRequirement           (bool clientRequirement)
{
    this->clientRequirement = clientRequirement;
}
