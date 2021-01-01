#include <appInc.h>

static sqlite3 * dbHandler = 0;

int InitDB(void)
{
    return sqlite3_open(DB_NAME, &dbHandler);
}

int CloseDB(void)
{
    if(dbHandler)
    {
        return sqlite3_close(dbHandler);
    }
    return -1;
}

static const char * PrepareInitTransactionTable(void)
{
    return "CREATE TABLE IF NOT EXISTS " TRANSACTIONS_TABLE
    " (" ID " INTEGER PRIMARY KEY AUTOINCREMENT, " TRANSACTION_TYPE_FIELD " INTEGER(2), "
    ACCOUNT_TYPE_FIELD " INTEGER(1), " SEQUENCE_NUMBER_FIELD " INTEGER, " BATCH_NUMBER_FIELD " INTEGER, " CARD_PAN_FIELD " VARCHAR(19), "
    CARD_HOLDER_FIELD " VARCHAR(50), " AMOUNT_FIELD "  VARCHAR(12), " OTHER_AMOUNT_FIELD " VARCHAR(12), "
    TRANSMISSION_DATE_TIME_FIELD " VARCHAR(10), "
    SHORT_TIME_FIELD " VARCHAR(6), " SHORT_DATE_FIELD " VARCHAR(6), " STAN_FIELD " VARCHAR(6), "
    TRANSACTION_DATE_FIELD " VARCHAR(10), "
    REFERENCE_NUMBER_FIELD " VARCHAR(12) NOT NULL, " RESPONSE_CODE_FIELD " VARCHAR(2), "
    RESPONSE_REASON_FIELD " VARCHAR(100), " ADDITIONAL_DATA_FIELD " VARCHAR(1000), "
    ORIG_FORWARD_INST_ID_FIELD  " VARCHAR(11), " AUTH_ID_FIELD " VARCHAR(6), " TVR_FIELD " VARCHAR(10), " 
    TSI_FIELD " VARCHAR(4), " CARD_LABEL_FIELD " VARCHAR(20), " CARD_EXPIRY_FIELD " VARCHAR(4),"
    AID_FIELD  " VARCHAR(20), " APPLICATION_CRYPTOGRAM_FIELD " VARCHAR(20), " NOTIFICATION_SENT_FIELD " INTEGER DEFAULT 0,"
    "UNIQUE(" REFERENCE_NUMBER_FIELD ") ON CONFLICT REPLACE );";
}

int InitTransactionTable(void)
{
    sqlite3_stmt * statement = 0;

    int nRet = sqlite3_prepare_v2(dbHandler, PrepareInitTransactionTable(), -1, &statement, 0);
    
    if(SQLITE_OK == nRet)
    {
        sqlite3_step(statement);
    }

    if(statement)
    {
        sqlite3_finalize(statement);
    }

    return nRet;
}

int ProcessQuery(const char * query, int(*SqlHandler)(sqlite3_stmt * statement, void * payload), void * params)
{
    sqlite3_stmt * statement = 0;
    int nRet = sqlite3_prepare_v2(dbHandler, query, -1, &statement, 0);
    
    if(SQLITE_OK == nRet)
    {
        nRet = SqlHandler(statement, params);
    }

    if(statement)
    {
        sqlite3_finalize(statement);
    }

    return (SQLITE_ROW == nRet || SQLITE_DONE == nRet || SQLITE_OK == nRet) ? OK : FAIL;
}

int GetTransactionCount(char * condition)
{
    sqlite3_stmt * statement = 0;
    char query[200] = { 0 };
    sprintf(query, "SELECT count(*) FROM %s %s ;", TRANSACTIONS_TABLE, condition);


    int nRet = sqlite3_prepare_v2(dbHandler, query, -1, &statement, 0);
    int totalRows = 0;

	if (SQLITE_ROW == sqlite3_step(statement) && sqlite3_column_count(statement) > 0) 
    {
		totalRows = sqlite3_column_int(statement, 0);
	}

    if(statement)
    {
        sqlite3_finalize(statement);
    }

    return totalRows;
}

const char * LastErrorDB()
{
    if(dbHandler)
    {
        return sqlite3_errmsg(dbHandler);
    }
    return NULL;
}