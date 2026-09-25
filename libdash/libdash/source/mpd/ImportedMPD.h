/*
 * ImportedMPD.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef IMPORTEDMPD_H_
#define IMPORTEDMPD_H_

#include "config.h"

#include "IImportedMPD.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        class ImportedMPD : public IImportedMPD, public AbstractMPDElement
        {
            public:
                ImportedMPD             ();
                virtual ~ImportedMPD    ();

                const std::string&  GetUrl                              ()  const;
                double              GetEarliestResolutionTimeOffset     ()  const;

                void    SetUrl                              (const std::string& url);
                void    SetEarliestResolutionTimeOffset     (double earliestResolutionTimeOffset);

            private:
                std::string url;
                double      earliestResolutionTimeOffset;
        };
    }
}

#endif /* IMPORTEDMPD_H_ */
