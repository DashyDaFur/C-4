#ifndef JUEGO_HPP_INCLUDED
#define JUEGO_HPP_INCLUDED

// Dimensiones estándar para Conecta 4
int GetBoardRows();
int GetBoardCols();

/**
 * @brief Cuenta fichas consecutivas en una dirección específica desde un punto de inicio.
 *        Adaptado de la lógica original.
 * @param initial_pos Índice 1D de la ficha recién colocada.
 * @param delta_offset Cambio en el índice 1D para moverse en una dirección específica.
 *                     (ej. 1 para horizontal, GetBoardCols() para vertical, etc.)
 * @param player Jugador cuyas fichas se cuentan (1 o 2).
 * @param board Puntero al array del tablero (representación 1D).
 * @return Número de fichas consecutivas encontradas en esa dirección (sin incluir la inicial).
 */
int contar(int initial_pos, int delta_offset, int player, const int* board);

/**
 * @brief Verifica si hay 4 fichas en línea a partir de la última jugada.
 *        Adaptado de la lógica original.
 * @param last_dropped_pos Índice 1D de la última ficha colocada.
 * @param player Jugador que acaba de mover (1 o 2).
 * @param board Puntero al array del tablero (representación 1D).
 * @return true si el jugador ha ganado, false en caso contrario.
 */
bool Cuatro(int last_dropped_pos, int player, const int* board);


#endif // JUEGO_HPP_INCLUDED
