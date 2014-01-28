#ifndef COLOR_H
#define COLOR_H


/*
 * Definição da Classe COLOR
 */
class Color{
      private:
              int red;      //quantidade de cor vermelha
              int green;    //quantidade de cor verde
              int blue;     //quantidade de cor azul 
      public:
             /* Construtor Default */
             Color(); 
             
             /*
              * Construtor que recebe os valores de
              * vermelho, verde e azul da "Color"
              */
             Color( int r, int g, int b );
             
             /*
              * Construtor de cópias
              */
             Color( Color *c );
             
             /*
              * Retorna a quantidade de vermelho da "Color"
              */
             int getRed();
             
             /*
              * Retorna a quantidade de verde da "Color"
              */
             int getGreen();
             
             /*
              * Retorna a quantidade de azul da "Color"
              */
             int getBlue();
             
             /*
              * Ajusta a quantidade de vermelho da "Color"
              */
             void setRed( int r );
             
              /*
              * Ajusta a quantidade de verde da "Color"
              */
             void setGreen( int g );
             
             /*
              * Ajusta a quantidade de azul da "Color"
              */
             void setBlue( int b );
             
             /*
              * Retorna o valor inteiro da cor, a partir da
              * combinação dos valores de R, G e B
              */
             int getColor();
};

#endif
