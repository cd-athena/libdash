/*
 * MPDWalker.cpp
 *****************************************************************************
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "MPDWalker.h"

using namespace dash;
using namespace dash::mpd;

MPDWalker::MPDWalker    () :
            elements(0),
            segments(0),
            sink(0),
            doubleSink(0)
{
}

unsigned long                       MPDWalker::GetElementCount      () const
{
    return this->elements;
}
unsigned long                       MPDWalker::GetSegmentCount      () const
{
    return this->segments;
}
const std::map<std::string, int>&   MPDWalker::GetUnknownElements   () const
{
    return this->unknownElements;
}

void    MPDWalker::Use                  (const std::string& value)
{
    this->sink += value.size();
}
void    MPDWalker::Use                  (uint64_t value)
{
    this->sink += value;
}
void    MPDWalker::Use                  (double value)
{
    this->doubleSink += value;
}
void    MPDWalker::Use                  (const std::vector<std::string>& values)
{
    for (size_t i = 0; i < values.size(); i++)
        Use(values[i]);
}
void    MPDWalker::Use                  (const std::vector<uint32_t>& values)
{
    for (size_t i = 0; i < values.size(); i++)
        Use((uint64_t) values[i]);
}

void    MPDWalker::Element              (const IMPDElement *element)
{
    if (!element)
        return;

    this->elements++;

    std::vector<xml::INode *> subNodes = element->GetAdditionalSubNodes();
    for (size_t i = 0; i < subNodes.size(); i++)
        if (!subNodes[i]->GetName().empty())
            this->unknownElements[subNodes[i]->GetName()]++;

    Use((uint64_t) element->GetRawAttributes().size());
}
void    MPDWalker::Descriptor           (const IDescriptor *descriptor)
{
    if (!descriptor)
        return;

    Element(descriptor);
    Use(descriptor->GetSchemeIdUri());
    Use(descriptor->GetValue());
    Use(descriptor->GetId());
}
void    MPDWalker::Descriptors          (const std::vector<IDescriptor *>& descriptors)
{
    for (size_t i = 0; i < descriptors.size(); i++)
        Descriptor(descriptors[i]);
}
void    MPDWalker::BaseUrls             (const std::vector<IBaseUrl *>& baseUrls)
{
    for (size_t i = 0; i < baseUrls.size(); i++)
    {
        Element(baseUrls[i]);
        Use(baseUrls[i]->GetUrl());
        Use(baseUrls[i]->GetServiceLocation());
        Use(baseUrls[i]->GetByteRange());
        Use(baseUrls[i]->GetAvailabilityTimeOffset());
        Use((uint64_t) baseUrls[i]->IsAvailabilityTimeComplete());
    }
}
void    MPDWalker::RequestParams        (const std::vector<IExtendedUrlInfo *>& requestParams)
{
    for (size_t i = 0; i < requestParams.size(); i++)
    {
        const IExtendedUrlInfo *param = requestParams[i];
        Element(param);
        Use(param->GetQueryTemplate());
        Use((uint64_t) param->UseMPDUrlQuery());
        Use(param->GetQueryString());
        Use(param->GetXlinkHref());
        Use(param->GetIncludeInRequests());
        Use(param->GetHeaderParamSource());
        Use((uint64_t) param->IsSameOriginOnly());
        Use(param->GetHeader());
    }
}
void    MPDWalker::URLType              (const IURLType *urlType)
{
    if (!urlType)
        return;

    Element(urlType);
    Use(urlType->GetSourceURL());
    Use(urlType->GetRange());
}
void    MPDWalker::SegmentBase          (const ISegmentBase *segmentBase)
{
    if (!segmentBase)
        return;

    Element(segmentBase);
    URLType(segmentBase->GetInitialization());
    URLType(segmentBase->GetRepresentationIndex());

    const IFailoverContent *failoverContent = segmentBase->GetFailoverContent();
    if (failoverContent)
    {
        Element(failoverContent);
        for (size_t i = 0; i < failoverContent->GetFCS().size(); i++)
            Element(failoverContent->GetFCS()[i]);
    }

    Use((uint64_t) segmentBase->GetTimescale());
    Use((uint64_t) segmentBase->GetEptDelta());
    Use((uint64_t) segmentBase->GetPdDelta());
    Use(segmentBase->GetPresentationTimeOffset());
    Use(segmentBase->GetPresentationDuration());
    Use(segmentBase->GetTimeShiftBufferDepth());
    Use(segmentBase->GetIndexRange());
    Use((uint64_t) segmentBase->HasIndexRangeExact());
    Use(segmentBase->GetAvailabilityTimeOffset());
    Use((uint64_t) segmentBase->IsAvailabilityTimeComplete());
}
void    MPDWalker::MultipleSegmentBase  (const IMultipleSegmentBase *multipleSegmentBase)
{
    if (!multipleSegmentBase)
        return;

    SegmentBase(multipleSegmentBase);
    URLType(multipleSegmentBase->GetBitstreamSwitching());
    Use((uint64_t) multipleSegmentBase->GetDuration());
    Use((uint64_t) multipleSegmentBase->GetStartNumber());
    Use((uint64_t) multipleSegmentBase->GetEndNumber());
    Use((double) multipleSegmentBase->GetTolerance());
    Use(multipleSegmentBase->GetEndSubNumber());
    Use(multipleSegmentBase->GetSegmentsInSequence());

    const ISegmentTimeline *timeline = multipleSegmentBase->GetSegmentTimeline();
    if (!timeline)
        return;

    Element(timeline);
    for (size_t i = 0; i < timeline->GetTimelines().size(); i++)
    {
        const ITimeline *s = timeline->GetTimelines()[i];
        Element(s);
        Use(s->GetStartTime());
        Use(s->GetNumber());
        Use(s->GetDuration());
        Use((uint64_t) s->GetRepeatCount());
        Use((uint64_t) s->GetSegmentsInSequence());
        Use((uint64_t) s->GetPatternId());
        Use((uint64_t) s->GetPatternEntry());
        Use((uint64_t) s->GetSsp());
    }
    for (size_t i = 0; i < timeline->GetPatterns().size(); i++)
    {
        const IPattern *pattern = timeline->GetPatterns()[i];
        Element(pattern);
        Use(pattern->GetId());
        for (size_t j = 0; j < pattern->GetRunLengths().size(); j++)
        {
            const IRunLength *runLength = pattern->GetRunLengths()[j];
            Element(runLength);
            Use(runLength->GetDuration());
            Use((uint64_t) runLength->GetRepeatCount());
            Use((uint64_t) runLength->GetSegmentsInSequence());
            Use((uint64_t) runLength->GetSsp());
        }
    }
}
void    MPDWalker::SegmentList          (const ISegmentList *segmentList)
{
    if (!segmentList)
        return;

    MultipleSegmentBase(segmentList);
    Use(segmentList->GetXlinkHref());
    for (size_t i = 0; i < segmentList->GetSegmentURLs().size(); i++)
    {
        const ISegmentURL *segmentUrl = segmentList->GetSegmentURLs()[i];
        Element(segmentUrl);
        Use(segmentUrl->GetMediaURI());
        Use(segmentUrl->GetMediaRange());
        Use(segmentUrl->GetIndexURI());
        Use(segmentUrl->GetIndexRange());
    }
}
void    MPDWalker::SegmentTemplate      (const ISegmentTemplate *segmentTemplate, const std::vector<IBaseUrl *>& baseUrls,
                                         const std::string& representationId, uint32_t bandwidth)
{
    if (!segmentTemplate)
        return;

    MultipleSegmentBase(segmentTemplate);
    Use(segmentTemplate->Getmedia());
    Use(segmentTemplate->Getindex());
    Use(segmentTemplate->Getinitialization());
    Use(segmentTemplate->GetbitstreamSwitching());

    if (representationId.empty() || segmentTemplate->Getmedia().empty())
        return;

    ISegment *segment = segmentTemplate->GetMediaSegmentFromNumber(baseUrls, representationId, bandwidth, segmentTemplate->GetStartNumber());
    if (segment)
    {
        this->segments++;
        delete segment;
    }
    if (!segmentTemplate->Getinitialization().empty())
    {
        ISegment *initialization = segmentTemplate->ToInitializationSegment(baseUrls, representationId, bandwidth);
        if (initialization)
        {
            this->segments++;
            delete initialization;
        }
    }
}
void    MPDWalker::ServiceDescription   (const IServiceDescription *serviceDescription)
{
    Element(serviceDescription);
    Use((uint64_t) serviceDescription->GetId());
    Descriptors(serviceDescription->GetScope());

    for (size_t i = 0; i < serviceDescription->GetLatency().size(); i++)
        Element(serviceDescription->GetLatency()[i]);
    for (size_t i = 0; i < serviceDescription->GetPlaybackRate().size(); i++)
        Element(serviceDescription->GetPlaybackRate()[i]);
    for (size_t i = 0; i < serviceDescription->GetOperatingQuality().size(); i++)
        Element(serviceDescription->GetOperatingQuality()[i]);
    for (size_t i = 0; i < serviceDescription->GetOperatingBandwidth().size(); i++)
        Element(serviceDescription->GetOperatingBandwidth()[i]);
    for (size_t i = 0; i < serviceDescription->GetContentSteerings().size(); i++)
    {
        const IContentSteering *steering = serviceDescription->GetContentSteerings()[i];
        Element(steering);
        Use(steering->GetUrl());
        Use(steering->GetDefaultServiceLocations());
        Use((uint64_t) steering->IsQueryBeforeStart());
        Use((uint64_t) steering->HasClientRequirement());
    }
    for (size_t i = 0; i < serviceDescription->GetClientDataReportings().size(); i++)
    {
        const IClientDataReporting *reporting = serviceDescription->GetClientDataReportings()[i];
        Descriptor(reporting);
        Use(reporting->GetServiceLocations());
        Use(reporting->GetAdaptationSets());
        for (size_t j = 0; j < reporting->GetCMCDParameters().size(); j++)
        {
            const ICMCDParameters *cmcd = reporting->GetCMCDParameters()[j];
            Element(cmcd);
            Use((uint64_t) cmcd->GetVersion());
            Use(cmcd->GetMode());
            Use(cmcd->GetIncludeInRequests());
            Use(cmcd->GetKeys());
            Use(cmcd->GetContentID());
            Use(cmcd->GetSessionID());
        }
    }
    for (size_t i = 0; i < serviceDescription->GetPlaybackRestrictions().size(); i++)
    {
        Element(serviceDescription->GetPlaybackRestrictions()[i]);
        Use(serviceDescription->GetPlaybackRestrictions()[i]->GetSkipAfter());
    }
}
void    MPDWalker::AlternativeMPDEvent  (const IAlternativeMPDEvent *event)
{
    if (!event)
        return;

    Element(event);
    Use(event->GetUri());
    Use(event->GetEarliestResolutionTimeOffset());
    Use((uint64_t) event->GetServiceDescriptionId());
    Use(event->GetMaxDuration());
    Use((uint64_t) event->IsExecuteOnce());
    Use((uint64_t) event->GetNoJump());
    Use(event->GetSkipAfter());
    Descriptors(event->GetSupplementalProperties());
}
void    MPDWalker::EventStreams         (const std::vector<IEventStream *>& eventStreams)
{
    for (size_t i = 0; i < eventStreams.size(); i++)
    {
        const IEventStream *eventStream = eventStreams[i];
        Element(eventStream);
        Use(eventStream->GetSchemeIdUri());
        Use(eventStream->GetValue());
        Use((uint64_t) eventStream->GetTimescale());
        Use(eventStream->GetPresentationTimeOffset());
        Use(eventStream->GetXlinkHref());
        BaseUrls(eventStream->GetBaseURLs());
        RequestParams(eventStream->GetRequestParams());
        Descriptors(eventStream->GetEssentialProperties());
        Descriptors(eventStream->GetSupplementalProperties());

        for (size_t j = 0; j < eventStream->GetEvents().size(); j++)
        {
            const IEvent *event = eventStream->GetEvents()[j];
            Element(event);
            Use(event->GetPresentationTime());
            Use(event->GetDuration());
            Use(event->GetId());
            Use(event->GetMessageData());
            Use(event->GetStatus());
            Use(event->GetContent());

            const ISelectionInfo *selectionInfo = event->GetSelectionInfo();
            if (selectionInfo)
            {
                Element(selectionInfo);
                Use(selectionInfo->GetSelectionInfo());
                Use(selectionInfo->GetContactURL());
                for (size_t k = 0; k < selectionInfo->GetSelections().size(); k++)
                {
                    Element(selectionInfo->GetSelections()[k]);
                    Use(selectionInfo->GetSelections()[k]->GetParameter());
                    Use(selectionInfo->GetSelections()[k]->GetData());
                }
            }
            for (size_t k = 0; k < event->GetServiceDescriptions().size(); k++)
                ServiceDescription(event->GetServiceDescriptions()[k]);

            AlternativeMPDEvent(event->GetInsertPresentation());
            const IAlternativeMPDReplaceEvent *replace = event->GetReplacePresentation();
            if (replace)
            {
                AlternativeMPDEvent(replace);
                Use(replace->GetReturnOffset());
                Use((uint64_t) replace->IsClip());
                Use((uint64_t) replace->IsStartWithOffset());
            }
            Descriptors(event->GetSupplementalProperties());
            Descriptors(event->GetEssentialProperties());
        }
    }
}
void    MPDWalker::RepresentationBase   (const IRepresentationBase *representationBase)
{
    Element(representationBase);
    Descriptors(representationBase->GetFramePacking());
    Descriptors(representationBase->GetAudioChannelConfiguration());
    Descriptor(representationBase->GetOutputProtection());

    for (size_t i = 0; i < representationBase->GetContentProtections().size(); i++)
    {
        const IContentProtection *contentProtection = representationBase->GetContentProtections()[i];
        Descriptor(contentProtection);
        Use(contentProtection->GetRobustness());
        Use(contentProtection->GetRefId());
        Use(contentProtection->GetRef());
    }
    Descriptors(representationBase->GetEssentialProperties());
    Descriptors(representationBase->GetSupplementalProperties());
    EventStreams(representationBase->GetEventStreams());

    for (size_t i = 0; i < representationBase->GetSwitchings().size(); i++)
        Element(representationBase->GetSwitchings()[i]);
    for (size_t i = 0; i < representationBase->GetRandomAccesses().size(); i++)
        Element(representationBase->GetRandomAccesses()[i]);
    for (size_t i = 0; i < representationBase->GetGroupLabels().size(); i++)
        Element(representationBase->GetGroupLabels()[i]);
    for (size_t i = 0; i < representationBase->GetLabels().size(); i++)
        Element(representationBase->GetLabels()[i]);
    for (size_t i = 0; i < representationBase->GetContentPopularityRates().size(); i++)
        Element(representationBase->GetContentPopularityRates()[i]);
    for (size_t i = 0; i < representationBase->GetProducerReferenceTimes().size(); i++)
        Element(representationBase->GetProducerReferenceTimes()[i]);
    for (size_t i = 0; i < representationBase->GetResyncs().size(); i++)
        Element(representationBase->GetResyncs()[i]);
    for (size_t i = 0; i < representationBase->GetSegmentSequenceProperties().size(); i++)
    {
        const ISegmentSequenceProperties *properties = representationBase->GetSegmentSequenceProperties()[i];
        Element(properties);
        Use((uint64_t) properties->GetSapType());
        Use((uint64_t) properties->GetCadence());
        Use((uint64_t) properties->HasEvent());
        Use(properties->GetAlignment());
    }

    Use(representationBase->GetProfiles());
    Use((uint64_t) representationBase->GetWidth());
    Use((uint64_t) representationBase->GetHeight());
    Use(representationBase->GetSar());
    Use(representationBase->GetFrameRate());
    Use(representationBase->GetAudioSamplingRate());
    Use(representationBase->GetMimeType());
    Use(representationBase->GetCodecs());
    Use(representationBase->GetSegmentProfiles());
    Use((uint64_t) representationBase->GetStartWithSAP());
    Use(representationBase->GetScanType());
    Use(representationBase->GetTag());
}
void    MPDWalker::AdaptationSets       (const std::vector<IAdaptationSet *>& adaptationSets,
                                         const std::vector<IBaseUrl *>& baseUrls, const ISegmentTemplate *periodTemplate)
{
    for (size_t i = 0; i < adaptationSets.size(); i++)
    {
        const IAdaptationSet *adaptationSet = adaptationSets[i];
        RepresentationBase(adaptationSet);
        Descriptors(adaptationSet->GetAccessibility());
        Descriptors(adaptationSet->GetRole());
        Descriptors(adaptationSet->GetRating());
        Descriptors(adaptationSet->GetViewpoint());
        for (size_t j = 0; j < adaptationSet->GetContentComponent().size(); j++)
        {
            Element(adaptationSet->GetContentComponent()[j]);
            Descriptors(adaptationSet->GetContentComponent()[j]->GetRole());
        }
        BaseUrls(adaptationSet->GetBaseURLs());
        RequestParams(adaptationSet->GetRequestParams());
        SegmentBase(adaptationSet->GetSegmentBase());
        SegmentList(adaptationSet->GetSegmentList());
        Use((uint64_t) adaptationSet->GetId());
        Use(adaptationSet->GetLang());
        Use(adaptationSet->GetContentType());
        Use((uint64_t) adaptationSet->GetMaxBandwidth());
        Use((uint64_t) adaptationSet->GetSubsegmentStartsWithSAP());
        Use(adaptationSet->GetInitializationSetRef());

        std::vector<IBaseUrl *> adaptationSetBaseUrls = baseUrls;
        adaptationSetBaseUrls.insert(adaptationSetBaseUrls.end(), adaptationSet->GetBaseURLs().begin(), adaptationSet->GetBaseURLs().end());
        const ISegmentTemplate *adaptationSetTemplate = adaptationSet->GetSegmentTemplate() ? adaptationSet->GetSegmentTemplate() : periodTemplate;
        SegmentTemplate(adaptationSet->GetSegmentTemplate(), adaptationSetBaseUrls, "", 0);

        for (size_t j = 0; j < adaptationSet->GetRepresentation().size(); j++)
        {
            const IRepresentation *representation = adaptationSet->GetRepresentation()[j];
            RepresentationBase(representation);
            BaseUrls(representation->GetBaseURLs());
            RequestParams(representation->GetRequestParams());
            for (size_t k = 0; k < representation->GetExtendedBandwidths().size(); k++)
                Element(representation->GetExtendedBandwidths()[k]);
            for (size_t k = 0; k < representation->GetSubRepresentations().size(); k++)
            {
                RepresentationBase(representation->GetSubRepresentations()[k]);
                Use((uint64_t) representation->GetSubRepresentations()[k]->GetLevel());
            }
            SegmentBase(representation->GetSegmentBase());
            SegmentList(representation->GetSegmentList());
            Use(representation->GetId());
            Use((uint64_t) representation->GetBandwidth());
            Use(representation->GetDependencyId());
            Use(representation->GetAssociationId());

            std::vector<IBaseUrl *> representationBaseUrls = adaptationSetBaseUrls;
            representationBaseUrls.insert(representationBaseUrls.end(), representation->GetBaseURLs().begin(), representation->GetBaseURLs().end());
            const ISegmentTemplate *segmentTemplate = representation->GetSegmentTemplate() ? representation->GetSegmentTemplate() : adaptationSetTemplate;
            SegmentTemplate(segmentTemplate, representationBaseUrls, representation->GetId(), representation->GetBandwidth());
        }
    }
}

void    MPDWalker::Walk                 (const IMPD *mpd)
{
    Element(mpd);
    Use(mpd->GetType());
    Use(mpd->GetMinBufferTime());
    Use(mpd->GetProfiles());
    Use(mpd->GetMediaPresentationDuration());

    for (size_t i = 0; i < mpd->GetProgramInformations().size(); i++)
    {
        Element(mpd->GetProgramInformations()[i]);
        Use(mpd->GetProgramInformations()[i]->GetTitle());
    }
    BaseUrls(mpd->GetBaseUrls());
    RequestParams(mpd->GetRequestParams());
    Use(mpd->GetLocations());
    for (size_t i = 0; i < mpd->GetLocationElements().size(); i++)
    {
        Element(mpd->GetLocationElements()[i]);
        Use(mpd->GetLocationElements()[i]->GetServiceLocation());
    }
    for (size_t i = 0; i < mpd->GetPatchLocations().size(); i++)
    {
        Element(mpd->GetPatchLocations()[i]);
        Use(mpd->GetPatchLocations()[i]->GetUrl());
        Use(mpd->GetPatchLocations()[i]->GetServiceLocation());
    }
    for (size_t i = 0; i < mpd->GetServiceDescriptions().size(); i++)
        ServiceDescription(mpd->GetServiceDescriptions()[i]);
    for (size_t i = 0; i < mpd->GetInitializationSets().size(); i++)
        RepresentationBase(mpd->GetInitializationSets()[i]);
    for (size_t i = 0; i < mpd->GetContentProtections().size(); i++)
        Descriptor(mpd->GetContentProtections()[i]);
    Descriptors(mpd->GetEssentialProperties());
    Descriptors(mpd->GetSupplementalProperties());
    Descriptors(mpd->GetUTCTimings());
    for (size_t i = 0; i < mpd->GetMetrics().size(); i++)
    {
        Element(mpd->GetMetrics()[i]);
        Descriptors(mpd->GetMetrics()[i]->GetReportings());
    }
    Element(mpd->GetLeapSecondInformation());
    if (mpd->GetContentSteering())
    {
        Element(mpd->GetContentSteering());
        Use(mpd->GetContentSteering()->GetUrl());
    }

    for (size_t p = 0; p < mpd->GetPeriods().size(); p++)
    {
        const IPeriod *period = mpd->GetPeriods()[p];
        Element(period);
        Use(period->GetId());
        Use(period->GetStart());
        Use(period->GetDuration());
        Use(period->GetMinBufferTime());
        BaseUrls(period->GetBaseURLs());
        RequestParams(period->GetRequestParams());
        SegmentBase(period->GetSegmentBase());
        SegmentList(period->GetSegmentList());
        MultipleSegmentBase(period->GetSegmentTemplate());
        Descriptor(period->GetAssetIdentifier());
        EventStreams(period->GetEventStreams());
        for (size_t i = 0; i < period->GetServiceDescriptions().size(); i++)
            ServiceDescription(period->GetServiceDescriptions()[i]);
        for (size_t i = 0; i < period->GetContentProtections().size(); i++)
            Descriptor(period->GetContentProtections()[i]);
        Descriptors(period->GetSupplementalProperties());
        for (size_t i = 0; i < period->GetSubsets().size(); i++)
        {
            Element(period->GetSubsets()[i]);
            Use(period->GetSubsets()[i]->Contains());
        }
        for (size_t i = 0; i < period->GetPreselections().size(); i++)
        {
            RepresentationBase(period->GetPreselections()[i]);
            Descriptors(period->GetPreselections()[i]->GetRole());
        }
        if (period->GetImportedMPD())
        {
            Element(period->GetImportedMPD());
            Use(period->GetImportedMPD()->GetUrl());
            Use(period->GetImportedMPD()->GetEarliestResolutionTimeOffset());
        }

        std::vector<IBaseUrl *> baseUrls = mpd->GetBaseUrls();
        baseUrls.insert(baseUrls.end(), period->GetBaseURLs().begin(), period->GetBaseURLs().end());
        AdaptationSets(period->GetAdaptationSets(), baseUrls, period->GetSegmentTemplate());
        AdaptationSets(period->GetEmptyAdaptationSets(), baseUrls, period->GetSegmentTemplate());
    }
}
