# ----------- #
#   openssl   #
# ----------- #
find_package(OpenSSL CONFIG REQUIRED GLOBAL)

# ------- #
#   fmt   #
# ------- #
find_package(fmt CONFIG REQUIRED GLOBAL)

# ----------- #
#   pugixml   #
# ----------- #
set(PUGIXML_INSTALL OFF)
find_package(pugixml CONFIG REQUIRED GLOBAL)

# ----------------- #
#   nlohmann/json   #
# ----------------- #
set(JSON_BuildTests OFF)
set(JSON_CI OFF)
set(JSON_GlobalUDLs OFF)
set(JSON_Install OFF)
set(JSON_SystemInclude OFF)
set(JSON_SystemInclude OFF)
find_package(nlohmann_json CONFIG REQUIRED GLOBAL)

# -------------- #
#   WorLibrary   #
# -------------- #
set(WORLIBRARY_JSON ON)
set(WORLIBRARY_DATA_CONVERTER ON)
set(WORLIBRARY_SQL ON)
set(WORLIBRARY_LOG ON)
set(WOR_DEV_LOG ON)
set(WORLIBRARY_MATH ON)
set(WORLIBRARY_NETWORK ON)
set(WORLIBRARY_CURRENCY ON)
set(WORLIBRARY_WRAPPERS ON)
set(WORLIBRARY_MIDI ON)
add_subdirectory(WorLibrary)

# ------------ #
#   ConfData   #
# ------------ #
add_subdirectory(MediaServerSpeaker_ConfData)

# ------ #
#   Qt   #
# ------ #
find_package(Qt6 COMPONENTS
        Widgets Gui GLOBAL REQUIRED)

# --------- #
#   Tracy   #
# --------- #
find_package(Tracy CONFIG REQUIRED GLOBAL)

# -------------- #
#   WorLibrary   #
# -------------- #
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
