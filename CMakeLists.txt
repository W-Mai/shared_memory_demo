cmake_minimum_required(VERSION 3.10)
project(shared_mem_demo C)

set(CMAKE_C_STANDARD 11)

add_executable(shared_server shared_server.c)
add_executable(shared_client shared_client.c)

add_custom_target(test
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test.sh ${CMAKE_CURRENT_BINARY_DIR}/test.sh
        COMMAND . ./test.sh
        DEPENDS shared_server shared_client
        VERBATIM
)
