/*#include <iostream>
#include "server.cpp"
#include <string>
#include <coss/CosNaming.h>
#include <allegro.h>
#include <winalleg.h>
#include "jogoServer.h"

int x = 0;
int y = 0;

using namespace std;
int main(){

	allegro_init();
	install_keyboard();
	install_timer(); 
	install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
	SAMPLE *menuSom = load_wav("sons\\menu.wav");
	set_color_depth( 32 );
	set_gfx_mode( GFX_AUTODETECT_WINDOWED , 800, 600, 0, 0 );
	set_window_title("BomberNinja");
	JogoServer *j = new JogoServer();
	j -> rodarJogo();
	return 0;

}END_OF_MAIN()*/