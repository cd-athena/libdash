/*
 * Location.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LOCATION_H_
#define LOCATION_H_

#include "config.h"

#include "ILocation.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class Location : public ILocation, public AbstractMPDElement
        {
            public:
                Location             ();
                virtual ~Location    ();

                const std::string&  GetUrl              ()  const;
                const std::string&  GetServiceLocation  ()  const;

                void    SetUrl              (const std::string& url);
                void    SetServiceLocation  (const std::string& serviceLocation);

            private:
                std::string url;
                std::string serviceLocation;
        };
    }
}

#endif /* LOCATION_H_ */
