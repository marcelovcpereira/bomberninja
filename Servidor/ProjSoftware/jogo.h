#include <cstdio>
#include <typeinfo>
#include <allegro.h>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstring>

#include "menuJogo.cpp"   
#include "mapa.h"       
#include "explosao.h"   
#include "bomba.h"
#include "carta.h"
#include "ninja.h" 
#include "MonstroVerde.cpp" 
#include "fumaca.h" 
#include "lista.cpp"
#include "caveiraRosa.cpp" 
#include "painel.h"  


#define NUM_H_TILES 20
#define NUM_V_TILES 15
#define TILE_WIDTH 40
#define TILE_HEIGHT 40
#define NUM_TILES NUM_V_TILES*NUM_H_TILES
#define DESTROY 50  
#define PONTOS_PASSAR 800 
#define NUM_ESTAGIOS 2
#define MAX_PONTOS 2000
#define TEMPO_HURRY 60
#define TEMPO_ESTAGIO 180000
 volatile int tempo;
 void incrementaTempo(){
        tempo++;
       }END_OF_FUNCTION( incrementaTempo );
       
class Jogo{


private :
         
          BITMAP *buffer;
    
          BITMAP *bombas[NUM_BOMBAS];
          Ninja *ninja;
          int estagioAtual;
          Mapa *mapa;
          MenuJogo *menu;
          SAMPLE *somBomba;
          MIDI *musica;
          BITMAP *arrayEstagio[NUM_ESTAGIOS];
          BITMAP *imagemHurry;
          BITMAP *imagem1Up;
          BITMAP *imagemTimeUp;
          ListaObjetos2D *efeitos;
          bool pintouHurry;
          bool criouTimeUp;
          bool timeUp;
          bool zerouJogo;
 
public:
          Jogo(){
          pintouHurry = false;
          tempo = 0;
          timeUp = false;
          criouTimeUp = false;
          zerouJogo = false;
          LOCK_VARIABLE( tempo ); //adiciona a variavel "tempo" como o tempo do cronometro

          LOCK_FUNCTION( incrementaTempo ); //adiciona a função "incrementaTempo" como função do tempo

          install_int( incrementaTempo , 1  ); //installa a função que contara de 100 em 100 milisegundos
        
          buffer = create_bitmap(800,600);//bitmap para o double buffering
          ninja = new Ninja();
          bombas[ 0 ] = load_bitmap("images\\bomba0.bmp",NULL);
          bombas[ 1 ] = load_bitmap("images\\bomba2.bmp",NULL);
          bombas[ 2 ] = load_bitmap("images\\bomba3.bmp",NULL);
          bombas[ 3 ] = load_bitmap("images\\bomba4.bmp",NULL);
          estagioAtual = Mapa::TIPO1;
          mapa = new Mapa( estagioAtual, ninja,&tempo);
          menu = new MenuJogo( &tempo , ninja );
          
          efeitos = new ListaObjetos2D();
          somBomba = load_wav("sons/hehehe.wav"); 
          musica = load_midi("sons/musica.mid");
          
           arrayEstagio[0] = load_bitmap("images\\stage1.bmp",NULL);
           arrayEstagio[1] = load_bitmap("images\\stage2.bmp",NULL);
           imagemHurry = load_bitmap("images\\painelHurry.bmp",NULL);
           imagem1Up = load_bitmap("images\\painelVida.bmp",NULL);
           imagemTimeUp = load_bitmap("images\\painelTempo.bmp",NULL);
           
          }

          void checarEfeitosMapa(){
               
               //Checando Pontos
                
				Pontos *obj = NULL;
				int i = 0;
				int tam = mapa -> getListaPontos() -> size();
                while( i < tam ){
                   obj = (Pontos*)(mapa -> getListaPontos() -> at( i ) );
                   this -> efeitos -> inserirObjeto( obj );
                   i++;
                   this -> mapa -> removerPontos( obj );    
                }
          }
          
