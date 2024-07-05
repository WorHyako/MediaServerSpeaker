cmake_minimum_required(VERSION 3.23)

############
#   soci   #
############
set(SOCI_EMPTY OFF)
set(SOCI_TESTS OFF)
set(SOCI_VISIBILITY OFF)
set(SOCI_FIREBIRD OFF)
set(SOCI_SQLITE3 OFF)
set(SOCI_ORACLE OFF)
set(SOCI_ODBC OFF)
set(SOCI_POSTGRESQL OFF)
set(SOCI_DB2 OFF)
add_subdirectory(soci)

#####################
#   nlohmann/json   #
#####################
set(JSON_BuildTests OFF)
set(JSON_CI OFF)
set(JSON_GlobalUDLs OFF)
set(JSON_Install OFF)
set(JSON_SystemInclude OFF)
set(JSON_SystemInclude OFF)
add_subdirectory(nlohmann-json)

##################
#   WorLibrary   #
##################
set(WORLIBRARY_JSON ON)
set(WORLIBRARY_DATA_CONVERTER ON)
set(WORLIBRARY_SQL ON)
set(WORLIBRARY_MATH ON)
set(WORLIBRARY_NETWORK ON)
set(WORLIBRARY_CURRENCY ON)
add_subdirectory(WorLibrary)

add_library(WorLibrary INTERFACE)
add_library(Wor::Lib ALIAS WorLibrary)

target_link_libraries(WorLibrary
        INTERFACE
        Wor::Converter
        Wor::Currency
        Wor::Json
        Wor::Math
        Wor::Network
        Wor::Sql)

##########
#   Qt   #
##########
find_package(Qt6 REQUIRED GLOBAL COMPONENTS
        Core
        Widgets
        Gui)

