#include <iostream>
using namespace std;

// Convierte una cadena de caracteres numéricos a un entero
int convertirCadenaANumero(const char* cadena);

int main() {
    char entrada[20];
    cout << "Ingresa una cadena numerica: ";
    cin >> entrada;

    int numero = convertirCadenaANumero(entrada);

    if (numero != -1) {
        cout << "Numero convertido: " << numero << endl;
    } else {
        cout << "La cadena contiene caracteres no numericos." << endl;
    }

    return 0;
}

int convertirCadenaANumero(const char* cadena) {
    int resultado = 0;
    for (int i = 0; cadena[i] != '\0'; i++) {
        // Verifica que cada carácter sea un dígito
        if (cadena[i] >= '0' && cadena[i] <= '9') {
            resultado = resultado * 10 + (cadena[i] - '0');
        } else {
            // Si hay un carácter no numérico, retorna -1 (o puedes lanzar error)
            return -1;
        }
    }
    return resultado;
}
