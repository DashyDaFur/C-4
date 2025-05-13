#ifndef JUEGO_HPP_INCLUDED
#define JUEGO_HPP_INCLUDED

/**
 * @brief Muestra el tablero de juego en la consola
 * @param tablero Puntero al array que representa el tablero
 */
void MostrarTablero(int* &tablero);

/**
 * @brief Cuenta fichas consecutivas en una direcci�n espec�fica
 * @param columna Columna donde se coloc� la �ltima ficha
 * @param op Direcci�n a verificar (1: horizontal, 7: vertical, 8: diagonal, etc.)
 * @param jugador Jugador actual (1 o 2)
 * @param juego Puntero al array del tablero
 * @return N�mero de fichas consecutivas encontradas
 */
int contar(int columna, int op, int jugador, int* juego);

/**
 * @brief Verifica si hay 4 fichas en l�nea
 * @param columna Columna donde se coloc� la �ltima ficha
 * @param jugador Jugador actual (1 o 2)
 * @param juego Puntero al array del tablero
 * @return true si hay 4 en l�nea, false en caso contrario
 */
bool Cuatro(int columna, int jugador, int* juego);

/**
 * @brief Simula la animaci�n de ca�da de una ficha
 * @param jugador Jugador actual (1 o 2)
 * @param columna Columna donde se coloca la ficha
 * @param tablero Puntero al array del tablero
 * @param altura Altura donde se colocar� la ficha
 */
void Caida(int jugador, int columna, int* &tablero, int altura);

/**
 * @brief Funci�n principal que maneja el flujo del juego
 * @return 0 al terminar el juego
 */
void Juego();



#endif // JUEGO_HPP_INCLUDED


