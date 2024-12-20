#ifndef _OGON_CLIENT_
#define _OGON_CLIENT_

#include "pcsclite.h"


extern int rdp_ready;

LONG Ogon_SCardEstablishContext(void* client, DWORD dwScope, 
                                LPCVOID pvReserved1, 
                                LPCVOID pvReserved2,
		                        LPSCARDCONTEXT phContext);  

LONG Ogon_SCardReleaseContext(void* client, SCARDCONTEXT hContext);                                                            

LONG Ogon_SCardListReaders(void* client,SCARDCONTEXT hContext, 
                           LPCSTR mszGroups,
	                       LPSTR mszReaders, 
                           LPDWORD pcchReaders); 

LONG Ogon_SCardListReaderGroups(void* client,SCARDCONTEXT hContext, 
                                LPSTR mszGroups, 
                                LPDWORD pcchGroups);
                           
LONG Ogon_SCardConnect(void* client,SCARDCONTEXT hContext, 
                       LPCSTR szReader,
	                   DWORD dwShareMode, 
                       DWORD dwPreferredProtocols, 
                       LPSCARDHANDLE phCard,
                       LPDWORD pdwActiveProtocol);

LONG Ogon_SCardReconnect(void* client,SCARDHANDLE hCard, 
                         DWORD dwShareMode,
	                     DWORD dwPreferredProtocols, 
                         DWORD dwInitialization,
                         LPDWORD pdwActiveProtocol);

LONG Ogon_SCardDisconnect(void* client,SCARDHANDLE hCard, DWORD dwDisposition);

LONG Ogon_SCardStatus(void* client,SCARDHANDLE hCard, 
                      LPSTR szReaderName, 
                      LPDWORD pcchReaderLen, 
                      LPDWORD pdwState, 
                      LPDWORD pdwProtocol, 
                      LPBYTE pbAtr, 
                      LPDWORD pcbAtrLen);    

LONG Ogon_SCardTransmit(void* client,SCARDHANDLE hCard, 
                        const SCARD_IO_REQUEST *pioSendPci,
	                    LPCBYTE pbSendBuffer, 
                        DWORD cbSendLength,
	                    SCARD_IO_REQUEST *pioRecvPci, 
                        LPBYTE pbRecvBuffer,
	                    LPDWORD pcbRecvLength);

LONG Ogon_SCardGetStatusChange(void* client,SCARDCONTEXT hContext, 
                               DWORD dwTimeout,	
                               SCARD_READERSTATE *rgReaderStates, 
                               DWORD cReaders);

LONG Ogon_SCardBeginTransaction(void* client,SCARDHANDLE hCard);

LONG Ogon_SCardEndTransaction(void* client,SCARDHANDLE hCard, DWORD dwDisposition);

LONG Ogon_SCardGetAttrib(void* client,SCARDHANDLE hCard, DWORD dwAttrId, LPBYTE pbAttr, LPDWORD pcbAttrLen);

LONG Ogon_SCardControl(void* client,SCARDHANDLE hCard, 
                       DWORD dwControlCode, 
                       LPCVOID pbSendBuffer,
                       DWORD cbSendLength, 
                       LPVOID pbRecvBuffer, 
                       DWORD cbRecvLength,
                       LPDWORD lpBytesReturned);

LONG Ogon_SCardCancel(void* client,SCARDCONTEXT hContext);

LONG Ogon_SCardIsValidContext(void* client,SCARDCONTEXT hContext);

void Ogon_SCardFreeMemory(void* client,SCARDCONTEXT hContext, LPCVOID pvMem);

#endif