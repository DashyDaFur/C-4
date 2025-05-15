#include "juego.hpp"
#include <iostream> // Temporal para depuración si es necesario, quitar en producción

// Constantes internas para la lógica del juego
const int BOARD_ROWS_CONNECT4 = 6;
const int BOARD_COLS_CONNECT4 = 7;

int GetBoardRows() { return BOARD_ROWS_CONNECT4; }
int GetBoardCols() { return BOARD_COLS_CONNECT4; }


// Adaptación de la función 'contar' original
// initial_pos: índice 1D de la ficha recién colocada
// delta_offset: cómo cambia el índice para moverse en una dirección
//              (e.g., 1 para derecha, -1 para izquierda, BOARD_COLS_CONNECT4 para abajo, etc.)
// player: el jugador actual (1 o 2)
// board: el tablero 1D
int contar(int initial_pos, int delta_offset, int player, const int* board)
{
    int count = 0;
    int current_pos = initial_pos + delta_offset; // Empezar a verificar desde la siguiente casilla en la dirección

    int num_rows = GetBoardRows();
    int num_cols = GetBoardCols();
    int total_cells = num_rows * num_cols;

    // Bucle para contar en la dirección dada
    while (true) {
        // Comprobaciones de límites del tablero
        if (current_pos < 0 || current_pos >= total_cells) { // Fuera de los límites verticales/generales
            break;
        }

        // Comprobación de cruce de bordes horizontales para movimientos no verticales
        // Si el movimiento es horizontal o diagonal, no debe "saltar" de un lado al otro del tablero.
        if (delta_offset == 1 || delta_offset == -1 || // Movimientos estrictamente horizontales
            delta_offset == (num_cols + 1) || delta_offset == (num_cols - 1) || // Diagonales hacia abajo
            delta_offset == -(num_cols + 1) || delta_offset == -(num_cols - 1)) { // Diagonales hacia arriba

            int prev_col = (current_pos - delta_offset) % num_cols;
            int current_col = current_pos % num_cols;

            // Si delta_offset es 1 (derecha), la col actual no debe ser 0 a menos que la anterior fuera num_cols-1 (esto es un error de lógica, debería ser más simple)
            // Simplificación: Si el delta te lleva a la columna 0 desde una columna != num_cols-1 y el delta es hacia la derecha, es un cruce.
            // O si te lleva a la columna num_cols-1 desde una columna != 0 y el delta es hacia la izquierda.
            if ( (delta_offset == 1 || delta_offset == (num_cols + 1) || delta_offset == -(num_cols - 1)) && current_col == 0 && prev_col != num_cols-1 ) break; // Cruzó de derecha a izquierda
            if ( (delta_offset == -1 || delta_offset == (num_cols - 1) || delta_offset == -(num_cols + 1)) && current_col == num_cols-1 && prev_col != 0) break; // Cruzó de izquierda a derecha
        }


        if (board[current_pos] == player) {
            count++;
            current_pos += delta_offset; // Mover a la siguiente posición en la misma dirección
        } else {
            break; // No es ficha del jugador, o está vacía
        }
    }
    return count;
}


// Adaptación de la función 'Cuatro' original
// last_dropped_pos: índice 1D de la última ficha colocada.
// player: el jugador actual (1 o 2)
// board: el tablero 1D
bool Cuatro(int last_dropped_pos, int player, const int* board) {
    int num_cols = GetBoardCols();

    // Offsets para las direcciones:
    // Horizontal: <- (-1), -> (1)
    // Vertical:   ^ (-num_cols), v (num_cols)
    // Diagonal 1 (\): Noroeste (-num_cols-1) a Sureste (num_cols+1)
    // Diagonal 2 (/): Suroeste (num_cols-1) a Noreste (-num_cols+1)

    // Horizontal
    int h_count = 1 + contar(last_dropped_pos, 1, player, board) + contar(last_dropped_pos, -1, player, board);
    if (h_count >= 4) return true;

    // Vertical
    int v_count = 1 + contar(last_dropped_pos, num_cols, player, board) + contar(last_dropped_pos, -num_cols, player, board);
    if (v_count >= 4) return true;

    // Diagonal \ (NO a SE)
    int d1_count = 1 + contar(last_dropped_pos, num_cols + 1, player, board) + contar(last_dropped_pos, -(num_cols + 1), player, board);
    if (d1_count >= 4) return true;

    // Diagonal / (SO a NE)
    int d2_count = 1 + contar(last_dropped_pos, num_cols - 1, player, board) + contar(last_dropped_pos, -(num_cols - 1), player, board);
    if (d2_count >= 4) return true;

    return false;
}
