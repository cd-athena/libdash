/*
 * MPDWalker.h
 *****************************************************************************
 * Walks the complete libdash object tree of an MPD and calls every getter, so
 * that crashes, invalid pointers and uninitialised values show up in tests
 * (especially in builds with AddressSanitizer and UndefinedBehaviorSanitizer).
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef MPDWALKER_H_
#define MPDWALKER_H_

#include "libdash.h"

#include <map>
#include <string>
#include <vector>

class MPDWalker
{
    public:
        MPDWalker   ();

        void    Walk    (const dash::mpd::IMPD *mpd);

        unsigned long                       GetElementCount     () const;
        unsigned long                       GetSegmentCount     () const;
        const std::map<std::string, int>&   GetUnknownElements  () const;

    private:
        void    Element                 (const dash::mpd::IMPDElement *element);
        void    Descriptor              (const dash::mpd::IDescriptor *descriptor);
        void    Descriptors             (const std::vector<dash::mpd::IDescriptor *>& descriptors);
        void    BaseUrls                (const std::vector<dash::mpd::IBaseUrl *>& baseUrls);
        void    RequestParams           (const std::vector<dash::mpd::IExtendedUrlInfo *>& requestParams);
        void    URLType                 (const dash::mpd::IURLType *urlType);
        void    SegmentBase             (const dash::mpd::ISegmentBase *segmentBase);
        void    MultipleSegmentBase     (const dash::mpd::IMultipleSegmentBase *multipleSegmentBase);
        void    SegmentList             (const dash::mpd::ISegmentList *segmentList);
        void    SegmentTemplate         (const dash::mpd::ISegmentTemplate *segmentTemplate, const std::vector<dash::mpd::IBaseUrl *>& baseUrls,
                                         const std::string& representationId, uint32_t bandwidth);
        void    ServiceDescription      (const dash::mpd::IServiceDescription *serviceDescription);
        void    AlternativeMPDEvent     (const dash::mpd::IAlternativeMPDEvent *event);
        void    EventStreams            (const std::vector<dash::mpd::IEventStream *>& eventStreams);
        void    RepresentationBase      (const dash::mpd::IRepresentationBase *representationBase);
        void    AdaptationSets          (const std::vector<dash::mpd::IAdaptationSet *>& adaptationSets,
                                         const std::vector<dash::mpd::IBaseUrl *>& baseUrls, const dash::mpd::ISegmentTemplate *periodTemplate);

        void    Use                     (const std::string& value);
        void    Use                     (uint64_t value);
        void    Use                     (double value);
        void    Use                     (const std::vector<std::string>& values);
        void    Use                     (const std::vector<uint32_t>& values);

        unsigned long               elements;
        unsigned long               segments;
        std::map<std::string, int>  unknownElements;
        uint64_t                    sink;       // every value read is added here, so that it is really read
        double                      doubleSink;
};

#endif /* MPDWALKER_H_ */
