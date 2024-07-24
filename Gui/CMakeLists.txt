cmake_minimum_required(VERSION 3.23)

#add_subdirectory(Controls)
#
#add_subdirectory(Actions)
#
#add_subdirectory(Components)
#
#add_subdirectory(Scopes)
#
#add_subdirectory(Dialogs)
#
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

file(GLOB_RECURSE Sources *.cpp)
target_sources(Mss_Gui
        PRIVATE ${Sources})

target_link_libraries(Mss_Gui
        PUBLIC
        Qt6::Widgets
#        Mss::System
        Mss::Backend)

target_include_directories(Mss_Gui
        PUBLIC .)

set_target_properties(Mss_Gui
        PROPERTIES
        AUTOMOC ON)

#target_precompile_headers(Mss_Gui
#        PRIVATE precompile_header.hpp)
