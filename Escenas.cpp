#include "raylib.h"
#include <cstring> // strcpy y memset
#include <string>  // std::string y std::to_string
#include "Escenas.hpp"
#include "juego.hpp"

#define MAX_NAME_LENGTH 13

// Texturas globales de main.cpp
extern Texture2D FichaRoja;
extern Texture2D FichaAmarilla;
extern Texture2D Controles;
extern Texture2D Fondo;

// Constantes de la pantalla
const int screenWidth = 1000;
const int screenHeight = 650;

// Constantes del tablero de Conecta 4
const int BOARD_GAME_ROWS = 6;
const int BOARD_GAME_COLS = 7;
const float CELL_SIZE = 70.0f;
const float TOKEN_RADIUS = CELL_SIZE / 2 * 0.85f;
const float BOARD_OFFSET_X = (screenWidth - (BOARD_GAME_COLS * CELL_SIZE) - 250) / 2;
const float BOARD_OFFSET_Y = 70.0f;
const Color BOARD_COLOR = {20, 60, 180, 255};
const Color EMPTY_CELL_COLOR = {5, 10, 90, 255};

// Estado del juego
int board[BOARD_GAME_ROWS * BOARD_GAME_COLS];
int currentPlayer;
bool gameOver;
int winner;
int hoverColumn; // Para el feedback visual del ratón (opcional, se podría quitar)
int selectedColumnKeyboard; // Columna seleccionada por el teclado
char jugador1NombreGlobal[MAX_NAME_LENGTH + 1];
char jugador2NombreGlobal[MAX_NAME_LENGTH + 1];

/*********************************************************************************/

void ResetGame()
{
    for (int i = 0; i < BOARD_GAME_ROWS * BOARD_GAME_COLS; ++i) {
        board[i] = 0;
    }
    currentPlayer = 1;
    gameOver = false;
    winner = 0;
    hoverColumn = -1; // O inicializar a 0 si se prefiere
    selectedColumnKeyboard = BOARD_GAME_COLS / 2; // Empezar en el centro con el teclado
}

/*********************************************************************************/

bool DropPiece(int col, int player)
{
    if (col < 0 || col >= BOARD_GAME_COLS) return false;

    for (int r = BOARD_GAME_ROWS - 1; r >= 0; --r)
    {
        if (board[r * BOARD_GAME_COLS + col] == 0)
        {
            int dropped_pos_1d = r * BOARD_GAME_COLS + col;
            board[dropped_pos_1d] = player;

            if (Cuatro(dropped_pos_1d, player, board))
            {
                gameOver = true;
                winner = player;
            }
            else {
                bool full = true;
                for (int i = 0; i < BOARD_GAME_ROWS * BOARD_GAME_COLS; ++i)
                {
                    if (board[i] == 0) {
                        full = false;
                        break;
                    }
                }
                if (full)
                {
                    gameOver = true;
                    winner = 3; // Empate
                }
            }
            return true;
        }
    }
    return false;
}

/*********************************************************************************/

void DrawBoard() {
    for (int r = 0; r < BOARD_GAME_ROWS; ++r)
    {
        for (int c = 0; c < BOARD_GAME_COLS; ++c)
        {
            Rectangle cellRect =
            {
                BOARD_OFFSET_X + c * CELL_SIZE,
                BOARD_OFFSET_Y + r * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE*1.4
            };
            DrawRectangleRec(cellRect, BOARD_COLOR);
            DrawCircle
            (
                BOARD_OFFSET_X + c * CELL_SIZE + CELL_SIZE / 2,
                BOARD_OFFSET_Y + r * CELL_SIZE + CELL_SIZE / 2,
                TOKEN_RADIUS,
                EMPTY_CELL_COLOR
            );
        }
    }
}

/*********************************************************************************/

void DrawPieces()
{
    for (int r = 0; r < BOARD_GAME_ROWS; ++r)
    {
        for (int c = 0; c < BOARD_GAME_COLS; ++c)
        {
            int piece = board[r * BOARD_GAME_COLS + c];

            if (piece != 0)
            {
                Texture2D currentTokenTexture = (piece == 1) ? FichaRoja : FichaAmarilla;
                float scale = (TOKEN_RADIUS * 3.5) / currentTokenTexture.width;

                DrawTextureEx
                (
                    currentTokenTexture,
                    { BOARD_OFFSET_X + c * CELL_SIZE + (CELL_SIZE - currentTokenTexture.width * scale) / 2,
                      BOARD_OFFSET_Y + r * CELL_SIZE + (CELL_SIZE - currentTokenTexture.height * scale) / 2 },
                    0.0f, // rotación
                    scale, // escala
                    WHITE // color
                );
            }
        } // BOARD_GAME_COLS
    } // BOARD_GAME_ROWS
}

