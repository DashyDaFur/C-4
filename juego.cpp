#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "juego.hpp"


using namespace std;

/* ************************************************************************************/

void MostrarTablero(int* &tablero)
{
    cout << "\t";
    for(int i=41;i>-1;i--)
    {
        cout << setw(2) << tablero[i];  // Muestra cada celda del tablero con formato
        if (i%7==0)
        {
            cout << "\n" << "\t";  // Salto de línea al final de cada fila
        }
    }
    cout << "\n";
}

/* ************************************************************************************/


int contar(int columna, int op, int jugador, int* juego)
{
    int conteo = 0;
    int posicion = columna + op;

    while (posicion >= 0 && posicion < 42 && juego[posicion] == jugador)
    {
        // Validar que no se cruce el borde del tablero
        int colActual = columna % 7;
        int colNueva = posicion % 7;

        conteo++;
        posicion += op;  // Avanza en la dirección especificada (op)
    }
    return conteo;
}

/* ************************************************************************************/

bool Cuatro(int columna, int jugador, int* juego)
{
    // Cuenta fichas consecutivas en todas direcciones
    int h  = 1 + contar(columna,  1, jugador, juego) + contar(columna, -1, jugador, juego);  // Horizontal
    int v  = 1 + contar(columna,  7, jugador, juego) + contar(columna, -7, jugador, juego);  // Vertical
    int d1 = 1 + contar(columna,  8, jugador, juego) + contar(columna, -8, jugador, juego);  // Diagonal inf izquierda a sup derecha
    int d2 = 1 + contar(columna,  6, jugador, juego) + contar(columna, -6, jugador, juego);  // Diagonal inf derecha a sup izquierda

    return (h >= 4 || v >= 4 || d1 >= 4 || d2 >= 4);  // Verifica si hay 4 en línea
}

/* ************************************************************************************/

void Caida(int jugador,int columna,int* &tablero,int altura)
{
    int alturaR = 5-altura;  // Calcula la altura relativa
    int* tableroCopia = new int[42];  // Crea copia del tablero para animación

    // Inicializa la copia del tablero
    for (int i=0 ; i<42 ; i++)
    {
        if (i!=columna)
        {
            tableroCopia[i] = tablero[i];
        }
        else
        {
            tableroCopia[i] = 0;  // Limpia la columna para la animación
        }
    }

    // Animación de caída de la ficha

    int alturaTemp = alturaR;

    for (int i=0 ; i<alturaR ; i++)
    {
        system("CLS");

        tableroCopia[columna+(7*alturaTemp)] = jugador;  // Coloca ficha en posición temporal
        MostrarTablero(tableroCopia);
        tableroCopia[columna+(7*alturaTemp)] = 0;  // Limpia posición temporal
        alturaTemp--;
        this_thread::sleep_for(std::chrono::milliseconds(500));  // Pausa para animación
        system("CLS");
    }
}
/* ************************************************************************************/


void Juego()
{
    int opcion=0;
    // Bucle principal del juego (permite jugar múltiples veces)
    do{
        int columna = 0;
        int altura;
        short int jugador = 1;
        int* tablero = new int[42];  // Crea el tablero

        // Inicializa el tablero con ceros
        for (int i=0;i<42;i++)
        {
            tablero[i] = 0;
        }

        //MostrarTablero(tablero);

        cout << "RENGLON  ";
        for(int i=0 ; i<7 ; i++)
        {
            cout << i+1 << " ";  // Muestra números de columnas
        }

        // Bucle de un juego completo
        do{
            jugador = (jugador%2)?1:2;  // Alterna entre jugador 1 y 2
            altura = 0;
            cout << "\n" << setw(10) << "JUGADOR " << jugador;

            cout << "\nEn que columna va a entrar la ficha?";
            cin >> columna;
            columna = 7-columna;  // Convierte entrada a índice interno

            int altura = 0;

            // Encuentra la posición vacía más baja en la columna
            while (tablero[columna]!= 0)
            {
                columna += 7;
                altura++;
            }

            cout << "\n ALTURA" << altura << "\n";
            tablero[columna] = jugador;     // Coloca la ficha del jugador

            //Caida(jugador, columna, juego, altura);  // Muestra animación de caída
            //MostrarTablero(juego);

            // Verifica si hay ganador
            if(Cuatro(columna, jugador, tablero))
            {
                this_thread::sleep_for(std::chrono::milliseconds(2000));
                system("CLS");
                cout << "EL JUGADOR "<<jugador<<" GANO!"<<"\n";
                break;
            }
            jugador++;

        } while(true);

        cout << "\n\250Quiere Jugar otra vez?";

        cout << "\n1)PARA S\241"<<"\n2)PARA NO";
        cin >> opcion;;

    } while(opcion!=0);
}
