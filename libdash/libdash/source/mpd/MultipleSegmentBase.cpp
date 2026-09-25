/*
 * MultipleSegmentBase.cpp
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

#include "MultipleSegmentBase.h"

using namespace dash::mpd;

MultipleSegmentBase::MultipleSegmentBase    () :
                        bitstreamSwitching(NULL),
                        segmentTimeline(NULL),
                        duration(0),
                        startNumber(1),
                        endNumber(1),
                        tolerance(50.0f),
                        endSubNumber(0),
                        hasEndSubNumber(false),
                        segmentsInSequence(1),
                        hasSegmentsInSequence(false)
{
}
MultipleSegmentBase::~MultipleSegmentBase   ()
{
    delete(this->segmentTimeline);
    delete(this->bitstreamSwitching);
}

const ISegmentTimeline *    MultipleSegmentBase::GetSegmentTimeline     ()  const
{
    return (ISegmentTimeline *) this->segmentTimeline;
}
void                        MultipleSegmentBase::SetSegmentTimeline     (SegmentTimeline *segmentTimeline)
{
    this->segmentTimeline = segmentTimeline;
}
const IURLType*             MultipleSegmentBase::GetBitstreamSwitching  ()  const
{
    return this->bitstreamSwitching;
}
void                        MultipleSegmentBase::SetBitstreamSwitching  (URLType *bitstreamSwitching)
{
    this->bitstreamSwitching = bitstreamSwitching;
}
uint32_t                    MultipleSegmentBase::GetDuration            ()  const
{
    return this->duration;
}
void                        MultipleSegmentBase::SetDuration            (uint32_t duration)
{
    this->duration = duration;
}
uint32_t                    MultipleSegmentBase::GetStartNumber         ()  const
{
    return this->startNumber;
}
void                        MultipleSegmentBase::SetStartNumber         (uint32_t startNumber)
{
    this->startNumber = startNumber;
}
uint32_t                    MultipleSegmentBase::GetEndNumber           ()  const
{
    return this->endNumber;
}
void                        MultipleSegmentBase::SetEndNumber           (uint32_t endNumber)
{
    this->endNumber = endNumber;
}
float                       MultipleSegmentBase::GetTolerance           ()  const
{
    return this->tolerance;
}
void                        MultipleSegmentBase::SetTolerance           (float tolerance)
{
    this->tolerance = tolerance;
}
uint64_t                    MultipleSegmentBase::GetEndSubNumber        ()  const
{
    return this->endSubNumber;
}
bool                        MultipleSegmentBase::HasEndSubNumber        ()  const
{
    return this->hasEndSubNumber;
}
void                        MultipleSegmentBase::SetEndSubNumber        (uint64_t endSubNumber)
{
    this->endSubNumber    = endSubNumber;
    this->hasEndSubNumber = true;
}
uint64_t                    MultipleSegmentBase::GetSegmentsInSequence  ()  const
{
    return this->segmentsInSequence;
}
bool                        MultipleSegmentBase::HasSegmentsInSequence  ()  const
{
    return this->hasSegmentsInSequence;
}
void                        MultipleSegmentBase::SetSegmentsInSequence  (uint64_t segmentsInSequence)
{
    this->segmentsInSequence    = segmentsInSequence;
    this->hasSegmentsInSequence = true;
}
