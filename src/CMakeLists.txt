cmake_minimum_required(VERSION 3.9.2)
project(CheddarApp)

add_subdirectory(engine)

set(HEADERS
    core.h
)

set(SOURCE
    main.cpp
)

add_executable(cheddar ${SOURCE})

target_link_libraries(cheddar engine)

install(FILES ${HEADERS} DESTINATION ${CHEDDAR_INSTALL_INCLUDE_DIR})
install(TARGETS cheddar DESTINATION ${CHEDDAR_INSTALL_BIN_DIR})
