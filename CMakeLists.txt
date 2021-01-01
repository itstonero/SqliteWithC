cmake_minimum_required(VERSION 3.0.0)
project(Transactions VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(SOURCE_DIR source)

# SET(GCC_COVERAGE_LINK_FLAGS    "-lpthread")
# SET(GCC_COVERAGE_LINK_FLAGS    "-ldl")

include(CPack)
include_directories(${SOURCE_DIR}/include)
include_directories(${SOURCE_DIR}/helpers/sqlite)

add_executable(${PROJECT_NAME} ${SOURCE_DIR}/index.c)
target_link_libraries(${PROJECT_NAME} DB)

add_library(DB ${SOURCE_DIR}/services/transactions.c 
${SOURCE_DIR}/helpers/dbHelper.c ${SOURCE_DIR}/helpers/sqlite/sqlite3.c)