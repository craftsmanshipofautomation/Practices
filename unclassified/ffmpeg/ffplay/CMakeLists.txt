cmake_minimum_required(VERSION 3.11)
project(leviathan)
include(ExternalProject)
# 3rd party
add_subdirectory(glog)


# https://github.com/pyke369/sffmpeg/blob/master/CMakeLists.txt

set(FFMPEG_MINIMAL_FEATURE_FLAGS
--disable-everything
--enable-decoder=mjpeg
#--enable-decoder=h264
#--enable-parser=h264
--enable-decoder=aac,ac3,flac
--enable-demuxer=mjpeg --enable-parser=mjpeg
--enable-demuxer=image2 --enable-muxer=mp4
#--enable-encoder=libx264 --enable-libx264
--enable-demuxer=mov
--enable-decoder=rawvideo
--enable-protocol=file
#--enable-hwaccels
)


set(FFMPEG_CONFIG_FLAGS
--prefix=${CMAKE_SOURCE_DIR}/fflib
${FFMPEG_MINIMAL_FEATURE_FLAGS}
--extra-cflags="-I/usr/local/include"
--extra-ldflags="-L/usr/lib"
--enable-cross-compile
#--arch=arm5te
#--enable-armv5te
--target-os=linux
--disable-stripping
--disable-neon
--enable-version3
#--disable-shared
--enable-shared
--enable-static
--enable-gpl
#--enable-memalign-hack
#--cc=arm-linux-androideabi-gcc
#--ld=arm-linux-androideabi-ld
#--extra-cflags="-fPIC -DANDROID -D__thumb__ -mthumb -Wfatal-errors -Wno-deprecated"
--disable-vaapi
--disable-vdpau
--disable-ffmpeg
--disable-ffplay
--disable-ffprobe
#--disable-ffserver
--disable-network
#--enable-filter=buffer
#--enable-filter=buffersink
#--disable-demuxer=v4l
#--disable-demuxer=v4l2
#--disable-indev=v4l
#--disable-indev=v4l2
)


#ExternalProject_Add(
#  ffmpeg
#  #DEPENDS yasm opencore-amr fdkaac lame libogg speex libvorbis libtheora opus xvidcore x264 x265 libvpx rtmpdump freetype libass openssl
#  #DEPENDS libx264
#  # URL http://www.ffmpeg.org/releases/ffmpeg-3.3.3.tar.bz2
#  #GIT_REPOSITORY ssh://root@silicon/root/git/FFmpeg
#  #GIT_REMOTE_NAME silicon
#  #GIT_TAG silicon/master
#  URL ${CMAKE_SOURCE_DIR}/ffmpeg
#  #PATCH_COMMAND ${CMAKE_SOURCE_DIR}/patches/patch-manager.sh ffmpeg
#  # todo remove datadir
#  CONFIGURE_COMMAND PATH=$ENV{PATH} PKG_CONFIG_PATH=$ENV{PKG_CONFIG_PATH} ./configure ${FFMPEG_CONFIG_FLAGS}
#  BUILD_COMMAND PATH=$ENV{PATH} make
#  BUILD_IN_SOURCE 1
#)



#include_directories(chromium)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.0.9/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
link_directories(/usr/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/fflib/lib)


set(ROOT_SOURCE_DIR ${PROJECT_SOURCE_DIR})

set (CMAKE_BUILD_TYPE Debug)


file(GLOB SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/thread/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg/fftools/cmdutils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fftools_variables.c
    #${CMAKE_CURRENT_SOURCE_DIR}/FFmpeg/fftools/ffmpeg.c
    #${CMAKE_CURRENT_SOURCE_DIR}/FFmpeg/fftools/ffmpeg.h
    ##${CMAKE_CURRENT_SOURCE_DIR}/FFmpeg/fftools/ffmpeg_opt.c
)

set(deplibs avdevice avformat
                avfilter
                swscale avcodec
                swresample
                avutil #bz2 x264
                pthread m z #lzma
                SDL2 glog)

add_library(ff ${SOURCE_FILES})
target_link_libraries(ff ${deplibs})

add_subdirectory(test)
