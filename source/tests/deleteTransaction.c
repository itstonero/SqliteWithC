#include <appInc.h>

int main()
{
    int nRet = InitDB() + InitTransactionTable();

    if(nRet == 0)
    {
        TransactionData transaction;
        memset(&transaction, '1', sizeof(TransactionData));
        
        nRet = DeleteTransaction(&transaction);
    }

    return nRet;
}