#include <iostream>
using namespace std;

/*
    Problema 6. Escriba un programa que encuentre el valor aproximado del número de Euler en base a la siguiente suma infinita.
*/

int main() {
    int x, factorial;
    double resultado = 0;

    cout << "Introduce el número de términos a considerar en la serie: ";
    cin >> x;

    for (int i = 0; i < x; i++) {
        if (i == 0) {
            factorial = 1;
        } else {
            factorial *= i;
        }

        resultado += 1.0 / factorial;
    }

    cout << "e es aproximadamente: " << resultado << endl;

    return 0;
}