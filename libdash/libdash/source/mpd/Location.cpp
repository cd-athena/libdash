/*
 * Location.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "Location.h"

using namespace dash::mpd;

Location::Location  ()  :
            url(""),
            serviceLocation("")
{
}
Location::~Location ()
{
}

const std::string&  Location::GetUrl                ()  const
{
    return this->url;
}
void                Location::SetUrl                (const std::string& url)
{
    this->url = url;
}
const std::string&  Location::GetServiceLocation    ()  const
{
    return this->serviceLocation;
}
void                Location::SetServiceLocation    (const std::string& serviceLocation)
{
    this->serviceLocation = serviceLocation;
}
