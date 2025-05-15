#include "raylib.h"
#include "BotonesMenu.hpp"
#include <string> // Incluir para std::string si no está ya por el .hpp

Texture2D BotonesMenu::textura; // Definición de la textura estática

BotonesMenu::BotonesMenu() {
    estado = NORMAL;
    textoBoton = ""; // Inicializar texto vacío por defecto
}

// Constructor modificado
BotonesMenu::BotonesMenu(const std::string& texto, float x, float y) {
    // indice = i; // 'indice' no se usa, se puede omitir o mantener si lo usas para algo más
    textoBoton = texto; // Almacenar el texto
    hitbox = {x, y, 300.0f, 60.0f}; // Asumiendo que la textura del botón tiene estas dimensiones
    estado = NORMAL;
}

void BotonesMenu::Draw() {
    // Dibujar la textura del botón
    // La textura "Botones.png" debe tener 3 estados (NORMAL, PRESSED, HOVER)
    // cada uno de 300x60 píxeles, apilados verticalmente.
    Rectangle src = {0, (60.0f * estado), 300.0f, 60.0f};
    DrawTextureRec(textura, src, {hitbox.x, hitbox.y}, WHITE);

    // Dibujar el texto del botón
    if (!textoBoton.empty()) {
        int fontSize = 20; // Tamaño de la fuente, ajústalo según necesites
        // Medir el texto para centrarlo
        float textWidth = MeasureText(textoBoton.c_str(), fontSize);

        // Calcular la posición x para centrar el texto
        float textX = hitbox.x + (hitbox.width - textWidth) / 2;
        // Calcular la posición y para centrar el texto verticalmente
        float textY = hitbox.y + (hitbox.height - fontSize) / 2;

        // Color del texto (puedes cambiarlo según el estado del botón si quieres)
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
