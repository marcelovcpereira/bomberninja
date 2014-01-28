#ifndef OBJETO2D_H
#define OBJETO2D_H

#include "caixaColisao.h"
#include "IRemote.h"

/**
 * Classe que representa um Objeto 2d que pode ser pintado na tela.
 * Tem uma imagem(BITMAP) que será renderizada.
 * Tem as posições X e Y de onde será renderizado.
 * Tem a largura e a altura do BITMAP
 */
class Objeto2D{

      private:
              int x, y, altura, largura;
              BITMAP *imagem;
              CaixaColisao *caixa;

      public:

      		/**
      		 * Construtor Default
      		 */
             Objeto2D(){
                     /*this -> x = 0;
                    this -> y = 0;
                    this -> altura = 0;
                    this -> largura = 0;
					this -> imagem = NULL;
                    this -> caixa = NULL;*/
					_asm {
						 mov eax, dword ptr[this]
						 mov dword ptr [eax+4], 0
						 mov dword ptr [eax+8], 0
						 mov dword ptr [eax+12], 0
						 mov dword ptr [eax+16], 0
						 mov dword ptr [eax+20], 0
						 mov dword ptr [eax+24], 0
					}
                    setCaixaColisao(0,0,0,0);
             }


             /**
			  * Construtor Que recebe a imagem do Objeto
      		  */
             Objeto2D( BITMAP *img ){
                   /*this -> x = 0;
                    this -> y = 0;
                    this -> altura = 0;
                    this -> largura = 0;
					this -> imagem = img;
					this -> caixa = NULL*/
					_asm {
						 mov eax, dword ptr[this]
						 mov dword ptr [eax+4], 0
						 mov dword ptr [eax+8], 0
						 mov dword ptr [eax+12], 0
						 mov dword ptr [eax+16], 0
						 mov ecx, dword ptr[img]
						 mov dword ptr [eax+20], ecx
						 mov dword ptr [eax+24], 0
					}
                    setCaixaColisao(0,0,0,0);
             }
             
             

             /**
			  * Construtor Que recebe as dimensões do Objeto
      		  */
             Objeto2D( int x, int y, int altura, int largura ){
				 /*this -> x = x;
				 this -> altura = altura;
				 this -> largura = largura;
				 this -> y = y;
				 this -> imagem = NULL;
				 this -> caixa = NULL;*/
				 _asm {
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[x]
					 mov dword ptr [eax+4], ecx
					 mov ecx, dword ptr[y]
					 mov dword ptr [eax+8], ecx
					 mov ecx, dword ptr[altura]
					 mov dword ptr [eax+12], ecx
					 mov ecx, dword ptr[largura]
					 mov dword ptr [eax+16], ecx
					 mov dword ptr [eax+20], 0
					 mov dword ptr [eax+24], 0
				 }
                 setCaixaColisao( x, y, largura ,altura );
             }

			 /**
			  * Construtor Completo
      		  */
             Objeto2D( BITMAP *img, int x, int y, int altura, int largura ){
                 /*this -> x = x;
                 this -> altura = altura;
                 this -> largura = largura;
                 this -> y = y;
				 this -> imagem = img;
                 this -> caixa = NULL;*/
				 _asm {
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[x]
					 mov dword ptr [eax+4], ecx
					 mov ecx, dword ptr[y]
					 mov dword ptr [eax+8], ecx
					 mov ecx, dword ptr[altura]
					 mov dword ptr [eax+12], ecx
					 mov ecx, dword ptr[largura]
					 mov dword ptr [eax+16], ecx
					 mov ecx, dword ptr[img]
					 mov dword ptr [eax+20], ecx
					 mov dword ptr [eax+24], 0
				 }
                 setCaixaColisao( x, y, largura ,altura );
             }
             
             virtual CaixaColisao *getCaixaColisao(){
                 //return this -> caixa;
				 _asm {
					 mov eax, dword ptr[this]
					 mov eax, dword ptr[eax+24]
				 }
             }
             
