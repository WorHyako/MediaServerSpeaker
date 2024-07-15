cmake_minimum_required(VERSION 3.23)

project(MediaServerSpeaker
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

##################
#   Mss System   #
##################
add_library(Mss_System)
add_library(Mss::System ALIAS Mss_System)

file(GLOB_RECURSE Sources Project/*.cpp)

target_sources(Mss_System
        PRIVATE ${Sources})

target_include_directories(Mss_System
        PUBLIC Project)

##################
#   ThirdParty   #
##################
add_subdirectory(ThirdParty)

################
#   Mss::Gui   #
################
add_subdirectory(Gui)

####################
#   Mss::Backend   #
####################
add_subdirectory(Backend)

##########################
#   MediaServerSpeaker   #
##########################
add_executable(MediaServerSpeaker)

target_sources(MediaServerSpeaker
        PRIVATE main.cpp)

target_include_directories(MediaServerSpeaker
        PRIVATE Include)

target_link_libraries(MediaServerSpeaker
        PRIVATE
        Mss::Gui
        Soci::core)

file(GLOB Resources Resources/*)
file(COPY ${Resources} DESTINATION ${CMAKE_BINARY_DIR}/Resources)
