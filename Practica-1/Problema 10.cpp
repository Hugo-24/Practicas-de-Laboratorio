#include <iostream>
using namespace std;

/*
    Problema 10. Escriba un programa que reciba un número n e imprima el enésimo número primo.
*/

int main() {
    int x, ctd = 0, aux = 2; 
    bool bandera;
    
    cout << "Ingrese el número: ";
    cin >> x;
    
    while (ctd < x) {
        bandera = true;
        for (int i = 2; i * i <= aux; i++) {
            if (aux % i == 0) {
                bandera = false;
                break;
            }
        }
        if (bandera) {
            ctd++;
            if (ctd == x) {
                cout << "El primo número " << x << " es: " << aux << endl;
                return 0;
            }
        }
        aux++;
    }
    
    return 0;
}
