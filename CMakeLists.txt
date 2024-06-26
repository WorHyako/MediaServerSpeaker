cmake_minimum_required(VERSION 3.23)

project(MediaServerSpeaker
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(CMAKE_AUTOMOC ON)

add_subdirectory(ThirdParty)

################
#   Mss::Gui   #
################
add_subdirectory(Gui)

##########################
#   MediaServerSpeaker   #
##########################
add_executable(MediaServerSpeaker)

target_sources(MediaServerSpeaker
        PRIVATE Src/main.cpp)

target_include_directories(MediaServerSpeaker
        PRIVATE Include)

target_link_libraries(MediaServerSpeaker
        PRIVATE
        Mss::Gui
        Soci::core)
