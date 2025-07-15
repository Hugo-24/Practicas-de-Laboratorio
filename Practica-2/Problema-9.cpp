#include <iostream>
#include <cstring> // Para strlen
using namespace std;

int main() {
    int n;
    char entrada[20];

    cout << "Ingresa el valor de n: ";
    cin >> n;

    cout << "Ingresa una cadena numerica: ";
    cin >> entrada;

    int longitud = strlen(entrada); // Longitud de la cadena ingresada

    // Calcular cuántos ceros hacen falta al principio para que la longitud sea múltiplo de n
    // Si el residuo es 0, no se agregan ceros. Si no, se agregan (n - residuo).
    int residuo = longitud % n;
    int cerosNecesarios = (residuo == 0) ? 0 : (n - residuo);
    // Explicación del operador ternario:
    // condición ? valor_verdadero : valor_falso
    // Es igual a:
    // if (residuo == 0)
    //     cerosNecesarios = 0;
    // else
    //     cerosNecesarios = n - residuo;

    int totalDigitos = longitud + cerosNecesarios;

    // Crear nueva cadena con los ceros agregados al principio
    char cadena[30]; // Espacio suficiente
    for (int i = 0; i < cerosNecesarios; i++) {
        cadena[i] = '0'; // Agrega ceros al inicio
    }
    for (int i = 0; i < longitud; i++) {
        cadena[cerosNecesarios + i] = entrada[i]; // Copia la cadena original
    }
    cadena[totalDigitos] = '\0'; // Marca el final de la cadena

    int suma = 0;

    // Recorrer la cadena en grupos de n dígitos
    for (int i = 0; i < totalDigitos; i += n) {
        int numero = 0;
        // Convertir el grupo de n caracteres en un número
        for (int j = 0; j < n; j++) {
            if (cadena[i + j] < '0' || cadena[i + j] > '9') {
                cout << "Error: la cadena contiene caracteres no numericos." << endl;
                return 1;
            }
            // cadena[i + j] - '0' convierte el carácter numérico a valor entero.
            // Por ejemplo, si cadena[i + j] = '5', entonces '5' - '0' = 5 ('53' - '48' = 0).
            // Esto es posible porque los caracteres están representados por códigos ASCII consecutivos.
            numero = numero * 10 + (cadena[i + j] - '0'); // Construye el número cifra por cifra
        }
        suma += numero; // Acumular la suma
    }

    // Mostrar resultados
    cout << "Original: " << entrada << endl;
    cout << "Suma: " << suma << endl;

    return 0;
}
