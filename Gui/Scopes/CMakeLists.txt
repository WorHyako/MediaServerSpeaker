cmake_minimum_required(VERSION 3.23)

add_library(Mss_Scopes)
add_library(Mss::Scopes ALIAS Mss_Scopes)

file(GLOB Sources *.cpp)
target_sources(Mss_Scopes
        PRIVATE ${Sources})

target_include_directories(Mss_Scopes
        PUBLIC ../)

target_link_libraries(Mss_Scopes
        PUBLIC Qt6::Widgets)
