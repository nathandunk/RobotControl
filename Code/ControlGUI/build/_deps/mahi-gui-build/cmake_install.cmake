# Install script for directory: C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/ControlGUI")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/glfw/src/glfw3.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/glad/glad.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/nativefiledialog-extended/src/nfd.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/nanovg/nanovg.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/clipper/clipper.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/mahi-gui.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/include/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/glad/include/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/imgui/imconfig.h"
    "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/imgui/imgui_internal.h"
    "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/imgui/imgui.h"
    "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/imgui/imstb_rectpack.h"
    "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/imgui/imstb_textedit.h"
    "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/imgui/imstb_truetype.h"
    "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/imgui/imgui_stdlib.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/nanovg/src/nanovg.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/nanosvg/src/nanosvg.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-src/3rdparty/clipper/clipper.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/mahi-gui/mahi-gui-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/mahi-gui/mahi-gui-targets.cmake"
         "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/CMakeFiles/Export/lib/cmake/mahi-gui/mahi-gui-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/mahi-gui/mahi-gui-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/mahi-gui/mahi-gui-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/mahi-gui" TYPE FILE FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/CMakeFiles/Export/lib/cmake/mahi-gui/mahi-gui-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/mahi-gui" TYPE FILE FILES "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/CMakeFiles/Export/lib/cmake/mahi-gui/mahi-gui-targets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/mahi-gui" TYPE FILE FILES
    "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/mahi-gui-config.cmake"
    "C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/mahi-gui-config-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/glfw/cmake_install.cmake")
  include("C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/glad/cmake_install.cmake")
  include("C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/nativefiledialog-extended/cmake_install.cmake")
  include("C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/nanovg/cmake_install.cmake")
  include("C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/3rdparty/clipper/cmake_install.cmake")
  include("C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-util-build/cmake_install.cmake")
  include("C:/Git/RobotControl/Code/ControlGUI/build/_deps/mahi-gui-build/src/Mahi/Gui/cmake_install.cmake")

endif()

