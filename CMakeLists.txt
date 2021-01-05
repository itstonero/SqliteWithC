cmake_minimum_required(VERSION 3.0.0)
project(Transactions VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(Threads REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(SOURCE_DIR source)

include(CPack)
include_directories(${SOURCE_DIR}/include)
include_directories(${SOURCE_DIR}/helpers/sqlite)

add_executable(${PROJECT_NAME} ${SOURCE_DIR}/index.c)
target_link_libraries(${PROJECT_NAME} DB ${CMAKE_THREAD_LIBS_INIT} dl)

add_library(DB ${SOURCE_DIR}/services/transactions.c 
${SOURCE_DIR}/helpers/dbHelper.c ${SOURCE_DIR}/helpers/sqlite/sqlite3.c ${SOURCE_DIR}/helpers/sqlite/sqlite3.h)

