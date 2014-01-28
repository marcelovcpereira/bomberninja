#ifndef MONSTRO_VERDE_H
#define MONSTRO_VERDE_H


#include <allegro.h>

#include "monstro.h"




#define NUM_IMAGENS  32
class MonstroVerde : public Monstro{
      private:
              BITMAP *arrayImagens[NUM_IMAGENS];
              int indiceAtual;
              int estadoAtual;
              volatile int *tempoAtual;
              int ultimoTempo;
              static const int intervalo = 120;//decimos de segundo 
              int tempoInicial;
              
      public:
             static const int PARADO = 0;
             static const int ANDANDO_DIREITA = 1;
             static const int ANDANDO_ESQUERDA = 2;
             static const int ANDANDO_CIMA =3;
             static const int ANDANDO_BAIXO = 4;
             
             
             MonstroVerde(BITMAP *arrayI[NUM_IMAGENS],volatile int *t, int dir){
                for(int i = 0; i < NUM_IMAGENS;i++){
                     this->arrayImagens[i] = arrayI[i];
                }
                this-> indiceAtual = 0;
                this->estadoAtual = PARADO;
                setVelocidade( 10 );
                setPontos(200);
                setVivo(true);
                 setCronometro(t);
                setDirecao(dir);
             
             }
             
             MonstroVerde(volatile int *t){
                 setVelocidade( 10 );
                 this->estadoAtual = PARADO;
                 this->indiceAtual = 0;
                 setPontos(200);
                  setVivo(true);
                  carregarMonstroVerde();
                  setCronometro(t);
                  setDirecao(Monstro::horizontal);
             }
             
             void setBounds( int x, int y, int l, int a ){
                  setX( x );
                  setY( y );
                  setLargura( l );
                  setAltura( a );
                  setCaixaColisao(getX()+5,getY()+30,l-10,a-30);
             }
       
             void setCronometro(volatile int *t){
                  this->tempoAtual = t;
                  this->tempoInicial = *tempoAtual;
                  this->ultimoTempo = this->tempoInicial;
             }
             
