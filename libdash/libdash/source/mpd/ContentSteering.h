/*
 * ContentSteering.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef CONTENTSTEERING_H_
#define CONTENTSTEERING_H_

#include "config.h"

#include "IContentSteering.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class ContentSteering : public IContentSteering, public AbstractMPDElement
        {
            public:
                ContentSteering             ();
                virtual ~ContentSteering    ();

                const std::string&              GetUrl                          ()  const;
                const std::string&              GetDefaultServiceLocation       ()  const;
                const std::vector<std::string>& GetDefaultServiceLocations      ()  const;
                bool                            IsQueryBeforeStart              ()  const;
                bool                            HasClientRequirement            ()  const;

                void    SetUrl                      (const std::string& url);
                void    SetDefaultServiceLocation   (const std::string& defaultServiceLocation);
                void    SetQueryBeforeStart         (bool queryBeforeStart);
                void    SetClientRequirement        (bool clientRequirement);

            private:
                std::string                 url;
                std::string                 defaultServiceLocation;
                std::vector<std::string>    defaultServiceLocations;
                bool                        queryBeforeStart;
                bool                        clientRequirement;
        };
    }
}

#endif /* CONTENTSTEERING_H_ */
