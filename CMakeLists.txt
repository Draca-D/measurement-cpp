cmake_minimum_required(VERSION 3.14)

project(measurement-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(RUN_TESTS "Build and run tests" OFF)

# === Library Target (Header-only) ===
add_library(measurement INTERFACE)
target_include_directories(measurement INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(RUN_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    add_executable(measurement-tests test/measurement-tests.cpp
        readme.md)
    target_link_libraries(measurement-tests
        measurement
        GTest::GTest
        GTest::Main
    )

    add_test(NAME MeasurementTests COMMAND measurement-tests)
endif()

# === Installation (always) ===
include(GNUInstallDirs)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS measurement
    EXPORT measurementTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT measurementTargets
    FILE measurementTargets.cmake
    NAMESPACE measurement::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/measurement-cpp
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/measurement-cppConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/measurement-cppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/measurement-cppConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/measurement-cpp
)
