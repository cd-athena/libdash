/*
 * RunLength.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "RunLength.h"

using namespace dash::mpd;

RunLength::RunLength    ()  :
            duration(0),
            repeatCount(0),
            segmentsInSequence(1),
            ssp(0),
            hasSsp(false)
{
}
RunLength::~RunLength   ()
{
}

uint64_t    RunLength::GetDuration              ()  const
{
    return this->duration;
}
void        RunLength::SetDuration              (uint64_t duration)
{
    this->duration = duration;
}
uint32_t    RunLength::GetRepeatCount           ()  const
{
    return this->repeatCount;
}
void        RunLength::SetRepeatCount           (uint32_t repeatCount)
{
    this->repeatCount = repeatCount;
}
uint32_t    RunLength::GetSegmentsInSequence    ()  const
{
    return this->segmentsInSequence;
}
void        RunLength::SetSegmentsInSequence    (uint32_t segmentsInSequence)
{
    this->segmentsInSequence = segmentsInSequence;
}
uint32_t    RunLength::GetSsp                   ()  const
{
    return this->ssp;
}
bool        RunLength::HasSsp                   ()  const
{
    return this->hasSsp;
}
void        RunLength::SetSsp                   (uint32_t ssp)
{
    this->ssp    = ssp;
    this->hasSsp = true;
}
