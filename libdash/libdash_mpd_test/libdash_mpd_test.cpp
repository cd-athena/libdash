/*
 * libdash_mpd_test.cpp
 *****************************************************************************
 * MPD parser tests.
 *
 *   libdash_mpd_test fields    <pre6ed_fields.mpd>        checks parsed values
 *   libdash_mpd_test sequences <segment_sequences.mpd>    checks segment sequences and duration patterns
 *   libdash_mpd_test urlparams <url_parameters.mpd>       checks RequestParam and EventStream children
 *   libdash_mpd_test steering  <content_steering.mpd>     checks ContentSteering and @serviceLocation
 *   libdash_mpd_test cmcd      <cmcd.mpd>                 checks ClientDataReporting and CMCDParameters
 *   libdash_mpd_test smoke  <file.mpd>...         checks that every file parses
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "libdash.h"

#include <cstdio>
#include <cstring>

using namespace dash;
using namespace dash::mpd;

static int failures = 0;

#define CHECK(expr)                                                     \
    do {                                                                \
        bool ok_ = (expr);                                              \
        printf("%s  %s\n", ok_ ? "PASS" : "FAIL", #expr);               \
        if (!ok_) failures++;                                           \
    } while (0)

static int TestFields (IDASHManager *manager, char *path)
{
    IMPD *mpd = manager->Open(path);
    CHECK(mpd != NULL);
    if (!mpd)
        return 1;

    IPeriod *period = mpd->GetPeriods().at(0);

    IEventStream *eventStream = period->GetEventStreams().at(0);
    CHECK(eventStream->GetXlinkType() == "simple");
    CHECK(eventStream->GetXlinkShow() == "embed");
    CHECK(eventStream->GetPresentationTimeOffset() == 8589934592ULL);

    CHECK(period->GetEmptyAdaptationSets().size() == 1);
    CHECK(period->GetEmptyAdaptationSets().at(0)->GetId() == 9);
    CHECK(period->GetAdaptationSets().size() == 2);

    IAdaptationSet *video = period->GetAdaptationSets().at(0);
    CHECK(video->GetMaxHeight() == 1080);
    CHECK(video->GetSubsegmentStartsWithSAP() == 1);

    // Descriptors returned through vector getters (regression: virtual inheritance broke the pointers)
    CHECK(video->GetRole().size() == 1 && video->GetRole().at(0)->GetValue() == "main");
    CHECK(video->GetContentProtections().size() == 1 && video->GetContentProtections().at(0)->GetValue() == "cenc");
    CHECK(video->GetContentProtections().size() == 1 && video->GetContentProtections().at(0)->GetRobustness() == "HW_SECURE");
    CHECK(video->GetContentProtections().size() == 1 && video->GetContentProtections().at(0)->GetSchemeIdUri() == "urn:mpeg:dash:mp4protection:2011");
    IRepresentation *videoRepresentation = video->GetRepresentation().at(0);
    CHECK(videoRepresentation->GetSupplementalProperties().size() == 1 && videoRepresentation->GetSupplementalProperties().at(0)->GetId() == "sp1");

    ISegmentTemplate *segmentTemplate = video->GetSegmentTemplate();
    CHECK(segmentTemplate->GetPresentationTimeOffset() == 5000000000ULL);
    CHECK(segmentTemplate->GetFailoverContent() != NULL);
    CHECK(segmentTemplate->GetFailoverContent() && segmentTemplate->GetFailoverContent()->GetFCS().size() == 1);
    CHECK(segmentTemplate->GetAdditionalSubNodes().empty());

    ITimeline *s0 = segmentTemplate->GetSegmentTimeline()->GetTimelines().at(0);
    CHECK(s0->GetStartTime() == 5000000000ULL);
    CHECK(s0->GetNumber() == 42);
    CHECK(s0->GetDuration() == 180000);
    CHECK(s0->GetRepeatCount() == -1);
    CHECK(s0->GetSegmentsInSequence() == 3);

    ITimeline *s1 = segmentTemplate->GetSegmentTimeline()->GetTimelines().at(1);
    CHECK(s1->GetRepeatCount() == 2);
    CHECK(s1->GetSegmentsInSequence() == 1);

    ISegmentList *segmentList = period->GetAdaptationSets().at(1)->GetSegmentList();
    CHECK(segmentList->GetFailoverContent() != NULL);
    CHECK(segmentList->GetAdditionalSubNodes().empty());

    delete mpd;
    return 0;
}
static int TestSequences (IDASHManager *manager, char *path)
{
    IMPD *mpd = manager->Open(path);
    CHECK(mpd != NULL);
    if (!mpd)
        return 1;

    IPeriod *period = mpd->GetPeriods().at(0);
    CHECK(period->GetAdaptationSets().size() == 3);

    // --- AdaptationSet 1: Segment Sequence Representation with S@ssp
    IAdaptationSet *video = period->GetAdaptationSets().at(0);

    CHECK(video->GetSegmentSequenceProperties().size() == 2);
    ISegmentSequenceProperties *ssp0 = video->GetSegmentSequenceProperties().at(0);
    CHECK(ssp0->GetSapType() == 2);
    CHECK(ssp0->GetCadence() == 4);
    CHECK(ssp0->HasEvent());
    CHECK(ssp0->GetAlignment().size() == 2);
    CHECK(ssp0->GetAlignment().size() == 2 && ssp0->GetAlignment().at(0) == "v2" && ssp0->GetAlignment().at(1) == "v3");
    ISegmentSequenceProperties *ssp1 = video->GetSegmentSequenceProperties().at(1);
    CHECK(ssp1->GetSapType() == 0);
    CHECK(ssp1->GetCadence() == 1);
    CHECK(!ssp1->HasEvent());
    CHECK(ssp1->GetAlignment().empty());

    IRepresentation *representation = video->GetRepresentation().at(0);
    CHECK(representation->GetSegmentSequenceProperties().size() == 1);
    CHECK(representation->GetSegmentSequenceProperties().at(0)->GetSapType() == 1);
    CHECK(representation->GetSegmentSequenceProperties().at(0)->GetCadence() == 16);

    const ISegmentTimeline *timeline = video->GetSegmentTemplate()->GetSegmentTimeline();
    CHECK(timeline->GetPatterns().size() == 2);
    CHECK(timeline->GetTimelines().size() == 2);
    CHECK(timeline->GetAdditionalSubNodes().empty());

    IPattern *pattern1 = timeline->GetPatterns().at(0);
    CHECK(pattern1->GetId() == 1);
    CHECK(pattern1->GetRunLengths().size() == 2);
    IRunLength *p0 = pattern1->GetRunLengths().at(0);
    CHECK(p0->GetDuration() == 172800);
    CHECK(p0->GetRepeatCount() == 0);
    CHECK(p0->GetSegmentsInSequence() == 16);
    CHECK(!p0->HasSsp());
    IRunLength *p1 = pattern1->GetRunLengths().at(1);
    CHECK(p1->GetDuration() == 180000);
    CHECK(p1->GetRepeatCount() == 2);
    CHECK(p1->GetSegmentsInSequence() == 8);

    IPattern *pattern3 = timeline->GetPatterns().at(1);
    CHECK(pattern3->GetId() == 3);
    CHECK(pattern3->GetRunLengths().size() == 1);
    CHECK(pattern3->GetRunLengths().at(0)->HasSsp() && pattern3->GetRunLengths().at(0)->GetSsp() == 1);
    CHECK(pattern3->GetRunLengths().at(0)->GetSegmentsInSequence() == 1);
    CHECK(pattern3->GetRunLengths().at(0)->GetRepeatCount() == 1);

    ITimeline *s0 = timeline->GetTimelines().at(0);
    CHECK(s0->GetStartTime() == 546975158ULL);
    CHECK(s0->GetRepeatCount() == 14);
    CHECK(s0->HasSsp() && s0->GetSsp() == 1);
    CHECK(!s0->HasPattern());
    CHECK(timeline->GetTimelines().at(1)->HasSsp());

    // --- AdaptationSet 2: duration pattern with S@p / S@pE
    ISegmentTemplate *audioTemplate = period->GetAdaptationSets().at(1)->GetSegmentTemplate();
    CHECK(audioTemplate->GetTolerance() == 12.5f);
    CHECK(!audioTemplate->HasEndSubNumber());
    CHECK(!audioTemplate->HasSegmentsInSequence());
    CHECK(audioTemplate->GetSegmentsInSequence() == 1);

    const ISegmentTimeline *audioTimeline = audioTemplate->GetSegmentTimeline();
    CHECK(audioTimeline->GetPatterns().size() == 1);
    CHECK(audioTimeline->GetPatterns().at(0)->GetId() == 2);
    ITimeline *sa = audioTimeline->GetTimelines().at(0);
    CHECK(sa->HasPattern() && sa->GetPatternId() == 2);
    CHECK(sa->GetPatternEntry() == 1);
    CHECK(sa->GetRepeatCount() == 164);
    CHECK(!sa->HasSsp());
    CHECK(sa->GetSegmentsInSequence() == 1);

    // --- AdaptationSet 3: SegmentTemplate@duration with @k and @endSubNumber
    ISegmentTemplate *textTemplate = period->GetAdaptationSets().at(2)->GetSegmentTemplate();
    CHECK(textTemplate->GetDuration() == 16000);
    CHECK(textTemplate->HasSegmentsInSequence() && textTemplate->GetSegmentsInSequence() == 16);
    CHECK(textTemplate->HasEndSubNumber() && textTemplate->GetEndSubNumber() == 7);
    CHECK(textTemplate->GetTolerance() == 50.0f);
    CHECK(textTemplate->GetSegmentTimeline() == NULL);

    delete mpd;
    return 0;
}
static int TestUrlParams (IDASHManager *manager, char *path)
{
    IMPD *mpd = manager->Open(path);
    CHECK(mpd != NULL);
    if (!mpd)
        return 1;

    // MPD level: defaults and whitespace-separated lists
    CHECK(mpd->GetRequestParams().size() == 2);
    IExtendedUrlInfo *mpdParam0 = mpd->GetRequestParams().at(0);
    CHECK(mpdParam0->GetQueryTemplate() == "$querypart$");
    CHECK(mpdParam0->UseMPDUrlQuery());
    CHECK(mpdParam0->GetQueryString().empty());
    CHECK(mpdParam0->GetIncludeInRequests().size() == 1 && mpdParam0->GetIncludeInRequests().at(0) == "segment");
    CHECK(mpdParam0->GetHeaderParamSource().size() == 1 && mpdParam0->GetHeaderParamSource().at(0) == "segment");
    CHECK(!mpdParam0->IsSameOriginOnly());
    CHECK(mpdParam0->GetHeader().empty());
    CHECK(mpdParam0->GetXlinkActuate() == "onRequest");
    IExtendedUrlInfo *mpdParam1 = mpd->GetRequestParams().at(1);
    CHECK(!mpdParam1->UseMPDUrlQuery());
    CHECK(mpdParam1->GetQueryString() == "token=abc&sid=42");
    CHECK(mpdParam1->GetIncludeInRequests().size() == 2);
    CHECK(mpdParam1->GetIncludeInRequests().size() == 2 && mpdParam1->GetIncludeInRequests().at(1) == "mpd");
    CHECK(mpdParam1->IsSameOriginOnly());
    CHECK(mpd->GetEssentialProperties().size() == 1);
    CHECK(mpd->GetEssentialProperties().size() == 1 && mpd->GetEssentialProperties().at(0)->GetSchemeIdUri() == "urn:mpeg:dash:urlparam:2025");

    // Period level: header parameters
    IPeriod *period = mpd->GetPeriods().at(0);
    CHECK(period->GetRequestParams().size() == 1);
    IExtendedUrlInfo *periodParam = period->GetRequestParams().at(0);
    CHECK(periodParam->GetHeaderParamSource().size() == 1 && periodParam->GetHeaderParamSource().at(0) == "mpd");
    CHECK(periodParam->GetQueryTemplate() == "$header:X-Session$");
    CHECK(periodParam->GetHeader() == "X-Session-Echo");

    // EventStream: BaseURL, RequestParam, EssentialProperty, SupplementalProperty
    IEventStream *eventStream = period->GetEventStreams().at(0);
    CHECK(eventStream->GetEvents().size() == 1);
    CHECK(eventStream->GetBaseURLs().size() == 1);
    CHECK(eventStream->GetBaseURLs().size() == 1 && eventStream->GetBaseURLs().at(0)->GetUrl() == "https://ads.example.com/");
    CHECK(eventStream->GetRequestParams().size() == 1);
    CHECK(eventStream->GetRequestParams().size() == 1 && eventStream->GetRequestParams().at(0)->GetIncludeInRequests().at(0) == "altmpd");
    CHECK(eventStream->GetEssentialProperties().size() == 1);
    CHECK(eventStream->GetSupplementalProperties().size() == 2);
    CHECK(eventStream->GetSupplementalProperties().size() == 2 && eventStream->GetSupplementalProperties().at(1)->GetValue() == "b");
    CHECK(eventStream->GetAdditionalSubNodes().empty());

    // AdaptationSet and Representation levels
    IAdaptationSet *adaptationSet = period->GetAdaptationSets().at(0);
    CHECK(adaptationSet->GetRequestParams().size() == 1);
    CHECK(adaptationSet->GetRequestParams().size() == 1 && adaptationSet->GetRequestParams().at(0)->GetXlinkHref() == "https://example.com/param.xml");
    CHECK(adaptationSet->GetRequestParams().size() == 1 && adaptationSet->GetRequestParams().at(0)->GetXlinkActuate() == "onLoad");
    IRepresentation *representation = adaptationSet->GetRepresentation().at(0);
    CHECK(representation->GetRequestParams().size() == 1);
    CHECK(representation->GetRequestParams().size() == 1 && representation->GetRequestParams().at(0)->GetQueryString() == "rep=v1");

    delete mpd;
    return 0;
}
static int TestSteering (IDASHManager *manager, char *path)
{
    IMPD *mpd = manager->Open(path);
    CHECK(mpd != NULL);
    if (!mpd)
        return 1;

    // MPD.ContentSteering
    const IContentSteering *steering = mpd->GetContentSteering();
    CHECK(steering != NULL);
    if (steering)
    {
        CHECK(steering->GetUrl() == "https://steering.example.com/app/instance1234");
        CHECK(steering->GetDefaultServiceLocation() == "beta");
        CHECK(steering->GetDefaultServiceLocations().size() == 1 && steering->GetDefaultServiceLocations().at(0) == "beta");
        CHECK(steering->IsQueryBeforeStart());
        CHECK(steering->HasClientRequirement());
    }

    // ServiceDescription.ContentSteering
    CHECK(mpd->GetServiceDescriptions().size() == 1);
    const std::vector<IContentSteering *> &sdSteering = mpd->GetServiceDescriptions().at(0)->GetContentSteerings();
    CHECK(sdSteering.size() == 2);
    if (sdSteering.size() == 2)
    {
        CHECK(sdSteering.at(0)->GetUrl() == "https://steering.example.com/sd");
        CHECK(!sdSteering.at(0)->HasClientRequirement());
        CHECK(!sdSteering.at(0)->IsQueryBeforeStart());
        CHECK(sdSteering.at(0)->GetDefaultServiceLocation().empty());
        CHECK(sdSteering.at(0)->GetDefaultServiceLocations().empty());
        CHECK(sdSteering.at(1)->GetDefaultServiceLocation() == "alpha");
    }
    CHECK(mpd->GetServiceDescriptions().at(0)->GetAdditionalSubNodes().empty());

    // Location@serviceLocation, with GetLocations() unchanged
    CHECK(mpd->GetLocations().size() == 2);
    CHECK(mpd->GetLocations().size() == 2 && mpd->GetLocations().at(1) == "https://origin.example.com/live.mpd");
    CHECK(mpd->GetLocationElements().size() == 2);
    CHECK(mpd->GetLocationElements().size() == 2 && mpd->GetLocationElements().at(0)->GetUrl() == "https://cdn-a.example.com/live.mpd");
    CHECK(mpd->GetLocationElements().size() == 2 && mpd->GetLocationElements().at(0)->GetServiceLocation() == "alpha");
    CHECK(mpd->GetLocationElements().size() == 2 && mpd->GetLocationElements().at(1)->GetServiceLocation().empty());

    // PatchLocation@serviceLocation and BaseURL@serviceLocation
    CHECK(mpd->GetPatchLocations().size() == 1);
    CHECK(mpd->GetPatchLocations().size() == 1 && mpd->GetPatchLocations().at(0)->GetServiceLocation() == "beta");
    CHECK(mpd->GetPatchLocations().size() == 1 && mpd->GetPatchLocations().at(0)->GetTtl() == 60.0);
    CHECK(mpd->GetBaseUrls().size() == 2 && mpd->GetBaseUrls().at(1)->GetServiceLocation() == "beta");

    delete mpd;
    return 0;
}
static int TestCMCD (IDASHManager *manager, char *path)
{
    IMPD *mpd = manager->Open(path);
    CHECK(mpd != NULL);
    if (!mpd)
        return 1;

    CHECK(mpd->GetServiceDescriptions().size() == 2);

    // Service Description 1: all attributes present
    const std::vector<IClientDataReporting *> &reportings = mpd->GetServiceDescriptions().at(0)->GetClientDataReportings();
    CHECK(reportings.size() == 1);
    if (reportings.size() == 1)
    {
        IClientDataReporting *reporting = reportings.at(0);
        CHECK(reporting->GetSchemeIdUri() == "urn:mpeg:dash:cta-5004:2023");
        CHECK(reporting->GetValue() == "1");
        CHECK(reporting->GetServiceLocations().size() == 2 && reporting->GetServiceLocations().at(1) == "beta");
        CHECK(reporting->GetAdaptationSets().size() == 2 && reporting->GetAdaptationSets().at(0) == 1 && reporting->GetAdaptationSets().at(1) == 3);
        CHECK(reporting->GetAdditionalSubNodes().empty());
        CHECK(reporting->GetCMCDParameters().size() == 1);
        if (reporting->GetCMCDParameters().size() == 1)
        {
            ICMCDParameters *cmcd = reporting->GetCMCDParameters().at(0);
            CHECK(cmcd->GetVersion() == 2);
            CHECK(cmcd->GetMode() == "header");
            CHECK(cmcd->GetIncludeInRequests().size() == 2 && cmcd->GetIncludeInRequests().at(1) == "mpd");
            CHECK(cmcd->GetKeys().size() == 9 && cmcd->GetKeys().at(0) == "br" && cmcd->GetKeys().at(8) == "v");
            CHECK(cmcd->GetContentID() == "movie-42");
            CHECK(cmcd->GetSessionID() == "6e2fb550-c457-11e9-bb97-0800200c9a66");
        }
    }
    CHECK(mpd->GetServiceDescriptions().at(0)->GetAdditionalSubNodes().empty());

    // Service Description 2: defaults
    const std::vector<IClientDataReporting *> &reportings2 = mpd->GetServiceDescriptions().at(1)->GetClientDataReportings();
    CHECK(reportings2.size() == 1);
    if (reportings2.size() == 1 && reportings2.at(0)->GetCMCDParameters().size() == 1)
    {
        CHECK(reportings2.at(0)->GetServiceLocations().empty());
        CHECK(reportings2.at(0)->GetAdaptationSets().empty());
        ICMCDParameters *cmcd = reportings2.at(0)->GetCMCDParameters().at(0);
        CHECK(cmcd->GetVersion() == 1);
        CHECK(cmcd->GetMode() == "query");
        CHECK(cmcd->GetIncludeInRequests().size() == 1 && cmcd->GetIncludeInRequests().at(0) == "segment");
        CHECK(cmcd->GetKeys().size() == 1);
        CHECK(cmcd->GetContentID().empty());
        CHECK(cmcd->GetSessionID().empty());
    }

    delete mpd;
    return 0;
}
static void TestSmoke (IDASHManager *manager, int count, char **paths)
{
    for (int i = 0; i < count; i++)
    {
        IMPD *mpd = manager->Open(paths[i]);
        printf("%s  %s\n", mpd ? "PASS" : "FAIL", paths[i]);
        if (!mpd)
            failures++;
        delete mpd;
    }
}

int main (int argc, char **argv)
{
    if (argc < 3 || (strcmp(argv[1], "fields") && strcmp(argv[1], "sequences") && strcmp(argv[1], "urlparams") && strcmp(argv[1], "steering") && strcmp(argv[1], "cmcd") && strcmp(argv[1], "smoke")))
    {
        fprintf(stderr, "usage: %s fields <pre6ed_fields.mpd> | sequences <segment_sequences.mpd> | urlparams <url_parameters.mpd> | steering <content_steering.mpd> | cmcd <cmcd.mpd> | smoke <file.mpd>...\n", argv[0]);
        return 2;
    }

    IDASHManager *manager = CreateDashManager();

    if (!strcmp(argv[1], "fields"))
        TestFields(manager, argv[2]);
    else if (!strcmp(argv[1], "sequences"))
        TestSequences(manager, argv[2]);
    else if (!strcmp(argv[1], "urlparams"))
        TestUrlParams(manager, argv[2]);
    else if (!strcmp(argv[1], "steering"))
        TestSteering(manager, argv[2]);
    else if (!strcmp(argv[1], "cmcd"))
        TestCMCD(manager, argv[2]);
    else
        TestSmoke(manager, argc - 2, argv + 2);

    manager->Delete();

    printf("%d failure(s)\n", failures);
    return failures ? 1 : 0;
}
