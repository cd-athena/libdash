/*
 * Descriptor.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * @contributor        Daniele Lorenzi
 * @contributoremail   lorenzidaniele.97@gmail.com
 * @contributiondate   2021
 * 
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

#include "config.h"

#include "IDescriptor.h"
#include "AbstractMPDElement.h"

namespace dash
{
    namespace mpd
    {
        /*
         * Implementation of the DescriptorType attributes, shared by Descriptor and ContentProtection.
         * DescriptorInterface (IDescriptor or an interface derived from it) is the first, non-virtual base,
         * because the getters of the containing elements return std::vector<Descriptor *> reinterpreted as
         * std::vector<IDescriptor *>, which requires the interface subobject at offset 0.
         */
        template <class DescriptorInterface>
        class DescriptorBase : public DescriptorInterface, public AbstractMPDElement
        {
            public:
                DescriptorBase          () : schemeIdUri(""), value(""), id("") {}
                virtual ~DescriptorBase () {}

                const std::string&      GetSchemeIdUri  () const    { return this->schemeIdUri; }
                const std::string&      GetValue        () const    { return this->value; }
                const std::string&      GetId           () const    { return this->id; }

                void    SetValue        (const std::string& value)          { this->value = value; }
                void    SetSchemeIdUri  (const std::string& schemeIdUri)    { this->schemeIdUri = schemeIdUri; }
                void    SetId           (const std::string& id)             { this->id = id; }

            protected:
                std::string  schemeIdUri;
                std::string  value;
                std::string  id;
        };

        class Descriptor : public DescriptorBase<IDescriptor>
        {
            public:
                Descriptor          ();
                virtual ~Descriptor ();
        };
    }
}

#endif /* DESCRIPTOR_H_ */
