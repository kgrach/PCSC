#include <thrift/c_glib/transport/thrift_transport.h>
#include <thrift/c_glib/transport/thrift_socket.h>
#include <thrift/c_glib/transport/thrift_buffered_transport.h>
#include <thrift/c_glib/protocol/thrift_binary_protocol.h>

#include <glib-object.h>
#include <glib.h>
#include <stdio.h>

#include "gen-c_glib/ogon.h"
#include "gen-c_glib/ogon_types.h"
#include "client.h"
#include "utils.h"


LONG Ogon_SCardEstablishContext(void* clientData, 
                                DWORD dwScope, 
                                LPCVOID pvReserved1, 
                                LPCVOID pvReserved2,
		                            LPSCARDCONTEXT phContext) {
    
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_ec *ret_rpc = g_object_new(TYPE_RETURN_EC, NULL);
  
  if (ogon_if_establish_context(client->client, &ret_rpc, dwScope, &client->error)) {

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "cardContext", phContext,
                  NULL);                 
  }
  else {
    printf ("Client caught an exception: %s\n", client->error->message);
    g_clear_error (&client->error);
  }

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardReleaseContext(void* clientData,SCARDCONTEXT hContext) {

  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  if (ogon_if_release_context(client->client, &ret, hContext, &client->error)) {

    /*g_object_get(ret_rpc,
                  "retValue", &ret,
                  NULL);                 */
  }

  return ret;
}

