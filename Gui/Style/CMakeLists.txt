add_library(mss.style)
add_library(mss::style ALIAS mss.style)

target_include_directories(mss.style
        PUBLIC include)

target_sources(mss.style
        PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        Style.ixx
        include/WorStyle.cppm
        include/TextEditStyle.cppm
        include/LineEditStyle.cppm
        include/WidgetControlStyle.cppm
        include/ButtonStyle.cppm)

target_link_libraries(mss.style
        PUBLIC
        __cmake_cxx23)

set_target_properties(mss.style
        PROPERTIES
        CMAKE_CXX_MODULE_STD ON)
