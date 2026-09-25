/*
 * ClientDataReporting.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef CLIENTDATAREPORTING_H_
#define CLIENTDATAREPORTING_H_

#include "config.h"

#include "IClientDataReporting.h"
#include "Descriptor.h"
#include "CMCDParameters.h"

namespace dash
{
    namespace mpd
    {
        class ClientDataReporting : public DescriptorBase<IClientDataReporting>
        {
            public:
                ClientDataReporting             ();
                virtual ~ClientDataReporting    ();

                const std::vector<std::string>&         GetServiceLocations     ()  const;
                const std::vector<uint32_t>&            GetAdaptationSets       ()  const;
                const std::vector<ICMCDParameters *>&   GetCMCDParameters       ()  const;

                void    SetServiceLocations     (const std::string& serviceLocations);
                void    SetAdaptationSets       (const std::string& adaptationSets);
                void    AddCMCDParameters       (CMCDParameters *cmcdParameters);

            private:
                std::vector<std::string>        serviceLocations;
                std::vector<uint32_t>           adaptationSets;
                std::vector<CMCDParameters *>   cmcdParameters;
        };
    }
}

#endif /* CLIENTDATAREPORTING_H_ */
