cmake_minimum_required(VERSION 3.31)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

file(GLOB SOURCES
        "*.cpp"
        "*.h"
)

add_executable(Project1 ${SOURCES})
target_link_libraries(Project1 PRIVATE Ws2_32)
target_link_libraries(Project1 PRIVATE sqlite3)
find_package(SQLite3 REQUIRED)

target_link_libraries(Project1 PRIVATE SQLite::SQLite3)

