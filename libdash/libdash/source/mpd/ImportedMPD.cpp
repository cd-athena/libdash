/*
 * ImportedMPD.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "ImportedMPD.h"

using namespace dash::mpd;

ImportedMPD::ImportedMPD    ()  :
                url(""),
                earliestResolutionTimeOffset(60.0)
{
}
ImportedMPD::~ImportedMPD   ()
{
}

const std::string&  ImportedMPD::GetUrl                             ()  const
{
    return this->url;
}
void                ImportedMPD::SetUrl                             (const std::string& url)
{
    this->url = url;
}
double              ImportedMPD::GetEarliestResolutionTimeOffset    ()  const
{
    return this->earliestResolutionTimeOffset;
}
void                ImportedMPD::SetEarliestResolutionTimeOffset    (double earliestResolutionTimeOffset)
{
    this->earliestResolutionTimeOffset = earliestResolutionTimeOffset;
}
