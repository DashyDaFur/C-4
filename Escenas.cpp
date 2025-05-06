//linux
#include "./lraylib/raylib-cpp.hpp"
//windows
// #include "raylib.h"

#include "Escenas.hpp"

void EscenaJuego()
{
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("Haz clic para volver al menu", 270, 340, 20, DARKGRAY);

        EndDrawing();

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            break;
        }
    }
}
void EscenaInstrucciones()
{

}

void EscenaCreditos()
{

}
