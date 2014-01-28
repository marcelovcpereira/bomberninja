//#include <cstdio>
//
//#ifndef ALLEGRO_H
//#include <allegro.h>
//#endif
//
////#ifndef WINDOWS_H
////#include <windows.h>
////#endif
//
//#include <cmath>
//#include <cstring>
//#include <cstdio>
//#include <cstring>
//#include "menuJogo.cpp"   
//
//#ifndef MAPA_H
//#include "mapa.h"            
//#endif    
//
//#ifndef EXPLOSAO_H          
//#include "explosao.h"    
//#endif
//
//#ifndef BOMBA_H
//#include "bomba.h"
//#endif
//
//#ifndef CARTA_H
//#include "carta.h"
//#endif
//  
//#ifndef NINJA_H    
//#include "ninja.h" 
//#endif
//
//#ifndef MONSTRO_VERDE_H
//#include "MonstroVerde.cpp"  
//#endif
//
//#ifndef FUMACA_H
//#include "fumaca.h" 
//#endif
//
//#ifndef LISTA_CPP
//#include "lista.cpp"
//#endif
//
//#ifndef CAVEIRA_ROSA_H
//#include "caveiraRosa.cpp"  
//#endif      
//
//#include <typeinfo>
//#define NUM_H_TILES 20
//#define NUM_V_TILES 15
//#define TILE_WIDTH 40
//#define TILE_HEIGHT 40
//#define NUM_TILES NUM_V_TILES*NUM_H_TILES
//#define DESTROY 50  
//#define PONTOS_PASSAR 800 
//
//int arrayTiles[NUM_V_TILES][NUM_H_TILES];
///*BITMAP *arrayMV[32];
//BITMAP *arrayCR[25];
//*/
//volatile int tempo = 0;
//
//  
////string global para fins de debugging
//char *str =  (char*)calloc(sizeof(char),80);
// 
// void explodir( Bomba * b, Mapa *map );
//
//
////função que incrementa a variavel de tempo
//void incrementaTempo(){
//     tempo++;
//}END_OF_FUNCTION( incrementaTempo );
//
//
////função main
//
//int main(){
//    allegro_init();	//inicia o allegro
//
//    set_color_depth(32);   //consfigura o allegro a usar 32bits de cor
//  
//    set_gfx_mode(GFX_AUTODETECT,800,600,0,0); //janela 800x600
//     
//    install_keyboard();	//configura o teclado
//
//    install_timer(); //instala um cronometro
//    
//    install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT,NULL);
//     
//    LOCK_VARIABLE( tempo ); //adiciona a variavel "tempo" como o tempo do cronometro
//
//    LOCK_FUNCTION( incrementaTempo ); //adiciona a função "incrementaTempo" como função do tempo
//
//    install_int( incrementaTempo , 1  ); //installa a função que contara de 100 em 100 milisegundos
//        
//    set_window_title("TESTE"); //titulo da janela
//
//    BITMAP *buffer = create_bitmap(800,600);//bitmap para o double buffering
//    BITMAP *ts = load_bitmap("carro.bmp",NULL);
//    //imagens dos tiles do chao, parede, e bloqueios
//  
//    
//    
//
//
//    BITMAP *bombas[NUM_BOMBAS];
//    bombas[ 0 ] = load_bitmap("bomba0.bmp",NULL);
//    bombas[ 1 ] = load_bitmap("bomba2.bmp",NULL);
//    bombas[ 2 ] = load_bitmap("bomba3.bmp",NULL);
//    bombas[ 3 ] = load_bitmap("bomba4.bmp",NULL);
//    
//    //cria um mapa default com as imagens
//    Bomba *arrayBombas[5];
//    int proxBomba = 0;
//    //posição do personagem
//
//    int i = 0;
//
// 
//    //tempo atual e tempo anterior
//    int t=0;
//    int oT = 0;
//    int tempoB = 0;
//    int tempoBvelho = 0;
//
//     
//    Ninja *ninja = new Ninja();
//    ninja -> setCronometro( &tempo );
//    //ninja->setForca( 2 );
//    
//    int estagioAtual = Mapa::TIPO1;
//    Mapa *mapa = new Mapa( estagioAtual, ninja,&tempo);
//    //mapa->setCronometro(&tempo);
//   // Monstro *m = new MonstroVerde();
//    int ultimoPonto = 0;
//    tempoBvelho = 0; 
//    MenuJogo *menu = new MenuJogo( &tempo , ninja );
//    mapa ->setMenu(menu);
//    SAMPLE *somBomba = load_wav("sons/hehehe.wav"); 
//    int tempoV = 0;
//    MIDI *musica = load_midi("sons/musica.mid");
//    //play_midi( musica, 1 );
//    bool sair = false;
//    BITMAP *arrayEstagio[2];
//    arrayEstagio[0] = load_bitmap("stage1.bmp",NULL);
//    arrayEstagio[1] = load_bitmap("stage2.bmp",NULL);
//    
//     while( !key[KEY_ENTER] && !key[KEY_ENTER_PAD] ){
//                  if( key[KEY_ESC])sair = true;
//                  clear_keybuf();
//                  clear_bitmap( buffer );
//                  textout(buffer,font,"Pressione ENTER para jogar",300,250,makecol(255,255,255));
//                  textout(buffer,font,"A cada 800 Pontos vc passara de estagio...",250,500,makecol(255,255,255));
//                  blit(buffer,screen,0,0,0,0,800,600);
//     }
//    
//    while( !sair ){   
//           stop_midi();
//           if( key[KEY_ESC]){
//               break;
//           }
//           
//           
//          
//           
//           //se passou de estagio
//           if( mapa -> zerouMapa() ){
//               menu -> zerarTempo(180000);
//               ultimoPonto = ninja -> getPontos();
//               ninja->setVivo( true );
//               ninja -> setBounds( 40, 10, 35, 57 );
//               ninja ->setEstadoAtual(Ninja::PARADO);
//               ninja -> setBombaPlantada( NULL );
//               ninja -> setNumBombas( 0 );
//               if( estagioAtual == Mapa::TIPO1 ){
//                   estagioAtual = Mapa::TIPO2;
//               }else estagioAtual = Mapa::TIPO1;
//               free(mapa);
//               mapa = NULL;
//              mapa = new Mapa( estagioAtual , ninja ,&tempo);
//               mapa -> setPersonagem( ninja );
//              // mapa->setCronometro(&tempo);
//   
//           }//se nao passou de estagio, mas tem vidas
//           else if( ninja -> getVidas() != 0 ){
//                menu->zerarTempo(180000);
//               ninja->setVivo( true );
//               ninja -> setBounds( 40, 10, 35, 57 );
//               ninja ->setEstadoAtual(Ninja::PARADO);
//               ninja ->setBombaPlantada( NULL );
//               ninja -> setNumBombas( 0 );
//              free(mapa);
//              mapa = NULL;
//              
//              mapa = new Mapa( estagioAtual, ninja,&tempo );
//              
//              mapa -> setPersonagem( ninja );
//              //mapa->setCronometro(&tempo);
//              
//               
//           }else{
//                 int uT2 = tempo;
//                 while( tempo - uT2 < 1200 ){
//                    clear_bitmap(buffer);
//                    rectfill( buffer, 0,0,800,600,makecol(0,0,0) );
//                    //masked_blit( arrayEstagio[estagioAtual],buffer,0,0,200,200,400,100);
//                    textout( buffer, font,"GAME OVER",370,200,makecol(255,0,0));
//                    blit(buffer,screen,0,0,0,0,800,600);
//                 }
//                  break; 
//           }
//           
//           int ut = tempo;
//           while( tempo - ut < 1000 ){
//              clear_bitmap(buffer);
//              rectfill( buffer, 0,0,800,600,makecol(0,0,0) );
//              masked_blit( arrayEstagio[estagioAtual],buffer,0,0,200,200,400,100);
//              blit(buffer,screen,0,0,0,0,800,600);
//           }
//    play_midi( musica, 1 );       
//    while( ninja -> isVivo() && !mapa->zerouMapa() ){ 
//				//limpa o buffer da tela
//                clear_bitmap(buffer);
//                //limpa o buffer do teclado
//                clear_keybuf();
// 
//                //se apertou ESC sair
//                if(key[KEY_ESC]) break;
//                if( key[KEY_V] ){
//                    if( tempo - tempoV >= 30 ){
//                       ninja -> setVidas(ninja->getVidas()-1);
//                       tempoV = tempo;
//                    }      
//                }else if( key[KEY_ALT] && key[KEY_F12] ){
//                      if( tempo - tempoV >= 30 ){
//                       ninja -> setPontos(ninja->getPontos()+ PONTOS_PASSAR);
//                       tempoV = tempo;
//                       }
//                      }else         
//                //se apertou esquerda...
//                if( key[KEY_LEFT] ){
//                                  ninja -> andarEsquerda();
//                                  if(/*mapa ->colidiuEsquerda(ninja->getX(),ninja->getY())*/mapa->colideCaixaEsq(ninja))
//                                     ninja->setX( ninja->getX() + ninja ->getVelocidade()/10 );
//                                     
//                   
//                }else
//                //se apertou direita...
//                if( key[KEY_RIGHT] ){
//                                   ninja -> andarDireita();
//                    if( /*mapa ->colidiuDireita(ninja->getX(),ninja->getY())*/mapa->colideCaixaDir(ninja) )
//                        ninja->setX( ninja ->getX() - ninja ->getVelocidade()/10 );
//                                    
//                }else 
//                //se apertou pra cima...
//                if( key[KEY_UP] ){
//                    ninja -> andarCima();
//                     if( /*mapa -> colidiuPorCima(ninja->getX(),ninja->getY())*/mapa->colideCaixaCima(ninja) )
//                       ninja->setY( ninja ->getY() + ninja ->getVelocidade()/10 );
//                    
//                }else
//				//se apertou pra baixo...
//                if( key[KEY_DOWN] ){
//                                  ninja -> andarBaixo();
//                                  if(/*mapa -> colidiuEmbaixo(ninja->getX(),ninja->getY()) */mapa->colideCaixaBaixo(ninja))
//                                     ninja->setY( ninja ->getY() - ninja ->getVelocidade()/10 );
//                                
//
//                }else //se não apertou nada...  
//                { 
//                    ninja -> parar(); 
//                }
//                
//                if( key[ KEY_B ] && ninja -> getEstadoAtual() != Ninja::MORRENDO){ 
//                      tempoB = tempo;
//                      sprintf( str, "tempo: %d tempoB: %d tBv: %d",tempo,tempoB,tempoBvelho );
//   
//                      if( tempoB - tempoBvelho >= 100 ){ 
//                        tempoBvelho = tempoB;
//                        if( (mapa -> getNumeroBombas()) < ninja -> getNumMaxBombas() ){
//   
//                            Tile *temp = mapa -> getTileAtXY(ninja->getX()+20,ninja->getY()+40);
//                             
//                            if( mapa -> getBombaAtXY(temp->getX(),temp->getY()) == NULL ){
//                               Bomba *nova = new Bomba( bombas );
//                               nova -> setForca( ninja -> getForca() );
//                               nova -> setCronometro( &tempo );
//                               nova -> setBounds(temp->getX(),temp->getY(),TILE_WIDTH,TILE_HEIGHT);
//                               mapa -> inserirObjeto( nova ); 
//                               ninja -> incrementarBombas();
//                               ninja -> setBombaPlantada( nova );
//                               ninja -> setPodePassar( true );
//                              // play_sample( somBomba, 255, 125, 2000, 0 );
//                                   
//                            }
//                        }
//                       
//                      }
//                }
//                
//                //pintar mapa no buffer
//                  
//                mapa -> paint( buffer );
//                
//                sprintf( str, "tempo: %d tempoB: %d tBv: %d",tempo,tempoB,tempoBvelho );
//                //pinta o ninja  
//                
//                ninja -> paint( buffer ); 
//                
//                //allegro_message("depois de criar");
//                menu -> paint( buffer );  
//                //imprimir o texto da string global no buffer
//                //textout( buffer, font , str, 100,100,makecol(255,255,255));
//
//                //blitar o buffer na tela
//                blit(buffer,screen,0,0,0,0,800,600);
//                if(menu->getTempo() <= 0){
//                //ninja->setVivo( false );
//                ninja->setEstadoAtual(Ninja::MORRENDO);
//                }
//                mapa->checarPersonagem(ninja);
//                if( !ninja -> isVivo() ){
//                   //ninja->setEstadoAtual(Ninja::MORRENDO);
//                   //ninja -> inicializarArray();
//                   ninja->setVidas(ninja->getVidas()-1);
//                }
//                }
//                
//                }
//}
////fim do main
//END_OF_MAIN();
