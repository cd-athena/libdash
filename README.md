# libdash


libdash is the **official reference software of the ISO/IEC MPEG-DASH standard** and is an open-source library that provides an object orient (OO) interface to the MPEG-DASH standard, developed by [Bitmovin](http://www.bitmovin.com).

## Supported MPEG-DASH edition

libdash parses Media Presentation Descriptions (MPDs) according to **ISO/IEC 23009-1, 6th edition**. Every element and attribute of the 6th-edition MPD schema (`DASH-MPD.xsd`) is available through the `dash::mpd` interfaces. Features added in the 4th to 6th editions include:

| Feature | Where to find it |
|---|---|
| Segment Sequences and duration patterns | `IRepresentationBase::GetSegmentSequenceProperties()`, `ISegmentTimeline::GetPatterns()`, `ITimeline` (`@n`, `@k`, `@p`, `@pE`, `@ssp`), `IMultipleSegmentBase` (`@k`, `@endSubNumber`, `@tolerance`) |
| URL query and header parameters (Annex I.3) | `GetRequestParams()` on `IMPD`, `IPeriod`, `IAdaptationSet`, `IRepresentation`, `IEventStream` |
| Content steering and service locations | `IMPD::GetContentSteering()`, `IServiceDescription::GetContentSteerings()`, `IMPD::GetLocationElements()`, `IPatchLocation::GetServiceLocation()` |
| Client data reporting and CMCD | `IServiceDescription::GetClientDataReportings()`, `IClientDataReporting::GetCMCDParameters()` |
| Alternative MPD events and service description events | `IEvent::GetInsertPresentation()`, `GetReplacePresentation()`, `GetServiceDescriptions()`, `GetSelectionInfo()`, `GetContent()` |
| Playback restrictions | `IServiceDescription::GetPlaybackRestrictions()` |
| Linked Periods and List MPDs | `IPeriod::GetImportedMPD()`, `IPeriod::GetMinBufferTime()` |
| Empty Adaptation Sets, failover content | `IPeriod::GetEmptyAdaptationSets()`, `ISegmentBase::GetFailoverContent()` |

libdash is an MPD parser and download library: behaviour that the specification defines for DASH clients (for example resolving Linked Periods, executing Alternative MPD events or sending CMCD data) is left to the application. MPD Patch documents are not parsed. Attributes and elements that libdash does not know are still available through `IMPDElement::GetRawAttributes()` and `GetAdditionalSubNodes()`.

## by bitmovin
<a href="https://www.bitmovin.com"><img src="https://ox4zindgwb3p1qdp2lznn7zb-wpengine.netdna-ssl.com/wp-content/uploads/2016/01/bitmovin-standard-2017.png" width="400px"/></a>

Video encoding 100x faster than any other encoding service
Your videos play everywhere with low startup delay, no buffering and in the highest quality

## Netflix Grade Quality
Encode your content with the same technology as Netflix and YouTube in a way that it plays everywhere with low startup delay and no buffering. <a href="https://bitmovin.com/cloud-encoding-service/">Bitmovins Cloud Encoding Service</a> encodes your content 100x faster than any other competitor while providing such a high quality output.

## API & Documentation
<a href="https://bitmovin.com/cloud-encoding-service/">The Bitmovin Cloud Encoding Service</a> is a powerful cloud encoding tool for developers built by developers. <a href="https://bitmovin.com/bitmovins-video-api/">The Bitmovin API</a> is available in our developer section including comprehensive documentation and API client for different programming languages such as Java, JavaScript, Ruby, Python, PHP, NodeJS, etc.

## HTML5 Adaptive Streaming Player
<a href="https://bitmovin.com/html5-player/">The Bitmovin Adaptive HTML5 Video Player</a> enables HTML5 adaptive streaming with MPEG-DASH native in your browser with no need for plugins like Flash or Silverlight. Due to the native integration with the browser it is possible to play back very high resolutions such as 4K or very high frame rates like 60fps.

## Professional Services
In addition to the public available open source resources and the mailing list support, we provide professional development and integration services, consulting, high-quality streaming componentes/logics, relicensing of libdash etc. based on your individual needs. Feel free to contact us via <a href="mailto:sales@bitmovin.com">sales@bitmovin.com</a> so we can discuss your requirements and provide you an offer.

## Architecture
The general architecture of <a href="https://bitmovin.com/dynamic-adaptive-streaming-http-mpeg-dash/">MPEG-DASH</a> is depicted in the figure below where the orange parts are standardized, i.e., the MPD and segment formats. The delivery of the MPD, the control heuristics and the media player itself, are depicted in blue in the figure. These parts are not standardized and allow the differentiation of industry solutions due to the performance or different features that can be integrated at that level. libdash is also depicted in blue and encapsulates the MPD parsing and HTTP part, which will be handled by the library. Therefore the library provides interfaces for the DASH Streaming Control and the Media Player to access MPDs and downloadable media segments. The download order of such media segments will not be handled by the library this is left to the DASH Streaming Control, which is an own component in this architecture but it could also be included in the Media Player.
In a typical deployment, a DASH server provides segments in several bitrates and resolutions. The client initially receives the MPD through libdash which provides a convenient object oriented interface to that MPD. The MPD contains the temporal relationships for the various qualities and segments. Based on that information the client can download individual media segments through libdash at any point in time. Therefore varying bandwidth conditions can be handled by switching to the corresponding quality level at segment boundaries in order to provide a smooth streaming experience. This adaptation is not part of libdash and the MPEG-DASH standard and will be left to the application which is using libdash.

## Documentation

The doxygen documentation availalbe in the repo.

## Sources and Binaries

You can find the latest sources and binaries on github.

## How to use

### Windows
Use CMake to generate a Visual Studio solution, e.g. `cmake -S libdash/libdash -B build -G "Visual Studio 17 2022"`, then build it in Visual Studio or with `cmake --build build --config Release`. On Windows, CMake looks for libxml2, libcurl, zlib and iconv in the prebuilt packages shipped in `libdash/libdash`.

The Visual Studio 2010 solution `libdash/libdash.sln` is outdated: it does not contain the source files added since 2021 and does not build the current library. The Windows build has not been tested with the 6th-edition changes.

### Linux and macOS
Requires CMake 3.12 or newer, a C++11 compiler, libxml2, libcurl and zlib.

1. Install the dependencies
   * Ubuntu/Debian: `sudo apt-get install build-essential cmake libxml2-dev libcurl4-openssl-dev zlib1g-dev`
   * macOS: libxml2, libcurl and zlib come with the SDK (Xcode or Command Line Tools); install CMake with `brew install cmake`
2. git clone https://github.com/bitmovin/libdash.git
3. cmake -S libdash/libdash -B build
4. cmake --build build --parallel
5. The library and test programs are in `build/bin`. Run the MPD parser tests with `ctest --test-dir build`

To also check that the parser handles the official example MPDs, clone [MPEGGroup/DASHSchema](https://github.com/MPEGGroup/DASHSchema) and add `-DLIBDASH_SCHEMA_EXAMPLES_DIR=<path to DASHSchema>` in step 3.

### Tests
`libdash_mpd_test` checks the parsed values of the test MPDs in `libdash/libdash_mpd_test/data`, one test per feature area (`ctest --test-dir build -N` lists them). All test MPDs validate against the 6th-edition XML schema. GitHub Actions builds and tests libdash on Ubuntu (GCC and Clang, including a build with AddressSanitizer and UndefinedBehaviorSanitizer) and macOS, and parses all example MPDs of the MPEGGroup/DASHSchema `6th-Ed` branch.

`libdash_networkpart_test` downloads files from a test server that is no longer available; build it with `-DLIBDASH_BUILD_NETWORK_TEST=OFF` to skip it.

#### QTSamplePlayer
Prerequisite: libdash must be built as described in the previous section.
Tested using **cmake** version **2.8.12.2**.

1. sudo apt-add-repository ppa:ubuntu-sdk-team/ppa
2. sudo apt-add-repository ppa:canonical-qt5-edgers/qt5-proper
3. sudo apt-get update
4. sudo apt-get install qtmultimedia5-dev qtbase5-dev libqt5widgets5 libqt5core5a libqt5gui5 libqt5multimedia5 libqt5multimedia5-plugins libqt5multimediawidgets5 libqt5opengl5 libav-tools libavcodec-dev libavdevice-dev libavfilter-dev libavformat-dev libavutil-dev libpostproc-dev libswscale-dev
5. cd libdash/libdash/qtsampleplayer
6. mkdir build
7. cd build
8. cmake ../
9. make
10. ./qtsampleplayer

If some issues arise regarding the *make* installation, please make sure to be using the right kernel and *cmake version*. It is important to run *cmake* with the appropriate version in order to avoid linking problems that can fail the *make* process.

## License

libdash is open source available and licensed under LGPL:

“This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA“

As libdash is licensed under LGPL, changes to the library have to be published again to the open-source project. As many user and companies do not want to publish their specific changes, libdash can be also relicensed to a commercial license on request. Please contact <a href="mailto:sales@bitmovin.com">sales@bitmovin.com</a> to provide you an offer.

## Acknowledgements

We specially want to thank our passionate developers at [Bitmovin](http://www.bitmovin.com) as well as the researchers at the [Institute of Information Technology](http://www-itec.aau.at/dash/) (ITEC) from the Alpen Adria Universitaet Klagenfurt (AAU)!

Furthermore we want to thank the [Netidee](http://www.netidee.at) initiative from the [Internet Foundation Austria](http://www.nic.at/ipa) for partially funding the open source development of libdash.

![netidee logo](http://www.bitmovin.com/files/bitmovin/img/logos/netidee.png "netidee")

## Citation of libdash
We kindly ask you to refer the following paper in any publication mentioning libdash:

Christopher Mueller, Stefan Lederer, Joerg Poecher, and Christian Timmerer, “libdash – An Open Source Software Library for the MPEG-DASH Standard”, in Proceedings of the IEEE International Conference on Multimedia and Expo 2013, San Jose, USA, July, 2013
