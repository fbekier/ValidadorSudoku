/***********************************************************************************
Programa: Validador de Sudoku
Descripción: Dado un tablero completo de Sudoku, se realiza la validación del mismo,
verificando que no haya números repetidos (entre el 1 el 9) en ninguna fila, columna
y cuadrante.
/***********************************************************************************/

#include <iostream>
#include "tablero.h"

using namespace std;

int main()
{

   Tablero *tablero;
    tablero = new Tablero;
	if (tablero)
		tablero->iniciar();
	if (tablero)
	{
		delete tablero;
		tablero = NULL;
	}
		 

}