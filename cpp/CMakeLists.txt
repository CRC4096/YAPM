# At LEAST 2.8 but newer is better
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(YAPM VERSION 0.1 LANGUAGES CXX)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
#include(GNUInstallDirs)

# Some other library that we import that was also built using CMake
# and has an exported target.
#find_package(MyOtherLibrary REQUIRED)

# Targets that we develop here
enable_testing()
add_subdirectory(DataServiceLib)
add_subdirectory(MetricsLib)
add_subdirectory(YAPMApp)
