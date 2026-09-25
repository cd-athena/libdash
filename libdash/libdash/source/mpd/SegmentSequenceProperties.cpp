/*
 * SegmentSequenceProperties.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "SegmentSequenceProperties.h"

using namespace dash::mpd;

SegmentSequenceProperties::SegmentSequenceProperties    ()  :
                            sapType(0),
                            cadence(1),
                            event(true)
{
}
SegmentSequenceProperties::~SegmentSequenceProperties   ()
{
}

uint32_t                        SegmentSequenceProperties::GetSapType   ()  const
{
    return this->sapType;
}
void                            SegmentSequenceProperties::SetSapType   (uint32_t sapType)
{
    this->sapType = sapType;
}
uint32_t                        SegmentSequenceProperties::GetCadence   ()  const
{
    return this->cadence;
}
void                            SegmentSequenceProperties::SetCadence   (uint32_t cadence)
{
    this->cadence = cadence;
}
bool                            SegmentSequenceProperties::HasEvent     ()  const
{
    return this->event;
}
void                            SegmentSequenceProperties::SetEvent     (bool event)
{
    this->event = event;
}
const std::vector<std::string>& SegmentSequenceProperties::GetAlignment ()  const
{
    return this->alignment;
}
void                            SegmentSequenceProperties::SetAlignment (const std::string& alignment)
{
    std::istringstream stream(alignment);
    std::string        entry;

    this->alignment.clear();
    while (stream >> entry)
        this->alignment.push_back(entry);
}
