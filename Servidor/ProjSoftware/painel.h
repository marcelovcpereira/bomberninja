#ifndef PAINEL_H
#define PAINEL_H


#include <allegro.h>
#include "UltimaTentativa.cpp"

class Painel :public Objeto2D{
      
      private:
              
              volatile int * tempo;
              bool terminou;
              int ultimoTempo;
              int tempoInicial;
              int intervalo;
              
      public:
             Painel(){
             
             }
             
             Painel( BITMAP * img,volatile int * tmp ){
                   setImagem( img );
                   this->setCronometro(tmp);
                   this->setBounds(0,0,600,200);
                   this->setTerminou(false);
                   setIntervalo( 0 );
                   
             }
             
             Painel(const char * url, volatile int * tmp ){
                   setImagem( load_bitmap( url, NULL ) );
                   this->setCronometro(tmp);
                   this->setBounds(0,0,600,200);
                   this->setTerminou(false);
                   setIntervalo( 0 );
             }
             
             int getIntervalo(){
                 return this-> intervalo;
             }
             
             void setIntervalo( int v ){
                  if( v >= 0 ){
                     this -> intervalo = v;
                  }else{
                     this -> intervalo = 0;
                  }
             }
             
             
             bool jaTerminou(){
                  return this->terminou;
             }
             
             void setTerminou(bool t){
                  this->terminou = t;
             }
             
             virtual const char * getNome(){
                  return "Painel";
             }
             void setCronometro(volatile int * t){
              this -> tempo = t;
              this-> ultimoTempo = * tempo;
              this->tempoInicial = ultimoTempo;
             }
             
             int getTempo(){
                 return *tempo;
             }
             
             void setUltimoTempo( int uT ){
                   this -> ultimoTempo = uT;
             }
             
             int getUltimoTempo(){
                  return this-> ultimoTempo;
             }
             
             int getTempoInicial(){
                  return this -> tempoInicial;
             }
             
             void setTempoInicial( int tI ){
                  this -> tempoInicial = tI;
             }
             
             
             virtual void paint(BITMAP *bitmap){
                 masked_blit(  getImagem() , bitmap, 0 , 0, getX(), getY(),getLargura(),getAltura() ); 
             } 

			 virtual ObjetoSerial getSerializable() = 0;
			 virtual UltimaTentativa *getSerial() = 0;
              
};


class PainelHurry: public Painel{
     
        public:
               
               
               
               PainelHurry(  BITMAP * img,volatile int * tmp ):
                             Painel( img, tmp ){
                    this -> setIntervalo( 10000 );
                    setBounds(-445,200,445,80);
               }
               
               PainelHurry( const char * url, volatile int * tmp ):
                            Painel( url, tmp ){
                    this -> setIntervalo( 10000 );
                    setBounds(-445,200,445,80);
               }
               
               const char *getNome(){
                 return "PainelHurry";
               }
               
               void paint( BITMAP *b ){
                    if( getTempo() - getTempoInicial() <= getIntervalo() ){
                         setX( getX() + 3 );
                    }else{
                        setTerminou( true );
                    }
                    
                    Painel::paint( b );
               }

		 ObjetoSerial getSerializable(){
				 ObjetoSerial serial;
				 setSerial(serial);
				 return serial;
				 
			 }

		     UltimaTentativa *getSerial(){
				UltimaTentativa *o = new UltimaTentativa();
				o -> x = getX();
				o -> y = getY();
				o -> tipo = 17;
				o -> info1 = 0;
				o -> info2 = 0;
				o -> info3 = 0;
				o -> info4 = 0;
				o -> info5 = 0;
				o -> info6 = 0;
				o -> info7 = 0;
				o -> info8 = 0;
				o -> info9 = 0;
				o -> info10 = 0;
				return o;
			}

			 void setSerial( ObjetoSerial &serial){
				/* serial.info.length(10);
			     serial.x = (CORBA::UShort) getX();
				 serial.y = (CORBA::UShort) getY();
				 serial.tipo =(CORBA::UShort)17;*/

			 }
               
               

};

class PainelVida: public Painel{
   
   public:
               
               
               
               PainelVida(  BITMAP * img,volatile int * tmp ):
                             Painel( img, tmp ){
                    this -> setIntervalo( 1500 );
                    setBounds(150,150,600,200);
               }
               
               PainelVida( const char * url, volatile int * tmp ):
                            Painel( url, tmp ){               
                    this -> setIntervalo( 1500 );
                    setBounds(150,150,600,200); 
               }
               
               void paint( BITMAP *b ){
                    if( getTempo() - getTempoInicial() >= getIntervalo() ){
                        setTerminou( true );
                    }
                    
                    Painel::paint( b );
               }
               
                const char *getNome(){
                 return "PainelVida";
               }


		ObjetoSerial getSerializable(){
				 ObjetoSerial serial;
				 setSerial(serial);
				 return serial;
				 
			 }

		UltimaTentativa *getSerial(){
				UltimaTentativa *o = new UltimaTentativa();
				o -> x = getX();
				o -> y = getY();
				o -> tipo = 18;
				o -> info1 = 0;
				o -> info2 = 0;
				o -> info3 = 0;
				o -> info4 = 0;
				o -> info5 = 0;
				o -> info6 = 0;
				o -> info7 = 0;
				o -> info8 = 0;
				o -> info9 = 0;
				o -> info10 = 0;
				return o;
			}
			 void setSerial( ObjetoSerial &serial){
				 /*serial.info.length(10);
			     serial.x = (CORBA::UShort) getX();
				 serial.y = (CORBA::UShort) getY();
				 serial.tipo =(CORBA::UShort)18;*/

			 }
               
               
};


class PainelTimeUp : public Painel{
      
      public:
             PainelTimeUp(BITMAP *img, volatile int *tmp):Painel( img, tmp ){
                          setIntervalo(1500);
                          setBounds(200,200,370,800);
             }
             
             PainelTimeUp(const char *url, volatile int *tmp):Painel( url, tmp ){
                          setIntervalo(1500);
                          setBounds(200,200,370,80);
             }
             
            void paint( BITMAP *b ){
                   if( getTempo() - getTempoInicial() >= getIntervalo() ){
                    setTerminou( true );
                    }
                       Painel::paint( b );
               }
               
                const char *getNome(){
                 return "PainelTimeUp";
               }

			ObjetoSerial getSerializable(){
				 ObjetoSerial serial;
				 setSerial(serial);
				 return serial;
				 
			 }

			UltimaTentativa *getSerial(){
				UltimaTentativa *o = new UltimaTentativa();
				o -> x = getX();
				o -> y = getY();
				o -> tipo = 19;
				o -> info1 = 0;
				o -> info2 = 0;
				o -> info3 = 0;
				o -> info4 = 0;
				o -> info5 = 0;
				o -> info6 = 0;
				o -> info7 = 0;
				o -> info8 = 0;
				o -> info9 = 0;
				o -> info10 = 0;
				return o;
			}

			 void setSerial( ObjetoSerial &serial){
				 /*serial.info.length(10);
			     serial.x = (CORBA::UShort) getX();
				 serial.y = (CORBA::UShort) getY();
				 serial.tipo =(CORBA::UShort)19;*/

			 }
};
#endif