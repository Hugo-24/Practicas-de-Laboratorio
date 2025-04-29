#include <iostream>
using namespace std;

/*
    Problema 8. Escriba un programa que reciba 3 números a, b, c, y calcule la suma de todos los 
    múltiplos de a y b que sean menores a c. Tenga en cuenta no sumar 2 veces los múltiplos comunes.
*/

int main() {
    int a, b, c, multiplo;
    int ctd1 = 1, ctd2 = 1;
    int sumatoria = 0;
    bool bandera = true;

    cout << "Introduce a: ";
    cin >> a;
    cout << "Introduce b: ";
    cin >> b;
    cout << "Introduce c: ";
    cin >> c;

    multiplo = a * ctd1;
    while (multiplo < c) {
        sumatoria += multiplo;
        cout << multiplo << " + ";
        ctd1 += 1;
        multiplo = a * ctd1;
    }

    multiplo = b * ctd2;
    while (multiplo < c) {
        for (int i = 1; i <= ctd1; i++) {
            if (a * i == multiplo) {
                bandera = false;
            }
        }
        if (bandera == true) {
            sumatoria += multiplo;
            cout << multiplo << " + ";
        } else {
            bandera = true;
        }
        ctd2 += 1;
        multiplo = b * ctd2;
    }

    cout << " = " << sumatoria;
    return 0;
}