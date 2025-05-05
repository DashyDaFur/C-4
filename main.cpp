//linux
#include "./lraylib/raylib-cpp.hpp"
//windows
// #include "raylib.h"

#include "Escenas.hpp"

int main()
{
    // Tamaño de la pantalla
    const int screenWidth = 800;
    const int screenHeight = 450;

    raylib::Window window(screenWidth, screenHeight, "Juego wawaw");

    SetTargetFPS(60);

    Rectangle buttons[4] = {
        { screenWidth/2 - 100, 150, 200, 50 },  // Botón 1
        { screenWidth/2 - 100, 250, 200, 50 },  // Botón 2
        { screenWidth/2 - 100, 350, 200, 50 },  // Botón 3
        { screenWidth/2 - 100, 450, 200, 50 }   // Botón 4
    };

    const char* buttonTexts[4] = {
        "OPCIÓN 1",
        "OPCIÓN 2",
        "OPCIÓN 3",
        "SALIR"
    };

    Color buttonColor = BLUE;
    Color hoverColor = SKYBLUE;
    int selectedOption = -1;

    SetTargetFPS(60);

    // Bucle principal del juego, si se preciona ESC se cierra
    while (!WindowShouldClose()) {


        for (int i = 0; i < 4; i++) {
            if (CheckCollisionPointRec(GetMousePosition(), buttons[i])) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    selectedOption = i;
                }
            }
        }

        // Dibujado
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Título
            DrawText("MENÚ PRINCIPAL", screenWidth/2 - MeasureText("MENÚ PRINCIPAL", 40)/2, 50, 40, DARKGRAY);

            // Dibujar botones
            for (int i = 0; i < 4; i++) {
                Color currentColor = CheckCollisionPointRec(GetMousePosition(), buttons[i]) ? hoverColor : buttonColor;
                DrawRectangleRec(buttons[i], currentColor);
                DrawRectangleLinesEx(buttons[i], 2, BLACK);

                // Centrar texto en los botones
                int textWidth = MeasureText(buttonTexts[i], 20);
                DrawText(buttonTexts[i],
                        buttons[i].x + buttons[i].width/2 - textWidth/2,
                        buttons[i].y + buttons[i].height/2 - 10,
                        20, WHITE);
            }

            // Mostrar opción seleccionada
            if (selectedOption != -1) {
                const char* message = TextFormat("Seleccionaste: %s", buttonTexts[selectedOption]);
                DrawText(message, screenWidth/2 - MeasureText(message, 20)/2, 520, 20, DARKGRAY);

                // Si se seleccionó salir, cerrar la ventana
                if (selectedOption == 3) {
                    CloseWindow();
                    return 0;
                }
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

