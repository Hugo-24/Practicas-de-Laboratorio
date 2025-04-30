#include <iostream>
using namespace std;

// Declaracion de funcion
long long contarCaminos(int n);
long long factorial(int num);

int main() {
    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    // Validacion: si se ingresa un caracter no numerico
    if (cin.fail()) {
        cin.clear(); // Limpia el estado de error de cin
        cin.ignore(1000, '\n'); // Descarta el resto de la entrada
        cout << "Entrada invalida. Debe ingresar un numero entero.\n";
        return 0;
    }

    // Validacion: si el numero es negativo
    if (n < 0) {
        cout << "El numero debe ser positivo.\n";
        return 0;
    }

    // Llamamos a la funcion contarCaminos para obtener el resultado
    long long caminos = contarCaminos(n);
    cout << "Para una malla de " << n << "x" << n << " puntos hay " << caminos << " caminos.\n";

    return 0;
}

// Devuelve el numero de caminos posibles en una malla nxn usando combinatoria
// Se usa la formula de combinatoria: C(2n, n) = (2n)! / (n! * n!)
// Se requiere usar long long para evitar desbordamientos en los factoriales grandes
// Aun asi, en entornos como Qt, esta version solo funciona correctamente hasta n = 10
long long contarCaminos(int n) {
    return factorial(2 * n) / (factorial(n) * factorial(n));
}

// Calcula el factorial de un numero usando tipo long long
// Se usa long long ya que los factoriales crecen muy rapido y exceden facilmente el rango de int
long long factorial(int num) {
    long long resultado = 1;
    for (int i = 2; i <= num; i++) {
        resultado *= i;
    }
    return resultado;
}
