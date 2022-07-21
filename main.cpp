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
        Etiqueta estado_actual = REPOSO;

        bool boton, fin;

        cout << "Boton: "<< boton <<"  Fin: " << fin << "\t" << "Relevante  \t";

        cout << "Cronometro en reposo: \t\t\t ENA1 = 0 ENA2 = 0\t\t" << endl;

        while (!cola.empty())
        {
            Evento medicion = cola.front();
            cola.pop();
            boton = medicion.get_boton();
            fin = medicion.get_fin();

            Etiqueta nuevo_estado = estado_actual;

            cout << "Boton: " << boton << "  Fin: " << fin << "\t";

            switch(estado_actual) {

                case REPOSO:
                    cout << "Cronometro en reposo: \t\t\t ENA1 = 0 ENA2 = 0\t";
                    // El jugador 1 presiona el botón por primera vez
                    if(boton == 0) {
                        nuevo_estado = TURNO_J1_BOTON_PULSADO;
                    }
                    break;

                case TURNO_J1_BOTON_PULSADO:
                    cout << "Tiempo 1 corriendo con boton apretado:   ENA1 = 1 ENA2 = 0\t";
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
                    cout << "Tiempo 1 corriendo sin apretar boton:    ENA1 = 1 ENA2 = 0\t";
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
                    cout << "Tiempo 2 corriendo con boton apretado:   ENA1 = 0 ENA2 = 1\t";
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
                    cout << "Tiempo 2 corriendo sin apretar boton:    ENA1 = 0 ENA2 = 1\t";
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
                    cout << "Fin del tiempo 1\t\t\t\t\t\t";
                    //Reset
                    if(boton == 1 && fin == 1) {
                        nuevo_estado = REPOSO;
                    }
                    break;

                case TERMINA_TIEMPO_J2:
                    cout << "Fin del tiempo 2\t\t\t\t\t\t";
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
                cout << "No modifica\n";
            }
            else
            {
                cout << "Relevante\n";
                estado_actual = nuevo_estado;
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
};

int main() {
    SimuladorCronometro cronometro;
    cronometro.exec();

    return 0;
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