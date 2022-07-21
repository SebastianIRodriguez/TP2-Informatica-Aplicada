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
        cout << "Cronometro en reposo: \t\t\t ENA1 = 0 ENA2 = 0\t\t" << endl;
    }
};

class Turno_J1_Boton_Pulsado : public Estado
{
public:
    ~Turno_J1_Boton_Pulsado() {}
    Etiqueta get_etiqueta() { return TURNO_J1_BOTON_PULSADO; }
    void handle()
    {
        cout << "Tiempo 1 corriendo con boton apretado:   ENA1 = 1 ENA2 = 0\t\t" << endl;
    }
};

class Turno_J1 : public Estado
{
public:
    ~Turno_J1() {}
    Etiqueta get_etiqueta() { return TURNO_J1; }
    void handle()
    {
        cout << "Tiempo 1 corriendo sin apretar boton:    ENA1 = 1 ENA2 = 0\t\t" << endl;
    }
};

class Turno_J2_Boton_Pulsado : public Estado
{
public:
    ~Turno_J2_Boton_Pulsado() {}
    Etiqueta get_etiqueta() { return TURNO_J2_BOTON_PULSADO; }
    void handle()
    {
        cout << "Tiempo 2 corriendo con boton apretado:   ENA1 = 0 ENA2 = 1\t\t" << endl;
    }
};

class Turno_J2 : public Estado
{
public:
    ~Turno_J2() {}
    Etiqueta get_etiqueta() { return TURNO_J2; }
    void handle()
    {
        cout << "Tiempo 2 corriendo sin apretar boton:    ENA1 = 0 ENA2 = 1\t\t" << endl;
    }
};

class Termina_Tiempo_J1 : public Estado
{
public:
    ~Termina_Tiempo_J1() {}
    Etiqueta get_etiqueta() { return TERMINA_TIEMPO_J1; }
    void handle()
    {
        cout << "Fin del tiempo 1" << endl;
    }
};

class Termina_Tiempo_J2 : public Estado
{
public:
    ~Termina_Tiempo_J2() {}
    Etiqueta get_etiqueta() { return TERMINA_TIEMPO_J2; }
    void handle()
    {
        cout << "Fin del tiempo 2" << endl;
    }
};

#endif