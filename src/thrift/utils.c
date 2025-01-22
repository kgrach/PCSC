#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>

#include "utils.h"

LONG Copy_WithMemAllocIfNeed(LPVOID srcBuf, DWORD srcBufLen, LPVOID* dstBuf, LPDWORD dstBufLen) {

    LPVOID buf = NULL;

    if(SCARD_AUTOALLOCATE == *dstBufLen) {

        if(NULL == dstBuf)
            goto end;
        
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

end:

    *dstBufLen = srcBufLen;
    
    return 0;
}

void OgonLog(FILE* f, const char *func, const char *fmt, ...)
{
	va_list args;

	fprintf(f, "[%lX]  %s : ", pthread_self(), func);

	va_start(args, fmt);
	vfprintf(f, fmt, args);
	va_end(args);

	fprintf(f, "\n");
}