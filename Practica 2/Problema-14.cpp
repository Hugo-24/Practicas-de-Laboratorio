#include <iostream>
using namespace std;

const int N = 5;  // Definición de tamaño de la matriz (5x5)

// Prototipos de funciones
void llenarMatriz(int matriz[N][N]);  // Función para llenar la matriz con números del 1 al 25
void imprimirMatriz(int matriz[N][N]);  // Función para imprimir la matriz
void rotar90(int original[N][N], int rotada[N][N]);  // Función para rotar la matriz 90°
void rotar180(int original[N][N], int rotada[N][N]);  // Función para rotar la matriz 180°
void rotar270(int original[N][N], int rotada[N][N]);  // Función para rotar la matriz 270°

int main() {
    int matriz[N][N];  // Declaración de la matriz original
    int rotada90[N][N], rotada180[N][N], rotada270[N][N];  // Matrices para las versiones rotadas

    // Llenado de la matriz con números del 1 al 25
    llenarMatriz(matriz);

    // Imprime la matriz original
    cout << "Matriz original:\n";
    imprimirMatriz(matriz);

    // Rota la matriz 90 grados y la imprime
    rotar90(matriz, rotada90);
    cout << "\nMatriz rotada 90 grados:\n";
    imprimirMatriz(rotada90);

    // Rota la matriz 180 grados y la imprime
    rotar180(matriz, rotada180);
    cout << "\nMatriz rotada 180 grados:\n";
    imprimirMatriz(rotada180);

    // Rota la matriz 270 grados y la imprime
    rotar270(matriz, rotada270);
    cout << "\nMatriz rotada 270 grados:\n";
    imprimirMatriz(rotada270);

    return 0;
}

// Función para llenar la matriz con números del 1 al 25
void llenarMatriz(int matriz[N][N]) {
    int valor = 1;  // Comienza el llenado desde el número 1
    for (int i = 0; i < N; i++)  // Recorre las filas
        for (int j = 0; j < N; j++)  // Recorre las columnas
            matriz[i][j] = valor++;  // Asigna el valor y luego lo incrementa
}

// Función para imprimir una matriz N x N
void imprimirMatriz(int matriz[N][N]) {
    for (int i = 0; i < N; i++) {  // Recorre las filas
        for (int j = 0; j < N; j++)  // Recorre las columnas
            cout << matriz[i][j] << "\t";  // Imprime el valor seguido de una tabulación
        cout << "\n";  // Salto de línea después de cada fila
    }
}

// Función para rotar la matriz 90 grados a la derecha
void rotar90(int original[N][N], int rotada[N][N]) {
    for (int i = 0; i < N; i++)  // Recorre las filas
        for (int j = 0; j < N; j++)  // Recorre las columnas
            rotada[j][N - 1 - i] = original[i][j];  // Asigna el valor rotado en la nueva matriz
}

// Función para rotar la matriz 180 grados
void rotar180(int original[N][N], int rotada[N][N]) {
    for (int i = 0; i < N; i++)  // Recorre las filas
        for (int j = 0; j < N; j++)  // Recorre las columnas
            rotada[N - 1 - i][N - 1 - j] = original[i][j];  // Asigna el valor rotado en la nueva matriz
}

// Función para rotar la matriz 270 grados a la izquierda
void rotar270(int original[N][N], int rotada[N][N]) {
    for (int i = 0; i < N; i++)  // Recorre las filas
        for (int j = 0; j < N; j++)  // Recorre las columnas
            rotada[N - 1 - j][i] = original[i][j];  // Asigna el valor rotado en la nueva matriz
}
