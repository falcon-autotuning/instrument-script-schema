cmake_minimum_required(VERSION 3.15)
project(
  instrument-script-schema
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

# Find dependencies
find_package(yaml-cpp REQUIRED)
find_package(GTest REQUIRED)

# Embed schemas
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/schemas/instrument_api.schema.json"
     INSTRUMENT_API_SCHEMA)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/schemas/system_context.schema.json"
     SYSTEM_CONTEXT_SCHEMA)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/schemas/runtime_contexts.schema.json"
     RUNTIME_CONTEXTS_SCHEMA)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/embedded_schemas.cpp.in"
               "${CMAKE_CURRENT_BINARY_DIR}/embedded_schemas.cpp" @ONLY)

# Main library
add_library(
  instrument_script_schema src/schema_validator.cpp
                           "${CMAKE_CURRENT_BINARY_DIR}/embedded_schemas.cpp")

target_include_directories(
  instrument_script_schema
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)

target_link_libraries(instrument_script_schema PUBLIC yaml-cpp)

# Set library properties
set_target_properties(instrument_script_schema
                      PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1)

# Template expander tool
add_executable(template_expander src/template_expander.cpp)
target_link_libraries(template_expander PRIVATE yaml-cpp)

# Tests
if(BUILD_TESTS)
  enable_testing()

  add_executable(test_validator tests/test_validator.cpp)
  target_link_libraries(test_validator PRIVATE instrument_script_schema
                                               GTest::gtest GTest::gtest_main)
  add_test(NAME ValidatorTests COMMAND test_validator)
endif()

# Install targets
install(
  TARGETS instrument_script_schema
  EXPORT instrument-script-schema-targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Install schemas and examples
install(DIRECTORY schemas/ DESTINATION share/instrument-script/schemas)

install(DIRECTORY lua_types/ DESTINATION share/instrument-script/lua_types)

install(DIRECTORY examples/ DESTINATION share/instrument-script/examples)

# Package configuration
include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/instrument-script-schema-config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/instrument-script-schema-config.cmake"
  INSTALL_DESTINATION lib/cmake/instrument-script-schema)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/instrument-script-schema-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/instrument-script-schema-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/instrument-script-schema-config-version.cmake"
  DESTINATION lib/cmake/instrument-script-schema)

install(
  EXPORT instrument-script-schema-targets
  FILE instrument-script-schema-targets.cmake
  NAMESPACE InstrumentScript::
  DESTINATION lib/cmake/instrument-script-schema)
