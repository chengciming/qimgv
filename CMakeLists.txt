# qimgv root
cmake_minimum_required(VERSION 3.13)
project(qimgv
    VERSION 0.9.2
    HOMEPAGE_URL "https://github.com/easymodo/qimgv"
    LANGUAGES CXX)

message(STATUS "Build configuration: " ${CMAKE_BUILD_TYPE})

if(IS_ABSOLUTE ${CMAKE_INSTALL_LIBDIR})
    set(QIMGV_PLUGIN_DIR "${CMAKE_INSTALL_LIBDIR}/qimgv")
else()
    set(QIMGV_PLUGIN_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/qimgv")
endif()

ADD_DEFINITIONS(-D_QIMGV_PLUGIN_DIR="${QIMGV_PLUGIN_DIR}")

message(STATUS "Plugin dir: " ${QIMGV_PLUGIN_DIR})

# check for gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND
        CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    message(FATAL_ERROR "\n!!! THIS PROJECT REQUIRES GCC 9.0 OR LATER !!!\n")
endif()

# AUTOMOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# USER OPTIONS
# Usage: cmake -DVIDEO_SUPPORT=ON [...]
option(EXIV2 "For reading/writing exif tags" ON)
option(VIDEO_SUPPORT "Enable video support" ON)
option(OPENCV_SUPPORT "Enable HQ scaling via OpenCV" ON)
option(KDE_SUPPORT "Support blur when using KDE" OFF)

# FIND PACKAGES
# test for qt5, use that if possible
find_package(Qt5 COMPONENTS Widgets QUIET)
if(Qt5_FOUND)
    find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Widgets Svg PrintSupport)
else()
    find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Widgets Svg Core5Compat PrintSupport OpenGLWidgets)
endif()

message(STATUS "Qt Version: " ${QT_VERSION})
if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Svg PrintSupport Core5Compat OpenGLWidgets)
else()
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Svg PrintSupport)
endif()

if(EXIV2)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(Exiv2 REQUIRED IMPORTED_TARGET exiv2)
endif()

if(KDE_SUPPORT)
    find_package(KF5WindowSystem REQUIRED)
endif()

if(OPENCV_SUPPORT)
    find_package(PkgConfig REQUIRED)
    find_package(OpenCV REQUIRED core imgproc)
endif()

##############################################################

add_subdirectory(qimgv)

if(VIDEO_SUPPORT)
    add_subdirectory(plugins/player_mpv)
endif()
