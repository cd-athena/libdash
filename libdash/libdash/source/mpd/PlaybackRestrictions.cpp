/*
 * PlaybackRestrictions.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "PlaybackRestrictions.h"

using namespace dash::mpd;

PlaybackRestrictions::PlaybackRestrictions  ()  :
                        skipAfter("PT0S")
{
}
PlaybackRestrictions::~PlaybackRestrictions ()
{
}

const std::string&  PlaybackRestrictions::GetSkipAfter  ()  const
{
    return this->skipAfter;
}
void                PlaybackRestrictions::SetSkipAfter  (const std::string& skipAfter)
{
    this->skipAfter = skipAfter;
}
