/*
 * UrlQueryInfo.h
 *****************************************************************************
 * Date: 2026
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef URLQUERYINFO_H_
#define URLQUERYINFO_H_

#include "config.h"

#include "IUrlQueryInfo.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        /*
         * Implementation of the UrlQueryInfoType attributes (ISO/IEC 23009-1 Annex I.2), shared by elements whose type
         * extends UrlQueryInfoType. UrlQueryInfoInterface (IUrlQueryInfo or an interface derived from it) is the first,
         * non-virtual base, so that vectors of implementation pointers can be returned as vectors of interface pointers.
         */
        template <class UrlQueryInfoInterface>
        class UrlQueryInfoBase : public UrlQueryInfoInterface, public AbstractMPDElement
        {
            public:
                UrlQueryInfoBase            () :
                    queryTemplate(""), useMPDUrlQuery(false), queryString(""),
                    xlinkHref(""), xlinkActuate("onRequest"), xlinkType("simple"), xlinkShow("embed") {}
                virtual ~UrlQueryInfoBase   () {}

                const std::string&  GetQueryTemplate    ()  const   { return this->queryTemplate; }
                bool                UseMPDUrlQuery      ()  const   { return this->useMPDUrlQuery; }
                const std::string&  GetQueryString      ()  const   { return this->queryString; }
                const std::string&  GetXlinkHref        ()  const   { return this->xlinkHref; }
                const std::string&  GetXlinkActuate     ()  const   { return this->xlinkActuate; }
                const std::string&  GetXlinkType        ()  const   { return this->xlinkType; }
                const std::string&  GetXlinkShow        ()  const   { return this->xlinkShow; }

                void    SetQueryTemplate    (const std::string& queryTemplate)  { this->queryTemplate  = queryTemplate; }
                void    SetUseMPDUrlQuery   (bool useMPDUrlQuery)               { this->useMPDUrlQuery = useMPDUrlQuery; }
                void    SetQueryString      (const std::string& queryString)    { this->queryString    = queryString; }
                void    SetXlinkHref        (const std::string& xlinkHref)      { this->xlinkHref      = xlinkHref; }
                void    SetXlinkActuate     (const std::string& xlinkActuate)   { this->xlinkActuate   = xlinkActuate; }
                void    SetXlinkType        (const std::string& xlinkType)      { this->xlinkType      = xlinkType; }
                void    SetXlinkShow        (const std::string& xlinkShow)      { this->xlinkShow      = xlinkShow; }

            protected:
                std::string queryTemplate;
                bool        useMPDUrlQuery;
                std::string queryString;
                std::string xlinkHref;
                std::string xlinkActuate;
                std::string xlinkType;
                std::string xlinkShow;
        };
    }
}

#endif /* URLQUERYINFO_H_ */
