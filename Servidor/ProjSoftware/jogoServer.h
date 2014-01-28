//#include <cstdio>
//#include <typeinfo>
#include <allegro.h>
//#include <cmath>
//#include <cstring>
#include <iostream>
#include <vector>

#ifndef SERVER_CPP
#include "server.cpp"
#endif

#include <string>
#include <coss/CosNaming.h>
//#include <winalleg.h>

#include <cstdio>

#include "menuJogo.cpp"   
#include "mapaServer.h"       
#include "explosao.h"   
#include "bomba.h"
#include "carta.h"
#include "ninja.h"  
#include "fumaca.h" 
#include "lista.cpp"
#include "painel.h" 



using namespace std;

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
#define NUM_OBJ 1 
#define NUM_INFO 10
#define NUM_CICLOS 4

 volatile int tempoServer;
 void incrementaTempoServer(){
        tempoServer++;
 }END_OF_FUNCTION( incrementaTempoServer );
      

static DWORD CALLBACK roda( void *parameter ){
	((CORBA:: ORB *)parameter)-> run();
	return 0;
}
 

class JogoServer{
private :
         
          BITMAP *buffer;
          BITMAP *bombas[NUM_BOMBAS];
          Ninja *ninja;
		  Ninja *player2;
          int estagioAtual;
		  Teclado *teclado;
		  //VetorObjetos *vetor;
		  vector<ObjetoSerial*> *array;
          MapaServer *mapa;
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
		  PortableServer::POA_var poa;
		  PortableServer::Servant iRemote_servant;
		  int indiceVetor;
		  bool pronto;
		  bool acabou;
		  bool clienteSaiu;
 
public:
          JogoServer(){
          pintouHurry = false;
          tempoServer = 0;
          timeUp = false;
          criouTimeUp = false;
          zerouJogo = false;
		  clienteSaiu = false;
          LOCK_VARIABLE( tempoServer ); //adiciona a variavel "tempo" como o tempo do cronometro

          LOCK_FUNCTION( incrementaTempoServer ); //adiciona a função "incrementaTempo" como função do tempo

          install_int( incrementaTempoServer , 1  ); //installa a função que contara de 100 em 100 milisegundos
        
          buffer = create_bitmap(800,600);//bitmap para o double buffering
          ninja = new Ninja();
		  ninja -> setVidas( 1 );
		  player2 = new Ninja();
		  player2 -> setVidas( 1 );
          bombas[ 0 ] = load_bitmap("images\\bomba0.bmp",NULL);
          bombas[ 1 ] = load_bitmap("images\\bomba2.bmp",NULL);
          bombas[ 2 ] = load_bitmap("images\\bomba3.bmp",NULL);
          bombas[ 3 ] = load_bitmap("images\\bomba4.bmp",NULL);
          estagioAtual = MapaServer::TIPO1;
          mapa = new MapaServer( estagioAtual, ninja,player2,&tempoServer);
          menu = new MenuJogo( &tempoServer , ninja );
          efeitos = new ListaObjetos2D();
          somBomba = load_wav("sons/hehehe.wav"); 
          musica = load_midi("sons/multiplayer.mid");
          
           arrayEstagio[0] = load_bitmap("images\\stage1.bmp",NULL);
           arrayEstagio[1] = load_bitmap("images\\stage2.bmp",NULL);
           imagemHurry = load_bitmap("images\\painelHurry.bmp",NULL);
           imagem1Up = load_bitmap("images\\painelVida.bmp",NULL);
           imagemTimeUp = load_bitmap("images\\painelTempo.bmp",NULL);
           teclado = new Teclado();
		   teclado -> keys.length( 6 );
		   //vetor = new VetorObjetos();
		   //vetor -> vetor.length( NUM_OBJ );
		   indiceVetor = 0;
		   pronto = false;
		   acabou = false;
			array = new vector<ObjetoSerial*>();
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

		  /*void zerarVetor(){
			  for( int i = 0; i < NUM_OBJ; i++ ){
				  this -> vetor ->vetor[ i ].tipo = 0;
			  }
			  indiceVetor = 0;
		  }*/

		  void adicionarObjeto( ObjetoSerial obj ){
			 /* if( indiceVetor < NUM_OBJ ){

				  this -> vetor -> vetor[ indiceVetor ].tipo = obj.tipo;
				  this -> vetor -> vetor[ indiceVetor ].x = obj.x;
				  this -> vetor -> vetor[ indiceVetor ].y = obj.y;
				  
				  for( int i = 0; i < NUM_INFO; i++ ){
					  this -> vetor -> vetor[indiceVetor].info[i]  = obj.info[i];

				  }

			    indiceVetor++;

			  }else{
				allegro_message("LOTOU O ARRAY!!!!!");
			  }*/
		  }


		  /*void adicionarObjetoUltima( UltimaTentativa *ult ){
			  if( indiceVetor < NUM_OBJ ){

				  this -> vetor -> vetor[ indiceVetor ].tipo = ult->type;
				  this -> vetor -> vetor[ indiceVetor ].x = ult->x;
				  this -> vetor -> vetor[ indiceVetor ].y = ult->y;
				  
				  for( int i = 0; i < NUM_INFO; i++ ){
					//  this -> vetor -> vetor[indiceVetor].info[i]  = ult->info[i];

				  }

			    indiceVetor++;

			  }else{
				allegro_message("LOTOU O ARRAY!!!!!");
			  }
		  }*/



		  void conectarServidor( Teclado *t, bool *p, bool *a, vector<ObjetoSerial*> *array ){

			  Teclado *teclado = t;
			  bool *pronto = p;
			  bool *acabou = a;	
			  char *argv[] = {"a parameter","-ORBInitRef","NameService=corbaloc::g3c25:9001/NameService"};
			  int argc = 3;
			  std::cout << "Initialize the ORB" << std::endl;

			  CORBA:: ORB_var orb = CORBA::ORB_init( argc, argv );
			  std::cout << "Obtain a reference to the RootPOA and its manager" << std::endl;


			  CORBA::Object_var poaobj = orb -> resolve_initial_references( "RootPOA" );

			  poa = PortableServer::POA::_narrow( poaobj );

			  PortableServer::POAManager_var mgr = poa -> the_POAManager();

			  std::cout << "Create an IRemote" << std::endl;

			  iRemote_servant = new Remote( teclado, pronto,acabou, array );

			  std::cout << "Activate the IRemote" << std::endl;


			  CORBA::Object_var the_iRemote = iRemote_servant -> _this();

			  std::cout << "Obtain a reference to the naming service object" << std::endl;

			  CORBA::Object_var nsobj = orb -> resolve_initial_references("NameService");

			  std::cout << "Obtain a name context" << std::endl;

			  CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow( nsobj );

			  std::cout << "Export the IRemote.ior to the name service" << std::endl;

			  CosNaming::Name name;
			  name.length(1);
			  name[0].id = (const char *)"myIRemote";
			  name[0].kind = (const char*)"";
			  nc -> rebind( name, the_iRemote );
			  std::cout <<	"Activate the POA and starting serving requests" << std::endl;

			  std::cout << "Running..." << std::endl;
			  mgr -> activate();
			  DWORD id;
			  CreateThread(0,0, roda,orb,0,&id);
			  

		  }
          
          void zerarListaEfeitos(){
             delete(efeitos);
             efeitos = new ListaObjetos2D();
          }

		  void checarTecladoCliente(Teclado *teclado,int tempoC,int tempoCvelho,int tempoServer){
			  if( teclado->keys[0] == 1 ){
				  player2 -> andarEsquerda();
				  if( mapa->colideCaixaEsq(player2) )
					  player2->setX( player2->getX() + player2 ->getVelocidade()/10 );
			  }else if( teclado->keys[1] == 1 ){
				  player2 -> andarDireita();
				  if( mapa->colideCaixaDir(player2) )
					  player2->setX( player2 ->getX() - player2 ->getVelocidade()/10 );
			  }else if( teclado->keys[2] == 1 ){
				  player2 -> andarCima();
				  if( mapa->colideCaixaCima(player2) )
					  player2->setY( player2 ->getY() + player2 ->getVelocidade()/10 );
			  }else if( teclado->keys[3] == 1 ){
				  player2 -> andarBaixo();
				  if( mapa->colideCaixaBaixo(player2) )
					  player2->setY( player2 ->getY() - player2 ->getVelocidade()/10 );
			  }else{ 
				  player2 -> parar(); 
			  }
			  if( teclado -> keys[5] == 1 ){
					clienteSaiu = true;
			  }

			  if( teclado->keys[4]==1 && player2 -> getEstadoAtual() != Ninja::MORRENDO){ 
				  tempoC = tempoServer;
				  if( tempoC - tempoCvelho >= 100 ){ 
					  tempoCvelho = tempoC;
					  if( player2 -> getNumeroBombas() < player2 -> getNumMaxBombas() ){

						  Tile *temp = mapa -> getTileAtXY(player2->getX()+20,player2->getY()+40);

						  if( mapa -> getBombaAtXY(temp->getX(),temp->getY()) == NULL ){
							  Bomba *nova = new Bomba( bombas );
							  nova -> setForca( player2 -> getForca() );
							  nova -> setCronometro( &tempoServer );
							  nova -> setBounds(temp->getX(),temp->getY(),TILE_WIDTH,TILE_HEIGHT);
							  player2 -> inserirBomba( nova );
							  player2 -> incrementarBombas();
							  player2 -> setBombaPlantada( nova );
							  player2 -> setPodePassar( true );
						  }
					  }

				  }
			  }
		  }
          
		  void  rodarJogo(){
			  int i = 0;
			  //tempo atual e tempo anterior
			  int t=0;
			  int oT = 0;
			  int tempoB = 0;
			  int tempoC = 0;
			  int tempoBvelho = 0;
			  int tempoCvelho = 0;
			  ninja -> setCronometro( &tempoServer );
			  player2 -> setCronometro( &tempoServer );
			  int ultimoPonto = 0;
			  tempoBvelho = 0; 
			  mapa ->setMenu(menu);
			  int tempoV = 0;
			  bool sair = false;
			  
			  //CONEXAO
			  conectarServidor( teclado, &pronto, &acabou, array );
			  //CONEXAO

			  while( teclado -> keys[0] != 1 && !sair ){
			    if(key[KEY_ESC]) sair = true;
				clear_bitmap( buffer );
				textprintf_ex( buffer, font, 50,50,makecol(255,255,255),makecol(0,0,0),"Esperando Player 2!!!");
				blit( buffer, screen, 0, 0, 0, 0, 800, 600 );
			  }
			  while( !sair  ){  
				  stop_midi();
				  if( key[KEY_ESC] ){
					  break;
				  }

				  /* DRAW GAME */
				  if( ninja -> getVidas() == 0 && player2 -> getVidas() == 0 ){
					  int uT2 = tempoServer;
					  while( tempoServer - uT2 < 1200 ){
						  clear_bitmap(buffer);
						  rectfill( buffer, 0,0,800,600,makecol(0,0,0) );
						  //masked_blit( arrayEstagio[estagioAtual],buffer,0,0,200,200,400,100);
						  textout( buffer, font,"EMPATE!!",370,200,makecol(0,0,255));
						  blit(buffer,screen,0,0,0,0,800,600);
					  }
					  sair = true;
					  //mapa -> setZerouMapa( true );
				  }
				  /* PLAYER 2 WIN */
				  else if( ninja -> getVidas() == 0 ){
					  int uT2 = tempoServer;
					  while( tempoServer - uT2 < 1200 ){
						  clear_bitmap(buffer);
						  rectfill( buffer, 0,0,800,600,makecol(0,0,0) );
						  //masked_blit( arrayEstagio[estagioAtual],buffer,0,0,200,200,400,100);
						  textout( buffer, font,"PLAYER 2 WIN!!",370,200,makecol(0,0,255));
						  blit(buffer,screen,0,0,0,0,800,600);
					  }
					  sair = true;
					  //mapa -> setZerouMapa( true );
				  }
				  /* PLAYER 1 WIN */
				  else if( player2 -> getVidas() == 0 ){
					  int uT2 = tempoServer;
					  while( tempoServer - uT2 < 1200 ){
						  clear_bitmap(buffer);
						  rectfill( buffer, 0,0,800,600,makecol(0,0,0) );
						  //masked_blit( arrayEstagio[estagioAtual],buffer,0,0,200,200,400,100);
						  textout( buffer, font,"PLAYER 1 WIN!!",370,200,makecol(0,0,255));
						  blit(buffer,screen,0,0,0,0,800,600);
					  }
					  sair = true;
					  //mapa -> setZerouMapa( true );
				  }

				  if( zerouJogo )
				  {
					  int uT2 = tempoServer;
					  while( tempoServer - uT2 < 1200 ){
						  clear_bitmap(buffer);
						  rectfill( buffer, 0,0,800,600,makecol(0,0,0) );
						  textout( buffer, font,"Voce Ganhou!!",370,200,makecol(0,0,255));
						  blit(buffer,screen,0,0,0,0,800,600);
					  }
					  sair = true;
				  }
				  if( ninja -> getVidas() == 1 && player2 -> getVidas() == 1 ){		  
					  zerarListaEfeitos();
					  menu->zerarTempo(TEMPO_ESTAGIO);
					  criouTimeUp = false;
					  pintouHurry = false;
					  ninja->setVivo( true );
					  ninja -> setBounds( 40, 10, 35, 57 );
					  ninja ->setEstadoAtual(Ninja::PARADO);
					  ninja ->setBombaPlantada( NULL );
					  ninja -> setNumBombas( 0 );

					  player2->setVivo( true );
					  player2 -> setBounds( 720, 10, 35, 57 );
					  player2 ->setEstadoAtual(Ninja::PARADO);
					  player2 ->setBombaPlantada( NULL );
					  player2 -> setNumBombas( 0 );
					  free(mapa);
					  mapa = NULL;

					  mapa = new MapaServer( estagioAtual, ninja,player2,&tempoServer );
					  mapa -> setPersonagem( ninja );
					  mapa -> setPersonagem2( player2 );

					  play_midi( musica, 1 ); 
				  }
				  int contador = 0;
				  while( ninja -> isVivo() && player2 -> isVivo() ){ 
					  //limpa o buffer da tela
					  clear_bitmap(buffer);
					  //limpa o buffer do teclado
					  clear_keybuf();

					  //se apertou ESC sair
					  if(key[KEY_ESC]) break;         
					  //se apertou esquerda...
					  if( key[KEY_LEFT] ){
						  ninja -> andarEsquerda();
						  if( mapa->colideCaixaEsq(ninja) )
							  ninja->setX( ninja->getX() + ninja ->getVelocidade()/10 );
					  }else
						  //se apertou direita...
						  if( key[KEY_RIGHT] ){
							  ninja -> andarDireita();
							  if( mapa->colideCaixaDir(ninja) )
								  ninja->setX( ninja ->getX() - ninja ->getVelocidade()/10 );

						  }else 
							  //se apertou pra cima...
							  if( key[KEY_UP] ){
								  ninja -> andarCima();
								  if( mapa->colideCaixaCima(ninja) )
									  ninja->setY( ninja ->getY() + ninja ->getVelocidade()/10 );

							  }else
								  //se apertou pra baixo...
								  if( key[KEY_DOWN] ){
									  ninja -> andarBaixo();
									  if( mapa->colideCaixaBaixo(ninja) )
										  ninja->setY( ninja ->getY() - ninja ->getVelocidade()/10 );


								  }else //se não apertou nada...  
								  { 
									  ninja -> parar(); 
								  }

								  if( key[ KEY_B ] && ninja -> getEstadoAtual() != Ninja::MORRENDO){ 
									  tempoB = tempoServer;

									  if( tempoB - tempoBvelho >= 100 ){ 
										  tempoBvelho = tempoB;
										  if( ninja -> getNumeroBombas() < ninja -> getNumMaxBombas() ){

											  Tile *temp = mapa -> getTileAtXY(ninja->getX()+20,ninja->getY()+40);

											  if( mapa -> getBombaAtXY(temp->getX(),temp->getY()) == NULL ){
												  Bomba *nova = new Bomba( bombas );
												  nova -> setForca( ninja -> getForca() );
												  nova -> setCronometro( &tempoServer );
												  nova -> setBounds(temp->getX(),temp->getY(),TILE_WIDTH,TILE_HEIGHT);
												  //mapa -> inserirObjeto( nova ); 
												  ninja -> inserirBomba( nova );
												  ninja -> incrementarBombas();
												  ninja -> setBombaPlantada( nova );
												  ninja -> setPodePassar( true );
												  // play_sample( somBomba, 255, 125, 2000, 0 );

											  }
										  }

									  }
								  }

								  this -> checarTecladoCliente(teclado,tempoC,tempoCvelho,tempoServer);
								  if( clienteSaiu ){
									  zerouJogo = true;
									  ninja -> setVivo( false );
									  player2 -> setVivo( false );
									  sair = true;
									  break;
								  
								  }
								  //Criar efeito de Hurry UP 
								  if((menu->getTempo()/1000 ) <= TEMPO_HURRY ){
									  if( !pintouHurry ){                     
										  Painel *hurry = new PainelHurry( imagemHurry, &tempoServer );
										  efeitos -> inserirObjeto( hurry );
										  pintouHurry = true;
									  }

								  }

							//	  while(!acabou){}

							//	 array -> clear();
								  //ZERAR VETOR
								  //this->zerarVetor();

							/*	  if(acabou){
									  array->clear();
								   ObjetoSerial *porra = new ObjetoSerial();
								  porra->tipo = 0;
								  porra->x =0;
								  porra->y=0;
								  porra->info1 = 0;
								  porra->info2 = 0;
								  porra->info3 = 0;
								  porra->info4 = 0;
								  porra->info5 = 0;
								  porra->info6 = 0;
								  porra->info7 = 0;
								  porra->info8 = 0;
								  porra->info9 = 0;
								  porra->info10 = 0;
								  array ->push_back(porra);
								   mapa -> inserirSeriais( array );

								  
								  
								  }*/
								  ObjetoSerial *porra = new ObjetoSerial();
								  porra->tipo = 0;
								  porra->x =0;
								  porra->y=0;
								  porra->info1 = 0;
								  porra->info2 = 0;
								  porra->info3 = 0;
								  porra->info4 = 0;
								  porra->info5 = 0;
								  porra->info6 = 0;
								  porra->info7 = 0;
								  porra->info8 = 0;
								  porra->info9 = 0;
								  porra->info10 = 0;


								  if(contador%NUM_CICLOS == 0){
									  array ->push_back(porra);
								  }
								  

								   mapa -> paint( buffer );
								   UltimaTentativa *n;
								  // mapa -> inserirSeriais( array );
								  //pintar mapa no buffer
								 
								 
								   //adiciona objeto serial ao vetor
								/*  VetorObjetos v = mapa->getSerializable();
									
								  int j = 0;
								  bool acabou = false;

								  while (j < NUM_OBJ && !acabou){
									  if(v.vetor[j].tipo == 20){
										  acabou = true;
									  }else{
										 // adicionarObjeto(v.vetor[j]);
									  }
										j++;
								  }
*/

									//delete array;
									//array = new vector<ObjetoSerial*>( NUM_OBJ, NULL );
								
								  

								  ninja -> paint( buffer );
								  //ObjetoSerial *o = ninja -> getSerial();
								  //UltimaTentativa *n = ninja->getSerial();
								  //this->inserirUltima(n);
								  
								  //adiciona objeto serial ao vetor
								 //adicionarObjeto(ninja->getSerializable());

								  //UltimaTentativa *u = ninja ->ultima();
								  //adicionarObjetoUltima(u);
								  /*this ->vetor ->vetor[0].x = ninja -> getX();
								  this -> vetor -> vetor[0].y = ninja -> getY();
								  this -> vetor -> vetor[0].tipo = 12;*/

								/*  ObjetoSerial *por = new ObjetoSerial();
								  por->tipo = 12;
								  por->x =player2->getX();
								  por->y=player2->getY();
								  por->info1 = player2->getIndice();
								  por->info2 = 0;
								  por->info3 = 0;
								  por->info4 = 0;
								  por->info5 = 0;
								  por->info6 = 0;
								  por->info7 = 0;
								  por->info8 = 0;
								  por->info9 = 0;
								  por->info10 = 0;
                                  array -> push_back( por );*/
								  //pinta o player 2
								  player2 -> paint( buffer );
								  //n = player2->getSerial();
								 // this->inserirUltima(n);

								  //adiciona objeto serial ao vetor
						//		 adicionarObjeto(player2->getSerializable());

								  
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
												  ninja -> setEstadoAtual( Personagem::MORRENDO );
												  player2 -> setEstadoAtual( Personagem::MORRENDO );
											  }else{
												  ((Painel*)obj) -> paint( buffer ); 
												  if(contador%NUM_CICLOS == 0){
												  n = ((Painel*)obj)->getSerial();
												  this->inserirUltima(n);
												  }
												  //adiciona objeto serial ao vetor
								               //  adicionarObjeto(((Painel*)obj)->getSerializable());
											  } 
										  }else{
											  if( ((Painel*)obj)-> jaTerminou() ){
												  efeitos -> removerObjeto( obj );
											  }else{
												  ((Painel*)obj) -> paint( buffer );
												  if(contador%NUM_CICLOS == 0){
												  n = ((Painel*)obj)->getSerial();
												  this->inserirUltima(n);
												  }
												  //adiciona objeto serial ao vetor
								              //    adicionarObjeto(((Painel*)obj)->getSerializable());
											  } 
										  }
									  }else if( strcmp( obj->getNome(), "Pontos") == 0 )
									  {
										  if( ((Pontos*)obj) ->jahAcabou() ){
											  this -> efeitos -> removerObjeto( obj );
										  }else{
											  ((Pontos*)obj) -> paint( buffer );
											  if(contador%NUM_CICLOS == 0){
											  n = ((Pontos*)obj)->getSerial();
												  this->inserirUltima(n);
											  }
											  //adiciona objeto serial ao vetor
								          //    adicionarObjeto(((Painel*)obj)->getSerializable());

											  
										  }
									  }
									  i++;
								  }
                                  
