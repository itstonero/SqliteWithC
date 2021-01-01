#include <appInc.h>

int main(void)
{
   if(OK != InitDB())
   {
       printf("%s\n", LastErrorDB());
       return QUIT;
   }

   if(OK != InitTransactionTable())
   {
       printf("%s\n", LastErrorDB());
       return QUIT;
   }

    TransactionData * trans = NULL;
    if(OK != GetAllTransactions(trans, ""))
    {
        printf("%s\n", LastErrorDB());
        return QUIT;
    }

    if(OK != CloseDB())
    {
        printf("%s\n", LastErrorDB());
        return QUIT;
    }
}