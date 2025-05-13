#include "raylib.h"

enum ButtonState {NORMAL,PRESSED,HOVER};

class BotonesMenu {
        int indice;
    public:
        ButtonState estado = NORMAL;
        Rectangle hitbox;
        static Texture2D textura;

        BotonesMenu();
        BotonesMenu(int i, float x, float y);

        void Update();
        void Draw();
        

        static void CargarTextura(const char* ruta);
        static void DescargarTextura();
    };
