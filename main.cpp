#include "raylib.h"
#include "BotonesMenu.hpp"
#include "Escenas.hpp"
#include "Sonidos.hpp"
#include <string> // Necesario para std::string

// ... (otras variables globales como Fondo, FichaRoja, etc.) ...
Texture2D Fondo;
Texture2D FichaRoja;
Texture2D FichaAmarilla;
Texture2D Controles; // Aseg�rate que esta est� declarada

const int screenWidth = 1000;
const int screenHeight = 650;

Sonidos sonidosCaida;

int main()
{
    bool title = true;
    // Texture2D miImagen; // 'miImagen' no se usa
    InitWindow(screenWidth, screenHeight, "Conecta 4");
    Fondo = LoadTexture("resources/Fondo.jpg");
    FichaRoja = LoadTexture("resources/FichaROJA.png");     // Aseg�rate que estas rutas sean correctas
    FichaAmarilla = LoadTexture("resources/FichaYLLW.png"); // y que las texturas existan
    Controles = LoadTexture("resources/Controles.png");      // y que esta textura tambi�n exista
    SetTargetFPS(60);

    InitAudioDevice();
    sonidosCaida.Cargar("resources/sfx");

    // --- Carga texturas ---
    BotonesMenu::CargarTextura("resources/Botones.png"); // Textura para el fondo de los botones
    Texture2D tituloTexture = LoadTexture("resources/logo.png");
    // DrawTextureEx(Fondo, (Vector2){0, 0}, 0.0f, 1, WHITE); // Mover esto al bucle de dibujado

    // --- Establece el texto, posicion en x y posicion en y de los botones ---
    const int numBotones = 4;
    BotonesMenu botones[numBotones] = {
        BotonesMenu("Jugar", (screenWidth - 300) / 2, 230),             // Texto para el bot�n 0
        BotonesMenu("Instrucciones", (screenWidth - 300) / 2, 310),     // Texto para el bot�n 1
        BotonesMenu("Creditos", (screenWidth - 300) / 2, 390),          // Texto para el bot�n 2
        BotonesMenu("Salir", (screenWidth - 300) / 2, 470)              // Texto para el bot�n 3
    };

    int currentKeyboardSelection = 0;

    SetExitKey(KEY_NULL); // Para manejar el cierre manualmente o por el bot�n "Salir"

    while (!WindowShouldClose()) {
        // --- L�gica de Input ---
        if (IsKeyPressed(KEY_DOWN)) {
            currentKeyboardSelection = (currentKeyboardSelection + 1) % numBotones;
        }

        if (IsKeyPressed(KEY_UP)) {
            currentKeyboardSelection--;
            if (currentKeyboardSelection < 0) {
                currentKeyboardSelection = numBotones - 1;
            }
        }

        int actionTriggeredBy = -1;

        // Actualizar estado de los botones (para hover visual con teclado)
        for (int i = 0; i < numBotones; i++) {
            if (i == currentKeyboardSelection) {
                botones[i].estado = HOVER;
            } else {
                botones[i].estado = NORMAL;
            }
        }

        if (IsKeyPressed(KEY_ENTER)) {
            actionTriggeredBy = currentKeyboardSelection;
        }

        // --- Ejecutar Accion ---
        if (actionTriggeredBy != -1) {
            // Opcional: cambiar estado a PRESSED visualmente por un momento
            // botones[actionTriggeredBy].estado = PRESSED;
            // EndDrawing(); BeginDrawing(); // Forzar redibujado si quieres ver el PRESSED
            // WaitTime(0.1); // Peque�a pausa

            switch (actionTriggeredBy) {
                case 0: // Jugar
                    title = false;
                    BotonesMenu::DescargarTextura(); // Descargar antes de cambiar de "escena" si es necesario
                    EscenaJuego();
                    BotonesMenu::CargarTextura("resources/Botones.png"); // Recargar para el men�
                    title = true;
                    break;
                case 1: // Instrucciones
                    EscenaInstrucciones();
                    break;
                case 2: // Cr�ditos
                    EscenaCreditos();
                    break;
                case 3: // Salir
                    // CloseWindow(); // No es necesario si el bucle termina
                    // Ya no se necesita 'return 0;' aqu�, el bucle terminar�
                    goto end_main_loop; // Salir del bucle while
            }
        }

        // --- Dibujado ---
        BeginDrawing();
        ClearBackground(RAYWHITE); // Limpiar fondo
        DrawTextureEx(Fondo, (Vector2){0, 0}, 0.0f, 1, WHITE); // Dibujar fondo primero

        if (title) {
            DrawTexture(
                tituloTexture,
                screenWidth / 2 - tituloTexture.width / 2,
                -10,
                WHITE
            );
        }

        for (int i = 0; i < numBotones; i++) {
            botones[i].Draw(); // El Draw del bot�n ahora incluye el texto
        }

        EndDrawing();
    }

end_main_loop:; // Etiqueta para el goto

    // --- Descarga de recursos ---
    sonidosCaida.Descargar();
    CloseAudioDevice();
    UnloadTexture(Fondo);
    UnloadTexture(FichaRoja);
    UnloadTexture(FichaAmarilla);
    UnloadTexture(Controles);
    UnloadTexture(tituloTexture);
    BotonesMenu::DescargarTextura(); // Descargar la textura de los botones

    CloseWindow(); // Cerrar la ventana de Raylib

    return 0;
}
