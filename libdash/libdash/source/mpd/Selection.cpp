/*
 * Selection.cpp
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "Selection.h"

using namespace dash::mpd;

Selection::Selection    ()  :
            dataEncoding(""),
            parameter(""),
            data("")
{
}
Selection::~Selection   ()
{
}

const std::string&  Selection::GetDataEncoding  ()  const
{
    return this->dataEncoding;
}
void                Selection::SetDataEncoding  (const std::string& dataEncoding)
{
    this->dataEncoding = dataEncoding;
}
const std::string&  Selection::GetParameter     ()  const
{
    return this->parameter;
}
void                Selection::SetParameter     (const std::string& parameter)
{
    this->parameter = parameter;
}
const std::string&  Selection::GetData          ()  const
{
    return this->data;
}
void                Selection::SetData          (const std::string& data)
{
    this->data = data;
}
