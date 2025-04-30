#include <iostream>
using namespace std;

// Función para calcular el factorial de un número
int factorial(int n);

int main() {

    char entrada[20];  // Para almacenar la entrada como texto
    int n = 0;
    cout << "Ingresa el valor de n: ";
    cin >> entrada;

    // Verificar que todos los caracteres sean dígitos
    int i = 0;
    while (entrada[i] != '\0') {
        if (entrada[i] < '0' || entrada[i] > '9') {
            cout << "Error: Solo se permiten caracteres numéricos." << endl;
            return 1;
        }
        i++;
    }

    // Convertir la cadena a número entero
    i = 0;
    while (entrada[i] != '\0') {
        n = n * 10 + (entrada[i] - '0');
        i++;
    }

    // Arreglo con los dígitos disponibles
    char digitos[10] = {'0','1','2','3','4','5','6','7','8','9'};

    // Arreglo booleano para marcar qué dígitos ya se han usado en la permutación
    bool usado[10] = {false};

    // Arreglo donde se almacenará el resultado (la permutación)
    char resultado[11]; // 10 caracteres para los dígitos + 1 para el carácter nulo '\0'
    resultado[10] = '\0'; // Fin de cadena para que sea imprimible como string

    // Se reduce en 1 porque las permutaciones están indexadas desde 0
    // (la permutación 1 es en realidad la de índice 0)
    n--;

    // Se generan los 10 dígitos de la permutación
    for (int i = 0; i < 10; i++) {
        // Se calcula el número de permutaciones posibles con los dígitos restantes
        int f = factorial(9 - i); // Ejemplo: si quedan 9 elementos, hay 9! formas de ordenarlos

        // Se determina cuál dígito colocar en la posición i dividiendo entre factorial
        int indice = n / f; // Esto nos da cuántos bloques de f caben antes de llegar a n
        n = n % f;          // Se actualiza n con el residuo (dentro del bloque actual)

        // Buscar el 'indice'-ésimo dígito disponible (no usado aún)
        int cuenta = -1;
        for (int j = 0; j < 10; j++) {
            if (!usado[j]) {
                cuenta++; // Solo se cuenta si el dígito no ha sido usado
                if (cuenta == indice) {
                    resultado[i] = digitos[j]; // Colocar el dígito en la posición i
                    usado[j] = true;           // Marcar como usado
                    break;
                }
            }
        }
    }

    // Mostrar la permutación resultante
    // Se suma nuevamente 1 a n porque anteriormente se le había restado
    cout << "La permutacion numero " << entrada << " es: " << resultado << endl;
    return 0;
}

// Función que calcula el factorial de un número de forma iterativa
int factorial(int n) {
    int resultado = 1;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

