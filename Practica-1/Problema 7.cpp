#include <iostream>
using namespace std;

/*
    Problema 7. En la serie de Fibonacci, cada número es la suma de los 2 anteriores.
    Escriba un programa que reciba un número n y halle la suma de todos los números 
    pares en la serie de Fibonacci menores a n.
*/

int main() {
    signed int n;
    cout << "Ingrese un número entero positivo para sacar la suma de todos los pares en la serie de Fibonacci menores a n: ";
    cin >> n;
    cout << endl;

    int a = 1, b = 1, suma = 0, serie;
    while (b < n) {
        if (b % 2 == 0) {
            suma += b;
        }
        serie = a + b;
        a = b;
        b = serie;
    }

    cout << "El resultado de la suma es: " << suma << endl;
    return 0;
}