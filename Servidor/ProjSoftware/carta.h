 #ifndef CARTA_H
 #define CARTA_H
 

#include <allegro.h>
 
 #include "objeto2D.h"
 #include "pontos.h"
 #include "personagem.h"

#include "UltimaTentativa.cpp"
 
  class Carta : public Objeto2D{
      
      private: BITMAP *imagem2;
               int pontos;
      
      public:
             
             Carta( BITMAP *img, BITMAP *img2, int x, int y, int altura, int largura ){
                       this->setX(x);
                       this->setAltura(altura);
                       this->setLargura(largura);
                       this->setY(y);
                       this->setImagem(img);
                       this->setImagem2(img2);
                       this -> pontos = 0;
             }
             
      void setImagem2(BITMAP *img2){
           this -> imagem2 = img2;
      }
      
      BITMAP *getImagem2(){
                    return this -> imagem2;
             }
      
      virtual void atuar(Personagem *p) = 0 ;
      
      virtual void paint(BITMAP *b) = 0;

	  virtual ObjetoSerial getSerializable() = 0;

	  virtual UltimaTentativa *getSerial() = 0;
      
      int pontosRand(){
          
                   int random = (int)(rand()%20);
                   
                   if(random <= 4 ){
                            pontos = 0; 
                   }else if(random > 4 && random <= 9){
                            pontos = 100;
                   }else if(random > 9 && random <= 13){
                            pontos = 200;  
                   }else if(random > 13 && random <= 16){
                            pontos = 300;    
                   }else if(random > 16 && random <= 19){
                            pontos = 400;   
                   }else {
                            pontos = 500;    
                   }
                    return pontos;
      }
      
      int getPontos(){
           return pontos;
      }
      
};



class CartaAumentarFogo: public Carta{
      
      public:
             int i ;
             bool b;
             
             CartaAumentarFogo( BITMAP *img, BITMAP *img2,int x, int y, int altura, int largura ):
                                Carta(img, img2, x, y, altura, largura){
                                           i = 0;
                                           b = false;
             }
              
              void atuar(Personagem *p){
                   int i = p->getForca();
                   p->setForca( i + 1);
                   p->incrementarCarta(0);  
                   int pontos = this -> pontosRand();
                   p->setPontos(p->getPontos() + pontos);  
              }
              
              void paint(BITMAP *bit){
              
                    if (b){
                    masked_blit(this->getImagem(),bit,0,0,getX(),getY(),getLargura(), getAltura() );       
                    }
                    else {
                    masked_blit(this->getImagem2(),bit,0,0,getX(),getY(),getLargura(), getAltura() );   
                    }
                    i = i + 1;
                    
                    if (i%10 == 0){b = !b;}
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
				o -> tipo = 1;
				o -> info1 = b;
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
				 serial.tipo =(CORBA::UShort)1;
				 serial.info[0] = (CORBA::UShort) b;*/

			 }
              
};

class CartaAumentarVelocidade: public Carta{
      
      public:
             int i ;
             bool b;
             
             CartaAumentarVelocidade( BITMAP *img,BITMAP *img2, int x, int y, int altura, int largura ):
                                Carta(img, img2, x, y, altura, largura){
                                           i = 0;
                                           b = false;
             }

              
              void atuar(Personagem *p){
                   
                   p->setVelocidade(p->getVelocidade() + 5);
                   p->incrementarCarta(1);
                   int pontos = this -> pontosRand();
                   p->setPontos(p->getPontos() + pontos);  
              }
              
              void paint(BITMAP *bit){
              
                   if (b){
                    masked_blit(this->getImagem(),bit,0,0,getX(),getY(),getLargura(), getAltura() );       
                    }
                    else {
                    masked_blit(this->getImagem2(),bit,0,0,getX(),getY(),getLargura(), getAltura() );   
                    }
                    i = i + 1;
                    
                    if (i%10 == 0){b = !b;}
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
				o -> tipo = 2;
				o -> info1 = b;
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
				 serial.tipo =(CORBA::UShort)2;
				 serial.info[0] = (CORBA::UShort) b;*/

			 }

};

class CartaDiminuirVelocidade: public Carta{
      
      public:
     
             int i ;
             bool b;
             CartaDiminuirVelocidade( BITMAP *img, BITMAP *img2,int x, int y, int altura, int largura ):
                                Carta(img, img2, x, y, altura, largura){
                                           i = 0;
                                           b = false;
             }
             
             void atuar(Personagem *p){
                  if(p->getVelocidade() > 20)
                  p->setVelocidade(p->getVelocidade() - 10);
                  else p->setVelocidade(10);
                  p->incrementarCarta(2);
                  int pontos = this -> pontosRand();
                   p->setPontos(p->getPontos() + pontos);  
             }
             
             void paint(BITMAP *bit){
              
                    if (b){
                    masked_blit(this->getImagem(),bit,0,0,getX(),getY(),getLargura(), getAltura() );       
                    }
                    else {
                    masked_blit(this->getImagem2(),bit,0,0,getX(),getY(),getLargura(), getAltura() );   
                    }
                    i = i + 1;
                    
                    if (i%10 == 0){b = !b;}
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
				o -> tipo = 3;
				o -> info1 = b;
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
				 serial.tipo =(CORBA::UShort)3;
				 serial.info[0] = (CORBA::UShort) b;*/

			 }
};

