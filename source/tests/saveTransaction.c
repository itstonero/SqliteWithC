#include <appInc.h>

int main(int argc, char * argv[])
{
    if(argc <= 3) return argc;

    int nRet = InitDB(argv[1]);
    if(nRet == 0)
    {
        nRet = InitTransactionTable();
    }

    if(nRet == 0)
    {
        TransactionData transaction;
        memset(&transaction, 0, sizeof(TransactionData));
        transaction.szStatus = false;
        strcpy(transaction.szRefNumber, argv[2]);
        
        nRet = SaveTransaction(transaction);
    }

    return nRet;
}