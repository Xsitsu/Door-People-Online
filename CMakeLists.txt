cmake_minimum_required(VERSION 3.17)

IF (WIN32)
    set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
    set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
ENDIF ()

project(DoorPeopleOnline VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_BINARY_DIR}/CPM_modules")

include(GNUInstallDirs)  # https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}" CACHE PATH ".lib, .a, etc.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}" CACHE PATH ".so, .dylib, etc.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}" CACHE PATH ".exe, .dll, etc.")

include(DllExport)

file(REAL_PATH "${PROJECT_BINARY_DIR}/../_dependency-cache" CPM_SOURCE_CACHE)

include(cpm)  # CPM.cmake has to come before dependencies

IF (WIN32)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindFreetype.cmake.in ${CMAKE_BINARY_DIR}/CPM_modules/FindFreetype.cmake @ONLY)
ENDIF ()

#include(allegro)

include_directories(${CMAKE_CURRENT_LIST_DIR})

#add_subdirectory(client)
#add_subdirectory(gamecore)
#add_subdirectory(network)
#add_subdirectory(server)
#add_subdirectory(util)
