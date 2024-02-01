#
# This proprietary code is created by dload0, and is subject to use only in Nyx. Unauthorized use
# of this code is prohibited by our Terms of Service. Copyright © 2023 Nyx. All rights reserved.
#
# -> `CMakeLists.txt` : 29/01/24
# ...
# our cmake :communism:

cmake_minimum_required(VERSION 3.12)

# Debug stripping.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DEBUG:NONE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /FORCE:MULTIPLE")
# add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:FORCE:MULTIPLE>")

# Set up project.
project(NPvP)

# Set up required packages.
find_package(JNI REQUIRED)
find_package(Java REQUIRED)

# Allow `UseJava` toolchain.
include(UseJava)

# Building using JDK 19.
set(JAVA_HOME "C:/Program Files/Java/jdk-19/bin")           # Modify to Java version path.
set(CMAKE_Java_COMPILE_FLAGS "-source" "19" "-target" "19") # Match Java version.

# Building using standard 20.
set(CMAKE_CXX_STANDARD 20)

# JNI binding.
include_directories(${JNI_INCLUDE_DIRS})

# Add all source files in the src folder to the library.
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE C_SOURCES "src/*.c")

# Add main src file.
add_library(NPvP SHARED ${CPP_SOURCES} ${C_SOURCES}
        src/main.cpp
)

target_link_options(NPvP PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>")

# Add `JNI` and `ws2_32` and `minhook`.
target_link_libraries(NPvP PRIVATE ${JNI_LIBRARIES} ws2_32)
