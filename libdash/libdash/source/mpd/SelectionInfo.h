/*
 * SelectionInfo.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef SELECTIONINFO_H_
#define SELECTIONINFO_H_

#include "config.h"

#include "ISelectionInfo.h"
#include "AbstractMPDElement.h"
#include "Selection.h"

namespace dash
{
    namespace mpd
    {
        class SelectionInfo : public ISelectionInfo, public AbstractMPDElement
        {
            public:
                SelectionInfo             ();
                virtual ~SelectionInfo    ();

                const std::string&                  GetSelectionInfo    ()  const;
                const std::string&                  GetContactURL       ()  const;
                const std::vector<ISelection *>&    GetSelections       ()  const;

                void    SetSelectionInfo    (const std::string& selectionInfo);
                void    SetContactURL       (const std::string& contactURL);
                void    AddSelection        (Selection *selection);

            private:
                std::string                 selectionInfo;
                std::string                 contactURL;
                std::vector<Selection *>    selections;
        };
    }
}

#endif /* SELECTIONINFO_H_ */
