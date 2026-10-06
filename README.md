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

### Requirements
CMake 3.13 or newer (3.21 or newer for the presets in `CMakePresets.json`), a C++11 compiler, libxml2, libcurl and zlib.

### Linux and macOS
1. Install the dependencies
   * Ubuntu/Debian: `sudo apt-get install build-essential cmake libxml2-dev libcurl4-openssl-dev zlib1g-dev`
   * macOS: libxml2, libcurl and zlib come with the SDK (Xcode or Command Line Tools); install CMake with `brew install cmake`
2. git clone https://github.com/bitmovin/libdash.git
3. cmake -S libdash/libdash -B build
4. cmake --build build --parallel
5. The library and test programs are in `build/bin`. Run the MPD parser tests with `cd build && ctest` (with CMake 3.20 or newer also `ctest --test-dir build`)

Alternatively, with CMake 3.21 or newer: `cmake --preset default`, `cmake --build --preset default` and `ctest --preset default` in `libdash/libdash`.

To also check that the parser handles the official example MPDs, clone [MPEGGroup/DASHSchema](https://github.com/MPEGGroup/DASHSchema) and add `-DLIBDASH_SCHEMA_EXAMPLES_DIR=<path to DASHSchema>` in step 3.

### Windows
The prebuilt libxml2, libcurl, zlib and iconv libraries shipped in `libdash/libdash` are **32-bit only**. For a 64-bit build, the dependencies come from [vcpkg](https://vcpkg.io), using the manifest `libdash/libdash/vcpkg.json`. `CMakePresets.json` provides both variants; they use the newest installed Visual Studio (2022 or newer):

| Preset | Architecture | Dependencies |
|---|---|---|
| `windows-x64` | 64-bit | vcpkg (set the environment variable `VCPKG_ROOT` to the vcpkg installation) |
| `windows-x86` | 32-bit | bundled libraries; their DLLs are copied next to the binaries |

* **Visual Studio**: open the folder `libdash/libdash` (File > Open > Folder) and select the preset in the toolbar.
* **Visual Studio Code** with the CMake Tools extension: open the folder `libdash/libdash` and select the configure preset (CMake: Select Configure Preset).
* **Command line** (Developer PowerShell): in `libdash/libdash`, run `cmake --preset windows-x64`, `cmake --build --preset windows-x64` and `ctest --preset windows-x64`.

Without presets, pass the architecture and, for 64-bit, the vcpkg toolchain explicitly, e.g. `cmake -S libdash/libdash -B build -A x64 -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake`. Visual Studio is a multi-configuration generator, so give the configuration when building and testing: `cmake --build build --config Release` and `cd build && ctest -C Release`.

The Visual Studio 2010 solution `libdash/libdash.sln` is outdated: it does not contain the source files added since 2021 and does not build the current library.

### Tests
`libdash_mpd_test` checks the parsed values of the test MPDs in `libdash/libdash_mpd_test/data`, one test per feature area (`ctest -N` in the build directory lists them). All test MPDs validate against the 6th-edition XML schema. GitHub Actions builds and tests libdash on Ubuntu (GCC and Clang, including a build with AddressSanitizer and UndefinedBehaviorSanitizer, and a build with the minimum CMake version 3.13), macOS and Windows (MSVC, 64-bit with vcpkg and 32-bit with the bundled libraries), and parses all example MPDs of the MPEGGroup/DASHSchema `6th-Ed` branch.

The deep smoke test (`libdash_mpd_test smoke <file.mpd>...`) opens each MPD, walks the complete object tree and calls every getter, which catches crashes, invalid pointers and uninitialised values, especially in a sanitizer build. It runs on all test MPDs and on the DASHSchema examples. To run it on further MPDs, e.g. the streams of the dash.js reference player, put them into a directory and add `-DLIBDASH_EXTRA_MPD_DIR=<directory>` when configuring.

`libdash_networkpart_test` downloads files from a test server that is no longer available, so it is not built by default; build it with `-DLIBDASH_BUILD_NETWORK_TEST=ON`.

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
