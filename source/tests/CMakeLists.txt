
add_executable(cDB createDatabase.c)
# add_executable(sTrans saveTransaction.c)
# add_executable(uTrans updateTransaction.c)
# add_executable(dTrans deleteTransaction.c)
add_executable(cTable createTransactionTable.c)


target_link_libraries(cDB DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
target_link_libraries(cTable DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
# target_link_libraries(dTrans DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
# target_link_libraries(uTrans DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
# target_link_libraries(sTrans DB ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})


add_test(NAME Create_Database_With_Right_Named_DB COMMAND cDB "good_name.db")
add_test(NAME Create_Database_With_No_Extension COMMAND cDB "no_extension")
add_test(NAME Create_Database_With_Default_DB COMMAND cDB)

# add_test(NAME Create_Database_And_Table_With_Right_Name_DB COMMAND cTable "good_name_2.db")
# add_test(NAME Create_Database_And_Table_With_Wrong_Extension_DB COMMAND cTable "wrong_extension.jpg")
# add_test(NAME Create_Database_And_Table_With_Default_DB COMMAND cTable)

# add_test(NAME SaveTransaction COMMAND sTrans)
# add_test(NAME DeleteTransaction COMMAND dTrans)
# add_test(NAME UpdateTransaction COMMAND uTrans)