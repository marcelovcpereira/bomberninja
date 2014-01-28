#ifndef BOMBA_H
#define BOMBA_H


#include <allegro.h>

#include "objeto2D.h"
#include "IRemote.h"
#include "UltimaTentativa.cpp"



#define NUM_BOMBAS 4


class Bomba : public Objeto2D{

      private:
			  BITMAP *array[NUM_BOMBAS];
              int nextImage;
              volatile int *cronometro;
              int forca;
              int ultimoTempo;
              int tempoInicial;
              bool destruida;
			  int incrementador;
              static const int intervaloExplosao = 3300; // 3.3segundos
              static const int intervaloImagens = 500; //0.5 segundos 

      public:
             
             Bomba( BITMAP *a[NUM_BOMBAS] ){
                    for( int i = 0; i < NUM_BOMBAS; i++ ){
                         array[ i ] = a[ i ]; 
                    }      
                    nextImage = 0; 
                    destruida = false;
                    incrementador = 1;
             }
             
             void setCronometro( volatile int *t ){
                  this -> cronometro = t;
                  this -> ultimoTempo = *cronometro;
                  this -> tempoInicial = ultimoTempo;
             }
             
             int getForca(){
                 //return this -> forca;
				 _asm {
					 mov eax, dword ptr[this]
					 mov eax, dword ptr[eax+4*NUM_BOMBAS+8+28]
				 }
             }
             
             void setForca( int f ){
                  //this -> forca = f;
				 _asm {
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[f]
					 mov dword ptr [eax+4*NUM_BOMBAS+8+28], ecx
				 }
             }
             
             void incrementNextImage(){
                  /*if( nextImage == NUM_BOMBAS - 1)
                      incrementador = -1;
                  else if( nextImage == 0 )
                       incrementador = 1;
                  nextImage += incrementador;*/
				 _asm {
					 mov eax, dword ptr[this]
					 mov ecx, NUM_BOMBAS
					 dec ecx
					 cmp dword ptr [eax+4*NUM_BOMBAS+28], ecx
					 jne diferente
					 mov dword ptr [eax+4*NUM_BOMBAS+24+28], -1
					 jmp endif
		diferente:	 cmp dword ptr [eax+4*NUM_BOMBAS+28], 0
					 jne endif
					 mov dword ptr [eax+4*NUM_BOMBAS+24+28], 1
		endif:		 mov ecx, dword ptr [eax+4*NUM_BOMBAS+28]
					 add ecx, dword ptr [eax+4*NUM_BOMBAS+24+28]
					 mov dword ptr [eax+4*NUM_BOMBAS+28], ecx
				 }                  
             }
             
             bool isDestruida(){
                  //return destruida;
				  _asm {
					 mov eax, dword ptr[this]
					 mov al, byte ptr[eax+4*NUM_BOMBAS+20+28]
				 }
             }
             
             void setDestruida( bool b ){
                  //this -> destruida = b;
				 _asm {
					 mov eax, dword ptr[this]
					 mov cl, byte ptr[b]
					 mov byte ptr [eax+4*NUM_BOMBAS+20+28], cl
				 }
             }
             
             void paint( BITMAP *b, int tempo ){
                  masked_blit( array[nextImage] , b , 0, 0, getX(), getY(),getLargura(),getAltura());
                  if( tempo - tempoInicial >= intervaloExplosao ){
                      destruida = true;
                  }
                  if( tempo - ultimoTempo >= intervaloImagens ){
                      incrementNextImage();
                      ultimoTempo = *cronometro;
                  }
             }
             
             const char *getNome(){
                   return "Bomba";
             }
             
             int getTipo(){
             return 2;
             }
                     
              UltimaTentativa *getSerial(){
				UltimaTentativa *o = new UltimaTentativa();
				o -> x = getX();
				o -> y = getY();
				o -> tipo = 20;
				o -> info1 = this-> nextImage;
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

			 ObjetoSerial getSerializable(){
				 ObjetoSerial serial;
				 setSerial(serial);
				 return serial;
				 
			 }

			 void setSerial( ObjetoSerial &serial){
				 /*serial.info.length(10);
			     serial.x = (CORBA::UShort) getX();
				 serial.y = (CORBA::UShort) getY();
				 serial.tipo =(CORBA::UShort)0;
				 serial.info[0] = (CORBA::UShort) nextImage;*/

			 }


			/* UltimaTentativa *ultima(){
				 int i[10];
				 i[0] = nextImage; 
				UltimaTentativa *t ;
					t = new UltimaTentativa(getX(),getY(),0,i);
				return t;
			 }*/

};

#endif