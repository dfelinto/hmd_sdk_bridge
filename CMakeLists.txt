cmake_minimum_required (VERSION 3.1)
project (BridgeLib)


# Allow the developer to select if Dynamic or Static libraries are built
option (BUILD_SHARED_LIBS "Build Shared Libraries" ON)

# Set the LIB_TYPE variable to STATIC
set (LIB_TYPE STATIC)
if (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  set (LIB_TYPE SHARED)
else()
    add_definitions(-DGLEW_STATIC)
endif (BUILD_SHARED_LIBS)


# The version number.
set (HMD_Bridge_VERSION_MAJOR 0)
set (HMD_Bridge_VERSION_MINOR 1)

# source files
set (PROJECT_SOURCE_DIR source)

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
    if (CMAKE_CL_64)
        set(PLATFORM "x64")
    else ()
        set(PLATFORM "Win32")
    endif()

    string(TOLOWER "${CMAKE_BUILD_TYPE}" _type)
    if (_type STREQUAL debug)
        set (BUILD_TYPE "Debug")
    else ()
        set (BUILD_TYPE "Release")
    endif()

    if (MSVC_VERSION EQUAL 1900)
        set (MSVC_PATH "VS2015")
    else()
        set (MSVC_PATH "VS2013")
    endif()

    # Oculus
    set (OCULUS_SDK_LIBRARY_PATH ${OCULUS_SDK_DIR}/Lib/Windows/${PLATFORM}/${BUILD_TYPE}/${MSVC_PATH})
endif ()
set(OCULUS_SDK_LIBRARY ${OCULUS_SDK_LIBRARY_PATH}/LibOVR.lib)

if (WIN32)
    option (OCULUS_BACKEND "Oculus Backend" ON)
else ()
    option (OCULUS_BACKEND "Oculus Backend" OFF)
endif(WIN32)

# Set the OCULUS_BACKEND
if (${OCULUS_BACKEND})
    add_definitions (-DOCULUS)
    set (BRIDGE_SOURCES
        ${BRIDGE_SOURCES}
        ${PROJECT_SOURCE_DIR}/Oculus.cpp
        ${PROJECT_SOURCE_DIR}/Oculus.h
    )
endif (${OCULUS_BACKEND})

add_library (${CMAKE_PROJECT_NAME} ${LIB_TYPE} ${BRIDGE_SOURCES} ${GLEW_SOURCES})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 11)

if (WIN32)
    target_link_libraries (${CMAKE_PROJECT_NAME} opengl32)
endif(WIN32)

if (${OCULUS_BACKEND})
    target_link_libraries (${CMAKE_PROJECT_NAME} ${OCULUS_SDK_LIBRARY})
endif (${OCULUS_BACKEND})


# Installing
if (CMAKE_CL_64)
    set (ARCH "x64")
else()
    set (ARCH "x86")
endif (CMAKE_CL_64)

# Hack, we can't set a default CMAKE_INSTALL_PREFIX so we simply
# override the original value (and hide the option under the advanced tab)

set (CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build)
mark_as_advanced(CMAKE_INSTALL_PREFIX)
message("-- Library destination: " ${CMAKE_INSTALL_PREFIX})

install (TARGETS ${CMAKE_PROJECT_NAME} DESTINATION lib/${ARCH})
install (FILES source/HMD_Bridge_API.h DESTINATION include)
install (DIRECTORY python/ DESTINATION .)
