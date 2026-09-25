/*
 * Pattern.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "Pattern.h"

using namespace dash::mpd;

Pattern::Pattern    ()  :
            id(0)
{
}
Pattern::~Pattern   ()
{
    for (size_t i = 0; i < this->runLengths.size(); i++)
        delete(this->runLengths.at(i));
}

uint64_t                            Pattern::GetId          ()  const
{
    return this->id;
}
void                                Pattern::SetId          (uint64_t id)
{
    this->id = id;
}
const std::vector<IRunLength *>&    Pattern::GetRunLengths  ()  const
{
    return (std::vector<IRunLength *> &) this->runLengths;
}
void                                Pattern::AddRunLength   (RunLength *runLength)
{
    if (runLength != NULL)
        this->runLengths.push_back(runLength);
}
