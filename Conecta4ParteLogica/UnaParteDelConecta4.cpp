#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

void MostrarTablero(int* &juego)
{
    cout<<"\t";
    for(int i=41;i>-1;i--)
    {
        cout<<setw(2)<<juego[i];
        if(i%7==0)
        {
            cout<<"\n"<<"\t";
        }
    }
    cout<<"\n";
}
int contar(int columna, int op, int jugador, int* juego) {
    int conteo = 0;
    int posicion = columna + op;

    while (posicion >= 0 && posicion < 42 && juego[posicion] == jugador) {
        // Validar que no se cruce el borde del tablero
        int colActual = columna % 7;
        int colNueva = posicion % 7;


        conteo++;
        posicion += op;
    }
    return conteo;
}


bool Cuatro(int columna, int jugador, int* juego) {
    int h  = 1 + contar(columna,  1, jugador, juego) + contar(columna, -1, jugador, juego);  // Horizontal
    int v  = 1 + contar(columna,  7, jugador, juego) + contar(columna, -7, jugador, juego);  // Vertical
    int d1 = 1 + contar(columna,  8, jugador, juego) + contar(columna, -8, jugador, juego);  // Diagonal izquierda a derecha
    int d2 = 1 + contar(columna,  6, jugador, juego) + contar(columna, -6, jugador, juego);  // Diagonal derecha a izquierda

    return (h >= 4 || v >= 4 || d1 >= 4 || d2 >= 4);
}

void Caida(int jugador,int columna,int* &juego,int altura)
{
    int alturaR=5-altura;
    int* juegoCopia=new int[42];

    for (int i=0;i<42;i++)
    {
        if(i!=columna)
        {
            juegoCopia[i]=juego[i];
        }
        else
        {
            juegoCopia[i]=0;
        }
    }


    int alturaTemp=alturaR;
    for(int i=0;i<alturaR;i++)
    {
        system("CLS");
        juegoCopia[columna+(7*alturaTemp)]=jugador;
        MostrarTablero(juegoCopia);
        juegoCopia[columna+(7*alturaTemp)]=0;
        alturaTemp--;
        this_thread::sleep_for(std::chrono::milliseconds(500));
        system("CLS");
    }

}

template <typename Tipo>
bool capturaSegura(Tipo &n)
{
    if (cin.fail()||n<0)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}


int main ()
{
    int opcion=0;
    //Aqui se repite varias veces el juego
    do{
        int columna=0;
        int altura;
        short int jugador=1;
        int* juego=new int[42];

        for (int i=0;i<42;i++)
        {
            juego[i]=0;
        }
        cout<<"TABLERO: \n";
        MostrarTablero(juego);

        cout<<"RENGLON  ";
        for(int i=0;i<7;i++)
        {
            cout<<i+1<<" ";
        }

        //Este es un solo juego
        do{

            jugador=(jugador%2)?1:2;
            altura=0;
            cout<<"\n"<<setw(10)<<"JUGADOR "<<jugador;
            do{
            cout<<"\nEn que columna va a entrar la ficha?";
            cin>>columna;
            columna=7-columna;
            }while(!capturaSegura(columna)||columna>7);

            int altura=0;
            while(juego[columna]!=0)
            {

                columna=columna+7;
                altura++;
            }
            cout<<"\n ALTURA"<<altura<<"\n";
            juego[columna]=jugador;



            Caida(jugador,columna,juego,altura);
            MostrarTablero(juego);

            if(Cuatro(columna,jugador,juego))
            {
                this_thread::sleep_for(std::chrono::milliseconds(2000));
                system("CLS");
                cout<<"EL JUGADOR "<<jugador<<" GANO!"<<"\n";
                break;
            }
            jugador++;
        }while(true);

        cout<<"\n\250Quiere Jugar otra vez?";
        do{
        cout<<"\n1)PARA S\241"<<"\n2)PARA NO";
        cin>>opcion;
        }while(!capturaSegura(opcion)||opcion>2);
    }while(opcion!=0);

    return 0;
}


