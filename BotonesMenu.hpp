#include "raylib.h"

enum ButtonState {NORMAL,PRESSED,HOVER};

class BotonesMenu {
        Rectangle hitbox;
        ButtonState estado = NORMAL;
        int indice;
public:
        static Texture2D textura;
    
        BotonesMenu();
        BotonesMenu(int i, float x, float y);
    
        bool Update(Vector2 mouse);
        void Draw();
    
        static void CargarTextura(const char* ruta);
        static void DescargarTextura();
    };