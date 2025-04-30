#include <iostream>
using namespace std;

int main() {
    char original[20];      // Cadena original ingresada
    char soloTexto[20];     // Cadena sin números
    char soloNumeros[20];   // Cadena solo con números

    cout << "Ingresa una cadena: ";
    cin >> original;

    int j = 0, k = 0;

    // Recorrer la cadena original
    for (int i = 0; original[i] != '\0'; i++) {
        if (original[i] >= '0' && original[i] <= '9') {
            // Si es un dígito, lo añadimos a la cadena de números
            soloNumeros[k++] = original[i];
        } else {
            // Si no es dígito, lo añadimos a la cadena de texto
            soloTexto[j++] = original[i];
        }
    }

    // Finalizar las cadenas con '\0'
    soloTexto[j] = '\0';
    soloNumeros[k] = '\0';

    // Mostrar resultados
    cout << "Original: " << original << endl;
    cout << "Texto: " << soloTexto << endl;
    cout << "Numero: " << soloNumeros << endl;

    return 0;
}
