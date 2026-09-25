/*
 * libdash_mpd_test.cpp
 *****************************************************************************
 * MPD parser tests.
 *
 *   libdash_mpd_test fields    <pre6ed_fields.mpd>        checks parsed values
 *   libdash_mpd_test sequences <segment_sequences.mpd>    checks segment sequences and duration patterns
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
    if (argc < 3 || (strcmp(argv[1], "fields") && strcmp(argv[1], "sequences") && strcmp(argv[1], "smoke")))
    {
        fprintf(stderr, "usage: %s fields <pre6ed_fields.mpd> | sequences <segment_sequences.mpd> | smoke <file.mpd>...\n", argv[0]);
        return 2;
    }

    IDASHManager *manager = CreateDashManager();

    if (!strcmp(argv[1], "fields"))
        TestFields(manager, argv[2]);
    else if (!strcmp(argv[1], "sequences"))
        TestSequences(manager, argv[2]);
    else
        TestSmoke(manager, argc - 2, argv + 2);

    manager->Delete();

    printf("%d failure(s)\n", failures);
    return failures ? 1 : 0;
}
