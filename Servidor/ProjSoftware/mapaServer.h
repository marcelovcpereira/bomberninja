#ifndef MAPA_SERVER_H
#define MAPA_SERVER_H

#include <allegro.h>
#include <ctime>
#include <typeinfo>
#include <cstring>
#include <cmath>

#include "tile.h"
#include "lista.cpp"
#include "carta.h"
#include "bomba.h"
#include "pontos.h"
#include "explosao.h"
#include "painel.h"
#include "ninja.h"
#include "menuJogo.cpp"
#include "fumaca.h"
#include "IRemote.h"
#include "UltimaTentativa.cpp"

#define LINHAS 13
#define COLUNAS 20
#define NUM_DEST 4
#define TILE_WIDTH 40
#define TILE_HEIGHT 40
#define NUM_BOMBAS  4
#define NUM_FUMACA  3
#define NUM_PONTOS  6
#define DESTRUIR 80
#define NUM_IMAGEM_EXP 9
#define SOM_FREQ 2000
#define NUM_OBJE 1

/* Classe que representa um Mapa, ou seja, um estágio do jogo.
 * Essa classe possui um array bidimensional de TILES.
 * Cada estágio também tem suas próprias imagens dos seus TILES.
 * Sendo floor a imagem do chão daquele estágio.
 * Sendo wall a imagem da parede daquele estágio.
 * Sendo block a imagem do TILE bloqueador daquele estágio.
 * Sendo destruindo um array de imagens do TILE wall sendo destruido
 */
class MapaServer: public Objeto2D{

      private:
              Tile *arrayTiles[LINHAS][COLUNAS];
              BITMAP *imagemPortal;
              BITMAP *floor;
              BITMAP *wall;
              BITMAP *block;
              BITMAP *arrayFumaca[NUM_FUMACA];
              BITMAP *arrayPontos[NUM_PONTOS];
              Personagem *personagem;
			  Personagem *player2;
              ListaObjetos2D *listaWall;
              ListaObjetos2D *listaCartas;
              ListaObjetos2D *objetos;
              ListaObjetos2D *listaPontos;

			  ListaObjetos2D *bombas1;
			  ListaObjetos2D *bombas2;
              int proxBomba;
              volatile int *tempo;
              int ultimoTempo;
              int tempoInicial;  
              MenuJogo *menu;
              BITMAP *arrayExplosao[ NUM_IMAGEM_EXP ];
              SAMPLE *somExplosao;
              SAMPLE *somCarta;
              int tipo;
              Painel *painel;
              bool podePintar;
             int ultimoPonto;
   
      public:
             static const int TIPO1 = 0;
             static const int TIPO2 = 1;
      		/* Construtor Default */
             MapaServer(){ 
                   inicializar();
                   
             }

             /* Construtor Completo */
             MapaServer(BITMAP *f, BITMAP *w, BITMAP* b, BITMAP *d[]){
                   this -> floor = f;
                   this -> wall = w;
                   this -> block = b;
                   inicializar();
             }
             
             /* Construtor que recebe as 3 imagens  */
             MapaServer(BITMAP *f, BITMAP *w, BITMAP* b){
                   this -> floor = f;
                   this -> wall = w;
                   this -> block = b;
                   inicializar();
             }
             
             MapaServer( int t , Personagem *p,volatile int * te ){
                   setTipo( t );
                   setPersonagem( p );
                   carregarImagensTiles();
                   setCronometro(te);
                   inicializar();
             }

			 MapaServer( int t , Personagem *p1, Personagem *p2, volatile int * te ){
                   setTipo( t );
                   setPersonagem( p1 );
				   setPersonagem2( p2 );
                   carregarImagensTiles();
                   setCronometro(te);
                   inicializar();
             }

             int getTipo(){
                 return tipo;
             }
             
             void setTipo(int t){
                 this->tipo = t;
             }
             
             bool aindaPodePintar(){
                  return podePintar;
             }
             
             Painel *getPainel(){
                   return this->painel;
             }
             void setPodePintar(bool p){
                   this->podePintar = p;
             }
             
             ListaObjetos2D *getListaPontos(){
                 return this -> listaPontos;
             }
             
             void carregarImagensTiles(){
                  if( this -> tipo == TIPO1 ){
                      
                      this -> floor = load_bitmap("images\\floor1.bmp" , NULL );
                      this -> wall = load_bitmap("images\\wall1.bmp" , NULL );
                      this -> block = load_bitmap("images\\block1.bmp" , NULL );
                      
                  }else if( this -> tipo == TIPO2 ){
                        
                      this -> floor = load_bitmap("images\\floor2.bmp" , NULL );
                      this -> wall = load_bitmap("images\\wall2.bmp" , NULL );
                      this -> block = load_bitmap("images\\block2.bmp" , NULL );
                      
                  }
             }
             
             ~MapaServer(){
                     delete floor;
                     delete wall;
                     delete block;
                     delete listaWall;
                     delete listaCartas;
                     delete listaPontos;
					 delete bombas1;
					 delete bombas2;
                     delete objetos;
                     delete [] arrayFumaca;
                     delete [] arrayExplosao;
                     delete [] arrayTiles;
                     delete [] arrayPontos;
                     delete somExplosao;
                     delete somCarta;

					 listaPontos = NULL;
					 listaCartas = NULL;
                     objetos = NULL;
                     listaWall = NULL;
					 bombas1 = NULL;
					 bombas2 = NULL;
             }
             
             void zerarMapa(){
                  delete listaWall;
                  delete objetos;
                  delete listaCartas;
                  delete listaPontos;
                  delete bombas1;
				  delete bombas2;

                  objetos = new ListaObjetos2D();
                  listaWall = new ListaObjetos2D();
                  listaCartas = new ListaObjetos2D();
                  listaPontos = new ListaObjetos2D();
				  bombas1 = new ListaObjetos2D();
				  bombas2 = new ListaObjetos2D();
                  
                  inicializarWalls();
                  destruirDefault();
                  destruirRandomico(DESTRUIR);
             }
             
