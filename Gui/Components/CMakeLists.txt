cmake_minimum_required(VERSION 3.23)

add_library(Mss_Components)
add_library(Mss::Components ALIAS Mss_Components)

file(GLOB Sources src/*.cpp)
target_sources(Mss_Components
        PRIVATE ${Sources})

target_include_directories(Mss_Components
        PRIVATE include/Components
        PUBLIC include)

target_link_libraries(Mss_Components
        PUBLIC
        Qt6::Widgets
        Qt6::Core
        Mss::Backend)
