cmake_minimum_required(VERSION 3.23)

add_subdirectory(Controls)

add_subdirectory(Components)

add_subdirectory(Style)

add_subdirectory(Creators)

add_subdirectory(Scopes)

#set_target_properties(Mss_Actions
#        Mss_Actions
#        Mss_Components
#        Mss_Controls
#        Mss_Dialogs
#        Mss_Scopes
#        PROPERTIES
#        AUTOMOC ON)
#
#add_library(Mss_Gui INTERFACE)
#add_library(Mss::Gui ALIAS Mss_Gui)
#
#target_link_libraries(Mss_Gui
#        INTERFACE
#        Mss::Actions
#        Mss::Components
#        Mss::Controls
#        Mss::Dialogs
#        Mss::Scopes)

add_library(Mss_Gui)
add_library(Mss::Gui ALIAS Mss_Gui)

target_sources(Mss_Gui
        PRIVATE MainWindow.cpp)

target_link_libraries(Mss_Gui
        PUBLIC
        Qt6::Widgets
        Mss::Components
        Mss::Controls
        Mss::Backend
        Mss::Creators
        Mss::Scopes
        INTERFACE
        Mss::Style)

target_include_directories(Mss_Gui
        PUBLIC .)

set_target_properties(Mss_Gui
        PROPERTIES
        AUTOMOC ON)
