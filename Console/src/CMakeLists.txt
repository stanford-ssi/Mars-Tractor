# Set flags for qt5 forms
set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

# Set flag standards for qt5
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms )

# Find packages
find_package( Qt5 COMPONENTS Widgets Svg REQUIRED )
find_package( SFML COMPONENTS system  CONFIG REQUIRED)

# Specify Include Directories
include_directories( ${Qt5Widgets_INCLUDES} )

# Define source files to compile
file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/* ${KBTHREAD_LIB_DIR}/* ${KBNET_LIB_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/forms/* )

# Add executable
add_executable( console ${SRCFILES} )

# Link libraries
# target_link_libraries( console PRIVATE Qt5::Widgets Qt5::Svg ${OpenCV_LIBS} jsoncpp_lib )
target_include_directories( console PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${ASIO_INCLUDE_DIR} ${GSTREAMER_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})
target_link_directories (console PRIVATE ${GSTREAMER_LIB_DIR} )
target_link_libraries( console PRIVATE Qt5::Widgets Qt5::Svg sfml-window)# bz2 cairo-gobject cairo-script-interpreter cairo charset croco-0.6 crypto dv expat ffi FLAC fontconfig freetype fribidi gdk_pixbuf-2.0 ges-1.0 gio-2.0 glib-2.0 gmodule-2.0 gobject-2.0 graphene-1.0 gstadaptivedemux-1.0 gstallocators-1.0 gstapp-1.0 gstaudio-1.0 gstbadaudio-1.0 gstbase-1.0 gstbasecamerabinsrc-1.0 gstcheck-1.0 gstcodecparsers-1.0 gstcodecs-1.0 gstcontroller-1.0 gstfft-1.0 gstgl-1.0 gstinsertbin-1.0 gstisoff-1.0 gstmpegts-1.0 gstnet-1.0 gstpbutils-1.0 gstphotography-1.0 gstplayer-1.0 gstreamer-1.0 gstriff-1.0 gstrtp-1.0 gstrtsp-1.0 gstrtspserver-1.0 gstsctp-1.0 gstsdp-1.0 gsttag-1.0 gsttranscoder-1.0 gsturidownloader-1.0 gstvalidate-1.0 gstvideo-1.0 gstwebrtc-1.0 gthread-2.0 harfbuzz iconv intl jpeg json-glib-1.0 kate mp3lame mpg123 nice ogg oggkate openh264 openjp2 opus orc-0.4 orc-test-0.4 pango-1.0 pangocairo-1.0 pangoft2-1.0 pangowin32-1.0 pixman-1 png16 psl rsvg-2 sbc soup-2.4 spandsp speex sqlite3 srt srtp2 ssl theora theoradec theoraenc tiff turbojpeg usrsctp visual-0.4 vorbis vorbisenc vorbisfile wavpack xml2 z zbar */)

# Copy executable and assets to main build folder
COPY_FILE_INTO_DIRECTORY_IF_CHANGED( ${CMAKE_BINARY_DIR}/src/console/console ${CMAKE_BINARY_DIR} console )
COPY_DIRECTORY_IF_CHANGED( ${CMAKE_SOURCE_DIR}/assets ${CMAKE_SOURCE_DIR}/build/assets console )