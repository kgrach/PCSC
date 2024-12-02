#ifndef _OGON_CLIENT_
#define _OGON_CLIENT_

#include "pcsclite.h"

int start_client ();
void stop_client();

LONG Ogon_SCardEstablishContext(DWORD dwScope, 
                                LPCVOID pvReserved1, 
                                LPCVOID pvReserved2,
		                        LPSCARDCONTEXT phContext);


#endif