/*********************************************************************************/

// Modificado para usar selectedColumnKeyboard para la ficha principal "fantasma"
// y hoverColumn para un feedback visual secundario del ratón si se desea.
void DrawHoverAndSelectedPiece()
{
    int columnToDrawPreview = -1;

    if (!gameOver)
    {
        columnToDrawPreview = selectedColumnKeyboard; // Prioridad al teclado
    }

    // Dibujar la ficha de previsualización seleccionada por teclado
    if (columnToDrawPreview != -1)
    {
        Texture2D currentTokenTexture = (currentPlayer == 1) ? FichaRoja : FichaAmarilla;
        float scale = (TOKEN_RADIUS * 2) / currentTokenTexture.width;

        DrawTextureEx
        (
            currentTokenTexture,
            { BOARD_OFFSET_X + columnToDrawPreview * CELL_SIZE + (CELL_SIZE - currentTokenTexture.width * scale) / 2,
              BOARD_OFFSET_Y - CELL_SIZE + (CELL_SIZE - currentTokenTexture.height * scale) / 2 },
            0.0f,
            scale,
            WHITE // Ficha sólida para la selección por teclado
        );
    }

    // Opcional: Dibujar una ficha "fantasma" más tenue para el hover del ratón, si es diferente de la selección del teclado
    if (!gameOver && hoverColumn != -1 && hoverColumn != selectedColumnKeyboard)
    {
        Texture2D currentTokenTextureMouse = (currentPlayer == 1) ? FichaRoja : FichaAmarilla;
        float scaleMouse = (TOKEN_RADIUS * 2) / currentTokenTextureMouse.width;

        DrawTextureEx
        (
            currentTokenTextureMouse,
            { BOARD_OFFSET_X + hoverColumn * CELL_SIZE + (CELL_SIZE - currentTokenTextureMouse.width * scaleMouse) / 2,
              BOARD_OFFSET_Y - CELL_SIZE + (CELL_SIZE - currentTokenTextureMouse.height * scaleMouse) / 2 },
            0.0f,
            scaleMouse,
            Fade(WHITE, 0.5f) // Semi-transparente para el hover del ratón
        );
    }
}

/*********************************************************************************/

