//linux
//#include "./lraylib/raylib-cpp.hpp"
//windows
#include "raylib.h"

#include "Escenas.hpp"

void EscenaJuego()
{
    while (!WindowShouldClose()){

        BeginDrawing();

        ClearBackground(Color{24, 7, 85, 255});



        DrawText("Presiona la tecla ESC para volver al menu", 340, 600, 15, RAYWHITE);
        EndDrawing();

        if (IsMouseButtonReleased(KEY_ESCAPE)) {
            break;
        }
    }
}
void EscenaInstrucciones()
{
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(Color{24, 7, 85, 255});

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

}

void EscenaCreditos()
{
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(Color{24, 7, 85, 255});

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
}
