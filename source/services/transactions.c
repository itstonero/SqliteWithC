#include <appInc.h>
static char query[2000] = { 0 };

static void ParseQueryToTransaction(sqlite3_stmt* processHandler, TransactionData * transaction);

static int SaveTransactionDelegate(sqlite3_stmt * processHandler, void * transaction)
{
    TransactionData * data = (TransactionData*)transaction;

	sqlite3_bind_int(processHandler, 1, data->szTransType);
	sqlite3_bind_int(processHandler, 2, data->szAccountNumber);
	sqlite3_bind_int(processHandler, 3, data->szSequenceNumber);
	sqlite3_bind_int(processHandler, 4, data->szBatchNumber);
	sqlite3_bind_text(processHandler, 5, data->szPan, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 6, data->szHolderName, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 7, data->szAmount, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 8, data->szOtherAmount, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 9, data->szTransmissionDate, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 10, data->szShortTime, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 11, data->szShortTime, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 12, data->szTrace, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 13, data->szRefNumber, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 14, data->szResponse, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 15, data->szResponseReason, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 16, data->szAdditionalData, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 17, data->szOrigForwardID, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 18, data->szAuthID, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 19, data->szTVR, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 20, data->szTSI, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 21, data->szCardLabel, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 22, data->szExpiryDate, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 23, data->szAID, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 24, data->szAppCrypto, -1, SQLITE_STATIC);
	sqlite3_bind_text(processHandler, 25, data->szTransactionDate, -1, SQLITE_STATIC);

    return sqlite3_step(processHandler);
}

static int UpdateTransactionDelegate(sqlite3_stmt * processHandler, void * transaction)
{
     return sqlite3_step(processHandler);
}

static int DeleteTransactionDelegate(sqlite3_stmt * processHandler, void * transaction)
{
 return sqlite3_step(processHandler);
}

static int GetOneTransactionDelegate(sqlite3_stmt * processHandler, void * transaction)
{
    int nRet =  sqlite3_step(processHandler);
 	if (nRet == SQLITE_ROW && sqlite3_column_count(processHandler) > 0) 
    {
        TransactionData * record = (TransactionData*)transaction;
        ParseQueryToTransaction(processHandler, record);
		return OK;
	}
	
    return FAIL;	
}

static int GetAllTransactionDelegate(sqlite3_stmt * processHandler, void * transaction)
{
    int nRet =  sqlite3_step(processHandler);
    if(SQLITE_ROW != nRet)
    {
        return FAIL;
    }
    
    int currentIteration = 0;
    TransactionData * transactions = (TransactionData*)transaction;

 	while(SQLITE_ROW == nRet) 
    {
        ParseQueryToTransaction(processHandler, (transactions + currentIteration));
        currentIteration += 1;
        nRet =  sqlite3_step(processHandler);
	}

    return OK;	
}

static const char * PrepareSaveTransactionQuery(TransactionData transaction)
{
    memset(query, 0, sizeof(query));
    sprintf(query, "INSERT INTO %s ( %s, %s, %s, %s, %s, %s, %s,"
            "%s, %s, %s, %s, %s,"
            "%s, %s, %s,%s, %s,"
            "%s, %s, %s, %s, %s, %s, %s, %s) VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10"
            ",?11,?12,?13,?14,?15,?16, ?17, ?18, ?19, ?20, ?21, ?22, ?23, ?24, ?25);",
            TRANSACTIONS_TABLE,
            TRANSACTION_TYPE_FIELD,ACCOUNT_TYPE_FIELD, SEQUENCE_NUMBER_FIELD, BATCH_NUMBER_FIELD,CARD_PAN_FIELD, CARD_HOLDER_FIELD,
            AMOUNT_FIELD, OTHER_AMOUNT_FIELD, TRANSMISSION_DATE_TIME_FIELD,
            SHORT_TIME_FIELD,SHORT_DATE_FIELD,STAN_FIELD,REFERENCE_NUMBER_FIELD,RESPONSE_CODE_FIELD,
            RESPONSE_REASON_FIELD,ADDITIONAL_DATA_FIELD,ORIG_FORWARD_INST_ID_FIELD,AUTH_ID_FIELD,TVR_FIELD,TSI_FIELD,
            CARD_LABEL_FIELD, CARD_EXPIRY_FIELD, AID_FIELD, APPLICATION_CRYPTOGRAM_FIELD,TRANSACTION_DATE_FIELD    
            );

    return query;
}

static const char * PrepareUpdateTransactionQuery(TransactionData transaction)
{
    memset(query, 0, sizeof(query));
	sprintf(query, "UPDATE %s SET %s = %i WHERE %s = '%s';", TRANSACTIONS_TABLE, NOTIFICATION_SENT_FIELD, 
    (int)transaction.szStatus, REFERENCE_NUMBER_FIELD, transaction.szRefNumber);
	
    return query;
}

