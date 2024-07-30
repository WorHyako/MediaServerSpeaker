cmake_minimum_required(VERSION 3.23)

add_library(Mss_Scopes SHARED)
add_library(Mss::Scopes ALIAS Mss_Scopes)

file(GLOB_RECURSE Sources src/*.cpp)
file(GLOB_RECURSE Headers include/*.hpp)
target_sources(Mss_Scopes
        PRIVATE ${Sources}
        PRIVATE FILE_SET headers
        TYPE HEADERS
        FILES ${Headers})

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
        Mss::Controls)
