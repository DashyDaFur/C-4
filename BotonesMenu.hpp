#ifndef BOTONESMENU_HPP_INCLUDED // Asegúrate de tener guardas de inclusión
#define BOTONESMENU_HPP_INCLUDED

#include "raylib.h"
#include <string> // Para std::string

enum ButtonState {NORMAL,PRESSED,HOVER};

class BotonesMenu {
    // int indice; // 'indice' no se usa actualmente, puedes quitarlo si no lo necesitas
public:
    ButtonState estado = NORMAL;
    Rectangle hitbox;
    std::string textoBoton; // NUEVO: Para almacenar el texto del botón
    static Texture2D textura;

    BotonesMenu();
    // Modificar constructor para aceptar texto
    BotonesMenu(const std::string& texto, float x, float y);

    // 'Update' no está implementado, puedes quitarlo si no lo necesitas
    // void Update();
    void Draw();

    static void CargarTextura(const char* ruta);
    static void DescargarTextura();
};

#endif // BOTONESMENU_HPP_INCLUDED
