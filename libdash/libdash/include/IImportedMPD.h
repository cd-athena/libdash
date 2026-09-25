/**
 *  @class      dash::mpd::IImportedMPD
 *  @brief      This interface is needed for accessing the <tt><b>ImportedMPD</b></tt> element of a Linked Period as specified in
 *              <em>ISO/IEC 23009-1, 6th edition</em>, subclause 5.3.2.6 (Table 5).
 *  @details    A Period with an ImportedMPD element is a Linked Period: it imports its content from an external MPD (restricted to the
 *              single period profile, 8.15), which is integrated with the reference processing model of subclause 5.3.2.6.2.
 *              The element may only be present if MPD@type is \c "list".
 *  @see        dash::mpd::IPeriod dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef IIMPORTEDMPD_H_
#define IIMPORTEDMPD_H_

#include "config.h"

#include "IMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class IImportedMPD : public virtual IMPDElement
        {
            public:
                virtual ~IImportedMPD(){}

                /**
                 *  Returns the URI of the imported MPD (the element content).
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetUrl                              ()  const = 0;

                /**
                 *  Returns the offset in seconds before PeriodStart from which the imported MPD may be requested; the Linked Period is to be
                 *  available at the latest at that time. Default: 60. \n\n
                 *  Corresponds to the \c \@earliestResolutionTimeOffset attribute. Note that, unlike the attribute of the same name on
                 *  Alternative MPD events, the value is in seconds, not in timescale units.
                 *  @return     a double value
                 */
                virtual double              GetEarliestResolutionTimeOffset     ()  const = 0;
        };
    }
}

#endif /* IIMPORTEDMPD_H_ */
