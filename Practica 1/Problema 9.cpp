#include <iostream>
using namespace std;

/*
    Problema 9. Escriba un programa que pida un número entero N e imprima el resultado de la suma 
    de todos sus dígitos elevados a sí mismos.
*/

// Función para calcular la potencia
int potencia(int base, int exponente) {
    int resultado = 1;
    for (int i = 0; i < exponente; i++) {
        resultado *= base;
    }
    return resultado;
}

int main() {
    signed int n;
    cout << "Ingrese un numero entero positivo para saber el resultado de la suma de todos sus digitos elevados a si mismos: ";
    cin >> n;
    cout << endl;

    int suma = 0;
    int numero = n;

    while (numero > 0) {
        int digito = numero % 10;
        suma += potencia(digito, digito);
        numero /= 10;
    }

    cout << "El resultado de la suma es: " << suma << endl;
    return 0;
}