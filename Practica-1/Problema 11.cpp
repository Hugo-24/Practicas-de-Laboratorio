#include <iostream>
using namespace std;

/*
    Problema 11. Escriba un programa que reciba un número y calcule el mínimo común múltiplo 
    de todos los números enteros entre 1 y el número ingresado.
*/

int MCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int MCM(int a, int b) {
    return (a / MCD(a, b)) * b;
}

int main() {
    signed int N;
    cout << "Ingrese un número entero positivo para hallar el mínimo común múltiplo de todos los números entre 1 y el número: ";
    cin >> N;
    cout << endl;

    signed int resultado = 1;
    for (int i = 2; i <= N; i++) {
        resultado = MCM(resultado, i);
    }

    cout << "El mínimo común múltiplo es: " << resultado << endl;
    
    return 0;
}