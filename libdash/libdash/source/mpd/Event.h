/*
 * Event.h
 *****************************************************************************
 * Name: Daniele Lorenzi
 * Email: lorenzidaniele.97@gmail.com
 * Date: 2021
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef EVENT_H_
#define EVENT_H_

#include "config.h"

#include "IEvent.h"
#include "AbstractMPDElement.h"
#include "Descriptor.h"
#include "SelectionInfo.h"
#include "ServiceDescription.h"
#include "AlternativeMPDEvent.h"

namespace dash
{
    namespace mpd
    {
        class Event : public IEvent, public AbstractMPDElement
        {
            public:
                Event             ();
                virtual ~Event    ();

                uint64_t             GetPresentationTime    ()  const;
                const std::string&   GetDuration            ()  const;
                uint64_t             GetId                  ()  const;
                const std::string&   GetContentEncoding     ()  const;
                const std::string&   GetMessageData         ()  const;
                const std::string&   GetStatus              ()  const;
                const std::string&   GetContent             ()  const;
                const ISelectionInfo *                      GetSelectionInfo            ()  const;
                const std::vector<IServiceDescription *>&   GetServiceDescriptions      ()  const;
                const IAlternativeMPDEvent *                GetInsertPresentation       ()  const;
                const IAlternativeMPDReplaceEvent *         GetReplacePresentation      ()  const;
                const std::vector<IDescriptor *>&           GetSupplementalProperties   ()  const;
                const std::vector<IDescriptor *>&           GetEssentialProperties      ()  const;

                void    SetPresentationTime    (uint64_t presentationTime);
                void    SetDuration            (const std::string& duration);
                void    SetId                  (uint64_t  id);
                void    SetContentEncoding     (const std::string&  contentEncoding);
                void    SetMessageData         (const std::string&  messageData);
                void    SetStatus              (const std::string&  status);
                void    SetContent             (const std::string&  content);
                void    SetSelectionInfo       (SelectionInfo *selectionInfo);
                void    AddServiceDescription  (ServiceDescription *serviceDescription);
                void    SetInsertPresentation  (AlternativeMPDEvent *insertPresentation);
                void    SetReplacePresentation (AlternativeMPDReplaceEvent *replacePresentation);
                void    AddSupplementalProperty(Descriptor *supplementalProperty);
                void    AddEssentialProperty   (Descriptor *essentialProperty);

            private:
                uint64_t    presentationTime;
                std::string duration;
                uint64_t    id;
                std::string contentEncoding;
                std::string messageData;
                std::string status;
                std::string content;
                SelectionInfo                       *selectionInfo;
                std::vector<ServiceDescription *>   serviceDescriptions;
                AlternativeMPDEvent                 *insertPresentation;
                AlternativeMPDReplaceEvent          *replacePresentation;
                std::vector<Descriptor *>           supplementalProperties;
                std::vector<Descriptor *>           essentialProperties;
                
        };
    }
}

#endif /* EVENT_H_ */
