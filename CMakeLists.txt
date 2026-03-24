cmake_minimum_required(VERSION 4.1)
project(projekt)

set(CMAKE_CXX_STANDARD 20)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

add_executable(projekt main.cpp)
target_link_libraries(projekt ${wxWidgets_LIBRARIES})