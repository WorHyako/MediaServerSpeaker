cmake_minimum_required(VERSION 3.23)

add_library(Mss_Dialogs)
add_library(Mss::Dialogs ALIAS Mss_Dialogs)

file(GLOB Sources *.cpp)
target_sources(Mss_Dialogs
        PRIVATE ${Sources})

target_include_directories(Mss_Dialogs
        PUBLIC ../)

target_link_libraries(Mss_Dialogs
        PUBLIC Qt6::Widgets)
