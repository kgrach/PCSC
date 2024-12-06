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

#endif