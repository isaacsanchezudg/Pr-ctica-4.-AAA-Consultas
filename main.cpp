
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "Deportista.h"

using namespace std;

void mostrarMenu();
void consultaIndividual(fstream& archivo);
void consultaGeneral(fstream& archivo);

int main() {
    fstream archivoDeportistas;

    // Abrir archivo en modo binario y lectura
    archivoDeportistas.open("deportistas.dat", ios::binary | ios::in);

    if (!archivoDeportistas) {
        cout << "Error: No se pudo abrir el archivo deportistas.dat" << endl;
        cout << "Asegúrate de que el archivo existe y tiene datos." << endl;
        return 1;
    }

    int opcion;

    do {
        mostrarMenu();
        cout << "Elige tu opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                consultaIndividual(archivoDeportistas);
                break;
            case 2:
                consultaGeneral(archivoDeportistas);
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }

        cout << endl; // línea en blanco para separar

    } while (opcion != 3);

    archivoDeportistas.close();
    return 0;
}

void mostrarMenu() {
    cout << "\nMENÚ - ASOCIACION DE DEPORTISTAS TAPATIOS" << endl;
    cout << "1. Consulta individual (número de socio)" << endl;
    cout << "2. Consultas generales (en formato de tabla)" << endl;
    cout << "3. Salir" << endl;
}

void consultaIndividual(fstream& archivoDeportistas) {
    int numeroSocio;
    cout << "Teclea el número de socio del deportista: ";
    cin >> numeroSocio;

    if (numeroSocio < 1 || numeroSocio > 100) {
        cout << "EL NÚMERO DE SOCIO NO EXISTE ..." << endl;
        return;
    }

    Deportista d;

    // Buscar la posición en el archivo del registro especificado
    archivoDeportistas.seekg((numeroSocio - 1) * sizeof(Deportista));

    // Leer la información específicada por el usuario en el archivo
    archivoDeportistas.read(reinterpret_cast<char*>(&d), sizeof(Deportista));

    // Verificar si el registro existe (tiene número de socio válido)
    if (archivoDeportistas && d.obtenerNumeroSocio() == numeroSocio) {
        // Mostrar información del deportista
        cout << "NUM DE SOCIO: " << d.obtenerNumeroSocio() << endl;
        cout << "NOMBRE    : " << d.obtenerNombre() << endl;
        cout << "EDAD    : " << d.obtenerEdad() << endl;
        cout << "DEPORTE    : " << d.obtenerDeporte() << endl;
    } else {
        cout << "EL NÚMERO DE SOCIO NO EXISTE ..." << endl;
    }

    // Limpiar flags de error para futuras operaciones
    archivoDeportistas.clear();
}

void consultaGeneral(fstream& archivoDeportistas) {
    Deportista d;

    // Regresar al inicio del archivo
    archivoDeportistas.seekg(0, ios::beg);

    // Encabezados de la tabla
    cout << "\nNUM SOCIO   NOMBRE        EDAD    DEPORTE" << endl;
    cout << "------------------------------------------" << endl;

    // Leer todos los registros
    while (archivoDeportistas.read(reinterpret_cast<char*>(&d), sizeof(Deportista))) {
        // Solo mostrar registros válidos (con número de socio > 0)
        if (d.obtenerNumeroSocio() > 0) {
            cout << setw(8) << d.obtenerNumeroSocio() << "   "
                 << setw(12) << d.obtenerNombre() << "   "
                 << setw(4) << d.obtenerEdad() << "    "
                 << setw(12) << d.obtenerDeporte() << endl;
        }
    }

    // Limpiar flags de error y regresar al inicio para futuras operaciones
    archivoDeportistas.clear();
}
