/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2006 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include "IRemote.h"


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------
#ifdef HAVE_EXPLICIT_STRUCT_OPS
ObjetoSerial::ObjetoSerial()
{
}

ObjetoSerial::ObjetoSerial( const ObjetoSerial& _s )
{
  x = ((ObjetoSerial&)_s).x;
  y = ((ObjetoSerial&)_s).y;
  tipo = ((ObjetoSerial&)_s).tipo;
  info1 = ((ObjetoSerial&)_s).info1;
  info2 = ((ObjetoSerial&)_s).info2;
  info3 = ((ObjetoSerial&)_s).info3;
  info4 = ((ObjetoSerial&)_s).info4;
  info5 = ((ObjetoSerial&)_s).info5;
  info6 = ((ObjetoSerial&)_s).info6;
  info7 = ((ObjetoSerial&)_s).info7;
  info8 = ((ObjetoSerial&)_s).info8;
  info9 = ((ObjetoSerial&)_s).info9;
  info10 = ((ObjetoSerial&)_s).info10;
}

ObjetoSerial::~ObjetoSerial()
{
}

ObjetoSerial&
ObjetoSerial::operator=( const ObjetoSerial& _s )
{
  x = ((ObjetoSerial&)_s).x;
  y = ((ObjetoSerial&)_s).y;
  tipo = ((ObjetoSerial&)_s).tipo;
  info1 = ((ObjetoSerial&)_s).info1;
  info2 = ((ObjetoSerial&)_s).info2;
  info3 = ((ObjetoSerial&)_s).info3;
  info4 = ((ObjetoSerial&)_s).info4;
  info5 = ((ObjetoSerial&)_s).info5;
  info6 = ((ObjetoSerial&)_s).info6;
  info7 = ((ObjetoSerial&)_s).info7;
  info8 = ((ObjetoSerial&)_s).info8;
  info9 = ((ObjetoSerial&)_s).info9;
  info10 = ((ObjetoSerial&)_s).info10;
  return *this;
}
#endif

class _Marshaller_ObjetoSerial : public ::CORBA::StaticTypeInfo {
    typedef ObjetoSerial _MICO_T;
  public:
    ~_Marshaller_ObjetoSerial();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_ObjetoSerial::~_Marshaller_ObjetoSerial()
{
}

::CORBA::StaticValueType _Marshaller_ObjetoSerial::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_ObjetoSerial::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_ObjetoSerial::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_ObjetoSerial::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->x ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->y ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->tipo ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info1 ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info2 ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info3 ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info4 ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info5 ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info6 ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info7 ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info8 ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info9 ) &&
    CORBA::_stc_ushort->demarshal( dc, &((_MICO_T*)v)->info10 ) &&
    dc.struct_end();
}

void _Marshaller_ObjetoSerial::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->x );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->y );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->tipo );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info1 );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info2 );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info3 );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info4 );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info5 );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info6 );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info7 );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info8 );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info9 );
  CORBA::_stc_ushort->marshal( ec, &((_MICO_T*)v)->info10 );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_ObjetoSerial;

#ifdef HAVE_EXPLICIT_STRUCT_OPS
Teclado::Teclado()
{
}

Teclado::Teclado( const Teclado& _s )
{
  keys = ((Teclado&)_s).keys;
}

Teclado::~Teclado()
{
}

Teclado&
Teclado::operator=( const Teclado& _s )
{
  keys = ((Teclado&)_s).keys;
  return *this;
}
#endif

class _Marshaller_Teclado : public ::CORBA::StaticTypeInfo {
    typedef Teclado _MICO_T;
  public:
    ~_Marshaller_Teclado();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_Teclado::~_Marshaller_Teclado()
{
}

::CORBA::StaticValueType _Marshaller_Teclado::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_Teclado::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_Teclado::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_Teclado::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stcseq_char->demarshal( dc, &((_MICO_T*)v)->keys ) &&
    dc.struct_end();
}

void _Marshaller_Teclado::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stcseq_char->marshal( ec, &((_MICO_T*)v)->keys );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_Teclado;

#ifdef HAVE_EXPLICIT_STRUCT_OPS
VetorObjetos::VetorObjetos()
{
}

VetorObjetos::VetorObjetos( const VetorObjetos& _s )
{
  vetor = ((VetorObjetos&)_s).vetor;
}

VetorObjetos::~VetorObjetos()
{
}

