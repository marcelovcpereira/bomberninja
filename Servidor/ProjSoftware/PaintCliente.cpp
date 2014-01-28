
#include <allegro.h>


#ifndef __IREMOTE_H__
#include "IRemote.h"
#endif


#define tamanho 50

class PaintCliente {

	  private:
			BITMAP *bombas[4];
			BITMAP *cartas[10];
			BITMAP *pontos[6];
			BITMAP *explosao[9];
			BITMAP *fumaca[3];
			BITMAP *cron[11];
            BITMAP *vidas[11];
            BITMAP *score[12];
            BITMAP *carta[5];
            BITMAP *menu;
			BITMAP *ninja[15];
			BITMAP *tile[3];
			BITMAP *painel[3];

      public:
		  PaintCliente (){
			  //bombas = new BITMAP[4];
			  this -> carregarBomba();

			  //cartas = new BITMAP[10];
			  this -> carregarCartas();

			  //pontos = new BITMAP[6];
			  this -> carregarPontos();

			  //explosao = new BITMAP[9];
			  this -> carregarExplosao();

			  this -> carregarFumaca();

			  //cron = new BITMAP[11];
              //vidas = new BITMAP[11];
              //score = new BITMAP[12];
              //cartas = new BITMAP[5];
			  this -> carregarMenu();

			  //ninja = new BITMAP[15];
			  this -> carregarNinja();

			  //tile = new BITMAP[3];
			  this -> carregarTile();

			  //painel = new BITMAP[3];
			  this -> carregarPainel();

			  //buffer = create_bitmap(800,600);
		  }

		  void paintNinja( ObjetoSerial *c, BITMAP *b ){
			  int indiceAtual = c -> info1;

			  masked_blit( ninja[indiceAtual], b, 0, 0, c->x, c->y, 30, 57);
  
		  }



