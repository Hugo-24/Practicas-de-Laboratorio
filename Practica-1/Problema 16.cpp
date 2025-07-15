/*
    Problema 16. La serie de Collatz se conforma con la siguiente regla:
    Si n es par, el siguiente elemento es n/2.
    Si n es impar, el siguiente elemento es 3n+1.
*/

#include <iostream>
using namespace std;

int main() {
    int x, aux = 0, semilla = 0, ctd = 0, ctdn = 0;

    cout << "Ingrese el numero: ";
    cin >> x;

    for (int i = x - 1; i > 1; i--) {
        aux = i;
        ctd = 0;
        while (aux != 1) {
            if (aux % 2 == 0) {
                aux = aux / 2;
            } else {
                aux = (aux * 3) + 1;
            }
            ctd++;
        }
        if (ctd > ctdn) {
            ctdn = ctd;
            semilla = i;
        }
    }

    cout << "La serie mas larga es con la semilla: " << semilla << " , teniendo " << ctdn << " terminos" << endl;

    return 0;
}