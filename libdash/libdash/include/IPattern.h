/**
 *  @class      dash::mpd::IPattern
 *  @brief      This interface is needed for accessing <tt><b>Pattern</b></tt> elements of a <tt><b>SegmentTimeline</b></tt> as specified in <em>ISO/IEC 23009-1, 6th edition</em>.
 *  @details    A <tt><b>Pattern</b></tt> is a duration pattern: an ordered list of <tt><b>P</b></tt> entries that <tt><b>S</b></tt> elements refer to through
 *              \c \@p (starting at entry \c \@pE), or that describes the Partial Segment durations of a Segment Sequence when referenced through \c \@ssp.
 *              Duration patterns may only be used if signalled with an EssentialProperty descriptor. See subclause 5.3.9.6.5 of <em>ISO/IEC 23009-1, 6th edition</em>.
 *  @see        dash::mpd::IRunLength dash::mpd::ISegmentTimeline dash::mpd::ITimeline dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef IPATTERN_H_
#define IPATTERN_H_

#include "config.h"

#include "IMPDElement.h"
#include "IRunLength.h"

namespace dash
{
    namespace mpd
    {
        class IPattern : public virtual IMPDElement
        {
            public:
                virtual ~IPattern(){}

                /**
                 *  Returns the identifier of this Pattern, unique within its <tt><b>SegmentTimeline</b></tt> and referenced by \c \@p or \c \@ssp. \n\n
                 *  Corresponds to the \c \@id attribute.
                 *  @return     an unsigned 64-bit integer
                 */
                virtual uint64_t                        GetId           ()  const = 0;

                /**
                 *  Returns a reference to a vector of pointers to dash::mpd::IRunLength objects, which correspond to the <tt><b>P</b></tt> elements.
                 *  @return     a reference to a vector of pointers to dash::mpd::IRunLength objects
                 */
                virtual const std::vector<IRunLength *>& GetRunLengths  ()  const = 0;
        };
    }
}

#endif /* IPATTERN_H_ */
