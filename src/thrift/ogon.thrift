typedef i64     DWORD_RPC;
typedef i64     SCARDCONTEXT_RPC;
typedef i64     LONG_RPC;
typedef i64     LPDWORD_RPC;
typedef string  LPSTR_RPC;
typedef string  LPCSTR_RPC;
typedef i64     SCARDHANDLE_RPC;
typedef binary  LPBYTE_RPC

struct return_ec {
  1: LONG_RPC           retValue
  2: SCARDCONTEXT_RPC   cardContext
}

struct return_rc {
  1: LONG_RPC           retValue
}

struct return_lr {
  1: LONG_RPC         retValue
  2: LPSTR_RPC        mszReaders
  3: DWORD_RPC        pcchReaders
}

struct return_c {
  1: LONG_RPC           retValue
  2: SCARDHANDLE_RPC    phCard
  3: DWORD_RPC          pdwActiveProtocol
}

struct return_s {
  1: LONG_RPC           retValue
  2: LPSTR_RPC          szReaderName
  3: DWORD_RPC          pcchReaderLen
  4: DWORD_RPC          pdwState
  5: DWORD_RPC          pdwProtocol
  6: LPBYTE_RPC         pbAtr
}

struct scard_io_request_rpc {
  1: LONG_RPC dwProtocol;	
	2: LONG_RPC cbPciLength;
}

struct return_t {
  1: LONG_RPC             retValue
  2: scard_io_request_rpc pioRecvPci
  3: LPBYTE_RPC           pbRecvBuffer
}

struct return_r {
  1: LONG_RPC           retValue
  2: DWORD_RPC          pdwActiveProtocol
}


service ogon {
  return_ec  EstablishContext(1: DWORD_RPC dwScope)
  return_lr  ListReaders(1: SCARDCONTEXT_RPC hContext)
  return_c   Connect(1: SCARDCONTEXT_RPC hContext, 2: LPCSTR_RPC szReader, 3:DWORD_RPC dwShareMode, 4: DWORD_RPC dwPreferredProtocols)
  return_s   Status(1: SCARDHANDLE_RPC hCard)
  return_t   Transmit(1: SCARDHANDLE_RPC hCard, 2:scard_io_request_rpc pioSendPci, 3:LPBYTE_RPC pbSendBuffer, 4: DWORD_RPC pcbRecvLength)
  return_r   Reconnect(1:SCARDHANDLE_RPC hCard, 2:DWORD_RPC dwShareMode, 3:DWORD_RPC dwPreferredProtocols, 4:DWORD_RPC dwInitialization)

  LONG_RPC   ReleaseContext(1: SCARDCONTEXT_RPC hContext)
  LONG_RPC   Disconnect(1:SCARDHANDLE_RPC hCard, 2:DWORD_RPC dwDisposition)
}