             void inicializar(){
                   setPodePintar(false);
                   somExplosao = load_wav("sons/explosao.wav");
                   somCarta = load_wav("sons/carta.wav");

                   objetos = new ListaObjetos2D();
                   listaWall = new ListaObjetos2D();
                   listaCartas = new ListaObjetos2D();
                   listaPontos = new ListaObjetos2D();
				   bombas1 = new ListaObjetos2D();
				   bombas2 = new ListaObjetos2D();

                   inicializarArray();
                   inicializarWalls();
                   destruirDefault();
                   destruirRandomico(DESTRUIR);
                   
                   this -> personagem -> setBombaPlantada( NULL );
				   this -> player2 -> setBombaPlantada( NULL );

                   this -> proxBomba = 0;
                   this -> carregarArrayFumaca();
                   this -> carregarArrayPontos();
                   this -> carregarExplosao();
             }
            
             void setCronometro(volatile int * t){
                  this -> tempo = t;
                  this -> ultimoTempo = *tempo;
                  this -> tempoInicial = ultimoTempo;
             }
             void setNumeroBombas(int nB){
                   this -> proxBomba = nB;
             }
             
              void setMenu(MenuJogo *m){
                   this -> menu = m;
             }
             
			  ListaObjetos2D *getBombas1(){
				return this -> bombas1;
			  }

			  ListaObjetos2D *getBombas2(){
				return this -> bombas2;
			  }

             void incrementarBombas(){
                  this -> proxBomba = proxBomba  + 1;
             }
             void decrementarBombas(){
                  if(this -> proxBomba > 0){ 
                  this -> proxBomba = proxBomba - 1;
                  }
             }
             
             int getNumeroBombas(){
                 return this ->  proxBomba;
             }
             
             void setPersonagem( Personagem *p ){
                  this -> personagem = p;
				  this -> bombas1 = p -> getBombas();
             }

			 void setPersonagem2( Personagem *p ){
				 this -> player2 = p;
				 this -> bombas2 = p -> getBombas();
			 }

             void carregarArrayFumaca(){
                 arrayFumaca[0] = load_bitmap("images\\fumaca0.bmp",NULL);
                 arrayFumaca[1] = load_bitmap("images\\fumaca1.bmp",NULL);
                 arrayFumaca[2] = load_bitmap("images\\fumaca2.bmp",NULL);
             }
             
             void carregarExplosao(){
                  arrayExplosao[ 0 ] = load_bitmap("images\\nucleo0.bmp",NULL);
                  arrayExplosao[ 1 ] = load_bitmap("images\\nucleo1.bmp",NULL);
                  arrayExplosao[ 2 ] = load_bitmap("images\\nucleo2.bmp",NULL);
                  arrayExplosao[ 3 ] = load_bitmap("images\\corpo0.bmp",NULL);
                  arrayExplosao[ 4 ] = load_bitmap("images\\corpo1.bmp",NULL);
                  arrayExplosao[ 5 ] = load_bitmap("images\\corpo2.bmp",NULL);
                  arrayExplosao[ 6 ] = load_bitmap("images\\cabeca0.bmp",NULL);
                  arrayExplosao[ 7 ] = load_bitmap("images\\cabeca1.bmp",NULL);
                  arrayExplosao[ 8 ] = load_bitmap("images\\cabeca2.bmp",NULL);
             }
             
             void carregarArrayPontos(){
                 arrayPontos[0] = load_bitmap("images\\pontos0.bmp",NULL);
                 arrayPontos[1] = load_bitmap("images\\pontos100.bmp",NULL);
                 arrayPontos[2] = load_bitmap("images\\pontos200.bmp",NULL);
                 arrayPontos[3] = load_bitmap("images\\pontos300.bmp",NULL);
                 arrayPontos[4] = load_bitmap("images\\pontos400.bmp",NULL);
                 arrayPontos[5] = load_bitmap("images\\pontos500.bmp",NULL);                 
             } 

			 /* Método que retorna o TILE da linha l e coluna c */
             Tile *getTile( int l, int c ){
                  return this -> arrayTiles[ l ][ c ];
             }
             
             /* Método que retorna o Tile que contem o ponto (X,Y)*/
             Tile *getTileAtXY( int x, int y ){
                  int linha = (int)(y / TILE_HEIGHT);
                  int coluna = (int)(x / TILE_WIDTH);
                  return getTile( linha , coluna );
             }
             
             void destruirRandomico( int qnt ){
                  /* seta o gerador pra hora atual */
                  srand ( time(NULL) ); 
                  int i = 0;
                  while( i < qnt ){
                         int random = (int)(rand()%( listaWall->size() ));
                         Objeto2D *obj = listaWall -> at( random );
						 listaWall -> removerObjeto( obj );
                         i++;
                  }
			 }
                  
             void destruirWall( int linha, int coluna ){
                  int x = coluna*TILE_WIDTH;
                  int y = linha*TILE_HEIGHT;
                  int i = 0;
				  int *tam = listaWall -> getTamanho();
                  bool achou = false;
                  while( i < *tam && !achou ){
                         WallTile *wT = (WallTile*)listaWall -> at( i );
                         if( wT -> getX() == x && wT -> getY() == y ){
                             achou = true;
                             listaWall -> removerObjeto( wT );
                         }
                         i++;
                  }
             }
             
             void inserirObjeto( Objeto2D *obj ){
                  this -> objetos -> inserirObjeto( obj );
                  if(strcmp(obj->getNome() ,"Bomba") == 0){
                     this -> incrementarBombas();
                  }
             }

