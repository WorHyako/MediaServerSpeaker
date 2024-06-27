cmake_minimum_required(VERSION 3.23)

add_subdirectory(Controls)

add_subdirectory(Actions)

add_subdirectory(Components)

add_subdirectory(Scopes)

add_subdirectory(Dialogs)

set_target_properties(Mss_Actions
        Mss_Actions
        Mss_Components
        Mss_Controls
        Mss_Dialogs
        Mss_Scopes
        PROPERTIES
        AUTOMOC ON)

add_library(Mss_Gui INTERFACE)
add_library(Mss::Gui ALIAS Mss_Gui)

target_link_libraries(Mss_Gui
        INTERFACE
        Mss::Actions
        Mss::Components
        Mss::Controls
        Mss::Dialogs
        Mss::Scopes)
