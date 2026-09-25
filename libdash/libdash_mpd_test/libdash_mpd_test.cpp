/*
 * libdash_mpd_test.cpp
 *****************************************************************************
 * MPD parser tests.
 *
 *   libdash_mpd_test fields <pre6ed_fields.mpd>   checks parsed values
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
    if (argc < 3 || (strcmp(argv[1], "fields") && strcmp(argv[1], "smoke")))
    {
        fprintf(stderr, "usage: %s fields <pre6ed_fields.mpd> | smoke <file.mpd>...\n", argv[0]);
        return 2;
    }

    IDASHManager *manager = CreateDashManager();

    if (!strcmp(argv[1], "fields"))
        TestFields(manager, argv[2]);
    else
        TestSmoke(manager, argc - 2, argv + 2);

    manager->Delete();

    printf("%d failure(s)\n", failures);
    return failures ? 1 : 0;
}
