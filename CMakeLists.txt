cmake_minimum_required(VERSION 3.0.0)
project(Transactions VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(Threads REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(SOURCE_DIR source)
set(TEST_DIR ${SOURCE_DIR}/tests)
set(HELPER_DIR ${SOURCE_DIR}/helpers)
set(SQLITE_DIR ${SOURCE_DIR}/helpers/sqlite)
set(SERVICE_DIR ${SOURCE_DIR}/services)

include(CPack)
include_directories(${SOURCE_DIR}/include)
include_directories(${SQLITE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_DIR}/index.c)
target_link_libraries(${PROJECT_NAME} DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

add_library(DB ${SERVICE_DIR}/transactions.c ${HELPER_DIR}/dbHelper.c ${SQLITE_DIR}/sqlite3.c)

add_subdirectory(${TEST_DIR})