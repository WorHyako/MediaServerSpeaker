cmake_minimum_required(VERSION 3.23)

add_library(Mss_Backend)
add_library(Mss::Backend ALIAS Mss_Backend)

file(GLOB_RECURSE Sources ./*.cpp)
file(GLOB_RECURSE Headers ./*.hpp)
target_sources(Mss_Backend
        PRIVATE ${Sources}
        PRIVATE
        FILE_SET headers
        TYPE HEADERS
        FILES ${Headers})

target_link_libraries(Mss_Backend
        PUBLIC
        Qt6::Widgets
        Mss::System
        pugixml::pugixml
        Wor::Lib
        Wor::Sql
        Wor::Network
        Wor::Wrappers
        Wor::Midi)

target_include_directories(Mss_Backend
        PUBLIC include
        PRIVATE
        include/Command)

set_target_properties(Mss_Backend
        PROPERTIES
        AUTOMOC ON)
