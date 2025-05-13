#ifndef JUEGO_HPP_INCLUDED
#define JUEGO_HPP_INCLUDED

/**
 * @brief Muestra el tablero de juego en la consola
 * @param tablero Puntero al array que representa el tablero
 */
void MostrarTablero(int* &tablero);

/**
 * @brief Cuenta fichas consecutivas en una dirección específica
 * @param columna Columna donde se colocó la última ficha
 * @param op Dirección a verificar (1: horizontal, 7: vertical, 8: diagonal, etc.)
 * @param jugador Jugador actual (1 o 2)
 * @param juego Puntero al array del tablero
 * @return Número de fichas consecutivas encontradas
 */
int contar(int columna, int op, int jugador, int* juego);

/**
 * @brief Verifica si hay 4 fichas en línea
 * @param columna Columna donde se colocó la última ficha
 * @param jugador Jugador actual (1 o 2)
 * @param juego Puntero al array del tablero
 * @return true si hay 4 en línea, false en caso contrario
 */
bool Cuatro(int columna, int jugador, int* juego);

/**
 * @brief Simula la animación de caída de una ficha
 * @param jugador Jugador actual (1 o 2)
 * @param columna Columna donde se coloca la ficha
 * @param tablero Puntero al array del tablero
 * @param altura Altura donde se colocará la ficha
 */
void Caida(int jugador, int columna, int* &tablero, int altura);

/**
 * @brief Función principal que maneja el flujo del juego
 * @return 0 al terminar el juego
 */
void Juego();



#endif // JUEGO_HPP_INCLUDED


