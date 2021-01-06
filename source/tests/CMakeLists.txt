
#################### Transaction Database Suites ####################
set(cDB Create_Database)
add_executable(${cDB} createDatabase.c)
target_link_libraries(${cDB} DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
add_test(NAME "${cDB}"   COMMAND ${cDB} "${cDB}.db")

#################### Transaction Database Table Suites ####################
set(cTable Create_Database_And_Table)
add_executable(${cTable} createTransactionTable.c)
target_link_libraries(${cTable} DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
add_test(NAME "${cTable}"       COMMAND ${cTable}   "${cTable}.db")

#################### Transaction Database Saving Suites ####################
# set(sTrans Saving_Transaction)
# add_executable(${sTrans} saveTransaction.c)
# target_link_libraries(${sTrans} DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
# add_test(NAME "${sTrans}"   COMMAND ${sTrans} "${sTrans}.db"    "000000000000")

# #################### Transaction Database Updating Suites ####################
# set(uTrans Updating_Transaction)
# add_executable(${uTrans} updateTransaction.c)
# target_link_libraries(${uTrans} DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
# add_test(NAME "${uTrans}"   COMMAND ${uTrans} "${sTrans}.db"    "000000000000")

# #################### Transaction Database Deleting Suites ####################
# set(dTrans Deleting_Transaction)
# add_executable(${dTrans} deleteTransaction.c)
# target_link_libraries(${dTrans} DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
# add_test(NAME "${dTrans}"   COMMAND ${dTrans} "${sTrans}.db"    "000000000000")
