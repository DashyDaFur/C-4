#include "raylib.h"
#include <cstring>
#include "Escenas.hpp"

#define MAX_NAME_LENGTH 13

extern Texture2D FichaRoja;
extern Texture2D FichaAmarilla;

const int screenWidth = 1000;
const int screenHeight = 650;

bool EscenaNombre(char* p1NameDest, char* p2NameDest)
{
    p1NameDest[0] = '\0';
    p2NameDest[0] = '\0';
    int p1LetterCount = 0;
    int p2LetterCount = 0;
    int activePlayerInput = 1; // Jugador 1 empieza
    bool namesConfirmed = false;
    bool firstFrameDone = false;

    Rectangle p1TextBox = { (float)screenWidth/2 - 100, 230, 200, 40 };
    Rectangle p2TextBox = { (float)screenWidth/2 - 100, 330, 200, 40 };

    while (!WindowShouldClose() && !namesConfirmed)
    {
        char* currentNameBuffer = (activePlayerInput == 1) ? p1NameDest : p2NameDest;
        int* currentLetterCount = (activePlayerInput == 1) ? &p1LetterCount : &p2LetterCount;

        int unicodeKey = GetCharPressed();
        while(unicodeKey > 0)
        {
            if((unicodeKey >= 32) && (unicodeKey <= 125) && (*currentLetterCount < MAX_NAME_LENGTH))
            {
                currentNameBuffer[*currentLetterCount] = (char)unicodeKey;
                currentNameBuffer[*currentLetterCount + 1] = '\0';
                (*currentLetterCount)++;
            }
            unicodeKey = GetCharPressed();
        }

        if(IsKeyPressed(KEY_BACKSPACE))
        {
            if (*currentLetterCount > 0)
            {
                (*currentLetterCount)--;
                currentNameBuffer[*currentLetterCount] = '\0';
            }
        }
        if(firstFrameDone)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                if(activePlayerInput == 1){
                    if (p1LetterCount == 0) strcpy(p1NameDest, "Jugador 1");
                    activePlayerInput = 2;
                } else {
                    if (p2LetterCount == 0) strcpy(p2NameDest, "Jugador 2");
                    namesConfirmed = true;
                }
            }

            if (IsKeyPressed(KEY_TAB))
            {
                if (activePlayerInput == 1) activePlayerInput = 2;
                else activePlayerInput = 1;
            }
        }

        if (IsKeyPressed(KEY_ESCAPE)) return false;
        
        BeginDrawing();
            ClearBackground(Color{ 47, 124, 192, 255 });

            DrawText("Conecta 4", screenWidth / 2 - MeasureText("Conecta 4", 40) / 2, 60, 40, RAYWHITE);
            DrawText("Introduce los nombres de los jugadores:", screenWidth / 2 - MeasureText("Introduce los nombres de los jugadores:", 20) / 2, 130, 20, RAYWHITE);

            DrawText("Jugador 1:", p1TextBox.x, p1TextBox.y - 25, 20, RAYWHITE);
            DrawRectangleRec(p1TextBox, LIGHTGRAY);
            if (activePlayerInput == 1) DrawRectangleLinesEx(p1TextBox, 2, YELLOW);
            else DrawRectangleLinesEx(p1TextBox, 1, DARKGRAY); 

            DrawText(p1NameDest, (int)p1TextBox.x + 10, (int)p1TextBox.y + 10, 20, BLACK);

            if (activePlayerInput == 1 && (p1LetterCount < MAX_NAME_LENGTH))
            {
                if (((int)(GetTime()*2.5f))%2 == 0) 
                {
                    DrawText("_", (int)p1TextBox.x + 10 + MeasureText(p1NameDest, 20), (int)p1TextBox.y + 12, 20, BLACK);
                }
            }

            // Jugador 2
            DrawText("Jugador 2:", p2TextBox.x, p2TextBox.y - 25, 20, RAYWHITE);
            DrawRectangleRec(p2TextBox, LIGHTGRAY);
            if (activePlayerInput == 2) DrawRectangleLinesEx(p2TextBox, 2, YELLOW);
            else DrawRectangleLinesEx(p2TextBox, 1, DARKGRAY);
            
            DrawText(p2NameDest, (int)p2TextBox.x + 10, (int)p2TextBox.y + 10, 20, BLACK);

            if (activePlayerInput == 2 && (p2LetterCount < MAX_NAME_LENGTH))
            {
                if (((int)(GetTime()*2.5f))%2 == 0)
                {
                    DrawText("_", (int)p2TextBox.x + 10 + MeasureText(p2NameDest, 20), (int)p2TextBox.y + 12, 20, BLACK);
                }
            }

            float helpTextY = screenHeight - 100;
            DrawText("Presiona ENTER para confirmar nombre / continuar.", screenWidth / 2 - MeasureText("Presiona ENTER para confirmar nombre / continuar.", 18) / 2, helpTextY, 18, RAYWHITE);
            helpTextY += 25;
            DrawText("Presiona TAB para cambiar de jugador.", screenWidth / 2 - MeasureText("Presiona TAB para cambiar de jugador.", 18) / 2, helpTextY, 18, RAYWHITE);
            helpTextY += 25;
            DrawText("Presiona ESC para volver al menú principal.", screenWidth / 2 - MeasureText("Presiona ESC para volver al menú principal.", 18) / 2, helpTextY, 18, RAYWHITE);

        EndDrawing();

        if (!firstFrameDone) firstFrameDone = true;
    }

    return true; 
}

void EscenaJuego()
{
    char jugador1Nombre[MAX_NAME_LENGTH + 1];
    char jugador2Nombre[MAX_NAME_LENGTH + 1];

    if (!EscenaNombre(jugador1Nombre, jugador2Nombre)) {
        return;
    }

    SetExitKey(KEY_ESCAPE);
    Texture2D FichaRoja = LoadTexture("resources/FichaROJA.png");
    Texture2D FichaAmarilla = LoadTexture("resources/FichaYLLW.png");
    Texture2D Controles = LoadTexture("resources/Controles.png");
    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(Color{ 47, 124, 192, 255 });


        DrawText(jugador1Nombre, 735, screenHeight - 150, 15, RAYWHITE);
        DrawTextureEx(FichaRoja, (Vector2){ (float)850, (float)(screenHeight - 170) },0.0f, 0.1f, WHITE);

        DrawText(jugador2Nombre, 735, screenHeight - 110, 15, RAYWHITE);
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
        ClearBackground(Color{ 47, 124, 192, 255 });

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
        ClearBackground(Color{ 47, 124, 192, 255 });

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