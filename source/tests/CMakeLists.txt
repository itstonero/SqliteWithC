add_executable(cDB createDatabase.c)
target_link_libraries(cDB DB ${CMAKE_THREAD_LIBS_INIT} dl)
add_test(NAME CreateDatabase COMMAND cDB)

add_executable(cTable createTransactionTable.c)
target_link_libraries(cTable DB ${CMAKE_THREAD_LIBS_INIT} dl)
add_test(NAME CreateTable COMMAND cTable)

add_executable(sTrans saveTransaction.c)
target_link_libraries(sTrans DB ${CMAKE_THREAD_LIBS_INIT} dl)
add_test(NAME SaveTransaction COMMAND sTrans)

add_executable(uTrans updateTransaction.c)
target_link_libraries(uTrans DB ${CMAKE_THREAD_LIBS_INIT} dl)
add_test(NAME Update COMMAND uTrans)

add_executable(dTrans deleteTransaction.c)
target_link_libraries(dTrans DB ${CMAKE_THREAD_LIBS_INIT} dl)
add_test(NAME DeleteTransaction COMMAND dTrans)
