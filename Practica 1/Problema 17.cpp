/*
    Problema 17. La secuencia de números triangulares se forma al sumar su posición en el arreglo con el valor del número anterior.
*/

#include <iostream>
using namespace std;

int main() {
    int k;
    cout << "Ingrese un numero k: ";
    cin >> k;
    cout << endl;

    int n = 1, triangular = 1, count;

    while (true) {
        count = 0;
        for (int i = 1; i * i <= triangular; i++) {
            if (triangular % i == 0) {
                count++;
                if (i != triangular / i) count++;
            }
        }
        if (count > k) {
            cout << "El numero es: " << triangular << " que tiene " << count << " divisores." << endl;
            break;
        }
        n++;
        triangular = n * (n + 1) / 2;
    }

    return 0;
}