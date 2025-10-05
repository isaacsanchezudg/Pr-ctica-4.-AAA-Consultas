
// Deportista.h
#ifndef DEPORTISTA_H
#define DEPORTISTA_H

#include <string>
using std::string;

class Deportista
{
public:
    // constructor
    Deportista(int = 0, string = "", int = 0, string = "");

    // numero de socio
    void establecerNumeroSocio(int);
    int obtenerNumeroSocio() const;

    // nombre
    void establecerNombre(string);
    string obtenerNombre() const;

    // edad
    void establecerEdad(int);
    int obtenerEdad() const;

    // deporte
    void establecerDeporte(string);
    string obtenerDeporte() const;

private:
    int numeroSocio;
    char nombre[15];
    int edad;
    char deporte[15];
};

#endif