		  void paint ( ObjetoSerial &obj , BITMAP *buffer ){
		  
		   
		    
		    int x = obj.x;
		    int y = obj.y;
		    int tipo = obj.tipo;
		    if ( tipo == 20 ){
		  	//BOMBA
		  	int nextImage = obj.info1;

		  	masked_blit( bombas[nextImage], buffer, 0, 0, x, y, 40, 45);

		    }else if ( tipo == 1 ){
		  	//CARTA AUMENTAR FOGO
		  	int b = obj.info1;

		  	if (b){
		  		masked_blit(cartas[0], buffer, 0, 0, x, y, 40, 40);       
		                  }
		                  else {
		  		masked_blit(cartas[1], buffer, 0, 0, x, y, 40, 40);   
		                  }

		    }else if ( tipo == 2 ){
		  	//CARTA AUMENTAR VELOCIDADE
		  	int b = obj.info1;

		  	if ( b ){
		  		masked_blit(cartas[2], buffer, 0, 0, x, y, 40, 40);       
		                  }
		                  else {
		  		masked_blit(cartas[3], buffer, 0, 0, x, y, 40, 40);   
		                  }

		    }else if ( tipo == 4 ){
		  	//CARTA NUM BOMBAS
		  	int b = obj.info1;

		  	if ( b ){
		  		masked_blit(cartas[4], buffer, 0, 0, x, y, 40, 40);       
		                  }
		                  else {
		  		masked_blit(cartas[5], buffer, 0, 0, x, y, 40, 40);   
		                  }

		    }else if ( tipo == 6 ){
		  	//CARTA AUMENTAR VIDA
		  	int b = obj.info1;

		  	if ( b ){
		  		masked_blit(cartas[6], buffer, 0, 0, x, y, 40, 40);       
		                  }
		                  else {
		  		masked_blit(cartas[7], buffer, 0, 0, x, y, 40, 40);   
		                  }

		    }else if ( tipo == 7 ){
		  	//CARTA SUPER FOGO
		  	int b = obj.info1;

		  	if ( b ){
		  		masked_blit(cartas[8], buffer, 0, 0, x, y, 40, 40);       
		                  }
		                  else {
		  		masked_blit(cartas[9], buffer, 0, 0, x, y, 40, 40);   
		                  }

		    }else if ( tipo == 8 ){
		  	//PONTOS
		  	int numeroPontos = obj.info1;

		  	masked_blit(pontos[numeroPontos/100], buffer, 0, 0, x, y, 40, 40 );

		    }else if ( tipo == 9 ){
		  	//EXPLOSAO
		  	int posicao = obj.info1;
		  	int indice = obj.info2;

		  	if( posicao == 1 ){
		                     rotate_sprite( buffer, explosao[indice], x, y, itofix(64) );
		                  }else if( posicao == 6 ){
		                     rotate_sprite( buffer, explosao[indice], x, y, itofix(256-64) );
		                  }else if( posicao == 5 ){
		                     rotate_sprite( buffer, explosao[indice], x, y, itofix(64) );
		                  }else if( posicao == 4 ){
		                     rotate_sprite( buffer, explosao[indice], x, y, itofix(128) );
		                  }else{
		                     masked_blit( explosao[indice], buffer, 0, 0, x, y, 40, 40 );
		                  }

		    }else if ( tipo == 10 ){
		  	//FUMAÇA
		  	int imagemAtual = obj.info1;
		  	
		  	masked_blit(fumaca[imagemAtual], buffer, 0, 0, x, y, 40, 40);

		    }else if ( tipo == 11 ){


				 draw_sprite(menu, score[10], 120,6);
				 masked_blit( cron[10],menu,0,0,350,27,25,34);
                 draw_sprite(menu, carta[0], 540,30);
                 draw_sprite(menu, carta[1], 590,30);
                 draw_sprite(menu, carta[2], 640,30);
                 draw_sprite(menu, carta[3], 690,30);
                 draw_sprite(menu, carta[4], 740,30);

		  	//MENU JOGO
		  	int cartas3 = obj.info1;
		  	int cartas0 = obj.info2;
		  	int cartas1 = obj.info3;
		  	int cartas5 = obj.info4;
		  	int cartas6 = obj.info5;
		  	int vid     = obj.info6;
		  	int pontos  = obj.info7;
		  	int min     = obj.info8;
		  	int sec1    = obj.info9;
		  	int sec2    = obj.info10;
		  	
		  	draw_sprite(menu, score[cartas3], 555,10); 
		  	draw_sprite(menu, score[cartas0], 605,10);
		  	draw_sprite(menu, score[cartas1], 655,10);
		  	draw_sprite(menu, score[cartas5], 705,10);
		  	draw_sprite(menu, score[cartas6], 755,10); 

		  	draw_sprite(menu, vidas[vid%10], 87,61);

		  	int p0 = pontos % 10;
		                  int p1 = pontos % 100;
		                  p1 = p1/10;
		                  int p2 = pontos % 1000;
		                  p2 = p2/100;
		                  int p3 = pontos % 10000;
		                  p3 = p3/1000;
		                  masked_blit( score[p3], menu, 0, 0, 130, 32, 12, 13 );
		                  masked_blit( score[p2], menu, 0, 0, 145, 32, 12, 13 );
		                  masked_blit( score[p1], menu, 0, 0, 160, 32, 12, 13 );
		                  masked_blit( score[p0], menu, 0, 0, 175, 32, 12, 13 );

		  	masked_blit( cron[min],  menu, 0, 0, 320, 29, 25, 34);
		                  masked_blit( cron[sec1], menu, 0, 0, 382, 29, 25, 34);
		                  masked_blit( cron[sec2], menu, 0, 0, 425, 29, 25, 34);

		  	draw_sprite(buffer, menu, 0,600-80);

		    }else if ( tipo == 12 ){
		  	//NINJA
		  	int indiceAtual = obj.info1;
		  	
		  	masked_blit( ninja[indiceAtual], buffer, 0, 0, x, y, 30, 57);

		    }else if ( tipo == 14 ){
		  	//BLOCKTILE
		  	
		  	masked_blit( tile[0] , buffer, 0, 0, x, y, 40, 40);

		    }else if ( tipo == 15 ){
		  	//FLOORTILE
		  	
		  	masked_blit( tile[1] , buffer, 0, 0, x, y, 40, 40);

		    }else if ( tipo == 16 ){
		  	//WALLTILE
		  	
		  	masked_blit( tile[2] , buffer, 0, 0, x, y, 40, 40);

		    }else if ( tipo == 17 ){
		  	//PAINEL HURRY
		  	
		  	masked_blit(painel[0], buffer, 0, 0, x, y,445, 80);

		    }else if ( tipo == 18 ){
		  	//PAINEL VIDA
		  	
		  	masked_blit(painel[1], buffer, 0, 0, x, y, 274, 71);

		    }else if ( tipo == 19 ){
		  	//PAINEL TIME UP
		  	
		  	masked_blit(painel[2], buffer, 0, 0, x, y, 370, 80);

		    }


		   


		  }


