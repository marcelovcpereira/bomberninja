#ifndef BUTTON_H
#define BUTTON_H


#include <allegro.h>
#include <string>

#include "color.h"

using namespace std;

/* Classe que representa um botao clic�vel */
class Button{

      private:
              int x;                //posi��o x do bot�o
              int y;                //posi��o y do bot�o
              int width;            //largura do bot�o
              int height;           //altura do bot�o
              string text;          //texto do bot�o
              Color *backColor;     //cor do fundo do bot�o
              Color *borderColor;   //cor da borda do bot�o
              Color *textColor;     //cor da string do Texto
              int borderSize;       // espessura da borda
              BITMAP *normalIcon;   // �cone normal do bot�o
              BITMAP *pressedIcon;  //�cone do bot�o presionado
              bool clicked;         //verifica se o bot�o foi clicado
              bool selected;        //verifica se o bot�o esta selecionado
      public:
             /* Construtor Default */
             Button();
             
             /* Construtor que recebe o texto do Bot�o */
             Button( string s );
             
             /* Construtor de c�pia */
             Button( Button *b );
             
             /* Inicializa os atributos com valores default */
             void getDefaultInitialize();
             
             /* Retorna a posi��o X do bot�o */
             int getX();
             
             /* Ajusta a localiza��o X,Y e as dimens�es W,H */
             void setBounds( int x, int y, int w, int h );
             
             /* Ajusta a posi��o X do Bot�o */
             void setX( int x1 );
             
             /* Retorna o BITMAP que representa o botao NORMAL */
             BITMAP *getNormalIcon();
             
             /* Ajusta o BITMAP que representa o botao NORMAL */
             void setNormalIcon( BITMAP *img );
             
             /* Retorna o BITMAP que representa o botao PRESSIONADO */
             BITMAP *getPressedIcon();
             
             /* Ajusta o BITMAP que representa o botao PRESSIONADO */
             void setPressedIcon( BITMAP *img );
             
             
             //caramba... muita coisa, desisto de comentar!
              int getY();
              
              void setY( int y1 );
              
              int getWidth();
              
              void setWidth( int w );
              
              int getHeight();
              
              void setHeight( int h );
              
              bool getSelected();
              
              void setSelected( bool b );
              
              bool getClicked();
              
              void setClicked( bool b );
              
              string getText();
              
              void setText( string s );
              
              Color *getBackColor();
              
              void setBackColor( Color *c );
              
              Color *getBorderColor();
              
              void setBorderColor( Color *c );
              
              Color *getTextColor();
              
              void setTextColor( Color *c );
              
              int getBorderSize();
              
              void setBorderSize( int b );
              
              void paint( BITMAP *window );
              
              void paintBorder( BITMAP *window );
              
              bool wasClicked( int xM, int yM );
              
              void paintClicked( BITMAP *window );
              
              void paintBack( BITMAP *window );
              
              void paintText( BITMAP *window );
              
              bool isSelected();
              
              void setSize( int x1, int y1 );
              
              void setLocation( int x1, int y1 );
              
};
#endif