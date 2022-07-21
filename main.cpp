#include <iostream>
#include <queue>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estados.h"
#include "Evento.h"

class SimuladorCronometro {

private:
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

    void correr_simulacion(queue<Evento> cola)
    {
        Estado *estado_actual = new Reposo();

        bool boton, fin;

        cout << "Boton: "<< boton <<"  Fin: " << fin << "\t" << "Relevante  \t";

        estado_actual->handle();

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

            if(nuevo_estado == NULL) 
            {
                cout << "No modifica \t";
                estado_actual->handle();
            }
            else
            {
                cout << "Relevante  \t";
                delete estado_actual;
                estado_actual = nuevo_estado;
                estado_actual->handle();
            }
        }
        cout << "\nFin de la simulacion\n" << endl;
    }


    queue<Evento>* crear_cola_eventos(int cant_eventos) {
        queue<Evento>* cola = new queue<Evento>();
        for(int i = 0; i < cant_eventos; i++) {
            Evento evento(rand() % 2, rand() % 2);
            cola->push(evento);
        }
        return cola;
    }

public:

    void exec()
    {
        int c_eventos;

        setbuf(stdout, 0);

        // Utilizar diferente semilla en cada llamada a rand()
        srand(time(NULL));

        cout << "\n\n\tBienvenido a la simulacion de ajedrez\n" << endl;

        while (true)
        {
            cout << "Ingrese la cantidad de eventos aleatorios que desea crear: " << endl;

            // Leemos la cantidad de eventos
            cin >> c_eventos;

            // Creamos la lista
            queue<Evento> *lista = crear_cola_eventos(c_eventos);

            correr_simulacion(*lista);

            delete lista;

            cout << "Desea realizar otra simulacion?" << endl;

            if (recibir_entrada() == 'N')
                break;
        }
    }
}

int main() {
    SimuladorCronometro cronometro;
    cronometro.exec();
}

/*

Volar a la mierda la clase Lista_Enlazada y reemplazarlo por std::queue     - LISTO
    - Medición dejaría de existir
    
Reemplazar los if en la parte de la maquina de estados con switch/case      - LISTO
Usar cin en vez de scanf y getchar                                          - LISTO
Las salidas deberian verse exactamente igual que en el enunciado            - LISTO
Con cronómetro en reposo las dos salidas deben estar en cero                - LISTO
No podemos tener el algoritmo principal dentro de la funcion global main,   - LISTO
hay que meterlo dentro de una clase Context
Ver métodos handle()                                                        - LISTO


*/