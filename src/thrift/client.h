#ifndef _OGON_CLIENT_
#define _OGON_CLIENT_

#include "pcsclite.h"


extern int rdp_ready;

LONG Ogon_SCardEstablishContext(DWORD dwScope, 
                                LPCVOID pvReserved1, 
                                LPCVOID pvReserved2,
		                        LPSCARDCONTEXT phContext);                             

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

LONG Ogon_SCardReleaseContext(SCARDCONTEXT hContext); 

LONG Ogon_SCardDisconnect(SCARDHANDLE hCard, DWORD dwDisposition);

void Ogon_SCardFreeMemory(SCARDCONTEXT hContext, LPCVOID pvMem);



#endif