#ifndef NINJA_H
#define NINJA_H


#include <allegro.h>

#include "personagem.h"
#include "UltimaTentativa.cpp"



#define NUM_IMAGES 15




class Ninja: public Personagem{
      
      private:
              
              BITMAP *arrayImagens[NUM_IMAGES];
              int indiceAtual;
              
              volatile int *tempoAtual;
              int ultimoTempo;
              int tempoInicial;
              
              int ultimoTempoAndar;
              static const int intervaloAndar = 10;
              static const int intervalo = 200;//decimos de segundo
              
              int incrementoImagem;
              
      public:
             
            /* static const int ANDANDO_ESQ = 1;
             static const int ANDANDO_DIR = 2;
             static const int ANDANDO_CIMA = 3;
             static const int ANDANDO_BAIXO = 4;
             static const int PARADO = 5;
             static const int MORRENDO = 6;*/
             
             Ninja():Personagem(){
                     this -> indiceAtual = 0;
                     carregarArrayNinja();
                     setVelocidade( 30 );
                     incrementoImagem =0;
                     setVivo( true );
             }
             
             Ninja( BITMAP *array[NUM_IMAGES] ):Personagem(){
                    this -> indiceAtual = 0;
                    carregarArrayNinja();
                    for( int i = 0; i < NUM_IMAGES; i++ ){
                         this -> arrayImagens[ i ] = array[ i ];
                    }
                    this -> indiceAtual = 0;
                    setVelocidade( 30 );
                    incrementoImagem = 0;
                    
             }
             
             void setCronometro( volatile int *t ){
                  this -> tempoAtual = t;
                  this -> ultimoTempo = *tempoAtual;
                  this -> tempoInicial = ultimoTempo;
                  this -> ultimoTempoAndar = ultimoTempo;
             }
             
             void setBounds(int x, int y, int l, int a ){
                  setX( x );
                  setY( y );
                  setLargura( l );
                  setAltura( a );
                  setCaixaColisao( x + 8, y + 30, l - 16 , a - 30 );
             }
             
             void andarDireita(){
                  if( getEstadoAtual() == MORRENDO ) return;
                  if( getEstadoAtual() != ANDANDO_DIR ){
                          indiceAtual = 6;
                       }
                  if( *tempoAtual - ultimoTempo >= intervalo ){
                       //atualizar imagem
                       if( getEstadoAtual() != ANDANDO_DIR ){
                          indiceAtual = 6;
                       }else{
                          if( indiceAtual == 7 || indiceAtual == 8 ){
                               indiceAtual = 6;
                           }else{
                                 if( incrementoImagem == 0 ){
                                     indiceAtual = 7;
                                     incrementoImagem = 1;
                                 }else{
                                     indiceAtual = 8;
                                     incrementoImagem = 0;
                                 }
                           } 
                       }
                       ultimoTempo = *tempoAtual;
                  }
                  setEstadoAtual(ANDANDO_DIR);
                  if( *tempoAtual - ultimoTempoAndar >= intervaloAndar ){
                    setX( getX() + getVelocidade()/10 );
                    this -> getCaixaColisao() -> incrementarX( getVelocidade() / 10 );
                    ultimoTempoAndar = *tempoAtual;
                  }
             }
             
             CaixaColisao *getCaixaColisao(){
                  setCaixaColisao( getX()+8, getY()+30, getLargura()-16, getAltura()-30 );
                  return Objeto2D::getCaixaColisao();
             }
             
             void setVivo(bool b){
                  Personagem::setVivo(b);
                  indiceAtual = 0;
             }
             
             void andarEsquerda(){
                  if( getEstadoAtual() == MORRENDO ) return;
                  if( getEstadoAtual() != ANDANDO_ESQ ){
                          indiceAtual = 9;
                       }
                  if( *tempoAtual - ultimoTempo >= intervalo ){
                      //atualizar imagem
                       if( getEstadoAtual() != ANDANDO_ESQ ){
                          indiceAtual = 9;
                       }else{
                           if( indiceAtual == 10 || indiceAtual == 11 ){
                               indiceAtual = 9;
                           }else{
                                 if( incrementoImagem == 0 ){
                                     indiceAtual = 10;
                                     incrementoImagem = 1;
                                 }else{
                                     indiceAtual = 11;
                                     incrementoImagem = 0;
                                 }
                           }  
                           
                       }
                       ultimoTempo = *tempoAtual;
                  }
                  setEstadoAtual(ANDANDO_ESQ);
                  if( *tempoAtual - ultimoTempoAndar >= intervaloAndar ){
                     setX( getX() - getVelocidade()/10 );
                     this -> getCaixaColisao() -> incrementarX( -(getVelocidade() / 10) );
                     ultimoTempoAndar = *tempoAtual;
                  }
             }

			 int getIndice(){
				return this -> indiceAtual;
			 }
             
