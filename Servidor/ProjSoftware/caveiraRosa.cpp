
#ifndef CAVEIRA_ROSA_H
#define CAVEIRA_ROSA_H


#include <allegro.h>

#include "monstro.h"

#define NUM_IMAGEM  25


class CaveiraRosa :public Monstro{
      private:
              BITMAP *arrayImagens[NUM_IMAGEM];
              int estadoAtual;
              int indiceAtual;
              int ultimoTempo;
              int tempoInicial;
              volatile int *tempoAtual;
              static const int intervalo = 80;
      
      public:
             static const int PARADO = 0;
             static const int ANDANDO_DIREITA = 1;
             static const int ANDANDO_ESQUERDA = 2;
             static const int ANDANDO_CIMA = 3;
             static const int ANDANDO_BAIXO = 4;
             
             CaveiraRosa(){
                  this->indiceAtual = 0;
                  this->estadoAtual = PARADO;
                  setVelocidade(10);  
                  setPontos(300);  
                  setVivo(true);         
             }
             
             CaveiraRosa(BITMAP *arrayI[NUM_IMAGEM], volatile int * tempo,int dir){
                  for(int i = 0; i < NUM_IMAGEM; i++){
                     this->arrayImagens[i] = arrayI[i];
                  }
                  this->indiceAtual = 0;
                  this->estadoAtual = PARADO;
                  setCronometro( tempo );
                  setDirecao( dir );
                  setVelocidade(10);  
                  setPontos(300); 
                  setVivo(true);
             }
              
             void setCronometro(volatile int *t){
                  this->tempoAtual = t;
                  this->tempoInicial = *tempoAtual;
                  this->ultimoTempo = this->tempoInicial;       
              }
              
              void setBounds( int x, int y, int l, int a ){
                  setX( x );
                  setY( y );
                  setLargura( l );
                  setAltura( a );
                  setCaixaColisao(getX()+3,getY()+3,l-6,a-3);
             }
             
             void andarDireita(){
                  if(this->estadoAtual != ANDANDO_DIREITA){
                      this->indiceAtual = 17;
                  }
                  if(*tempoAtual - ultimoTempo >= intervalo){
                        if(this->estadoAtual != ANDANDO_DIREITA){
                            this->indiceAtual = 17;
                         } else{
                        this->indiceAtual++;
                        if(this->indiceAtual == 25){
                            this -> indiceAtual = 17;                 
                        } 
                  } 
                  ultimoTempo = *tempoAtual;    
                  }
                   this->estadoAtual = ANDANDO_DIREITA;
                   this->setX (getX() + getVelocidade()/10);
                   getCaixaColisao() -> incrementarX(getVelocidade()/10);
                  }
              
             void andarEsquerda(){
             if(this->estadoAtual != ANDANDO_ESQUERDA){
                this->indiceAtual = 9;
             }
             if(*tempoAtual - ultimoTempo >= intervalo){
                       if(this->estadoAtual != ANDANDO_ESQUERDA){
                            this->indiceAtual = 9;
                         } else{
                        this->indiceAtual++;
                        if(this->indiceAtual == 17){
                            this -> indiceAtual = 9;                 
                        } 
             }
             ultimoTempo = *tempoAtual;
             }
             this->estadoAtual = ANDANDO_ESQUERDA;
             this->setX (getX() - getVelocidade()/10);
             getCaixaColisao() -> incrementarX(-(getVelocidade()/10));
             }
             
             void andarCima(){
                   if(this->estadoAtual != ANDANDO_CIMA){
                      this->indiceAtual = 8;
                  }
                  if(*tempoAtual - ultimoTempo >= intervalo){
                        if(this->estadoAtual != ANDANDO_CIMA){
                            this->indiceAtual = 8;
                         } 
                         ultimoTempo = *tempoAtual; 
                  } 
                   this->estadoAtual = ANDANDO_CIMA;
                   this->setY (getY() - getVelocidade()/10);
                   getCaixaColisao() -> incrementarY(-(getVelocidade()/10));
             }
             
              
             void andarBaixo(){
                   if(this->estadoAtual != ANDANDO_BAIXO){
                      this->indiceAtual = 0;
                  }
                  if(*tempoAtual - ultimoTempo >= intervalo){
                        if(this->estadoAtual != ANDANDO_BAIXO){
                            this->indiceAtual = 0;
                         } else{
                        this->indiceAtual++;
                        if(this->indiceAtual == 8){
                            this -> indiceAtual = 0;                 
                        } 
                  } 
                  ultimoTempo = *tempoAtual;    
                  }
                   this->estadoAtual = ANDANDO_BAIXO;
                   this->setY (getY() + getVelocidade()/10);
                    getCaixaColisao() -> incrementarY(getVelocidade()/10);
             }
             
             void parar(){
                  if(this->estadoAtual == ANDANDO_DIREITA){
                    this->indiceAtual = 17;
                  }else if(this->estadoAtual == ANDANDO_ESQUERDA){
                           this->indiceAtual = 9;
                        }else if(this->estadoAtual == ANDANDO_CIMA){
                              this->indiceAtual = 8;
                              }else if(this->estadoAtual == ANDANDO_BAIXO){
                                    this->indiceAtual = 0;
                                    }
                  this->estadoAtual = PARADO;
             }
             
               bool colideCaixa( int x ,int  y, int largura, int altura  ){
                  if( this -> getX() > x + largura ) return false;
                  if( this -> getY() > y + altura ) return false;
                  if( this -> getX() + this -> getLargura() < x ) return false;
                  if( this -> getY() + this -> getAltura() < y ) return false;
                  return true;
               }
               
             void paint( BITMAP *bitmap ){
                  masked_blit( arrayImagens[ indiceAtual ],bitmap,
                               0,0,
                               getX(),getY(),
                               getLargura(), getAltura() );   
                               
                               /*int x = getCaixaColisao() -> getX();
                               int y = getCaixaColisao() -> getY();
                               int x2 = x + getCaixaColisao() ->getLargura();
                               int y2 = y + getCaixaColisao()->getAltura();
                              rect( bitmap,x,y,x2,y2,makecol(255,255,255));*/  
             }  
      
      };
#endif