/*
bool Vecindad(short int opcion, int columna, short int jugador, int* juego)
{
    switch(opcion)
    {
        case 1: // Vertical
            if (columna + 7 < 42 && juego[columna + 7] == jugador)
                return true;
            if (columna - 7 >= 0 && juego[columna - 7] == jugador)
                return true;
            break;

        case 2: // Horizontal
            if (columna % 7 < 6 && juego[columna + 1] == jugador) // derecha
                return true;
            if (columna % 7 > 0 && juego[columna - 1] == jugador) // izquierda
                return true;
            break;

        case 3: // Diagonales
            // Diagonal abajo derecha
            if (columna + 8 < 42 && columna % 7 < 6 && juego[columna + 8] == jugador)
                return true;
            // Diagonal abajo izquierda
            if (columna + 6 < 42 && columna % 7 > 0 && juego[columna + 6] == jugador)
                return true;
            // Diagonal arriba derecha
            if (columna - 6 >= 0 && columna % 7 < 6 && juego[columna - 6] == jugador)
                return true;
            // Diagonal arriba izquierda
            if (columna - 8 >= 0 && columna % 7 > 0 && juego[columna - 8] == jugador)
                return true;
            break;
    }


    return false;
}*/
/*
bool Vecindad(int opcion, int columna, short int jugador, int* juego)
{
    switch(opcion)
    {
        case 1: // Vertical
            if (columna + 7 < 42 && juego[columna + 7] == jugador)
                return true;
            if (columna - 7 >= 0 && juego[columna - 7] == jugador)
                return true;
            break;

        case 2: // Horizontal
            // derecha: evitar pasar al inicio de la siguiente fila
            if ((columna % 7) < 6 && juego[columna + 1] == jugador)
                return true;
            // izquierda: evitar salirse al final de la fila anterior
            if ((columna % 7) > 0 && juego[columna - 1] == jugador)
                return true;
            break;

        case 3: // Diagonales
            // abajo derecha
            if (columna + 8 < 42 && (columna % 7) < 6 && juego[columna + 8] == jugador)
                return true;
            // abajo izquierda
            if (columna + 6 < 42 && (columna % 7) > 0 && juego[columna + 6] == jugador)
                return true;
            // arriba derecha
            if (columna - 6 >= 0 && (columna % 7) < 6 && juego[columna - 6] == jugador)
                return true;
            // arriba izquierda
            if (columna - 8 >= 0 && (columna % 7) > 0 && juego[columna - 8] == jugador)
                return true;
            break;
    }

    return false;
}*/
/*int Vecindad(int opcion, int columna, short int jugador, int* juego)
{
    switch(opcion)
    {
        case 1: // Vertical
            if ((columna + 7 < 42 && juego[columna + 7] == jugador)==true)
                return true;

        case 2: // Horizontal
            // derecha: evitar pasar al inicio de la siguiente fila
            if ((columna % 7) < 6 && juego[columna + 1] == jugador)
                return true;
            // izquierda: evitar salirse al final de la fila anterior
            if ((columna % 7) > 0 && juego[columna - 1] == jugador)
                return true;
            break;

        case 3: // Diagonales
            // abajo derecha
            if (columna + 8 < 42 && (columna % 7) < 6 && juego[columna + 8] == jugador)
                return true;
            // abajo izquierda
            if (columna + 6 < 42 && (columna % 7) > 0 && juego[columna + 6] == jugador)
                return true;
            // arriba derecha
            if (columna - 6 >= 0 && (columna % 7) < 6 && juego[columna - 6] == jugador)
                return true;
            // arriba izquierda
            if (columna - 8 >= 0 && (columna % 7) > 0 && juego[columna - 8] == jugador)
                return true;
            break;
    }

    return false;
}*/



/*
#include <iostream>

using namespace std;

void showGrid(unsigned long long p1, unsigned long long p2)
{
    int i = 42;
    while (--i)
    {
        cout << ((p1 >> i) & 1);
        if (i%7 == 0)
        {
            cout << endl;
        }
    }
    cout << (p1 & 1);
}

void gameLoop(unsigned long long *p1, unsigned long long *p2, unsigned long long *column, unsigned char *curr, unsigned int *depth)
{
    for (int i = 0; i < 10; i++)
    {
        cout << "Ingrese columna para O: ";
	    cin >> *column;
	    *depth += (1ULL << 3*(*column));
	    *curr = ((*depth) >> 3*(*column)) & 7;
	    (*curr)--;
	    *p1 += (1ULL << (7*(*curr) + (*column)));
	    showGrid(*p1, *p2);
	    cout << endl;
    }
}

void showBits(unsigned long long a)
{
    int i = 64;
    while (--i)
    {
        cout << ((a >> i) & 1);
        if (i%8 == 0)
        {
            cout << endl;
        }
    }
    cout << (a & 1);
}

int main(int argc, char *argv[])
{
	// depth de columnas
	unsigned long long p1 = 0, p2 = 0;
	unsigned int depth = 0;
	unsigned long long column = 0;
	unsigned char curr = 0;

	/*cout << "Ingrese columna para O: ";
	cin >> column;
	p1 = (1ULL << (column));
	depth += (1ULL << 3*column);
	showGrid(p1, p2);
	cout << endl << endl;//////////////////Aca termina este comentario
	gameLoop(&p1, &p2, &column, &curr, &depth);
	//showBits(p1);
	return 0;
}
*/
