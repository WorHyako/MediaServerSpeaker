set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)

set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk" CACHE PATH "" FORCE)

set(VCPKG_OSX_ARCHITECTURES arm64)

set(LLVM_ROOT "/opt/homebrew/opt/llvm")

set(VCPKG_CMAKE_SYSTEM_NAME Darwin)
set(VCPKG_TARGET_ARCHITECTURE arm64)

set(VCPKG_CMAKE_CONFIGURE_OPTIONS
        "-DCMAKE_C_COMPILER=${LLVM_ROOT}/bin/clang"
        "-DCMAKE_CXX_COMPILER=${LLVM_ROOT}/bin/clang++")
