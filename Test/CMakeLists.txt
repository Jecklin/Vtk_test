
cmake_minimum_required(VERSION 2.8)
 


PROJECT(Test)
 


find_package(VTK REQUIRED)


include(${VTK_USE_FILE})
 


add_executable(Test MACOSX_BUNDLE Test.cpp )
 

target_link_libraries(Test ${VTK_LIBRARIES})
