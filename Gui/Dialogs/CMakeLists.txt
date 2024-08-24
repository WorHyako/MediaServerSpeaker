cmake_minimum_required(VERSION 3.23)

add_library(Mss_Dialogs)
add_library(Mss::Dialogs ALIAS Mss_Dialogs)

file(GLOB_RECURSE Sources src/*.cpp)
file(GLOB_RECURSE Headers include/*.hpp)

target_sources(Mss_Dialogs
        PRIVATE ${Sources}
        PRIVATE FILE_SET headers
        TYPE HEADERS
        FILES ${Headers})

set_target_properties(Mss_Dialogs
        PROPERTIES
        AUTOMOC ON)

target_include_directories(Mss_Dialogs
        PUBLIC include
        PRIVATE include/Dialogs)

target_link_libraries(Mss_Dialogs
        PUBLIC
        Qt6::Widgets
        Qt6::Core
        Mss::Scopes
        Wor::Network
        Wor::Template
        Wor::Midi)
