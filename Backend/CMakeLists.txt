add_library(mss.backend)
add_library(mss::backend ALIAS mss.backend)

file(GLOB_RECURSE Sources src/*.cpp)
file(GLOB_RECURSE Headers include/*.hpp)

target_sources(mss.backend
        PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        Backend.ixx
        include/Command/CommandBuilder.cppm
        include/Midi/MidiRoadMap.cppm
        include/Midi/MidiRoad.cppm
        include/Midi/ServerRoad.cppm

        PRIVATE
        FILE_SET cxx_modules_impl
        TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        src/Midi/MidiRoadMap.cpp
        src/Midi/MidiRoad.cpp
        src/Midi/ServerRoad.cpp

        PRIVATE ${Sources}
        PRIVATE
        FILE_SET headers
        TYPE HEADERS
        FILES ${Headers})

target_link_libraries(mss.backend
        PUBLIC
        __cmake_cxx23
        Mss::System
        pugixml::pugixml
        Wor::Lib
        Wor::Sql
        Wor::Network
        Wor::Wrappers
        Wor::Midi)

target_include_directories(mss.backend
        PUBLIC include
        PRIVATE
        include/Command)

set_target_properties(mss.backend
        PROPERTIES
        CMAKE_CXX_MODULE_STD ON)
