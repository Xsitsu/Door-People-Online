cmake_minimum_required(VERSION 3.17)

project(DoorPeopleOnline VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(DllExport)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(Client)
add_subdirectory(GameCore)
add_subdirectory(Network)
add_subdirectory(Server)
add_subdirectory(Util)
