// Problema 1. Escriba un programa que identique si un carácter ingresado es una vocal, una consonante o ninguna de las 2 e imprima un mensaje según el caso.
#include <iostream>

using namespace std;

int main() {
    char letra;
    
    cout << "Ingrese un caracter: ";
    cin >> letra;
    cout << endl;
    
    if (letra >= 'A' && letra <= 'Z') {
        letra = letra + 32; // Convertir a minúscula
    }

    cout << "El caracter ingresado '" << letra << "':";

    switch (letra) {
        case 'a': case 'e': case 'i': case 'o': case 'u':
            cout << " es una vocal." << endl;
            break;
        default:
            if ((letra >= 'b' && letra <= 'z') && letra != 'e' && letra != 'i' && letra != 'o' && letra != 'u') {
                cout << " es una consonante." << endl;
            } else {
                cout << " no es una letra." << endl;
            }
    }

    return 0;
}