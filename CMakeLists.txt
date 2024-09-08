cmake_minimum_required(VERSION 3.23)

project(MediaServerSpeaker
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

option(LOG_TO_FILE "" OFF)

if (LOG_TO_FILE)
    add_compile_definitions(LOG_TO_FILE)
endif ()

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

####################
#   Mss::Backend   #
####################
add_subdirectory(Backend)

################
#   Mss::Gui   #
################
add_subdirectory(Gui)

##########################
#   MediaServerSpeaker   #
##########################
add_executable(MediaServerSpeaker)

target_sources(MediaServerSpeaker
        PRIVATE main.cpp)

target_link_libraries(MediaServerSpeaker
        PRIVATE
        Mss::Gui
        Mss::ConfData)

file(GLOB Resources Resources/*)
file(COPY ${Resources} DESTINATION ${CMAKE_BINARY_DIR}/Resources)

##############
#   Bridge   #
##############
add_executable(bridge)
target_sources(bridge
        PRIVATE bridge/main.cpp)
target_link_libraries(bridge
        PUBLIC
        pugixml::pugixml
        Wor::Network)
