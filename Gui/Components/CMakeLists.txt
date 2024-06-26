cmake_minimum_required(VERSION 3.23)

add_library(Mss_Components)
add_library(Mss::Components ALIAS Mss_Components)

file(GLOB Sources *.cpp)
target_sources(Mss_Components
        PRIVATE ${Sources})

target_include_directories(Mss_Components
        PUBLIC ../)

target_link_libraries(Mss_Components
        PUBLIC Qt6::Widgets)
