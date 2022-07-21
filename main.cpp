#include <iostream>
#include <queue>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estados.h"
#include "Evento.h"

class SimuladorCronometro {

public:

    void correr_simulacion(queue<Evento> cola)
    {
        Estados estado_actual = REPOSO;

        bool boton = 1;
        bool fin = 1;

        cout << "Estado inicial: \tBoton: "<< boton <<"  Fin: " << fin << "\t";

        cout << "Relevante\tCronometro en reposo: \t\t\t ENA1 = 0 ENA2 = 0" << endl;

        while (!cola.empty())
        {
            Evento medicion = cola.front();
            cola.pop();
            boton = medicion.get_boton();
            fin = medicion.get_fin();

            Estados nuevo_estado = estado_actual;

            cout << "\t\t\tBoton: " << boton << "  Fin: " << fin << "\t";

            switch(estado_actual) {

                case REPOSO:
                    // El jugador 1 presiona el botón por primera vez
                    if(boton == 0) {
                        nuevo_estado = TURNO_J1_BOTON_PULSADO;
                    }
                    break;

                case TURNO_J1_BOTON_PULSADO:
                    // Si el jugador 1 suelta el botón
                    if(boton == 1 && fin == 0) {
                        nuevo_estado = TURNO_J1;
                    }
                    // Se le termina el tiempo al jugador 1
                    if(boton == 0 && fin == 1) {
                        nuevo_estado = TERMINA_TIEMPO_J1;
                    }
                    //Reset
                    if(boton == 1 && fin == 1) {
                        nuevo_estado = REPOSO;
                    }
                    break;

                case TURNO_J1:
                    //El jugador 2 presiona el botón
                    if(boton == 0 && fin == 0) {
                        nuevo_estado = TURNO_J2_BOTON_PULSADO;
                    }
                    if(boton == 0 && fin == 1) {
                        nuevo_estado = TERMINA_TIEMPO_J2;
                    }
                    //Reset
                    if(boton == 1 && fin == 1) {
                        nuevo_estado = REPOSO;
                    }
                    break;

                case TURNO_J2_BOTON_PULSADO:
                    //El jugador 2 suelta el botón
                    if(boton == 1 && fin == 0) {
                        nuevo_estado = TURNO_J2;
                    }
                    //Se le termina el tiempo al jugador 2
                    if(boton == 0 && fin == 1) {
                        nuevo_estado = TERMINA_TIEMPO_J2;
                    }
                    //Reset
                    if(boton == 1 && fin == 1) {
                        nuevo_estado = REPOSO;
                    }
                    break;

                case TURNO_J2:
                    //El jugador 1 vuelve a presionar el boton
                    if(boton == 0 && fin == 0) {
                        nuevo_estado = TURNO_J1_BOTON_PULSADO;
                    }
                    if(boton == 0 && fin == 1) {
                        nuevo_estado = TERMINA_TIEMPO_J1;
                    }
                    //Reset
                    if(boton == 1 && fin == 1) {
                        nuevo_estado = REPOSO;
                    }
                    break;

                case TERMINA_TIEMPO_J1:
                    //Reset
                    if(boton == 1 && fin == 1) {
                        nuevo_estado = REPOSO;
                    }
                    break;

                case TERMINA_TIEMPO_J2:
                    //Reset
                    if(boton == 1 && fin == 1) {
                        nuevo_estado = REPOSO;
                    }
                    break;

                default:
                    break;
            }

            if(nuevo_estado == estado_actual)
            {
                cout << "No modifica\t";
            }
            else
            {
                cout << "Relevante\t";
                estado_actual = nuevo_estado;
            }

            imprimir_estado(estado_actual);

        }
        cout << "\nFin de la simulacion\n" << endl;
    }

private:

    void imprimir_estado(Estados estado) {
        switch(estado) {

            case REPOSO:
                cout << "Cronometro en reposo: \t\t\t ENA1 = 0 ENA2 = 0" << endl;
                break;

            case TURNO_J1_BOTON_PULSADO:
                cout << "Tiempo 1 corriendo con boton apretado:   ENA1 = 1 ENA2 = 0" << endl;
                break;

            case TURNO_J1:
                cout << "Tiempo 1 corriendo sin apretar boton:    ENA1 = 1 ENA2 = 0" << endl;
                break;

            case TURNO_J2_BOTON_PULSADO:
                cout << "Tiempo 2 corriendo con boton apretado:   ENA1 = 0 ENA2 = 1" << endl;
                break;

            case TURNO_J2:
                cout << "Tiempo 2 corriendo sin apretar boton:    ENA1 = 0 ENA2 = 1" << endl;
                break;

            case TERMINA_TIEMPO_J1:
                cout << "Fin del tiempo 1" << endl;
                break;

            case TERMINA_TIEMPO_J2:
                cout << "Fin del tiempo 2" << endl;
                break;

            default:
                break;
        }
    }
};

char recibir_entrada()
{
    /**
    Funcion que itera hasta recibir una entrada valida S o N.

    Si se ingresa S, se repetira la simulacion.
    Si se ingresa N, se finaliza la ejecucion del programa.

    recibir_entrada() retorna el caracter 'S' o 'N' ingresado.
    */

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

queue<Evento>* crear_cola_eventos(int cant_eventos) {
    queue<Evento>* cola = new queue<Evento>();
    for(int i = 0; i < cant_eventos; i++) {
        Evento evento(rand() % 2, rand() % 2);
        cola->push(evento);
    }
    return cola;
}

int main() {
    int c_eventos;
    SimuladorCronometro cronometro;

    setbuf(stdout, 0);

    // Utilizar diferente semilla en cada llamada a rand()
    srand(time(NULL));

    cout << "\n\n\tBienvenido a la simulacion de ajedrez\n" << endl;

    while (true)
    {
        cout << "Ingrese la cantidad de eventos aleatorios que desea crear: " ;

        // Leemos la cantidad de eventos
        cin >> c_eventos;

        // Creamos la lista
        queue<Evento> *lista = crear_cola_eventos(c_eventos);

        cronometro.correr_simulacion(*lista);

        delete lista;

        cout << "Desea realizar otra simulacion?" << endl;

        if (recibir_entrada() == 'N')
            break;
    }

    return 0;
}