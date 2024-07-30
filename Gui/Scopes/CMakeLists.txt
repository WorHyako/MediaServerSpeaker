cmake_minimum_required(VERSION 3.23)

add_library(Mss_Scopes)
add_library(Mss::Scopes ALIAS Mss_Scopes)

file(GLOB_RECURSE Sources src/*.cpp)
target_sources(Mss_Scopes
        PRIVATE ${Sources})

set_target_properties(Mss_Scopes
        PROPERTIES
        AUTOMOC ON)

target_include_directories(Mss_Scopes
        PUBLIC include
        PRIVATE
        include/Scopes
        include/Menus
        include/Interfaces
        include/Tabs
        include/Config)

target_link_libraries(Mss_Scopes
        PUBLIC
        Qt6::Widgets
        Qt6::Core
        Mss::Components
        Mss::Controls)
