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

    //raylib::Window window(screenWidth, screenHeight, "Conecta 4");    // LINUX
    InitWindow(screenWidth, screenHeight, "Juego wawaw");   // WINDOWS
    SetTargetFPS(60);

    //raylib::Texture2D botonesTexture("resources/botones.png");    // LINUX
    BotonesMenu::CargarTextura("resources/botones.png");    // WINDOWS

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
                        //botonesTexture.Unload();  // LNUX
                        //EscenaJuego();    // LINUX
                        BotonesMenu::DescargarTextura(); // WINDOWS
                        EscenaJuego();  // WINDOWS
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

    // Descargar textura antes de salir
    BotonesMenu::DescargarTextura();  // WINDOWS
    CloseWindow();  // WINDOWS

    // prueba

    return 0;
}
