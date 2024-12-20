#include <pcsclite.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>

#include <thrift/c_glib/transport/thrift_transport.h>
#include <thrift/c_glib/transport/thrift_socket.h>
#include <thrift/c_glib/transport/thrift_buffered_transport.h>
#include <thrift/c_glib/protocol/thrift_binary_protocol.h>

#include "gen-c_glib/ogon.h"

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

static pthread_mutex_t clientMutex = PTHREAD_MUTEX_INITIALIZER;
static GPtrArray *thriftClients = NULL;

struct ThriftClientData {
    ThriftSocket     *socket;
    ThriftTransport  *transport;
    ThriftProtocol   *protocol;
    ogonIf           *client;
    long             tid;
};

void* GetThriftClient() {

    pthread_mutex_lock(&clientMutex);

    ogonIf *client = NULL;

    if(NULL == thriftClients)
        thriftClients = g_ptr_array_new();

    long tid =  gettid();

    for(int i = 0; i < thriftClients->len; i++) {

        struct ThriftClientData *cli = g_ptr_array_index(thriftClients, i);

        if(tid == cli->tid) {
            client = cli->client;
            goto end;
        }
    }

    gboolean success = FALSE;

    ThriftSocket     *socket;
    ThriftTransport  *transport;
    ThriftProtocol   *protocol;
    GError           *error;

#if (!GLIB_CHECK_VERSION (2, 36, 0))
  g_type_init ();
#endif

  socket    = g_object_new (THRIFT_TYPE_SOCKET,
                            "hostname",  "192.168.101.177",
                            "port",      9091,
                            NULL);
  transport = g_object_new (THRIFT_TYPE_BUFFERED_TRANSPORT,
                            "transport", socket,
                            NULL);
  protocol  = g_object_new (THRIFT_TYPE_BINARY_PROTOCOL,
                            "transport", transport,
                            NULL);

  client = g_object_new (TYPE_OGON_CLIENT,
                         "input_protocol",  protocol,
                         "output_protocol", protocol,
                         NULL);

  success = thrift_transport_open(transport, &error);

  if(success) {

    struct ThriftClientData *cli = malloc(sizeof(struct ThriftClientData));

    cli->socket = socket;
    cli->transport = transport;
    cli->protocol = protocol;
    cli->client = client;
    //cli->error = error;
    cli->tid = tid;

    g_ptr_array_add(thriftClients, cli);
  }
  else {
    client = NULL;
  }


end:
  pthread_mutex_unlock(&clientMutex);

  return client;
}
 
