# Require a fairly up to date cmake
cmake_minimum_required(VERSION 3.2)

# Add Hunter support for 3rd parties
include(cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.20.22.tar.gz"
    SHA1 "91e2d0346f2d3d7edcc1a036a4f7733aa5c0334d"
)

# Create project using C++
project(elysion_engine VERSION 0.0.1 LANGUAGES CXX)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

# Include Catch as an imported target
hunter_add_package(Catch)
find_package(Catch2 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(src)
add_subdirectory(unit_test)
