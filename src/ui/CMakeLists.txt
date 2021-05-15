cmake_minimum_required(VERSION 3.9.2)
project(CheddarUI)

set(HEADERS
    ui.h
)

set(SOURCE
    ui.cpp
)

add_library(ui SHARED STATIC ${SOURCE})

target_link_libraries(ui engine)

install(TARGETS ui DESTINATION ${CHEDDAR_INSTALL_LIB_DIR})

install(FILES ${HEADERS} DESTINATION ${CHEDDAR_INSTALL_INCLUDE_DIR})