          void zerarListaEfeitos(){
             delete(efeitos);
             efeitos = new ListaObjetos2D();
          }
          
          
void  rodarJogo(){

    int i = 0;
    //tempo atual e tempo anterior
    int t=0;
    int oT = 0;
    int tempoB = 0;
    int tempoBvelho = 0;
    ninja -> setCronometro( &tempo );
    int ultimoPonto = 0;
    tempoBvelho = 0; 
    mapa ->setMenu(menu);
    int tempoV = 0;
    bool sair = false;

    while( !sair  ){   
           stop_midi();
           if( key[KEY_ESC]){
               break;
           }
           
           //se passou de estagio
		   if( mapa -> zerouMapa() ){
               clear_bitmap(buffer);
               zerarListaEfeitos();
               menu -> zerarTempo(TEMPO_ESTAGIO);
               criouTimeUp = false;
               pintouHurry = false;
               ninja->setVivo( true );
               ninja -> setBounds( 40, 10, 35, 57 );
               ninja ->setEstadoAtual(Ninja::PARADO);
               ninja -> setBombaPlantada( NULL );
               ninja -> setNumBombas( 0 );
               ultimoPonto = ninja->getPontos();
               if( estagioAtual == Mapa::TIPO1 ){
                   estagioAtual = Mapa::TIPO2;
               }else {
                   estagioAtual = Mapa::TIPO1;
                   zerouJogo = true;
               }
               free(mapa);
               mapa = NULL;
              mapa = new Mapa( estagioAtual , ninja ,&tempo);
               mapa -> setPersonagem( ninja );
              // mapa->setCronometro(&tempo);
   
           }//se nao passou de estagio, mas tem vidas
           else if( ninja -> getVidas() != 0 ){
                clear_bitmap(buffer);
                zerarListaEfeitos();
                menu->zerarTempo(TEMPO_ESTAGIO);
                criouTimeUp = false;
               pintouHurry = false;
               ninja->setVivo( true );
               ninja -> setBounds( 40, 10, 35, 57 );
               ninja ->setEstadoAtual(Ninja::PARADO);
               ninja ->setBombaPlantada( NULL );
               ninja -> setNumBombas( 0 );
               ultimoPonto = ninja->getPontos();
              free(mapa);
              mapa = NULL;
              
              mapa = new Mapa( estagioAtual, ninja,&tempo );
              mapa -> setPersonagem( ninja );
               
           }else{
                 int uT2 = tempo;
                 while( tempo - uT2 < 1200 ){
                    clear_bitmap(buffer);
                    rectfill( buffer, 0,0,800,600,makecol(0,0,0) );
                    //masked_blit( arrayEstagio[estagioAtual],buffer,0,0,200,200,400,100);
                    textout( buffer, font,"GAME OVER",370,200,makecol(255,0,0));
                    blit(buffer,screen,0,0,0,0,800,600);
                 }
                  sair = true;
           }
           
           if( zerouJogo )
          {
             int uT2 = tempo;
                 while( tempo - uT2 < 1200 ){
                    clear_bitmap(buffer);
                    rectfill( buffer, 0,0,800,600,makecol(0,0,0) );
                    //masked_blit( arrayEstagio[estagioAtual],buffer,0,0,200,200,400,100);
                    textout( buffer, font,"Voce Ganhou!!",370,200,makecol(0,0,255));
                    blit(buffer,screen,0,0,0,0,800,600);
                 }
                  sair = true;
                  mapa -> setZerouMapa( true );
          }
          
          if( !sair ){
           int ut = tempo;
           while( tempo - ut < 1000 ){
              clear_bitmap(buffer);
              rectfill( buffer, 0,0,800,600,makecol(0,0,0) );
              masked_blit( arrayEstagio[estagioAtual],buffer,0,0,200,200,400,100);
              blit(buffer,screen,0,0,0,0,800,600);
           }
            play_midi( musica, 1 );  
          }
          
               
    while( ninja -> isVivo() && !mapa->zerouMapa() ){ 
				//limpa o buffer da tela
                clear_bitmap(buffer);
                //limpa o buffer do teclado
                clear_keybuf();
 
                //se apertou ESC sair
                if(key[KEY_ESC]) break;
                if(key[KEY_ALT] && key[KEY_F12]){
                   mapa -> setZerouMapa( true );
                }
                if( key[KEY_V] ){
                    if( tempo - tempoV >= 30 ){
                       ninja -> setVidas(ninja->getVidas()-1);
                       tempoV = tempo;
                    }      
                
                      }else         
                //se apertou esquerda...
                if( key[KEY_LEFT] ){
                                  ninja -> andarEsquerda();
                                  if(/*mapa ->colidiuEsquerda(ninja->getX(),ninja->getY())*/mapa->colideCaixaEsq(ninja))
                                     ninja->setX( ninja->getX() + ninja ->getVelocidade()/10 );
                                     
                   
                }else
                //se apertou direita...
                if( key[KEY_RIGHT] ){
                                   ninja -> andarDireita();
                    if( /*mapa ->colidiuDireita(ninja->getX(),ninja->getY())*/mapa->colideCaixaDir(ninja) )
                        ninja->setX( ninja ->getX() - ninja ->getVelocidade()/10 );
                                    
                }else 
                //se apertou pra cima...
                if( key[KEY_UP] ){
                    ninja -> andarCima();
                     if( /*mapa -> colidiuPorCima(ninja->getX(),ninja->getY())*/mapa->colideCaixaCima(ninja) )
                       ninja->setY( ninja ->getY() + ninja ->getVelocidade()/10 );
                    
                }else
				//se apertou pra baixo...
                if( key[KEY_DOWN] ){
                                  ninja -> andarBaixo();
                                  if(/*mapa -> colidiuEmbaixo(ninja->getX(),ninja->getY()) */mapa->colideCaixaBaixo(ninja))
                                     ninja->setY( ninja ->getY() - ninja ->getVelocidade()/10 );
                                

                }else //se não apertou nada...  
                { 
                    ninja -> parar(); 
                }
                
                if( key[ KEY_B ] && ninja -> getEstadoAtual() != Ninja::MORRENDO){ 
                      tempoB = tempo;
   
                      if( tempoB - tempoBvelho >= 100 ){ 
                        tempoBvelho = tempoB;
                        if( (mapa -> getNumeroBombas()) < ninja -> getNumMaxBombas() ){
   
                            Tile *temp = mapa -> getTileAtXY(ninja->getX()+20,ninja->getY()+40);
                             
                            if( mapa -> getBombaAtXY(temp->getX(),temp->getY()) == NULL ){
                               Bomba *nova = new Bomba( bombas );
                               nova -> setForca( ninja -> getForca() );
                               nova -> setCronometro( &tempo );
                               nova -> setBounds(temp->getX(),temp->getY(),TILE_WIDTH,TILE_HEIGHT);
                               mapa -> inserirObjeto( nova ); 
                               ninja -> incrementarBombas();
                               ninja -> setBombaPlantada( nova );
                               ninja -> setPodePassar( true );
                              // play_sample( somBomba, 255, 125, 2000, 0 );
                                   
                            }
                        }
                       
                      }
                }
                
                
                
                //Criar efeito de Hurry UP 
                if((menu->getTempo()/1000 ) <= TEMPO_HURRY ){
                  if( !pintouHurry ){                     
                     Painel *hurry = new PainelHurry( imagemHurry, &tempo );
                     efeitos -> inserirObjeto( hurry );
                     pintouHurry = true;
                  }
                 
                }
                
               //Criar efeito de +1 VIDA 
               if(ninja->getPontos() -  ultimoPonto >=  MAX_PONTOS ){
                  Painel *lifeUp = new PainelVida( imagem1Up, &tempo );
                  efeitos -> inserirObjeto( lifeUp );
                  ultimoPonto = ninja -> getPontos();
                  ninja -> setVidas( ninja -> getVidas() + 1 );
                  }
                
                //pintar mapa no buffer
                mapa -> paint( buffer );
                
                //pinta o ninja  
                ninja -> paint( buffer ); 
                
                //Pintando os EFEITOS ESPECIAIS
                Objeto2D *obj = NULL;
				int *tam = efeitos -> getTamanho();
				int i = 0;
                while( i < *tam )
                {
                  obj = efeitos -> at( i ); 
                  if( strcmp(obj->getNome(),"PainelHurry") == 0 ||
                      strcmp(obj->getNome(),"PainelVida") == 0  ||
                      strcmp(obj->getNome(),"PainelTimeUp") == 0 )
                  {
                      if( strcmp(((Painel*)obj) -> getNome() , "PainelTimeUp") == 0 ){
                          if( ((Painel*)obj)-> jaTerminou() ){
                             efeitos -> removerObjeto( obj );
                             ninja -> setEstadoAtual(Personagem::MORRENDO);
                       }else{
                            ((Painel*)obj) -> paint( buffer ); 
                       } 
                      }else{
                          if( ((Painel*)obj)-> jaTerminou() ){
                                efeitos -> removerObjeto( obj );
                          }else{
                               ((Painel*)obj) -> paint( buffer ); 
                          } 
                       }
                  }else if( strcmp( obj->getNome(), "Pontos") == 0 )
                  {
                        if( ((Pontos*)obj) ->jahAcabou() ){
                            this -> efeitos -> removerObjeto( obj );
                        }else{
                            ((Pontos*)obj) -> paint( buffer );
                       }
                      
                  }
                  i++;
                }
                
               
                menu -> paint( buffer ); 
                
                
                  
                //blitar o buffer na tela
                blit(buffer,screen,0,0,0,0,800,600);
                
                if(menu->getTempo() <= 0){
                   if(!criouTimeUp){
                   Painel *timeUp = new PainelTimeUp( imagemTimeUp, &tempo );
                   criouTimeUp = true;
                   efeitos->inserirObjeto(timeUp);
                   }
                }
                
                mapa->checarPersonagem(ninja);
                this -> checarEfeitosMapa();
                
                if( !ninja -> isVivo() ){
                   ninja->setVidas(ninja->getVidas()-1);
                }
                
                
                }
                
                }
}
};
