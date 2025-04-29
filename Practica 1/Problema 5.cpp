#include <iostream>
using namespace std;

/*
    Problema 5. Escriba un programa que muestre el siguiente patrón en la pantalla:
*/

int main() {
    signed int x;
    while (true) {
        cout << "Ingrese un entero positivo impar para imprimir un patrón de asteriscos en la pantalla: ";
        cin >> x;
        cout << endl;

        if (x % 2 != 0) {
            for (short int i = 1; i <= x; i += 2) {
                for (short int j = i; j < x; j += 2) {
                    cout << " ";
                }
                for (short int k = 0; k < i; k++) {
                    cout << "*";
                }
                cout << endl;
            }
            for (short int i = x - 2; i >= 1; i -= 2) {
                for (short int j = i; j < x; j += 2) {
                    cout << " ";
                }
                for (short int k = 0; k < i; k++) {
                    cout << "*";
                }
                cout << endl;
            }
            break;
        } else {
            cout << "Por favor ingrese un número impar." << endl;
        }
    }

    return 0;
}