/**
 *  @class      dash::mpd::IAlternativeMPDEvent
 *  @brief      This interface is needed for accessing <tt><b>InsertPresentation</b></tt> elements and the common properties of
 *              <tt><b>ReplacePresentation</b></tt> elements (type <tt><b>AlternativeMPDEventType</b></tt>) as specified in
 *              <em>ISO/IEC 23009-1, 6th edition</em>, subclause 5.16 (Tables 60 and 63).
 *  @details    An Alternative MPD event switches playback from the current (main) Media Presentation to the alternative Media Presentation
 *              described by the MPD at \c \@uri, e.g. for ad insertion. Insertion events use the Event Stream scheme
 *              \c "urn:mpeg:dash:event:alternativeMPD:insert:2025"; for replacement events see dash::mpd::IAlternativeMPDReplaceEvent.
 *              Times are in units of EventStream@timescale.
 *  @see        dash::mpd::IAlternativeMPDReplaceEvent dash::mpd::IEvent dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef IALTERNATIVEMPDEVENT_H_
#define IALTERNATIVEMPDEVENT_H_

#include "config.h"

#include "IMPDElement.h"
#include "IDescriptor.h"

namespace dash
{
    namespace mpd
    {
        class IAlternativeMPDEvent : public virtual IMPDElement
        {
            public:
                virtual ~IAlternativeMPDEvent(){}

                /**
                 *  Returns the URI (typically an HTTP URL) of the MPD describing the alternative Media Presentation. It may contain MPD anchors (Annex C.4). \n\n
                 *  Corresponds to the mandatory \c \@uri attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&                  GetUri                              ()  const = 0;

                /**
                 *  Returns the time interval before Event@presentationTime during which the alternative MPD may be requested.
                 *  Only meaningful if HasEarliestResolutionTimeOffset() returns true; otherwise the specification defines a default of
                 *  60 seconds (in units of EventStream@timescale). \n\n
                 *  Corresponds to the \c \@earliestResolutionTimeOffset attribute.
                 *  @return     an unsigned 64-bit integer
                 */
                virtual uint64_t                            GetEarliestResolutionTimeOffset     ()  const = 0;

                /**
                 *  Returns true if the \c \@earliestResolutionTimeOffset attribute is present.
                 *  @return     a bool value
                 */
                virtual bool                                HasEarliestResolutionTimeOffset     ()  const = 0;

                /**
                 *  Returns the \c \@id of the ServiceDescription that applies to this Event and to any presentation started by executing it.
                 *  Only meaningful if HasServiceDescriptionId() returns true.
                 *  @return     an unsigned integer
                 */
                virtual uint32_t                            GetServiceDescriptionId             ()  const = 0;

                /**
                 *  Returns true if the \c \@serviceDescriptionId attribute is present.
                 *  @return     a bool value
                 */
                virtual bool                                HasServiceDescriptionId             ()  const = 0;

                /**
                 *  Returns the maximum duration of the alternative presentation. The schema default 2251799813685247 stands for infinity:
                 *  the current presentation then resumes only when the alternative presentation ends. \n\n
                 *  Corresponds to the \c \@maxDuration attribute.
                 *  @return     an unsigned 64-bit integer
                 */
                virtual uint64_t                            GetMaxDuration                      ()  const = 0;

                /**
                 *  Returns whether the event is executed only the first time its active interval is played. Default: false. \n\n
                 *  Corresponds to the \c \@executeOnce attribute.
                 *  @return     a bool value
                 */
                virtual bool                                IsExecuteOnce                       ()  const = 0;

                /**
                 *  Returns the no-jump mode. If non-zero, the active interval of the event cannot be skipped by seeking: with 1 all such events are
                 *  executed, with 2 only the latest one. Default: 0. \n\n
                 *  Corresponds to the \c \@noJump attribute.
                 *  @return     a signed 64-bit integer
                 */
                virtual int64_t                             GetNoJump                           ()  const = 0;

                /**
                 *  Returns the offset, as xs:duration, from the beginning of the alternative presentation after which the rest of it may be skipped
                 *  in response to a user action. Default: \c "PT0S" (skipping allowed everywhere). \n\n
                 *  Corresponds to the \c \@skipAfter attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&                  GetSkipAfter                        ()  const = 0;

                /**
                 *  Returns a reference to a vector of pointers to dash::mpd::IDescriptor objects that correspond to the <tt><b>SupplementalProperty</b></tt> elements.
                 *  @return     a reference to a vector of pointers to dash::mpd::IDescriptor objects
                 */
                virtual const std::vector<IDescriptor *>&   GetSupplementalProperties           ()  const = 0;
        };
    }
}

#endif /* IALTERNATIVEMPDEVENT_H_ */
