#include <stdio.h>
#include <windows.h>
#include "orderapi.h"


/*
   int SKOrderLib_Initialize( [in]const char* lpszUser, [in]const char* lpszPassword)
   int GetUserAccount()
   int RegisterOnAccountCallBack( long lCallBackFunction)
   int SKOrderLib_ReadCertByID([in]char* lpszID)
   int SendFutureOrder( [in]const TCHAR* lpszAccount, [in]const TCHAR* lpszStockNo,
        [in]unsigned short usTradeType, [in]unsigned short usDayTrade, [in]unsigned short usBuySell,
        [in]const TCHAR* lpszPrice, [in]int nQty, [in,out] TCHAR* lpszMessage, [in,out] int*
        pnMessageBufferSize)
 */

//DLL function . use LoadLibrary / GetProcAddress to get function address
static int  __stdcall (*__pointer_SKOrderLib_Initialize)        (char* lpszUser,char* lpszPassword);
#define SKOrderLib_Initialize       (*__pointer_SKOrderLib_Initialize)

static int  __stdcall (*__pointer_GetUserAccount)   (void);
#define SKOrderLib_GetUserAccount   (*__pointer_GetUserAccount)

static int  __stdcall (*__pointer_RegisterOnAccountCallBack)    (long lCallBackFunction);
#define SKOrderLib_RegisterOnAccountCallBack    (*__pointer_RegisterOnAccountCallBack)

static int  __stdcall (*__pointer_SKOrderLib_ReadCertByID)      (char* lpszID);
#define SKOrderLib_ReadCertByID     (*__pointer_SKOrderLib_ReadCertByID)

static int  __stdcall (*__pointer_SendFutureOrder)  (
        char* lpszAccount,char* lpszStockNo
        ,unsigned short int usTradeType,unsigned short int usDayTrade
        ,unsigned short int usBuySell,char* lpszPrice
        ,int nQty,char* lpszMessage
        ,int* pnMessageBufferSize);
#define SKOrderLib_SendFutureOrder  (*__pointer_SendFutureOrder)

////////////////////////////////////////

static HINSTANCE __lib = NULL;

static char __load_ql(void);
static char __load_ql(void) {
    void* __funcp;

    __lib = LoadLibrary("SKOrderLib.dll");
    if(__lib == NULL) return -1;

    __funcp = GetProcAddress(__lib,"SKOrderLib_Initialize");
    if(__funcp == NULL) return -1;
    __pointer_SKOrderLib_Initialize = __funcp;

    __funcp = GetProcAddress(__lib,"GetUserAccount");
    if(__funcp == NULL) return -1;
    __pointer_GetUserAccount = __funcp;

    __funcp = GetProcAddress(__lib,"RegisterOnAccountCallBack");
    if(__funcp == NULL) return -1;
    __pointer_RegisterOnAccountCallBack = __funcp;

    __funcp = GetProcAddress(__lib,"SKOrderLib_ReadCertByID");
    if(__funcp == NULL) return -1;
    __pointer_SKOrderLib_ReadCertByID = __funcp;

    __funcp = GetProcAddress(__lib,"SendFutureOrder");
    if(__funcp == NULL) return -1;
    __pointer_SendFutureOrder = __funcp;

    return 1;
}

static void __free_ql(void);
static void __free_ql(void) {
    if(__lib != NULL) FreeLibrary(__lib);
}

//Void __stdcall OnAccount( BSTR bstrData);
static void __stdcall __account_pull_notify (void* bstrData);
static void __stdcall __account_pull_notify (void* bstrData) {
    printf("Account callback notify.");
    wprintf(L"[%s]\n",(wchar_t*)bstrData);
}

////////////////////////////////////////



//###################################################
char OL_LoginServer(char* username, char* password) {
    if( __load_ql() == -1) return -1;

    printf("SKOrderLib_Initialize() return %d\n"
            ,SKOrderLib_Initialize(username,password) );
    printf("SKOrderLib_RegisterOnAccountCallBack() return %d\n"
            ,SKOrderLib_RegisterOnAccountCallBack((long)__account_pull_notify) );
    printf("SKOrderLib_GetUserAccount() return %d\n"
            ,SKOrderLib_GetUserAccount() );
    printf("SKOrderLib_ReadCertByID() return %d\n"
            ,SKOrderLib_ReadCertByID(username) );
    return 1;
}


void OL_Bye(void) {
    __free_ql();
}



//###################################################