             void setCaixaColisao( CaixaColisao *c ){
                 //this -> caixa = c;
				 _asm {
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[c]
					 mov dword ptr [eax+24], ecx
				 }
             }
             
             void setCaixaColisao( int x, int y, int l, int a ){
                  if( caixa == NULL ){
                      this -> caixa = new CaixaColisao();
                  }
                  this -> caixa -> setBounds( x, y, l ,a );
             }


				/**  GETTERS E SETTERS  **/
             int getAltura(){
                 //return this -> altura;
				 _asm {
					 mov eax, dword ptr[this]
					 mov eax, dword ptr[eax+12]
				 }
             }

             int getLargura(){
                 //return this -> largura;
				 _asm {
					 mov eax, dword ptr[this]
					 mov eax, dword ptr[eax+16]
				 }
             }

             BITMAP *getImagem(){
                  //return this -> imagem;
				 _asm {
					 mov eax, dword ptr[this]
					 mov eax, dword ptr[eax+20]
				 }
             }

             void setImagem( BITMAP *b ){
                  //this -> imagem = b;
				 _asm {
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[b]
					 mov dword ptr [eax+20], ecx
				 }
             }

             int getX(){
                 //return this -> x;
				 _asm {
					 mov eax, dword ptr[this]
					 mov eax, dword ptr[eax+4]
				 }
             }

             int getY(){
                 //return this -> y;
				 _asm {
					 mov eax, dword ptr[this]
					 mov eax, dword ptr[eax+8]
				 }
             }

             void setX( int i ){
                  //this -> x = i;
				 _asm {
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[i]
					 mov dword ptr [eax+4], ecx
				 }
             }

             void setY( int i ){
                  //this -> y = i;
				 _asm {
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[i]
					 mov dword ptr [eax+8], ecx
				 }
             }
             
             void setAltura( int a ){
                 /*if( a > 0 ){
                     this -> altura = a;
                 }else{
                     this -> altura = 0;
                 }*/
				 _asm {
					 cmp dword ptr[a], 0
					 jle menorIgual
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[a]
					 mov dword ptr [eax+12], ecx
					 jmp fim
		menorIgual:	 mov eax, dword ptr[this]
					 mov dword ptr [eax+12], 0
		fim:
				 }
             }
             
             void setLargura( int l ){
                  /*if( l > 0 ){
                     this -> largura = l;
                  }else{
                     this -> largura = 0;
                  }*/
				 _asm {
					 cmp dword ptr[l], 0
					 jle lessEqual
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[l]
					 mov dword ptr [eax+16], ecx
					 jmp final
	 lessEqual:		 mov eax, dword ptr[this]
					 mov dword ptr [eax+16], 0
	 final:
				 }
             }

			/** Ajusta as dimensões do Objeto 2D
			 * largura, altura, x e y
			 */
             virtual void setBounds(int x, int y, int w, int h){
                  /*this -> x = x;
                  this->y=y;
                  this->altura=h;
                  this->largura =w;*/
				  _asm {
					 mov eax, dword ptr[this]
					 mov ecx, dword ptr[x]
					 mov dword ptr [eax+4], ecx
					 mov ecx, dword ptr[y]
					 mov dword ptr [eax+8], ecx
					 mov ecx, dword ptr[h]
					 mov dword ptr [eax+12], ecx
					 mov ecx, dword ptr[w]
					 mov dword ptr [eax+16], ecx
				  }
                  setCaixaColisao(x,y,w,h);
             }
             
             virtual const char *getNome(){
                     return "Objeto2D";
             }
             
             virtual int getTipo(){
             return 0;
             }
             
             virtual bool colideCaixa( Objeto2D *obj ){
                  setCaixaColisao( getX(), getY(), getLargura(), getAltura() );
                  return this -> caixa -> colideCaixa( obj -> getCaixaColisao() );
             }
             
             bool colideCaixaColisao( Objeto2D *obj ){
                  return this -> caixa -> colideCaixa( obj -> getCaixaColisao() );
             }

			 /*virtual SerialObject getSerialObject(){
				 SerialObject c; 
				 return c;
			 }*/

};
#endif