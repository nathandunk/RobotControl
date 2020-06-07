#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mahi::fmt" for configuration "MinSizeRel"
set_property(TARGET mahi::fmt APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(mahi::fmt PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/fmt.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS mahi::fmt )
list(APPEND _IMPORT_CHECK_FILES_FOR_mahi::fmt "${_IMPORT_PREFIX}/lib/fmt.lib" )

# Import target "mahi::util" for configuration "MinSizeRel"
set_property(TARGET mahi::util APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(mahi::util PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/mahi-util.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS mahi::util )
list(APPEND _IMPORT_CHECK_FILES_FOR_mahi::util "${_IMPORT_PREFIX}/lib/mahi-util.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
