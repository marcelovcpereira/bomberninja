#ifndef CAIXA_COLISAO_H
#define CAIXA_COLISAO_H


#include <allegro.h>

class CaixaColisao{
      
      private: 
                int x;
                int y;
                int largura;
                int altura;
      
      public:
             
             CaixaColisao(){ setBounds(0,0,0,0);}
             
             CaixaColisao( int x, int y, int l , int a ){
                 setBounds( x, y, l, a );
             }
             
             void setBounds( int nX, int nY, int nL, int nA ){
                setX( nX );
                setY( nY );
                setLargura( nL );
                setAltura( nA );
             }
             
             void incrementarX( int iX ){
                  x = x + iX;
                  if( x < 0 ){
                     x = 0;
                  }
             }
             
             void incrementarY( int iY ){
                  y = y + iY;
                  if( y < 0 ){
                     y = 0;
                  }
             }
             
             void incrementarLargura( int iL ){
                  largura = largura + iL;
                  if( largura < 0 ){
                     largura = 0;
                  }
             }
             
             void incrementarAltura( int iA ){
                  altura = altura + iA;
                  if( altura < 0 ){
                     altura = 0;
                  }
             }
             
             
             int getX(){
                 return x;
             }
             int getY(){
                 return y;
             }
             int getAltura(){
                 return altura;
             }
             int getLargura(){
                 return largura;
             }
             void setX( int nX ){
                  if(nX >= 0){
                     x = nX;
                  }
             }
             void setY( int nY ){
                  if( nY >= 0){
                     y = nY;
                  }
             }
             void setAltura( int nA ){
                  if( nA >= 0 ){
                     altura = nA;
                  }
             }
             void setLargura( int nL ){
                  if( nL >= 0 ){
                     largura = nL;
                  }
             }
             
             bool colideCaixa( CaixaColisao *c ){
                 if( x + largura < c -> getX() ) return false;
                 if( y + altura < c -> getY() ) return false;
                 if( x > c -> getX() + c -> getLargura() ) return false;
                 if( y > c-> getY() + c -> getAltura() ) return false;
                 return true;
             }


};

#endif
