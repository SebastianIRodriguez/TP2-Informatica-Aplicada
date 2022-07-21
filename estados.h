/*
En este archivo header definimos las clases utilizadas
en el patrón State
*/
#ifndef ESTADOS
#define ESTADOS

enum Estados
{
    REPOSO,
    TURNO_J1_BOTON_PULSADO,
    TURNO_J1,
    TERMINA_TIEMPO_J1,
    TURNO_J2_BOTON_PULSADO,
    TURNO_J2,
    TERMINA_TIEMPO_J2,
};

#endif