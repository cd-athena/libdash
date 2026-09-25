/**
 *  @class      dash::mpd::ISelectionInfo
 *  @brief      This interface is needed for accessing <tt><b>SelectionInfo</b></tt> elements of an <tt><b>Event</b></tt> as specified in <em>ISO/IEC 23009-1, 6th edition</em>, Annex L.3.4 (Table L.1).
 *  @details    SelectionInfo carries the selection information of a nonlinear storyline event (Event Stream scheme \c "urn:mpeg:dash:nonlinearplayback:2020"):
 *              the data common to all choices and one dash::mpd::ISelection per choice. Event@presentationTime and Event@duration give the selection window.
 *  @see        dash::mpd::ISelection dash::mpd::IEvent dash::mpd::IMPDElement
 *
 *  @version    2.2
 *  @date       2026
 */

#ifndef ISELECTIONINFO_H_
#define ISELECTIONINFO_H_

#include "config.h"

#include "IMPDElement.h"
#include "ISelection.h"

namespace dash
{
    namespace mpd
    {
        class ISelectionInfo : public virtual IMPDElement
        {
            public:
                virtual ~ISelectionInfo(){}

                /**
                 *  Returns information on the possible selections for the client. \n\n
                 *  Corresponds to the \c \@selectionInfo attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&                  GetSelectionInfo    ()  const = 0;

                /**
                 *  Returns the URL the client contacts to signal the selected choice, e.g. <tt>.../selection?parameter=blue</tt>. \n\n
                 *  Corresponds to the mandatory \c \@contactURL attribute.
                 *  @return     a reference to a string
                 */
                virtual const std::string&                  GetContactURL       ()  const = 0;

                /**
                 *  Returns a reference to a vector of pointers to dash::mpd::ISelection objects, one per choice.
                 *  @return     a reference to a vector of pointers to dash::mpd::ISelection objects
                 */
                virtual const std::vector<ISelection *>&    GetSelections       ()  const = 0;
        };
    }
}

#endif /* ISELECTIONINFO_H_ */
