cmake_minimum_required(VERSION 3.30)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cxx_modules_flags)

project(MediaServerSpeaker
        LANGUAGES CXX)

include(cxx_modules_deps)

option(LOG_TO_FILE "" OFF)

if (LOG_TO_FILE)
    add_compile_definitions(LOG_TO_FILE)
endif ()

# -------------- #
#   Mss System   #
# -------------- #
add_subdirectory(Project)

# -------------- #
#   ThirdParty   #
# -------------- #
add_subdirectory(ThirdParty)

# ---------------- #
#   mss::backend   #
# ---------------- #
add_subdirectory(Backend)

# ------------ #
#   Mss::Gui   #
# ------------ #
add_subdirectory(Gui)

# ---------------------- #
#   MediaServerSpeaker   #
# ---------------------- #
add_executable(MediaServerSpeaker)

target_sources(MediaServerSpeaker
        PRIVATE main.cpp)

target_link_libraries(MediaServerSpeaker
        PRIVATE
        Mss::Gui
        Tracy::TracyClient
        Mss::ConfData)

file(GLOB Resources Resources/*)
file(COPY ${Resources} DESTINATION ${CMAKE_BINARY_DIR}/Resources)

# ---------- #
#   Bridge   #
# ---------- #
add_executable(bridge)
target_sources(bridge
        PRIVATE bridge/main.cpp)
target_link_libraries(bridge
        PUBLIC
        pugixml::pugixml
        Wor::Network)
