/*
 * Timeline.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef TIMELINE_H_
#define TIMELINE_H_

#include "config.h"

#include "ITimeline.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class Timeline : public ITimeline, public AbstractMPDElement
        {
            public:
                Timeline             ();
                virtual ~Timeline    ();

                uint64_t    GetStartTime            ()  const;
                uint64_t    GetNumber               ()  const;
                uint64_t    GetDuration             ()  const;
                int64_t     GetRepeatCount          ()  const;
                uint32_t    GetSegmentsInSequence   ()  const;
                uint32_t    GetPatternId            ()  const;
                bool        HasPattern              ()  const;
                uint32_t    GetPatternEntry         ()  const;
                uint32_t    GetSsp                  ()  const;
                bool        HasSsp                  ()  const;

                void    SetStartTime            (uint64_t startTime);
                void    SetNumber               (uint64_t number);
                void    SetDuration             (uint64_t duration);
                void    SetRepeatCount          (int64_t repeatCount);
                void    SetSegmentsInSequence   (uint32_t segmentsInSequence);
                void    SetPatternId            (uint32_t patternId);
                void    SetPatternEntry         (uint32_t patternEntry);
                void    SetSsp                  (uint32_t ssp);

            private:
                uint64_t    startTime;
                uint64_t    number;
                uint64_t    duration;
                int64_t     repeatCount;
                uint32_t    segmentsInSequence;
                uint32_t    patternId;
                bool        hasPattern;
                uint32_t    patternEntry;
                uint32_t    ssp;
                bool        hasSsp;
        };
    }
}

#endif /* TIMELINE_H_ */
