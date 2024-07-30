cmake_minimum_required(VERSION 3.23)

add_library(Mss_Style INTERFACE)
add_library(Mss::Style ALIAS Mss_Style)

target_include_directories(Mss_Style
        INTERFACE include)
