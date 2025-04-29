#include <iostream>
using namespace std;

/*
    Problema 12. Escriba un programa que calcula el máximo factor primo de un número.
*/

int main() {
    int x, primo = 1;
    
    cout << "Ingrese el número: ";
    cin >> x;

    for (int i = 2; i <= x; i++) {
        while (x % i == 0) {
            primo = i;
            x /= i;
        }
    }

    cout << "El mayor factor primo es: " << primo << endl;
    
    return 0;
}
