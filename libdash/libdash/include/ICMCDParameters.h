/**
 *  @class      dash::mpd::ICMCDParameters
 *  @brief      This interface is needed for accessing <tt><b>CMCDParameters</b></tt> elements as specified in <em>ISO/IEC 23009-1, 6th edition</em>
 *              (Annex K.3.7, Tables K.8 and K.17).
 *  @details    CMCDParameters configure Common Media Client Data (CMCD, CTA-5004) reporting inside a <tt><b>ClientDataReporting</b></tt>
 *              element with \c \@schemeIdUri \c "urn:mpeg:dash:cta-5004:2023".
 *  @see        dash::mpd::IClientDataReporting dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef ICMCDPARAMETERS_H_
#define ICMCDPARAMETERS_H_

#include "config.h"

#include "IMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class ICMCDParameters : public virtual IMPDElement
        {
            public:
                virtual ~ICMCDParameters(){}

                /**
                 *  Returns the highest CMCD version (CTA-5004) accepted by the reporting server. Default: 1. \n\n
                 *  Corresponds to the \c \@version attribute.
                 *  @return     an unsigned integer
                 */
                virtual uint32_t                        GetVersion              ()  const = 0;

                /**
                 *  Returns the transmission mode for CMCD data, \c "query" (CTA-5004 subclause 2.2, default) or \c "header" (subclause 2.1). \n\n
                 *  Corresponds to the \c \@mode attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&              GetMode                 ()  const = 0;

                /**
                 *  Returns the keys of the HTTP GET requests that include CMCD data, with the semantics of \c \@includeInRequests
                 *  in Table I.3 (see dash::mpd::IExtendedUrlInfo). Default: \c "segment".
                 *  @return     a reference to a vector of strings
                 */
                virtual const std::vector<std::string>& GetIncludeInRequests    ()  const = 0;

                /**
                 *  Returns the CMCD keys to be reported (CTA-5004). Unsupported keys are to be ignored by the client. \n\n
                 *  Corresponds to the mandatory, space-separated \c \@keys attribute.
                 *  @return     a reference to a vector of strings
                 */
                virtual const std::vector<std::string>& GetKeys                 ()  const = 0;

                /**
                 *  Returns the value of the Content ID (\c cid) key, at most 64 characters. If empty, Table K.8 defines how to derive it. \n\n
                 *  Corresponds to the \c \@contentID attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&              GetContentID            ()  const = 0;

                /**
                 *  Returns the value of the Session ID (\c sid) key, at most 64 characters. If empty, Table K.8 defines how to derive it
                 *  (ultimately a client-generated UUID). \n\n
                 *  Corresponds to the \c \@sessionID attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&              GetSessionID            ()  const = 0;
        };
    }
}

#endif /* ICMCDPARAMETERS_H_ */
