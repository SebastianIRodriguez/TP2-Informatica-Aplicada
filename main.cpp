#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estados.h"
#include "lista_eventos.h"

char recibir_entrada()
{
    /**
    Funcion que itera hasta recibir una entrada valida S o N.

    Si se ingresa S, se repetira la simulacion.
    Si se ingresa N, se finaliza la ejecucion del programa.

    recibir_entrada() retorna el caracter 'S' o 'N' ingresado.*/

    char c;
    while (true)
    {
        cout << "Ingrese su respuesta (S/N): " << endl;
        scanf("%c", &c);
        getchar();

        c = toupper(c);

        if (c == 'N' || c == 'S')
        {
            return c;
        }
        else
        {
            cout << "Opcion invalida, intente otra vez:" << endl;
        }
    }
}

void correr_simulacion(Lista_Enlazada *lista)
{
    Mediciones *medicion;

    Estado *estado_actual = new Reposo();

    estado_actual->imprimir_estado();

    bool boton, fin;

    while ((medicion = lista->get_nodo()) != NULL)
    {
        boton = medicion->get_boton();
        fin = medicion->get_fin();

        // El jugador 1 presiona el botón por primera vez
        if (boton == 0 && estado_actual->get_etiqueta() == REPOSO)
        {
            delete estado_actual;
            estado_actual = new Turno_J1_Boton_Pulsado();
        }
        // Si el jugador 1 suelta el botón
        else if (boton == 1 && fin == 0 && estado_actual->get_etiqueta() == TURNO_J1_BOTON_PULSADO)
        {
            delete estado_actual;
            estado_actual = new Turno_J1();
        }
        // El jugador 2 presiona el botón
        else if (boton == 0 && fin == 0 && estado_actual->get_etiqueta() == TURNO_J1)
        {
            delete estado_actual;
            estado_actual = new Turno_J2_Boton_Pulsado();
        }
        // El jugador 2 suelta el botón
        else if (boton == 1 && fin == 0 && estado_actual->get_etiqueta() == TURNO_J2_BOTON_PULSADO)
        {
            delete estado_actual;
            estado_actual = new Turno_J2();
        }
        // El jugador 1 vuelve a presionar el boton
        else if (boton == 0 && fin == 0 && estado_actual->get_etiqueta() == TURNO_J2)
        {
            delete estado_actual;
            estado_actual = new Turno_J1_Boton_Pulsado();
        }
        // Se le termina el tiempo al jugador 1
        else if (boton == 0 && fin == 1 && estado_actual->get_etiqueta() == TURNO_J1_BOTON_PULSADO)
        {
            delete estado_actual;
            estado_actual = new Termina_Tiempo_J1();
        }
        else if (boton == 0 && fin == 1 && estado_actual->get_etiqueta() == TURNO_J2)
        {
            delete estado_actual;
            estado_actual = new Termina_Tiempo_J1();
        }
        // Se le termina el tiempo al jugador 2
        else if (boton == 0 && fin == 1 && estado_actual->get_etiqueta() == TURNO_J2_BOTON_PULSADO)
        {
            delete estado_actual;
            estado_actual = new Termina_Tiempo_J2();
        }
        else if (boton == 0 && fin == 1 && estado_actual->get_etiqueta() == TURNO_J1)
        {
            delete estado_actual;
            estado_actual = new Termina_Tiempo_J2();
        }
        // Vuelve a reset despues de que se les termina el tiempo
        else if (boton == 1 && fin == 1 && (estado_actual->get_etiqueta() == TERMINA_TIEMPO_J1 || estado_actual->get_etiqueta() == TERMINA_TIEMPO_J2))
        {
            delete estado_actual;
            estado_actual = new Reposo();
        }
        // Se pide un reset
        else if (boton == 1 && fin == 1 && (estado_actual->get_etiqueta() == TURNO_J1 || estado_actual->get_etiqueta() == TURNO_J2 || estado_actual->get_etiqueta() == TURNO_J2_BOTON_PULSADO || estado_actual->get_etiqueta() == TURNO_J1_BOTON_PULSADO))
        {
            delete estado_actual;
            estado_actual = new Reposo();
        }
        else
        {
            // Estado imposible o irrelevante
            continue;
        }

        estado_actual->imprimir_estado();
    }
    cout << "\nFin de la simulacion\n" << endl;
}

int main()
{
    int c_eventos;
    bool imprimir = false;

    // Utilizar diferente semilla en cada llamada a rand()
    setbuf(stdout, 0);

    srand(time(NULL));

    cout << "\n\n\tBienvenido a la simulacion de ajedrez\n"
         << endl;
    cout << "  Desea ver las listas de eventos aleatorios que se generen? \n  Aplica a todas las simulaciones\n"
         << endl;

    if (recibir_entrada() == 'S')
        imprimir = true;

    while (true)
    {
        cout << "Ingrese la cantidad de eventos aleatorios que desea crear: " << endl;

        // Leemos la cantidad de eventos
        scanf("%d", &c_eventos);
        getchar(); // Descarta el \n

        // Creamos la lista
        Lista_Enlazada *lista = new Lista_Enlazada(c_eventos);

        if (imprimir)
            lista->imprimir_lista();

        correr_simulacion(lista);

        delete lista;

        cout << "Desea realizar otra simulacion?" << endl;

        if (recibir_entrada() == 'N')
            break;
    }

    return 0;
}