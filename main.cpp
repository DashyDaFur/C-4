//linux
#include "./lraylib/raylib-cpp.hpp"
//windows
// #include "raylib.h"

#include "Escenas.hpp"


// Tamaño de la pantalla
const int screenWidth = 1000;
const int screenHeight = 650;
// Tamaño de los botones

enum ButtonState {NORMAL,PRESSED,HOVER};

int main()
{
    bool title = true;
    ButtonState estado;

    raylib::Window window(screenWidth, screenHeight, "Conecta 4");
    SetTargetFPS(60);

    raylib::Texture2D botonesTexture("resources/botones.png");

    Rectangle botones[4];
    for (int i = 0; i < 4; i++){
        botones[i] = { (float)(screenWidth - buttonWidth) / 2, 200 + i * 80, (float)buttonWidth, (float)buttonHeight};
    }

    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (title) DrawText("Conecta 4", screenWidth / 2 - MeasureText("Conecta 4", 50) / 2, 50, 50, DARKBLUE);

        Vector2 mouse = GetMousePosition();

        for (int i = 0; i < 4; i++){
            estado = NORMAL;

            if (CheckCollisionPointRec(mouse, botones[i])){
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) estado = PRESSED;
                else estado = HOVER;

                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                    if (i == 0){
                        title = false;
                        botonesTexture.Unload();
                        EscenaJuego();
                        title = true;
                        raylib::Texture2D botonesTexture("resources/botones.png");
                    }
                    else if (i == 1) EscenaInstrucciones();
                    else if (i == 2) EscenaCreditos();
                    else if (i == 3) CloseWindow();
                }
            }

            Rectangle src = { 0, (float)(estado * buttonHeight), (float)buttonWidth, (float)buttonHeight };
            DrawTextureRec(botonesTexture, src, { botones[i].x, botones[i].y }, WHITE);
        }

        EndDrawing();
    }

    botonesTexture.Unload();
    return 0;
}
