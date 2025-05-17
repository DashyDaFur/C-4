#include "Sonidos.hpp"
#include <string>

void Sonidos::Cargar(const char* ruta) 
{
    for (int i = 0; i < 10; i++) {
        std::string rutaCompleta = std::string(ruta) + "/Caida_" + std::to_string(i + 1) + ".wav";
        efectos[i] = LoadSound(rutaCompleta.c_str());
    }
}

void Sonidos::ReproducirAleatorio() 
{
    int indiceAleatorio = GetRandomValue(0, 9);
    PlaySound(efectos[indiceAleatorio]);
}

void Sonidos::Descargar() 
{
    for (int i = 0; i < 10; i++) {
        UnloadSound(efectos[i]);
    }
}