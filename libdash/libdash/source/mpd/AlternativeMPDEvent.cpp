/*
 * AlternativeMPDEvent.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "AlternativeMPDEvent.h"

using namespace dash::mpd;

AlternativeMPDEvent::AlternativeMPDEvent    ()
{
}
AlternativeMPDEvent::~AlternativeMPDEvent   ()
{
}

AlternativeMPDReplaceEvent::AlternativeMPDReplaceEvent  ()  :
                                returnOffset(0),
                                hasReturnOffset(false),
                                clip(true),
                                startWithOffset(false)
{
}
AlternativeMPDReplaceEvent::~AlternativeMPDReplaceEvent ()
{
}

uint64_t    AlternativeMPDReplaceEvent::GetReturnOffset     ()  const
{
    return this->returnOffset;
}
bool        AlternativeMPDReplaceEvent::HasReturnOffset     ()  const
{
    return this->hasReturnOffset;
}
void        AlternativeMPDReplaceEvent::SetReturnOffset     (uint64_t returnOffset)
{
    this->returnOffset    = returnOffset;
    this->hasReturnOffset = true;
}
bool        AlternativeMPDReplaceEvent::IsClip              ()  const
{
    return this->clip;
}
void        AlternativeMPDReplaceEvent::SetClip             (bool clip)
{
    this->clip = clip;
}
bool        AlternativeMPDReplaceEvent::IsStartWithOffset   ()  const
{
    return this->startWithOffset;
}
void        AlternativeMPDReplaceEvent::SetStartWithOffset  (bool startWithOffset)
{
    this->startWithOffset = startWithOffset;
}
