/*
 * ClientDataReporting.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "ClientDataReporting.h"

using namespace dash::mpd;

ClientDataReporting::ClientDataReporting    ()
{
}
ClientDataReporting::~ClientDataReporting   ()
{
    for (size_t i = 0; i < this->cmcdParameters.size(); i++)
        delete(this->cmcdParameters.at(i));
}

const std::vector<std::string>&         ClientDataReporting::GetServiceLocations    ()  const
{
    return this->serviceLocations;
}
void                                    ClientDataReporting::SetServiceLocations    (const std::string& serviceLocations)
{
    std::istringstream stream(serviceLocations);
    std::string        entry;

    this->serviceLocations.clear();
    while (stream >> entry)
        this->serviceLocations.push_back(entry);
}
const std::vector<uint32_t>&            ClientDataReporting::GetAdaptationSets      ()  const
{
    return this->adaptationSets;
}
void                                    ClientDataReporting::SetAdaptationSets      (const std::string& adaptationSets)
{
    std::istringstream stream(adaptationSets);
    std::string        entry;

    this->adaptationSets.clear();
    while (stream >> entry)
        this->adaptationSets.push_back((uint32_t) strtoul(entry.c_str(), NULL, 10));
}
const std::vector<ICMCDParameters *>&   ClientDataReporting::GetCMCDParameters      ()  const
{
    return (std::vector<ICMCDParameters *> &) this->cmcdParameters;
}
void                                    ClientDataReporting::AddCMCDParameters      (CMCDParameters *cmcdParameters)
{
    if (cmcdParameters != NULL)
        this->cmcdParameters.push_back(cmcdParameters);
}
