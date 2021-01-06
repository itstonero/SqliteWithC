#include <appInc.h>

int main()
{
    int nRet = InitDB(DB_NAME) + InitTransactionTable();

    if(nRet == 0)
    {
        TransactionData transaction;
        memset(&transaction, '9', sizeof(TransactionData));
        transaction.szStatus = true;
        
        nRet = UpdateTransaction(transaction);
    }

    return nRet;
}