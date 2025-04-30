#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

using namespace std;

int main() {
    const int size = 200;
    char arreglo[size];
    int conteo[26] = {0}; // Para contar cuántas veces aparece cada letra

    // Semilla para la aleatoriedad basada en el tiempo
    srand(time(0)); // Esto asegura que el generador de números aleatorios cambie con el tiempo

    // Generar las letras aleatorias
    for (int i = 0; i < size; i++) {
        arreglo[i] = 'A' + (rand() % 26); // Número aleatorio entre 0 y 25 → letra A-Z
        cout << arreglo[i];
        int posicion = arreglo[i] - 'A'; // A es 0, B es 1, ..., Z es 25
        conteo[posicion]++;
    }
    cout << endl << endl;

    // Mostrar el conteo
    for (int i = 0; i < 26; i++) {
        if (conteo[i] > 0) {
            cout << (char)('A' + i) << ": " << conteo[i] << endl;
        }
    }

    return 0;
}
