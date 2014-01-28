#ifndef MAPA_H
#define MAPA_H


#include <allegro.h>
#include <ctime>
#include "tile.h"
#include <typeinfo>
#include <cstring>
#include <cmath>

#include "lista.cpp"
#include "carta.h"
#include "bomba.h"
#include "pontos.h"
#include "explosao.h"
#include "painel.h"
#include "ninja.h"
#include "menuJogo.cpp"
#include "fumaca.h"
#include "monstro.h"
#include "MonstroVerde.cpp"
#include "caveiraRosa.cpp"
#include "portal.h"

 
#define LINHAS 13
#define COLUNAS 20
#define NUM_DEST 4
#define TILE_WIDTH 40
#define TILE_HEIGHT 40
#define NUM_BOMBAS  4
#define NUM_FUMACA  3
#define NUM_PONTOS  6
#define NUM_IMAGEM_MV 32
#define NUM_IMAGEM_CR 25
#define DESTRUIR 80
#define NUM_IMAGEM_EXP 9
#define SOM_FREQ 2000

/* Classe que representa um Mapa, ou seja, um estágio do jogo.
 * Essa classe possui um array bidimensional de TILES.
 * Cada estágio também tem suas próprias imagens dos seus TILES.
 * Sendo floor a imagem do chão daquele estágio.
 * Sendo wall a imagem da parede daquele estágio.
 * Sendo block a imagem do TILE bloqueador daquele estágio.
 * Sendo destruindo um array de imagens do TILE wall sendo destruido
 */
class Mapa: public Objeto2D{

      private:

              Tile *arrayTiles[LINHAS][COLUNAS];
              BITMAP *imagemPortal;
              BITMAP *floor;
              BITMAP *wall;
              BITMAP *block;
              BITMAP *arrayMonstroVerde[NUM_IMAGEM_MV];
              BITMAP *arrayCaveiraRosa[NUM_IMAGEM_CR];
              BITMAP *arrayFumaca[NUM_FUMACA];
              BITMAP *arrayPontos[NUM_PONTOS];
              Personagem *personagem;
              ListaObjetos2D *listaWall;
              ListaObjetos2D *listaMonstros;
              ListaObjetos2D *listaCartas;
              ListaObjetos2D *objetos;
              ListaObjetos2D *listaPontos;
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
             bool colidiuPassagem; 
             Portal *passagem; 
             int ultimoPonto;
   
      public:
             static const int TIPO1 = 0;
             static const int TIPO2 = 1;
      		/* Construtor Default */
             Mapa(){ 
                   inicializar();
                   
             }

             /* Construtor Completo */
             Mapa(BITMAP *f, BITMAP *w, BITMAP* b, BITMAP *d[]){
                   this -> floor = f;
                   this -> wall = w;
                   this -> block = b;
                   inicializar();
             }
             
             
             /* Construtor que recebe as 3 imagens  */
             Mapa(BITMAP *f, BITMAP *w, BITMAP* b){
                   this -> floor = f;
                   this -> wall = w;
                   this -> block = b;
                   inicializar();
             }
             
