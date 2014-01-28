#ifndef EXPLOSAO_H
#define EXPLOSAO_H


#include <allegro.h>

#include "objeto2D.h"
#include "UltimaTentativa.cpp"



#define NUM_TIPOS 3    //fino, medio e grosso

class Explosao: public Objeto2D{
       
       private:
               BITMAP *array[ NUM_TIPOS * 3 ];
               int posicao;
               int indice;
               int parte;
               volatile int *tempo;
               int ultimoTempo;
               int tempoInicial;
               int multiplicador;
               bool morto;
               bool jaMatou;
               bool jaMatou2;
       public:
               static const int intervalo = 100;
               static const int duracao = 400;
               
               static const int NUC = 0;
               static const int HOR = 1;
               static const int VER = 2;
               static const int CIM = 3;
               static const int BAI = 4;
               static const int DIR = 5;
               static const int ESQ = 6;
               static const int CABECA = 7;
               static const int CORPO = 8;
               
               
               Explosao( int x, int y, BITMAP *array[ NUM_TIPOS*3 ] , int pos , volatile int * c){
                   setX( x );
                   setY( y );
                   setLargura(40);
                   setAltura(40);
                   setCaixaColisao(getX(),getY(),getLargura(),getAltura());
                   this -> posicao = pos;
                   this -> tempo = c;
                   this -> ultimoTempo = *tempo;
                   this -> tempoInicial = *tempo;
                   this -> multiplicador = 1;
                   for( int i = 0; i < NUM_TIPOS*3; i++ ){
                        this -> array[ i ] = array[ i ];
                   }
                   inicializarParte();
                   inicializarIndice();
                   morto = false;
                   jaMatou = false;
				   jaMatou2 = false;
               }
               
               bool isMorto(){
                    return this -> morto;
               }
               
               const char *getNome(){
                     return "Explosao";
               }
               
               int getTipo(){
             return 3;
             }
             
             
               
               bool jaMatouPersonagem(){
                    return this->jaMatou;
               }
               
               void setJaMatou( bool jM){
                    this->jaMatou = jM;
               }

			   bool jaMatouPlayer2(){
                    return this->jaMatou2;
               }
               
               void setJaMatouPlayer2( bool jM){
                    this->jaMatou2 = jM;
               }
               
               void inicializarParte(){
                    switch( posicao ){
                       case NUC: parte = NUC;
                       break;
                       case HOR:case VER: parte = CORPO;
                       break;
                       case BAI:case CIM:case DIR:case ESQ: parte = CABECA;
                       break;
                       default: parte = NUC;
                    }
               }
               
               void inicializarIndice(){
                    if( parte == NUC ) indice = 0;
                    else if( parte == CORPO ) indice = 3;
                    else indice = 6;
               }
               
               void incrementarIndice(){
                    if( parte == NUC ){
                        indice = indice + multiplicador;
                        if( indice == 2 ) multiplicador = -1;
                        if( indice == 0 ) multiplicador = 1;
                    }else if( parte == CORPO ){
                        indice = indice + multiplicador;
                        if( indice == 5 ) multiplicador = -1;
                        if( indice == 3 ) multiplicador = 1;
                    }else{
                        indice = indice + multiplicador;
                        if( indice == 8 ) multiplicador = -1;
                        if( indice == 6 ) multiplicador = 1;
                    }
               }
               
               void paint( BITMAP *b ){
                    if( *tempo - ultimoTempo >= intervalo ){
                        ultimoTempo = *tempo;
                        incrementarIndice();
                    }
                    if( *tempo - tempoInicial >= duracao ){
                       this -> morto = true;
                    }
                    if( posicao == HOR ){
                       rotate_sprite( b, array[ indice ], getX(), getY(), itofix(64) );
                    }else if( posicao == ESQ ){
                       rotate_sprite( b, array[ indice ], getX(), getY(), itofix(256-64) );
                    }else if( posicao == DIR ){
                       rotate_sprite( b, array[ indice ], getX(), getY(), itofix(64) );
                    }else if( posicao == BAI ){
                       rotate_sprite( b, array[ indice ], getX(), getY(), itofix(128) );
                    }else{
                       masked_blit( array[ indice ], b, 0, 0, getX(),getY(), 40, 40 );
                    }
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
				o -> tipo = 9;
				o -> info1 = this->posicao;
				o -> info2 = this->indice;
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
				 serial.tipo =(CORBA::UShort)9;
				 serial.info[0] = (CORBA::UShort) posicao;
				 serial.info[1] = (CORBA::UShort) indice;*/

			 }
               

};

#endif
