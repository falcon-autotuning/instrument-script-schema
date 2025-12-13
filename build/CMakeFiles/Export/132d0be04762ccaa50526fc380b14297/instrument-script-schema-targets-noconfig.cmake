#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "InstrumentScript::instrument_script_schema" for configuration ""
set_property(TARGET InstrumentScript::instrument_script_schema APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(InstrumentScript::instrument_script_schema PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libinstrument_script_schema.a"
  )

list(APPEND _cmake_import_check_targets InstrumentScript::instrument_script_schema )
list(APPEND _cmake_import_check_files_for_InstrumentScript::instrument_script_schema "${_IMPORT_PREFIX}/lib/libinstrument_script_schema.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