			 /*problema*/	
             void removerObjeto( Objeto2D *obj ){
                  if( strcmp( obj -> getNome(), "Bomba" ) == 0 ){
					  if( personagem -> hasBomba( (Bomba*)obj ) ){
							personagem -> decrementarBombas();
							this -> bombas1 -> removerObjeto( (Bomba*)obj );
					  }else if( player2 -> hasBomba( (Bomba*)obj) ){
							player2 -> decrementarBombas();
							this -> bombas2 -> removerObjeto( (Bomba*)obj );
					  }
                      decrementarBombas();
				  }else{
					  this -> objetos -> removerObjeto( obj );
				  }
             }
             
              void inserirCarta( Carta *m ){
                  this -> listaCartas -> inserirObjeto( m );
             }
             
             void removerCarta(  Carta *m ){
                  this -> listaCartas -> removerObjeto( m );
             }
             
             void inserirPontos( Pontos *m ){
                  this -> listaPontos -> inserirObjeto( m );
             }
             
             void removerPontos( Pontos *m ){
                  this -> listaPontos -> removerObjeto( m );
             }
             
             void destruirWallAtXY( int x, int y ){
                  int i = 0;
				  int *tam = listaWall -> getTamanho();
                  bool achou = false;
                  while( i < *tam && !achou ){
                         WallTile *wT = (WallTile*)listaWall -> at( i );
                         if( wT -> getX() == x && wT -> getY() == y ){
                             achou = true;
                             listaWall -> removerObjeto( wT ); 
                             int random = (int)(rand()%8);
                             if(random == 0)
                             verificarCarta(x,y);  
                         }
                         i++;
                  }
             }
             
             void verificarCarta(int x,int y){
             
                                      /*  n bombas = 40%
                                        aum forca = 40%
                                        aum vel = 10%
                                        X dim forca = 10% X
                                        X dim vel = 10% X
                                        vida = 10%
                                      */
                                  BITMAP *cartaIMG;   
                                  BITMAP *cartaIMG2; 
                                  Carta *c; 
                                
                                int r = (int)(rand()%11);
                                if(r>=0 && r < 5){
                                        cartaIMG = load_bitmap("images\\cartaBomba.bmp",NULL); 
                                        cartaIMG2 = load_bitmap("images\\cartaBomba2.bmp",NULL);
                                        c = new CartaNumBombas( cartaIMG,cartaIMG2 ,x,y,40,40 ); 
                                }else if(r>=5 && r < 9 ){
                                        cartaIMG = load_bitmap("images\\cartaFogoexe.bmp",NULL);  
                                        cartaIMG2 = load_bitmap("images\\cartaFogoexe2.bmp",NULL);  
                                        c = new CartaAumentarFogo( cartaIMG,cartaIMG2, x,y,40,40 );
                                }else if(r == 9){
                                       cartaIMG = load_bitmap("images\\cartaVelo.bmp",NULL);  
                                        cartaIMG2 = load_bitmap("images\\cartaVelo2.bmp",NULL); 
                                        c = new CartaAumentarVelocidade( cartaIMG,cartaIMG2, x,y,40,40 );
                                }else if(r == 10){
                                        cartaIMG = load_bitmap("images\\cartasuperfogo.bmp",NULL);  
                                         cartaIMG2 = load_bitmap("images\\cartasuperfogo2.bmp",NULL);
                                        c = new CartaSuperFogo( cartaIMG, cartaIMG2, x,y,40,40 );
                                }
                                this -> inserirCarta(c);
             }
             
             void destruirCartaAtXY( int x, int y ){
                  int *tam = listaCartas -> getTamanho();
				  int i = 0;
                  bool achou = false;
                  while( i < *tam && !achou ){
                         Carta *wT = (Carta*)listaCartas -> at( i );
                         if( wT -> getX() == x && wT -> getY() == y ){
                             achou = true;
                             listaCartas -> removerObjeto( wT );
                         }
                         i++;
                  }
             }
             
             void destruirDefault(){
                  destruirWall(1,1);
                  destruirWall(1,2);
                  destruirWall(2,1);
                  destruirWall(1,18);
                  destruirWall(1,17);
                  destruirWall(1,16);
                  destruirWall(5,9);
                  destruirWall(6,9);
                  destruirWall(7,9);
                  destruirWall(11,13);
                  destruirWall(11,14);
                  destruirWall(11,15);
             }
             
             bool existeWallAtXY( int x, int y ){
                  bool ret = false;
                  bool achou = false;
				  int *tam = listaWall -> getTamanho();
				  int i = 0;
                  
                  while( i < *tam && !achou ){
                         WallTile *wT = (WallTile*)listaWall -> at( i );
                         if( wT -> getX() == x && wT -> getY() == y ){
                             achou = true;
                             ret = true;
                         }
                         i++;
                  }
                  return ret;
             }
             
             
             bool existeCartaAtXY( int x, int y ){
				  bool ret = false;
                  bool achou = false;
				  int *tam = listaCartas -> getTamanho();
				  int i = 0;
                  
                  while( i < *tam && !achou ){
                         Carta *wT = (Carta*)listaCartas -> at( i );
                         if( wT -> getX() == x && wT -> getY() == y ){
                             achou = true;
                             ret = true;
                         }
                         i++;
                  }
                  return ret;
             }
             
             Objeto2D *getObjetoAtXY( int x, int y ){
                  int *tam = objetos -> getTamanho();
				  int i = 0;
                  bool achou = false;
                  Objeto2D *ret = NULL;
                  while( i < *tam && !achou ){
                         Objeto2D *obj = objetos -> at( i );
                         if( obj -> getX() == x && obj -> getY() == y ){
                             achou = true;  
                             ret = obj;                           
                         }
                         i++;
                  }
                  return ret;
             }
             
              Carta *getCartaAtXY( int x, int y ){
                  int *tam = listaCartas -> getTamanho();
				  int i = 0;
                  bool achou = false;
                  Carta *ret = NULL;
                  while( i < *tam && !achou ){
                         Carta *obj = (Carta*)listaCartas -> at( i );
                         if( obj -> getX() == x && obj -> getY() == y ){
                             achou = true;  
                             ret = obj;                           
                         }
                         i++;
                  }
                  return ret;
             }
             
