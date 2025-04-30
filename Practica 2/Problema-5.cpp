#include <iostream>
using namespace std;

// Convierte un número entero a cadena de caracteres
void convertirNumeroACadena(int numero, char* cadena);

int main() {
    int numero;
    char resultado[20];

    cout << "Ingresa un numero entero: ";
    cin >> numero;

    convertirNumeroACadena(numero, resultado);

    cout << "Cadena convertida: " << resultado << endl;

    return 0;
}

void convertirNumeroACadena(int numero, char* cadena) {
    int i = 0;            // Índice para recorrer la cadena de caracteres
    bool negativo = false; // Variable para verificar si el número es negativo

    // Caso especial: si el número es 0
    if (numero == 0) {
        cadena[i++] = '0';  // Asigna '0' a la cadena
        cadena[i] = '\0';   // Agrega el carácter nulo al final
        return;             // Salir de la función ya que no hay más procesamiento necesario
    }

    // Si el número es negativo, se marca y se convierte en positivo
    if (numero < 0) {
        negativo = true;    // Marca que el número es negativo
        numero = -numero;  // Convierte el número a positivo
    }

    // Convertir el número al revés
    while (numero > 0) {
        // Extrae el último dígito del número y lo convierte en un carácter
        cadena[i++] = (numero % 10) + '0'; // Agrega el dígito a la cadena
        numero /= 10;  // Elimina el último dígito del número
    }

    // Si el número era negativo, agrega el signo '-' al final de la cadena
    if (negativo == true) {
        cadena[i++] = '-'; // Agrega el signo negativo
    }

    // Coloca el carácter nulo al final para finalizar la cadena
    cadena[i] = '\0';

    // Invertir la cadena para obtener el número en el orden correcto
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = cadena[j];  // Intercambia los caracteres de las posiciones j y k
        cadena[j] = cadena[k];
        cadena[k] = temp;
    }
}
