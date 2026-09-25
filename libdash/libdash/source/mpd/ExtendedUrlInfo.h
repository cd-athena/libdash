/*
 * ExtendedUrlInfo.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef EXTENDEDURLINFO_H_
#define EXTENDEDURLINFO_H_

#include "config.h"

#include "IExtendedUrlInfo.h"
#include "UrlQueryInfo.h"

namespace dash
{
    namespace mpd
    {
        class ExtendedUrlInfo : public UrlQueryInfoBase<IExtendedUrlInfo>
        {
            public:
                ExtendedUrlInfo             ();
                virtual ~ExtendedUrlInfo    ();

                const std::vector<std::string>& GetIncludeInRequests    ()  const;
                const std::vector<std::string>& GetHeaderParamSource    ()  const;
                bool                            IsSameOriginOnly        ()  const;
                const std::string&              GetHeader               ()  const;

                void    SetIncludeInRequests    (const std::string& includeInRequests);
                void    SetHeaderParamSource    (const std::string& headerParamSource);
                void    SetSameOriginOnly       (bool sameOriginOnly);
                void    SetHeader               (const std::string& header);

            private:
                static void SplitWhitespace     (const std::string& value, std::vector<std::string>& entries);

                std::vector<std::string>    includeInRequests;
                std::vector<std::string>    headerParamSource;
                bool                        sameOriginOnly;
                std::string                 header;
        };
    }
}

#endif /* EXTENDEDURLINFO_H_ */
