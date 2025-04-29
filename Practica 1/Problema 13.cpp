#include <iostream>
using namespace std;

/*
    Problema 13. Escriba un programa que reciba un número y calcule la suma de todos los primos menores que el número ingresado.
*/

int main() {
    signed int p;
    cout << "Ingrese un número entero positivo para calcular la suma de todos los primos menores a este: ";
    cin >> p;
    cout << endl;

    signed int suma = 0;

    for (int num = 2; num < p; num++) {
        bool primo = true;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                primo = false;
                break;
            }
        }
        if (primo) {
            suma += num;
        }
    }

    cout << "El resultado de la suma es: " << suma << endl;

    return 0;
}