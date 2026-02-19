cmake_minimum_required(VERSION 3.8)
project(LibraryManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Sources
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${MY_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/includes/"
    "${CMAKE_CURRENT_SOURCE_DIR}/externals/nlohmann" #include json
)

# Copy resources after every build
file(GLOB_RECURSE MY_RESOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/res/*"
)

# # Define a custom target to copy the whole res folder
# add_custom_target(copy_resources ALL
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/res
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_SOURCE_DIR}/res
#             ${CMAKE_CURRENT_BINARY_DIR}/res
#     DEPENDS ${MY_RESOURCE_FILES}
# )

# # Make sure resources are updated before building the executable
# add_dependencies(${PROJECT_NAME} copy_resources)