             /* algoritmo modificado para dois player ( 2 listas ) */
             Bomba *getBombaAtXY( int x, int y ){
				   bool achou = false;
				   int i = 0;
				   Bomba *temp = NULL;
				   Bomba *ret = NULL;
				   while( !achou && i < bombas1 -> size() ){
						temp = (Bomba*)bombas1 -> at( i );
						if( temp -> getX() == x && temp -> getY() == y ){
							achou = true;
							ret = temp;
						}
						i++;
				   }
				   if( !achou ){
						i = 0;
						while( !achou &&  i < bombas2 -> size() ){
							temp = (Bomba*)bombas2 -> at( i );
							if( temp -> getX() == x && temp -> getY() == y ){
								achou = true;
								ret = temp;
							}
							i++;
						}
				   }
				   return ret;
             }
             
             void explodir( Bomba * b ){
                   if( b != NULL ){
                      Explosao *ex = new Explosao( b->getX(),b->getY(),arrayExplosao,Explosao::NUC,tempo);
                      inserirObjeto( ex ); 
                      b -> setDestruida( true );
                      explodirAcima( b );
                      explodirAbaixo( b );
                      explodirDireita( b );
                      explodirEsquerda( b );
                   }
             }
             
             void explodirEsquerda( Bomba *b ){
                   int x = b -> getX();
                   int y = b -> getY();
                   x = x - TILE_WIDTH;
                   bool achou = false;
                   int i = 0;
                   while( !achou && (i < b -> getForca()) ){
                          if( getTileAtXY(x,y)-> getTipo() == 2 ){
                               achou = true;
                          }else if( existeWallAtXY(x,y) ){
                              
                               destruirWallAtXY( x, y );
                               
                               achou = true;
                               Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                               inserirObjeto( f );
                          }else if(getBombaAtXY(x,y) != NULL){
                               Bomba *bomba = getBombaAtXY(x,y);
                               achou = true;
                               if( !(bomba -> isDestruida()) ){
                                  explodir( bomba );
                                  removerObjeto( bomba );
                               }
                          }else if( existeCartaAtXY(x,y) ){
                               destruirCartaAtXY( x, y );
                               achou = true;
                               Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                               inserirObjeto( f );
                          }else{
                                i++;
                               if( i == b-> getForca() ){
                                   Explosao *ex  = new Explosao( x,y,arrayExplosao,Explosao::ESQ,tempo);
                                   inserirObjeto( ex );
                               }else{
                                   Explosao *ex  = new Explosao( x,y,arrayExplosao,Explosao::HOR,tempo);
                                   inserirObjeto( ex );
                               }
                               x = x - TILE_WIDTH;
                          }
                   } 
             }
             
        
             void explodirDireita( Bomba *b ){
                      int x = b -> getX();
                      int y = b -> getY();
                      x = x + TILE_WIDTH;
                      bool achou = false;
                      int i = 0;
                     
                      while( !achou && (i < b -> getForca()) ){
                             if( getTileAtXY(x,y)-> getTipo() == 2 ){
                                achou = true;
                             }else if( existeWallAtXY(x,y) ){
                                      destruirWallAtXY( x, y );
                                      achou = true;
                                      Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                                       inserirObjeto( f );
                             }else if(getBombaAtXY(x,y) != NULL){
                                    Bomba *bomba = getBombaAtXY(x,y);
                                    achou = true;
                                    if( !(bomba -> isDestruida()) ){
                                        explodir( bomba );
                                        removerObjeto( bomba );
                                    }
                            }else if( existeCartaAtXY(x,y) ){
                               destruirCartaAtXY( x, y );
                               achou = true;
                               Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                               inserirObjeto( f );
                          }else{
                                  i++;
                                     if( i == b-> getForca() ){
                                        Explosao *ex  = new Explosao( x,y,arrayExplosao,Explosao::DIR,tempo);
                                        inserirObjeto( ex );
                                     }else{
                                        Explosao *ex  = new Explosao( x,y,arrayExplosao,Explosao::HOR,tempo);
                                        inserirObjeto( ex );
                                      }
                                      x = x + TILE_WIDTH;
                             }
                
                      }
             }
             
             void explodirAbaixo( Bomba *b ){
                  int x = b -> getX();
                  int y = b -> getY();
                  y = y + TILE_HEIGHT;
                  bool achou = false;
                  int i = 0;
                  while( !achou && (i < b -> getForca()) ){
                         if( getTileAtXY(x,y)-> getTipo() == 2 ){
                             achou = true;
                         }else if( existeWallAtXY(x,y) ){
                                  destruirWallAtXY( x, y );
                                  achou = true;
                                  Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                                   inserirObjeto( f );
                         }else if(getBombaAtXY(x,y) != NULL){
                                  Bomba *bomba = getBombaAtXY(x,y);
                                  achou = true;
                                  if( !(bomba -> isDestruida()) ){
                                      explodir( bomba );
                                      removerObjeto( bomba );
                                  }
                          }else if( existeCartaAtXY(x,y) ){
                               destruirCartaAtXY( x, y );
                               achou = true;
                               Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                               inserirObjeto( f );
                          }else{
                                i++;
                                  if( i == b-> getForca() ){
                                   Explosao *ex  = new Explosao(x,y,arrayExplosao,Explosao::BAI,tempo);
                                   inserirObjeto( ex );
                               }else{
                                   Explosao *ex  = new Explosao( x,y,arrayExplosao,Explosao::VER,tempo);
                                   inserirObjeto( ex );
                               }
                                   y = y + TILE_HEIGHT;
                         }
                   }
             }

