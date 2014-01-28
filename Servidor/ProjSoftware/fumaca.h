#ifndef FUMACA_H
#define FUMACA_H


#include <allegro.h>

#include "objeto2D.h"
#include "UltimaTentativa.cpp"

#define NUM_FUMACA 3

class Fumaca: public Objeto2D{

      private:
              BITMAP *arrayFumaca[NUM_FUMACA];
              bool morreu;
              int imagemAtual;
              volatile int *cronometro;
              int ultimoTempo;
              static const int intervaloFumaca = 100; //0.1 segundo
      public:
             Fumaca( BITMAP *array[NUM_FUMACA], int x, int y, volatile int *t ){
                      for(int i = 0; i < NUM_FUMACA; i++ ){
                              this -> arrayFumaca[ i ] = array[ i ];
                      }
                      morreu = false;
                      imagemAtual = 0;
                      setX( x );
                      setY( y );
                      this -> cronometro = t;
                      this -> ultimoTempo = *t;
             }
             
             void paint( BITMAP *b ){
                  if( *cronometro - ultimoTempo >= intervaloFumaca ){
                      ultimoTempo = *cronometro;
                      imagemAtual++;
                  }
                  if(imagemAtual == 2){
                        morreu = true;         
                  }
                  if(imagemAtual > 2){
                        imagemAtual = 2;
                  }
                  masked_blit( arrayFumaca[ imagemAtual ], b,
                               0, 0, getX(), getY(),
                               40,40 );
             }
             
             bool isMorto(){
                  return morreu;
             }
             
             const char *getNome(){
                   return "Fumaca";
             }
             
             int getTipo(){
                 
             return 1;
             }

               UltimaTentativa *getSerial(){

				UltimaTentativa *o = new UltimaTentativa();
				o -> x = getX();
				o -> y = getY();
				o -> tipo = 10;
				o -> info1 = this-> imagemAtual;
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
				 serial.tipo =(CORBA::UShort)10;
				 serial.info[0] = (CORBA::UShort) imagemAtual;*/

			 }
             
             
      
};

#endif
