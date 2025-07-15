#include <iostream>
using namespace std;

// Función que compara dos cadenas de caracteres
bool sonIguales(const char* cadena1, const char* cadena2);

int main() {
    char cadena1[20];
    char cadena2[20];

    cout << "Ingrese la primera cadena: ";
    cin.getline(cadena1, 20);
    //cin.getline() permite leer una línea completa de texto (incluyendo espacios)hasta encontrar un salto de línea (\n), lo almacena en un arreglo de caracteres (char[]).
    cout << "Ingrese la segunda cadena: ";
    cin.getline(cadena2,20);

    if (sonIguales(cadena1, cadena2)) {
        cout << "Las cadenas son iguales." << endl;
    } else {
        cout << "Las cadenas son diferentes." << endl;
    }

    return 0;
}

bool sonIguales(const char* cadena1, const char* cadena2) {
    int i = 0;

    while (cadena1[i] != '\0' && cadena2[i] != '\0') {
        if (cadena1[i] != cadena2[i]) {
            return false; // Caracteres diferentes
        }
        i++;
    }
    // Si ambas terminaron al mismo tiempo, son iguales
    return cadena1[i] == '\0' && cadena2[i] == '\0';
}
