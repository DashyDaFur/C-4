//linux
//#include "./lraylib/raylib-cpp.hpp"
//windows
#include "raylib.h"

#include "BotonesMenu.hpp"
#include "Escenas.hpp"

Texture2D FichaRoja;
Texture2D FichaAmarilla;
Texture2D Controles;

int main()
{
    bool title = true;
    Texture2D miImagen;
    InitWindow(screenWidth, screenHeight, "Conecta 4");
    FichaRoja= LoadTexture("resources/FichaROJA.png");
    FichaAmarilla= LoadTexture("resources/FichasYLLW.png");
    Controles= LoadTexture("resources/Controles.png");
    SetTargetFPS(60);

    // --- Carga texturas ---
    BotonesMenu::CargarTextura("resources/Botones.png");
    Texture2D tituloTexture = LoadTexture("resources/logo.png"); // Nueva textura para el título
    ClearBackground(Color{ 47, 124, 192, 255 });

    // --- Establece el indice, posicion en x y posicion en y de los botones ---
    BotonesMenu botones[4] = {
        BotonesMenu(0, (screenWidth - 300) / 2, 230),
        BotonesMenu(1, (screenWidth - 300) / 2, 310),
        BotonesMenu(2, (screenWidth - 300) / 2, 390),
        BotonesMenu(3, (screenWidth - 300) / 2, 470)
    };

    SetExitKey(KEY_NULL);

    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(Color{ 47, 124, 192, 255 });
        if (title) {
            // Dibuja la imagen del título en lugar del texto
            DrawTexture(
                tituloTexture,
                screenWidth / 2 - tituloTexture.width / 2, // Centrado horizontal
                -10, // Posición vertical
                WHITE
            );
        }

        Vector2 mouse = GetMousePosition();

        for (int select = 0; select < 4; select++){

            if (botones[select].Update(mouse)){

                    switch(select){
                    case 0:
                        title = false;
                        BotonesMenu::DescargarTextura();
                        EscenaJuego();
                        BotonesMenu::CargarTextura("resources/Botones.png");
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

    // Descargar texturas al salir
    BotonesMenu::DescargarTextura();
    UnloadTexture(tituloTexture);
    UnloadTexture(FichaRoja);
    UnloadTexture(FichaAmarilla);
    UnloadTexture(Controles);
    CloseWindow();
    return 0;
}
