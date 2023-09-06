#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OSMManager" for configuration "MinSizeRel"
set_property(TARGET OSMManager APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(OSMManager PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/OSMManager-1.0/libOSMManager.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS OSMManager )
list(APPEND _IMPORT_CHECK_FILES_FOR_OSMManager "${_IMPORT_PREFIX}/lib/OSMManager-1.0/libOSMManager.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
