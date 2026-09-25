/*
 * Timeline.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "Timeline.h"

using namespace dash::mpd;

Timeline::Timeline    ()  :
                startTime(0),
                number(0),
                duration(0),
                repeatCount(0),
                segmentsInSequence(1)
{
}
Timeline::~Timeline   ()
{
}

uint64_t    Timeline::GetStartTime          ()  const
{
    return this->startTime;
}
void        Timeline::SetStartTime          (uint64_t startTime)
{
    this->startTime = startTime;
}
uint64_t    Timeline::GetNumber             ()  const
{
    return this->number;
}
void        Timeline::SetNumber             (uint64_t number)
{
    this->number = number;
}
uint64_t    Timeline::GetDuration           ()  const
{
    return this->duration;
}
void        Timeline::SetDuration           (uint64_t duration)
{
    this->duration = duration;
}
int64_t     Timeline::GetRepeatCount        ()  const
{
    return this->repeatCount;
}
void        Timeline::SetRepeatCount        (int64_t repeatCount)
{
    this->repeatCount = repeatCount;
}
uint32_t    Timeline::GetSegmentsInSequence ()  const
{
    return this->segmentsInSequence;
}
void        Timeline::SetSegmentsInSequence (uint32_t segmentsInSequence)
{
    this->segmentsInSequence = segmentsInSequence;
}