VetorObjetos&
VetorObjetos::operator=( const VetorObjetos& _s )
{
  vetor = ((VetorObjetos&)_s).vetor;
  return *this;
}
#endif

class _Marshaller_VetorObjetos : public ::CORBA::StaticTypeInfo {
    typedef VetorObjetos _MICO_T;
  public:
    ~_Marshaller_VetorObjetos();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_VetorObjetos::~_Marshaller_VetorObjetos()
{
}

::CORBA::StaticValueType _Marshaller_VetorObjetos::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_VetorObjetos::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_VetorObjetos::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_VetorObjetos::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    _marshaller__seq_ObjetoSerial->demarshal( dc, &((_MICO_T*)v)->vetor ) &&
    dc.struct_end();
}

void _Marshaller_VetorObjetos::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  _marshaller__seq_ObjetoSerial->marshal( ec, &((_MICO_T*)v)->vetor );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_VetorObjetos;


/*
 * Base interface for class IRemote
 */

IRemote::~IRemote()
{
}

void *
IRemote::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:IRemote:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

IRemote_ptr
IRemote::_narrow( CORBA::Object_ptr _obj )
{
  IRemote_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:IRemote:1.0" )))
      return _duplicate( (IRemote_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:IRemote:1.0") || _obj->_is_a_remote ("IDL:IRemote:1.0")) {
      _o = new IRemote_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

IRemote_ptr
IRemote::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_IRemote : public ::CORBA::StaticTypeInfo {
    typedef IRemote_ptr _MICO_T;
  public:
    ~_Marshaller_IRemote();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_IRemote::~_Marshaller_IRemote()
{
}

::CORBA::StaticValueType _Marshaller_IRemote::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_IRemote::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::IRemote::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_IRemote::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_IRemote::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_IRemote::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::IRemote::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_IRemote::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_IRemote;


/*
 * Stub interface for class IRemote
 */

IRemote_stub::~IRemote_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_IRemote::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:IRemote:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_IRemote *
POA_IRemote::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:IRemote:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_IRemote *) p;
  }
  return NULL;
}

IRemote_stub_clp::IRemote_stub_clp ()
{
}

IRemote_stub_clp::IRemote_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

IRemote_stub_clp::~IRemote_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

void IRemote_stub::sendKeys( const Teclado& _par_keys )
{
  CORBA::StaticAny _sa_keys( _marshaller_Teclado, &_par_keys );
  CORBA::StaticRequest __req( this, "sendKeys" );
  __req.add_in_arg( &_sa_keys );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


#ifndef MICO_CONF_NO_POA

void
IRemote_stub_clp::sendKeys( const Teclado& _par_keys )
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_IRemote * _myserv = POA_IRemote::_narrow (_serv);
    if (_myserv) {
      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        _myserv->sendKeys(_par_keys);
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return;
    }
    _postinvoke ();
  }

  IRemote_stub::sendKeys(_par_keys);
}

#endif // MICO_CONF_NO_POA

CORBA::Boolean IRemote_stub::pronto()
{
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "pronto" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifndef MICO_CONF_NO_POA

CORBA::Boolean
IRemote_stub_clp::pronto()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_IRemote * _myserv = POA_IRemote::_narrow (_serv);
    if (_myserv) {
      CORBA::Boolean __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->pronto();
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return __res;
    }
    _postinvoke ();
  }

  return IRemote_stub::pronto();
}

#endif // MICO_CONF_NO_POA

CORBA::Boolean IRemote_stub::acabou()
{
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "acabou" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifndef MICO_CONF_NO_POA

CORBA::Boolean
IRemote_stub_clp::acabou()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_IRemote * _myserv = POA_IRemote::_narrow (_serv);
    if (_myserv) {
      CORBA::Boolean __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->acabou();
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return __res;
    }
    _postinvoke ();
  }

  return IRemote_stub::acabou();
}

#endif // MICO_CONF_NO_POA

ObjetoSerial IRemote_stub::getProximo()
{
  ObjetoSerial _res;
  CORBA::StaticAny __res( _marshaller_ObjetoSerial, &_res );

  CORBA::StaticRequest __req( this, "getProximo" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


#ifndef MICO_CONF_NO_POA

ObjetoSerial
IRemote_stub_clp::getProximo()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_IRemote * _myserv = POA_IRemote::_narrow (_serv);
    if (_myserv) {
      ObjetoSerial __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->getProximo();
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return __res;
    }
    _postinvoke ();
  }

  return IRemote_stub::getProximo();
}

