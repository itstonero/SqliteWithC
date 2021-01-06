#include <appInc.h>

int main()
{
    int nRet = InitDB(DB_NAME) + InitTransactionTable();

    if(nRet == 0)
    {
        TransactionData transaction;
        memset(&transaction, '1', sizeof(TransactionData));
        transaction.szStatus = true;
        
        nRet = SaveTransaction(transaction);
    }

    return nRet;
}