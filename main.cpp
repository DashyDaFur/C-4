// Inclusión de bibliotecas
#include "raylib.h"                 /
#include "BotonesMenu.hpp"
#include "Escenas.hpp"

// Declaración de texturas globales
Texture2D FichaRoja;
Texture2D FichaAmarilla;
Texture2D Controles;

// Configuración de la ventana
const int screenWidth = 1000;      // Ancho de la ventana
const int screenHeight = 650;      // Alto de la ventana

int main()
{
    bool title = true;             // Control para mostrar el título
    Texture2D miImagen;            // Variable para texturas (no se usa luego)

    // Inicialización de la ventana
    InitWindow(screenWidth, screenHeight, "Conecta 4");

    // Carga de texturas
    FichaRoja = LoadTexture("resources/FichaROJA.png");
    FichaAmarilla = LoadTexture("resources/FichasYLLW.png");
    Controles = LoadTexture("resources/Controles.png");
    SetTargetFPS(60);              // Establece el límite de FPS

    // Carga de texturas del menú
    BotonesMenu::CargarTextura("resources/Botones.png");
    Texture2D tituloTexture = LoadTexture("resources/logo.png"); // Textura del título

    // Configuración de botones del menú
    const int numBotones = 4;
    BotonesMenu botones[4] = {
        BotonesMenu(0, (screenWidth - 300) / 2, 230),  // Botón 1 (Jugar)
        BotonesMenu(1, (screenWidth - 300) / 2, 310),  // Botón 2 (Instrucciones)
        BotonesMenu(2, (screenWidth - 300) / 2, 390),  // Botón 3 (Créditos)
        BotonesMenu(3, (screenWidth - 300) / 2, 470)  // Botón 4 (Salir)
    };

    int currentKeyboardSelection = 0;  // Índice del botón seleccionado con teclado
    SetExitKey(KEY_NULL);             // Deshabilita la tecla de salida por defecto

    // Bucle principal del juego
    while (!WindowShouldClose()){
        // Navegación con teclado (flechas arriba/abajo)
        if(IsKeyPressed(KEY_DOWN)){
            currentKeyboardSelection = (currentKeyboardSelection + 1) % numBotones;
        }
        if(IsKeyPressed(KEY_UP)){
            currentKeyboardSelection--;
            if(currentKeyboardSelection < 0){
                currentKeyboardSelection = numBotones - 1;
            }
        }

        // Detección de acción (Enter)
        int actionTriggeredBy = -1; // -1: sin acción
        if(IsKeyPressed(KEY_ENTER)){
            actionTriggeredBy = currentKeyboardSelection;
        }

        // Manejo de acciones del menú
        if(actionTriggeredBy != -1){
            switch(actionTriggeredBy){
                case 0:  // Jugar
                    BotonesMenu::DescargarTextura();
                    EscenaJuego();                     // Entra en la escena de juego
                    BotonesMenu::CargarTextura("resources/Botones.png");
                    break;
                case 1:  // Instrucciones
                    EscenaInstrucciones();            // Muestra instrucciones
                    break;
                case 2:  // Créditos
                   EscenaCreditos();                  // Muestra créditos
                   break;
                case 3:  // Salir
                    CloseWindow();                     // Cierra el juego
                    break;
            }
        }

        // Renderizado
        BeginDrawing();
        //ClearBackground(Color{ 0, 0, 0, 255 });
        ClearBackground(Color{ 20, 20, 120, 255 });

        // Dibuja el título
        if(title){
            DrawTexture(
                tituloTexture,
                screenWidth / 2 - tituloTexture.width / 2, // Centrado
                -10,
                WHITE
            );
        }

        // Dibuja los botones y resalta el seleccionado
        for(int i = 0; i < numBotones; i++){
            botones[i].Draw();
            if (i == currentKeyboardSelection){
                DrawRectangleLinesEx(botones[i].hitbox, 2.0f, RED); // Resaltado
            }
        }
        EndDrawing();
    }

    // Limpieza al salir
    BotonesMenu::DescargarTextura();
    UnloadTexture(tituloTexture);
    UnloadTexture(FichaRoja);
    UnloadTexture(FichaAmarilla);
    UnloadTexture(Controles);
    CloseWindow();
    return 0;
}
