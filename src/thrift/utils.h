#ifndef _UTILS_
#define _UTILS_

#include "pcsclite.h"

LONG Copy_WithMemAllocIfNeed(LPVOID srcBuf, DWORD srcBufLen, LPVOID* dstBuf, LPDWORD dstBufLen);

struct ThriftClientData {
    ThriftSocket     *socket;
    ThriftTransport  *transport;
    ThriftProtocol   *protocol;
    ogonIf           *client;
    long             tid;
    GError           *error;
};

#endif