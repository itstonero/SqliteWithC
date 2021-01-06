#include <appInc.h>

int main(int argc, char * argv[])
{
    int nRet = InitDB(argv[0]);
    
    if(0 == nRet)
    {
        nRet = InitTransactionTable();
    }
    
    return nRet;
}