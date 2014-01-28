#include <iostream>
#include <cstdio>
#include <fstream>
#include "IRemote.h"
#include <string>
#include <coss/CosNaming.h>
#include <allegro.h>
#include "PaintCliente.cpp"
#include "tile.h"
#define NUM_TEC 6
 
#define LINHAS 13
#define COLUNAS 20
#define TILE_WIDTH 40
#define TILE_HEIGHT 40

using std::string;

class Cliente{
private:
	    string ip;
		BITMAP *block;
		BITMAP *floor;
		Tile *arrayTiles[LINHAS][COLUNAS];




public:
	Cliente(string i){
	    this->ip = i;
		
        this -> floor = load_bitmap("images\\floor1.bmp" , NULL );
        this -> block = load_bitmap("images\\block1.bmp" , NULL );
		inicializarArray();

	}

	void adicionarTecla(int indice , Teclado &t){
		if(indice >= 0 && indice < NUM_TEC)
			t.keys[indice] = 1;

	}

	void zerarTeclado(	Teclado &t ){

		for(int i = 0; i < NUM_TEC; i++){
			t.keys[i] = 0;
		}

	}

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

   void paintTile(BITMAP *b){

	   for( int i =0; i < LINHAS; i++ ){
                        for( int j = 0; j < COLUNAS; j++ ){
                             arrayTiles[ i ][ j ] -> paint(b);

                        }
                  }
                  
   }

	void rodarCliente(BITMAP *buffer){
		
		std::cout << "Initialize the ORB" << std::endl;
		
        string s = "NameService=corbaloc::" + this->ip + ":9001/NameService";
		char *c = new char[s.length()+1];
		strcpy( c, s.c_str() );

		char *argv[] = {"ABC", "-ORBInitRef","NameService=corbaloc::g3c25:9001/NameService" };
		int argc = 3;

		CORBA::ORB_var orb = CORBA::ORB_init (argc,argv);

		std::cout <<"Obtain a reference to the naming service object" << std::endl;

		CORBA::Object_var nsobj = orb->resolve_initial_references("NameService");

		CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(nsobj);

		CosNaming::Name name;
		name.length(1);
		name[0].id = (const char*) "myIRemote";
		name[0].kind = (const char*) "";

		CORBA::Object_var obj;
		obj = nc->resolve(name);

		IRemote_var iRemote = IRemote::_narrow(obj);
		std::cout << "EBA" <<std::endl;
		Teclado t;
		t.keys.length(NUM_TEC);
		t.keys[0] = 1;
		PaintCliente *pC = new PaintCliente();
		iRemote -> sendKeys( t );

		zerarTeclado(t);
		while( !key[KEY_ESC] ){
			//esq = 0 dir = 1 cima = 2 baixo = 3 b = 4 

			if(key[KEY_LEFT]){

				adicionarTecla( 0 , t );

			}else if(key[KEY_RIGHT]){

				adicionarTecla( 1 , t );

			}else if(key[KEY_UP]){

				adicionarTecla( 2 , t );

			}else if(key[KEY_DOWN]){

				adicionarTecla( 3 , t );

			}
			
			if(key[KEY_B]){

				adicionarTecla( 4 , t );

			}
			iRemote -> sendKeys( t );
			while (!iRemote->pronto()){

			}

			clear_bitmap(buffer);
			ObjetoSerial n;
            paintTile(buffer);
			while(/*!iRemote ->acabou()*/ true){
				n = iRemote -> getProximo();
				if( n . tipo == 0 ){
					break;
				}
				pC->paint(n, buffer );
			}

         /*   while(!iRemote->acabou() ){
				n = iRemote -> getProximo();
				pC->paint(n, buffer );

			}*/

			blit(buffer,screen,0,0,0,0,800,600);
			zerarTeclado(t);
		}
		 
        zerarTeclado( t );
		adicionarTecla( 5 , t );
		iRemote -> sendKeys( t );
		
			



	}
};
