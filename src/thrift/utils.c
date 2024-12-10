#include <pcsclite.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


LONG Copy_WithMemAllocIfNeed(LPVOID srcBuf, DWORD srcBufLen, LPVOID* dstBuf, LPDWORD dstBufLen) {

    LPVOID buf = NULL;

    if(SCARD_AUTOALLOCATE == *dstBufLen) {

        buf = malloc(srcBufLen);
        
        if (NULL == buf) {
            return SCARD_E_NO_MEMORY;
        }

        *dstBuf = buf;
    } else {

        if(*dstBufLen < srcBufLen) {
            return SCARD_E_INSUFFICIENT_BUFFER;
        }   

        buf = dstBuf;     
    }

    memcpy(buf, srcBuf, srcBufLen);
    
    *dstBufLen = srcBufLen;
    
    return 0;
}
