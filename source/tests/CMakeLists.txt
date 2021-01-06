
#################### Transaction Database Suites ####################
set(cDB Create_Database)
add_executable(${cDB} createDatabase.c)
target_link_libraries(${cDB} DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
add_test(NAME "${cDB}_With_Right_Name"   COMMAND ${cDB} "${cDB}.db")
add_test(NAME "${cDB}_With_No_Extension" COMMAND ${cDB} "${cDB}")

#################### Transaction Database Table Suites ####################
set(cTable Create_Database_And_Table)
add_executable(${cTable} createTransactionTable.c)
target_link_libraries(${cTable} DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
add_test(NAME "${cTable}_With_Right_Name"       COMMAND ${cTable}   "${cTable}.db")
add_test(NAME "${cTable}_With_No_Extension"     COMMAND ${cTable}   "${cTable}")  

#################### Transaction Database Saving Suites ####################
# set(sTrans Create_Database_And_Table_Saving_Transaction)
# add_executable(${sTrans} saveTransaction.c)
# target_link_libraries(${sTrans} DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
# add_test(NAME "${sTrans}_With_Right_Name"   COMMAND ${sTrans} "${sTrans}.db"    "000000000000")
# add_test(NAME "${sTrans}_With_No_Extension" COMMAND ${sTrans} "${sTrans}"       "000000000001")


# add_executable(uTrans updateTransaction.c)
# add_executable(dTrans deleteTransaction.c)

# target_link_libraries(dTrans DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
# target_link_libraries(uTrans DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})


# add_test(NAME DeleteTransaction COMMAND dTrans)
# add_test(NAME UpdateTransaction COMMAND uTrans)