static const char * PrepareDeleteTransactionQuery(TransactionData * transaction)
{
	memset(query, 0, sizeof(query));

	if (transaction) 
    {
		sprintf(query, "DELETE FROM %s WHERE %s = '%s';", TRANSACTIONS_TABLE, REFERENCE_NUMBER_FIELD, transaction->szRefNumber);
	}else 
    {
		sprintf(query, "DELETE FROM %s;", TRANSACTIONS_TABLE);
	}
    return query;
}

static const char * PrepareGetOneTransactionQuery(char * condition)
{
    memset(query, 0, sizeof(query));
    sprintf(query, "SELECT * FROM %s %s DESC LIMIT 1;", TRANSACTIONS_TABLE, condition);
    return query;
}

static const char * PrepareGetAllTransactionQuery(char * condition)
{
    memset(query, 0, sizeof(query));
    sprintf(query, "SELECT * FROM %s %s;", TRANSACTIONS_TABLE, condition);
    return query;
}

int SaveTransaction(TransactionData transaction)
{
    return ProcessQuery(PrepareSaveTransactionQuery(transaction), SaveTransactionDelegate, (void*)&transaction);
}

int UpdateTransaction(TransactionData transaction)
{
    return ProcessQuery(PrepareUpdateTransactionQuery(transaction), UpdateTransactionDelegate, (void*)&transaction);
}

int DeleteTransaction(TransactionData * transaction)
{
    return ProcessQuery(PrepareDeleteTransactionQuery(transaction), DeleteTransactionDelegate, (void*)transaction);
}

int GetOneTransaction(TransactionData * transactions, char * condition)
{
    return ProcessQuery(PrepareGetOneTransactionQuery(condition), GetOneTransactionDelegate, (void*)transactions);
}

int GetAllTransactions(TransactionData * transaction, char * condition)
{
    int totalRecords = GetTransactionCount(condition);
    if(totalRecords == 0) return FAIL;
    
    TransactionData * transactions = (TransactionData*)calloc(totalRecords, sizeof(TransactionData));
    int nRet =  ProcessQuery(PrepareGetAllTransactionQuery(condition), GetAllTransactionDelegate, (void *)transactions);

    transaction = transactions;
    return nRet;
}

void RetrieveString(char * target, char * source)
{
    strcpy(target, source);
}

static void ParseQueryToTransaction(sqlite3_stmt * processHandler, TransactionData * record)
{
	memset(record, 0, sizeof(TransactionData));

	int i, totalColumns = sqlite3_column_count(processHandler);
    
	for (i = 0; i < totalColumns ; i++) 
    {
		switch (i) 
        {
            case 1:
                record->szTransType = sqlite3_column_int(processHandler, i);
                break;
            case 2:
                record->szAccountNumber = sqlite3_column_int(processHandler, i);
                break;
            case 3:
                record->szSequenceNumber = sqlite3_column_int(processHandler, i);
                break;
            case 4:
                record->szBatchNumber = sqlite3_column_int(processHandler, i);
                break;
            case 5:
                RetrieveString(record->szPan, (char *)sqlite3_column_text(processHandler, i));
                break;
            case 6:
                RetrieveString(record->szHolderName, (char *)sqlite3_column_text(processHandler, i));
                break;
            case 7:
                RetrieveString(record->szAmount, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 8:
                RetrieveString(record->szOtherAmount, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 9:
                RetrieveString(record->szTransmissionDate, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 10:
                RetrieveString(record->szShortTime, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 11:
                RetrieveString(record->szShortDate, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 12:
                RetrieveString(record->szTrace, (char *)sqlite3_column_text(processHandler, i));                    
                break;
            case 13:
                RetrieveString(record->szTransactionDate, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 14:
                RetrieveString(record->szRefNumber, (char *)sqlite3_column_text(processHandler, i));                    
                break;
            case 15:
                RetrieveString(record->szResponse, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 16:
                RetrieveString(record->szResponseReason, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 17: 
                RetrieveString(record->szAdditionalData, (char *)sqlite3_column_text(processHandler, i));                    
                break;
            case 18:
                RetrieveString(record->szOrigForwardID, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 19:
                RetrieveString(record->szAuthID, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 20:
                RetrieveString(record->szTVR, (char *)sqlite3_column_text(processHandler, i));                    
                break;
            case 21:
                RetrieveString(record->szTSI, (char *)sqlite3_column_text(processHandler, i));                    
                break;
            case 22:
                RetrieveString(record->szCardLabel, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 23:
                RetrieveString(record->szExpiryDate, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 24:
                RetrieveString(record->szAID, (char *)sqlite3_column_text(processHandler, i));                    
                break;
            case 25:
                RetrieveString(record->szAppCrypto, (char *)sqlite3_column_text(processHandler, i));					
                break;
            case 26:
                record->szStatus = (bool)sqlite3_column_int(processHandler, i);
                break;
		}

	}
}