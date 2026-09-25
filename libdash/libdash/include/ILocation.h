/**
 *  @class      dash::mpd::ILocation
 *  @brief      This interface is needed for accessing <tt><b>Location</b></tt> elements of the <tt><b>MPD</b></tt> (type <tt><b>LocationType</b></tt>)
 *              as specified in <em>ISO/IEC 23009-1, 6th edition</em>.
 *  @details    A <tt><b>Location</b></tt> element specifies a location at which the MPD is available (Table 3, Annex A.11).
 *              Since the 6th edition it may carry a \c \@serviceLocation label (subclause 5.6.6).
 *  @see        dash::mpd::IMPD dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef ILOCATION_H_
#define ILOCATION_H_

#include "config.h"

#include "IMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class ILocation : public virtual IMPDElement
        {
            public:
                virtual ~ILocation(){}

                /**
                 *  Returns the URL at which the MPD is available (the element content).
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetUrl              ()  const = 0;

                /**
                 *  Returns the label of the Service Location this URL belongs to (subclause 5.6.6). URLs with the same label are likely
                 *  served from a common network location, e.g. the same CDN. Empty if not present. \n\n
                 *  Corresponds to the \c \@serviceLocation attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetServiceLocation  ()  const = 0;
        };
    }
}

#endif /* ILOCATION_H_ */
