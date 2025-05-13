#include "juego.hpp"

// Constantes internas para la lógica del juego
const int BOARD_ROWS_CONNECT4 = 6;
const int BOARD_COLS_CONNECT4 = 7;

// Funciones para acceder a las dimensiones desde otros archivos si es necesario
// (aunque en este caso, Escenas.cpp las define también para su dibujado)
int GetBoardRows()
{
    return BOARD_ROWS_CONNECT4;
}
int GetBoardCols()
{
    return BOARD_COLS_CONNECT4;
}


/**
 * @brief Cuenta las fichas consecutivas de un jugador en una dirección específica desde un punto de inicio.
 * @param r_start Fila inicial.
 * @param c_start Columna inicial.
 * @param dr Delta para la fila (dirección de búsqueda en filas).
 * @param dc Delta para la columna (dirección de búsqueda en columnas).
 * @param player Jugador cuyas fichas se cuentan.
 * @param board Puntero al array del tablero.
 * @return Número de fichas consecutivas encontradas en esa dirección.
 */
int CountLine(int r_start, int c_start, int dr, int dc, int player, const int* board) {
    int count = 0;
    int r = r_start + dr;
    int c = c_start + dc;

    while (r >= 0 && r < BOARD_ROWS_CONNECT4 && c >= 0 && c < BOARD_COLS_CONNECT4 &&
           board[r * BOARD_COLS_CONNECT4 + c] == player) {
        count++;
        r += dr;
        c += dc;
    }
    return count;
}

bool CheckWin(int r_dropped, int c_dropped, int player, const int* board)
{
    // Direcciones: {delta_fila, delta_columna}
    // Horizontal, Vertical, Diagonal (abajo-derecha), Diagonal (arriba-derecha)
    int dr[] = {0, 1, 1,  -1};
    int dc[] = {1, 0, 1,   1};

    for (int i = 0; i < 4; ++i) {
        int count = 1; // Contar la ficha recién colocada
        count += CountLine(r_dropped, c_dropped,  dr[i],  dc[i], player, board); // Contar en una dirección
        count += CountLine(r_dropped, c_dropped, -dr[i], -dc[i], player, board); // Contar en la dirección opuesta
        if (count >= 4) {
            return true;
        }
    }
    return false;
}
