#ifndef _OGON_CLIENT_
#define _OGON_CLIENT_

#include "pcsclite.h"

void start_client ();
void stop_client();

extern int rdp_ready;

LONG Ogon_SCardEstablishContext(DWORD dwScope, 
                                LPCVOID pvReserved1, 
                                LPCVOID pvReserved2,
		                        LPSCARDCONTEXT phContext);


#endif