bool EscenaNombre(char* p1NameDest, char* p2NameDest)
{
    p1NameDest[0] = '\0';
    p2NameDest[0] = '\0';
    int p1LetterCount = 0;
    int p2LetterCount = 0;
    int activePlayerInput = 1;
    bool namesConfirmed = false;
    bool firstFrameDone = false;

    Rectangle p1TextBox = { (float)screenWidth/2 - 100, 230, 200, 40 };
    Rectangle p2TextBox = { (float)screenWidth/2 - 100, 330, 200, 40 };

    while (!WindowShouldClose() && !namesConfirmed)
    {
        char* currentNameBuffer = (activePlayerInput == 1) ? p1NameDest : p2NameDest;
        int* currentLetterCount = (activePlayerInput == 1) ? &p1LetterCount : &p2LetterCount;

        int unicodeKey = GetCharPressed();
        while(unicodeKey > 0)
        {
            if((unicodeKey >= 32) && (unicodeKey <= 125) && (*currentLetterCount < MAX_NAME_LENGTH))
            {
                currentNameBuffer[*currentLetterCount] = (char)unicodeKey;
                currentNameBuffer[*currentLetterCount + 1] = '\0';
                (*currentLetterCount)++;
            }
            unicodeKey = GetCharPressed();
        }

        if(IsKeyPressed(KEY_BACKSPACE))
        {
            if (*currentLetterCount > 0)
            {
                (*currentLetterCount)--;
                currentNameBuffer[*currentLetterCount] = '\0';
            }
        }
        if(firstFrameDone)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                if(activePlayerInput == 1){
                    if (p1LetterCount == 0) strcpy(p1NameDest, "Jugador 1");
                    activePlayerInput = 2;
                } else {
                    if (p2LetterCount == 0) strcpy(p2NameDest, "Jugador 2");
                    namesConfirmed = true;
                }
            }

            if (IsKeyPressed(KEY_TAB))
            {
                if (activePlayerInput == 1) activePlayerInput = 2;
                else activePlayerInput = 1;
            }
        }

        if (IsKeyPressed(KEY_ESCAPE)) return false;

        BeginDrawing();
            DrawTextureEx(Fondo, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);
            DrawText("Conecta 4", screenWidth / 2 - MeasureText("Conecta 4", 40) / 2, 60, 40, RAYWHITE);
            DrawText("Introduce los nombres de los jugadores:", screenWidth / 2 - MeasureText("Introduce los nombres de los jugadores:", 20) / 2, 130, 20, RAYWHITE);
            DrawText("Jugador 1:", p1TextBox.x, p1TextBox.y - 25, 20, RAYWHITE);
            DrawRectangleRec(p1TextBox, LIGHTGRAY);
            if (activePlayerInput == 1) DrawRectangleLinesEx(p1TextBox, 2, YELLOW);
            else DrawRectangleLinesEx(p1TextBox, 1, DARKGRAY);
            DrawText(p1NameDest, (int)p1TextBox.x + 10, (int)p1TextBox.y + 10, 20, BLACK);
            if (activePlayerInput == 1 && (p1LetterCount < MAX_NAME_LENGTH))
            {
                if (((int)(GetTime()*2.5f))%2 == 0)
                    DrawText("_", (int)p1TextBox.x + 10 + MeasureText(p1NameDest, 20), (int)p1TextBox.y + 12, 20, BLACK);
            }
            DrawText("Jugador 2:", p2TextBox.x, p2TextBox.y - 25, 20, RAYWHITE);
            DrawRectangleRec(p2TextBox, LIGHTGRAY);
            if (activePlayerInput == 2) DrawRectangleLinesEx(p2TextBox, 2, YELLOW);
            else DrawRectangleLinesEx(p2TextBox, 1, DARKGRAY);
            DrawText(p2NameDest, (int)p2TextBox.x + 10, (int)p2TextBox.y + 10, 20, BLACK);
            if (activePlayerInput == 2 && (p2LetterCount < MAX_NAME_LENGTH))
            {
                if (((int)(GetTime()*2.5f))%2 == 0)
                    DrawText("_", (int)p2TextBox.x + 10 + MeasureText(p2NameDest, 20), (int)p2TextBox.y + 12, 20, BLACK);
            }
            float helpTextY = screenHeight - 100;
            DrawText("Presiona ENTER para confirmar nombre / continuar.", screenWidth / 2 - MeasureText("Presiona ENTER para confirmar nombre / continuar.", 18) / 2, helpTextY, 18, RAYWHITE);
            helpTextY += 25;
            DrawText("Presiona TAB para cambiar de jugador.", screenWidth / 2 - MeasureText("Presiona TAB para cambiar de jugador.", 18) / 2, helpTextY, 18, RAYWHITE);
            helpTextY += 25;
            DrawText("Presiona ESC para volver al menú principal.", screenWidth / 2 - MeasureText("Presiona ESC para volver al menú principal.", 18) / 2, helpTextY, 18, RAYWHITE);
        EndDrawing();
        if(!firstFrameDone) firstFrameDone = true;
    }
    return true;
}

/*********************************************************************************/

