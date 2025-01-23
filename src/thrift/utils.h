#ifndef _UTILS_
#define _UTILS_

#include <pcsclite.h>
#include <stdio.h>

LONG Copy_WithMemAllocIfNeed(LPVOID srcBuf, DWORD srcBufLen, LPVOID* dstBuf, LPDWORD dstBufLen);

struct ThriftClientData {
    ThriftSocket     *socket;
    ThriftTransport  *transport;
    ThriftProtocol   *protocol;
    ogonIf           *client;
    long             tid;
    GError           *error;
};

char* Dump2Str(char* in_buf, unsigned long in_buf_len);

void OgonLog(FILE* f, const char *func, const char *fmt, ...);

#endif