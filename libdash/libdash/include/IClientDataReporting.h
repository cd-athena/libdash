/**
 *  @class      dash::mpd::IClientDataReporting
 *  @brief      This interface is needed for accessing <tt><b>ClientDataReporting</b></tt> elements of a <tt><b>ServiceDescription</b></tt>
 *              as specified in <em>ISO/IEC 23009-1, 6th edition</em> (Annex K.3.7, Tables K.7 and K.16).
 *  @details    ClientDataReportingType extends DescriptorType: \c \@schemeIdUri identifies the reporting system, e.g. \c "urn:mpeg:dash:cta-5004:2023"
 *              for CMCD, with the specification version as \c \@value. \c \@serviceLocations and \c \@adaptationSets filter the requests
 *              that are reported; if both are present, reporting applies to their intersection.
 *  @see        dash::mpd::IDescriptor dash::mpd::ICMCDParameters dash::mpd::IServiceDescription
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef ICLIENTDATAREPORTING_H_
#define ICLIENTDATAREPORTING_H_

#include "config.h"

#include "IDescriptor.h"
#include "ICMCDParameters.h"

namespace dash
{
    namespace mpd
    {
        class IClientDataReporting : public IDescriptor
        {
            public:
                virtual ~IClientDataReporting(){}

                /**
                 *  Returns the Service Locations (subclause 5.6.6) for which reporting is enabled. Empty means all Service Locations of the MPD. \n\n
                 *  Corresponds to the space-separated \c \@serviceLocations attribute.
                 *  @return     a reference to a vector of strings
                 */
                virtual const std::vector<std::string>&         GetServiceLocations     ()  const = 0;

                /**
                 *  Returns the \c \@id values of the Adaptation Sets for which reporting is applied. Empty means all eligible Adaptation Sets. \n\n
                 *  Corresponds to the space-separated \c \@adaptationSets attribute.
                 *  @return     a reference to a vector of unsigned integers
                 */
                virtual const std::vector<uint32_t>&            GetAdaptationSets       ()  const = 0;

                /**
                 *  Returns a reference to a vector of pointers to dash::mpd::ICMCDParameters objects, which correspond to the <tt><b>CMCDParameters</b></tt> elements.
                 *  @return     a reference to a vector of pointers to dash::mpd::ICMCDParameters objects
                 */
                virtual const std::vector<ICMCDParameters *>&   GetCMCDParameters       ()  const = 0;
        };
    }
}

#endif /* ICLIENTDATAREPORTING_H_ */
