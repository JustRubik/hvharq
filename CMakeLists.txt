cmake_minimum_required(VERSION 3.12)

project(HVHarq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files .cpp
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(hvharq ${SRC_FILES})

# Include files .h
target_include_directories(hvharq PUBLIC include)

# add_custom_command(TARGET hvharq POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         # "${CMAKE_SOURCE_DIR}/dll"
#         "$<TARGET_FILE_DIR:hvharq>"
#         COMMENT "Copying .dll/.so files to build/"
# )
