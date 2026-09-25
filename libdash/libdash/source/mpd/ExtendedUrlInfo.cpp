/*
 * ExtendedUrlInfo.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "ExtendedUrlInfo.h"

using namespace dash::mpd;

ExtendedUrlInfo::ExtendedUrlInfo    ()  :
                    sameOriginOnly(false),
                    header("")
{
    this->includeInRequests.push_back("segment");
    this->headerParamSource.push_back("segment");
}
ExtendedUrlInfo::~ExtendedUrlInfo   ()
{
}

const std::vector<std::string>& ExtendedUrlInfo::GetIncludeInRequests   ()  const
{
    return this->includeInRequests;
}
void                            ExtendedUrlInfo::SetIncludeInRequests   (const std::string& includeInRequests)
{
    SplitWhitespace(includeInRequests, this->includeInRequests);
}
const std::vector<std::string>& ExtendedUrlInfo::GetHeaderParamSource   ()  const
{
    return this->headerParamSource;
}
void                            ExtendedUrlInfo::SetHeaderParamSource   (const std::string& headerParamSource)
{
    SplitWhitespace(headerParamSource, this->headerParamSource);
}
bool                            ExtendedUrlInfo::IsSameOriginOnly       ()  const
{
    return this->sameOriginOnly;
}
void                            ExtendedUrlInfo::SetSameOriginOnly      (bool sameOriginOnly)
{
    this->sameOriginOnly = sameOriginOnly;
}
const std::string&              ExtendedUrlInfo::GetHeader              ()  const
{
    return this->header;
}
void                            ExtendedUrlInfo::SetHeader              (const std::string& header)
{
    this->header = header;
}
void                            ExtendedUrlInfo::SplitWhitespace        (const std::string& value, std::vector<std::string>& entries)
{
    std::istringstream stream(value);
    std::string        entry;

    entries.clear();
    while (stream >> entry)
        entries.push_back(entry);
}
