#include "raylib.h"

#include "Escenas.hpp"

extern Texture2D Fondo;
extern Texture2D FichaRoja;
extern Texture2D FichaAmarilla;

const int screenWidth = 1000;
const int screenHeight = 650;

void EscenaJuego()
{
    SetExitKey(KEY_ESCAPE);
    Texture2D Fondo = LoadTexture("resources/Fondo.jpg");
    Texture2D FichaRoja = LoadTexture("resources/FichaROJA.png");
    Texture2D FichaAmarilla = LoadTexture("resources/FichaYLLW.png");
    Texture2D Controles = LoadTexture("resources/Controles.png");
    while (!WindowShouldClose()){

        BeginDrawing();
        DrawTextureEx(Fondo, (Vector2){0, 0}, 0.0f, 1, WHITE);


        DrawText("Jugador 1", 735, screenHeight - 150, 15, RAYWHITE);
        DrawTextureEx(FichaRoja, (Vector2){ (float)850, (float)(screenHeight - 170) },0.0f, 0.1f, WHITE);

        DrawText("Jugador 2", 735, screenHeight - 110, 15, RAYWHITE);
        DrawTextureEx(FichaAmarilla,(Vector2){ (float)850, (float)(screenHeight - 130) },0.0f, 0.1f, WHITE);


        DrawTextureEx(Controles,(Vector2){(float)50, (float)(screenHeight - 220 ) },0.0f, 0.4f, WHITE);
        DrawText("Controles",115, screenHeight - 110, 15, RAYWHITE);



        DrawText("Presiona la tecla ESC para volver al menu", 340, 600, 15, RAYWHITE);
        EndDrawing();

        if (IsMouseButtonReleased(KEY_ESCAPE)) {
            break;
        }
    }
    UnloadTexture(FichaRoja);
    SetExitKey(KEY_NULL);
}
void EscenaInstrucciones()
{
    SetExitKey(KEY_ESCAPE);
    while (!WindowShouldClose()){
        BeginDrawing();
        DrawTextureEx(Fondo, (Vector2){0, 0}, 0.0f, 1, WHITE);

        DrawText("INSTRUCCIONES:", 410, 30, 20, RAYWHITE);
        DrawText("El juego consiste en conectar 4 fichas de las que te corresponden", 145, 100, 20, RAYWHITE);
        DrawText(" ya sea de forma vertical, horizontal o en diagonal. El primero en ", 145, 130, 20, RAYWHITE);
        DrawText("conectar 4 gana", 410, 160, 20, RAYWHITE);
        DrawText("Presiona la tecla ESC para volver al menu", 340, 600, 15, RAYWHITE);

        EndDrawing();

        if (IsMouseButtonReleased(KEY_ESCAPE)) {
            break;
        }
    }
    SetExitKey(KEY_NULL);
}

void EscenaCreditos()
{
    SetExitKey(KEY_ESCAPE);
    while (!WindowShouldClose()){
        BeginDrawing();
        DrawTextureEx(Fondo, (Vector2){0, 0}, 0.0f, 1, WHITE);

        DrawText("CREDITOS:", 440, 30, 20, RAYWHITE);
        DrawText(" Programa elaborado como proyecto final de Programación de", 175, 100, 20, RAYWHITE);
        DrawText("Computadoras de la Licenciatura en Ciencias de la Computación", 175, 130, 20, RAYWHITE);
        DrawText("de la Universidad de Sonora.", 345, 160, 20, RAYWHITE);
        DrawText("Presentado el 17 de mayo de 2025.", 315, 250, 20, RAYWHITE);
        DrawText("Desarrolladores:", 400, 300, 20, RAYWHITE);
        DrawText("-DANIEL LEINAD DOMÍNGUEZ CALVARIO", 280, 350, 20, RAYWHITE);
        DrawText("-ALEJANDRO CORDERO FRAGA", 335, 380, 20, RAYWHITE);
        DrawText("-JOSE RODRIGO ESPINOZA GARCIA", 310, 410, 20, RAYWHITE);
        DrawText("-ALBERTO GALVEZ MENDOZA", 335, 440, 20, RAYWHITE);


        DrawText("Presiona la tecla ESC para volver al menu", 340, 600, 15, RAYWHITE);

        EndDrawing();

        if (IsMouseButtonReleased(KEY_ESCAPE)) {
            break;
        }
    }
    SetExitKey(KEY_NULL);
}
