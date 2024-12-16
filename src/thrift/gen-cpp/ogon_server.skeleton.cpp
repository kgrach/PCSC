// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ogon.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class ogonHandler : virtual public ogonIf {
 public:
  ogonHandler() {
    // Your initialization goes here
  }

  void EstablishContext(return_ec& _return, const DWORD_RPC dwScope) {
    // Your implementation goes here
    printf("EstablishContext\n");
  }

  LONG_RPC ReleaseContext(const SCARDCONTEXT_RPC hContext) {
    // Your implementation goes here
    printf("ReleaseContext\n");
  }

  void ListReaders(return_lr& _return, const SCARDCONTEXT_RPC hContext, const DWORD_RPC pcchReaders) {
    // Your implementation goes here
    printf("ListReaders\n");
  }

  void ListReaderGroups(return_lrg& _return, const SCARDCONTEXT_RPC hContext, const DWORD_RPC pcchGroups) {
    // Your implementation goes here
    printf("ListReaderGroups\n");
  }

  void Connect(return_c& _return, const SCARDCONTEXT_RPC hContext, const LPCSTR_RPC& szReader, const DWORD_RPC dwShareMode, const DWORD_RPC dwPreferredProtocols) {
    // Your implementation goes here
    printf("Connect\n");
  }

  void Reconnect(return_r& _return, const SCARDHANDLE_RPC hCard, const DWORD_RPC dwShareMode, const DWORD_RPC dwPreferredProtocols, const DWORD_RPC dwInitialization) {
    // Your implementation goes here
    printf("Reconnect\n");
  }

  LONG_RPC Disconnect(const SCARDHANDLE_RPC hCard, const DWORD_RPC dwDisposition) {
    // Your implementation goes here
    printf("Disconnect\n");
  }

  void Status(return_s& _return, const SCARDHANDLE_RPC hCard, const DWORD_RPC pcchReaderLen, const DWORD_RPC pcbAtrLen) {
    // Your implementation goes here
    printf("Status\n");
  }

  void GetStatusChange(return_gsc& _return, const SCARDCONTEXT_RPC hContext, const DWORD_RPC dwTimeout, const std::vector<scard_readerstate_rpc> & rgReaderStates, const DWORD_RPC cReaders) {
    // Your implementation goes here
    printf("GetStatusChange\n");
  }

  void Transmit(return_t& _return, const SCARDHANDLE_RPC hCard, const scard_io_request_rpc& pioSendPci, const LPBYTE_RPC& pbSendBuffer, const DWORD_RPC pcbRecvLength) {
    // Your implementation goes here
    printf("Transmit\n");
  }

  LONG_RPC BeginTransaction(const SCARDHANDLE_RPC hCard) {
    // Your implementation goes here
    printf("BeginTransaction\n");
  }

  LONG_RPC EndTransaction(const SCARDHANDLE_RPC hCard, const DWORD_RPC dwDisposition) {
    // Your implementation goes here
    printf("EndTransaction\n");
  }

  void GetAttrib(return_ga& _return, const SCARDHANDLE_RPC hCard, const DWORD_RPC dwAttrId, const DWORD_RPC pcbAttrLen) {
    // Your implementation goes here
    printf("GetAttrib\n");
  }

  void Control(return_ctrl& _return, const SCARDHANDLE_RPC hCard, const DWORD_RPC dwControlCode, const LPVOID_RPC& pbSendBuffer, const DWORD_RPC cbRecvLength) {
    // Your implementation goes here
    printf("Control\n");
  }

  LONG_RPC Cancel(const SCARDCONTEXT_RPC hContext) {
    // Your implementation goes here
    printf("Cancel\n");
  }

  LONG_RPC IsValidContext(const SCARDCONTEXT_RPC hContext) {
    // Your implementation goes here
    printf("IsValidContext\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<ogonHandler> handler(new ogonHandler());
  ::std::shared_ptr<TProcessor> processor(new ogonProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

