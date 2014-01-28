
#ifndef PORTAL_H
#define PORTAL_H



#include <allegro.h>

#include "objeto2D.h"


class Portal: public Objeto2D{

      private:
              bool aberto;


  public:
         Portal(){
			 aberto = false;
			 setImagem( NULL );
			 setBounds(0,0,0,0);

         }
         
         Portal( BITMAP *img , int x, int y ){
            aberto = false;
            this ->setImagem( img );
            this -> setBounds( x, y, 40, 40 );
         }
         
         int getTipo(){
             return 4;
         }
         
         void paint( BITMAP *b ){
                masked_blit( getImagem() , b, 0, 0, getX(), getY(), getAltura(), getLargura() );
         }
         
         bool isAberto(){
              return aberto;
         }
         
         void setAberto(bool b){
              aberto = b;
         }


		 ObjetoSerial getSerializable(){
				 ObjetoSerial serial;
				 setSerial(serial);
				 return serial;
				 
			 }

		void setSerial( ObjetoSerial &serial){
				/* serial.info.length(10);
			     serial.x = (CORBA::UShort) getX();
				 serial.y = (CORBA::UShort) getY();
				 serial.tipo =(CORBA::UShort)13;
				 serial.info[0] = (CORBA::UShort) aberto;*/

			 }


};
#endif