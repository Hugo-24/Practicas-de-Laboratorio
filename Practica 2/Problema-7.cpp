#include <iostream>
using namespace std;

// Función para eliminar caracteres repetidos de una cadena
void eliminarRepetidos(char* cadena);

int main() {
    char cadena[20];

    // Solicitar la cadena al usuario
    cout << "Ingresa una cadena: ";
    cin >> cadena;

    cout << "Original: " << cadena << endl;

    eliminarRepetidos(cadena); // Eliminar caracteres repetidos

    cout << "Sin repetidos: " << cadena << endl;

    return 0;
}

void eliminarRepetidos(char* cadena) {
    bool encontrado[256] = {false}; // Array para verificar si un carácter ya ha sido encontrado. El arreglo tiene 256 elementos, uno por cada posible valor ASCII.
    int i = 0, j = 0;
    //i es para recorrer la cadena ingresada y j para la cadena sin repetir (solo aumenta cuando se encuentra un nuevo char)
    // Recorremos cada carácter de la cadena
    while (cadena[i] != '\0') {
        // Si el carácter no ha sido encontrado antes, lo copiamos a la posición j
        if (encontrado[cadena[i]] == false) { // C++ trata char como un número entre 0 y 255, que se puede usar como índice para un arreglo.
            encontrado[cadena[i]] = true;  // Marcamos el carácter como encontrado
            cadena[j++] = cadena[i];       // Copiamos el carácter a la nueva posición
        }
        i++;
    }

    // Colocamos el carácter nulo al final de la cadena resultante
    cadena[j] = '\0';
}