void EscenaJuego()
{
    if (!EscenaNombre(jugador1NombreGlobal, jugador2NombreGlobal)) return;

    ResetGame();
    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose()) {
        // --- Lógica de Actualización ---
        Vector2 mousePos = GetMousePosition();
        hoverColumn = -1; // Resetear columna de hover del ratón

        if (!gameOver) {
            // Feedback visual del ratón (opcional)
            if (mousePos.x >= BOARD_OFFSET_X && mousePos.x < BOARD_OFFSET_X + BOARD_GAME_COLS * CELL_SIZE &&
                mousePos.y >= BOARD_OFFSET_Y - CELL_SIZE && mousePos.y < BOARD_OFFSET_Y + BOARD_GAME_ROWS * CELL_SIZE) {
                hoverColumn = (int)((mousePos.x - BOARD_OFFSET_X) / CELL_SIZE);
            }

            // Control por teclado
            if (IsKeyPressed(KEY_RIGHT)) {
                selectedColumnKeyboard = (selectedColumnKeyboard + 1) % BOARD_GAME_COLS;
            }
            if (IsKeyPressed(KEY_LEFT)) {
                selectedColumnKeyboard--;
                if (selectedColumnKeyboard < 0) {
                    selectedColumnKeyboard = BOARD_GAME_COLS - 1;
                }
            }

            // Soltar ficha con Enter o Flecha Abajo (usando selectedColumnKeyboard)
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_DOWN)) {
                if (DropPiece(selectedColumnKeyboard, currentPlayer)) {
                    if (!gameOver) {
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    }
                }
            }
            // Opcional: Mantener la posibilidad de soltar con el ratón si hoverColumn es válido
            // y no se ha usado el teclado recientemente (esto puede complicar la UX, considera si lo quieres)
            /*
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverColumn != -1) {
                if (DropPiece(hoverColumn, currentPlayer)) { // Usar hoverColumn para el clic del ratón
                    if (!gameOver) {
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                        selectedColumnKeyboard = hoverColumn; // Sincronizar la selección del teclado con el último clic del ratón
                    }
                }
            }
            */
        }

        if (IsKeyPressed(KEY_R)) {
            ResetGame();
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
             break;
        }

        // --- Dibujado ---
        BeginDrawing();
        DrawTextureEx(Fondo, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);

        DrawBoard();
        DrawPieces();
        DrawHoverAndSelectedPiece(); // MODIFICADO para dibujar la pieza seleccionada por teclado y opcionalmente la de hover del ratón

        // --- UI: Información del Juego ---
        float uiPanelX = BOARD_OFFSET_X + BOARD_GAME_COLS * CELL_SIZE + 20;
        float uiPanelY = BOARD_OFFSET_Y;

        DrawText(jugador1NombreGlobal, uiPanelX, uiPanelY, 20, RAYWHITE);
        DrawTextureEx(FichaRoja, {uiPanelX + MeasureText(jugador1NombreGlobal, 20) + 10, uiPanelY - 5}, 0.0f, TOKEN_RADIUS*2 / FichaRoja.height *0.5f, WHITE);
        DrawText(jugador2NombreGlobal, uiPanelX, uiPanelY + 30, 20, RAYWHITE);
        DrawTextureEx(FichaAmarilla, {uiPanelX + MeasureText(jugador2NombreGlobal, 20) + 10, uiPanelY + 25}, 0.0f, TOKEN_RADIUS*2 / FichaAmarilla.height * 0.5f, WHITE);

        std::string statusText;
        if (gameOver) {
            if (winner == 1) statusText = std::string(jugador1NombreGlobal) + " GANA!";
            else if (winner == 2) statusText = std::string(jugador2NombreGlobal) + " GANA!";
            else if (winner == 3) statusText = "EMPATE!";
            DrawText(statusText.c_str(), uiPanelX, uiPanelY + 80, 24, YELLOW);
            DrawText("Presiona 'R' para reiniciar", uiPanelX, uiPanelY + 110, 18, LIGHTGRAY);
        } else {
            statusText = "Turno de: " + std::string((currentPlayer == 1) ? jugador1NombreGlobal : jugador2NombreGlobal);
            DrawText(statusText.c_str(), uiPanelX, uiPanelY + 80, 20, RAYWHITE);
            DrawText("Usa <- -> para mover", uiPanelX, uiPanelY + 110, 18, LIGHTGRAY);
            DrawText("ENTER o ABAJO para soltar", uiPanelX, uiPanelY + 135, 18, LIGHTGRAY);
        }

        DrawText("Presiona ESC para volver al menú", uiPanelX, screenHeight - 60, 18, RAYWHITE);

        //float controlesScale = 0.3f;
        //DrawTextureEx(Controles, {uiPanelX, uiPanelY + 180}, 0.0f, controlesScale, WHITE); // Ajustar Y para más espacio
        //DrawText("Controles", uiPanelX + (Controles.width * controlesScale - MeasureText("Controles",15))/2 , uiPanelY + 180 + Controles.height*controlesScale + 5, 15, RAYWHITE);

        EndDrawing();
    }
    SetExitKey(KEY_NULL);
}

/*********************************************************************************/

