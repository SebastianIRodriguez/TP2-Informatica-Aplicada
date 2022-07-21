/*
En este archivo header definimos las clases utilizadas
en el patrón State
*/
#ifndef ESTADOS
#define ESTADOS

enum Etiqueta
{
    REPOSO,
    TURNO_J1_BOTON_PULSADO,
    TURNO_J1,
    TERMINA_TIEMPO_J1,
    TURNO_J2_BOTON_PULSADO,
    TURNO_J2,
    TERMINA_TIEMPO_J2,
};

class Estado
{
public:
    virtual ~Estado() {}
    virtual Etiqueta get_etiqueta() = 0;
    virtual void handle() = 0;
};

class Reposo : public Estado
{
public:
    ~Reposo() {}
    Etiqueta get_etiqueta() { return REPOSO; }
    void handle()
    {
    }
};

class Turno_J1_Boton_Pulsado : public Estado
{
public:
    ~Turno_J1_Boton_Pulsado() {}
    Etiqueta get_etiqueta() { return TURNO_J1_BOTON_PULSADO; }
    void handle()
    {
    }
};

class Turno_J1 : public Estado
{
public:
    ~Turno_J1() {}
    Etiqueta get_etiqueta() { return TURNO_J1; }
    void handle()
    {
    }
};

class Turno_J2_Boton_Pulsado : public Estado
{
public:
    ~Turno_J2_Boton_Pulsado() {}
    Etiqueta get_etiqueta() { return TURNO_J2_BOTON_PULSADO; }
    void handle()
    {
    }
};

class Turno_J2 : public Estado
{
public:
    ~Turno_J2() {}
    Etiqueta get_etiqueta() { return TURNO_J2; }
    void handle()
    {
    }
};

class Termina_Tiempo_J1 : public Estado
{
public:
    ~Termina_Tiempo_J1() {}
    Etiqueta get_etiqueta() { return TERMINA_TIEMPO_J1; }
    void handle()
    {
    }
};

class Termina_Tiempo_J2 : public Estado
{
public:
    ~Termina_Tiempo_J2() {}
    Etiqueta get_etiqueta() { return TERMINA_TIEMPO_J2; }
    void handle()
    {
    }
};

#endif