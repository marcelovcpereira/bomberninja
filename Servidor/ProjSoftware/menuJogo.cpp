 #ifndef MENUJOGO_CPP
#define MENUJOGO_CPP


#include <allegro.h>
 

 #include "objeto2D.h"
 #include "personagem.h"
 #include "IRemote.h"
#include "UltimaTentativa.cpp"

 class MenuJogo : public Objeto2D {
      
      
      private:
              volatile int *tempo;
              int ultimoTempo;
              int tempoEstagio;
              BITMAP *arrayImagensCron[11];
              BITMAP *arrayImagensVidas[11];
              BITMAP *arrayImagensScore[12];
              BITMAP *arrayImagensCartas[5];
              BITMAP *menu;
              Personagem *personagem;
			  int min;
			  int sec1;
			  int sec2;
      
      public:
             
             MenuJogo(volatile int *t, Personagem *p){
             
                  tempo = t;
                  ultimoTempo = 1000;
                  personagem = p;
                  
                  tempoEstagio = 60000;
                  
                  this ->inicializarBitmaps();
                  
                  this ->pintarBitmapInicial();
             
             }
             
             
             bool passou(){
                  return (*tempo - ultimoTempo) >100;      
             }
             
             
             void inicializarBitmaps(){
                  
                  //cronometro:
                  arrayImagensCron[0] = load_bitmap("images\\numero0.bmp",NULL);
                  arrayImagensCron[1] = load_bitmap("images\\numero1.bmp",NULL);
                  arrayImagensCron[2] = load_bitmap("images\\numero2.bmp",NULL);
                  arrayImagensCron[3] = load_bitmap("images\\numero3.bmp",NULL);
                  arrayImagensCron[4] = load_bitmap("images\\numero4.bmp",NULL);
                  arrayImagensCron[5] = load_bitmap("images\\numero5.bmp",NULL);
                  arrayImagensCron[6] = load_bitmap("images\\numero6.bmp",NULL);
                  arrayImagensCron[7] = load_bitmap("images\\numero7.bmp",NULL);
                  arrayImagensCron[8] = load_bitmap("images\\numero8.bmp",NULL);
                  arrayImagensCron[9] = load_bitmap("images\\numero9.bmp",NULL);
                  arrayImagensCron[10] = load_bitmap("images\\numero2p.bmp",NULL);
                  
                  //vidas
                  arrayImagensVidas[0] = load_bitmap("images\\x0.bmp",NULL);
                  arrayImagensVidas[1] = load_bitmap("images\\x1.bmp",NULL);
                  arrayImagensVidas[2] = load_bitmap("images\\x2.bmp",NULL);
                  arrayImagensVidas[3] = load_bitmap("images\\x3.bmp",NULL);
                  arrayImagensVidas[4] = load_bitmap("images\\x4.bmp",NULL);
                  arrayImagensVidas[5] = load_bitmap("images\\x5.bmp",NULL);
                  arrayImagensVidas[6] = load_bitmap("images\\x6.bmp",NULL);
                  arrayImagensVidas[7] = load_bitmap("images\\x7.bmp",NULL);
                  arrayImagensVidas[8] = load_bitmap("images\\x8.bmp",NULL);
                  arrayImagensVidas[9] = load_bitmap("images\\x9.bmp",NULL);
                  arrayImagensVidas[10] = load_bitmap("images\\rostoBoneco.bmp",NULL);
                  
                  //score
                  arrayImagensScore[0] = load_bitmap("images\\small0.bmp",NULL);
                  arrayImagensScore[1] = load_bitmap("images\\small1.bmp",NULL);
                  arrayImagensScore[2] = load_bitmap("images\\small2.bmp",NULL);
                  arrayImagensScore[3] = load_bitmap("images\\small3.bmp",NULL);
                  arrayImagensScore[4] = load_bitmap("images\\small4.bmp",NULL);
                  arrayImagensScore[5] = load_bitmap("images\\small5.bmp",NULL);
                  arrayImagensScore[6] = load_bitmap("images\\small6.bmp",NULL);
                  arrayImagensScore[7] = load_bitmap("images\\small7.bmp",NULL);
                  arrayImagensScore[8] = load_bitmap("images\\small8.bmp",NULL);
                  arrayImagensScore[9] = load_bitmap("images\\small9.bmp",NULL);
                  arrayImagensScore[10] = load_bitmap("images\\score.bmp",NULL);
                  arrayImagensScore[11] = load_bitmap("images\\mais.bmp",NULL);
                  
                  //cartas
                  arrayImagensCartas[0] = load_bitmap("images\\cartaBomba.bmp",NULL);
                  arrayImagensCartas[1] = load_bitmap("images\\cartaFogoexe.bmp",NULL);
                  arrayImagensCartas[2] = load_bitmap("images\\cartaVelo.bmp",NULL);
                  arrayImagensCartas[3] = load_bitmap("images\\cartavida.bmp",NULL);
                  arrayImagensCartas[4] = load_bitmap("images\\cartasuperfogo.bmp",NULL);
                  
                  menu = load_bitmap("images\\menu3.bmp",NULL);
                  
             }
             
             void pintarBitmapInicial(){
             
                  //pintando boneco
                  //draw_sprite(menu, arrayImagensVidas[8], 30,20);
                  
                  //pintando o score
                  draw_sprite(menu, arrayImagensScore[10], 120,6);
                  //draw_sprite(menu, arrayImagensScore[6], 120,30);
                  
                  //pintando os :
                  masked_blit( arrayImagensCron[10],menu,0,0,350,27,25,34);
                 // draw_sprite(menu, arrayImagensCron[10], 350,27);
                  
                  //pintando as cartas
                  draw_sprite(menu, arrayImagensCartas[0], 540,30);
                  draw_sprite(menu, arrayImagensCartas[1], 590,30);
                  draw_sprite(menu, arrayImagensCartas[2], 640,30);
                  draw_sprite(menu, arrayImagensCartas[3], 690,30);
                  draw_sprite(menu, arrayImagensCartas[4], 740,30);
                  /*draw_sprite(menu, arrayImagensCartas[1], 730,50);
                  draw_sprite(menu, arrayImagensCartas[2], 765,50);
                  draw_sprite(menu, arrayImagensCartas[0], 590,20);
                  draw_sprite(menu, arrayImagensCartas[1], 625,20);
                  draw_sprite(menu, arrayImagensCartas[2], 660,20);
                  draw_sprite(menu, arrayImagensCartas[0], 695,20);
                  draw_sprite(menu, arrayImagensCartas[1], 730,20);
                  draw_sprite(menu, arrayImagensCartas[2], 765,20);*/
             }
             
             
             void paint (BITMAP *bitmap){
                        //numeros cartas:
                        int x = personagem->getNumCartas(3); 
                        //pintando numero bombas
                        if (x>= 10){
                           x = 11;
                        }
                        draw_sprite(menu, arrayImagensScore[x], 555,10); 
                        
                        x = personagem->getNumCartas(0);
                        if (x>= 10){
                           x = 11;
                        }
                        //pintando numero fogo
                        draw_sprite(menu, arrayImagensScore[x], 605,10); 
                        
                        x = personagem->getNumCartas(1);
                        if (x>= 10){
                           x = 11;
                        }
                        //pintando velocidade
                        draw_sprite(menu, arrayImagensScore[x], 655,10);
                        
                        x = personagem->getNumCartas(5);
                        if (x>= 10){
                           x = 11;
                        }
                        //pintando numero vidas 
                        draw_sprite(menu, arrayImagensScore[x], 705,10); 
                        
                        x = personagem->getNumCartas(6);
                        if (x>= 10){
                           x = 11;
                        }
                        //pintando super fogo 
                        draw_sprite(menu, arrayImagensScore[x], 755,10); 
                       
                        /*x = personagem->getNumCartas(4);
                        draw_sprite(menu, arrayImagensScore[x], 730,20); 
                        x = personagem->getNumCartas(5);
                        draw_sprite(menu, arrayImagensScore[x], 765,20); 
                        draw_sprite(menu, arrayImagensScore[6], 590,50); 
                        draw_sprite(menu, arrayImagensScore[7], 625,50); 
                        draw_sprite(menu, arrayImagensScore[8], 660,50); 
                        draw_sprite(menu, arrayImagensScore[9], 695,50); 
                        draw_sprite(menu, arrayImagensScore[2], 730,50); 
                        draw_sprite(menu, arrayImagensScore[6], 765,50); */
                        
                  // numero vidas:
                        int vidas = personagem -> getVidas();
                        /*mudança*/
                        draw_sprite(menu, arrayImagensVidas[vidas%10], 87,61);
                        
                  // numero pontos:
                        int pontos = personagem -> getPontos();
                        int p0 = pontos % 10;
                        int p1 = pontos % 100;
                        p1 = p1/10;
                        int p2 = pontos % 1000;
                        p2 = p2/100;
                        int p3 = pontos % 10000;
                        p3 = p3/1000;
                        /*mudança*/
                        masked_blit( arrayImagensScore[p3], menu, 0, 0, 130, 32, 12, 13 );
                        masked_blit( arrayImagensScore[p2], menu, 0, 0, 145, 32, 12, 13 );
                        masked_blit( arrayImagensScore[p1], menu, 0, 0, 160, 32, 12, 13 );
                        masked_blit( arrayImagensScore[p0], menu, 0, 0, 175, 32, 12, 13 );
                 
                  // cronometro:
                        int i = this -> getTempo();
                        this->min = this -> getMin(i);
                        this->sec1 = this -> getSec1(i);
                        this->sec2 = this -> getSec2(i);
                        
                        if(min < 0)min = 0;
                        if(sec1 <0)sec1 = 0;
                        if(sec2 < 0)sec2 = 0;
                        /*mudança*/
                        masked_blit( arrayImagensCron[min],menu,0,0,320,29,25,34);
                        masked_blit( arrayImagensCron[sec1],menu,0,0,382,29,25,34);
                        masked_blit( arrayImagensCron[sec2],menu,0,0,425,29,25,34);
                        //draw_sprite(menu, arrayImagensCron[min], 320,27);
                       // draw_sprite(menu, arrayImagensCron[sec1], 382,27);
                      //  draw_sprite(menu, arrayImagensCron[sec2], 425,27);
                        
                  // pintando menu na tela:
                        draw_sprite(bitmap, menu, 0,600-80);
             }
           
           
           int getMin(int i){
               
               int ret = i;
               ret = ret/1000;
               ret = ret / 60;
               return ret;
                    
           }
           
           int getSec1(int i){
               
               int ret = i;
               ret = ret/1000;
               ret = ret % 60;
               ret = ret / 10;
               return ret;
                    
           }
           
           int getSec2(int i){
               
               int ret = i;
               ret = ret/1000;
               ret = ret % 60;
               ret = ret % 10;
               return ret;
                    
           }
           
           void zerarTempo(int tempEst){
                ultimoTempo = *tempo + 1000;
                tempoEstagio = tempEst;
           }
           
           int getTempo(){
               
               return (tempoEstagio - (*tempo - ultimoTempo));
           }


		   void atualizarTempo (){
		       int i = this -> getTempo();
			   this->min = this -> getMin(i);
               this->sec1 = this -> getSec1(i);
               this->sec2 = this -> getSec2(i);
		   
		   } 
             
		   
		   UltimaTentativa *getSerial(){
				UltimaTentativa *o = new UltimaTentativa();
				o -> x = getX();
				o -> y = getY();
				o -> tipo = 11;
				o -> info1 = personagem ->getNumCartas(3);
				o -> info2 = personagem ->getNumCartas(0);
				o -> info3 = personagem ->getNumCartas(1);
				o -> info4 = personagem ->getNumCartas(5);
				o -> info5 = personagem ->getNumCartas(6);
				o -> info6 = personagem -> getVidas();
				o -> info7 = personagem -> getPontos();
				o -> info8 = min;
				o -> info9 = sec1;
				o -> info10 = sec2;
				return o;
			}
            
		    
		    ObjetoSerial getSerializable(){
				 ObjetoSerial serial;
				 setSerial(serial);
				 return serial;
				 
			 }

			 void setSerial( ObjetoSerial &serial ){
				 /*this -> atualizarTempo();
			     serial.x = (CORBA::UShort) getX();
				 serial.y = (CORBA::UShort) getY();
				 serial.tipo =(CORBA::UShort) getTipo();
				 serial.info[0] = (CORBA::UShort) 0;
				 serial.info[1] = (CORBA::UShort) 0;
				 serial.info[2] = (CORBA::UShort) 0;
				 serial.info[3] = (CORBA::UShort) 0;
				 serial.info[4] = (CORBA::UShort) 0;
				 serial.info[5] = (CORBA::UShort) 0;
				 serial.info[6] = (CORBA::UShort) 0;
				 serial.info[7] = (CORBA::UShort) min;
				 serial.info[8] = (CORBA::UShort) sec1;
				 serial.info[9] = (CORBA::UShort) sec2;*/

			 }
      
};
#endif