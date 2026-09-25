/**
 *  @class      dash::mpd::IUrlQueryInfo
 *  @brief      This interface is needed for accessing the attributes of elements of type <tt><b>UrlQueryInfoType</b></tt> as specified in <em>ISO/IEC 23009-1, 6th edition</em>, Annex I.2.
 *  @details    UrlQueryInfoType describes how to build a URL query string for requests such as media Segment requests.
 *              The query string comes from the MPD URL (\c \@useMPDUrlQuery), from \c \@queryString, or from \c \@queryString after XLink resolution;
 *              \c \@queryTemplate selects and orders the parameters that are used. See Table I.1.
 *  @see        dash::mpd::IExtendedUrlInfo dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef IURLQUERYINFO_H_
#define IURLQUERYINFO_H_

#include "config.h"

#include "IMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class IUrlQueryInfo : public virtual IMPDElement
        {
            public:
                virtual ~IUrlQueryInfo(){}

                /**
                 *  Returns the URL parameters template, containing one or more \c $<ParamIdentifier>$ template identifiers (Table I.2)
                 *  that are replaced to build the query string. \n\n
                 *  Corresponds to the \c \@queryTemplate attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetQueryTemplate    ()  const = 0;

                /**
                 *  Returns whether the URL parameters of the URL used to download the latest MPD or MPD Patch are used to construct
                 *  the output URLs. Default: false. \n\n
                 *  Corresponds to the \c \@useMPDUrlQuery attribute.
                 *  @return     a bool value
                 */
                virtual bool                UseMPDUrlQuery      ()  const = 0;

                /**
                 *  Returns the query string used to construct the output URLs, e.g. \c "a=X&b=Y" or scheme-dependent \c "a=$urn:XYZ$". \n\n
                 *  Corresponds to the \c \@queryString attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetQueryString      ()  const = 0;

                /**
                 *  Returns a reference to a remote element of this type.
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetXlinkHref        ()  const = 0;

                /**
                 *  Returns the XLink processing instruction, \c "onLoad" or \c "onRequest" (default).
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetXlinkActuate     ()  const = 0;

                /**
                 *  Returns the W3C XLINK type, fixed to \c "simple".
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetXlinkType        ()  const = 0;

                /**
                 *  Returns the W3C XLINK show behaviour, fixed to \c "embed".
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetXlinkShow        ()  const = 0;
        };
    }
}

#endif /* IURLQUERYINFO_H_ */
