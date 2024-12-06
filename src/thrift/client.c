#include <thrift/c_glib/transport/thrift_transport.h>
#include <thrift/c_glib/transport/thrift_socket.h>
#include <thrift/c_glib/transport/thrift_buffered_transport.h>
#include <thrift/c_glib/protocol/thrift_binary_protocol.h>

#include <glib-object.h>
#include <glib.h>

#include "gen-c_glib/ogon.h"
#include "gen-c_glib/ogon_types.h"
#include "client.h"

static ThriftSocket     *socket     = NULL;
static ThriftTransport  *transport  = NULL;
static ThriftProtocol   *protocol   = NULL;
static GError           *error      = NULL;
static ogonIf           *client     = NULL;

int rdp_ready = 0;

void __attribute__((constructor)) start_client (void) {
  
  gboolean success = FALSE;

#if (!GLIB_CHECK_VERSION (2, 36, 0))
  g_type_init ();
#endif

  socket    = g_object_new (THRIFT_TYPE_SOCKET,
                            "hostname",  "192.168.1.64",
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
  
  rdp_ready = (success ? 1 : 0 );
}


void __attribute__((destructor)) stop_client() {

  thrift_transport_close (transport, &error);

  g_clear_error (&error);

  g_object_unref (client);
  g_object_unref (protocol);
  g_object_unref (transport);
  g_object_unref (socket);
}

LONG Ogon_SCardEstablishContext(DWORD dwScope, 
                                LPCVOID pvReserved1, 
                                LPCVOID pvReserved2,
		                            LPSCARDCONTEXT phContext) {
    
  LONG ret = SCARD_F_INTERNAL_ERROR;

  return_ec *ret_rpc = g_object_new(TYPE_RETURN_EC, NULL);
  
  if (ogon_if_establish_context(client, &ret_rpc, dwScope, &error)) {

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "cardContext", phContext,
                  NULL);                 
  }

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardListReaders(SCARDCONTEXT hContext, 
                           LPCSTR mszGroups,
	                         LPSTR mszReaders, 
                           LPDWORD pcchReaders) {
    
  LONG ret = SCARD_F_INTERNAL_ERROR;

  return_lr *ret_rpc = g_object_new(TYPE_RETURN_LR, NULL);
  
  if (ogon_if_list_readers(client, &ret_rpc, hContext, &error)) {

    LPSTR_RPC Readers = NULL;
    DWORD_RPC chReaders = 0;
    char *buf = NULL;

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "mszReaders",  &Readers,
                  "pcchReaders", &chReaders,
                  NULL);           

    if(*mszReaders) {
      
      if(*pcchReaders < chReaders) {
        ret = SCARD_E_INSUFFICIENT_BUFFER;
        goto end; 
      } 
              
    } else {

      buf = malloc(chReaders);
      
      if (NULL == buf) {
        ret = SCARD_E_NO_MEMORY;
        goto end;
      }

      *(char**)mszReaders = buf;
    }

    memcpy(*(char**)mszReaders, Readers, chReaders);
    
    g_free (Readers);

    *pcchReaders = chReaders;
  }
end:

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardConnect(SCARDCONTEXT hContext, 
                       LPCSTR szReader,
	                     DWORD dwShareMode, 
                       DWORD dwPreferredProtocols, 
                       LPSCARDHANDLE phCard,
                       LPDWORD pdwActiveProtocol) {
  LONG ret = SCARD_F_INTERNAL_ERROR;

  return_c *ret_rpc = g_object_new(TYPE_RETURN_C, NULL);
  
  if (ogon_if_connect(client, &ret_rpc, hContext, (LPCSTR_RPC)szReader, dwShareMode, dwPreferredProtocols, &error)) {
    
    SCARDHANDLE_RPC hCard;
    DWORD_RPC       activeProtocol;

    g_object_get(ret_rpc,
                  "retValue",  &ret,
                  "phCard",    &hCard,
                  "pdwActiveProtocol", &activeProtocol,
                  NULL);   
    *phCard = hCard;
    *pdwActiveProtocol = activeProtocol;
  }

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardReleaseContext(SCARDCONTEXT hContext){

  LONG ret = SCARD_F_INTERNAL_ERROR;

  //return_rc *ret_rpc = g_object_new(TYPE_RETURN_RC, NULL);
  
  if (ogon_if_release_context(client, &ret, hContext, &error)) {

    /*g_object_get(ret_rpc,
                  "retValue", &ret,
                  NULL);                 */
  }

  //g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardDisconnect(SCARDHANDLE hCard, DWORD dwDisposition) {
  
  LONG ret = SCARD_F_INTERNAL_ERROR;

  //return_rc *ret_rpc = g_object_new(TYPE_RETURN_RC, NULL);
    
  if (ogon_if_disconnect(client, &ret, hCard, dwDisposition, &error)) {

    /*g_object_get(ret_rpc,
                  "retValue", &ret,
                  NULL);                 */
  }

  //g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardFreeMemory(SCARDCONTEXT hContext, LPCVOID pvMem) {
  
  if(pvMem)
    free(pvMem);
}