cmake_minimum_required (VERSION 2.8)
project (HMD_Bridge)

# Allow the developer to select if Dynamic or Static libraries are built
option (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
# Set the LIB_TYPE variable to STATIC
set (LIB_TYPE STATIC)
if (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  set (LIB_TYPE SHARED)
endif (BUILD_SHARED_LIBS)


# The version number.
set (HMD_Bridge_VERSION_MAJOR 0)
set (HMD_Bridge_VERSION_MINOR 1)

# source files
set (PROJECT_SOURCE_DIR source)

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/HMD_Bridge_Config.h.in"
#  "${PROJECT_BINARY_DIR}/HMD_Bridge_Config.h"
#  )

# add the binary tree to the search path for include files
# so that we will find HMD_Bridge_Config.h
include_directories ("${PROJECT_BINARY_DIR}")

set (BRIDGE_SOURCES
    ${PROJECT_SOURCE_DIR}/Backend.h
    ${PROJECT_SOURCE_DIR}/Debug.h
    ${PROJECT_SOURCE_DIR}/HMD_Bridge_API.cpp
    ${PROJECT_SOURCE_DIR}/HMD_Bridge_API.h
    ${PROJECT_SOURCE_DIR}/Stub.h
    )

set (EXTERN extern)
set (GLEW_SOURCES ${EXTERN}/glew/src/glew.c)
set (GLEW_INCLUDES ${EXTERN}/glew/include)

include_directories (${GLEW_INCLUDES})

set (OCULUS_SDK_DIR "" CACHE PATH "Oculus SDK 0.7 LibOVR Folder")
include_directories (${OCULUS_SDK_DIR}/Include)

if (WIN32)
    string(TOLOWER "${CMAKE_BUILD_TYPE}" _type)
    if (_type STREQUAL debug)
        set (OCULUS_SDK_LIBRARY_PATH ${OCULUS_SDK_DIR}/Lib/Windows/Win32/Debug/VS2013)
    else()
        set (OCULUS_SDK_LIBRARY_PATH ${OCULUS_SDK_DIR}/Lib/Windows/Win32/Release/VS2013)
    endif()
endif ()
set(OCULUS_SDK_LIBRARY ${OCULUS_SDK_LIBRARY_PATH}/LibOVR)

option (OCULUS_BACKEND "Oculus Backend" ON)
# Set the OCULUS_BACKEND
if (${OCULUS_BACKEND})
    add_definitions (-DOCULUS)
    set (BRIDGE_SOURCE
        ${BRIDGE_SOURCE}
        ${PROJECT_SOURCE_DIR}/Oculus.cpp
        ${PROJECT_SOURCE_DIR}/Oculus.h
    )
endif (${OCULUS_BACKEND})

add_library (BridgeLib ${LIB_TYPE} ${BRIDGE_SOURCES} ${GLEW_SOURCES})

if (WIN32)
    target_link_libraries (BridgeLib opengl32)
endif(WIN32)

if (${OCULUS_BACKEND})
    target_link_libraries (BridgeLib ${OCULUS_SDK_LIBRARY})
endif (${OCULUS_BACKEND})
