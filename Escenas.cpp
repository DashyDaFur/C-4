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
