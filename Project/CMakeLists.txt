add_library(mss.system)
add_library(mss::system ALIAS mss.system)

target_sources(mss.system
        PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        Project.ixx
        Files.cppm
        JsonContentKeys.cppm)

target_link_libraries(mss.system
        PUBLIC
        __cmake_cxx23)
