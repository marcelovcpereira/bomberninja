#ifndef MONSTRO_H
#define MONSTRO_H


#include <allegro.h>

#include "objeto2D.h"


class Monstro: public Objeto2D{
      
      private:
              
              int velocidade;
              int pontos;
              bool vivo;
              int direcao;
              int direcaoAtual;
              
              
      public:
             static const int horizontal = 0;
             static const int vertical = 1;
             static const int cima = 0;
             static const int baixo = 1;
             static const int direita = 2;
             static const int esquerda = 3;
             
             Monstro(){
             setDirecao(horizontal);
             setDirecaoAtual(direita);
             }
             
             void setDirecao(int dir){
                  direcao = dir;
             }
             
             int getDirecao(){
                  return this->direcao;
             }
             
             void setDirecaoAtual(int dir){
                  this->direcaoAtual = dir;
             }
             
             int getDirecaoAtual(){
                  return this->direcaoAtual;
             }
             
             int getVelocidade(){
                 return this-> velocidade;
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
             
             void setPontos( int p ){
                  this -> pontos = p;
             }
             
             void setVivo( bool b ){
                  this -> vivo = b;
             }
            
             const char *getNome(){
                   return "Monstro";
             }
             
             
             int getTipo(){
                 return 1000;
             }
             
             virtual void paint(BITMAP *b) = 0;
             
             bool colideCaixa( int x ,int  y, int largura, int altura  ){
                  if( this -> getX() > x + largura ) return false;
                  if( this -> getY() > y + altura ) return false;
                  if( this -> getX() + this -> getLargura() < x ) return false;
                  if( this -> getY() + this -> getAltura() < y ) return false;
                  return true;
         }
          bool colideCaixa( Objeto2D *obj ){
                  if( this -> getX() > obj -> getX() + obj -> getLargura() ) return false;
                  if( this -> getY() > obj -> getY() + obj -> getAltura() ) return false;
                  if( this -> getX() + this -> getLargura() < obj -> getX() ) return false;
                  if( this -> getY() + this -> getAltura() < obj -> getY() ) return false;
                  return true;
             }
         
         virtual void andarEsquerda() = 0;
         virtual void andarDireita() = 0;
         virtual void andarCima() = 0;
         virtual void andarBaixo() = 0;
};

#endif
