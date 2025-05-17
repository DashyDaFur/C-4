#ifndef SONIDOS_HPP_INCLUDED
#define SONIDOS_HPP_INCLUDED

#include "raylib.h"

struct Sonidos {
    Sound efectos[10]; 

    void Cargar(const char* ruta);

    void ReproducirAleatorio();

    void Descargar();
};

#endif // SONIDOS_HPP_INCLUDED