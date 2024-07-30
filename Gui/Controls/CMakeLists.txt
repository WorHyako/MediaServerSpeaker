cmake_minimum_required(VERSION 3.23)

qt_add_library(Mss_Controls SHARED)
add_library(Mss::Controls ALIAS Mss_Controls)

file(GLOB_RECURSE Sources src/*.cpp)
target_sources(Mss_Controls
        PRIVATE ${Sources})

set_target_properties(Mss_Controls
        PROPERTIES
        AUTOMOC ON)

target_include_directories(Mss_Controls
        PUBLIC include
        PRIVATE
        include/Controls
        include/Dialogs
        include/Menus)

target_link_libraries(Mss_Controls
        PUBLIC
        Qt6::Widgets
        Qt6::Core
        Mss::Components
        Mss::Style
        Mss::Backend
        Mss::Creators)

add_library(Mss_Controls_shared SHARED $<TARGET_OBJECTS:Mss_Controls>)
add_library(Mss_Controls_static STATIC $<TARGET_OBJECTS:Mss_Controls>)