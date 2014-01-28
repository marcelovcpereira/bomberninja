#ifndef TILE_H
#define TILE_H

#include <allegro.h>

#include "objeto2D.h"
#include "UltimaTentativa.cpp"



/*
 * Classe Abstrata que representa um TILE da tela
 */
class Tile: public Objeto2D{

      private: BITMAP *imagem; //imagem do tile
      private: int tipo; // inteiro que representa o tipo do TILE

      public:
              Tile(){}

              Tile( BITMAP *img ){
                    this -> imagem = img;
              }
              /*
              ~Tile(){
              free(imagem);
              }*/

			  //método virtual abstrato que será reescrito pelos subtipos
              virtual void paint( BITMAP *b ) = 0;

              BITMAP *getImagem(){
                     return this -> imagem;
              }

              int getTipo(){
                  return this -> tipo;
              }

              void setTipo( int t){
                  tipo = t;
              }
              
              const char *getNome(){
                   return "Tile";
             }

			 virtual UltimaTentativa *getSerial() = 0;


};

/*
 * Classe que representa um Tile bloqueador
 */
class BlockTile: public Tile{

      public:
             BlockTile(){setTipo(2);}
             BlockTile( BITMAP *b ):Tile( b ){setTipo(2);}

             void paint( BITMAP *b ){
                  masked_blit( getImagem() , b, 0, 0, getX(), getY(), getLargura(),
                               getAltura() );
             }
             
             const char *getNome(){
                   return "BlockTile";
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
				o -> tipo = 14;
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
				 serial.tipo =(CORBA::UShort)14;*/
			 }

};


/*
 * Classe que representa um Tile do chão
 */
class FloorTile: public Tile{

      public:
            FloorTile(){setTipo(0);}
            FloorTile( BITMAP *b ):Tile( b ){setTipo(0);}

             void paint( BITMAP *b ){
                  masked_blit( getImagem() , b, 0, 0, getX(), getY(), getLargura(),
                               getAltura() );
             }
             
             const char *getNome(){
                   return "FloorTile";
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
				o -> tipo = 15;
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
				 serial.tipo =(CORBA::UShort)15;*/

			 }

};


/*
 * Classe que representa um Tile parede(quevrável)
 */
class WallTile : public Tile{

      private:
              int estado;  //estado que indicará se está sendo destruido(temporário)
              static const int NORMAL = 0;
              static const int DESTRUINDO = 1;
              static const int DESTRUIDO = 2;
      public:

             WallTile(){ setTipo(1); }
             WallTile( BITMAP *b ):Tile( b ){ setTipo(1); }

             void paint( BITMAP *b ){
                  masked_blit(getImagem() ,b ,0 ,0 ,getX() , getY(), getLargura(),
                                          getAltura() );
             }
             int getEstado(){
                 return this -> estado;
             }

             void setEstado( int i ){
                  this -> estado = i;
             }
             
             const char *getNome(){
                   return "WallTile";
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
				o -> tipo = 16;
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
/*				 serial.info.length(10);
			     serial.x = (CORBA::UShort) getX();
				 serial.y = (CORBA::UShort) getY();
				 serial.tipo =(CORBA::UShort)16;*/

			 }


};
#endif