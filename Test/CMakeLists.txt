
cmake_minimum_required(VERSION 2.8)

PROJECT(Test)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED QUIET)


 
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES *.ui)
file(GLOB QT_WRAP *.h)
file(GLOB CPP_FILES *.cpp)

qt5_wrap_ui(UISrcs ${UI_FILES} )
add_executable(Test MACOSX_BUNDLE ${CPP_FILES} ${UISrcs} ${QT_WRAP})

qt5_use_modules(Test Core Gui)
target_link_libraries(Test ${VTK_LIBRARIES})
