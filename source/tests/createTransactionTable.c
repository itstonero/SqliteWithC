#include <appInc.h>

int main()
{
    int nRet = InitDB() + InitTransactionTable();
    
    return nRet;
}