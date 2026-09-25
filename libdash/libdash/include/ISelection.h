/**
 *  @class      dash::mpd::ISelection
 *  @brief      This interface is needed for accessing <tt><b>Selection</b></tt> elements of a <tt><b>SelectionInfo</b></tt> as specified in <em>ISO/IEC 23009-1, 6th edition</em>, Annex L.3.4 (Table L.2).
 *  @details    A Selection describes one choice of a nonlinear storyline: the \c \@parameter identifies an available Period (or a custom value understood by the server),
 *              \c \@data carries interactive data for the application.
 *  @see        dash::mpd::ISelectionInfo dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef ISELECTION_H_
#define ISELECTION_H_

#include "config.h"

#include "IMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class ISelection : public virtual IMPDElement
        {
            public:
                virtual ~ISelection(){}

                /**
                 *  Returns the encoding of \c \@data, e.g. \c "base64" (IETF RFC 4648). Empty if not encoded.
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetDataEncoding     ()  const = 0;

                /**
                 *  Returns the identifier of the available Period (or custom parameter) for this choice. Unique within the SelectionInfo element.
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetParameter        ()  const = 0;

                /**
                 *  Returns the interactive data for the application for the \c \@parameter Period.
                 *  @return     a reference to a string
                 */
                virtual const std::string&  GetData             ()  const = 0;
        };
    }
}

#endif /* ISELECTION_H_ */
