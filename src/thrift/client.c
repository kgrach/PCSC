#include <thrift/c_glib/transport/thrift_transport.h>
#include <thrift/c_glib/transport/thrift_socket.h>
#include <thrift/c_glib/transport/thrift_buffered_transport.h>
#include <thrift/c_glib/protocol/thrift_binary_protocol.h>

#include <glib-object.h>
#include <glib.h>

#include "gen-c_glib/ogon.h"
#include "client.h"

static ThriftSocket     *socket     = NULL;
static ThriftTransport  *transport  = NULL;
static ThriftProtocol   *protocol   = NULL;
static GError           *error      = NULL;
static ogonIf           *client     = NULL;

int start_client (void) {

  gboolean success = FALSE;
  
#if (!GLIB_CHECK_VERSION (2, 36, 0))
  g_type_init ();
#endif

  socket    = g_object_new (THRIFT_TYPE_SOCKET,
                            "hostname",  "localhost",
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
  
  return (success ? 0 : 1 );
}


void stop_client() {

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