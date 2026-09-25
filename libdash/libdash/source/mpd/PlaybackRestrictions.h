/*
 * PlaybackRestrictions.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef PLAYBACKRESTRICTIONS_H_
#define PLAYBACKRESTRICTIONS_H_

#include "config.h"

#include "IPlaybackRestrictions.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class PlaybackRestrictions : public IPlaybackRestrictions, public AbstractMPDElement
        {
            public:
                PlaybackRestrictions             ();
                virtual ~PlaybackRestrictions    ();

                const std::string&  GetSkipAfter    ()  const;

                void    SetSkipAfter    (const std::string& skipAfter);

            private:
                std::string skipAfter;
        };
    }
}

#endif /* PLAYBACKRESTRICTIONS_H_ */