             void setVivo( bool b ){
                  Monstro::setVivo( b );
             }
             void andarDireita(){
                  if(this->estadoAtual != ANDANDO_DIREITA){
                      this->indiceAtual = 25;
                  }
                  if(*tempoAtual - ultimoTempo >= intervalo){
                        if(this->estadoAtual != ANDANDO_DIREITA){
                            this->indiceAtual = 25;
                         } else{
                        this->indiceAtual++;
                        if(this->indiceAtual == 32){
                            this -> indiceAtual = 25;                 
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
                this->indiceAtual = 18;
             }
             if(*tempoAtual - ultimoTempo >= intervalo){
                       if(this->estadoAtual != ANDANDO_ESQUERDA){
                            this->indiceAtual = 18;
                         } else{
                        this->indiceAtual++;
                        if(this->indiceAtual == 25){
                            this -> indiceAtual = 18;                 
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
                      this->indiceAtual = 10;
                  }
                  
                    
                  if(*tempoAtual - ultimoTempo >= intervalo){
                                 
                        if(this->estadoAtual != ANDANDO_CIMA){
                            this->indiceAtual = 10;
                         } else{
                        this->indiceAtual++;
                        if(this->indiceAtual == 18){
                            this -> indiceAtual = 10;                 
                        } 
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
                        if(this->indiceAtual == 10){
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
                    this->indiceAtual = 25;
                  }else if(this->estadoAtual == ANDANDO_ESQUERDA){
                           this->indiceAtual = 18;
                        }else if(this->estadoAtual == ANDANDO_CIMA){
                              this->indiceAtual = 10;
                              }else if(this->estadoAtual == ANDANDO_BAIXO){
                                    this->indiceAtual = 0;
                                    }
                  this->estadoAtual = PARADO;
             }
             
          void paint( BITMAP *bitmap ){
                  masked_blit( arrayImagens[ indiceAtual ],bitmap,
                               0,0,
                               getX(),getY(),
                               getLargura(), getAltura() ); 
                               
                             /*   int x = getCaixaColisao() -> getX();
                               int y = getCaixaColisao() -> getY();
                               int x2 = x + getCaixaColisao() ->getLargura();
                               int y2 = y + getCaixaColisao()->getAltura();
                              rect( bitmap,x,y,x2,y2,makecol(255,255,255)); */      
          }  
             
          bool colideCaixa( int x ,int  y, int largura, int altura  ){
                  if( this -> getX() > x + largura ) return false;
                  if( this -> getY() > y + altura ) return false;
                  if( this -> getX() + this -> getLargura() < x ) return false;
                  if( this -> getY() + this -> getAltura() < y ) return false;
                  return true;
         }
         
                  void carregarMonstroVerde(){
                    arrayImagens[0]=load_bitmap("images\\monstrov1.bmp",NULL);
                    arrayImagens[1]=load_bitmap("images\\monstrov2.bmp",NULL);
                    arrayImagens[2]=load_bitmap("images\\monstrov3.bmp",NULL);
                    arrayImagens[3]=load_bitmap("images\\monstrov4.bmp",NULL);
                    arrayImagens[4]=load_bitmap("images\\monstrov5.bmp",NULL);
                    arrayImagens[5]=load_bitmap("images\\monstrov6.bmp",NULL);
                    arrayImagens[6]=load_bitmap("images\\monstrov7.bmp",NULL);
                    arrayImagens[7]=load_bitmap("images\\monstrov8.bmp",NULL);
                    arrayImagens[8]=load_bitmap("images\\monstrov9.bmp",NULL);
                    arrayImagens[9]=load_bitmap("images\\monstrov10.bmp",NULL);
                    arrayImagens[10]=load_bitmap("images\\monstrovcostas1.bmp",NULL);
                    arrayImagens[11]=load_bitmap("images\\monstrovcostas2.bmp",NULL);
                    arrayImagens[12]=load_bitmap("images\\monstrovcostas3.bmp",NULL);
                    arrayImagens[13]=load_bitmap("images\\monstrovcostas4.bmp",NULL);
                    arrayImagens[14]=load_bitmap("images\\monstrovcostas5.bmp",NULL);
                    arrayImagens[15]=load_bitmap("images\\monstrovcostas6.bmp",NULL);
                    arrayImagens[16]=load_bitmap("images\\monstrovcostas7.bmp",NULL);
                    arrayImagens[17]=load_bitmap("images\\monstrovcostas8.bmp",NULL);
                    arrayImagens[18]=load_bitmap("images\\monstrovlado1.bmp",NULL);
                    arrayImagens[19]=load_bitmap("images\\monstrovlado2.bmp",NULL);
                    arrayImagens[20]=load_bitmap("images\\monstrovlado3.bmp",NULL);
                    arrayImagens[21]=load_bitmap("images\\monstrovlado4.bmp",NULL);
                    arrayImagens[22]=load_bitmap("images\\monstrovlado5.bmp",NULL);
                    arrayImagens[23]=load_bitmap("images\\monstrovlado6.bmp",NULL);
                    arrayImagens[24]=load_bitmap("images\\monstrovlado7.bmp",NULL);
                    arrayImagens[25]=load_bitmap("images\\monstrovladodir1.bmp",NULL);
                    arrayImagens[26]=load_bitmap("images\\monstrovladodir2.bmp",NULL);
                    arrayImagens[27]=load_bitmap("images\\monstrovladodir3.bmp",NULL);
                    arrayImagens[28]=load_bitmap("images\\monstrovladodir4.bmp",NULL);
                    arrayImagens[29]=load_bitmap("images\\monstrovladodir5.bmp",NULL);
                    arrayImagens[30]=load_bitmap("images\\monstrovladodir6.bmp",NULL);
                    arrayImagens[31]=load_bitmap("images\\monstrovladodir7.bmp",NULL);
             }
             
          
      };
#endif