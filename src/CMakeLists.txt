cmake_minimum_required (VERSION 2.8.11)
project (NavetasResearch)

add_library (NavetasResearch readData.cpp currentMedianFilter.cpp)
target_include_directories (NavetasResearch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (readDataMedianFilter readDataMedianFilter.cpp)

target_link_libraries (readDataMedianFilter LINK_PUBLIC NavetasResearch)



