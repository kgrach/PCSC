#ifndef _UTILS_
#define _UTILS_

#include <pcsclite.h>
#include <stdio.h>

LONG Copy_WithMemAllocIfNeed(LPVOID srcBuf, DWORD srcBufLen, LPVOID* dstBuf, LPDWORD dstBufLen);
void OgonLog(FILE* f, const char *func, const char *fmt, ...);
#endif