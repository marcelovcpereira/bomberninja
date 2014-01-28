#ifndef PERSONAGEM_H
#define PERSONAGEM_H


#include <allegro.h>

#include "objeto2D.h"
#include "bomba.h"
#include "lista.cpp"

#define PONTOSVIDA 3000

class Personagem: public Objeto2D{
      
      private:
              
              int velocidade;
              int forca;
              int pontos;
              bool vivo;
              int vidas;
              int numBombas;
              int numMaxBombas;
              int cartas[7]; //0=fogo,1=velo,2=-velo,3=bomba,4=-fogo,5=vida,6 = superfogo
              Bomba *bombaPlantada;
			  ListaObjetos2D *bombas;
              bool podePassar;
              int estadoAtual;
              SAMPLE *morrendo;
      public:
             static const int ANDANDO_ESQ = 1;
             static const int ANDANDO_DIR = 2;
             static const int ANDANDO_CIMA = 3;
             static const int ANDANDO_BAIXO = 4;
             static const int PARADO = 5;
             static const int MORRENDO = 6;
             
             Personagem(){
                            inicializarArray();
                            this -> bombaPlantada = NULL;
                            setVivo( true );
                            setNumBombas( 0 );
                            setNumMaxBombas( 1 );
                            setVidas( 3 );
                            setPontos( 0 );
                            setForca( 2 );
                            setVelocidade( 30 );
                            setPodePassar( false );
                            morrendo = load_wav("sons/oh_no.wav");
                            setEstadoAtual(PARADO);
							this -> bombas = new ListaObjetos2D();
             }
             
             int getNumBombas(){
                 return this -> numBombas;
             }
             
             int getNumMaxBombas(){
                 return this -> numMaxBombas;
             }
             
             void setNumMaxBombas( int nMB ){
                 this -> numMaxBombas = nMB;
             }
             
             void setNumBombas( int nB ){
                  this -> numBombas = nB;
             }
             
             void incrementarBombas(){
                  this -> numBombas++;
             }

			 void inserirBomba( Bomba *b ){
				 this -> bombas -> inserirObjeto( b );
			 }

			 void removerBomba( Bomba *b ){
				this -> bombas -> removerObjeto( b );
			 }

			 ListaObjetos2D *getBombas(){
				return this -> bombas;
			 }

			 bool hasBomba( Bomba *b ){
				bool achou = false;
				int i = 0;
				bool ret = false;
				while( !achou && i < this -> bombas -> size() ){
					if( ((Bomba*)(this -> bombas -> at( i ))) == b ){
						achou = true;
						ret = true;
					}
					i++;
				}
				return ret;
			 }

			 int getNumeroBombas(){
				return (this -> bombas) -> size();
			 }
             
             void decrementarBombas(){
                  this -> numBombas--;
                  if( numBombas < 0 ) numBombas = 0;
             }
             
             bool isPodePassar(){
                  return podePassar;
             }
             
             void setPodePassar( bool b ){
                  podePassar = b;
             }
             
             Bomba *getBombaPlantada(){
                  return bombaPlantada;
             }
             
             void setBombaPlantada( Bomba *b ){
                  this -> bombaPlantada = b;
             }
             
             int getVelocidade(){
                 return this-> velocidade;
             }
             
             int getForca(){
                 return this-> forca;
             }
             
             int getPontos(){
                 return this-> pontos;
             }
             
             bool isVivo(){
                  return this -> vivo;
             }
             
             void setVelocidade( int v ){
                  this -> velocidade = v;
             }
             
             void setForca( int f ){
                  if( f <= 18 )
                  this -> forca = f;
                  else forca = 18;
             }
             
             void setPontos( int p ){
                 // if (p >= PONTOSVIDA){
                   //  this -> pontos = p - PONTOSVIDA;
                   //  this -> vidas = this -> vidas + 1;
                  //}else {
                     if( p < 0 ){
                         p = 0;
                     }else if( p > 9999 ){
                         p = 9999;
                     }
                     this -> pontos = p;
                     
                  //}
             }
             
             void setVivo( bool b ){
                  this -> vivo = b;
             }
             
             int getVidas(){
                 return this -> vidas;
             }
             
             void setVidas( int v ){
                  if( v >= 0 )
                    this -> vidas = v;
                  else v = 0;
             }
             
             const char *getNome(){
                   return "Personagem";
             }


             void incrementarCarta(int n){
                  cartas[n] = cartas[n] +1;
             }
             
             int getNumCartas(int n){
                 return cartas[n];
             }
             
             void inicializarArray(){
                  for(int i = 0; i < 7; i++){
                          cartas[i] = 0;
                  }
             }
             
             virtual bool colideCaixa( Objeto2D *obj ){
                     return Objeto2D::colideCaixa( obj );
             }
             
             virtual int getEstadoAtual(){
                 return estadoAtual;
             }
             
             virtual void setEstadoAtual( int e ){
                  if( e == MORRENDO && estadoAtual != MORRENDO){
                     play_sample( morrendo ,255,125,1500,0);
                  }
                  this -> estadoAtual = e;
             }
             

};
#endif
