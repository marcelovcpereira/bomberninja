#include <iostream>
#include "server.cpp"
#include <string>
#include <coss/CosNaming.h>
#include <allegro.h>
#include <winalleg.h>

#include <stdlib.h>
#include "menu.h"
#include "jogo.h"
#include "jogoServer.h"
#include "cliente.cpp"

/************MAIN*************/

int main(){

//system ("bomber.exe");
    
allegro_init();


install_keyboard();
install_timer(); 

install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);

SAMPLE *menuSom = load_wav("sons\\menu.wav");

set_color_depth( 32 );
set_gfx_mode( GFX_AUTODETECT_WINDOWED , 800, 600, 0, 0 );

set_window_title("BomberNinja");

BITMAP *buffer;
BITMAP *background = load_bitmap("images\\background.bmp",NULL);
BITMAP *backgroundHelp = load_bitmap("images\\backgroundHelp.bmp",NULL);
BITMAP *backgroundCredits = load_bitmap("images\\backgroundCredits.bmp",NULL);
buffer = create_bitmap( 800, 600 );

Menu *menu = new Menu( 5 );

menu -> setLocation( 160, 250);

menu -> setGapSize( 16 );



Button *b = new Button();
Button *c = new Button();
Button *d = new Button();
Button *e = new Button();
Button *f = new Button();


b -> setSelected( true );
b -> setSize( 120, 30 );
b -> setNormalIcon( load_bitmap("images\\botaoSingle.bmp",NULL) );

c -> setSize( 120, 30 );
c -> setNormalIcon( load_bitmap("images\\botaoMulti.bmp",NULL) );

d -> setSize( 120, 30 );
d -> setNormalIcon( load_bitmap("images\\botaoExit.bmp",NULL) );

e -> setSize( 120, 30 );
e -> setNormalIcon( load_bitmap("images\\botaoHelp.bmp",NULL) );

f -> setSize( 120, 30 );
f -> setNormalIcon( load_bitmap("images\\botaoCredits.bmp",NULL) );

menu -> addButton( b );
menu -> addButton( c );
menu -> addButton( e );
menu -> addButton( f );
menu -> addButton( d );

bool terminar = false;

while( !terminar  ){
       
       clear_bitmap( buffer );
       blit( background,buffer,0,0,0,0,800,600);
       /* Se o usuário presionar setaDIREITA ou setaPRA_BAIXO,
        * selecione o botao do menu e toque o som
        */
       if( key[KEY_RIGHT]  || key[KEY_DOWN] ){
           menu -> selectNextButton();
           play_sample( menuSom, 255, 122, 2100, 0);
           clear_keybuf();
       }
       
       /* Se o usuário presionar setaESQUERDA ou setaPRA_CIMA,
        * selecione o botao do menu e toque o som
        */
       if( key[KEY_LEFT] || key[KEY_UP] ){
           menu -> selectPrevButton();
           play_sample( menuSom, 255, 122, 2100, 0);
           clear_keybuf();
       }
       
       /* Se o usuário presionar ENTER faça a ação
        * do botão selecionado
        */
       if( key[KEY_ENTER_PAD] || key[KEY_ENTER]  ){
           if( menu->getSelectedButton() == 4 ){
                terminar = true;
           }else if(menu ->getSelectedButton() == 2){
                 while(!key[KEY_ESC]){
                       blit(backgroundHelp,screen,0,0,0,0,800,600);
                 }
           }else if(menu -> getSelectedButton() == 3){
                 blit(backgroundCredits,screen,0,0,0,0,800,600);
                 while(!key[KEY_ESC]){
                 }
           }else if(menu -> getSelectedButton() == 0){
                 Jogo *j = new Jogo();
                 j ->rodarJogo();
		   }else if(menu -> getSelectedButton() == 1){
			     
			     rest(65);
			     Menu *menuMulti = new Menu( 3 );
                 menuMulti -> setLocation( 160 , 250 );
				 menuMulti -> setGapSize( 16 );
				 //menuMulti -> setPaintHorizontal( true );

				 Button *b1 = new Button();
				 Button *b2 = new Button();
				 Button *b3 = new Button();
                 
                 b1 -> setSelected( true );
				 b1 -> setSize( 120, 30 );
				 b1 -> setNormalIcon( load_bitmap("images\\botaoNew.bmp",NULL) );

				 b2 -> setSize( 120, 30 );
				 b2 -> setNormalIcon( load_bitmap("images\\botaoJoin.bmp",NULL) );

				 b3 -> setSize( 120, 30 );
				 b3 -> setNormalIcon( load_bitmap("images\\botaoExit.bmp",NULL) );


                 menuMulti -> addButton( b1 );
				 menuMulti -> addButton( b2 );
				 menuMulti -> addButton( b3 );
                 
				 bool sair = false;

				 while( !sair ){

					 if( key[KEY_RIGHT]  || key[KEY_DOWN] ){
						 menuMulti -> selectNextButton();
						 play_sample( menuSom, 255, 122, 2100, 0);
						 clear_keybuf();
					 }

					 if( key[KEY_LEFT] || key[KEY_UP] ){
						 menuMulti -> selectPrevButton();
						 play_sample( menuSom, 255, 122, 2100, 0);
						 clear_keybuf();
					 }

					 if( key[KEY_ENTER_PAD] || key[KEY_ENTER] ){

						 if( menuMulti->getSelectedButton() == 0 ){
							 try{JogoServer *j = new JogoServer();
							 j -> rodarJogo();
							 }catch(...){
							 }
						 }else if( menuMulti -> getSelectedButton() == 1 ){
							 try{Cliente *c = new Cliente("g3c07");
							 c->rodarCliente( buffer );
							  }catch(...){
							 }
							 
						 }else if( menuMulti -> getSelectedButton() == 2 ){
							 sair = true;
						 }
					 }
					 clear_bitmap( buffer );
					 blit( background,buffer,0,0,0,0,800,600);
				     menuMulti ->paint( buffer );
				     blit( buffer , screen , 0 , 0 , 0 , 0, 800, 600);
					 rest(65);
					 if(sair){
					   clear_bitmap( buffer );
					 }
				 }

			}
           
       }
       /* Pinta o menu no buffer */
       menu -> paint( buffer );
       
       /* Cola o buffer na janela */
       blit(buffer,screen,0,0,0,0,800,600);
       
       /* Limpa o buffer do teclado */
       clear_keybuf();
       rest(65);
       vsync();
}

return 0;
}
END_OF_MAIN();