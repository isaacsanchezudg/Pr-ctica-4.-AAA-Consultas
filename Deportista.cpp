
// Deportista.cpp
#include "Deportista.h"
#include <cstring>

Deportista::Deportista(int ns, string nom, int ed, string dep) {
    establecerNumeroSocio(ns);
    establecerNombre(nom);
    establecerEdad(ed);
    establecerDeporte(dep);
}

void Deportista::establecerNumeroSocio(int ns) {
    numeroSocio = ns;
}

int Deportista::obtenerNumeroSocio() const {
    return numeroSocio;
}

void Deportista::establecerNombre(string nom) {
    int longitud = nom.size();
    longitud = (longitud < 15 ? longitud : 14);
    strncpy(nombre, nom.c_str(), longitud);
    nombre[longitud] = '\0';
}

string Deportista::obtenerNombre() const {
    return string(nombre);
}

void Deportista::establecerEdad(int ed) {
    edad = ed;
}

int Deportista::obtenerEdad() const {
    return edad;
}

void Deportista::establecerDeporte(string dep) {
    int longitud = dep.size();
    longitud = (longitud < 15 ? longitud : 14);
    strncpy(deporte, dep.c_str(), longitud);
    deporte[longitud] = '\0';
}

string Deportista::obtenerDeporte() const {
    return string(deporte);
}
