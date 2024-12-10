#include <pcsclite.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


LONG Copy_WithMemAllocIfNeed(LPVOID srcBuf, DWORD srcBufLen, LPVOID* dstBuf, LPDWORD dstBufLen) {

    if(*dstBuf) {

        if(*dstBufLen < srcBufLen) {
            return SCARD_E_INSUFFICIENT_BUFFER;
        } 
                    
    } else {

        LPVOID buf = malloc(srcBufLen);
        
        if (NULL == buf) {
            return SCARD_E_NO_MEMORY;
        }

        *dstBuf = buf;
    }

    memcpy(*dstBuf, srcBuf, srcBufLen);
    
    *dstBufLen = srcBufLen;
    
    return 0;
}
