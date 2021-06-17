cmake_minimum_required(VERSION 3.0.2)
project(pigeon_tui)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/aaleino/FTXUI
  GIT_TAG 40929423e0b3eb5e276661be91f183641440cd5c
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


add_library(pigeon_robot_steering
    src/pigeon_robot_steering.cpp
    include/pigeon_tui/pigeon_robot_steering.h
    )

add_library(pigeon_terminal
    include/pigeon_terminal/pigeon_terminal.h
    src/pigeon_terminal/pigeon_terminal.cpp
    )

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pigeon_tui
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pigeon_robot_steering_node src/pigeon_robot_steering.cpp)
target_link_libraries(pigeon_robot_steering_node
  PRIVATE pigeon_terminal
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component ${catkin_LIBRARIES})
