//linux
//#include "./lraylib/raylib-cpp.hpp"
//windows
#include "raylib.h"

#include "BotonesMenu.hpp"
#include "Escenas.hpp"

Texture2D FichaRoja;
Texture2D FichaAmarilla;
Texture2D Controles;

const int screenWidth = 1000;
const int screenHeight = 650;

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
    const int numBotones = 4;
    BotonesMenu botones[4] = {
        BotonesMenu(0, (screenWidth - 300) / 2, 230),
        BotonesMenu(1, (screenWidth - 300) / 2, 310),
        BotonesMenu(2, (screenWidth - 300) / 2, 390),
        BotonesMenu(3, (screenWidth - 300) / 2, 470)
    };

    int currentKeyboardSelection = 0; 

    SetExitKey(KEY_NULL);

    while (!WindowShouldClose()){

        if(IsKeyPressed(KEY_DOWN)){
            currentKeyboardSelection = (currentKeyboardSelection + 1) % numBotones;
        }

        if(IsKeyPressed(KEY_UP)){
            currentKeyboardSelection--;
            if(currentKeyboardSelection < 0){
                currentKeyboardSelection = numBotones - 1;
            }
        }

        int actionTriggeredBy = -1; // -1: sin acción

        if(IsKeyPressed(KEY_ENTER)){
            actionTriggeredBy = currentKeyboardSelection; // La accion es la del boton actualmente seleccionado por teclado
        }

        // --- Ejecutar Accion ---
        if(actionTriggeredBy != -1){
            switch(actionTriggeredBy){
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

        // --- Dibujado ---
        BeginDrawing();
        ClearBackground(Color{ 47, 124, 192, 255 });
        
        if(title){
            // Dibuja la imagen del título en lugar del texto
            DrawTexture(
                tituloTexture,
                screenWidth / 2 - tituloTexture.width / 2, // Centrado horizontal
                -10, // Posición vertical
                WHITE
            );
        }

        for(int i = 0; i < numBotones; i++){

            botones[i].Draw(); 

            if (i == currentKeyboardSelection){
                DrawRectangleLinesEx(botones[i].hitbox, 2.0f, RED); // Dibuja el contorno en el botton actual seleccionado

                // Aqui se pondra la flecha que estara en la seleccion de botones

            }
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
