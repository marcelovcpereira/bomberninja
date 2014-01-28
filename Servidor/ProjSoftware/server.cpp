#include <iostream>
#include <fstream>
#include "IRemote.h"
#include <string>
#include <allegro.h>
#include "ninja.h"
#include <vector>



#ifndef SERVER_CPP
#define SERVER_CPP
#endif

#define TAMANHO 2

using std::vector;

class Remote : virtual public POA_IRemote{
private:
	Teclado *teclado;
	vector<ObjetoSerial*> *array;
    bool *isPronto;
	bool *isAcabou;
	int indice;
public:

	Remote( Teclado*t, bool *p, bool *a, vector<ObjetoSerial*> *arr ){
		this -> teclado = t;
		this -> isPronto = p;
		this -> isAcabou = a; 
		this -> array = arr;
		this -> indice = 1;
	}

	void sendKeys( const ::Teclado& keys ){
		copiarTeclado( keys );
	}

	void copiarTeclado( const::Teclado& k ){
		for(int i = 0; i < 6; i++ )
		teclado -> keys[i] = k.keys[i];
	}

	CORBA::Boolean pronto(){
		return (*isPronto);
	}

	CORBA::Boolean acabou(){
		return (*isAcabou);
	}

	::ObjetoSerial getProximo(){
        ObjetoSerial no;
		
		if( this -> array -> size() == 1 ){
		    *isAcabou = true;
			*isPronto = false;
		}


		ObjetoSerial *objeto = this -> array -> back();
		this -> array -> pop_back();

		if( objeto != NULL ){
			no.info1  = objeto -> info1;
			no.info2  = objeto -> info2;
			no.info3  = objeto -> info3;
			no.info4  = objeto -> info4;
			no.info5  = objeto -> info5;
			no.info6  = objeto -> info6;
			no.info7  = objeto -> info7;
			no.info8  = objeto -> info8;
			no.info9  = objeto -> info9;
			no.info10 = objeto -> info10;
			no.tipo   = objeto -> tipo;
			no.x      = objeto -> x;
			no.y      = objeto -> y;
		}else{
			no.info1  = 0;
			no.info2  = 0;
			no.info3  = 0;
			no.info4  = 0;
			no.info5  = 0;
			no.info6  = 0;
			no.info7  = 0;
			no.info8  = 0;
			no.info9  = 0;
			no.info10 = 0;
			no.tipo   = 0;
			no.x      = 0;
			no.y      = 0;
		}
		//this -> incrementarIndice();
		
		return  no;
	}

	/*void incrementarIndice(){
		if( indice == array->size() ){
			indice = 0;
			isAcabou = true;
			*isPronto = false;
		}else{
			indice++;
		}
	}*/
};


