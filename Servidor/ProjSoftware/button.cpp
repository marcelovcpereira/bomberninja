#include <allegro.h>
#include <string>

#include "color.h"
#include "button.h" 

using namespace std;



             Button::Button(){
                   getDefaultInitialize();   
             }
             
             /* Construtor que recebe o texto do Botão */
             Button::Button( string s ){
                   getDefaultInitialize();
                   this -> text = s;
             }
             
             Button::Button( Button *b ){
                  getDefaultInitialize();
                  setBounds( b->getX(), b->getY(), b->getWidth(),b->getHeight());
                  setNormalIcon( b->getNormalIcon() );
                 // setPressedIcon( b->getPressedIcon() );           
             }
             
             /* Inicializa os atributos com valores default */
             void Button::getDefaultInitialize(){
                  setBounds( 30, 30, 100, 35 );
                  setText("Button");
                  setBorderSize( 2 );
				  normalIcon = NULL;
                  //setNormalIcon( load_bitmap("images\\botaoHome.bmp",NULL) );
                 /* setPressedIcon( load_bitmap("images\\botaoHome_focus.bmp",NULL) );
                  setBackColor( new Color( 150, 150, 150 ) );
                  setBorderColor( new Color( 0, 0, 0 ) );
                  setTextColor( new Color( 255, 255, 255 ) );*/
                  this -> selected = false;
             }
             
             int Button::getX(){
                 return this -> x;
             }
             
             void Button::setBounds( int x, int y, int w, int h ){
                  setX( x );
                  setY( y );
                  setWidth( w );
                  setHeight( h );
             }
              
             void Button::setX( int x1 ){
                 this -> x = x1;
             }
             
             BITMAP *Button::getNormalIcon(){
                    return this -> normalIcon;
             }
             
             void Button::setNormalIcon( BITMAP *img ){
                  if( normalIcon != NULL ){
                      delete( normalIcon );
                  }
                  this -> normalIcon = img;
             }
             
             BITMAP *Button::getPressedIcon(){
                    return this -> pressedIcon;
             }
             
             void Button::setPressedIcon( BITMAP *img ){
                  if( pressedIcon != NULL ){
                      delete( pressedIcon );
                  }
                  this -> pressedIcon = img;
             }
             
             int Button::getY(){
                 return this -> y;
             }
             
             void Button::setY( int y1 ){
                 this -> y = y1;
             }
             
             int Button::getWidth(){
                 return this -> width;
             }
             
             void Button::setWidth( int w ){
                  if( w >= 0 )
                    this -> width = w;
             }
             
             int Button::getHeight(){
                 return this -> height;
             }
             
             void Button::setHeight( int h ){
                  if( h >= 0 )
                      this -> height = h;
             }
             
             bool Button::getSelected(){
                  return this -> selected;
             }
             
             void Button::setSelected( bool b ){
                  this -> selected = b;
             }
             
             bool Button::getClicked(){
                  return this -> clicked;
             }
             
             void Button::setClicked( bool b ){
                  this -> clicked = b;
             }
             
             string Button::getText(){
                  return this -> text;
             }
             
             void Button::setText( string s ){
                  this -> text = s;
             }
               
             Color *Button::getBackColor(){
                   return this -> backColor;
             }
             
             void Button::setBackColor( Color *c ){
                  if( backColor != NULL ){
                        delete( backColor );
                  }
                  this -> backColor = new Color( c );
             }
             
             Color *Button::getBorderColor(){
                   return this -> borderColor;
             }
             
             void Button::setBorderColor( Color *c ){
                  if( borderColor != NULL ){
                      delete( borderColor );
                  }
                  this -> borderColor = new Color( c );
             }
             
             Color *Button::getTextColor(){
                   return this -> textColor;
             }
             
             void Button::setTextColor( Color *c ){
                  if( textColor != NULL ){
                     delete( textColor );
                  }
                  this -> textColor = new Color( c );
             }
             
             int Button::getBorderSize(){
                 return this -> borderSize;
             }
             
             void Button::setBorderSize( int b ){
                  if( b >= 0 )
                      this -> borderSize = b;
             }
             
             void Button::paint( BITMAP *window ){
                  if( selected ){
                      rectfill( window,x-4,y-4,x+width+3,y+height+3,makecol(255,255,0));
                      rectfill( window, x-1,y-1,x+width,y+height,makecol(0,0,0));
                      draw_sprite( window, this -> normalIcon , x, y );
                  }else{
                      draw_sprite( window, this -> normalIcon , x, y );
                  }
             }
             
             void Button::paintBorder( BITMAP *window ){
                  int cor = borderColor -> getColor();
                  for( int i = 0; i < borderSize; i++ ){
                     rect(window,x+i,y+i,x+width-(i),y+height-(i),cor);
                  }
             }
             
             bool Button::wasClicked( int xM, int yM ){
                  bool ret = false;
                  if( xM >= x && xM <= x+width ){
                       if( yM >= y && yM <= y+height ){
                            ret = true;
                       }
                  }
                  return ret;
             }
             
             void Button::paintClicked( BITMAP *window ){
                  draw_sprite( window, this -> pressedIcon , x,y);
                  paintBorder( window );
             }
             
             void Button::paintBack( BITMAP *window ){
                  int cor = backColor -> getColor();
                  rectfill(window,x+borderSize,y+borderSize,x+width-borderSize,y+height-borderSize,cor);
             }
             
             void Button::paintText( BITMAP *window ){
                  int cor = textColor -> getColor();
                  const char *str = text.c_str();
             }
             
             bool Button::isSelected(){
                  return this -> selected;
             }
             
             void Button::setSize( int x1, int y1 ){
                  setBounds( getX(), getY(), x1, y1 );
             }
             
             void Button::setLocation( int x1, int y1 ){
                  setBounds( x1, y1, getWidth(), getHeight() );
             }
