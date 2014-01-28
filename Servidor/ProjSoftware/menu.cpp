#include <allegro.h>
#include <cstdio>

#include "button.h"
#include "menu.h"

Menu::Menu(){
   this -> arrayButton = (Button **)calloc( sizeof(Button) , 3 ); 
   this -> next = 0;
   setUpdated( false ); 
   setPaintHorizontal( false );
   setCapacity( 3 );      
   setSelectedButton( 0 ); 
}

Menu::Menu( int numButton ){
   this -> arrayButton = (Button **)calloc( sizeof(Button) , numButton );
   this -> next = 0;
   setPaintHorizontal( false );
   setUpdated( false );
   setCapacity( numButton );
   setSelectedButton( 0 ); 
}

Menu::~Menu(){
   delete[] arrayButton;
}

int Menu::getSelectedButton(){
    return this -> selectedButton;
}

void Menu::setSelectedButton( int n ){
     if( n >= 0 && n < capacity ){
         this -> selectedButton = n;
     }
}

int Menu::getCapacity(){
    return this -> capacity;
}

bool Menu::isUpdated(){
     return this -> updated;
}

void Menu::setUpdated( bool b ){
     this -> updated = b;
}

void Menu::setCapacity( int c ){
     this -> capacity = c;
}

void Menu::incrementSelectedButton(){
     if( selectedButton == capacity - 1 ){
         selectedButton = 0;
     }else{
         selectedButton++;
     }
}

void Menu::decrementSelectedButton(){
     if( selectedButton == 0 ){
         selectedButton = capacity - 1;    
     }else{
         selectedButton--;
     }
}

void Menu::selectNextButton(){
     this -> arrayButton[ selectedButton ] -> setSelected( false );
     incrementSelectedButton();
     this -> arrayButton[ selectedButton ] -> setSelected( true );
}

void Menu::selectPrevButton(){
     this -> arrayButton[ selectedButton ] -> setSelected( false );
     decrementSelectedButton();
     this -> arrayButton[ selectedButton ] -> setSelected( true );
}

int Menu::getNext(){
    return this -> next;
}

void Menu::setNext( int n ){
     if( n >= 0 && n < capacity ){
         this -> next = n;
     }
}

void Menu::addButton( Button *b ){
     if( next < capacity ){
         this -> arrayButton[ next ] = new Button( b );
         this -> next++;
     }
     if( next == 1 ) arrayButton[ 0 ] -> setSelected( true );
     setUpdated( false );
}

void Menu::updateBounds(){
     if( paintHorizontal ){
         for( int i = 0; i < next; i++ ){
                arrayButton[ i ] -> setLocation( x + i*arrayButton[ i ]->getWidth()+gapSize, y );
           }
     }else{
         for( int i = 0; i < next; i++ ){
                //arrayButton[ i ] -> setLocation( this->getX() , this->getY() + (arrayButton[ i ]->getHeight())*i + gapSize );
                arrayButton[ i ] -> setLocation(this->getX(),this->getY()+(arrayButton[ i ]->getHeight()*i+ i*gapSize));
         }
     }
     setUpdated( true );
}


void Menu::paint( BITMAP *window ){
     if( !updated ){
         updateBounds();
     }
     for( int i = 0; i < next; i++ ){
         if( arrayButton[ i ] != NULL ){
          this -> arrayButton[ i ] -> paint( window );
         }
          
     }
     
}

int Menu::getX(){
    return this -> x;
}

int Menu::getY(){
    return this -> y;
}

void Menu::setX( int x1 ){
     this -> x = x1;     
}

void Menu::setY( int y1 ){
     this -> y = y1;
}

void Menu::setLocation( int x1, int y1 ){
     setX( x1 );
     setY( y1 );
}

int Menu::getGapSize(){
    return this -> gapSize;
}

void Menu::setGapSize( int gS ){
     this -> gapSize = gS; 
}

bool Menu::isPaintHorizontal(){
     return this -> paintHorizontal;     
}

void Menu::setPaintHorizontal( bool b ){
     this -> paintHorizontal = b;
}
