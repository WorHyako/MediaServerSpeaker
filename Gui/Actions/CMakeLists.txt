cmake_minimum_required(VERSION 3.23)

add_library(Mss_Actions)
add_library(Mss::Actions ALIAS Mss_Actions)

file(GLOB Sources *.cpp)
target_sources(Mss_Actions
        PRIVATE ${Sources})

target_include_directories(Mss_Actions
        PUBLIC ../)

target_link_libraries(Mss_Actions
        PUBLIC Qt6::Widgets)
