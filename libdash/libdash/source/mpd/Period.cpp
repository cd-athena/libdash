/*
 * Period.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * @contributor        Daniele Lorenzi
 * @contributiondate   2021
 * 
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "Period.h"

using namespace dash::mpd;

Period::Period  () :
        segmentBase(NULL),
        segmentList(NULL),
        segmentTemplate(NULL),
        xlinkActuate("onRequest"),
        xlinkHref(""),
		xlinkType("simple"),
		xlinkShow("embed"),
        id(""),
        start(""),
        duration(""),
        isBitstreamSwitching(false)
{
}
Period::~Period ()
{
    for(size_t i = 0; i < this->baseURLs.size(); i++)
        delete(this->baseURLs.at(i));
    for(size_t i = 0; i < this->adaptationSets.size(); i++)
        delete(this->adaptationSets.at(i));
    for(size_t i = 0; i < this->subsets.size(); i++)
        delete(this->subsets.at(i));
	for(size_t i = 0; i < this->eventStreams.size(); i++)
        delete(this->eventStreams.at(i));
    delete(segmentBase);
    delete(segmentList);
    delete(segmentTemplate);
}

const std::vector<IBaseUrl *>&      Period::GetBaseURLs             ()  const
{
    return (std::vector<IBaseUrl *> &) this->baseURLs;
}
void                                Period::AddBaseURL              (BaseUrl *baseUrl)
{
    this->baseURLs.push_back(baseUrl);
}
ISegmentBase*                       Period::GetSegmentBase          ()  const
{
    return this->segmentBase;
}
void                                Period::SetSegmentBase          (SegmentBase *segmentBase)
{
    this->segmentBase = segmentBase;
}
ISegmentList*                       Period::GetSegmentList          ()  const
{
    return this->segmentList;
}
void                                Period::SetSegmentList          (SegmentList *segmentList)
{
    this->segmentList = segmentList;
}
ISegmentTemplate*                   Period::GetSegmentTemplate      ()  const
{
    return this->segmentTemplate;
}
void                                Period::SetSegmentTemplate      (SegmentTemplate *segmentTemplate) 
{
    this->segmentTemplate = segmentTemplate;
}
const std::vector<IEventStream *>&  Period::GetEventStreams         ()  const
{
    return (std::vector<IEventStream *> &) this->eventStreams;
}
void                                Period::AddEventStream          (EventStream *eventStream)
{
    this->eventStreams.push_back(eventStream);
}
const std::vector<IAdaptationSet*>& Period::GetAdaptationSets       () const
{
    return (std::vector<IAdaptationSet*> &) this->adaptationSets;
}
void                                Period::AddAdaptationSet        (AdaptationSet *adaptationSet)
{
    if(adaptationSet != NULL)
        this->adaptationSets.push_back(adaptationSet);
}
const std::vector<ISubset *>&       Period::GetSubsets              () const
{
    return (std::vector<ISubset *> &) this->subsets;
}
void                                Period::AddSubset               (Subset *subset)
{
    this->subsets.push_back(subset);
}
const std::string&                  Period::GetXlinkHref            ()  const
{
    return this->xlinkHref;
}
void                                Period::SetXlinkHref            (const std::string& xlinkHref)
{
    this->xlinkHref = xlinkHref;
}
const std::string&                  Period::GetXlinkActuate         ()  const
{
    return this->xlinkActuate;
}
void                                Period::SetXlinkActuate         (const std::string& xlinkActuate)
{
    this->xlinkActuate = xlinkActuate;
}
const std::string&                  Period::GetXlinkType            ()  const
{
    return this->xlinkType;
}
void                                Period::SetXlinkType            (const std::string& xlinkType)
{
    this->xlinkType = xlinkType;
}
const std::string&                  Period::GetXlinkShow            ()  const
{
    return this->xlinkShow;
}
void                                Period::SetXlinkShow            (const std::string& xlinkShow)
{
    this->xlinkShow = xlinkShow;
}
const std::string&                  Period::GetId                   ()  const
{
    return this->id;
}
void                                Period::SetId                   (const std::string& id)
{
    this->id = id;
}
const std::string&                  Period::GetStart                ()  const
{
    return this->start;
}
void                                Period::SetStart                (const std::string& start)
{
    this->start = start;
}
const std::string&                  Period::GetDuration             ()  const
{
    return this->duration;
}
void                                Period::SetDuration             (const std::string& duration)
{
    this->duration = duration;
}
bool                                Period::GetBitstreamSwitching   ()  const
{
    return this->isBitstreamSwitching;
}
void                                Period::SetBitstreamSwitching   (bool value)
{
    this->isBitstreamSwitching = value;
}
