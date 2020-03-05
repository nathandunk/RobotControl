#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mahi::glfw" for configuration "Release"
set_property(TARGET mahi::glfw APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mahi::glfw PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/glfw3.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS mahi::glfw )
list(APPEND _IMPORT_CHECK_FILES_FOR_mahi::glfw "${_IMPORT_PREFIX}/lib/glfw3.lib" )

# Import target "mahi::glad" for configuration "Release"
set_property(TARGET mahi::glad APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mahi::glad PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/glad.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS mahi::glad )
list(APPEND _IMPORT_CHECK_FILES_FOR_mahi::glad "${_IMPORT_PREFIX}/lib/glad.lib" )

# Import target "mahi::nativefiledialog" for configuration "Release"
set_property(TARGET mahi::nativefiledialog APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mahi::nativefiledialog PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/nativefiledialog.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS mahi::nativefiledialog )
list(APPEND _IMPORT_CHECK_FILES_FOR_mahi::nativefiledialog "${_IMPORT_PREFIX}/lib/nativefiledialog.lib" )

# Import target "mahi::nanovg" for configuration "Release"
set_property(TARGET mahi::nanovg APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mahi::nanovg PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/nanovg.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS mahi::nanovg )
list(APPEND _IMPORT_CHECK_FILES_FOR_mahi::nanovg "${_IMPORT_PREFIX}/lib/nanovg.lib" )

# Import target "mahi::gui" for configuration "Release"
set_property(TARGET mahi::gui APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mahi::gui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/mahi-gui.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS mahi::gui )
list(APPEND _IMPORT_CHECK_FILES_FOR_mahi::gui "${_IMPORT_PREFIX}/lib/mahi-gui.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