             void explodirAcima( Bomba *b ){
                  int x = b -> getX();
                  int y = b -> getY();
                  y = y - TILE_HEIGHT;
                  bool achou = false;
                  int i = 0;
                   while( !achou && (i < b -> getForca()) ){
                          if( getTileAtXY(x,y)-> getTipo() == 2 ){
                              achou = true;
                          }else if( existeWallAtXY(x,y) ){
                                   destruirWallAtXY( x, y );
                                   Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                                   inserirObjeto( f ); 
                                  achou = true;
                          }else if(getBombaAtXY(x,y) != NULL){
                                    achou = true;
                                   Bomba *bomba = getBombaAtXY(x,y);
                                    if( !(bomba -> isDestruida()) ){
                                        explodir( bomba );
                                        
                                        removerObjeto( bomba );
                                    }
                          }else if( existeCartaAtXY(x,y) ){
                               destruirCartaAtXY( x, y );
                               achou = true;
                               Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                               inserirObjeto( f );
                          }else{
                                i++;
                                if( i == b-> getForca() ){
                                   Explosao *ex  = new Explosao( x,y,arrayExplosao,Explosao::CIM,tempo);
                                   inserirObjeto( ex );
                                }else{
                                   Explosao *ex  = new Explosao(x,y,arrayExplosao,Explosao::VER,tempo);
                                   inserirObjeto( ex );
                                }
                                  y = y - TILE_HEIGHT;
                          }
                  }
            }
            
			/* Pinta o mapa na tela. Simplesmente pinta todos os
			 * seus TILES
			 */
             void paint(BITMAP *b){
                  
                  
                  /* pintar Tiles*/
                  for( int i =0; i < LINHAS; i++ ){
                        for( int j = 0; j < COLUNAS; j++ ){
                             arrayTiles[ i ][ j ] -> paint(b);

                        }
                  }

                  /*pintar lista walls*/
				  for( int i = 0; i < listaWall -> size(); i++ ){
						((WallTile*)(listaWall -> at( i ))) -> paint( b );  
				  }
                  
                  /*pintar lista carta*/
				  for( int i = 0; i < listaCartas -> size(); i++ ){
						((Carta*)(listaCartas -> at( i ))) -> paint( b );  
				  }

				  /* pintar bombas player1 */
				  for( int i = 0; i < bombas1 -> size(); i++ ){
				      Bomba *obj = (Bomba*)bombas1 -> at( i );
					  if( obj->isDestruida() ){
						  this ->explodir( obj );
						  play_sample( somExplosao, 255, 125, 1200, 0 );
						  this -> bombas1 -> removerObjeto( obj );
					  }else{
						  obj -> paint( b,*tempo );   
					  }
					  
				  }

				  /* pintar bombas player2 */
				  for( int i = 0; i < bombas2 -> size(); i++ ){
				      Bomba *obj = (Bomba*)bombas2 -> at( i );
					  if( obj->isDestruida() ){
						  this ->explodir( obj );
						  play_sample( somExplosao, 255, 125, 1200, 0 );
						  this -> bombas2 -> removerObjeto( obj );
					  }else{
						  obj -> paint( b, *tempo);   
					  }
				  }

                  /* pintar lista objetos */
                  Objeto2D *obj = NULL;
				  int *tamO = objetos -> getTamanho();
				  int h = 0;

                  while( h < *tamO ){
                         obj = objetos -> at( h );
                         if( obj != NULL ){
                           if(  obj->getTipo()== 1 ){
                               if(((Fumaca*)obj)->isMorto()){                         
                                  this -> removerObjeto( obj );
                               }else{
                                  ((Fumaca*)obj) -> paint( b );
                               }
                           }else if( obj->getTipo() == 3){
                                 if( ((Explosao*)obj)-> isMorto() ){
                                     this -> removerObjeto( obj );
                                 }else{
                                       if( personagem -> colideCaixa(obj)&& !((Explosao*)obj)->jaMatouPersonagem()){
                                          personagem -> setEstadoAtual( Personagem::MORRENDO );
                                           ((Explosao*)obj)->setJaMatou( true );
									   }
									   if( player2 -> colideCaixa(obj)&& !((Explosao*)obj)->jaMatouPlayer2()){
                                          player2 -> setEstadoAtual( Personagem::MORRENDO );
                                          
                                           ((Explosao*)obj)->setJaMatouPlayer2( true );
									   }
                                       ((Explosao*)obj)-> paint( b );
                                 }
                           }
                         }else{
                           break;
                         }
                           h++;
                           obj = NULL;
                  }//fim while
                  
                   if(podePintar){
                     painel->paint(b);
                   if(painel->jaTerminou()){
                      setPodePintar(false);                   
                     }
                   }
             }//fim paint


			 void inserirSeriais( vector<ObjetoSerial *> *array ){
				UltimaTentativa *o = new UltimaTentativa();
				
				for( int i = 0; i < (listaWall -> size()) ; i++ ){
						o = ((WallTile*)(listaWall -> at( i ))) -> getSerial();
						inserirUltima( o , array );
					
				  }

			for( int i = 0; i < (listaCartas -> size()) ; i++ ){
						o = ((Carta *)(listaCartas -> at( i ))) -> getSerial();
						inserirUltima( o , array );
					
				  }

				for( int i = 0; i < (listaPontos -> size()) ; i++ ){
						o = ((Pontos*)(listaPontos -> at( i ))) -> getSerial();
						inserirUltima( o , array );
					
				  }

				Objeto2D *objeto ;
				for( int i = 0; i < (objetos -> size()) ; i++ ){
						objeto = objetos -> at( i );

						if( strcmp(objeto ->getNome(), "Fumaca" )== 0 ){
                           o = ((Fumaca *)( objeto ) )-> getSerial();
							inserirUltima( o , array );

						}else if( strcmp( objeto -> getNome(), "Explosao") == 0){

							 o = ((Explosao *)( objeto ) )-> getSerial();
							inserirUltima( o , array );

						}
						
					
				  }

				for( int i = 0; i < (bombas1 -> size()) ; i++ ){
						o = ((Bomba*)(bombas1 -> at( i ))) -> getSerial();
						inserirUltima( o , array );
					
				  }

				for( int i = 0; i < (bombas2 -> size()) ; i++ ){
						o = ((Bomba*)(bombas2 -> at( i ))) -> getSerial();
						inserirUltima( o , array );
					
				  }

			 }

			 


