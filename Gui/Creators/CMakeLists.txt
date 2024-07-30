cmake_minimum_required(VERSION 3.23)

add_library(Mss_Creators INTERFACE)
add_library(Mss::Creators ALIAS Mss_Creators)

target_include_directories(Mss_Creators
        INTERFACE include)
