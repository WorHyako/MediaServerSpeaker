if (APPLE)
    find_package(Threads REQUIRED)

    if (TARGET __cmake_cxx23)
        target_link_libraries(__cmake_cxx23
                PUBLIC
                Threads::Threads)

        target_compile_options(__cmake_cxx23
                PUBLIC
                $<$<CXX_COMPILER_ID:Clang>:-pthread>)
    else ()
        message(WARNING "Can't find CXX23 target.")
    endif ()
endif ()

add_library(unused_std_target STATIC)

set_target_properties(unused_std_target
        PROPERTIES
        EXCLUDE_FROM_ALL ON)

target_sources(unused_std_target
        PRIVATE
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS
        /opt/homebrew/Cellar/llvm/21.1.8/share/libc++/v1
        FILES
        /opt/homebrew/Cellar/llvm/21.1.8/share/libc++/v1/std.cppm
        /opt/homebrew/Cellar/llvm/21.1.8/share/libc++/v1/std.compat.cppm)
