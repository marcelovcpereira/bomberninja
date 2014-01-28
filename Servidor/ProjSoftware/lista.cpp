#ifndef LISTA_CPP
#define LISTA_CPP


#include <allegro.h>
#include <vector>

using std::vector;

#include "objeto2D.h"


class ListaObjetos2D{
      
      private:
		  vector<Objeto2D*> *vetor;
		  int tamanho;
              
      public:
             ListaObjetos2D(){
                 vetor = new vector<Objeto2D*>();
				 tamanho = vetor -> size();
             }
             
             void inserirObjeto( Objeto2D *obj ){
                  this -> vetor -> push_back( obj );
				  tamanho = vetor -> size();
             }
             
             void removerObjeto( Objeto2D *obj ){
				 vector<Objeto2D*>::iterator it = this -> vetor -> begin();
				 int i = 0;
				 Objeto2D *retorno = NULL;
				 int tam = this -> vetor -> size();
				 while( obj != *it && i < tam ){
					it++;
					i++;
				 }
				 if( i != tam ){
					 vetor -> erase( it ); 
				 }
				 tamanho = vetor -> size();
               
             }
             
             int *getTamanho() {
                 return &tamanho;
             }

			 int size(){
				return this -> vetor -> size();
			 }


			 Objeto2D* at( int i ){
				return this -> vetor -> at( i );
			 }
};

#endif
