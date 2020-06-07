#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mahi::robo" for configuration "RelWithDebInfo"
set_property(TARGET mahi::robo APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(mahi::robo PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/mahi-robo.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS mahi::robo )
list(APPEND _IMPORT_CHECK_FILES_FOR_mahi::robo "${_IMPORT_PREFIX}/lib/mahi-robo.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
