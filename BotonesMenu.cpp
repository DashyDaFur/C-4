#include "raylib.h"
#include "BotonesMenu.hpp"
#include <string> // Incluir para std::string si no est� ya por el .hpp

Texture2D BotonesMenu::textura; // Definici�n de la textura est�tica

BotonesMenu::BotonesMenu() {
    estado = NORMAL;
    textoBoton = ""; // Inicializar texto vac�o por defecto
}

// Constructor modificado
BotonesMenu::BotonesMenu(const std::string& texto, float x, float y) {
    // indice = i; // 'indice' no se usa, se puede omitir o mantener si lo usas para algo m�s
    textoBoton = texto; // Almacenar el texto
    hitbox = {x, y, 300.0f, 60.0f}; // Asumiendo que la textura del bot�n tiene estas dimensiones
    estado = NORMAL;
}

void BotonesMenu::Draw() {
    // Dibujar la textura del bot�n
    // La textura "Botones.png" debe tener 3 estados (NORMAL, PRESSED, HOVER)
    // cada uno de 300x60 p�xeles, apilados verticalmente.
    Rectangle src = {0, (60.0f * estado), 300.0f, 60.0f};
    DrawTextureRec(textura, src, {hitbox.x, hitbox.y}, WHITE);

    // Dibujar el texto del bot�n
    if (!textoBoton.empty()) {
        int fontSize = 20; // Tama�o de la fuente, aj�stalo seg�n necesites
        // Medir el texto para centrarlo
        float textWidth = MeasureText(textoBoton.c_str(), fontSize);

        // Calcular la posici�n x para centrar el texto
        float textX = hitbox.x + (hitbox.width - textWidth) / 2;
        // Calcular la posici�n y para centrar el texto verticalmente
        float textY = hitbox.y + (hitbox.height - fontSize) / 2;

        // Color del texto (puedes cambiarlo seg�n el estado del bot�n si quieres)
        Color textColor = BLACK;
        if (estado == HOVER) {
            // textColor = DARKBLUE; // Ejemplo: cambiar color al hacer hover
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
