/**
 * Autogenerated by Thrift Compiler (0.14.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef ogon_TYPES_H
#define ogon_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <functional>
#include <memory>




typedef int64_t DWORD_RPC;

typedef int64_t SCARDCONTEXT_RPC;

typedef int64_t LONG_RPC;

typedef int64_t LPDWORD_RPC;

typedef std::string LPSTR_RPC;

typedef std::string LPCSTR_RPC;

typedef int64_t SCARDHANDLE_RPC;

typedef std::string LPBYTE_RPC;

typedef std::string LPVOID_RPC;

class return_ec;

class return_rc;

class return_lr;

class return_lrg;

class return_c;

class return_s;

class scard_io_request_rpc;

class return_t;

class return_r;

class scard_readerstate_rpc;

class return_gsc;

class return_ga;

class return_ctrl;

typedef struct _return_ec__isset {
  _return_ec__isset() : retValue(false), cardContext(false) {}
  bool retValue :1;
  bool cardContext :1;
} _return_ec__isset;

class return_ec : public virtual ::apache::thrift::TBase {
 public:

  return_ec(const return_ec&);
  return_ec& operator=(const return_ec&);
  return_ec() : retValue(0), cardContext(0) {
  }

  virtual ~return_ec() noexcept;
  LONG_RPC retValue;
  SCARDCONTEXT_RPC cardContext;

  _return_ec__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_cardContext(const SCARDCONTEXT_RPC val);

  bool operator == (const return_ec & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(cardContext == rhs.cardContext))
      return false;
    return true;
  }
  bool operator != (const return_ec &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_ec & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_ec &a, return_ec &b);

std::ostream& operator<<(std::ostream& out, const return_ec& obj);

typedef struct _return_rc__isset {
  _return_rc__isset() : retValue(false) {}
  bool retValue :1;
} _return_rc__isset;

class return_rc : public virtual ::apache::thrift::TBase {
 public:

  return_rc(const return_rc&);
  return_rc& operator=(const return_rc&);
  return_rc() : retValue(0) {
  }

  virtual ~return_rc() noexcept;
  LONG_RPC retValue;

  _return_rc__isset __isset;

  void __set_retValue(const LONG_RPC val);

  bool operator == (const return_rc & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    return true;
  }
  bool operator != (const return_rc &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_rc & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_rc &a, return_rc &b);

std::ostream& operator<<(std::ostream& out, const return_rc& obj);

typedef struct _return_lr__isset {
  _return_lr__isset() : retValue(false), mszReaders(false) {}
  bool retValue :1;
  bool mszReaders :1;
} _return_lr__isset;

class return_lr : public virtual ::apache::thrift::TBase {
 public:

  return_lr(const return_lr&);
  return_lr& operator=(const return_lr&);
  return_lr() : retValue(0), mszReaders() {
  }

  virtual ~return_lr() noexcept;
  LONG_RPC retValue;
  LPBYTE_RPC mszReaders;

  _return_lr__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_mszReaders(const LPBYTE_RPC& val);

  bool operator == (const return_lr & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(mszReaders == rhs.mszReaders))
      return false;
    return true;
  }
  bool operator != (const return_lr &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_lr & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_lr &a, return_lr &b);

std::ostream& operator<<(std::ostream& out, const return_lr& obj);

typedef struct _return_lrg__isset {
  _return_lrg__isset() : retValue(false), mszGroups(false) {}
  bool retValue :1;
  bool mszGroups :1;
} _return_lrg__isset;

class return_lrg : public virtual ::apache::thrift::TBase {
 public:

  return_lrg(const return_lrg&);
  return_lrg& operator=(const return_lrg&);
  return_lrg() : retValue(0), mszGroups() {
  }

  virtual ~return_lrg() noexcept;
  LONG_RPC retValue;
  LPBYTE_RPC mszGroups;

  _return_lrg__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_mszGroups(const LPBYTE_RPC& val);

  bool operator == (const return_lrg & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(mszGroups == rhs.mszGroups))
      return false;
    return true;
  }
  bool operator != (const return_lrg &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_lrg & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_lrg &a, return_lrg &b);

std::ostream& operator<<(std::ostream& out, const return_lrg& obj);

typedef struct _return_c__isset {
  _return_c__isset() : retValue(false), phCard(false), pdwActiveProtocol(false) {}
  bool retValue :1;
  bool phCard :1;
  bool pdwActiveProtocol :1;
} _return_c__isset;

class return_c : public virtual ::apache::thrift::TBase {
 public:

  return_c(const return_c&);
  return_c& operator=(const return_c&);
  return_c() : retValue(0), phCard(0), pdwActiveProtocol(0) {
  }

  virtual ~return_c() noexcept;
  LONG_RPC retValue;
  SCARDHANDLE_RPC phCard;
  DWORD_RPC pdwActiveProtocol;

  _return_c__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_phCard(const SCARDHANDLE_RPC val);

  void __set_pdwActiveProtocol(const DWORD_RPC val);

  bool operator == (const return_c & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(phCard == rhs.phCard))
      return false;
    if (!(pdwActiveProtocol == rhs.pdwActiveProtocol))
      return false;
    return true;
  }
  bool operator != (const return_c &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_c & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_c &a, return_c &b);

std::ostream& operator<<(std::ostream& out, const return_c& obj);

typedef struct _return_s__isset {
  _return_s__isset() : retValue(false), szReaderName(false), pdwState(false), pdwProtocol(false), pbAtr(false) {}
  bool retValue :1;
  bool szReaderName :1;
  bool pdwState :1;
  bool pdwProtocol :1;
  bool pbAtr :1;
} _return_s__isset;

class return_s : public virtual ::apache::thrift::TBase {
 public:

  return_s(const return_s&);
  return_s& operator=(const return_s&);
  return_s() : retValue(0), szReaderName(), pdwState(0), pdwProtocol(0), pbAtr() {
  }

  virtual ~return_s() noexcept;
  LONG_RPC retValue;
  LPBYTE_RPC szReaderName;
  DWORD_RPC pdwState;
  DWORD_RPC pdwProtocol;
  LPBYTE_RPC pbAtr;

  _return_s__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_szReaderName(const LPBYTE_RPC& val);

  void __set_pdwState(const DWORD_RPC val);

  void __set_pdwProtocol(const DWORD_RPC val);

  void __set_pbAtr(const LPBYTE_RPC& val);

  bool operator == (const return_s & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(szReaderName == rhs.szReaderName))
      return false;
    if (!(pdwState == rhs.pdwState))
      return false;
    if (!(pdwProtocol == rhs.pdwProtocol))
      return false;
    if (!(pbAtr == rhs.pbAtr))
      return false;
    return true;
  }
  bool operator != (const return_s &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_s & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_s &a, return_s &b);

std::ostream& operator<<(std::ostream& out, const return_s& obj);

typedef struct _scard_io_request_rpc__isset {
  _scard_io_request_rpc__isset() : dwProtocol(false), cbPciLength(false) {}
  bool dwProtocol :1;
  bool cbPciLength :1;
} _scard_io_request_rpc__isset;

class scard_io_request_rpc : public virtual ::apache::thrift::TBase {
 public:

  scard_io_request_rpc(const scard_io_request_rpc&);
  scard_io_request_rpc& operator=(const scard_io_request_rpc&);
  scard_io_request_rpc() : dwProtocol(0), cbPciLength(0) {
  }

  virtual ~scard_io_request_rpc() noexcept;
  LONG_RPC dwProtocol;
  LONG_RPC cbPciLength;

  _scard_io_request_rpc__isset __isset;

  void __set_dwProtocol(const LONG_RPC val);

  void __set_cbPciLength(const LONG_RPC val);

  bool operator == (const scard_io_request_rpc & rhs) const
  {
    if (!(dwProtocol == rhs.dwProtocol))
      return false;
    if (!(cbPciLength == rhs.cbPciLength))
      return false;
    return true;
  }
  bool operator != (const scard_io_request_rpc &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const scard_io_request_rpc & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(scard_io_request_rpc &a, scard_io_request_rpc &b);

std::ostream& operator<<(std::ostream& out, const scard_io_request_rpc& obj);

typedef struct _return_t__isset {
  _return_t__isset() : retValue(false), pioRecvPci(false), pbRecvBuffer(false) {}
  bool retValue :1;
  bool pioRecvPci :1;
  bool pbRecvBuffer :1;
} _return_t__isset;

class return_t : public virtual ::apache::thrift::TBase {
 public:

  return_t(const return_t&);
  return_t& operator=(const return_t&);
  return_t() : retValue(0), pbRecvBuffer() {
  }

  virtual ~return_t() noexcept;
  LONG_RPC retValue;
  scard_io_request_rpc pioRecvPci;
  LPBYTE_RPC pbRecvBuffer;

  _return_t__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_pioRecvPci(const scard_io_request_rpc& val);

  void __set_pbRecvBuffer(const LPBYTE_RPC& val);

  bool operator == (const return_t & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(pioRecvPci == rhs.pioRecvPci))
      return false;
    if (!(pbRecvBuffer == rhs.pbRecvBuffer))
      return false;
    return true;
  }
  bool operator != (const return_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_t &a, return_t &b);

std::ostream& operator<<(std::ostream& out, const return_t& obj);

typedef struct _return_r__isset {
  _return_r__isset() : retValue(false), pdwActiveProtocol(false) {}
  bool retValue :1;
  bool pdwActiveProtocol :1;
} _return_r__isset;

class return_r : public virtual ::apache::thrift::TBase {
 public:

  return_r(const return_r&);
  return_r& operator=(const return_r&);
  return_r() : retValue(0), pdwActiveProtocol(0) {
  }

  virtual ~return_r() noexcept;
  LONG_RPC retValue;
  DWORD_RPC pdwActiveProtocol;

  _return_r__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_pdwActiveProtocol(const DWORD_RPC val);

  bool operator == (const return_r & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(pdwActiveProtocol == rhs.pdwActiveProtocol))
      return false;
    return true;
  }
  bool operator != (const return_r &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_r & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_r &a, return_r &b);

std::ostream& operator<<(std::ostream& out, const return_r& obj);

typedef struct _scard_readerstate_rpc__isset {
  _scard_readerstate_rpc__isset() : szReader(false), dwCurrentState(false), dwEventState(false), rgbAtr(false) {}
  bool szReader :1;
  bool dwCurrentState :1;
  bool dwEventState :1;
  bool rgbAtr :1;
} _scard_readerstate_rpc__isset;

class scard_readerstate_rpc : public virtual ::apache::thrift::TBase {
 public:

  scard_readerstate_rpc(const scard_readerstate_rpc&);
  scard_readerstate_rpc& operator=(const scard_readerstate_rpc&);
  scard_readerstate_rpc() : szReader(), dwCurrentState(0), dwEventState(0), rgbAtr() {
  }

  virtual ~scard_readerstate_rpc() noexcept;
  LPBYTE_RPC szReader;
  DWORD_RPC dwCurrentState;
  DWORD_RPC dwEventState;
  LPBYTE_RPC rgbAtr;

  _scard_readerstate_rpc__isset __isset;

  void __set_szReader(const LPBYTE_RPC& val);

  void __set_dwCurrentState(const DWORD_RPC val);

  void __set_dwEventState(const DWORD_RPC val);

  void __set_rgbAtr(const LPBYTE_RPC& val);

  bool operator == (const scard_readerstate_rpc & rhs) const
  {
    if (!(szReader == rhs.szReader))
      return false;
    if (!(dwCurrentState == rhs.dwCurrentState))
      return false;
    if (!(dwEventState == rhs.dwEventState))
      return false;
    if (!(rgbAtr == rhs.rgbAtr))
      return false;
    return true;
  }
  bool operator != (const scard_readerstate_rpc &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const scard_readerstate_rpc & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(scard_readerstate_rpc &a, scard_readerstate_rpc &b);

std::ostream& operator<<(std::ostream& out, const scard_readerstate_rpc& obj);

typedef struct _return_gsc__isset {
  _return_gsc__isset() : retValue(false), rgReaderStates(false) {}
  bool retValue :1;
  bool rgReaderStates :1;
} _return_gsc__isset;

class return_gsc : public virtual ::apache::thrift::TBase {
 public:

  return_gsc(const return_gsc&);
  return_gsc& operator=(const return_gsc&);
  return_gsc() : retValue(0) {
  }

  virtual ~return_gsc() noexcept;
  LONG_RPC retValue;
  std::vector<scard_readerstate_rpc>  rgReaderStates;

  _return_gsc__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_rgReaderStates(const std::vector<scard_readerstate_rpc> & val);

  bool operator == (const return_gsc & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(rgReaderStates == rhs.rgReaderStates))
      return false;
    return true;
  }
  bool operator != (const return_gsc &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_gsc & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_gsc &a, return_gsc &b);

std::ostream& operator<<(std::ostream& out, const return_gsc& obj);

typedef struct _return_ga__isset {
  _return_ga__isset() : retValue(false), pbAttr(false) {}
  bool retValue :1;
  bool pbAttr :1;
} _return_ga__isset;

class return_ga : public virtual ::apache::thrift::TBase {
 public:

  return_ga(const return_ga&);
  return_ga& operator=(const return_ga&);
  return_ga() : retValue(0), pbAttr() {
  }

  virtual ~return_ga() noexcept;
  LONG_RPC retValue;
  LPBYTE_RPC pbAttr;

  _return_ga__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_pbAttr(const LPBYTE_RPC& val);

  bool operator == (const return_ga & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(pbAttr == rhs.pbAttr))
      return false;
    return true;
  }
  bool operator != (const return_ga &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_ga & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_ga &a, return_ga &b);

std::ostream& operator<<(std::ostream& out, const return_ga& obj);

typedef struct _return_ctrl__isset {
  _return_ctrl__isset() : retValue(false), pbRecvBuffer(false) {}
  bool retValue :1;
  bool pbRecvBuffer :1;
} _return_ctrl__isset;

class return_ctrl : public virtual ::apache::thrift::TBase {
 public:

  return_ctrl(const return_ctrl&);
  return_ctrl& operator=(const return_ctrl&);
  return_ctrl() : retValue(0), pbRecvBuffer() {
  }

  virtual ~return_ctrl() noexcept;
  LONG_RPC retValue;
  LPVOID_RPC pbRecvBuffer;

  _return_ctrl__isset __isset;

  void __set_retValue(const LONG_RPC val);

  void __set_pbRecvBuffer(const LPVOID_RPC& val);

  bool operator == (const return_ctrl & rhs) const
  {
    if (!(retValue == rhs.retValue))
      return false;
    if (!(pbRecvBuffer == rhs.pbRecvBuffer))
      return false;
    return true;
  }
  bool operator != (const return_ctrl &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const return_ctrl & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(return_ctrl &a, return_ctrl &b);

std::ostream& operator<<(std::ostream& out, const return_ctrl& obj);



#endif