								  //this-> array ->push_back( menu->getSerial() );
								  menu -> paint( buffer );
								  if(contador%NUM_CICLOS == 0){
								  n = menu->getSerial();
								  this->inserirUltima(n);


								  n = player2->getSerial();
								  this->inserirUltima(n);

								  n = ninja->getSerial();
								  this->inserirUltima(n);

								   mapa -> inserirSeriais( array );
								  
								  //adicionarObjeto(menu->getSerializable());

								  /*textprintf_ex( buffer, font, 220,20,makecol(255,255,255),makecol(0,0,0),"SIZE 2 :%d",mapa->getBombas2()->size());	
								  textprintf_ex( buffer, font, 20,20,makecol(255,255,255),makecol(0,0,0),"SIZE 1 :%d",mapa->getBombas2()->size());	
								  textprintf_ex( buffer, font, 420,20,makecol(255,255,255),makecol(0,0,0),"PLAYER 1 : %d",ninja->getBombas()->size());
								  textprintf_ex( buffer, font, 620,20,makecol(255,255,255),makecol(0,0,0),"PLAYER 2 :%d",player2->getBombas()->size());	

								  textprintf_ex( buffer, font, 500,20,makecol(255,255,255),makecol(0,0,0),"CRONOMETRO: %d",tempoServer);	

			*/

								  //blitar o buffer na tela
								  this -> pronto = true;
								  this -> acabou = false;
								  }

								  blit(buffer,screen,0,0,0,0,800,600);


								  
								  while(!acabou){}


								  if(menu->getTempo() <= 0){
									  if(!criouTimeUp){
										  Painel *timeUp = new PainelTimeUp( imagemTimeUp, &tempoServer );
										  criouTimeUp = true;
										  efeitos->inserirObjeto(timeUp);
									  }
								  }

								  //mapa->checarPersonagem(ninja);
								  this -> checarEfeitosMapa();

								  if( !ninja -> isVivo() ){
									  ninja->setVidas(ninja->getVidas()-1);
								  }
								  if( !player2 -> isVivo() ){
									  player2->setVidas(player2->getVidas()-1);
								  }
								  
								  contador++;


				  }

			  }
			  poa -> destroy( TRUE,TRUE );
			  delete iRemote_servant;

			  
		  }


		  void inserirUltima(UltimaTentativa *ult){
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


};
