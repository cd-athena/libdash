/**
 *  @class      dash::mpd::ISegmentSequenceProperties
 *  @brief      This interface is needed for accessing the attributes of <tt><b>SegmentSequenceProperties</b></tt> elements as specified in <em>ISO/IEC 23009-1, 6th edition</em>.
 *  @details    In a Segment Sequence Representation, \c \@startWithSAP only applies to the first Partial Segment of each Segment Sequence.
 *              A <tt><b>SegmentSequenceProperties</b></tt> element signals properties (SAP type, inband events, alignment) for a subset of the
 *              remaining Partial Segments, selected by \c \@cadence. Multiple elements may be present, each with a different \c \@cadence.
 *              The element should only be present for Segment Sequence Representations. See Table 14 of <em>ISO/IEC 23009-1, 6th edition</em>.
 *  @see        dash::mpd::IRepresentationBase dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef ISEGMENTSEQUENCEPROPERTIES_H_
#define ISEGMENTSEQUENCEPROPERTIES_H_

#include "config.h"

#include "IMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class ISegmentSequenceProperties : public virtual IMPDElement
        {
            public:
                virtual ~ISegmentSequenceProperties(){}

                /**
                 *  Returns the SAP type of the Partial Segments selected by \c \@cadence: their SAP type is equal to or lower than this value.
                 *  0 (the default) means the SAP type is unknown. For details refer to \c \@startWithSAP. \n\n
                 *  Corresponds to the \c \@sapType attribute.
                 *  @return     an unsigned integer
                 */
                virtual uint32_t                        GetSapType      ()  const = 0;

                /**
                 *  Returns the cadence C (greater than 0, default 1) that selects the Partial Segments these properties apply to:
                 *  for a Segment Sequence with Partial Segments PS(1)...PS(k), these are PS(C*n + 1) for n = 0, 1, ... with C*n + 1 < k. \n\n
                 *  Corresponds to the \c \@cadence attribute.
                 *  @return     an unsigned integer
                 */
                virtual uint32_t                        GetCadence      ()  const = 0;

                /**
                 *  Returns whether the Partial Segments selected by \c \@cadence may contain an inband Event. Default: true.
                 *  If false, these Partial Segments do not include an inband Event, so a client need not parse them for one. \n\n
                 *  Corresponds to the \c \@event attribute.
                 *  @return     a bool value
                 */
                virtual bool                            HasEvent        ()  const = 0;

                /**
                 *  Returns the \c \@id values of the Representations for which the cadence of Partial Segments aligns
                 *  (time-aligned and non-overlapping) with the Segments of this Representation. Empty if no alignment is defined. \n\n
                 *  Corresponds to the space-separated \c \@alignment attribute.
                 *  @return     a reference to a vector of strings
                 */
                virtual const std::vector<std::string>& GetAlignment    ()  const = 0;
        };
    }
}

#endif /* ISEGMENTSEQUENCEPROPERTIES_H_ */
