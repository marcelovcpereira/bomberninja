#include <allegro.h>

#include "color.h"

Color::Color(){
    setRed( 0 );
    setGreen( 0 );
    setBlue( 0 );
}

Color::Color( int r, int g, int b ){
   setRed( r );
   setGreen( g );
   setBlue( b );
}

Color::Color( Color *c ){
   setRed( c ->getRed() );
   setGreen( c -> getGreen() );
   setBlue( c -> getBlue() );
}

int Color::getRed(){
   return this -> red;
} 

int Color::getGreen(){
   return this -> green;
}

int Color::getBlue(){
   return this-> blue;
}

void Color::setRed( int r ){
   if( r >= 0 && r <= 255 ){
      this -> red = r;
   }                     
   else{
      this -> red = 0;
   }                
}

void Color::setGreen( int g ){
   if( g >= 0 && g <= 255 ){
      this -> green = g;
   }                     
   else{
      this -> green = 0;
   }
}

void Color::setBlue( int b ){
   if( b >= 0 && b <= 255 ){
      this -> blue = b;
   }                     
   else{
      this -> blue = 0;
   }
}

int Color::getColor(){
   return makecol( getRed(), getGreen(), getBlue() );
}
