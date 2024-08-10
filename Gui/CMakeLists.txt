cmake_minimum_required(VERSION 3.23)

add_subdirectory(Controls)

add_subdirectory(Components)

add_subdirectory(Style)

add_subdirectory(Creators)

add_subdirectory(Scopes)

add_subdirectory(Dialogs)

add_library(Mss_Gui INTERFACE)
add_library(Mss::Gui ALIAS Mss_Gui)

target_link_libraries(Mss_Gui
        INTERFACE
        Qt6::Widgets
        Mss::Controls
        Mss::Backend
        Mss::Creators
        Mss::Scopes
        Mss::Dialogs
        Mss::Style)
