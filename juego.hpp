#ifndef JUEGO_HPP_INCLUDED
#define JUEGO_HPP_INCLUDED

// Dimensiones est�ndar para Conecta 4
int GetBoardRows();
int GetBoardCols();

/**
 * @brief Cuenta fichas consecutivas en una direcci�n espec�fica desde un punto de inicio.
 *        Adaptado de la l�gica original.
 * @param initial_pos �ndice 1D de la ficha reci�n colocada.
 * @param delta_offset Cambio en el �ndice 1D para moverse en una direcci�n espec�fica.
 *                     (ej. 1 para horizontal, GetBoardCols() para vertical, etc.)
 * @param player Jugador cuyas fichas se cuentan (1 o 2).
 * @param board Puntero al array del tablero (representaci�n 1D).
 * @return N�mero de fichas consecutivas encontradas en esa direcci�n (sin incluir la inicial).
 */
int contar(int initial_pos, int delta_offset, int player, const int* board);

/**
 * @brief Verifica si hay 4 fichas en l�nea a partir de la �ltima jugada.
 *        Adaptado de la l�gica original.
 * @param last_dropped_pos �ndice 1D de la �ltima ficha colocada.
 * @param player Jugador que acaba de mover (1 o 2).
 * @param board Puntero al array del tablero (representaci�n 1D).
 * @return true si el jugador ha ganado, false en caso contrario.
 */
bool Cuatro(int last_dropped_pos, int player, const int* board);


#endif // JUEGO_HPP_INCLUDED
