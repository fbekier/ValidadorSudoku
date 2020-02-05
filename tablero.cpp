#include "tablero.h"


Tablero::Tablero()
{
    _contCeldasLlenas = 0;
    
    int f=0;
    int c=0;

    int numRegion = 0;
    
    //Inicializo todas las celdas del tablero en 0
    while (f < LONG_TABLERO)
    {
        while (c < LONG_TABLERO)
        {
            _tablero[f][c] = 0;
            setRegion(f, c, numRegion);
            c++;
        }
        c = 0;
        f++;
    }
    
}

Tablero::~Tablero()
{

}
 //Dadas unas coordenadas de filas y columnas, si indican el inicio de una región (ejemplo  [0,0] o [3,3]) las asigna al vector de regiones
void Tablero::setRegion(int f, int c, int & numRegion)
{
    if (f % LONG_REGION == 0 && c % LONG_REGION == 0) //Si la fila y la columna es divisible por 3, estas coordenadas indican el inicio de una región
    {
        _inicioRegion[numRegion].fila = f;
        _inicioRegion[numRegion].col = c;
        numRegion ++;
    }
}

void Tablero::iniciar()
{
    bool cargaOk = true;
    cout << "Cargando matriz desde el archivo sudoku.txt" << endl << endl;
    cargaOk = cargarTablero();
    
    if (cargaOk)
    {
        cout << endl << endl << "Validando datos ..." <<endl << endl;
        validar();
    }
    
}


/*
Levanta la matriz desde un archivo .txt, verificando:
 -que todos los caracteres sean entre 1 y 9
 -que no haya caracteres de más ni de menos.
 Devuelve True si la carga se realizó correctamente
*/
bool Tablero::cargarTablero()
{
    bool cargaCorrecta = true;
    bool hayCeldaIncorrecta = false;
    try
    {

        //Cargo el archivo de input en la matriz
        FILE * pArchivo = NULL;
        pArchivo = fopen("sudoku.txt", "r");

        char celda = ' ';
        int f = 0;
        int c = 0;
        int numCelda = 0;

        if (pArchivo != NULL)
        {
            while (!feof(pArchivo) && !hayCeldaIncorrecta && _contCeldasLlenas < CANT_PIEZAS)
            {
                fread(&celda, sizeof(char), 1, pArchivo); //el valor de celda viene en ASCII
                numCelda = celda - 48; //En ASCII el 0 es 48, por lo tanto para convertir de código ascii al valor decimal se hace esta resta.
                cout << celda;
                if (celda == ' ') //Si es un espacio en blanco sólo vuelvo a leer el siguiente caracter
                {
                    continue;
                } 
                else if (celda == '\n') //Si hay salto de línea en el archivo, avanzo a la primer posición de la siguiente fila
                {

                    f++;
                    c = 0;
                    continue;
                } 
                else if (numCelda > 0 && numCelda < 10 &&  //verifico que el contenido de la celda sea entre 1 y 9 inclusive y asigno a la matriz
                        f >= 0 && f <= 8 &&  //Verifico que el rango de la matriz sea correcto (para casos donde el archivo tiene, por ejemplo, filas o columnas demás)
                        c >= 0 && c <= 8 ) 
                {
                    _tablero[f][c] = numCelda;
                    c++;
                    _contCeldasLlenas++;
                }
                else //casos de errores
                {
                    cout << endl << endl;
                    hayCeldaIncorrecta = true;
                    if (c > 8 || f > 8)
                    {
                        cout << "Error: hay un caracter fuera del rango de la matriz o algun espacio en blanco. Finalizara el programa" << endl;         
                    }
                    else if(numCelda < 1 || numCelda > 9)
                    {
                        cout << "Error: los caracteres deben ser numericos entre 1 y 9. Revisar la posicion: " << f << "-" << c << ". Finalizara el programa" << endl;         
                    }
                    else
                    {
                        cout << "Error: Es posible que el tablero no haya sido completado en sus 81 posiciones. Revise que no haya espacios en blanco o caracteres fuera del rango numerico 1-9" << endl;         
                    }
                    
                    cargaCorrecta = false;
                    cin.get();
                }
                
            }    
        }
        
        fclose(pArchivo);

        if(pArchivo)
        {
            delete pArchivo;
            pArchivo = NULL;
        }
        else
        {
            cout << "No se encuentra el archivo sudoku.txt" << endl;
            cin.get();
            cargaCorrecta = false;
        }
        
    }
    catch(exception)
    {
        cargaCorrecta = false;
        cout << "Error cargando archivo sudoku.txt" <<endl;
        cin.get();
    }

    return cargaCorrecta;
}

/*
Recibe un número a buscar, el índice de la fila,columna o región a validar y el tipo de validacion (por fila, columna o region)
Devuelve True si lo encontró
*/
bool Tablero::buscarNumero(int num, int indice, T_Validacion tipo)
{
    bool bEncontrado = false;
    
    if (tipo == T_Validacion::fila)
    {
        int col = 0;
        while (col < LONG_TABLERO && !bEncontrado)
        {
            if (num == _tablero[indice][col])
            {
                bEncontrado = true;
            }
            col ++;
        }
    }
    else if (tipo == T_Validacion::columna)
    {
        int fila = 0;
        while (fila < LONG_TABLERO && !bEncontrado)
        {
            if (num == _tablero[fila][indice])
            {
                bEncontrado = true;
            }
            fila ++;
        }
    }
    else //validación por Region
    {
        int f = _inicioRegion[indice].fila;
        int c = _inicioRegion[indice].col;

        int fTope = f + LONG_REGION;
        int cTope = c + LONG_REGION;
        
        while (f < fTope)
        {
            while (c < cTope)
            {
                if (num == _tablero[f][c])
                {
                    bEncontrado = true;
                }
                c++;
            }
            c = _inicioRegion[indice].col;
            f++;
        }
    }
    
    return bEncontrado;

}

/*
Recibe el tipo de validación a realizar (por fila, columna o región)
Devuelve true si no hay números repetidos
*/
bool Tablero::validarPorTipo(T_Validacion tipo)
{
    int iIndice = 0;

    int numBuscado = 1;
    bool bEncontrado = true;

    while (iIndice < LONG_TABLERO && bEncontrado) 
    {
        while (numBuscado <= LONG_TABLERO && bEncontrado)
        {
            if (!buscarNumero(numBuscado, iIndice, tipo))
            {
                bEncontrado = false;
            }

            numBuscado ++;
        }
        numBuscado = 1;
        iIndice++;
    }
    return bEncontrado;
}

/*
Si el tablero está completo en sus 81 posiciones procede a su validación
*/
void Tablero::validar()
{
    if (esCompleto())
    {
        if(validarPorTipo(T_Validacion::fila) && validarPorTipo(T_Validacion::columna) && validarPorTipo(T_Validacion::region))
        {
            cout << "SUDOKU COMPLETADO CORRECTAMENTE!" <<endl;
        }
        else
        {
            cout << "HAY NUMEROS REPETIDOS!"<< endl;
        }
        
    }
    else
    {
        cout << "El tablero esta incompleto y no se procedera a su validacion" << endl;
    }
    cin.get();
}

//Devuelve true si las 81 celdas del tablero están completas
bool Tablero::esCompleto()
{
    if (_contCeldasLlenas == CANT_PIEZAS)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
