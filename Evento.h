/*
Clase donde almacenamos el estado simulado del cronometro en un instante de
*/
#ifndef EVENTOS
#define EVENTOS

class Evento
{
private:
    bool boton;
    bool fin;

public:
    Evento(bool boton, bool fin)
    {
        this->boton = boton;
        this->fin = fin;
    }

    bool get_boton()
    {
        return boton;
    }

    bool get_fin()
    {
        return fin;
    }
};

#endif