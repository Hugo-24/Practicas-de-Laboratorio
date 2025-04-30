#include <iostream>
using namespace std;

// Función que calcula la intersección entre dos rectángulos
// Cada rectángulo se representa con un arreglo de 4 enteros: {x, y, ancho, alto}
// La función modifica por referencia el arreglo 'interseccion' con los valores del rectángulo resultante
// Declaracion de la funcion
void calcularInterseccion(int A[4], int B[4], int interseccion[4]);

int main() {
    // Definimos dos rectangulos A y B, cada uno como un arreglo de 4 enteros: {x, y, ancho, alto}
    int A[4] = {0, 0, 8, 4};
    int B[4] = {5, 2, 6, 7};
    int C[4]; // Aqui se almacenara el rectangulo de interseccion

    calcularInterseccion(A, B, C);

    // Imprimimos el rectangulo resultante de la interseccion
    cout << "\nRectangulo interseccion: {";
    for (int i = 0; i < 4; i++) {
        cout << C[i];
        if (i < 3) cout << ", ";
    }
    cout << "}\n";

    return 0;
}

// Definicion de la funcion
void calcularInterseccion(int A[4], int B[4], int interseccion[4]) {
    // Coordenadas del rectangulo A
    int x1_A = A[0];
    int y1_A = A[1];
    int x2_A = x1_A + A[2]; // x derecho
    int y2_A = y1_A + A[3]; // y inferior

    // Coordenadas del rectangulo B
    int x1_B = B[0];
    int y1_B = B[1];
    int x2_B = x1_B + B[2];
    int y2_B = y1_B + B[3];

    // Coordenadas del rectangulo interseccion
    int x1_I = max(x1_A, x1_B); // El borde izquierdo mas a la derecha
    int y1_I = max(y1_A, y1_B); // El borde superior mas abajo
    int x2_I = min(x2_A, x2_B); // El borde derecho mas a la izquierda
    int y2_I = min(y2_A, y2_B); // El borde inferior mas arriba

    // Verificamos si hay una interseccion valida
    if (x1_I < x2_I && y1_I < y2_I) {
        interseccion[0] = x1_I;
        interseccion[1] = y1_I;
        interseccion[2] = x2_I - x1_I; // ancho
        interseccion[3] = y2_I - y1_I; // alto
    } else {
        // No hay interseccion: todos los valores en cero
        interseccion[0] = interseccion[1] = interseccion[2] = interseccion[3] = 0;
    }
}
