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
            cout << "Opcion invalida, intente otra vez:\n"
                 << endl;
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
    cout << "fin de la simulacion\n\n"
         << endl;
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

    Estado *esta1 = new Reposo();
    Estado *esta2 = new Turno_J1_Boton_Pulsado();

    printf("Esta1:%d   Esta2:%d  \n", esta1->get_etiqueta(), esta2->get_etiqueta());

    delete esta1;
    delete esta2;

    if (recibir_entrada() == 'S')
    {
        imprimir = true;
    }

    while (true)
    {
        cout << "Ingrese la cantidad de eventos aleatorios que desea crear: " << endl;

        // Leemos la cantidad de eventos
        scanf("%d", &c_eventos);
        getchar(); // Descarta el \n

        Lista_Enlazada *lista = new Lista_Enlazada(c_eventos);

        if (imprimir)
            lista->imprimir_lista();

        correr_simulacion(lista);

        delete lista;

        cout << "Desea realizar otra simulacion?" << endl;

        if (recibir_entrada() == 'N')
        {
            break;
        }
    }

    return 0;
}

/**

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

bool requiere_ensanche;
unsigned char cinta;

typedef enum
{
    ALTA_VELOCIDAD,
    BAJA_VELOCIDAD,
    DETENIDO_ENSANCHANDO,
    BAJA_VELOCIDAD_ENSANCHADO,
} Estado;

void correr_simulacion(Evento *eventos)
{

       // Funcion que itera hasta recibir una entrada valida S o N.

        //Si se ingresa S, se repetira la simulacion.
        //Si se ingresa N, se finaliza la ejecucion del programa.

        //recibir_entrada() retorna el caracter 'S' o 'N' ingresado.

    Evento *p = eventos;
    Estado estado_actual = ALTA_VELOCIDAD;

    printf("Cinta a Alta Velocidad: \t\t\t C1 = 1 C0 = 1\t\trequiere_ensanche = 0\n");
    requiere_ensanche = 0;
    cinta = 3;

    while (p->sig != NULL)
    {
        // Se detecta vela
        if (p->s1 == 1 && p->s2 == 0 && estado_actual == ALTA_VELOCIDAD)
        {
            estado_actual = BAJA_VELOCIDAD;
        }
        // Hay que ensanchar la vela
        else if (estado_actual == BAJA_VELOCIDAD && p->s1 == 0 && p->s2 == 0)
        {
            estado_actual = DETENIDO_ENSANCHANDO;
        }
        // Si no hay que ensanchar la vela
        else if (p->s1 == 1 && p->s2 == 1 && estado_actual == BAJA_VELOCIDAD)
        {
            estado_actual = BAJA_VELOCIDAD_ENSANCHADO;
        }
        // Se terminó de ensanchar la vela
        else if (estado_actual == DETENIDO_ENSANCHANDO && p->s1 == 1 && p->s2 == 1)
        {
            estado_actual = BAJA_VELOCIDAD_ENSANCHADO;
        }
        // La vela salió del proceso
        else if (p->s1 == 0 && p->s2 == 0 && estado_actual == BAJA_VELOCIDAD_ENSANCHADO)
        {
            // Cortar la simulacion
            printf("La vela abandono el puesto de control\n");
            printf("Cinta a Alta Velocidad: \t\t\t C1 = 1 C0 = 1\t\trequiere_ensanche = 0\n");
            requiere_ensanche = 0;
            cinta = 3;
            break;
        }
        else
        {
            // Estado imposible o irrelevante
            p = p->sig;
            continue;
        }

        switch (estado_actual)
        {

        case BAJA_VELOCIDAD:
            printf("Cinta a Baja Velocidad: \t\t\t C1 = 1 C0 = 0 \t\trequiere_ensanche = 0\n");
            requiere_ensanche = 0;
            cinta = 2;
            break;

        case BAJA_VELOCIDAD_ENSANCHADO:
            printf("Cinta a Baja Velocidad, vela correcta:\t\t C1 = 1 C0 = 0 \t\trequiere_ensanche = 0\n");
            requiere_ensanche = 0;
            cinta = 2;
            break;

        case ALTA_VELOCIDAD:
            break;

        case DETENIDO_ENSANCHANDO:
            printf("Cinta detenida: \t\t\t\t C1 = 0 C0 = 0 \t\trequiere_ensanche = 1\n");
            requiere_ensanche = 1;
            cinta = 0;
            break;

        default:
            break;
        }

        p = p->sig;
    }
    printf("fin de la simulacion\n\n");
}

**/