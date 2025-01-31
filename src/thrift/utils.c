#include <pcsclite.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>



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

unsigned short GetServerPort() {
    
    int fd_w, fd_r, len;
    char buf_in[100], buf_out[100];
    const char *fifoname = getenv("OGON_COOKIE");

    unsigned short port = 0;

    strcpy(buf_in, "/tmp/");
    strcpy(buf_in+strlen(buf_in), fifoname);
    strcpy(buf_in+strlen(buf_in), ".in");

    strcpy(buf_out, "/tmp/");
    strcpy(buf_out+strlen(buf_out), fifoname);
    strcpy(buf_out+strlen(buf_out), ".out");

    if ( (fd_w = open(buf_in, O_WRONLY))> 0 ) {

        write(fd_w, &fd_w, 1);      
        close(fd_w);
    }

    if ( (fd_r = open(buf_out, O_RDONLY))> 0 ) {

        memset(buf_out, '\0', sizeof(buf_out));
        len = read(fd_r, buf_out, sizeof(buf_out)-1);

        if(2 == len) {
          port = *(unsigned short*)&buf_out[0];
        }
        
        close(fd_r);

    }
    return port;
}


void* GetThriftClient() {

    pthread_mutex_lock(&clientMutex);

    struct ThriftClientData *clientData = NULL;

    if(NULL == thriftClients)
        thriftClients = g_ptr_array_new();

    long tid =  syscall(SYS_gettid);//gettid();

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
  
  static unsigned short port = 0;
  
  if(0 == port) 
    port = GetServerPort();

  if(0 == port)
    goto end;

  socket    = g_object_new (THRIFT_TYPE_SOCKET,
                            "hostname",  "127.0.0.1",
                            "port",      port,
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

  if(f) {

    pthread_mutex_lock(&logMutex);

    va_list args;

    fprintf(f, "[%lX]  %s : ", pthread_self(), func);

    va_start(args, fmt);
    vfprintf(f, fmt, args);
    va_end(args);

    fprintf(f, "\n");

    pthread_mutex_unlock(&logMutex);
  }
}

char* Dump2Str(char* in_buf, unsigned long in_buf_len) {

  const char bin2char[] = "0123456789ABCDEF";  
  
  char *out_buf = malloc(in_buf_len * 2 + 1);
  
  memset(out_buf, 0, in_buf_len * 2 + 1);

  int j;
  
  for(j = 0; j < in_buf_len; j++ ){
    char ch = *(in_buf + j);

    *(out_buf + 2*j) = bin2char[ (ch >> 4) & 0x0F ];
    *(out_buf + (2*j)+1) = bin2char[ch & 0x0F];  
  }

  return out_buf;
}