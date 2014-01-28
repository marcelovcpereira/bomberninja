#ifndef MENU_H
#define MENU_H


#include <allegro.h>

#include "button.h"




/* Definição da classe Menu que contém um array de Button's */
class Menu{
      private:
              Button **arrayButton;
              int selectedButton;
              int capacity;
              int next;
              int x;
              int y;
              int gapSize;
              bool paintHorizontal;
              bool updated;
              
              /* funções privadas */
             void setCapacity( int c );       //
             void incrementSelectedButton();   //
             void decrementSelectedButton();   //
             void updateBounds();
              
      public:
             Menu();                           //
             Menu( int numButton );            //
             ~Menu();                          //
             int getSelectedButton();          //
             void setSelectedButton( int n );  //
             void paint( BITMAP *window );
             void selectNextButton();          //
             void selectPrevButton();          //
             int getCapacity();                //
             void addButton( Button *b );      //
             int getNext();                    //
             void setNext( int n );            //
             void setLocation( int x1, int y1 );
             int getX();
             void setX( int x1 );
             int getY();
             void setY( int y1 );
             int getGapSize();
             void setGapSize( int gS );
             bool isPaintHorizontal();
             void setPaintHorizontal( bool b );
             bool isUpdated();
             void setUpdated( bool b );
};


#endif
