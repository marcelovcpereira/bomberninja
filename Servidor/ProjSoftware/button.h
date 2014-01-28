#ifndef BUTTON_H
#define BUTTON_H


#include <allegro.h>
#include <string>

#include "color.h"

using namespace std;

/* Classe que representa um botao clicável */
class Button{

      private:
              int x;                //posição x do botão
              int y;                //posição y do botão
              int width;            //largura do botão
              int height;           //altura do botão
              string text;          //texto do botão
              Color *backColor;     //cor do fundo do botão
              Color *borderColor;   //cor da borda do botão
              Color *textColor;     //cor da string do Texto
              int borderSize;       // espessura da borda
              BITMAP *normalIcon;   // ícone normal do botão
              BITMAP *pressedIcon;  //ícone do botão presionado
              bool clicked;         //verifica se o botão foi clicado
              bool selected;        //verifica se o botão esta selecionado
      public:
             /* Construtor Default */
             Button();
             
             /* Construtor que recebe o texto do Botão */
             Button( string s );
             
             /* Construtor de cópia */
             Button( Button *b );
             
             /* Inicializa os atributos com valores default */
             void getDefaultInitialize();
             
             /* Retorna a posição X do botão */
             int getX();
             
             /* Ajusta a localização X,Y e as dimensões W,H */
             void setBounds( int x, int y, int w, int h );
             
             /* Ajusta a posição X do Botão */
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