#include <iostream>
using namespace std;

const int FILAS = 6;  // Número de filas en la matriz
const int COLUMNAS = 8;  // Número de columnas en la matriz

// Prototipo de la función que contará las estrellas
int contarEstrellas(int (*matriz)[COLUMNAS]);

int main() {
    // Inicialización de la matriz de la imagen con valores de luz en cada celda
    int imagen[FILAS][COLUMNAS] = {
        {0, 3, 4, 0, 0, 0, 6, 8},
        {5, 13, 6, 0, 0, 0, 2, 3},
        {2, 6, 2, 7, 3, 0, 10, 0},
        {0, 0, 4, 15, 4, 1, 6, 0},
        {0, 0, 7, 12, 6, 9, 10, 4},
        {5, 0, 6, 10, 6, 4, 8, 0}
    };

    // Llamada a la función que cuenta las estrellas en la matriz
    int totalEstrellas = contarEstrellas(imagen);
    cout << "Cantidad de estrellas encontradas: " << totalEstrellas << endl;

    return 0;
}

// Función que cuenta las estrellas en la matriz
int contarEstrellas(int (*matriz)[COLUMNAS]) {
    int contador = 0;  // Variable para contar el número de estrellas

    // Recorre la matriz, ignorando los bordes (por eso comienza en 1 y termina en FILAS-1 y COLUMNAS-1)
    for (int i = 1; i < FILAS - 1; i++) {
        for (int j = 1; j < COLUMNAS - 1; j++) {
            // Calcula la suma de la celda actual y sus 4 vecinos
            int suma = matriz[i][j] +
                       matriz[i][j - 1] +  // vecino a la izquierda
                       matriz[i][j + 1] +  // vecino a la derecha
                       matriz[i - 1][j] +  // vecino arriba
                       matriz[i + 1][j];   // vecino abajo

            // Calcula el promedio de los 5 valores (celda y sus 4 vecinos)
            double promedio = suma / 5.0;

            // Si el promedio es mayor que 6, se considera una estrella
            if (promedio > 6) {
                contador++;  // Incrementa el contador de estrellas
            }
        }
    }

    return contador;  // Devuelve la cantidad de estrellas encontradas
}
