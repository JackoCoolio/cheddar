cmake_minimum_required(VERSION 3.9.2)
project(CheddarApp)

add_subdirectory(engine)
set(SOURCE
    main.cpp
)

add_executable(cheddar ${SOURCE})

target_link_libraries(cheddar engine)

install(TARGETS cheddar DESTINATION ${CHEDDAR_INSTALL_BIN_DIR})
