/*
 * SegmentSequenceProperties.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef SEGMENTSEQUENCEPROPERTIES_H_
#define SEGMENTSEQUENCEPROPERTIES_H_

#include "config.h"

#include "ISegmentSequenceProperties.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class SegmentSequenceProperties : public ISegmentSequenceProperties, public AbstractMPDElement
        {
            public:
                SegmentSequenceProperties             ();
                virtual ~SegmentSequenceProperties    ();

                uint32_t                        GetSapType      ()  const;
                uint32_t                        GetCadence      ()  const;
                bool                            HasEvent        ()  const;
                const std::vector<std::string>& GetAlignment    ()  const;

                void    SetSapType      (uint32_t sapType);
                void    SetCadence      (uint32_t cadence);
                void    SetEvent        (bool event);
                void    SetAlignment    (const std::string& alignment);

            private:
                uint32_t                    sapType;
                uint32_t                    cadence;
                bool                        event;
                std::vector<std::string>    alignment;
        };
    }
}

#endif /* SEGMENTSEQUENCEPROPERTIES_H_ */
