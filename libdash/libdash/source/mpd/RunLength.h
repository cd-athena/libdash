/*
 * RunLength.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef RUNLENGTH_H_
#define RUNLENGTH_H_

#include "config.h"

#include "IRunLength.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class RunLength : public IRunLength, public AbstractMPDElement
        {
            public:
                RunLength             ();
                virtual ~RunLength    ();

                uint64_t    GetDuration             ()  const;
                uint32_t    GetRepeatCount          ()  const;
                uint32_t    GetSegmentsInSequence   ()  const;
                uint32_t    GetSsp                  ()  const;
                bool        HasSsp                  ()  const;

                void    SetDuration             (uint64_t duration);
                void    SetRepeatCount          (uint32_t repeatCount);
                void    SetSegmentsInSequence   (uint32_t segmentsInSequence);
                void    SetSsp                  (uint32_t ssp);

            private:
                uint64_t    duration;
                uint32_t    repeatCount;
                uint32_t    segmentsInSequence;
                uint32_t    ssp;
                bool        hasSsp;
        };
    }
}

#endif /* RUNLENGTH_H_ */