#endif // MICO_CONF_NO_POA

class _Marshaller__seq_ObjetoSerial : public ::CORBA::StaticTypeInfo {
    typedef SequenceTmpl< ObjetoSerial,MICO_TID_DEF> _MICO_T;
  public:
    ~_Marshaller__seq_ObjetoSerial();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller__seq_ObjetoSerial::~_Marshaller__seq_ObjetoSerial()
{
}

::CORBA::StaticValueType _Marshaller__seq_ObjetoSerial::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_ObjetoSerial::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_ObjetoSerial::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller__seq_ObjetoSerial::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( ::CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_ObjetoSerial->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_ObjetoSerial::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( ::CORBA::ULong i = 0; i < len; i++ )
    _marshaller_ObjetoSerial->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

::CORBA::StaticTypeInfo *_marshaller__seq_ObjetoSerial;

struct __tc_init_IREMOTE {
  __tc_init_IREMOTE()
  {
    _marshaller_ObjetoSerial = new _Marshaller_ObjetoSerial;
    _marshaller_Teclado = new _Marshaller_Teclado;
    _marshaller_VetorObjetos = new _Marshaller_VetorObjetos;
    _marshaller_IRemote = new _Marshaller_IRemote;
    _marshaller__seq_ObjetoSerial = new _Marshaller__seq_ObjetoSerial;
  }

  ~__tc_init_IREMOTE()
  {
    delete static_cast<_Marshaller_ObjetoSerial*>(_marshaller_ObjetoSerial);
    delete static_cast<_Marshaller_Teclado*>(_marshaller_Teclado);
    delete static_cast<_Marshaller_VetorObjetos*>(_marshaller_VetorObjetos);
    delete static_cast<_Marshaller_IRemote*>(_marshaller_IRemote);
    delete static_cast<_Marshaller__seq_ObjetoSerial*>(_marshaller__seq_ObjetoSerial);
  }
};

static __tc_init_IREMOTE __init_IREMOTE;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

// PortableServer Skeleton Class for interface IRemote
POA_IRemote::~POA_IRemote()
{
}

::IRemote_ptr
POA_IRemote::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::IRemote::_narrow (obj);
}

CORBA::Boolean
POA_IRemote::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:IRemote:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_IRemote::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:IRemote:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_IRemote::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:IRemote:1.0");
}

CORBA::Object_ptr
POA_IRemote::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::IRemote_stub_clp (poa, obj);
}

bool
POA_IRemote::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    switch (mico_string_hash (__req->op_name(), 7)) {
    case 0:
      if( strcmp( __req->op_name(), "acabou" ) == 0 ) {
        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        __req->set_result( &__res );

        if( !__req->read_args() )
          return true;

        _res = acabou();
        __req->write_results();
        return true;
      }
      break;
    case 2:
      if( strcmp( __req->op_name(), "pronto" ) == 0 ) {
        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        __req->set_result( &__res );

        if( !__req->read_args() )
          return true;

        _res = pronto();
        __req->write_results();
        return true;
      }
      break;
    case 4:
      if( strcmp( __req->op_name(), "sendKeys" ) == 0 ) {
        ::Teclado _par_keys;
        CORBA::StaticAny _sa_keys( _marshaller_Teclado, &_par_keys );

        __req->add_in_arg( &_sa_keys );

        if( !__req->read_args() )
          return true;

        sendKeys( _par_keys );
        __req->write_results();
        return true;
      }
      break;
    case 6:
      if( strcmp( __req->op_name(), "getProximo" ) == 0 ) {
        ::ObjetoSerial _res;
        CORBA::StaticAny __res( _marshaller_ObjetoSerial, &_res );
        __req->set_result( &__res );

        if( !__req->read_args() )
          return true;

        _res = getProximo();
        __req->write_results();
        return true;
      }
      break;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    __req->set_exception( _ex->_clone() );
    __req->write_results();
    return true;
  } catch( ... ) {
    CORBA::UNKNOWN _ex (CORBA::OMGVMCID | 1, CORBA::COMPLETED_MAYBE);
    __req->set_exception (_ex->_clone());
    __req->write_results ();
    return true;
  }
  #endif

  return false;
}

void
POA_IRemote::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}

