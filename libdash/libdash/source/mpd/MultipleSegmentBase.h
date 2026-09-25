/*
 * MultipleSegmentBase.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * @contributor        Daniele Lorenzi
 * @contributoremail   lorenzidaniele.97@gmail.com
 * @contributiondate   2021
 * 
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef MULTIPLESEGMENTBASE_H_
#define MULTIPLESEGMENTBASE_H_

#include "config.h"

#include "IMultipleSegmentBase.h"
#include "SegmentBase.h"
#include "SegmentTimeline.h"
#include "URLType.h"

namespace dash
{
    namespace mpd
    {
        class MultipleSegmentBase : public virtual IMultipleSegmentBase, public SegmentBase
        {
            public:
                MultipleSegmentBase             ();
                virtual ~MultipleSegmentBase    ();

                const ISegmentTimeline*                 GetSegmentTimeline      ()  const;
                const IURLType*                         GetBitstreamSwitching   ()  const;
                uint32_t                                GetDuration             ()  const;
                uint32_t                                GetStartNumber          ()  const;
                uint32_t                                GetEndNumber            ()  const;
                float                                   GetTolerance            ()  const;
                uint64_t                                GetEndSubNumber         ()  const;
                bool                                    HasEndSubNumber         ()  const;
                uint64_t                                GetSegmentsInSequence   ()  const;
                bool                                    HasSegmentsInSequence   ()  const;

                void    SetSegmentTimeline      (SegmentTimeline *segmentTimeline);
                void    SetBitstreamSwitching   (URLType *bitstreamSwitching);
                void    SetDuration             (uint32_t duration);
                void    SetStartNumber          (uint32_t startNumber);
                void    SetEndNumber            (uint32_t endNumber);
                void    SetTolerance            (float tolerance);
                void    SetEndSubNumber         (uint64_t endSubNumber);
                void    SetSegmentsInSequence   (uint64_t segmentsInSequence);

            protected:
                SegmentTimeline                 *segmentTimeline;
                URLType                         *bitstreamSwitching;
                uint32_t                        duration;
                uint32_t                        startNumber;
                uint32_t                        endNumber;
                float                           tolerance;
                uint64_t                        endSubNumber;
                bool                            hasEndSubNumber;
                uint64_t                        segmentsInSequence;
                bool                            hasSegmentsInSequence;
        };
    }
}

#endif /* MULTIPLESEGMENTBASE_H_ */
