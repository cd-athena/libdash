/**
 *  @class      dash::mpd::IExtendedUrlInfo
 *  @brief      This interface is needed for accessing <tt><b>RequestParam</b></tt>, <tt><b>ExtUrlQueryInfo</b></tt> and <tt><b>ExtHttpHeaderInfo</b></tt> elements
 *              (type <tt><b>ExtendedUrlInfoType</b></tt>) as specified in <em>ISO/IEC 23009-1, 6th edition</em>, Annex I.3.
 *  @details    ExtendedUrlInfoType extends dash::mpd::IUrlQueryInfo with the requests that carry the parameters, the HTTP responses
 *              header values are taken from, an origin restriction, and an optional output HTTP header. See Table I.3. \n
 *              <tt><b>RequestParam</b></tt> elements are used with the \c "urn:mpeg:dash:urlparam:2025" scheme, signalled by an MPD EssentialProperty.
 *  @see        dash::mpd::IUrlQueryInfo dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef IEXTENDEDURLINFO_H_
#define IEXTENDEDURLINFO_H_

#include "config.h"

#include "IUrlQueryInfo.h"

namespace dash
{
    namespace mpd
    {
        class IExtendedUrlInfo : public IUrlQueryInfo
        {
            public:
                virtual ~IExtendedUrlInfo(){}

                /**
                 *  Returns the keys (Annex I.3.6) of the HTTP GET requests that carry the parameters, e.g. \c "segment", \c "mpd",
                 *  \c "steering", \c "altmpd" or \c "callback". Default: \c "segment". \n\n
                 *  Corresponds to the whitespace-separated \c \@includeInRequests attribute.
                 *  @return     a reference to a vector of strings
                 */
                virtual const std::vector<std::string>& GetIncludeInRequests    ()  const = 0;

                /**
                 *  Returns the keys (Annex I.3.6) of the HTTP responses from which header values, identified by \c $header:<header-name>$
                 *  in \c \@queryTemplate, are extracted. Default per the XML schema: \c "segment". \n\n
                 *  Corresponds to the whitespace-separated \c \@headerParamSource attribute.
                 *  @return     a reference to a vector of strings
                 */
                virtual const std::vector<std::string>& GetHeaderParamSource    ()  const = 0;

                /**
                 *  Returns whether parameters are only sent to the same origin (IETF RFC 6454) they were instantiated from. Default: false. \n\n
                 *  Corresponds to the \c \@sameOriginOnly attribute.
                 *  @return     a bool value
                 */
                virtual bool                            IsSameOriginOnly        ()  const = 0;

                /**
                 *  Returns the name of the HTTP header the final query string is written to. If empty, the output is written into a query parameter. \n\n
                 *  Corresponds to the \c \@header attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&              GetHeader               ()  const = 0;
        };
    }
}

#endif /* IEXTENDEDURLINFO_H_ */
