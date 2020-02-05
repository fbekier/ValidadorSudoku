/***********************************************************
 
  
 Tomo como ejemplo el sudoku obtenido del link: https://es.wikipedia.org/wiki/Sudoku
  
    5 3 4 6 7 8 9 1 2
    6 7 2 1 9 5 3 4 8
    1 9 8 3 4 2 5 6 7
    8 5 9 7 6 1 4 2 3
    4 2 6 8 5 3 7 9 1
    7 1 3 9 2 4 8 5 6
    9 6 1 5 3 7 2 8 4
    2 8 7 4 1 9 6 3 5
    3 4 5 2 8 6 1 7 9
 ************************************************************/

#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#define LONG_TABLERO 9      //Longitud del tablero (9x9)
#define LONG_REGION 3       //Longitud de región (3x3)
#define CANT_REGIONES 9     //Cantidad de Regiones
#define CANT_PIEZAS 81      //Cantidad de Celdas

using namespace std;

struct coord
{
    int fila;
    int col;
};

//Enumero tipos de Validacion
enum T_Validacion {fila, columna, region};

class Tablero{

private:
    int _tablero[9][9];
    int _contCeldasLlenas;
    coord _inicioRegion[9]; //vector que indica las coordenadas de inicio de cada región. Ejemplo [0,0],[0,3],[0,6]
public:

    Tablero();
    ~Tablero();
    void iniciar();
    void validar();
    void setRegion(int f, int c, int &numRegion);

    bool cargarTablero();
    bool esCompleto();
    bool buscarNumero(int num, int fila, T_Validacion tipo);
    bool validarPorTipo(T_Validacion tipo);
    bool validarRegiones();
    bool validarRegion(int numRegion);
    
};

#endif