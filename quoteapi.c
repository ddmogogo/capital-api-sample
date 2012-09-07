#include <windows.h>
#include "quoteapi.h"

//DLL function . use LoadLibrary / GetProcAddress to get function address
static int  (*__pointer_SKQuoteLib_GetVersion)     (char* lpszVersion,int* pnSize);
static int  (*__pointer_SKQuoteLib_Initialize)     (char* lpszLoginID,char* lpszPassword);
static int  (*__pointer_SKQuoteLib_EnterMonitor)   (void);
static int  (*__pointer_SKQuoteLib_LeaveMonitor)   (void);
static int  (*__pointer_SKQuoteLib_RequestStocks)  (short* psPageNo,char* pStockNos);

#define SKQuoteLib_GetVersion       (*__pointer_SKQuoteLib_GetVersion)
#define SKQuoteLib_Initialize       (*__pointer_SKQuoteLib_Initialize)
#define SKQuoteLib_EnterMonitor     (*__pointer_SKQuoteLib_EnterMonitor)
#define SKQuoteLib_LeaveMonitor     (*__pointer_SKQuoteLib_LeaveMonitor)
#define SKQuoteLib_RequestStocks    (*__pointer_SKQuoteLib_RequestStocks)

////////////////////////////////////////

static HINSTANCE __lib = NULL;

static char __load_ql(void);
static char __load_ql(void) {
    void* __funcp;

    __lib = LoadLibrary("SKQuoteLib.dll");
    if(__lib == NULL) return -1;


    __funcp = GetProcAddress(__lib,"SKQuoteLib_Initialize");
    if(__funcp == NULL) return -1; 

    __pointer_SKQuoteLib_Initialize = __funcp;

    return 1;
}

static void __free_ql(void);
static void __free_ql(void) {
    if(__lib != NULL) FreeLibrary(__lib);
}
////////////////////////////////////////



//###################################################
char QL_LoginServer(char* username, char* password) {

}
void QL_Bye(void) {

}
//###################################################

