cmake_minimum_required(VERSION 3.23)

add_library(Mss_Backend)
add_library(Mss::Backend ALIAS Mss_Backend)

file(GLOB_RECURSE Sources *.cpp)
target_sources(Mss_Backend
        PRIVATE ${Sources})

target_link_libraries(Mss_Backend
        PUBLIC
        Qt6::Widgets
        Wor::Lib
        Mss::System
        pugixml::pugixml)

target_include_directories(Mss_Backend
        PUBLIC .)

set_target_properties(Mss_Backend
        PROPERTIES
        AUTOMOC ON)
