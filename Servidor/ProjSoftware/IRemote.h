/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __IREMOTE_H__
#define __IREMOTE_H__




class IRemote;
typedef IRemote *IRemote_ptr;
typedef IRemote_ptr IRemoteRef;
typedef ObjVar< IRemote > IRemote_var;
typedef ObjOut< IRemote > IRemote_out;



struct ObjetoSerial;
typedef TFixVar< ObjetoSerial > ObjetoSerial_var;
typedef ObjetoSerial& ObjetoSerial_out;


struct ObjetoSerial {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ObjetoSerial_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ObjetoSerial();
  ~ObjetoSerial();
  ObjetoSerial( const ObjetoSerial& s );
  ObjetoSerial& operator=( const ObjetoSerial& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  CORBA::UShort x;
  CORBA::UShort y;
  CORBA::UShort tipo;
  CORBA::UShort info1;
  CORBA::UShort info2;
  CORBA::UShort info3;
  CORBA::UShort info4;
  CORBA::UShort info5;
  CORBA::UShort info6;
  CORBA::UShort info7;
  CORBA::UShort info8;
  CORBA::UShort info9;
  CORBA::UShort info10;
};

struct Teclado;
typedef TVarVar< Teclado > Teclado_var;
typedef TVarOut< Teclado > Teclado_out;


struct Teclado {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef Teclado_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  Teclado();
  ~Teclado();
  Teclado( const Teclado& s );
  Teclado& operator=( const Teclado& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  typedef SequenceTmpl< CORBA::Char,MICO_TID_CHAR> _keys_seq;
  _keys_seq keys;
};

struct VetorObjetos;
typedef TVarVar< VetorObjetos > VetorObjetos_var;
typedef TVarOut< VetorObjetos > VetorObjetos_out;


struct VetorObjetos {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef VetorObjetos_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  VetorObjetos();
  ~VetorObjetos();
  VetorObjetos( const VetorObjetos& s );
  VetorObjetos& operator=( const VetorObjetos& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  typedef SequenceTmpl< ObjetoSerial,MICO_TID_DEF> _vetor_seq;
  _vetor_seq vetor;
};


/*
 * Base class and common definitions for interface IRemote
 */

class IRemote : 
  virtual public CORBA::Object
{
  public:
    virtual ~IRemote();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef IRemote_ptr _ptr_type;
    typedef IRemote_var _var_type;
    #endif

    static IRemote_ptr _narrow( CORBA::Object_ptr obj );
    static IRemote_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static IRemote_ptr _duplicate( IRemote_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static IRemote_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void sendKeys( const ::Teclado& keys ) = 0;
    virtual CORBA::Boolean pronto() = 0;
    virtual CORBA::Boolean acabou() = 0;
    virtual ::ObjetoSerial getProximo() = 0;

  protected:
    IRemote() {};
  private:
    IRemote( const IRemote& );
    void operator=( const IRemote& );
};

// Stub for interface IRemote
class IRemote_stub:
  virtual public IRemote
{
  public:
    virtual ~IRemote_stub();
    void sendKeys( const ::Teclado& keys );
    CORBA::Boolean pronto();
    CORBA::Boolean acabou();
    ::ObjetoSerial getProximo();

  private:
    void operator=( const IRemote_stub& );
};

#ifndef MICO_CONF_NO_POA

class IRemote_stub_clp :
  virtual public IRemote_stub,
  virtual public PortableServer::StubBase
{
  public:
    IRemote_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~IRemote_stub_clp ();
    void sendKeys( const ::Teclado& keys );
    CORBA::Boolean pronto();
    CORBA::Boolean acabou();
    ::ObjetoSerial getProximo();

  protected:
    IRemote_stub_clp ();
  private:
    void operator=( const IRemote_stub_clp & );
};

#endif // MICO_CONF_NO_POA

#ifndef MICO_CONF_NO_POA

class POA_IRemote : virtual public PortableServer::StaticImplementation
{
  public:
    virtual ~POA_IRemote ();
    IRemote_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static POA_IRemote * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual void sendKeys( const ::Teclado& keys ) = 0;
    virtual CORBA::Boolean pronto() = 0;
    virtual CORBA::Boolean acabou() = 0;
    virtual ::ObjetoSerial getProximo() = 0;

  protected:
    POA_IRemote () {};

  private:
    POA_IRemote (const POA_IRemote &);
    void operator= (const POA_IRemote &);
};

#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_ObjetoSerial;

extern CORBA::StaticTypeInfo *_marshaller_Teclado;

extern CORBA::StaticTypeInfo *_marshaller_VetorObjetos;

extern CORBA::StaticTypeInfo *_marshaller_IRemote;

extern CORBA::StaticTypeInfo *_marshaller__seq_ObjetoSerial;

#endif
