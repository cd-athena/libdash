/**
 *  @class      dash::mpd::IPlaybackRestrictions
 *  @brief      This interface is needed for accessing <tt><b>PlaybackRestrictions</b></tt> elements of a <tt><b>ServiceDescription</b></tt> as specified in <em>ISO/IEC 23009-1, 6th edition</em>, Annex K.3.8 (Tables K.9 and K.18).
 *  @details    PlaybackRestrictions describe restrictions on playback behaviour within the scope of the Service Description.
 *  @see        dash::mpd::IServiceDescription dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef IPLAYBACKRESTRICTIONS_H_
#define IPLAYBACKRESTRICTIONS_H_

#include "config.h"

#include "IMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class IPlaybackRestrictions : public virtual IMPDElement
        {
            public:
                virtual ~IPlaybackRestrictions(){}

                /**
                 *  Returns the offset, as xs:duration, from the beginning of the scope of the Service Description until the rest of the presentation may be skipped.
                 *  The default \c "PT0S" means skipping is allowed everywhere. \n\n
                 *  Corresponds to the \c \@skipAfter attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetSkipAfter    ()  const = 0;
        };
    }
}

#endif /* IPLAYBACKRESTRICTIONS_H_ */
