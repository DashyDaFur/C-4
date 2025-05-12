#include "raylib.h"
#include "BotonesMenu.hpp"

Texture2D BotonesMenu::textura;

BotonesMenu::BotonesMenu() {
    estado = NORMAL;
}

BotonesMenu::BotonesMenu(int i, float x, float y)
{
    indice = i;
    hitbox = {x, y, 300.0f, 60.0f};
    estado = NORMAL;
}

void BotonesMenu::Draw()
{
    Rectangle src = {0, (60.0f * estado), 300.0f, 97.0f};
    DrawTextureRec(textura, src, {hitbox.x, hitbox.y}, WHITE);
}

void BotonesMenu::CargarTextura(const char* ruta)
{
    textura = ::LoadTexture(ruta);
}

void BotonesMenu::DescargarTextura()
{
    ::UnloadTexture(textura);
}
