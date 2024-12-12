#include <thrift/c_glib/transport/thrift_transport.h>
#include <thrift/c_glib/transport/thrift_socket.h>
#include <thrift/c_glib/transport/thrift_buffered_transport.h>
#include <thrift/c_glib/protocol/thrift_binary_protocol.h>

#include <glib-object.h>
#include <glib.h>

#include "gen-c_glib/ogon.h"
#include "gen-c_glib/ogon_types.h"
#include "client.h"
#include "utils.h"

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

LONG Ogon_SCardReleaseContext(SCARDCONTEXT hContext) {

  LONG ret = SCARD_F_INTERNAL_ERROR;
 
  if (ogon_if_release_context(client, &ret, hContext, &error)) {

    /*g_object_get(ret_rpc,
                  "retValue", &ret,
                  NULL);                 */
  }

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

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "mszReaders",  &Readers,
                  "pcchReaders", &chReaders,
                  NULL);           

    LONG err = Copy_WithMemAllocIfNeed(Readers, chReaders, (void**)mszReaders, pcchReaders);
    
    if(err) {
      ret = err;
    }
    
    //g_free (Readers);
  }

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

LONG Ogon_SCardReconnect(SCARDHANDLE hCard, 
                         DWORD dwShareMode,
	                       DWORD dwPreferredProtocols, 
                         DWORD dwInitialization,
                         LPDWORD pdwActiveProtocol) {
  LONG ret = SCARD_F_INTERNAL_ERROR;

  return_r *ret_rpc = g_object_new(TYPE_RETURN_R, NULL);
  
  if (ogon_if_reconnect(client, &ret_rpc, hCard, dwShareMode, dwPreferredProtocols, dwInitialization, &error)) {
    
    DWORD_RPC       activeProtocol;

    g_object_get(ret_rpc,
                  "retValue",  &ret,
                  "pdwActiveProtocol", &activeProtocol,
                  NULL);   
    *pdwActiveProtocol = activeProtocol;
  }

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardDisconnect(SCARDHANDLE hCard, DWORD dwDisposition) {
  
  LONG ret = SCARD_F_INTERNAL_ERROR;
  
  if (ogon_if_disconnect(client, &ret, hCard, dwDisposition, &error)) {

    /*g_object_get(ret_rpc,
                  "retValue", &ret,
                  NULL);                 */
  }

  return ret;
}

LONG Ogon_SCardStatus(SCARDHANDLE hCard, 
                      LPSTR szReaderName, 
                      LPDWORD pcchReaderLen, 
                      LPDWORD pdwState, 
                      LPDWORD pdwProtocol, 
                      LPBYTE pbAtr, 
                      LPDWORD pcbAtrLen) {
  LONG ret = SCARD_F_INTERNAL_ERROR;

  return_s *ret_rpc = g_object_new(TYPE_RETURN_S, NULL);
  
  if (ogon_if_status(client, &ret_rpc, hCard, &error)) {

    DWORD_RPC dwState, dwProtocol;

    LPSTR_RPC ReaderName = NULL;
    DWORD_RPC ReaderNameLen = 0;
    GByteArray *Atr;

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "pdwState",  &dwState,
                  "pdwProtocol", &dwProtocol,
                  "szReaderName", &ReaderName,
                  "pcchReaderLen", &ReaderNameLen,
                  "pbAtr", &Atr,
                  NULL);     

    *pdwState = dwState;
    *pdwProtocol = dwProtocol;

    LONG err = Copy_WithMemAllocIfNeed(ReaderName, ReaderNameLen, (void**)szReaderName, pcchReaderLen);
    
    if(err) {
      ret = err;
    }
    
    //g_free (ReaderName);

    err = Copy_WithMemAllocIfNeed(Atr->data, Atr->len, (void**)pbAtr, pcbAtrLen);
    
    if(err) {
      ret = err;
    }

    //g_byte_array_free (Atr, TRUE);

  }

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardGetStatusChange(SCARDCONTEXT hContext, 
                               DWORD dwTimeout,	
                               SCARD_READERSTATE *rgReaderStates, 
                               DWORD cReaders) { 
  LONG ret = SCARD_F_INTERNAL_ERROR;

  return_gsc *ret_rpc = g_object_new(TYPE_RETURN_GSC, NULL);
  
  GPtrArray *inReaderStates = g_ptr_array_new();
  
  int i ;
  
  for(i = 0; i < cReaders; i++) {
    
    scard_readerstate_rpc *in_reader_state = g_object_new(TYPE_SCARD_READERSTATE_RPC, NULL);
    GByteArray *atr = g_byte_array_new();
    DWORD AtrSize = rgReaderStates->cbAtr > MAX_ATR_SIZE ? MAX_ATR_SIZE : rgReaderStates->cbAtr;

    atr = g_byte_array_append(atr, &rgReaderStates->rgbAtr[0], AtrSize);

    g_object_set(in_reader_state,
                  "szReader",  rgReaderStates->szReader,
                  "dwCurrentState", rgReaderStates->dwCurrentState,
                  "dwEventState", rgReaderStates->dwEventState,
                  "rgbAtr", atr,
                  NULL);   

    g_ptr_array_add(inReaderStates, in_reader_state);
  }

  if (ogon_if_get_status_change(client, &ret_rpc, hContext, dwTimeout, inReaderStates, cReaders, &error)) {
    
    GPtrArray *outReaderStates;

    g_object_get(ret_rpc,
                  "retValue",  &ret,
                  "rgReaderStates", &outReaderStates,
                  NULL);  

    for(i = 0; i < cReaders; i++) {
      scard_readerstate_rpc *out_reader_state = g_ptr_array_index(outReaderStates, i);

      LPSTR_RPC    szReader;
      DWORD_RPC    dwCurrentState;
	    DWORD_RPC    dwEventState;
      LPBYTE_RPC   rgbAtr;
          
      g_object_set(out_reader_state,
                  "szReader",  &szReader,
                  "dwCurrentState", &dwCurrentState,
                  "dwEventState", &dwEventState,
                  "rgbAtr", &rgbAtr,
                  NULL);  
      
        rgReaderStates[j].dwCurrentState = dwCurrentState;
        rgReaderStates[j].dwEventState = dwEventState;
        rgReaderStates[j].cbAtr = rgbAtr->len;
        memcpy(rgReaderStates[j].rgbAtr, rgbAtr->data, rgbAtr->len);
      }
    }
  }

  for(i = 0; i < cReaders; i++) {
    scard_readerstate_rpc *in_reader_state = g_ptr_array_index(inReaderStates, i);
    g_object_unref(in_reader_state); 
  }

  g_ptr_array_free(inReaderStates, TRUE);
  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardTransmit(SCARDHANDLE hCard, 
                        const SCARD_IO_REQUEST *pioSendPci,
	                      LPCBYTE pbSendBuffer, 
                        DWORD cbSendLength,
	                      SCARD_IO_REQUEST *pioRecvPci, 
                        LPBYTE pbRecvBuffer,
	                      LPDWORD pcbRecvLength) {

  LONG ret = SCARD_F_INTERNAL_ERROR;

  return_t *ret_rpc = g_object_new(TYPE_RETURN_T, NULL);

  scard_io_request_rpc *ioSendPCI = g_object_new(TYPE_SCARD_IO_REQUEST_RPC, NULL);

  ioSendPCI->cbPciLength = pioSendPci->cbPciLength;
  ioSendPCI->dwProtocol = pioSendPci->dwProtocol;

  GByteArray *sendBuf = g_byte_array_new();
  sendBuf = g_byte_array_append(sendBuf, pbSendBuffer, cbSendLength);
  
  if (ogon_if_transmit(client, &ret_rpc, hCard, ioSendPCI, sendBuf, *pcbRecvLength, &error)) {

    GByteArray *recvBuf = NULL;
    scard_io_request_rpc *ioRecvPCI;

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "pioRecvPci",  &ioRecvPCI,
                  "pbRecvBuffer", &recvBuf,
                   NULL);     

    LONG err = Copy_WithMemAllocIfNeed(recvBuf->data, recvBuf->len, (void**)pbRecvBuffer, pcbRecvLength);
    
    if(err) {
      ret = err;
    }

    pioRecvPci->cbPciLength = ioRecvPCI->cbPciLength;
    pioRecvPci->dwProtocol = ioRecvPCI->dwProtocol;

    //g_byte_array_free (recvBuf, TRUE);
    //g_object_unref(ioRecvPCI);
  }

  g_byte_array_free (sendBuf, TRUE);
  g_object_unref(ioSendPCI);
  g_object_unref(ret_rpc);

  return ret;
}



void Ogon_SCardFreeMemory(SCARDCONTEXT hContext, LPCVOID pvMem) {
  
  if(pvMem)
    free((void*)pvMem);
}