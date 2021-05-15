cmake_minimum_required(VERSION 3.9.2)

project(Cheddar VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -Wall")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.67.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost couldn't be found!")
endif()

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(CHEDDAR_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CHEDDAR_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CHEDDAR_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(ENGINE_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/engine)
set(UI_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/ui)

include_directories(${ENGINE_HEADERS_DIR})
include_directories(${UI_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)
