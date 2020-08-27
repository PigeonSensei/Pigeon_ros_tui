cmake_minimum_required(VERSION 3.0.2)
project(pigeon_tui)

## Compile as C++11, supported in ROS Kinetic and newer
 add_compile_options(-std=c++17)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
)

find_package(Threads)

add_library(screen
  src/ftxui/screen/box.cpp
  src/ftxui/screen/screen.cpp
  src/ftxui/screen/string.cpp
  src/ftxui/screen/terminal.cpp
  src/ftxui/screen/wcwidth.cpp
  include/ftxui/screen/box.hpp
  include/ftxui/screen/color.hpp
  include/ftxui/screen/screen.hpp
  include/ftxui/screen/string.hpp
)

add_library(dom
  include/ftxui/dom/elements.hpp
  include/ftxui/dom/node.hpp
  include/ftxui/dom/requirement.hpp
  include/ftxui/dom/take_any_args.hpp
  src/ftxui/dom/blink.cpp
  src/ftxui/dom/bold.cpp
  src/ftxui/dom/border.cpp
  src/ftxui/dom/color.cpp
  src/ftxui/dom/composite_decorator.cpp
  src/ftxui/dom/dbox.cpp
  src/ftxui/dom/dim.cpp
  src/ftxui/dom/flex.cpp
  src/ftxui/dom/frame.cpp
  src/ftxui/dom/gauge.cpp
  src/ftxui/dom/graph.cpp
  src/ftxui/dom/hbox.cpp
  src/ftxui/dom/hflow.cpp
  src/ftxui/dom/inverted.cpp
  src/ftxui/dom/node.cpp
  src/ftxui/dom/node_decorator.cpp
  src/ftxui/dom/paragraph.cpp
  src/ftxui/dom/separator.cpp
  src/ftxui/dom/size.cpp
  src/ftxui/dom/spinner.cpp
  src/ftxui/dom/text.cpp
  src/ftxui/dom/underlined.cpp
  src/ftxui/dom/util.cpp
  src/ftxui/dom/vbox.cpp
)

add_library(component
  src/ftxui/component/checkbox.cpp
  src/ftxui/component/component.cpp
  src/ftxui/component/container.cpp
  src/ftxui/component/event.cpp
  src/ftxui/component/input.cpp
  src/ftxui/component/menu.cpp
  src/ftxui/component/radiobox.cpp
  src/ftxui/component/radiobox.cpp
  src/ftxui/component/screen_interactive.cpp
  src/ftxui/component/toggle.cpp
  include/ftxui/component/checkbox.hpp
  include/ftxui/component/component.hpp
  include/ftxui/component/container.hpp
  include/ftxui/component/event.hpp
  include/ftxui/component/input.hpp
  include/ftxui/component/menu.hpp
  include/ftxui/component/radiobox.hpp
  include/ftxui/component/screen_interactive.hpp
  include/ftxui/component/receiver.hpp
  include/ftxui/component/toggle.hpp
)

add_library(ftxui::screen ALIAS screen)
add_library(ftxui::dom ALIAS dom)
add_library(ftxui::component ALIAS component)

target_link_libraries(dom PUBLIC screen)
target_link_libraries(component PUBLIC dom Threads::Threads)

foreach(lib screen dom component)
  target_include_directories(${lib}
    PUBLIC
      $<INSTALL_INTERFACE:include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
      src
  )

# C++17 is used. We requires fold expression at least.
set_property(TARGET ${lib} PROPERTY CXX_STANDARD 17)

# Force Microsoft Visual Studio to decode sources files in UTF-8. This applies
# to the library and the library users.
if (MSVC)
  target_compile_options(${lib} PUBLIC "/utf-8")
endif()

# Add as many warning as possible:
if (WIN32)
  if (MSVC)
    target_compile_options(${lib} PRIVATE "/W4")
    target_compile_options(${lib} PRIVATE "/WX")
    target_compile_options(${lib} PRIVATE "/wd4244")
    target_compile_options(${lib} PRIVATE "/wd4267")
  endif()
  # Force Win32 to UNICODE
  target_compile_definitions(${lib} PRIVATE UNICODE _UNICODE)
else()
  target_compile_options(${lib} PRIVATE "-Wall")
  target_compile_options(${lib} PRIVATE "-Wextra")
  target_compile_options(${lib} PRIVATE "-pedantic")
  target_compile_options(${lib} PRIVATE "-Werror")
  target_compile_options(${lib} PRIVATE "-Wno-sign-compare")
endif()

endforeach()

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pigeon_tui
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pigeon_robot_steering_node src/pigeon_robot_steering.cpp)
target_link_libraries(pigeon_robot_steering_node PRIVATE screen PRIVATE component PRIVATE gtest PRIVATE gmock PRIVATE gtest_main ${catkin_LIBRARIES})
## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/pigeon_tui.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/pigeon_tui_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_pigeon_tui.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
