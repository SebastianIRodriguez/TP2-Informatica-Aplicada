#include <iostream>
#include <queue>
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
        cin >> c;

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

        Estado *nuevo_estado = NULL;

        switch(estado_actual->get_etiqueta()) {
            case REPOSO:
                // El jugador 1 presiona el botón por primera vez
                if(boton == 0) {
                    nuevo_estado = new Turno_J1_Boton_Pulsado();
                }
                break;

            case TURNO_J1_BOTON_PULSADO:
                // Si el jugador 1 suelta el botón
                if(boton == 1 && fin == 0) {
                    nuevo_estado = new Turno_J1();
                }
                // Se le termina el tiempo al jugador 1
                if(boton == 0 && fin == 1) {
                    nuevo_estado = new Termina_Tiempo_J1();
                }
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TURNO_J1:
                //El jugador 2 presiona el botón
                if(boton == 0 && fin == 0) {
                    nuevo_estado = new Turno_J2_Boton_Pulsado();
                }
                if(boton == 0 && fin == 1) {
                    nuevo_estado = new Termina_Tiempo_J2();
                }
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TURNO_J2_BOTON_PULSADO:
                //El jugador 2 suelta el botón
                if(boton == 1 && fin == 0) {
                    nuevo_estado = new Turno_J2();
                }
                //Se le termina el tiempo al jugador 2
                if(boton == 0 && fin == 1) {
                    nuevo_estado = new Termina_Tiempo_J2();
                }
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TURNO_J2:
                //El jugador 1 vuelve a presionar el boton
                if(boton == 0 && fin == 0) {
                    nuevo_estado = new Turno_J1_Boton_Pulsado();
                }
                if(boton == 0 && fin == 1) {
                    nuevo_estado = new Termina_Tiempo_J1();
                }
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TERMINA_TIEMPO_J1:
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TERMINA_TIEMPO_J2:
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            default:
                break;
        }

        if(nuevo_estado != NULL) {
            delete estado_actual;
            estado_actual = nuevo_estado;
            estado_actual->imprimir_estado();
        }
    }
    cout << "\nFin de la simulacion\n" << endl;
}

void _correr_simulacion(queue<Evento> cola)
{
    Estado *estado_actual = new Reposo();

    estado_actual->imprimir_estado();

    bool boton, fin;

    while (!cola.empty())
    {
        Evento medicion = cola.front();
        cola.pop();
        boton = medicion.get_boton();
        fin = medicion.get_fin();

        Estado *nuevo_estado = NULL;

        switch(estado_actual->get_etiqueta()) {
            case REPOSO:
                // El jugador 1 presiona el botón por primera vez
                if(boton == 0) {
                    nuevo_estado = new Turno_J1_Boton_Pulsado();
                }
                break;

            case TURNO_J1_BOTON_PULSADO:
                // Si el jugador 1 suelta el botón
                if(boton == 1 && fin == 0) {
                    nuevo_estado = new Turno_J1();
                }
                // Se le termina el tiempo al jugador 1
                if(boton == 0 && fin == 1) {
                    nuevo_estado = new Termina_Tiempo_J1();
                }
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TURNO_J1:
                //El jugador 2 presiona el botón
                if(boton == 0 && fin == 0) {
                    nuevo_estado = new Turno_J2_Boton_Pulsado();
                }
                if(boton == 0 && fin == 1) {
                    nuevo_estado = new Termina_Tiempo_J2();
                }
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TURNO_J2_BOTON_PULSADO:
                //El jugador 2 suelta el botón
                if(boton == 1 && fin == 0) {
                    nuevo_estado = new Turno_J2();
                }
                //Se le termina el tiempo al jugador 2
                if(boton == 0 && fin == 1) {
                    nuevo_estado = new Termina_Tiempo_J2();
                }
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TURNO_J2:
                //El jugador 1 vuelve a presionar el boton
                if(boton == 0 && fin == 0) {
                    nuevo_estado = new Turno_J1_Boton_Pulsado();
                }
                if(boton == 0 && fin == 1) {
                    nuevo_estado = new Termina_Tiempo_J1();
                }
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TERMINA_TIEMPO_J1:
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            case TERMINA_TIEMPO_J2:
                //Reset
                if(boton == 1 && fin == 1) {
                    nuevo_estado = new Reposo();
                }
                break;

            default:
                break;
        }

        cout << "Boton: "<< boton <<"  Fin: \n" << fin << "\t\t";

        if(nuevo_estado != NULL) {
            delete estado_actual;
            estado_actual = nuevo_estado;
            estado_actual->imprimir_estado();
        }
    }
    cout << "\nFin de la simulacion\n" << endl;
}


queue<Evento>* crear_cola_eventos(int cant_eventos) {
    queue<Evento>* cola = new queue<Evento>();
    for(int i = 0; i < cant_eventos; i++) {
        Evento evento(rand() % 2, rand() % 2, NULL);
        cola->push(evento);
    }
    return cola;
}

int _main()
{
    int c_eventos;
    bool imprimir = false;

    setbuf(stdout, 0);

    // Utilizar diferente semilla en cada llamada a rand()
    srand(time(NULL));

    cout << "\n\n\tBienvenido a la simulacion de ajedrez\n" << endl;
    cout << "  Desea ver las listas de eventos aleatorios que se generen? \n  Aplica a todas las simulaciones\n" << endl;

    if (recibir_entrada() == 'S')
        imprimir = true;

    while (true)
    {
        cout << "Ingrese la cantidad de eventos aleatorios que desea crear: " << endl;

        // Leemos la cantidad de eventos
        cin >> c_eventos;

        // Creamos la lista
        Lista_Enlazada *lista = new Lista_Enlazada(c_eventos);
        queue<Evento> *_lista = crear_cola_eventos(c_eventos);

        if (imprimir)
            lista->imprimir_lista();

        _correr_simulacion(*_lista);

        delete lista;
        delete _lista;

        cout << "Desea realizar otra simulacion?" << endl;

        if (recibir_entrada() == 'N')
            break;
    }

    return 0;
}

  void resta(queue<int> myqueue)
  {
    myqueue.front() -= myqueue.back();    // 77-16=61
    std::cout << "myqueue.front() is now " << myqueue.front() << '\n';
  }


int main ()
{
  std::queue<int> myqueue;
  
  myqueue.push(77);
  myqueue.push(16);

  const std::queue<int> cola = myqueue;

  myqueue.front() = 82;    // 77-16=61

  std::cout << "myqueue.front() is now " << myqueue.front() << '\n';

  return 0;
}

/*

Volar a la mierda la clase Lista_Enlazada y reemplazarlo por std::queue
    - Medición dejaría de existir
    
Reemplazar los if en la parte de la maquina de estados con switch/case      - LISTO
Usar cin en vez de scanf y getchar                                          - LISTO
Las salidas deberian verse exactamente igual que en el enunciado            - WTF
No podemos tener el algoritmo principal dentro de la funcion global main, hay que meterlo dentro de una clase Context


*/