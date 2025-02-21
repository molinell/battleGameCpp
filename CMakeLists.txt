cmake_minimum_required(VERSION 3.10)

project(BattleGame)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

find_package(Boost 1.86 REQUIRED COMPONENTS serialization)

# Add your source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

# Create executable
add_executable(BG ${SOURCES})

# Set include directories
target_include_directories(BG PRIVATE include ${Boost_INCLUDE_DIRS})
target_link_libraries(BG PRIVATE ${Boost_LIBRARIES})
