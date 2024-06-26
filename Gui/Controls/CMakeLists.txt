cmake_minimum_required(VERSION 3.23)

add_library(Mss_Controls)
add_library(Mss::Controls ALIAS Mss_Controls)

file(GLOB Sources *.cpp)
target_sources(Mss_Controls
        PRIVATE ${Sources})

target_include_directories(Mss_Controls
        PUBLIC ../)

target_link_libraries(Mss_Controls
        PUBLIC Qt6::Widgets)
