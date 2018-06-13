# Define library. Only source files here!
project(DataContainerLib VERSION 0.1 LANGUAGES CXX)

add_library(dataContainerLib
    src/powermeasurement.cpp
    src/powervalue.cpp
  )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(dataContainerLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# If we have compiler requirements for this library, list them
# here
target_compile_features(dataContainerLib
    PRIVATE cxx_std_17)

# Depend on a library that we defined in the top-level file
#target_link_libraries(lib
#    boost
#    MyOtherLibrary)

# 'make install' to the correct locations (provided by GNUInstallDirs).
#install(TARGETS lib EXPORT MyLibraryConfig
#    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
#install(EXPORT MyLibraryConfig DESTINATION share/MyLibrary/cmake)

# This makes the project importable from the build directory
export(TARGETS dataContainerLib FILE MyLibraryConfig.cmake)

# Every library has unit tests, of course
add_executable(testDataContainerLib
    test/main.cpp
    test/pwrmsrcontainertest
    test/powervaluecontainertest
    )

target_link_libraries(testDataContainerLib
    dataContainerLib gtest gtest_main)
target_compile_features(testDataContainerLib
    PRIVATE cxx_std_17)

add_test(testDataContainerLib testDataContainerLib)
