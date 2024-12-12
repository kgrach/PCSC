#ifndef _OGON_CLIENT_
#define _OGON_CLIENT_

#include "pcsclite.h"


extern int rdp_ready;

LONG Ogon_SCardEstablishContext(DWORD dwScope, 
                                LPCVOID pvReserved1, 
                                LPCVOID pvReserved2,
		                        LPSCARDCONTEXT phContext);  

LONG Ogon_SCardReleaseContext(SCARDCONTEXT hContext);                                                            

LONG Ogon_SCardListReaders(SCARDCONTEXT hContext, 
                           LPCSTR mszGroups,
	                       LPSTR mszReaders, 
                           LPDWORD pcchReaders); 
                           
LONG Ogon_SCardConnect(SCARDCONTEXT hContext, 
                       LPCSTR szReader,
	                   DWORD dwShareMode, 
                       DWORD dwPreferredProtocols, 
                       LPSCARDHANDLE phCard,
                       LPDWORD pdwActiveProtocol);

LONG Ogon_SCardReconnect(SCARDHANDLE hCard, 
                         DWORD dwShareMode,
	                     DWORD dwPreferredProtocols, 
                         DWORD dwInitialization,
                         LPDWORD pdwActiveProtocol);

LONG Ogon_SCardDisconnect(SCARDHANDLE hCard, DWORD dwDisposition);

LONG Ogon_SCardStatus(SCARDHANDLE hCard, 
                      LPSTR szReaderName, 
                      LPDWORD pcchReaderLen, 
                      LPDWORD pdwState, 
                      LPDWORD pdwProtocol, 
                      LPBYTE pbAtr, 
                      LPDWORD pcbAtrLen);    

LONG Ogon_SCardTransmit(SCARDHANDLE hCard, 
                        const SCARD_IO_REQUEST *pioSendPci,
	                    LPCBYTE pbSendBuffer, 
                        DWORD cbSendLength,
	                    SCARD_IO_REQUEST *pioRecvPci, 
                        LPBYTE pbRecvBuffer,
	                    LPDWORD pcbRecvLength);

LONG Ogon_SCardGetStatusChange(SCARDCONTEXT hContext, 
                               DWORD dwTimeout,	
                               SCARD_READERSTATE *rgReaderStates, 
                               DWORD cReaders);

LONG Ogon_SCardBeginTransaction(SCARDHANDLE hCard);

LONG Ogon_SCardEndTransaction(SCARDHANDLE hCard, DWORD dwDisposition);

LONG Ogon_SCardGetAttrib(SCARDHANDLE hCard, DWORD dwAttrId, LPBYTE pbAttr, LPDWORD pcbAttrLen);

LONG Ogon_SCardControl(SCARDHANDLE hCard, 
                       DWORD dwControlCode, 
                       LPCVOID pbSendBuffer,
                       DWORD cbSendLength, 
                       LPVOID pbRecvBuffer, 
                       DWORD cbRecvLength,
                       LPDWORD lpBytesReturned);

LONG Ogon_SCardCancel(SCARDCONTEXT hContext);

LONG Ogon_SCardIsValidContext(SCARDCONTEXT hContext);

void Ogon_SCardFreeMemory(SCARDCONTEXT hContext, LPCVOID pvMem);

#endif