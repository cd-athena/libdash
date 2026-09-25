/*
 * CMCDParameters.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef CMCDPARAMETERS_H_
#define CMCDPARAMETERS_H_

#include "config.h"

#include "ICMCDParameters.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class CMCDParameters : public ICMCDParameters, public AbstractMPDElement
        {
            public:
                CMCDParameters             ();
                virtual ~CMCDParameters    ();

                uint32_t                        GetVersion              ()  const;
                const std::string&              GetMode                 ()  const;
                const std::vector<std::string>& GetIncludeInRequests    ()  const;
                const std::vector<std::string>& GetKeys                 ()  const;
                const std::string&              GetContentID            ()  const;
                const std::string&              GetSessionID            ()  const;

                void    SetVersion              (uint32_t version);
                void    SetMode                 (const std::string& mode);
                void    SetIncludeInRequests    (const std::string& includeInRequests);
                void    SetKeys                 (const std::string& keys);
                void    SetContentID            (const std::string& contentID);
                void    SetSessionID            (const std::string& sessionID);

            private:
                static void SplitWhitespace     (const std::string& value, std::vector<std::string>& entries);

                uint32_t                    version;
                std::string                 mode;
                std::vector<std::string>    includeInRequests;
                std::vector<std::string>    keys;
                std::string                 contentID;
                std::string                 sessionID;
        };
    }
}

#endif /* CMCDPARAMETERS_H_ */