		    void inserirUltima(UltimaTentativa *ult,vector<ObjetoSerial *> *array ){
			ObjetoSerial *porr = new ObjetoSerial();
			porr->tipo = ult->tipo;
			porr->x = ult->x;
			porr->y = ult->y; 
			porr->info1 = ult->info1;
			porr->info2 = ult->info2;
			porr->info3 = ult->info3;
			porr->info4 = ult->info4;
			porr->info5 = ult->info5;
			porr->info6 = ult->info6;
			porr->info7 = ult->info7;
			porr->info8 = ult->info8;
			porr->info9 = ult->info9;
			porr->info10 = ult->info10;
            array -> push_back( porr );
		  }

			VetorObjetos getSerializable(){
				 VetorObjetos v;
				 v.vetor.length(NUM_OBJE);


				 int j = 0;

				 //walls
				 for( int i = 0; i < (listaWall -> size()) ; i++ ){
						v.vetor[j] = ((WallTile*)(listaWall -> at( i ))) -> getSerializable();  
						j++;
				  }


				 //cartas
				  for( int i = 0; i < listaCartas -> size() ; i++ ){
						v.vetor[j] = ((Carta*)(listaCartas -> at( i ))) -> getSerializable();
						j++;
				  }


				  //bombas player 1
				  for( int i = 0; i < bombas1 -> size() ; i++ ){
				      v.vetor[j] = ((Bomba*)bombas1 -> at( i )) -> getSerializable();
					  j++;
				  }

				  //bombas player 2
				  for( int i = j; i < bombas2 -> size() ; i++ ){
				      v.vetor[j] = ((Bomba*)bombas2 -> at( i )) -> getSerializable();
					  j++;
				  }

                  // lista objetos
                  Objeto2D *obj = NULL;
				  int *tamO = objetos -> getTamanho();
				  int h = 0;

                  while( h < *tamO ){
                         obj = objetos -> at( h );
                         if( obj != NULL ){
                           if(  obj->getTipo()== 1 ){
                                v.vetor[j] = ((Fumaca*)obj) -> getSerializable();
                           }else if( obj->getTipo() == 3){  
                                 v.vetor[j] = ((Explosao*)obj) -> getSerializable();
                           }
                         }else{
                           break;
                         }
                           h++;
						   j++;
                           obj = NULL;
                  }//fim while
                  
				  //painel
                   if(podePintar){
                     v.vetor[j] = painel -> getSerializable();
                   j++;
                   }

				   while (j < NUM_OBJE){
						v.vetor[ j ].tipo = 0;
						j++;
				   }

				 return v;
				 
			 }
             
             void inserirWall( WallTile *wT ){
                  this -> listaWall -> inserirObjeto( wT );
             }
             
             void removerWall( WallTile *wT ){
                  this -> listaWall -> removerObjeto( wT );
             }
             
             void inicializarWalls(){
                  for( int linha = 0; linha < LINHAS; linha++ ){
                       for( int coluna = 0; coluna < COLUNAS; coluna++ ){
                           
                            if( getTile(linha,coluna) -> getTipo() == 0 ){
                                 WallTile *tW = new WallTile( wall );
                                 tW -> setBounds(coluna*TILE_WIDTH,
                                                 linha*TILE_HEIGHT,
                                                 TILE_WIDTH,
                                                 TILE_HEIGHT);
                                this -> inserirWall( tW );
                                
                            }
                       }
                  }
             }

			/* Algoritmo que replica as imagens dos TILES em seus
			 * respectivos locais. Neste exemplo cria uma arena vazia
			 * cercada de paredes pelos 4 lados.
			 */
             void inicializarArray(){
                  // laço que desenha os tiles do chao
                  for( int i = 0; i < LINHAS ; i++){
                       for(int j = 0; j < COLUNAS; j++){
                               arrayTiles[i][j] = new FloorTile(floor);
                               arrayTiles[i][j] -> setBounds(
                                   j*TILE_WIDTH , i*TILE_HEIGHT
                                   , TILE_WIDTH , TILE_HEIGHT);
                      }
                  }  
                  //desenha as paredes laterais(ESQ,DIR)
                  for(int i = 0; i < LINHAS; i++ ){
                    if(arrayTiles[i][0] != NULL )
                        delete arrayTiles[i][0];
                    arrayTiles[i][0] = new BlockTile(block);
                    arrayTiles[i][0] -> setBounds( 0, i*TILE_HEIGHT,
                                          TILE_WIDTH , TILE_HEIGHT);

                    if(arrayTiles[i][COLUNAS - 1] != NULL )
                        delete arrayTiles[i][COLUNAS - 1];
                    arrayTiles[i][COLUNAS - 1] = new BlockTile(block);
                    arrayTiles[i][COLUNAS - 1]->setBounds((COLUNAS - 1)*TILE_WIDTH,
                    i*TILE_HEIGHT, TILE_WIDTH,TILE_HEIGHT);

                  }
                    //paredes superior e inferior
                    for(int i = 0; i < COLUNAS; i++ ){
                      if(arrayTiles[0][i] != NULL )
                          delete arrayTiles[0][i];
                      arrayTiles[0][i] = new BlockTile(block);
                      arrayTiles[0][i] -> setBounds( i*TILE_WIDTH, 0,
                                           TILE_WIDTH , TILE_HEIGHT);

                      if(arrayTiles[LINHAS - 1][i] != NULL )
                          delete arrayTiles[LINHAS - 1][i];
                      arrayTiles[LINHAS - 1][i] = new BlockTile(block);
                      arrayTiles[LINHAS - 1][i]->setBounds(i*TILE_WIDTH,
                      (LINHAS-1)*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT );
                    }

                     for( int i = 0; i < LINHAS ; i++){
                       for(int j = 0; j < COLUNAS; j++){
                               if( i%2 == 0 && j%2 == 0 ){
                                 if(arrayTiles[i][j] != NULL )
                                   delete arrayTiles[i][j];
                               arrayTiles[i][j] = new BlockTile(block);
                               arrayTiles[i][j] -> setBounds(
                                   j*TILE_WIDTH , i*TILE_HEIGHT
                                   , TILE_WIDTH , TILE_HEIGHT);
                                   }
                      }
                  }
                                                            
             }
             
