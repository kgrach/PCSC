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

static pthread_mutex_t clientMutex = PTHREAD_MUTEX_INITIALIZER,
                       logMutex = PTHREAD_MUTEX_INITIALIZER;

static GPtrArray *thriftClients = NULL;

void CleanClientData(void* clientData) {
    
  struct ThriftClientData *cli = clientData;

  thrift_transport_close (cli->transport, &cli->error);

  g_clear_error (&cli->error);
  
  g_object_unref (cli->client);
  
  g_object_unref (cli->protocol);
  
  g_object_unref (cli->transport);
  
  g_object_unref (cli->socket);
}


void* GetThriftClient() {

    //return NULL;

    pthread_mutex_lock(&clientMutex);

    struct ThriftClientData *clientData = NULL;

    if(NULL == thriftClients)
        thriftClients = g_ptr_array_new();

    long tid =  gettid();

    for(int i = 0; i < thriftClients->len; i++) {

        struct ThriftClientData *cli = g_ptr_array_index(thriftClients, i);

        if(tid == cli->tid) {
            clientData = cli;
            goto end;
        }
    }

    gboolean success = FALSE;

    ThriftSocket     *socket     = NULL;
    ThriftTransport  *transport  = NULL;
    ThriftProtocol   *protocol   = NULL;
    GError           *error      = NULL;
    ogonIf           *client     = NULL;

#if (!GLIB_CHECK_VERSION (2, 36, 0))
  g_type_init ();
#endif

  socket    = g_object_new (THRIFT_TYPE_SOCKET,
                            //"hostname",  "192.168.1.64",
                            "hostname",  "127.0.0.1",
                            "port",      9092,
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
    cli->error = error;
    cli->tid = tid;

    clientData = cli;

    g_ptr_array_add(thriftClients, cli);
  }
  else {

    g_clear_error (&error);
    g_object_unref (client);
    g_object_unref (protocol);
    g_object_unref (transport);
    g_object_unref (socket);
  }


end:
  pthread_mutex_unlock(&clientMutex);

  return clientData;
}

void OgonLog(FILE* f, const char *func, const char *fmt, ...)
{

  pthread_mutex_lock(&logMutex);

	va_list args;

	fprintf(f, "[%lX]  %s : ", pthread_self(), func);

	va_start(args, fmt);
	vfprintf(f, fmt, args);
	va_end(args);

	fprintf(f, "\n");

  pthread_mutex_unlock(&logMutex);
}