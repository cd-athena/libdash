/*
 * Event.cpp
 *****************************************************************************
 * Name: Daniele Lorenzi
 * Email: lorenzidaniele.97@gmail.com
 * Date: 2021
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "Event.h"

using namespace dash::mpd;

Event::Event    ()  :
    presentationTime(0),
    id(0),
    contentEncoding(""),
    messageData(""),
    status("repeat"),
    content(""),
    selectionInfo(NULL),
    insertPresentation(NULL),
    replacePresentation(NULL)
{
}
Event::~Event   ()
{
    delete(this->selectionInfo);
    delete(this->insertPresentation);
    delete(this->replacePresentation);
    for (size_t i = 0; i < this->serviceDescriptions.size(); i++)
        delete(this->serviceDescriptions.at(i));
    for (size_t i = 0; i < this->supplementalProperties.size(); i++)
        delete(this->supplementalProperties.at(i));
    for (size_t i = 0; i < this->essentialProperties.size(); i++)
        delete(this->essentialProperties.at(i));
}

uint64_t            Event::GetPresentationTime    ()  const
{
    return this->presentationTime;
}
void                Event::SetPresentationTime    (uint64_t presentationTime) 
{
    this->presentationTime = presentationTime;
}
const std::string&  Event::GetDuration            ()  const
{
    return this->duration;
}
void                Event::SetDuration            (const std::string& duration) 
{
    this->duration = duration;
}
uint64_t            Event::GetId                  ()  const
{
    return this->id;
}
void                Event::SetId                  (uint64_t id) 
{
    this->id = id;
}
const std::string&  Event::GetContentEncoding     ()  const
{
    return this->contentEncoding;
}
void                Event::SetContentEncoding     (const std::string& contentEncoding) 
{
    this->contentEncoding = contentEncoding;
}
const std::string&  Event::GetMessageData         ()  const
{
    return this->messageData;
}
void                Event::SetMessageData         (const std::string& messageData) 
{
    this->messageData = messageData;
}
const std::string&                          Event::GetStatus                ()  const
{
    return this->status;
}
void                                        Event::SetStatus                (const std::string& status)
{
    this->status = status;
}
const std::string&                          Event::GetContent               ()  const
{
    return this->content;
}
void                                        Event::SetContent               (const std::string& content)
{
    this->content = content;
}
const ISelectionInfo *                      Event::GetSelectionInfo         ()  const
{
    return this->selectionInfo;
}
void                                        Event::SetSelectionInfo         (SelectionInfo *selectionInfo)
{
    delete(this->selectionInfo);
    this->selectionInfo = selectionInfo;
}
const std::vector<IServiceDescription *>&   Event::GetServiceDescriptions   ()  const
{
    return (std::vector<IServiceDescription *> &) this->serviceDescriptions;
}
void                                        Event::AddServiceDescription    (ServiceDescription *serviceDescription)
{
    if (serviceDescription != NULL)
        this->serviceDescriptions.push_back(serviceDescription);
}
const IAlternativeMPDEvent *                Event::GetInsertPresentation    ()  const
{
    return this->insertPresentation;
}
void                                        Event::SetInsertPresentation    (AlternativeMPDEvent *insertPresentation)
{
    delete(this->insertPresentation);
    this->insertPresentation = insertPresentation;
}
const IAlternativeMPDReplaceEvent *         Event::GetReplacePresentation   ()  const
{
    return this->replacePresentation;
}
void                                        Event::SetReplacePresentation   (AlternativeMPDReplaceEvent *replacePresentation)
{
    delete(this->replacePresentation);
    this->replacePresentation = replacePresentation;
}
const std::vector<IDescriptor *>&           Event::GetSupplementalProperties    ()  const
{
    return (std::vector<IDescriptor *> &) this->supplementalProperties;
}
void                                        Event::AddSupplementalProperty      (Descriptor *supplementalProperty)
{
    if (supplementalProperty != NULL)
        this->supplementalProperties.push_back(supplementalProperty);
}
const std::vector<IDescriptor *>&           Event::GetEssentialProperties       ()  const
{
    return (std::vector<IDescriptor *> &) this->essentialProperties;
}
void                                        Event::AddEssentialProperty         (Descriptor *essentialProperty)
{
    if (essentialProperty != NULL)
        this->essentialProperties.push_back(essentialProperty);
}