             Mapa( int t , Personagem *p,volatile int * te ){
                   setTipo( t );
                   setPersonagem( p );
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
             
             ~Mapa(){
                     free(floor);
                     free(wall);
                     free(block);
                     free(listaWall);
                     listaWall = NULL;
                     free(listaMonstros);
                     listaMonstros = NULL;
                     free(listaCartas);
                     listaCartas = NULL;
                     free(listaPontos);
                     listaPontos = NULL;
                     free(objetos);
                     objetos = NULL;
                     delete [] arrayMonstroVerde;
                     delete [] arrayCaveiraRosa;
                     delete [] arrayFumaca;
                     delete [] arrayExplosao;
                     delete [] arrayTiles;
                     delete [] arrayPontos;
                     free(somExplosao);
                     free(somCarta);
                     destruirPassagem();
             }
             
             void zerarMapa(){
                  free(listaWall);
                  free(listaMonstros);
                  free(objetos);
                  free(listaCartas);
                  free(listaPontos);
                  
                  objetos = new ListaObjetos2D();
                  listaWall = new ListaObjetos2D();
                  listaMonstros = new ListaObjetos2D();
                  listaCartas = new ListaObjetos2D();
                  listaPontos = new ListaObjetos2D();
                  
                  inicializarWalls();
                   destruirDefault();
                  destruirRandomico(DESTRUIR);
                 
             }
             
             void inicializar(){
                   this -> passagem = NULL;
                   setPodePintar(false);
                   this -> carregarImagemPortal();
                   somExplosao = load_wav("sons/explosao.wav");
                   somCarta = load_wav("sons/carta.wav");
                   objetos = new ListaObjetos2D();
                   listaWall = new ListaObjetos2D();
                   listaMonstros = new ListaObjetos2D();
                   listaCartas = new ListaObjetos2D();
                   listaPontos = new ListaObjetos2D();
                   //personagem = new Personagem();
                   inicializarArray();
                   inicializarWalls();
                   destruirDefault();
                   destruirRandomico(DESTRUIR);
                   
                   
                   this -> personagem -> setBombaPlantada( NULL );
                   this -> proxBomba = 0;
                   this -> carregarArrayFumaca();
                   this -> carregarArrayPontos();
                   this -> carregarMonstroVerde();
                   this -> carregarExplosao();
                   this -> carregarCaveiraRosa();
                     
                   criarMonstros();
                   //this -> passagem = NULL;
                   this -> colidiuPassagem = false;
                   
                   //criarCaveiraRosa(200,200, tempo,Monstro::vertical);
                 
               
             }
             
             void criarMonstros(){
             if(this->tipo == TIPO1){
                criarMonstroVerde(640,14,tempo,Monstro::horizontal);
                criarMonstroVerde(356,240,tempo,Monstro::vertical);
                criarMonstroVerde(530,414,tempo,Monstro::horizontal);
             }else if(this->tipo == TIPO2){
                 criarCaveiraRosa(640,40,tempo,Monstro::horizontal);
                 criarCaveiraRosa(358,240,tempo,Monstro::vertical);
                 criarCaveiraRosa(530,440,tempo,Monstro::horizontal);
             }
             }
             
             void criarMonstroVerde( int x, int y,volatile int *t , int direcao){
             MonstroVerde *m = new MonstroVerde(arrayMonstroVerde , t, direcao);
             if(direcao == Monstro::horizontal){
                m->setDirecaoAtual(Monstro::direita);
             }else{
                m->setDirecaoAtual(Monstro::cima);
             }
             m->setBounds(x,y,46,63);
             inserirMonstro(m);
             }
             
             void criarCaveiraRosa( int x, int y,volatile int *t , int direcao){
             CaveiraRosa *c = new CaveiraRosa(arrayCaveiraRosa , t, direcao);
             if(direcao == Monstro::horizontal){
                c->setDirecaoAtual(Monstro::direita);
             }else{
                c->setDirecaoAtual(Monstro::cima);
             }
             c->setBounds(x,y,40,39);
             inserirMonstro(c);
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
             
             void setPersonagem(Personagem *p){
                  this -> personagem = p;
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
             
             void carregarCaveiraRosa(){
                 arrayCaveiraRosa[0] = load_bitmap("images\\caveira.bmp",NULL);
                 arrayCaveiraRosa[1] = load_bitmap("images\\caveira2.bmp",NULL);
                 arrayCaveiraRosa[2] = load_bitmap("images\\caveira3.bmp",NULL);
                 arrayCaveiraRosa[3] = load_bitmap("images\\caveira4.bmp",NULL);
                 arrayCaveiraRosa[4] = load_bitmap("images\\caveira5.bmp",NULL);
                 arrayCaveiraRosa[5] = load_bitmap("images\\caveira6.bmp",NULL);
                 arrayCaveiraRosa[6] = load_bitmap("images\\caveira7.bmp",NULL);
                 arrayCaveiraRosa[7] = load_bitmap("images\\caveira8.bmp",NULL);
                 arrayCaveiraRosa[8] = load_bitmap("images\\caveiracostas.bmp",NULL);
                 arrayCaveiraRosa[9] = load_bitmap("images\\caveiralado.bmp",NULL);
                 arrayCaveiraRosa[10] = load_bitmap("images\\caveiralado2.bmp",NULL);
                 arrayCaveiraRosa[11] = load_bitmap("images\\caveiralado3.bmp",NULL);
                 arrayCaveiraRosa[12] = load_bitmap("images\\caveiralado4.bmp",NULL);
                 arrayCaveiraRosa[13] = load_bitmap("images\\caveiralado5.bmp",NULL);
                 arrayCaveiraRosa[14] = load_bitmap("images\\caveiralado6.bmp",NULL);
                 arrayCaveiraRosa[15] = load_bitmap("images\\caveiralado7.bmp",NULL);
                 arrayCaveiraRosa[16] = load_bitmap("images\\caveiralado8.bmp",NULL);
                 arrayCaveiraRosa[17] = load_bitmap("images\\caveiraladodir.bmp",NULL);
                 arrayCaveiraRosa[18] = load_bitmap("images\\caveiraladodir2.bmp",NULL);
                 arrayCaveiraRosa[19] = load_bitmap("images\\caveiraladodir3.bmp",NULL);
                 arrayCaveiraRosa[20] = load_bitmap("images\\caveiraladodir4.bmp",NULL);
                 arrayCaveiraRosa[21] = load_bitmap("images\\caveiraladodir5.bmp",NULL);
                 arrayCaveiraRosa[22] = load_bitmap("images\\caveiraladodir6.bmp",NULL);
                 arrayCaveiraRosa[23] = load_bitmap("images\\caveiraladodir7.bmp",NULL);
                 arrayCaveiraRosa[24] = load_bitmap("images\\caveiraladodir8.bmp",NULL);
             } 
             
             
             void carregarArrayPontos(){
                 arrayPontos[0] = load_bitmap("images\\pontos0.bmp",NULL);
                 arrayPontos[1] = load_bitmap("images\\pontos100.bmp",NULL);
                 arrayPontos[2] = load_bitmap("images\\pontos200.bmp",NULL);
                 arrayPontos[3] = load_bitmap("images\\pontos300.bmp",NULL);
                 arrayPontos[4] = load_bitmap("images\\pontos400.bmp",NULL);
                 arrayPontos[5] = load_bitmap("images\\pontos500.bmp",NULL);
                 
                 
             } 
             

             void carregarMonstroVerde(){
                    arrayMonstroVerde[0]=load_bitmap("images\\monstrov1.bmp",NULL);
                    arrayMonstroVerde[1]=load_bitmap("images\\monstrov2.bmp",NULL);
                    arrayMonstroVerde[2]=load_bitmap("images\\monstrov3.bmp",NULL);
                    arrayMonstroVerde[3]=load_bitmap("images\\monstrov4.bmp",NULL);
                    arrayMonstroVerde[4]=load_bitmap("images\\monstrov5.bmp",NULL);
                    arrayMonstroVerde[5]=load_bitmap("images\\monstrov6.bmp",NULL);
                    arrayMonstroVerde[6]=load_bitmap("images\\monstrov7.bmp",NULL);
                    arrayMonstroVerde[7]=load_bitmap("images\\monstrov8.bmp",NULL);
                    arrayMonstroVerde[8]=load_bitmap("images\\monstrov9.bmp",NULL);
                    arrayMonstroVerde[9]=load_bitmap("images\\monstrov10.bmp",NULL);
                    arrayMonstroVerde[10]=load_bitmap("images\\monstrovcostas1.bmp",NULL);
                    arrayMonstroVerde[11]=load_bitmap("images\\monstrovcostas2.bmp",NULL);
                    arrayMonstroVerde[12]=load_bitmap("images\\monstrovcostas3.bmp",NULL);
                    arrayMonstroVerde[13]=load_bitmap("images\\monstrovcostas4.bmp",NULL);
                    arrayMonstroVerde[14]=load_bitmap("images\\monstrovcostas5.bmp",NULL);
                    arrayMonstroVerde[15]=load_bitmap("images\\monstrovcostas6.bmp",NULL);
                    arrayMonstroVerde[16]=load_bitmap("images\\monstrovcostas7.bmp",NULL);
                    arrayMonstroVerde[17]=load_bitmap("images\\monstrovcostas8.bmp",NULL);
                    arrayMonstroVerde[18]=load_bitmap("images\\monstrovlado1.bmp",NULL);
                    arrayMonstroVerde[19]=load_bitmap("images\\monstrovlado2.bmp",NULL);
                    arrayMonstroVerde[20]=load_bitmap("images\\monstrovlado3.bmp",NULL);
                    arrayMonstroVerde[21]=load_bitmap("images\\monstrovlado4.bmp",NULL);
                    arrayMonstroVerde[22]=load_bitmap("images\\monstrovlado5.bmp",NULL);
                    arrayMonstroVerde[23]=load_bitmap("images\\monstrovlado6.bmp",NULL);
                    arrayMonstroVerde[24]=load_bitmap("images\\monstrovlado7.bmp",NULL);
                    arrayMonstroVerde[25]=load_bitmap("images\\monstrovladodir1.bmp",NULL);
                    arrayMonstroVerde[26]=load_bitmap("images\\monstrovladodir2.bmp",NULL);
                    arrayMonstroVerde[27]=load_bitmap("images\\monstrovladodir3.bmp",NULL);
                    arrayMonstroVerde[28]=load_bitmap("images\\monstrovladodir4.bmp",NULL);
                    arrayMonstroVerde[29]=load_bitmap("images\\monstrovladodir5.bmp",NULL);
                    arrayMonstroVerde[30]=load_bitmap("images\\monstrovladodir6.bmp",NULL);
                    arrayMonstroVerde[31]=load_bitmap("images\\monstrovladodir7.bmp",NULL);
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
                  int random = (int)(rand()%( listaWall->size() ));
				  Objeto2D *obj = listaWall -> at( random );
				  this -> criarPassagem( obj -> getX(), obj -> getY() );
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
             
             
   
             void removerObjeto( Objeto2D *obj ){
                  if( strcmp( obj -> getNome(), "Bomba" ) == 0 ){
                      personagem -> decrementarBombas();
                      decrementarBombas();
                      
                  }
                  this -> objetos -> removerObjeto( obj );
             }
             
             void inserirMonstro( Monstro *m ){
                  this -> listaMonstros -> inserirObjeto( m );
             }
             
             void removerMonstro(  Monstro *m ){
                  this -> listaMonstros -> removerObjeto( m );
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
             
             
                void destruirMonstroAtXY( int x, int y ){
                  int *tam = listaMonstros -> getTamanho();
				  int i = 0;
                  bool achou = false;
                  while( i < *tam && !achou ){
                         Monstro *wT = (Monstro*)listaMonstros -> at( i );
                         if( wT -> getX() == x && wT -> getY() == y ){
                             achou = true;
                             listaMonstros -> removerObjeto( wT );
                         }
                         i++;
                  }
             }
             
             void carregarImagemPortal(){
                this -> imagemPortal = load_bitmap("images\\portal.bmp", NULL);
             }
             
             void criarPassagem( int x, int y ){
                  this -> passagem = new Portal( imagemPortal , x, y );
                  //is -> inserirObjeto( passagem );
             }
             
             bool zerouMapa(){
                 return this -> colidiuPassagem;
             }
             
             void setZerouMapa( bool b ){
                 this -> colidiuPassagem = b;     
             }
             
             void destruirPassagem(){
                 delete( passagem );
                 this -> passagem = NULL;
             }
             
             bool acabouMonstros(){
                  return (listaMonstros -> size() == 0);                  
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
                                
                                int r = (int)(rand()%10);
                                if(r>=0 && r < 5){
                                        cartaIMG = load_bitmap("images\\cartaBomba.bmp",NULL); 
                                        cartaIMG2 = load_bitmap("images\\cartaBomba2.bmp",NULL);
                                        c = new CartaNumBombas( cartaIMG,cartaIMG2 ,x,y,40,40 ); 
                                }else if(r>=5 && r < 9 ){
                                        cartaIMG = load_bitmap("images\\cartaFogoexe.bmp",NULL);  
                                        cartaIMG2 = load_bitmap("images\\cartaFogoexe2.bmp",NULL);  
                                        c = new CartaAumentarFogo( cartaIMG,cartaIMG2, x,y,40,40 );
                                     //  c = new CartaNumBombas( cartaIMG, p,y,40,40 ); 
                                }else /*if( r>=11 && r < 15)*/if(r == 9){
                                       cartaIMG = load_bitmap("images\\cartaVelo.bmp",NULL);  
                                        cartaIMG2 = load_bitmap("images\\cartaVelo2.bmp",NULL); 
                                   //     c = new CartaNumBombas( cartaIMG, p,y,40,40 ); 
                                        c = new CartaAumentarVelocidade( cartaIMG,cartaIMG2, x,y,40,40 );
                                }else if(r>=11 && r < 15){
                                        cartaIMG = load_bitmap("images\\cartasuperfogo.bmp",NULL);  
                                         cartaIMG2 = load_bitmap("images\\cartasuperfogo2.bmp",NULL);
                                    //    c = new CartaNumBombas( cartaIMG, p,y,40,40 ); 
                                        c = new CartaSuperFogo( cartaIMG, cartaIMG2, x,y,40,40 );
                                }/*else if(r>=17 && r < 19){
                                        cartaIMG = load_bitmap("cartaPoison.bmp",NULL);  
                                        c = new CartaNumBombas( cartaIMG, p,y,40,40 ); 
                                        c = new CartaDiminuirVelocidade( cartaIMG, x,y,40,40 );
                                }*/else{
                                        cartaIMG = load_bitmap("images\\cartavida.bmp",NULL); 
                                        cartaIMG2 = load_bitmap("images\\cartavida2.bmp",NULL); 
                                   //     c = new CartaNumBombas( cartaIMG, p,y,40,40 );  
                                        c = new CartaAumentarVida( cartaIMG, cartaIMG2,x,y,40,40 );
                                }
                               // c = new CartaNumBombas( cartaIMG, p,y,40,40 ); 
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
                 /*bool ret = false;
                  bool achou = false;
                  No *ptr = listaCartas -> getHead();
                  while( ptr != NULL && !achou ){
                         Carta *wT = (Carta*)ptr->getObjeto();
                         if( wT -> getX() == x && wT -> getY() == y ){
                             achou = true;
                             ret = true;
                         }
                         ptr = ptr -> getNext();
                  }
                  return ret;*/
             }
             
             
               bool existeMonstroAtXY( int x, int y ){
                  bool ret = false;
                  bool achou = false;
				  int *tam = listaMonstros -> getTamanho();
				  int i = 0;
                  while( i < *tam && !achou ){
                         Monstro *wT = (Monstro*)listaMonstros -> at( i );
                         if( personagem->colideCaixa((Monstro*)wT)){
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
             
             
             Bomba *getBombaAtXY( int x, int y ){
                   Objeto2D *obj = getObjetoAtXY( x, y );
                   Bomba *ret = NULL;
                   if( obj != NULL ){
                      if( strcmp(obj -> getNome(),"Bomba" ) == 0 ){
                          ret = (Bomba*)obj;
                      }
                   }
                   return ret;
             }
             
    
             void explodir( Bomba * b ){
                   if( b != NULL ){
                      // if( this -> personagem -> colideCaixa( b ) ){
//                             this -> personagem -> setVivo( false );
//                              this -> personagem -> setVidas( personagem->getVidas()-1);
//                          }
                      Explosao *ex = new Explosao( b->getX(),b->getY(),arrayExplosao,Explosao::NUC,tempo);
                      inserirObjeto( ex ); 
                      b -> setDestruida( true );
                      explodirAcima( b );
                      explodirAbaixo( b );
                      explodirDireita( b );
                      explodirEsquerda( b );
                      
                      
                   }
                   //this -> personagem -> setVivo( true );
             }
             
             Monstro *monstroAtXY(int x , int y, int largura, int altura){
                  //No *temp = listaMonstros->getHead();
				 int *tam = listaMonstros -> getTamanho();
				 int i = 0;
                  bool achou = false;
                  Monstro *ret = NULL;
                  while(!achou && i < *tam ){
                      Monstro *ptr = (Monstro *)listaMonstros -> at( i );
                        if(ptr->colideCaixa( x , y , largura, altura)){
                              achou = true; 
                              ret = ptr;
                        }else{
                                i++;
                        }
                 }
                 
                 return ret;
             }
             void explodirEsquerda( Bomba *b ){
                   int x = b -> getX();
                   int y = b -> getY();
                   x = x - TILE_WIDTH;
                   bool achou = false;
                   int i = 0;
                    Monstro *ptr ;
                   while( !achou && (i < b -> getForca()) ){
                          ptr = monstroAtXY(x , y , TILE_WIDTH , TILE_HEIGHT);
                          //if( this -> personagem -> isVivo() ){
//                          if( this -> personagem -> colideCaixa(getTileAtXY(x,y)) ){
//                              this -> personagem -> setVidas( personagem->getVidas()-1);
//                              this -> personagem -> setVivo( false );
//                          }
//                          }
                          if( getTileAtXY(x,y)-> getTipo() == 2 ){
                               achou = true;
                          }else if( existeWallAtXY(x,y) ){
                              
                               destruirWallAtXY( x, y );
                               
                               achou = true;
                               Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                               inserirObjeto( f );
                          }else if(ptr!= NULL){
                              
                                 int pontos = ptr -> getPontos();
                                 this -> addPontos(pontos, ptr->getX(), ptr->getY());
                                 personagem -> setPontos( personagem->getPontos()+ ptr->getPontos());
                                 removerMonstro(ptr);
                                int random = (int)(rand()%6);
                                if(random == 0)
                                verificarCarta(x,y); 
                               //free(temp);
                               //dar pontos
                               
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
                     
                   Monstro *ptr;
                        
                      while( !achou && (i < b -> getForca()) ){
                             ptr = monstroAtXY(x , y , TILE_WIDTH , TILE_HEIGHT);
                            //  if( this -> personagem -> isVivo() ){
//                          if( this -> personagem -> colideCaixa(getTileAtXY(x,y)) ){
//                              this -> personagem -> setVidas( personagem->getVidas()-1);
//                              this -> personagem -> setVivo( false );
//                          }
//                          }
                             if( getTileAtXY(x,y)-> getTipo() == 2 ){
                                achou = true;
                             }else if( existeWallAtXY(x,y) ){
                                      destruirWallAtXY( x, y );
                                      achou = true;
                                      Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                                       inserirObjeto( f );
                             }else if(ptr!= NULL){
                                 int pontos = ptr -> getPontos();
                                 this -> addPontos(pontos, ptr->getX(), ptr->getY());
                                 personagem -> setPontos( personagem->getPontos()+ ptr->getPontos());
                                 removerMonstro(ptr);
                                 int random = (int)(rand()%6);
                                 if(random == 0)
                                 verificarCarta(x,y); 
                               //free(temp);
                               //dar pontos
                               
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
                   Monstro *ptr ;
              
                  while( !achou && (i < b -> getForca()) ){
                         ptr = monstroAtXY(x , y , TILE_WIDTH , TILE_HEIGHT);
                          //if( this -> personagem -> isVivo() ){
//                          if( this -> personagem -> colideCaixa(getTileAtXY(x,y)) ){
//                              this -> personagem -> setVidas( personagem->getVidas()-1);
//                              this -> personagem -> setVivo( false );
//                          }
//                          }
                         if( getTileAtXY(x,y)-> getTipo() == 2 ){
                             achou = true;
                         }else if( existeWallAtXY(x,y) ){
                                  destruirWallAtXY( x, y );
                                  achou = true;
                                  Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                                   inserirObjeto( f );
                         }else if(ptr!= NULL){
                                 int pontos = ptr -> getPontos();
                                 this -> addPontos(pontos, ptr->getX(), ptr->getY());
                                 personagem -> setPontos( personagem->getPontos()+ ptr->getPontos());
                                 removerMonstro(ptr);
                                 int random = (int)(rand()%6);
                                 if(random == 0)
                                 verificarCarta(x,y); 
                               //free(temp);
                               //dar pontos
                               
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
                 
                    Monstro *ptr ;
                   while( !achou && (i < b -> getForca()) ){
                          ptr = monstroAtXY(x , y , TILE_WIDTH , TILE_HEIGHT);
                          if( getTileAtXY(x,y)-> getTipo() == 2 ){
                              achou = true;
                          }else if( existeWallAtXY(x,y) ){
                                   destruirWallAtXY( x, y );
                                   Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                                   inserirObjeto( f ); 
                                  achou = true;
                          }else if(ptr!= NULL){
                                 int pontos = ptr -> getPontos();
                                 this -> addPontos(pontos, ptr->getX(), ptr->getY());
                                 personagem -> setPontos( personagem->getPontos()+ ptr->getPontos());
                                 removerMonstro(ptr);
                                 int random = (int)(rand()%6);
                                 if(random == 0)
                                 verificarCarta(x,y); 
                               //free(temp);
                               //dar pontos
                               
                                 achou = true;
                                 Fumaca *f = new Fumaca( arrayFumaca, x,y,tempo);
                                 inserirObjeto( f );
                                
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
                  
                  
                  /* pintar portal */
                  if (this -> passagem != NULL){
                               this -> passagem -> paint( b );
                  }
                  
                  /*pintar lista walls*/
                /*  No *ptr = listaWall -> getHead();
                  while( ptr != NULL ){
                         WallTile *wT = (WallTile*)ptr->getObjeto();
                         wT -> paint( b );
                         ptr = ptr -> getNext();
                  }*/
				  for( int i = 0; i < listaWall -> size(); i++ ){
						((WallTile*)(listaWall -> at( i ))) -> paint( b );  
				  }
                  
                     /*pintar lista carta*/
                 /* ptr = listaCartas -> getHead();
                  while( ptr != NULL ){
                         Carta *wT = (Carta*)ptr->getObjeto();
                         wT -> paint( b );
                         ptr = ptr -> getNext();
                  }*/
				  for( int i = 0; i < listaCartas -> size(); i++ ){
						((Carta*)(listaCartas -> at( i ))) -> paint( b );  
				  }
                  
                  
                  
				  int *tamM = listaMonstros -> getTamanho();
				  int j = 0;
                   
                  /* pintar lista objetos */
                  /*if( objetos != NULL ){
                         ptr = objetos -> getHead();
                  }else{
                         ptr = NULL;
                  }*/
                                
                                Objeto2D *obj = NULL;
								int *tamO = objetos -> getTamanho();
								int h = 0;

                  while( h < *tamO ){
                         
                 
                          obj = objetos -> at( h );
                         if( obj != NULL ){
                             
                                if(obj == NULL)break;
                                else {
                                }
                           if(  obj->getTipo()== 1 ){
                             
                               if(((Fumaca*)obj)->isMorto()){                         
                                  this -> removerObjeto( obj );
                               }else{
                               ((Fumaca*)obj) -> paint( b );
                                
                               }
                                
                           }else if( obj->getTipo()== 2){
                                if(((Bomba *)obj)->isDestruida()){
                                   this ->explodir( (Bomba *)obj  );
                                   play_sample( somExplosao, 255, 125, 1200, 0 );
                                   this -> removerObjeto( obj );
                                }else{
                                   ((Bomba*)obj) -> paint( b,*tempo);   
                                }
                           }else if( obj->getTipo() == 3){
                                 if( ((Explosao*)obj)-> isMorto() ){
                                     this -> removerObjeto( obj );
                                 }else{
                                       if( personagem -> colideCaixa(obj)&& !((Explosao*)obj)->jaMatouPersonagem()){
                                          personagem -> setEstadoAtual( Personagem::MORRENDO );
                                          
                                           ((Explosao*)obj)->setJaMatou( true );
                                       }else if( j < *tamM ){
                                             
                                             while( j < *tamM ){
                                             Monstro * temp = (Monstro*)listaMonstros -> at( j );
                                             if(temp->colideCaixaColisao(obj)){
                                             int pontos = temp -> getPontos();
                                             this -> addPontos(pontos, temp->getX(), temp->getY());
                                             personagem -> setPontos( personagem->getPontos()+ temp->getPontos());                           
                                             removerMonstro(temp);
                                             Fumaca *f = new Fumaca( arrayFumaca, temp->getX(),temp->getY(),tempo);
                                             inserirObjeto( f );
                                             }
                                             j++;
                                       }
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
                  
                  /*pintar lista monstros*/
                  for( int i = 0; i < listaMonstros -> size(); i++ ){
						((Monstro*)(listaMonstros -> at( i ))) -> paint( b );  
				  }
                 
                 
                   if(podePintar){
                   
                     painel->paint(b);
                   if(painel->jaTerminou()){
                      setPodePintar(false);                   
                     }
                   }
                
                 if( acabouMonstros() ){
					 if( passagem != NULL ){
                      if( !(this -> passagem -> isAberto()) ){
                          BITMAP *im = load_bitmap("images\\portal2.bmp",NULL);
                         this -> passagem -> setImagem(im);
                         this -> passagem -> setAberto(true);
                      }
					 }
                  }
                  
                  movimentarMonstros();
                  
             }//fim paint
             
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
           
           
          
          void movimentarMonstros(){
			  for( int i = 0; i < listaMonstros -> size(); i++ ){
				Monstro *m = (Monstro*)listaMonstros -> at( i );
				andarMonstro( m );
			  }
          }
          
          void andarMonstro(Monstro *m){
               if(m->getDirecao() == Monstro::horizontal){
                  if(m->getDirecaoAtual() == Monstro::direita){                
                     m -> andarDireita();
                     if( colideCaixaDir(m) ){
                         m->andarEsquerda();
                         m->setDirecaoAtual(Monstro::esquerda);
                     }
                  }else{
                      m->andarEsquerda();
                      if( colideCaixaEsq(m) ){
                         m->andarDireita();
                         m->setDirecaoAtual(Monstro::direita);
                       }
                  }
               }else if(m->getDirecao() == Monstro::vertical){
                  if(m->getDirecaoAtual() == Monstro::cima){                
                     m -> andarCima();
                     if( colideCaixaCima(m) ){
                         m->andarBaixo();
                         m->setDirecaoAtual(Monstro::baixo);
                     }
                  }else{
                      m->andarBaixo();
                      if( colideCaixaBaixo(m) ){
                         m->andarCima();
                         m->setDirecaoAtual(Monstro::cima);
                       }
                  }  
               }
               
          
          }
          
          void checarPersonagem( Personagem *p ){
            if( p != NULL ){
               if( p -> getEstadoAtual() != Personagem::MORRENDO){
                   if( acabouMonstros() ){
                      if( p -> colideCaixa( passagem ) ){
                        this -> colidiuPassagem = true;
                      }
                   }
				  int i = 0;
				  int *tam = listaMonstros -> getTamanho();	
				  Monstro *m = NULL;
            
                  while( i < *tam ){
					  m = (Monstro*)listaMonstros -> at( i );
                       if( p -> colideCaixaColisao( m ) ){
                           p -> setEstadoAtual(Personagem::MORRENDO);
                       }
                       i++;
                  }
                  
                  
            
               }
            }
          
          }
          
          
          void addPontos(int p, int x, int y){
               Pontos *pontos = new Pontos(arrayPontos[p/100], x, y, tempo, p);
               this -> inserirPontos(pontos);
          }

};

#endif

