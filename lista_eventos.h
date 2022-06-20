/*
En este archivo header definimos las clases utilizadas
en el manejo de la lista enlazada
*/

class Mediciones
{
public:
    virtual bool get_boton() = 0;
    virtual bool get_fin() = 0;
};

class Evento : public Mediciones
{
private:
    bool boton;
    bool fin;

public:
    Evento *sig;

    Evento(bool boton, bool fin, Evento *sig)
    {
        this->boton = boton;
        this->fin = fin;
        this->sig = sig;
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

class Lista_Enlazada
{
private:
    Evento *cabecera;
    Evento *nodo_actual;

    // Crea una lista de eventos del largo adecuado, con informacion generada en forma aleatoria, en forma recursiva
    Evento *crear_lista_eventos(int cantidad)
    {
        return new Evento(rand() % 2, rand() % 2, (cantidad > 1) ? crear_lista_eventos(cantidad - 1) : NULL);
    }

    /*
     * Función recursiva que toma como parámetro un puntero a un evento de la lista,
     * si no es el último se llama a si misma pasando como parámetro el puntero al próximo elemento.
     * De esta forma se va liberando la memoria desde el ultimo elemento al primero.
     */
    void liberar_memoria(Evento *evento)
    {
        if (evento->sig != NULL)
        {
            liberar_memoria(evento->sig);
        }
        free(evento);
    }

public:
    Lista_Enlazada(int largo)
    {
        cabecera = crear_lista_eventos(largo);
        nodo_actual = cabecera;
    }

    ~Lista_Enlazada()
    {
        liberar_memoria(cabecera);
    }

    // Imprime la lista de eventos generados con los valores de los sensores asociados a cada evento.
    void imprimir_lista()
    {
        Evento *p = cabecera;
        while (p->sig != NULL)
        {
            cout << "Boton:" << p->get_boton() << " Fin:" << p->get_fin() << endl;
            p = p->sig;
        }
        cout << "Boton:" << p->get_boton() << " Fin:" << p->get_fin() << endl;
    }

    //Retorna el nodo actual y avanza una posicion en la lista
    Mediciones *get_nodo()
    {
        Evento *aux = nodo_actual;

        if (nodo_actual != NULL)
            nodo_actual = aux->sig;

        return aux;
    }
};
