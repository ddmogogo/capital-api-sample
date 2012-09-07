#ifndef __QUOTE_LIBRARY__
#define __QUOTE_LIBRARY__

typedef struct STOCK
{
    short m_sStockidx; 
    short m_sDecimal; 
    short m_sTypeNo; 
    char m_cMarketNo;
    char m_caStockNo[20]; 
    char m_caName[10]; 
    int m_nOpen; 
    int m_nHigh; 
    int m_nLow; 
    int m_nClose; 
    int m_nTickQty; 
    int m_nRef; 
    int m_nBid; 
    int m_nBc;
    int m_nAsk; 
    int m_nAc; 
    int m_nTBc; 
    int m_nTAc; 
    int m_nFutureOI; 
    int m_nTQty; 
    int m_nYQty; 
    int m_nUp; 
    int m_nDown;
} TStock;

typedef struct TICK
{
    int m_nPtr;
    int m_nTime; 
    int m_nBid; 
    int m_nAsk; 
    int m_nClose; 
    int m_nQty; 
} TTick;


extern char QL_LoginServer(char* username, char* password);
extern void QL_Bye(void);


#endif

