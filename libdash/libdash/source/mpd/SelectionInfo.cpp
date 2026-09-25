/*
 * SelectionInfo.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "SelectionInfo.h"

using namespace dash::mpd;

SelectionInfo::SelectionInfo    ()  :
                selectionInfo(""),
                contactURL("")
{
}
SelectionInfo::~SelectionInfo   ()
{
    for (size_t i = 0; i < this->selections.size(); i++)
        delete(this->selections.at(i));
}

const std::string&                  SelectionInfo::GetSelectionInfo ()  const
{
    return this->selectionInfo;
}
void                                SelectionInfo::SetSelectionInfo (const std::string& selectionInfo)
{
    this->selectionInfo = selectionInfo;
}
const std::string&                  SelectionInfo::GetContactURL    ()  const
{
    return this->contactURL;
}
void                                SelectionInfo::SetContactURL    (const std::string& contactURL)
{
    this->contactURL = contactURL;
}
const std::vector<ISelection *>&    SelectionInfo::GetSelections    ()  const
{
    return (std::vector<ISelection *> &) this->selections;
}
void                                SelectionInfo::AddSelection     (Selection *selection)
{
    if (selection != NULL)
        this->selections.push_back(selection);
}