LONG Ogon_SCardListReaders(void* clientData,SCARDCONTEXT hContext, 
                           LPCSTR mszGroups,
	                         LPSTR mszReaders, 
                           LPDWORD pcchReaders) {
    
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_lr *ret_rpc = g_object_new(TYPE_RETURN_LR, NULL);

  if (NULL == mszReaders)
    *pcchReaders = SCARD_AUTOALLOCATE;

  if (ogon_if_list_readers(client->client, &ret_rpc, hContext, *pcchReaders, &client->error)) {

    GByteArray *Readers;

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "mszReaders",  &Readers,
                  NULL); 

    LONG err;

    if(SCARD_S_SUCCESS == ret) {
      err = Copy_WithMemAllocIfNeed(Readers->data, Readers->len, (void**)mszReaders, pcchReaders);
      if(err){
        ret = err;
      }
    }
  }

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardListReaderGroups(void* clientData,SCARDCONTEXT hContext, 
                                LPSTR mszGroups, 
                                LPDWORD pcchGroups) {
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_lrg *ret_rpc = g_object_new(TYPE_RETURN_LRG, NULL);

  if (NULL == mszGroups)
    *pcchGroups = SCARD_AUTOALLOCATE;
  
  if (ogon_if_list_reader_groups(client->client, &ret_rpc, hContext, *pcchGroups, &client->error)) {

    GByteArray *Groups;

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "mszGroups",  &Groups,
                  NULL);           
    LONG err;

    if(SCARD_S_SUCCESS == ret) {
      err = Copy_WithMemAllocIfNeed(Groups->data, Groups->len, (void**)mszGroups, pcchGroups);
      if(err){
        ret = err;
      }
    }
  }

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardConnect(void* clientData,SCARDCONTEXT hContext, 
                       LPCSTR szReader,
	                     DWORD dwShareMode, 
                       DWORD dwPreferredProtocols, 
                       LPSCARDHANDLE phCard,
                       LPDWORD pdwActiveProtocol) {
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_c *ret_rpc = g_object_new(TYPE_RETURN_C, NULL);
  
  if (ogon_if_connect(client->client, &ret_rpc, hContext, (LPCSTR_RPC)szReader, dwShareMode, dwPreferredProtocols, &client->error)) {
    
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

LONG Ogon_SCardReconnect(void* clientData,SCARDHANDLE hCard, 
                         DWORD dwShareMode,
	                       DWORD dwPreferredProtocols, 
                         DWORD dwInitialization,
                         LPDWORD pdwActiveProtocol) {
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_r *ret_rpc = g_object_new(TYPE_RETURN_R, NULL);
  
  if (ogon_if_reconnect(client->client, &ret_rpc, hCard, dwShareMode, dwPreferredProtocols, dwInitialization, &client->error)) {
    
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

LONG Ogon_SCardDisconnect(void* clientData,SCARDHANDLE hCard, DWORD dwDisposition) {
  
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  ogon_if_disconnect(client->client, &ret, hCard, dwDisposition, &client->error);

  return ret;
}

LONG Ogon_SCardStatus(void* clientData,SCARDHANDLE hCard, 
                      LPSTR szReaderName, 
                      LPDWORD pcchReaderLen, 
                      LPDWORD pdwState, 
                      LPDWORD pdwProtocol, 
                      LPBYTE pbAtr, 
                      LPDWORD pcbAtrLen) {
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_s *ret_rpc = g_object_new(TYPE_RETURN_S, NULL);

  if (NULL == szReaderName)
    *pcchReaderLen = SCARD_AUTOALLOCATE;
  
  if (NULL == pbAtr)
    *pcbAtrLen = SCARD_AUTOALLOCATE;
  
  if (ogon_if_status(client->client, &ret_rpc, hCard, *pcchReaderLen, *pcbAtrLen, &client->error)) {

    DWORD_RPC dwState, dwProtocol;

    GByteArray *ReaderName;
    GByteArray *Atr;

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "pdwState",  &dwState,
                  "pdwProtocol", &dwProtocol,
                  "szReaderName", &ReaderName,
                  "pbAtr", &Atr,
                  NULL);     

    *pdwState = dwState;
    *pdwProtocol = dwProtocol;

    LONG err;

    if(SCARD_S_SUCCESS == ret) {
      err = Copy_WithMemAllocIfNeed(ReaderName->data, ReaderName->len, (void**)szReaderName, pcchReaderLen);
      if(err){
        ret = err;
      }
    }

    if(SCARD_S_SUCCESS == ret) {
      err = Copy_WithMemAllocIfNeed(Atr->data, Atr->len, (void**)pbAtr, pcbAtrLen);
      if(err){
        ret = err;
      }
    }
  }

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardGetStatusChange(void* clientData,SCARDCONTEXT hContext, 
                               DWORD dwTimeout,	
                               SCARD_READERSTATE *rgReaderStates, 
                               DWORD cReaders) { 
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_gsc *ret_rpc = g_object_new(TYPE_RETURN_GSC, NULL);
  
  GPtrArray *inReaderStates = g_ptr_array_new();
  
  int i ;
  
  for(i = 0; i < cReaders; i++) {
    
    scard_readerstate_rpc *in_reader_state = g_object_new(TYPE_SCARD_READERSTATE_RPC, NULL);

    g_object_set(in_reader_state,
                  "szReader",  rgReaderStates[i].szReader,
                  "dwCurrentState", rgReaderStates[i].dwCurrentState,
                  NULL);   

    g_ptr_array_add(inReaderStates, in_reader_state);
  }

  if (ogon_if_get_status_change(client->client, &ret_rpc, hContext, dwTimeout, inReaderStates, cReaders, &client->error)) {
    
    GPtrArray *outReaderStates;

    g_object_get(ret_rpc,
                  "retValue",  &ret,
                  "rgReaderStates", &outReaderStates,
                  NULL);  

    for(i = 0; i < cReaders; i++) {
      scard_readerstate_rpc *out_reader_state = g_ptr_array_index(outReaderStates, i);

      LPSTR_RPC    szReader;
	    DWORD_RPC    dwEventState;
      LPBYTE_RPC   rgbAtr;
          
      g_object_get(out_reader_state,
                  "szReader",  &szReader,
                  "dwEventState", &dwEventState,
                  "rgbAtr", &rgbAtr,
                  NULL);  
      
      rgReaderStates[i].dwEventState = dwEventState;
      rgReaderStates[i].cbAtr = rgbAtr->len;
      memcpy(rgReaderStates[i].rgbAtr, rgbAtr->data, rgbAtr->len);
    }
  }

  for(i = 0; i < cReaders; i++) {
    scard_readerstate_rpc *in_reader_state = g_ptr_array_index(inReaderStates, i);
    g_object_unref(in_reader_state); 
  }
  //printf ("Client caught an exception: %s\n", error->message);
  g_ptr_array_free(inReaderStates, TRUE);
  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardTransmit(void* clientData,SCARDHANDLE hCard, 
                        const SCARD_IO_REQUEST *pioSendPci,
	                      LPCBYTE pbSendBuffer, 
                        DWORD cbSendLength,
	                      SCARD_IO_REQUEST *pioRecvPci, 
                        LPBYTE pbRecvBuffer,
	                      LPDWORD pcbRecvLength) {

  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_t *ret_rpc = g_object_new(TYPE_RETURN_T, NULL);

  scard_io_request_rpc *ioSendPCI = g_object_new(TYPE_SCARD_IO_REQUEST_RPC, NULL);

  ioSendPCI->cbPciLength = pioSendPci->cbPciLength;
  ioSendPCI->dwProtocol = pioSendPci->dwProtocol;

  GByteArray *sendBuf = g_byte_array_new();
  sendBuf = g_byte_array_append(sendBuf, pbSendBuffer, cbSendLength);
  
  if (ogon_if_transmit(client->client, &ret_rpc, hCard, ioSendPCI, sendBuf, *pcbRecvLength, &client->error)) {

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

    if(pioRecvPci) {
      pioRecvPci->cbPciLength = ioRecvPCI->cbPciLength;
      pioRecvPci->dwProtocol = ioRecvPCI->dwProtocol;
    }
  }

  g_byte_array_free (sendBuf, TRUE);
  g_object_unref(ioSendPCI);
  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardBeginTransaction(void* clientData,SCARDHANDLE hCard) {
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;
  
  ogon_if_begin_transaction(client->client, &ret, hCard, &client->error);

  return ret;
}

LONG Ogon_SCardEndTransaction(void* clientData,SCARDHANDLE hCard, DWORD dwDisposition) {
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  ogon_if_end_transaction(client->client, &ret, hCard, dwDisposition, &client->error);

  return ret;
}

LONG Ogon_SCardGetAttrib(void* clientData,SCARDHANDLE hCard, DWORD dwAttrId, LPBYTE pbAttr, LPDWORD pcbAttrLen) {
  
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_ga *ret_rpc = g_object_new(TYPE_RETURN_GA, NULL);
  
  if (NULL == pbAttr)
    *pcbAttrLen = SCARD_AUTOALLOCATE;
  
  if (ogon_if_get_attrib(client->client, &ret_rpc, hCard, dwAttrId, *pcbAttrLen, &client->error)) {

    GByteArray *Attr;

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "pbAttr", &Attr,
                  NULL);     
    
    LONG err;

    if(SCARD_S_SUCCESS == ret) {
      err = Copy_WithMemAllocIfNeed(Attr->data, Attr->len, (void**)pbAttr, pcbAttrLen);
      if(err){
        ret = err;
      }
    }
  }

  g_object_unref(ret_rpc);

  return ret;
}

LONG Ogon_SCardControl(void* clientData,SCARDHANDLE hCard, 
                       DWORD dwControlCode, 
                       LPCVOID pbSendBuffer,
                       DWORD cbSendLength, 
                       LPVOID pbRecvBuffer, 
                       DWORD cbRecvLength,
                       LPDWORD lpBytesReturned) {
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  return_ctrl *ret_rpc = g_object_new(TYPE_RETURN_CTRL, NULL);

  GByteArray *sendBuf = g_byte_array_new();
  sendBuf = g_byte_array_append(sendBuf, pbSendBuffer, cbSendLength); 
  
  if (ogon_if_control(client->client, &ret_rpc, hCard, dwControlCode, sendBuf, cbRecvLength, &client->error)) {

    GByteArray *recvBuf;

    g_object_get(ret_rpc,
                  "retValue", &ret,
                  "pbRecvBuffer", &recvBuf,
                  NULL);     
    
    LONG err;

    if(SCARD_S_SUCCESS == ret) {
      *lpBytesReturned = cbRecvLength;
      err = Copy_WithMemAllocIfNeed(recvBuf->data, recvBuf->len, (void**)pbRecvBuffer, lpBytesReturned);
      if(err){
        ret = err;
      }
    }
  }

  g_byte_array_free (sendBuf, TRUE);
  g_object_unref(ret_rpc);

  return ret;                                             
}

LONG Ogon_SCardCancel(void* clientData,SCARDCONTEXT hContext) {
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;


  ogon_if_cancel(client->client, &ret, hContext, &client->error);

  return ret;
}

LONG Ogon_SCardIsValidContext(void* clientData,SCARDCONTEXT hContext) {
  LONG ret = SCARD_F_INTERNAL_ERROR;
  struct ThriftClientData *client = clientData;

  ogon_if_is_valid_context(client->client, &ret, hContext, &client->error);

  return ret;
}

void Ogon_SCardFreeMemory(void* clientData,SCARDCONTEXT hContext, LPCVOID pvMem) {
  
  if(pvMem)
    free((void*)pvMem);
}