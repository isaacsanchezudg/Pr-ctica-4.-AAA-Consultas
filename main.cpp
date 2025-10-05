#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "Deportista.h"

using namespace std;

void mostrarMenu();
void consultaIndividual(fstream& archivo);
void consultaGeneral(fstream& archivo);
void agregarDeportistas();

int main() {
    int opcion;

    do {
        mostrarMenu();
        cout << "Elige tu opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                fstream archivo("deportistas.dat", ios::binary | ios::in);
                if (archivo) {
                    consultaIndividual(archivo);
                    archivo.close();
                } else {
                    cout << "No existe el archivo deportistas.dat" << endl;
                }
                break;
            }
            case 2: {
                fstream archivo("deportistas.dat", ios::binary | ios::in);
                if (archivo) {
                    consultaGeneral(archivo);
                    archivo.close();
                } else {
                    cout << "No existe el archivo deportistas.dat" << endl;
                }
                break;
            }
            case 3:
                agregarDeportistas();
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }

        cout << endl;

    } while (opcion != 4);

    return 0;
}

void mostrarMenu() {
    cout << "MENU - ASOCIACION DE DEPORTISTAS TAPATIOS" << endl;
    cout << "1. Consulta individual" << endl;
    cout << "2. Consultas generales" << endl;
    cout << "3. Agregar deportistas" << endl;
    cout << "4. Salir" << endl;
}

void consultaIndividual(fstream& archivo) {
    int numeroSocio;
    cout << "Numero de socio: ";
    cin >> numeroSocio;

    if (numeroSocio < 1 || numeroSocio > 100) {
        cout << "Numero no valido" << endl;
        return;
    }

    Deportista d;
    archivo.seekg((numeroSocio - 1) * sizeof(Deportista));
    archivo.read(reinterpret_cast<char*>(&d), sizeof(Deportista));

    if (archivo && d.obtenerNumeroSocio() == numeroSocio) {
        cout << "NUM DE SOCIO: " << d.obtenerNumeroSocio() << endl;
        cout << "NOMBRE: " << d.obtenerNombre() << endl;
        cout << "EDAD: " << d.obtenerEdad() << endl;
        cout << "DEPORTE: " << d.obtenerDeporte() << endl;
    } else {
        cout << "EL NUMERO DE SOCIO NO EXISTE" << endl;
    }

    archivo.clear();
}

void consultaGeneral(fstream& archivo) {
    Deportista d;
    archivo.seekg(0, ios::beg);

    cout << "NUM SOCIO   NOMBRE    EDAD    DEPORTE" << endl;
    cout << "-------------------------------------" << endl;

    while (archivo.read(reinterpret_cast<char*>(&d), sizeof(Deportista))) {
        if (d.obtenerNumeroSocio() > 0) {
            cout << setw(8) << d.obtenerNumeroSocio() << "   "
                 << setw(8) << d.obtenerNombre() << "   "
                 << setw(4) << d.obtenerEdad() << "    "
                 << setw(10) << d.obtenerDeporte() << endl;
        }
    }

    archivo.clear();
}

void agregarDeportistas() {
    fstream archivo("deportistas.dat", ios::out | ios::binary | ios::in);

    if (!archivo) {
        archivo.open("deportistas.dat", ios::out | ios::binary);
        archivo.close();
        archivo.open("deportistas.dat", ios::out | ios::binary | ios::in);
    }

    if (!archivo) {
        cout << "Error al abrir archivo" << endl;
        return;
    }

    int numeroSocio;
    string nombre;
    int edad;
    string deporte;

    cout << "Numero de socio (1-100, 0 para terminar): ";
    cin >> numeroSocio;

    Deportista deportista;

    while (numeroSocio > 0 && numeroSocio <= 100) {
        cout << "Nombre edad deporte: ";
        cin >> nombre >> edad >> deporte;

        deportista.establecerNumeroSocio(numeroSocio);
        deportista.establecerNombre(nombre);
        deportista.establecerEdad(edad);
        deportista.establecerDeporte(deporte);

        archivo.seekp((numeroSocio - 1) * sizeof(Deportista));
        archivo.write(reinterpret_cast<const char*>(&deportista), sizeof(Deportista));

        cout << "Numero de socio (1-100, 0 para terminar): ";
        cin >> numeroSocio;
    }

    archivo.close();
    cout << "Datos guardados" << endl;
}