             void andarCima(){
                  if( getEstadoAtual() == MORRENDO ) return;
                  if( getEstadoAtual() != ANDANDO_CIMA ){
                         indiceAtual = 3;
                     }
                  if( *tempoAtual - ultimoTempo >= intervalo ){
                     //atualizar imagem
                     if( getEstadoAtual() != ANDANDO_CIMA ){
                         indiceAtual = 3;
                     }else{
                           switch( indiceAtual ){
                               case 4:  indiceAtual = 5; break;
                               default: indiceAtual = 4; break;
                           } 
                     }
                     ultimoTempo = *tempoAtual;
                  }
                  setEstadoAtual(ANDANDO_CIMA);
                  if( *tempoAtual - ultimoTempoAndar >= intervaloAndar ){
                     setY( getY() - getVelocidade()/10 );
                     this -> getCaixaColisao() -> incrementarY( -(getVelocidade() / 10) );
                     ultimoTempoAndar = *tempoAtual;
                  }
             }
             
             void andarBaixo(){
                  if( getEstadoAtual() == MORRENDO ) return;
                  if( getEstadoAtual() != ANDANDO_BAIXO ){
                         indiceAtual = 3;
                     }
                  //se deu o intervalo
                  if( *tempoAtual - ultimoTempo >= intervalo ){
                           //troque de imagem
                           switch( indiceAtual ){
                               case 1:  indiceAtual = 2; break;
                               default: indiceAtual = 1; break;
                           } 
                    //atualize o tempo
                    ultimoTempo = *tempoAtual;
                  } 
                  //mude o estado atual
                  setEstadoAtual(ANDANDO_BAIXO);
                  //atualize a posição
                  if( *tempoAtual - ultimoTempoAndar >= intervaloAndar ){
                     setY( getY() + getVelocidade()/10 );
                     this -> getCaixaColisao() -> incrementarY( getVelocidade() / 10 );
                     ultimoTempoAndar = *tempoAtual;
                     
                  }
             }
             
             void parar(){
                  if( getEstadoAtual() == MORRENDO ) return;
                  //atualizar imagem
                  if( getEstadoAtual() == ANDANDO_DIR ){
                        indiceAtual = 6; 
                  }else if( getEstadoAtual() == ANDANDO_ESQ ){
                        indiceAtual = 9;
                  }else if( getEstadoAtual() == ANDANDO_CIMA ){
                        indiceAtual = 3;
                  }else if( getEstadoAtual() == ANDANDO_BAIXO ){
                        indiceAtual = 0;
                  }
                  //atualizar Estado
                  setEstadoAtual( PARADO );
             }
             
             void paint( BITMAP *bitmap ){
                  if( getEstadoAtual() == MORRENDO ){
                     if( *tempoAtual - ultimoTempo >= intervalo ){
                      indiceAtual++;
                      if( indiceAtual < 12 )indiceAtual = 12;
                      if( indiceAtual == 14 ) setVivo( false );
                      ultimoTempo = *tempoAtual;
                      }
                      
                  }
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
             
             
             void carregarArrayNinja(){
                  arrayImagens[0] = load_bitmap("images\\ninja.bmp",NULL);
                  arrayImagens[1] = load_bitmap("images\\ninjaAndando1.bmp",NULL);
                  arrayImagens[2] = load_bitmap("images\\ninjaAndando2.bmp",NULL);        
                  arrayImagens[3] = load_bitmap("images\\ninjaCostas.bmp",NULL);
                  arrayImagens[4] = load_bitmap("images\\ninjaCostas1.bmp",NULL);
                  arrayImagens[5] = load_bitmap("images\\ninjaCostas2.bmp",NULL);
                  arrayImagens[6] = load_bitmap("images\\ninjaLadoDireito1.bmp",NULL);
                  arrayImagens[7] = load_bitmap("images\\ninjaLadoDireito2.bmp",NULL);
                  arrayImagens[8] = load_bitmap("images\\ninjaLadoDireito3.bmp",NULL);
                  arrayImagens[9] = load_bitmap("images\\ninjaLadoEsquerdo1.bmp",NULL);
                  arrayImagens[10] = load_bitmap("images\\ninjaLadoEsquerdo2.bmp",NULL);
                  arrayImagens[11] = load_bitmap("images\\ninjaLadoEsquerdo3.bmp",NULL);
                  arrayImagens[12] = load_bitmap("images\\ninjamorto2.bmp",NULL);
                  arrayImagens[13] = load_bitmap("images\\ninjamorto3.bmp",NULL);
                  arrayImagens[14] = load_bitmap("images\\ninjamorto4.bmp",NULL);
                  
             }
             
             bool colideCaixa( Objeto2D *obj ){
                  if( this -> getX() +8> obj -> getX() + obj -> getLargura() ) return false;
                  if( this -> getY()+35 > obj -> getY() + obj -> getAltura() ) return false;
                  if( this -> getX() + this -> getLargura()-8 < obj -> getX() ) return false;
                  if( this -> getY() + this -> getAltura() < obj -> getY() ) return false;
                  return true;
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
				o -> tipo = 12;
				o -> info1 = indiceAtual;
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
				/* serial.info.length(10);
			     serial.x = (CORBA::UShort) getX();
				 serial.y = (CORBA::UShort) getY();
				 serial.tipo =(CORBA::UShort)12;
				 serial.info[0] = (CORBA::UShort) indiceAtual;*/

			 }

			 /* UltimaTentativa *ultima(){
				 int i[10];
				 i[0] = indiceAtual; 
				UltimaTentativa *t ;
					t = new UltimaTentativa(getX(),getY(),12,i);
				return t;
			 }*/

};


#endif
