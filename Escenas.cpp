#include "raylib.h"

#include "Escenas.hpp"

// Declaración de texturas externas (definidas en otro archivo)
extern Texture2D FichaRoja;
extern Texture2D FichaAmarilla;

// Configuración de dimensiones de pantalla
const int screenWidth = 1000;   // Ancho de la ventana
const int screenHeight = 650;   // Alto de la ventana

// Función de la escena principal del juego
void EscenaJuego()
{
    SetExitKey(KEY_ESCAPE);  // Tecla ESC para salir de la escena

    // Carga de texturas para esta escena
    Texture2D FichaRoja = LoadTexture("resources/FichaROJA.png");      // Ficha jugador 1
    Texture2D FichaAmarilla = LoadTexture("resources/FichaYLLW.png");  // Ficha jugador 2
    Texture2D Controles = LoadTexture("resources/Controles.png");      // Imagen de controles

    // Bucle principal de la escena
    while (!WindowShouldClose()){
        // Inicio del dibujado
        BeginDrawing();
        ClearBackground(Color{ 23, 62, 190, 255 });  // Fondo azul

        // Información del jugador 1 (rojo)
        DrawText("Jugador 1", 735, screenHeight - 150, 15, RAYWHITE);
        DrawTextureEx(FichaRoja, (Vector2){850, screenHeight - 170}, 0.0f, 0.1f, WHITE);

        // Información del jugador 2 (amarillo)
        DrawText("Jugador 2", 735, screenHeight - 110, 15, RAYWHITE);
        DrawTextureEx(FichaAmarilla, (Vector2){850, screenHeight - 130}, 0.0f, 0.1f, WHITE);

        // Controles del juego
        DrawTextureEx(Controles, (Vector2){50, screenHeight - 220}, 0.0f, 0.4f, WHITE);
        DrawText("Controles", 115, screenHeight - 110, 15, RAYWHITE);

        // Indicación para volver al menú
        DrawText("Presiona la tecla ESC para volver al menu", 340, 600, 15, RAYWHITE);

        // función para juego

        // Fin del dibujado
        EndDrawing();

        // Comprobar si se presiona ESC para salir
        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }

    // Liberación de recursos al salir
    UnloadTexture(FichaRoja);
    UnloadTexture(FichaAmarilla);
    UnloadTexture(Controles);
    SetExitKey(KEY_NULL);  // Restablecer tecla de salida
}

// Escena de instrucciones del juego
void EscenaInstrucciones()
{
    SetExitKey(KEY_ESCAPE);  // Configurar ESC para salir

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(Color{ 23, 62, 190, 255 });  // Fondo azul

        // Título y texto de instrucciones
        DrawText("INSTRUCCIONES:", 410, 30, 20, RAYWHITE);
        DrawText("El juego consiste en conectar 4 fichas de las que te corresponden", 145, 100, 20, RAYWHITE);
        DrawText(" ya sea de forma vertical, horizontal o en diagonal. El primero en ", 145, 130, 20, RAYWHITE);
        DrawText("conectar 4 gana", 410, 160, 20, RAYWHITE);

        // Indicación para volver al menú
        DrawText("Presiona la tecla ESC para volver al menu", 340, 600, 15, RAYWHITE);

        EndDrawing();

        // Comprobar si se presiona ESC para salir
        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }

    SetExitKey(KEY_NULL);  // Restablecer tecla de salida
}

// Escena de créditos del juego
void EscenaCreditos()
{
    SetExitKey(KEY_ESCAPE);  // Configurar ESC para salir

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(Color{ 23, 62, 190, 255 });  // Fondo azul

        // Título y texto de créditos
        DrawText("CREDITOS:", 440, 30, 20, RAYWHITE);
        DrawText(" Programa elaborado como proyecto final de Programación de", 175, 100, 20, RAYWHITE);
        DrawText("Computadoras de la Licenciatura en Ciencias de la Computación", 175, 130, 20, RAYWHITE);
        DrawText("de la Universidad de Sonora.", 345, 160, 20, RAYWHITE);
        DrawText("Presentado el 17 de mayo de 2025.", 315, 250, 20, RAYWHITE);

        // Lista de desarrolladores
        DrawText("Desarrolladores:", 400, 300, 20, RAYWHITE);
        DrawText("-DANIEL LEINAD DOMÍNGUEZ CALVARIO", 280, 350, 20, RAYWHITE);
        DrawText("-ALEJANDRO CORDERO FRAGA", 335, 380, 20, RAYWHITE);
        DrawText("-JOSE RODRIGO ESPINOZA GARCIA", 310, 410, 20, RAYWHITE);
        DrawText("-ALBERTO GALVEZ MENDOZA", 335, 440, 20, RAYWHITE);

        // Indicación para volver al menú
        DrawText("Presiona la tecla ESC para volver al menu", 340, 600, 15, RAYWHITE);

        EndDrawing();

        // Comprobar si se presiona ESC para salir
        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }

    SetExitKey(KEY_NULL);  // Restablecer tecla de salida
}
