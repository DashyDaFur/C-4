#ifndef JUEGO_HPP_INCLUDED
#define JUEGO_HPP_INCLUDED

// Dimensiones estándar para Conecta 4
int GetBoardRows(); // MODIFICADO: quitado const
int GetBoardCols(); // MODIFICADO: quitado const

/**
 * @brief Verifica si el jugador actual ha ganado después de colocar una ficha en (r_dropped, c_dropped).
 * @param r_dropped Fila donde se colocó la última ficha (0-indexed desde arriba).
 * @param c_dropped Columna donde se colocó la última ficha (0-indexed desde la izquierda).
 * @param player El jugador que acaba de mover (1 o 2).
 * @param board Puntero al array del tablero (representación 1D, row-major).
 * @return true si el jugador ha ganado, false en caso contrario.
 */
bool CheckWin(int r_dropped, int c_dropped, int player, const int* board);

#endif // JUEGO_HPP_INCLUDED
