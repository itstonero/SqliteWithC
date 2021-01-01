#include <sqlite3.h>
#include <stdbool.h>

typedef struct
{
    int szTransType;
    int szAccountNumber;
    int szSequenceNumber;
    int szBatchNumber;
    char szPan[19];
    char szHolderName[50];
    char szAmount[12];
    char szOtherAmount[12];
    char szTransmissionDate[10];
    char szShortTime[6];
    char szShortDate[6];
    char szTrace[6];
    char szTransactionDate[10];
    char szRefNumber[12];
    char szResponse[2];
    char szResponseReason[100];
    char szAdditionalData[1000];
    char szOrigForwardID[11];
    char szAuthID[6];
    char szTVR[10];
    char szTSI[4];
    char szCardLabel[20];
    char szExpiryDate[4];
    char szAID[20];
    char szAppCrypto[20];
    bool szStatus;
}TransactionData;

int InitDB(void);

int CloseDB(void);

int ProcessQuery(const char * query, int(*SqlHandler)(sqlite3_stmt * statement, void * payload), void * params);

const char * LastErrorDB();

int InitTransactionTable(void);

int SaveTransaction(TransactionData transaction);

int UpdateTransaction(TransactionData transaction);

int DeleteTransaction(TransactionData * transaction);

int GetOneTransaction(TransactionData * transactions, char * condition);

int GetAllTransactions(TransactionData * transactions, char * condition);

int GetTransactionCount(char * condition);

#define DB_NAME "transactions.db"
#define TRANSACTIONS_TABLE "Transactions"
#define ID "id"
#define TRANSACTION_TYPE_FIELD "transaction_type"
#define	CARD_PAN_FIELD "card_pan"
#define CARD_HOLDER_FIELD "card_holder"
#define AMOUNT_FIELD "amount"
#define OTHER_AMOUNT_FIELD "other_amount"
#define TRANSMISSION_DATE_TIME_FIELD "transmission_date_time"
#define SHORT_TIME_FIELD "short_time"
#define SHORT_DATE_FIELD "short_date"
#define STAN_FIELD "STAN"
#define REFERENCE_NUMBER_FIELD "reference_number"
#define RESPONSE_CODE_FIELD "response_code"
#define RESPONSE_REASON_FIELD "response_reason"
#define ADDITIONAL_DATA_FIELD "additional_payment_data"
#define ORIG_FORWARD_INST_ID_FIELD "original_forwarding_id_code"
#define AUTH_ID_FIELD "auth_id"
#define TVR_FIELD "TVR"
#define TSI_FIELD "TSI"
#define AID_FIELD "AID"
#define CARD_LABEL_FIELD "card_label"
#define APPLICATION_CRYPTOGRAM_FIELD "AC"
#define TRANSACTION_DATE_FIELD "transaction_date"
#define CARD_EXPIRY_FIELD "card_expiry"
#define BATCH_NUMBER_FIELD "batch_number"
#define SEQUENCE_NUMBER_FIELD "sequence_number"
#define ACCOUNT_TYPE_FIELD "account_type"
#define NOTIFICATION_SENT_FIELD "notification_sent"
