/**
 *  @class      dash::mpd::IRunLength
 *  @brief      This interface is needed for accessing the attributes of <tt><b>P</b></tt> elements (RunLengthType) as specified in <em>ISO/IEC 23009-1, 6th edition</em>.
 *  @details    A <tt><b>P</b></tt> element is one entry of a <tt><b>Pattern</b></tt>: \c \@r + 1 contiguous Segments or Segment Sequences
 *              of identical duration \c \@d. P elements are ordered. Either \c \@d or \c \@ssp is present. See Table 25 of <em>ISO/IEC 23009-1, 6th edition</em>.
 *  @see        dash::mpd::IPattern dash::mpd::ISegmentTimeline dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef IRUNLENGTH_H_
#define IRUNLENGTH_H_

#include "config.h"

#include "IMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class IRunLength : public virtual IMPDElement
        {
            public:
                virtual ~IRunLength(){}

                /**
                 *  Returns the duration, in \c \@timescale units. \n\n
                 *  Corresponds to the \c \@d attribute.
                 *  @return     an unsigned 64-bit integer
                 */
                virtual uint64_t    GetDuration             ()  const = 0;

                /**
                 *  Returns the zero-based repeat count of contiguous Segments or Segment Sequences with duration \c \@d. Default: 0, never negative. \n\n
                 *  Corresponds to the \c \@r attribute.
                 *  @return     an unsigned integer
                 */
                virtual uint32_t    GetRepeatCount          ()  const = 0;

                /**
                 *  Returns the nominal number of Segments in each Segment Sequence. Values greater than 1 mean Segment Sequences are used. Default: 1.
                 *  Only present together with \c \@d. \n\n
                 *  Corresponds to the \c \@k attribute.
                 *  @return     an unsigned integer
                 */
                virtual uint32_t    GetSegmentsInSequence   ()  const = 0;

                /**
                 *  Returns the \c \@id of the dash::mpd::IPattern in the same <tt><b>SegmentTimeline</b></tt> that defines the Segment Sequence
                 *  used by this entry. Only meaningful if HasSsp() returns true. \n\n
                 *  Corresponds to the \c \@ssp attribute.
                 *  @return     an unsigned integer
                 */
                virtual uint32_t    GetSsp                  ()  const = 0;

                /**
                 *  Returns true if the \c \@ssp attribute is present.
                 *  @return     a bool value
                 */
                virtual bool        HasSsp                  ()  const = 0;
        };
    }
}

#endif /* IRUNLENGTH_H_ */
