#include <iostream>
using namespace std;

const int N = 3;
const int MIN_VALOR = -9;
const int MAX_VALOR = 9;

int matriz[N][N];
bool usado[MAX_VALOR - MIN_VALOR + 1] = { false };

// Declaraciones
void imprimirMatriz();
bool esCuadradoMagico();
bool yaFueUsado(int valor);
void marcarUsado(int valor);

int main() {
    // Solicita al usuario que ingrese los números separados por espacios
    cout << "Ingresa los 9 numeros del cuadrado magico (del -9 al 9, sin repetir y sin incluir el 0, separados por espacios):\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int numero;
            cin >> numero;

            // Verifica si la entrada es válida (no una letra u otro símbolo)
            if (cin.fail()) {
                cin.clear();               // Limpia el error de cin
                cin.ignore(1000, '\n');    // Descarta caracteres sobrantes
                cout << "Entrada invalida. Debe ingresar un numero entero.\n";
                return 0;
            }

            // Verifica si el número está dentro del rango permitido y no es 0
            if (numero == 0 || numero < MIN_VALOR || numero > MAX_VALOR) {
                cout << "Numero fuera de rango. Solo se permiten numeros del -9 al 9, sin incluir el 0.\n";
                return 0;
            }

            // Verifica que el número no esté repetido
            if (yaFueUsado(numero)) {
                cout << "Numero repetido. No es un cuadrado magico.\n";
                return 0;
            }

            marcarUsado(numero);
            matriz[i][j] = numero;
        }
    }

    imprimirMatriz();

    // Verifica si la matriz es un cuadrado mágico
    if (esCuadradoMagico()) {
        cout << "Es un cuadrado magico.\n";
    } else {
        cout << "No es un cuadrado magico.\n";
    }

    return 0;
}

// Imprime la matriz ingresada
void imprimirMatriz() {
    cout << "Matriz ingresada:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriz[i][j] << "\t"; // Imprime cada número seguido de una tabulación
        }
        cout << "\n";
    }
}

// Verifica si la matriz es un cuadrado mágico
bool esCuadradoMagico() {
    int sumaRef = 0;
    for (int j = 0; j < N; j++) sumaRef += matriz[0][j]; // Suma de la primera fila como referencia

    // Verifica la suma de todas las filas
    for (int i = 0; i < N; i++) {
        int sumaFila = 0;
        for (int j = 0; j < N; j++) sumaFila += matriz[i][j];
        if (sumaFila != sumaRef){
            return false;
        }
    }

    // Verifica la suma de todas las columnas
    for (int j = 0; j < N; j++) {
        int sumaColumna = 0;
        for (int i = 0; i < N; i++) sumaColumna += matriz[i][j];
        if (sumaColumna != sumaRef){
            return false;
        }
    }

    // Verifica la diagonal principal
    int sumaDiag1 = 0;
    for (int i = 0; i < N; i++) sumaDiag1 += matriz[i][i];
    if (sumaDiag1 != sumaRef){
        return false;
    }

    // Verifica la diagonal secundaria
    int sumaDiag2 = 0;
    for (int i = 0; i < N; i++) sumaDiag2 += matriz[i][N - 1 - i];
    if (sumaDiag2 != sumaRef){
        return false;
    }

    return true; // Si todas las verificaciones pasaron, es un cuadrado mágico
}

// Marca un valor como ya usado
void marcarUsado(int valor) {
    int indice = valor - MIN_VALOR;
    usado[indice] = true;
}

// Verifica si un valor ya fue usado previamente
bool yaFueUsado(int valor) {
    int indice = valor - MIN_VALOR;
    return usado[indice];
}
