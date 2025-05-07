//linux
//#include "./lraylib/raylib-cpp.hpp"
//windows
#include "raylib.h"

#include "BotonesMenu.hpp"
#include "Escenas.hpp"


// Tamaño de la pantalla
const int screenWidth = 1000;
const int screenHeight = 650;

int main()
{
    bool title = true;

    InitWindow(screenWidth, screenHeight, "Conecta 4");
    SetTargetFPS(60);

    // --- Carga textura de los botones ---
    BotonesMenu::CargarTextura("resources/botones.png");

    // --- Establece el indice, posicion en x y posicion en y de los botones ---
    BotonesMenu botones[4] = {
        BotonesMenu(0, (screenWidth - 300) / 2, 200),
        BotonesMenu(1, (screenWidth - 300) / 2, 280),
        BotonesMenu(2, (screenWidth - 300) / 2, 360),
        BotonesMenu(3, (screenWidth - 300) / 2, 440)
    };

    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (title) DrawText("Conecta 4", screenWidth / 2 - MeasureText("Conecta 4", 50) / 2, 50, 50, DARKBLUE);

        Vector2 mouse = GetMousePosition();

        for (int select = 0; select < 4; select++){

            if (botones[select].Update(mouse)){

                    switch(select){
                    case 0:
                        title = false;
                        BotonesMenu::DescargarTextura();
                        EscenaJuego();
                        BotonesMenu::CargarTextura("resources/botones.png");
                        title = true;
                        break;
                    case 1:
                        EscenaInstrucciones();
                        break;
                    case 2:
                       EscenaCreditos();
                       break;
                    case 3:
                        CloseWindow();
                        break;
                    }
            }

            botones[select].Draw();
        }

        EndDrawing();
    }

    BotonesMenu::DescargarTextura();

    CloseWindow();  
    return 0;
}
