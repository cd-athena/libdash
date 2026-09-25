/*
 * PlaybackRate.cpp
 *****************************************************************************
 * Name: Daniele Lorenzi
 * Email: lorenzidaniele.97@gmail.com
 * Date: 2021
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "PlaybackRate.h"

using namespace dash::mpd;

PlaybackRate::PlaybackRate    () :
                max(0),
                min(0)
{
}
PlaybackRate::~PlaybackRate   ()
{
}

double                                     PlaybackRate::GetMax                      ()  const
{
    return this->max;
}
void                                       PlaybackRate::SetMax                      (double max)
{
    this->max = max;
}
double                                     PlaybackRate::GetMin                      ()  const
{
    return this->min;
}
void                                       PlaybackRate::SetMin                      (double min)
{
    this->min = min;
}