void EscenaInstrucciones()
{
    SetExitKey(KEY_ESCAPE);
    while (!WindowShouldClose()){
        BeginDrawing();
        DrawTextureEx(Fondo, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);
        DrawText("INSTRUCCIONES:", screenWidth/2 - MeasureText("INSTRUCCIONES:", 20)/2, 30, 20, RAYWHITE);
        DrawText("El juego consiste en conectar 4 fichas de tu color", screenWidth/2 - MeasureText("El juego consiste en conectar 4 fichas de tu color", 20)/2, 100, 20, RAYWHITE);
        DrawText("ya sea de forma vertical, horizontal o en diagonal.", screenWidth/2 - MeasureText("ya sea de forma vertical, horizontal o en diagonal.", 20)/2, 130, 20, RAYWHITE);
        DrawText("El primero en conectar 4 gana.", screenWidth/2 - MeasureText("El primero en conectar 4 gana.", 20)/2, 160, 20, RAYWHITE);
        DrawText("En el juego, usa las FLECHAS IZQUIERDA y DERECHA para elegir columna.", screenWidth/2 - MeasureText("En el juego, usa las FLECHAS IZQUIERDA y DERECHA para elegir columna.", 18)/2, 220, 18, LIGHTGRAY);
        DrawText("Presiona ENTER o FLECHA ABAJO para soltar tu ficha.", screenWidth/2 - MeasureText("Presiona ENTER o FLECHA ABAJO para soltar tu ficha.", 18)/2, 250, 18, LIGHTGRAY);
        DrawText("Presiona 'R' en el juego para reiniciar la partida.", screenWidth/2 - MeasureText("Presiona 'R' en el juego para reiniciar la partida.", 18)/2, 280, 18, LIGHTGRAY);
        DrawText("Presiona la tecla ESC para volver al menú", screenWidth/2 - MeasureText("Presiona la tecla ESC para volver al menú", 15)/2, screenHeight - 60, 15, RAYWHITE);
        EndDrawing();
         if (IsKeyPressed(KEY_ESCAPE)) {
             break;
        }
    }
    SetExitKey(KEY_NULL);
}

/*********************************************************************************/

void EscenaCreditos()
{
    SetExitKey(KEY_ESCAPE);
    while (!WindowShouldClose()){
        BeginDrawing();
        DrawTextureEx(Fondo, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);
        DrawText("CREDITOS:", screenWidth/2 - MeasureText("CREDITOS:", 20)/2, 30, 20, RAYWHITE);
        DrawText("Programa elaborado como proyecto final de Programación de", screenWidth/2 - MeasureText("Programa elaborado como proyecto final de Programación de", 20)/2, 100, 20, RAYWHITE);
        DrawText("Computadoras de la Licenciatura en Ciencias de la Computación", screenWidth/2 - MeasureText("Computadoras de la Licenciatura en Ciencias de la Computación", 20)/2, 130, 20, RAYWHITE);
        DrawText("de la Universidad de Sonora.", screenWidth/2 - MeasureText("de la Universidad de Sonora.", 20)/2, 160, 20, RAYWHITE);
        DrawText("Presentado el 17 de mayo de 2024.", screenWidth/2 - MeasureText("Presentado el 17 de mayo de 2024.", 20)/2, 250, 20, RAYWHITE);
        DrawText("Desarrolladores:", screenWidth/2 - MeasureText("Desarrolladores:", 20)/2, 300, 20, RAYWHITE);
        DrawText("-DANIEL LEINAD DOMÍNGUEZ CALVARIO", screenWidth/2 - MeasureText("-DANIEL LEINAD DOMÍNGUEZ CALVARIO", 20)/2, 350, 20, RAYWHITE);
        DrawText("-ALEJANDRO CORDERO FRAGA", screenWidth/2 - MeasureText("-ALEJANDRO CORDERO FRAGA", 20)/2, 380, 20, RAYWHITE);
        DrawText("-JOSE RODRIGO ESPINOZA GARCIA", screenWidth/2 - MeasureText("-JOSE RODRIGO ESPINOZA GARCIA", 20)/2, 410, 20, RAYWHITE);
        DrawText("-ALBERTO GALVEZ MENDOZA", screenWidth/2 - MeasureText("-ALBERTO GALVEZ MENDOZA", 20)/2, 440, 20, RAYWHITE);
        DrawText("Presiona la tecla ESC para volver al menú", screenWidth/2 - MeasureText("Presiona la tecla ESC para volver al menú", 15)/2, screenHeight - 60, 15, RAYWHITE);
        EndDrawing();
         if (IsKeyPressed(KEY_ESCAPE)) {
             break;
        }
    }
    SetExitKey(KEY_NULL);
}
