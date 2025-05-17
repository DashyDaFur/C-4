#include "raylib.h"
#include "BotonesMenu.hpp"
#include <string> // Incluir para std::string si no est� ya por el .hpp

Texture2D BotonesMenu::textura; // Definici�n de la textura est�tica

BotonesMenu::BotonesMenu() 
{
    estado = NORMAL;
    textoBoton = ""; // Inicializar texto vac�o por defecto
}

// Constructor modificado
BotonesMenu::BotonesMenu(const std::string& texto, float x, float y) 
{
    textoBoton = texto;
    hitbox = {x, y, 300.0f, 60.0f};
    estado = NORMAL;
}

void BotonesMenu::Draw() 
{
    Rectangle src = {0, (60.0f * estado), 300.0f, 60.0f};
    DrawTextureRec(textura, src, {hitbox.x, hitbox.y}, WHITE);

    // Dibujar el texto del bot�n
    if (!textoBoton.empty()) {
        int fontSize = 20;
        float textWidth = MeasureText(textoBoton.c_str(), fontSize);

        float textX = hitbox.x + (hitbox.width - textWidth) / 2;

        float textY = hitbox.y + (hitbox.height - fontSize) / 2;

        Color textColor = BLACK;
        if (estado == HOVER) {
            textColor = DARKBLUE;
        }

        DrawText(textoBoton.c_str(), (int)textX, (int)textY, fontSize, textColor);
    }
}

void BotonesMenu::CargarTextura(const char* ruta) {
    textura = ::LoadTexture(ruta);
}

void BotonesMenu::DescargarTextura() {
    ::UnloadTexture(textura);
}