             const char *getNome(){
                   return "Mapa";
             }
             
           bool colideCaixaDir( Objeto2D *obj ){
                int x = obj -> getCaixaColisao() -> getX() +obj -> getCaixaColisao() -> getLargura();
                int y = obj -> getCaixaColisao() -> getY();
                int x2 = x;
                int y2 = y + obj -> getCaixaColisao() -> getAltura();
                
                Tile *t1 = getTileAtXY( x, y );
                Tile *t2 = getTileAtXY( x2, y2 );
                
                bool co = false;
                bool co2 = false;
                if( t1->getTipo() == 2 || t1->getTipo() == 1 ) co = true;
                if( t2 -> getTipo() == 2 || t2 -> getTipo() == 1 )co2= true;
                
               
                if( existeWallAtXY( t1 -> getX(), t1 -> getY() ) ) co = true;
                if( existeWallAtXY( t2 -> getX(), t2 -> getY() ) ) co2 = true;
                
                Bomba *bomb = getBombaAtXY( t1->getX(),t1->getY());
                Bomba *bomb2 = getBombaAtXY(t2->getX(),t2->getY());
                if( bomb != NULL )co = true;
                if( bomb2 != NULL )co2 = true;
                
                 
                if( strcmp( obj -> getNome(), "Personagem" ) == 0 ){
                    
                    Bomba *b = ((Personagem*)obj)->getBombaPlantada();
                    if( b != NULL && ((Personagem*)obj) -> getNumBombas() > 0){
                       if( ((Personagem*)obj) -> colideCaixa( b ) ){
                          if( !((Personagem*)obj) -> isPodePassar() ){
                            if( bomb == b )co = true;
                            if( bomb2 == b )co2 = true;
                          }else{
                            if(bomb == b ) co = false;
                             if(bomb2 == b )co2 = false;
                          }
                       }else{
                             ((Personagem*)obj) -> setPodePassar( false );
                       }
                  }
                
                    
                    if( !co && co2 ){
                       if( !colideCaixaCima(obj) )
                         obj -> setY( obj-> getY() - 1 );
                    }
                    if( !co2 && co ){
                       if( !colideCaixaBaixo(obj) )
                         obj -> setY( obj-> getY() + 1 );
                    }
                    if (existeCartaAtXY( t1 -> getX(), t1 -> getY() )){
                     Carta *carta = this -> getCartaAtXY(t1 -> getX(), t1 -> getY());
                     carta -> atuar( ((Personagem *)obj) );
                     int pontos = carta -> getPontos();
                     this -> addPontos(pontos, carta->getX(), carta->getY());
                     play_sample( somCarta, 255, 125, SOM_FREQ, 0 );
                     listaCartas -> removerObjeto(carta);
                     co = false;
                    }
                    
                  
                }
                
                return ( co || co2 );
             
           }
           
           bool colideCaixaCima( Objeto2D *obj ){
                int x = obj -> getCaixaColisao() -> getX();
                int y = obj -> getCaixaColisao() -> getY();
                int x2 = obj -> getCaixaColisao() -> getX() +obj -> getCaixaColisao() -> getLargura();
                
                int y2 = y ;
                
                Tile *t1 = getTileAtXY( x, y );
                Tile *t2 = getTileAtXY( x2, y2 );
                
                bool co = false;
                bool co2 = false;
                if( t1->getTipo() == 2 || t1->getTipo() == 1 ) co = true;
                if( t2 -> getTipo() == 2 || t2 -> getTipo() == 1 )co2= true;
                
                
                if( existeWallAtXY( t1 -> getX(), t1 -> getY() ) ) co = true;
                if( existeWallAtXY( t2 -> getX(), t2 -> getY() ) ) co2 = true;
                
                Bomba *bomb = getBombaAtXY( t1->getX(),t1->getY());
                Bomba *bomb2 = getBombaAtXY(t2->getX(),t2->getY());
                if( bomb != NULL )co = true;
                if( bomb2 != NULL )co2 = true;
                
                
                  
                if( strcmp( obj -> getNome(), "Personagem" ) == 0 ){
                    Bomba *b = ((Personagem*)obj)->getBombaPlantada();
                    if( b != NULL && ((Personagem*)obj) -> getNumBombas() > 0){
                       if( ((Personagem*)obj) -> colideCaixa( b ) ){
                          if( !((Personagem*)obj) -> isPodePassar() ){
                            if( bomb == b )co = true;
                            if( bomb2 == b )co2 = true;
                          }else{
                            if(bomb == b ) co = false;
                             if(bomb2 == b )co2 = false;
                          }
                       }else{
                             ((Personagem*)obj) -> setPodePassar( false );
                       }
                  }
                    
                   if( !co && co2 ){
                      if( !colideCaixaEsq(obj) )
                      obj -> setX( obj-> getX() - 1 );
                  }
                  if( !co2 && co ){
                      if( !colideCaixaDir(obj) )
                      obj -> setX( obj-> getX() + 1 );
                  }
                    if (existeCartaAtXY( t1 -> getX(), t1 -> getY() )){
                     Carta *carta = this -> getCartaAtXY(t1 -> getX(), t1 -> getY());
                     carta -> atuar( ((Personagem *)obj) );
                     int pontos = carta -> getPontos();
                     this -> addPontos(pontos, carta->getX(), carta->getY());
                     play_sample( somCarta, 255, 125, SOM_FREQ, 0 );
                     listaCartas -> removerObjeto(carta);
                     co = false;
                    }
                }
                
                return ( co || co2 );
             
           }
           