		  void carregarBomba(){
			 bombas[ 0 ] = load_bitmap("images\\bomba0.bmp",NULL);
			 bombas[ 1 ] = load_bitmap("images\\bomba2.bmp",NULL);
			 bombas[ 2 ] = load_bitmap("images\\bomba3.bmp",NULL);
			 bombas[ 3 ] = load_bitmap("images\\bomba4.bmp",NULL);
		  }


		  void carregarCartas(){
			 cartas[0] = load_bitmap("images\\cartaFogoexe.bmp",NULL);  
             cartas[1] = load_bitmap("images\\cartaFogoexe2.bmp",NULL);
			 cartas[2] = load_bitmap("images\\cartaVelo.bmp",NULL);  
             cartas[3] = load_bitmap("images\\cartaVelo2.bmp",NULL);
			 cartas[4] = load_bitmap("images\\cartaBomba.bmp",NULL);  
             cartas[5] = load_bitmap("images\\cartaBomba2.bmp",NULL);
			 cartas[6] = load_bitmap("images\\cartavida.bmp",NULL);  
             cartas[7] = load_bitmap("images\\cartavida2.bmp",NULL);
			 cartas[8] = load_bitmap("images\\cartasuperfogo.bmp",NULL);  
             cartas[9] = load_bitmap("images\\cartasuperfogo2.bmp",NULL);
		  }


		  void carregarPontos(){
			 pontos[0] = load_bitmap("images\\pontos0.bmp",NULL);
             pontos[1] = load_bitmap("images\\pontos100.bmp",NULL);
             pontos[2] = load_bitmap("images\\pontos200.bmp",NULL);
             pontos[3] = load_bitmap("images\\pontos300.bmp",NULL);
             pontos[4] = load_bitmap("images\\pontos400.bmp",NULL);
             pontos[5] = load_bitmap("images\\pontos500.bmp",NULL);
		  }


		  void carregarExplosao(){
			 explosao[0] = load_bitmap("images\\nucleo0.bmp",NULL);
             explosao[1] = load_bitmap("images\\nucleo1.bmp",NULL);
             explosao[2] = load_bitmap("images\\nucleo2.bmp",NULL);
             explosao[3] = load_bitmap("images\\corpo0.bmp",NULL);
             explosao[4] = load_bitmap("images\\corpo1.bmp",NULL);
             explosao[5] = load_bitmap("images\\corpo2.bmp",NULL);
             explosao[6] = load_bitmap("images\\cabeca0.bmp",NULL);
             explosao[7] = load_bitmap("images\\cabeca1.bmp",NULL);
             explosao[8] = load_bitmap("images\\cabeca2.bmp",NULL);
		  }


