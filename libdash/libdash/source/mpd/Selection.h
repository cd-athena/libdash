/*
 * Selection.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef SELECTION_H_
#define SELECTION_H_

#include "config.h"

#include "ISelection.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class Selection : public ISelection, public AbstractMPDElement
        {
            public:
                Selection             ();
                virtual ~Selection    ();

                const std::string&  GetDataEncoding     ()  const;
                const std::string&  GetParameter        ()  const;
                const std::string&  GetData             ()  const;

                void    SetDataEncoding     (const std::string& dataEncoding);
                void    SetParameter        (const std::string& parameter);
                void    SetData             (const std::string& data);

            private:
                std::string dataEncoding;
                std::string parameter;
                std::string data;
        };
    }
}

#endif /* SELECTION_H_ */
