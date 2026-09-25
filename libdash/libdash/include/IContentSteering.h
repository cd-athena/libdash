/**
 *  @class      dash::mpd::IContentSteering
 *  @brief      This interface is needed for accessing <tt><b>ContentSteering</b></tt> elements as specified in <em>ISO/IEC 23009-1, 6th edition</em>
 *              (Table 3, Annex K.3.6, Tables K.6 and K.15).
 *  @details    The element content is the URL of the Content Steering server. It references a DASH Content Steering Manifest (DCSM)
 *              as defined in ETSI TS 103 998; a resolved resource that is not a DCSM is ignored.
 *              The element may be present once in the <tt><b>MPD</b></tt> and in <tt><b>ServiceDescription</b></tt> elements.
 *  @see        dash::mpd::IMPD dash::mpd::IServiceDescription dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef ICONTENTSTEERING_H_
#define ICONTENTSTEERING_H_

#include "config.h"

#include "IMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class IContentSteering : public virtual IMPDElement
        {
            public:
                virtual ~IContentSteering(){}

                /**
                 *  Returns the URL of the Content Steering server (the element content), with surrounding whitespace removed.
                 *  @return     a reference to a string
                 */
                virtual const std::string&              GetUrl                          ()  const = 0;

                /**
                 *  Returns the \c \@defaultServiceLocation attribute as signalled. It names the Service Location(s) the client should use
                 *  when multiple accesses exist, e.g. when no Content Steering server is available or before it has responded.
                 *  @return     a reference to a string
                 */
                virtual const std::string&              GetDefaultServiceLocation       ()  const = 0;

                /**
                 *  Returns the entries of \c \@defaultServiceLocation. Table K.6 defines it as a space-separated list of Service Locations
                 *  (the XML schema type does not allow whitespace, so a schema-valid MPD has at most one entry).
                 *  @return     a reference to a vector of strings
                 */
                virtual const std::vector<std::string>& GetDefaultServiceLocations      ()  const = 0;

                /**
                 *  Returns whether the player is expected to resolve the response from the Steering Server prior to starting playback. Default: false. \n\n
                 *  Corresponds to the \c \@queryBeforeStart attribute.
                 *  @return     a bool value
                 */
                virtual bool                            IsQueryBeforeStart              ()  const = 0;

                /**
                 *  Returns whether a client in the context of the Service Description shall follow the content steering rules of ETSI TS 103 998.
                 *  If false, the client either ignores the Content Steering instructions or follows them as if this flag were true. Default: true. \n\n
                 *  Corresponds to the \c \@clientRequirement attribute.
                 *  @return     a bool value
                 */
                virtual bool                            HasClientRequirement            ()  const = 0;
        };
    }
}

#endif /* ICONTENTSTEERING_H_ */
