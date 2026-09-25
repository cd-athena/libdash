/*
 * EventStream.cpp
 *****************************************************************************
 * Name: Daniele Lorenzi
 * Email: lorenzidaniele.97@gmail.com
 * Date: 2021
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "EventStream.h"

using namespace dash::mpd;

EventStream::EventStream    ()  :
                 xlinkHref(""),
                 xlinkActuate("onRequest"),
                 xlinkType("simple"),
                 xlinkShow("embed"),
                 schemeIdUri(""),
                 value(""),
                 presentationTimeOffset(0),
                 timescale(1)
{
}
EventStream::~EventStream   ()
{
    for (size_t i=0; i < this->events.size(); i++)
        delete(this->events.at(i));
    for (size_t i=0; i < this->baseURLs.size(); i++)
        delete(this->baseURLs.at(i));
    for (size_t i=0; i < this->requestParams.size(); i++)
        delete(this->requestParams.at(i));
    for (size_t i=0; i < this->essentialProperties.size(); i++)
        delete(this->essentialProperties.at(i));
    for (size_t i=0; i < this->supplementalProperties.size(); i++)
        delete(this->supplementalProperties.at(i));
}

const std::vector<IEvent *>&   EventStream::GetEvents                  ()  const
{
    return (std::vector<IEvent*> &) this->events;
}
void                           EventStream::AddEvent                   (Event *event)
{
    this->events.push_back(event);
}
const std::string&             EventStream::GetXlinkHref               ()  const
{
    return this->xlinkHref;
}
void                           EventStream::SetXlinkHref               (const std::string& xlinkHref)
{
    this->xlinkHref = xlinkHref;
}
const std::string&             EventStream::GetXlinkActuate            ()  const
{
    return this->xlinkActuate;
}
void                           EventStream::SetXlinkActuate            (const std::string& xlinkActuate)
{
    this->xlinkActuate = xlinkActuate;
}
const std::string&             EventStream::GetXlinkType               ()  const
{
    return this->xlinkType;
}
void                           EventStream::SetXlinkType               (const std::string& xlinkType)
{
    this->xlinkType = xlinkType;
}
const std::string&             EventStream::GetXlinkShow               ()  const
{
    return this->xlinkShow;
}
void                           EventStream::SetXlinkShow               (const std::string& xlinkShow)
{
    this->xlinkShow = xlinkShow;
}
const std::string&             EventStream::GetSchemeIdUri             ()  const
{
    return this->schemeIdUri;
}
void                           EventStream::SetSchemeIdUri             (const std::string& schemeIdUri)
{
    this->schemeIdUri = schemeIdUri;
}
const std::string&             EventStream::GetValue                   ()  const
{
    return this->value;
}
void                           EventStream::SetValue                   (const std::string& value)
{
    this->value = value;
}
uint32_t                       EventStream::GetTimescale               ()  const
{
    return this->timescale;
}
void                           EventStream::SetTimescale               (uint32_t timescale)
{
    this->timescale = timescale;
}
uint64_t                       EventStream::GetPresentationTimeOffset  ()  const
{
    return this->presentationTimeOffset;
}
void                           EventStream::SetPresentationTimeOffset  (uint64_t presentationTimeOffset)
{
    this->presentationTimeOffset = presentationTimeOffset;
}
const std::vector<IBaseUrl *>&     EventStream::GetBaseURLs   ()  const
{
    return (std::vector<IBaseUrl *> &) this->baseURLs;
}
void                           EventStream::AddBaseURL   (BaseUrl *element)
{
    if (element != NULL)
        this->baseURLs.push_back(element);
}
const std::vector<IExtendedUrlInfo *>&     EventStream::GetRequestParams   ()  const
{
    return (std::vector<IExtendedUrlInfo *> &) this->requestParams;
}
void                           EventStream::AddRequestParam   (ExtendedUrlInfo *element)
{
    if (element != NULL)
        this->requestParams.push_back(element);
}
const std::vector<IDescriptor *>&     EventStream::GetEssentialProperties   ()  const
{
    return (std::vector<IDescriptor *> &) this->essentialProperties;
}
void                           EventStream::AddEssentialProperty   (Descriptor *element)
{
    if (element != NULL)
        this->essentialProperties.push_back(element);
}
const std::vector<IDescriptor *>&     EventStream::GetSupplementalProperties   ()  const
{
    return (std::vector<IDescriptor *> &) this->supplementalProperties;
}
void                           EventStream::AddSupplementalProperty   (Descriptor *element)
{
    if (element != NULL)
        this->supplementalProperties.push_back(element);
}
