typedef i64     DWORD_RPC;
typedef i64     SCARDCONTEXT_RPC;
typedef i64     LONG_RPC;
typedef i64     LPDWORD_RPC;
typedef string  LPSTR_RPC;
typedef string  LPCSTR_RPC;
typedef i64     SCARDHANDLE_RPC;

struct return_ec {
  1: LONG_RPC           retValue,
  2: SCARDCONTEXT_RPC   cardContext
}

struct return_rc {
  1: LONG_RPC           retValue
}

struct return_lr {
  1: LONG_RPC         retValue,
  2: LPSTR_RPC        mszReaders, 
  3: DWORD_RPC        pcchReaders
}

struct return_c {
  1: LONG_RPC           retValue,
  2: SCARDHANDLE_RPC    phCard, 
  3: DWORD_RPC          pdwActiveProtocol
}

service ogon {
   return_ec EstablishContext(1: DWORD_RPC dwScope);
   return_rc ReleaseContext(1: SCARDCONTEXT_RPC hContext);
   return_lr ListReaders(1: SCARDCONTEXT_RPC hContext);
   return_c  Connect(1: SCARDCONTEXT_RPC hContext, 2: LPCSTR_RPC szReader, 3:DWORD_RPC dwShareMode, 4: DWORD_RPC dwPreferredProtocols);
}



