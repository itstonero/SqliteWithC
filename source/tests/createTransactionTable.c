#include <appInc.h>

int main(int argc, char * argv[])
{
    if(argc <= 1) return -1;
    
    int nRet = InitDB(argv[1]);
    
    if(0 == nRet)
    {
        nRet = InitTransactionTable();
    }
    
    return nRet;
}