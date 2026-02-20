cmake_minimum_required(VERSION 3.8)
project(LibraryManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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