typedef i64     DWORD_RPC;
typedef i64     CARDCONTEXT_RPC;
typedef i64     LONG_RPC;

struct return_ec {
  1: LONG_RPC         retValue,
  2: CARDCONTEXT_RPC  cardContext
}

service ogon {
   return_ec EstablishContext(1: DWORD_RPC dwScope)
}