		  void carregarMenu(){
		  
			  //cronometro:
                  cron[0] = load_bitmap("images\\numero0.bmp",NULL);
                  cron[1] = load_bitmap("images\\numero1.bmp",NULL);
                  cron[2] = load_bitmap("images\\numero2.bmp",NULL);
                  cron[3] = load_bitmap("images\\numero3.bmp",NULL);
                  cron[4] = load_bitmap("images\\numero4.bmp",NULL);
                  cron[5] = load_bitmap("images\\numero5.bmp",NULL);
                  cron[6] = load_bitmap("images\\numero6.bmp",NULL);
                  cron[7] = load_bitmap("images\\numero7.bmp",NULL);
                  cron[8] = load_bitmap("images\\numero8.bmp",NULL);
                  cron[9] = load_bitmap("images\\numero9.bmp",NULL);
                  cron[10] = load_bitmap("images\\numero2p.bmp",NULL);
                  
                  //vidas
                  vidas[0] = load_bitmap("images\\x0.bmp",NULL);
                  vidas[1] = load_bitmap("images\\x1.bmp",NULL);
                  vidas[2] = load_bitmap("images\\x2.bmp",NULL);
                  vidas[3] = load_bitmap("images\\x3.bmp",NULL);
                  vidas[4] = load_bitmap("images\\x4.bmp",NULL);
                  vidas[5] = load_bitmap("images\\x5.bmp",NULL);
                  vidas[6] = load_bitmap("images\\x6.bmp",NULL);
                  vidas[7] = load_bitmap("images\\x7.bmp",NULL);
                  vidas[8] = load_bitmap("images\\x8.bmp",NULL);
                  vidas[9] = load_bitmap("images\\x9.bmp",NULL);
                  vidas[10] = load_bitmap("images\\rostoBoneco.bmp",NULL);
                  
                  //score
                  score[0] = load_bitmap("images\\small0.bmp",NULL);
                  score[1] = load_bitmap("images\\small1.bmp",NULL);
                  score[2] = load_bitmap("images\\small2.bmp",NULL);
                  score[3] = load_bitmap("images\\small3.bmp",NULL);
                  score[4] = load_bitmap("images\\small4.bmp",NULL);
                  score[5] = load_bitmap("images\\small5.bmp",NULL);
                  score[6] = load_bitmap("images\\small6.bmp",NULL);
                  score[7] = load_bitmap("images\\small7.bmp",NULL);
                  score[8] = load_bitmap("images\\small8.bmp",NULL);
                  score[9] = load_bitmap("images\\small9.bmp",NULL);
                  score[10] = load_bitmap("images\\score.bmp",NULL);
                  score[11] = load_bitmap("images\\mais.bmp",NULL);
                  
                  //cartas
                  carta[0] = load_bitmap("images\\cartaBomba.bmp",NULL);
                  carta[1] = load_bitmap("images\\cartaFogoexe.bmp",NULL);
                  carta[2] = load_bitmap("images\\cartaVelo.bmp",NULL);
                  carta[3] = load_bitmap("images\\cartavida.bmp",NULL);
                  carta[4] = load_bitmap("images\\cartasuperfogo.bmp",NULL);
                  
                  menu = load_bitmap("images\\menu3.bmp",NULL);
		  }


		  void carregarNinja(){
                  ninja[0] = load_bitmap("images\\ninja.bmp",NULL);
                  ninja[1] = load_bitmap("images\\ninjaAndando1.bmp",NULL);
                  ninja[2] = load_bitmap("images\\ninjaAndando2.bmp",NULL);        
                  ninja[3] = load_bitmap("images\\ninjaCostas.bmp",NULL);
                  ninja[4] = load_bitmap("images\\ninjaCostas1.bmp",NULL);
                  ninja[5] = load_bitmap("images\\ninjaCostas2.bmp",NULL);
                  ninja[6] = load_bitmap("images\\ninjaLadoDireito1.bmp",NULL);
                  ninja[7] = load_bitmap("images\\ninjaLadoDireito2.bmp",NULL);
                  ninja[8] = load_bitmap("images\\ninjaLadoDireito3.bmp",NULL);
                  ninja[9] = load_bitmap("images\\ninjaLadoEsquerdo1.bmp",NULL);
                  ninja[10] = load_bitmap("images\\ninjaLadoEsquerdo2.bmp",NULL);
                  ninja[11] = load_bitmap("images\\ninjaLadoEsquerdo3.bmp",NULL);
                  ninja[12] = load_bitmap("images\\ninjamorto2.bmp",NULL);
                  ninja[13] = load_bitmap("images\\ninjamorto3.bmp",NULL);
                  ninja[14] = load_bitmap("images\\ninjamorto4.bmp",NULL);
                  
             }


		  void carregarTile(){
                  tile[0] = load_bitmap("images\\block1.bmp" , NULL );
				  tile[1] = load_bitmap("images\\floor1.bmp" , NULL );
                  tile[2] = load_bitmap("images\\wall1.bmp" , NULL );
             }



		  void carregarPainel(){
                 painel[0] = load_bitmap("images\\painelHurry.bmp" , NULL );
	   		     painel[1] = load_bitmap("images\\painelVida.bmp" , NULL );
                 painel[2] = load_bitmap("images\\painelTempo.bmp" , NULL );
             }


		  void carregarFumaca(){
                 fumaca[0] = load_bitmap("images\\fumaca0.bmp",NULL);
                 fumaca[1] = load_bitmap("images\\fumaca1.bmp",NULL);
                 fumaca[2] = load_bitmap("images\\fumaca2.bmp",NULL);
                  
             }



};