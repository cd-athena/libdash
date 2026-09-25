/**
 *  @class      dash::mpd::IAlternativeMPDReplaceEvent
 *  @brief      This interface is needed for accessing <tt><b>ReplacePresentation</b></tt> elements (type <tt><b>AlternativeMPDReplaceEventType</b></tt>)
 *              as specified in <em>ISO/IEC 23009-1, 6th edition</em>, subclause 5.16.4 (Table 62).
 *  @details    A replacement event (Event Stream scheme \c "urn:mpeg:dash:event:alternativeMPD:replace:2025") replaces part of the main
 *              Media Presentation with the alternative one and defines where and how the main presentation resumes.
 *  @see        dash::mpd::IAlternativeMPDEvent dash::mpd::IEvent
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef IALTERNATIVEMPDREPLACEEVENT_H_
#define IALTERNATIVEMPDREPLACEEVENT_H_

#include "config.h"

#include "IAlternativeMPDEvent.h"

namespace dash
{
    namespace mpd
    {
        class IAlternativeMPDReplaceEvent : public IAlternativeMPDEvent
        {
            public:
                virtual ~IAlternativeMPDReplaceEvent(){}

                /**
                 *  Returns the offset from Event@presentationTime, in units of EventStream@timescale, at which playback of the main presentation resumes.
                 *  Only meaningful if HasReturnOffset() returns true; if absent, the main presentation resumes where the alternative one ended. \n\n
                 *  Corresponds to the \c \@returnOffset attribute.
                 *  @return     an unsigned 64-bit integer
                 */
                virtual uint64_t    GetReturnOffset     ()  const = 0;

                /**
                 *  Returns true if the \c \@returnOffset attribute is present.
                 *  @return     a bool value
                 */
                virtual bool        HasReturnOffset     ()  const = 0;

                /**
                 *  Returns whether the alternative presentation ends at the latest at Event@presentationTime + \c \@maxDuration even if the event
                 *  was executed later (true, default), or at the execution time + \c \@maxDuration (false). \n\n
                 *  Corresponds to the \c \@clip attribute.
                 *  @return     a bool value
                 */
                virtual bool        IsClip              ()  const = 0;

                /**
                 *  Returns whether a static alternative presentation starts at an offset equal to the delay between Event@presentationTime and
                 *  the actual execution time (true), or at its beginning (false, default). \n\n
                 *  Corresponds to the \c \@startWithOffset attribute.
                 *  @return     a bool value
                 */
                virtual bool        IsStartWithOffset   ()  const = 0;
        };
    }
}

#endif /* IALTERNATIVEMPDREPLACEEVENT_H_ */
