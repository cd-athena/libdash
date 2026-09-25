/*
 * AlternativeMPDEvent.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef ALTERNATIVEMPDEVENT_H_
#define ALTERNATIVEMPDEVENT_H_

#include "config.h"

#include "IAlternativeMPDEvent.h"
#include "IAlternativeMPDReplaceEvent.h"
#include "AbstractMPDElement.h"
#include "Descriptor.h"

namespace dash
{
    namespace mpd
    {
        /*
         * Implementation of AlternativeMPDEventType, shared by InsertPresentation and ReplacePresentation.
         * The interface is the first, non-virtual base (see DescriptorBase).
         */
        template <class AlternativeMPDEventInterface>
        class AlternativeMPDEventBase : public AlternativeMPDEventInterface, public AbstractMPDElement
        {
            public:
                AlternativeMPDEventBase () :
                    uri(""), earliestResolutionTimeOffset(0), hasEarliestResolutionTimeOffset(false),
                    serviceDescriptionId(0), hasServiceDescriptionId(false), maxDuration(2251799813685247ULL),
                    executeOnce(false), noJump(0), skipAfter("PT0S") {}
                virtual ~AlternativeMPDEventBase ()
                {
                    for (size_t i = 0; i < this->supplementalProperties.size(); i++)
                        delete(this->supplementalProperties.at(i));
                }

                const std::string&                  GetUri                          ()  const   { return this->uri; }
                uint64_t                            GetEarliestResolutionTimeOffset ()  const   { return this->earliestResolutionTimeOffset; }
                bool                                HasEarliestResolutionTimeOffset ()  const   { return this->hasEarliestResolutionTimeOffset; }
                uint32_t                            GetServiceDescriptionId         ()  const   { return this->serviceDescriptionId; }
                bool                                HasServiceDescriptionId         ()  const   { return this->hasServiceDescriptionId; }
                uint64_t                            GetMaxDuration                  ()  const   { return this->maxDuration; }
                bool                                IsExecuteOnce                   ()  const   { return this->executeOnce; }
                int64_t                             GetNoJump                       ()  const   { return this->noJump; }
                const std::string&                  GetSkipAfter                    ()  const   { return this->skipAfter; }
                const std::vector<IDescriptor *>&   GetSupplementalProperties       ()  const   { return (std::vector<IDescriptor *> &) this->supplementalProperties; }

                void    SetUri                          (const std::string& uri)    { this->uri = uri; }
                void    SetEarliestResolutionTimeOffset (uint64_t offset)           { this->earliestResolutionTimeOffset = offset; this->hasEarliestResolutionTimeOffset = true; }
                void    SetServiceDescriptionId         (uint32_t id)               { this->serviceDescriptionId = id; this->hasServiceDescriptionId = true; }
                void    SetMaxDuration                  (uint64_t maxDuration)      { this->maxDuration = maxDuration; }
                void    SetExecuteOnce                  (bool executeOnce)          { this->executeOnce = executeOnce; }
                void    SetNoJump                       (int64_t noJump)            { this->noJump = noJump; }
                void    SetSkipAfter                    (const std::string& skip)   { this->skipAfter = skip; }
                void    AddSupplementalProperty         (Descriptor *property)      { if (property != NULL) this->supplementalProperties.push_back(property); }

            protected:
                std::string                 uri;
                uint64_t                    earliestResolutionTimeOffset;
                bool                        hasEarliestResolutionTimeOffset;
                uint32_t                    serviceDescriptionId;
                bool                        hasServiceDescriptionId;
                uint64_t                    maxDuration;
                bool                        executeOnce;
                int64_t                     noJump;
                std::string                 skipAfter;
                std::vector<Descriptor *>   supplementalProperties;
        };

        class AlternativeMPDEvent : public AlternativeMPDEventBase<IAlternativeMPDEvent>
        {
            public:
                AlternativeMPDEvent             ();
                virtual ~AlternativeMPDEvent    ();
        };

        class AlternativeMPDReplaceEvent : public AlternativeMPDEventBase<IAlternativeMPDReplaceEvent>
        {
            public:
                AlternativeMPDReplaceEvent             ();
                virtual ~AlternativeMPDReplaceEvent    ();

                uint64_t    GetReturnOffset     ()  const;
                bool        HasReturnOffset     ()  const;
                bool        IsClip              ()  const;
                bool        IsStartWithOffset   ()  const;

                void    SetReturnOffset     (uint64_t returnOffset);
                void    SetClip             (bool clip);
                void    SetStartWithOffset  (bool startWithOffset);

            private:
                uint64_t    returnOffset;
                bool        hasReturnOffset;
                bool        clip;
                bool        startWithOffset;
        };
    }
}

#endif /* ALTERNATIVEMPDEVENT_H_ */