           bool colideCaixaBaixo( Objeto2D *obj ){
                int x = obj -> getCaixaColisao() -> getX();
                int y = obj -> getCaixaColisao() -> getY() + obj -> getCaixaColisao() -> getAltura();
                int x2 = obj -> getCaixaColisao() -> getX() +obj -> getCaixaColisao() -> getLargura();
                
                int y2 = y ;
                
                Tile *t1 = getTileAtXY( x, y );
                Tile *t2 = getTileAtXY( x2, y2 );
                
                bool co = false;
                bool co2 = false;
                if( t1->getTipo() == 2 || t1->getTipo() == 1 ) co = true;
                if( t2 -> getTipo() == 2 || t2 -> getTipo() == 1 )co2= true;
                
                
                if( existeWallAtXY( t1 -> getX(), t1 -> getY() ) ) co = true;
                if( existeWallAtXY( t2 -> getX(), t2 -> getY() ) ) co2 = true;
                
                Bomba *bomb = getBombaAtXY( t1->getX(),t1->getY());
                Bomba *bomb2 = getBombaAtXY(t2->getX(),t2->getY());
                if( bomb != NULL )co = true;
                if( bomb2 != NULL )co2 = true;
                
                
                
                if( strcmp( obj -> getNome(), "Personagem" ) == 0 ){
                    Bomba *b = ((Personagem*)obj)->getBombaPlantada();
                    if( b != NULL && ((Personagem*)obj) -> getNumBombas() > 0){
                       if( ((Personagem*)obj) -> colideCaixa( b ) ){
                          if( !((Personagem*)obj) -> isPodePassar() ){
                            if( bomb == b )co = true;
                            if( bomb2 == b )co2 = true;
                          }else{
                            if(bomb == b ) co = false;
                             if(bomb2 == b )co2 = false;
                          }
                       }else{
                             ((Personagem*)obj) -> setPodePassar( false );
                       }
                  }
                    
                    if( !co && co2 ){
                      if( !colideCaixaEsq(obj) )
                      obj -> setX( obj-> getX() - 1 );
                  }
                  if( !co2 && co ){
                      if( !colideCaixaDir(obj) )
                      obj -> setX( obj-> getX() + 1 );
                  }
                    if (existeCartaAtXY( t1 -> getX(), t1 -> getY() )){
                     Carta *carta = this -> getCartaAtXY(t1 -> getX(), t1 -> getY());
                     carta -> atuar( ((Personagem *)obj) );
                     int pontos = carta -> getPontos();
                     this -> addPontos(pontos, carta->getX(), carta->getY());
                     play_sample( somCarta, 255, 125, SOM_FREQ, 0 );
                     listaCartas -> removerObjeto(carta);
                     co = false;
                    }
                }
                
                return ( co || co2 );
             
           }
           
           bool colideCaixaEsq( Objeto2D *obj ){
                int x = obj -> getCaixaColisao() -> getX();
                int y = obj -> getCaixaColisao() -> getY();
                int x2 = x;
                int y2 = y + obj -> getCaixaColisao() -> getAltura();
                
                Tile *t1 = getTileAtXY( x, y );
                Tile *t2 = getTileAtXY( x2, y2 );
                
                bool co = false;
                bool co2 = false;
                if( t1->getTipo() == 2 || t1->getTipo() == 1 ) co = true;
                if( t2 -> getTipo() == 2 || t2 -> getTipo() == 1 )co2= true;
                
                
                if( existeWallAtXY( t1 -> getX(), t1 -> getY() ) ) co = true;
                if( existeWallAtXY( t2 -> getX(), t2 -> getY() ) ) co2 = true;
                
                Bomba *bomb = getBombaAtXY( t1->getX(),t1->getY());
                Bomba *bomb2 = getBombaAtXY(t2->getX(),t2->getY());
                if( bomb != NULL )co = true;
                if( bomb2 != NULL )co2 = true;
                
                
                
                if( strcmp( obj -> getNome(), "Personagem" ) == 0 ){
                    Bomba *b = ((Personagem*)obj)->getBombaPlantada();
                    if( b != NULL && ((Personagem*)obj) -> getNumBombas() > 0){
                       if( ((Personagem*)obj) -> colideCaixa( b ) ){
                          if( !((Personagem*)obj) -> isPodePassar() ){
                            if( bomb == b )co = true;
                            if( bomb2 == b )co2 = true;
                          }else{
                            if(bomb == b ) co = false;
                             if(bomb2 == b )co2 = false;
                          }
                       }else{
                             ((Personagem*)obj) -> setPodePassar( false );
                       }
                  }
                    
                    if( !co && co2 ){
                    if( !colideCaixaCima(obj) )
                    obj -> setY( obj-> getY() - 1 );
                }
                if( !co2 && co ){
                    if( !colideCaixaBaixo(obj) )
                    obj -> setY( obj-> getY() + 1 );
                }
                    if (existeCartaAtXY( t1 -> getX(), t1 -> getY() )){
                     Carta *carta = this -> getCartaAtXY(t1 -> getX(), t1 -> getY());
                     carta -> atuar( ((Personagem *)obj) );
                     int pontos = carta -> getPontos();
                     this -> addPontos(pontos, carta->getX(), carta->getY());
                     play_sample( somCarta, 255, 125, SOM_FREQ, 0 );
                     listaCartas -> removerObjeto(carta);
                     co = false;
                    }
                }
                
                return ( co || co2 );
             
           }

          void addPontos(int p, int x, int y){
               Pontos *pontos = new Pontos(arrayPontos[p/100], x, y, tempo, p);
               this -> inserirPontos(pontos);
          }


		 
};
#endif