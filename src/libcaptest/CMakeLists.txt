add_library(libcaptest captest.cpp)
target_link_libraries(libcaptest cap)
target_include_directories(libcaptest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})