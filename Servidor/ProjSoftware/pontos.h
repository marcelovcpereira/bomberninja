#ifndef PONTOS_H
#define PONTOS_H


#include <allegro.h>
#include "UltimaTentativa.cpp"



#ifndef OBJETO2D_H
#include "objeto2D.h"
#endif


class Pontos: public Objeto2D{

      private:
              BITMAP *imagem;
			  int pontos;
              bool acabou;
              volatile int *cronometro;
              int ultimoTempo;
              bool t;
              static const int intervaloFumaca = 600;
      public:
             Pontos( BITMAP *im, int x, int y, volatile int *te, int p){
                      this -> imagem = im;
                      acabou = false;
                      setX( x );
                      setY( y );
                      this -> cronometro = te;
                      this -> ultimoTempo = *te;
                      t = true;
					  this -> pontos = p;
             }
             
             void paint( BITMAP *b ){
                  if( *cronometro - ultimoTempo <= intervaloFumaca ){
                      if (t){
                         this -> setY(this ->getY() - 1);
                      }
                      t = !t;
                      //this -> setX(this ->getX() + 3);
                  }else{
                        acabou = true;
                  }
                  
                  masked_blit(  imagem , b,
                               0, 0, getX(), getY(),
                               40,40 );
             }
             
                          
             const char *getNome(){
                   return "Pontos";
             }
             
             int getTipo(){
                 
             return 5;
             }
             
           bool jahAcabou (){
                  return acabou;
             }

            UltimaTentativa *getSerial(){
				UltimaTentativa *o = new UltimaTentativa();
				o -> x = getX();
				o -> y = getY();
				o -> tipo = 8;
				o -> info1 = this->pontos;
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
			    /* serial.x = (CORBA::UShort) getX();
				 serial.y = (CORBA::UShort) getY();
				 serial.tipo =(CORBA::UShort)8;
				 serial.info[0] = (CORBA::UShort) pontos;*/

			 }
      
};
#endif