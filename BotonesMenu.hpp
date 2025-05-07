#include "raylib.h"

enum ButtonState {NORMAL,PRESSED,HOVER};

class BotonesMenu {
    public:
        Rectangle hitbox;
        ButtonState estado = NORMAL;
        int indice;
        static Texture2D textura;
    
        BotonesMenu();
        BotonesMenu(int index, int x, int y);
    
        bool Update(Vector2 mouse);
        void Draw();
    
        static void CargarTextura(const char* ruta);
        static void DescargarTextura();
    };