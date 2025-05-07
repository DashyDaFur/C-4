#include "raylib.h"
#include "BotonesMenu.hpp"

Texture2D BotonesMenu::textura;

BotonesMenu::BotonesMenu() {}

BotonesMenu::BotonesMenu(int i, float x, float y)
{
    indice = i;
    hitbox = {x, y, 300.0f, 60.0f};
}

bool BotonesMenu::Update(Vector2 mouse)
{
    estado = NORMAL;
    if (CheckCollisionPointRec(mouse, hitbox)){
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) estado = PRESSED;
        else estado = HOVER;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            return true;
        }
    }
    return false;
}

void BotonesMenu::Draw()
{
    Rectangle src = {0, (60.0f * estado), 300.0f, 60.0f};
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