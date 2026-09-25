/*
 * Pattern.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef PATTERN_H_
#define PATTERN_H_

#include "config.h"

#include "IPattern.h"
#include "AbstractMPDElement.h"
#include "RunLength.h"

namespace dash
{
    namespace mpd
    {
        class Pattern : public IPattern, public AbstractMPDElement
        {
            public:
                Pattern             ();
                virtual ~Pattern    ();

                uint64_t                            GetId           ()  const;
                const std::vector<IRunLength *>&    GetRunLengths   ()  const;

                void    SetId           (uint64_t id);
                void    AddRunLength    (RunLength *runLength);

            private:
                uint64_t                    id;
                std::vector<RunLength *>    runLengths;
        };
    }
}

#endif /* PATTERN_H_ */