class CartaNumBombas: public Carta{
      
      public:

             int i ;
             bool b;
              CartaNumBombas( BITMAP *img, BITMAP *img2,int x, int y, int altura, int largura ):
                                Carta(img, img2, x, y, altura, largura){
                                           i = 0;
                                           b = false;
                                           
             }
             
             void atuar(Personagem *p){
                  
                  p->setNumMaxBombas(p->getNumMaxBombas() + 1);
                  p->incrementarCarta(3); 
                  int pontos = this -> pontosRand();
                   p->setPontos(p->getPontos() + pontos);                   
             }
             
              void paint(BITMAP *bit){
                   if (b){
                    masked_blit(this->getImagem(),bit,0,0,getX(),getY(),getLargura(), getAltura() );       
                    }
                    else {
                    masked_blit(this->getImagem2(),bit,0,0,getX(),getY(),getLargura(), getAltura() );   
                    }
                    i = i + 1;
                    
                    if (i%10 == 0){b = !b;}
                         
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
				o -> tipo = 4;
				o -> info1 = b;
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
				 serial.tipo =(CORBA::UShort)4;
				 serial.info[0] = (CORBA::UShort) b;*/

			 }

};

class CartaDiminuirFogo: public Carta{
      
      public:
      
             int i ;
             bool b;
      
             CartaDiminuirFogo( BITMAP *img, BITMAP *img2,int x, int y, int altura, int largura ):
                                Carta(img, img2, x, y, altura, largura){
                                           i = 0;
                                           b = false;
             }
              
              void atuar(Personagem *p){
                   if(p->getForca() > 1){
                     int x = p->getForca();
                     p->setForca(x - 1);}
                   p->incrementarCarta(4);
                   int pontos = this -> pontosRand();
                   p->setPontos(p->getPontos() + pontos);  
                   
              }
              
              void paint(BITMAP *bit){
              
                    if (b){
                    masked_blit(this->getImagem(),bit,0,0,getX(),getY(),getLargura(), getAltura() );       
                    }
                    else {
                    masked_blit(this->getImagem2(),bit,0,0,getX(),getY(),getLargura(), getAltura() );   
                    }
                    i = i + 1;
                    
                    if (i%10 == 0){b = !b;}
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
				o -> tipo = 5;
				o -> info1 = b;
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
				 serial.tipo =(CORBA::UShort)5;
				 serial.info[0] = (CORBA::UShort) b;*/

			 }
              
};


class CartaAumentarVida: public Carta{
      
      public:
      
             int i ;
             bool b;
      
             CartaAumentarVida( BITMAP *img,BITMAP *img2, int x, int y, int altura, int largura ):
                                Carta(img, img2, x, y, altura, largura){
                                           i = 0;
                                           b = false;
             }
              
              void atuar(Personagem *p){
                   int i = p -> getVidas();
                   p->setVidas(i+1);
                   p->incrementarCarta(5);
                   int pontos = this -> pontosRand();
                   p->setPontos(p->getPontos() + pontos);  
                   
              }
              
              void paint(BITMAP *bit){
              
                    if (b){
                    masked_blit(this->getImagem(),bit,0,0,getX(),getY(),getLargura(), getAltura() );       
                    }
                    else {
                    masked_blit(this->getImagem2(),bit,0,0,getX(),getY(),getLargura(), getAltura() );   
                    }
                    i = i + 1;
                    
                    if (i%10 == 0){b = !b;}
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
				o -> tipo = 6;
				o -> info1 = b;
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
				 serial.tipo =(CORBA::UShort)6;
				 serial.info[0] = (CORBA::UShort) b;*/

			 }
              
};
class CartaSuperFogo: public Carta{
      
      public:
             int i ;
             bool b;
             
             CartaSuperFogo( BITMAP *img, BITMAP *img2,int x, int y, int altura, int largura ):
                                Carta(img, img2, x, y, altura, largura){
                                           i = 0;
                                           b = false;
             }
              
              void atuar(Personagem *p){
                   p->setForca( 18 );
                   p->incrementarCarta( 6 );  
                   int pontos = this -> pontosRand();
                   p->setPontos(p->getPontos() + pontos);  
              }
              
              void paint(BITMAP *bit){
              
                    if (b){
                    masked_blit(this->getImagem(),bit,0,0,getX(),getY(),getLargura(), getAltura() );       
                    }
                    else {
                    masked_blit(this->getImagem2(),bit,0,0,getX(),getY(),getLargura(), getAltura() );   
                    }
                    i = i + 1;
                    
                    if (i%10 == 0){b = !b;}
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
				o -> tipo = 7;
				o -> info1 = b;
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
				 serial.tipo =(CORBA::UShort)7;
				 serial.info[0] = (CORBA::UShort) b;*/

			 }
              
};
#endif