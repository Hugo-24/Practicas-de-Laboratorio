#include <iostream>
using namespace std;

// Constantes que definen el tamaño de la sala de cine
const int FILAS = 15;
const int COLUMNAS = 20;

// Matriz que representa los asientos de la sala
// Cada asiento puede estar disponible '-' o reservado '+'
char sala[FILAS][COLUMNAS];

// Declaración de funciones
void inicializarSala();       // Inicializa todos los asientos como disponibles
void mostrarSala();           // Muestra la sala con el estado de cada asiento
void gestionarAsiento();      // Permite al usuario reservar o cancelar un asiento
int filaALetra(char letra);   // Convierte una letra (A-O) en el índice correspondiente de la fila

int main() {
    inicializarSala(); // Se marca toda la sala como vacía al inicio

    int opcion;
    // Bucle principal que permite al usuario elegir una opción del menú
    do {
        cout << "\n1. Ver sala\n2. Reservar/Cancelar asiento\n3. Salir\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            mostrarSala(); // Muestra la sala actual
            break;
        case 2:
            gestionarAsiento(); // Permite reservar o cancelar un asiento
            break;
        case 3:
            cout << "Saliendo...\n"; // Finaliza el programa
            break;
        default:
            cout << "Opcion invalida.\n"; // Controla opciones no válidas
        }
    } while (opcion != 3); // El programa se repite hasta que se elija salir

    return 0;
}

// Inicializa la sala con todos los asientos marcados como disponibles '-'
void inicializarSala() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            sala[i][j] = '-';
        }
    }
}

// Muestra el estado actual de la sala
// Filas se muestran con letras A-O y columnas del 1 al 20
void mostrarSala() {
    cout << "  ";
    for (int j = 0; j < COLUMNAS; j++) {
        if (j < 9) {
            cout << j + 1 << "  ";  // Alineación para números de un solo dígito
        } else {
            cout << j + 1 << " ";   // Alineación para números de dos dígitos
        }
    }
    cout << "\n";

    for (int i = 0; i < FILAS; i++) {
        cout << char('A' + i) << " "; // Muestra la letra de la fila
        for (int j = 0; j < COLUMNAS; j++) {
            cout << sala[i][j] << "  "; // Muestra el estado del asiento
        }
        cout << "\n";
    }
}

// Convierte una letra (A-O o a-o) en el índice correspondiente de la fila
// Devuelve -1 si la letra no es válida
int filaALetra(char letra) {
    if (letra >= 'A' && letra <= 'O') {
        return letra - 'A';
    } else if (letra >= 'a' && letra <= 'o') {
        return letra - 'a';
    } else {
        return -1;
    }
}

// Permite reservar ('+') o cancelar ('-') un asiento
void gestionarAsiento() {
    char letra;     // Letra de la fila (A-O)
    int numero;     // Número de la columna (1-20)
    char accion;    // Acción: '+' para reservar, '-' para cancelar

    cout << "Ingrese la fila (A-O): ";
    cin >> letra;

    // Verifica si la letra es válida
    if (!((letra >= 'A' && letra <= 'O') || (letra >= 'a' && letra <= 'o'))) {
        cout << "Fila invalida. Debe ser una letra entre A y O.\n";
        return;
    }

    cout << "Ingrese el numero de asiento (1-20): ";
    cin >> numero;

    // Valida que la entrada sea un número entero válido
    // Verifica si la entrada falló, por ejemplo si se ingresó una letra o símbolo en vez de un número
    if (cin.fail()) {
        cin.clear();               // Limpia el estado de error del stream (deja de estar en modo de error)
        cin.ignore(1000, '\n');    // Descarta hasta 1000 caracteres o hasta encontrar un salto de línea, lo que ocurra primero.
            // Esto limpia el búfer de entrada, eliminando el dato inválido que causó el error.
        cout << "Entrada invalida. Debe ingresar un numero entero entre 1 y 20.\n";
        return;
    }

    // Valida que el número esté dentro del rango permitido
    if (numero < 1 || numero > 20) {
        cout << "Numero de asiento invalido. Debe estar entre 1 y 20.\n";
        return;
    }

    // Convierte la letra en índice de fila y ajusta la columna
    int fila = filaALetra(letra);
    int columna = numero - 1;

    cout << "Desea reservar (+) o cancelar (-) el asiento? ";
    cin >> accion;

    // Gestiona la acción elegida
    if (accion == '+') {
        if (sala[fila][columna] == '+') {
            cout << "Asiento ya reservado.\n";
        } else {
            sala[fila][columna] = '+';
            cout << "Reserva exitosa.\n";
        }
    } else if (accion == '-') {
        if (sala[fila][columna] == '-') {
            cout << "Asiento ya disponible.\n";
        } else {
            sala[fila][columna] = '-';
            cout << "Cancelacion exitosa.\n";
        }
    } else {
        cout << "Accion invalida. Use '+' para reservar o '-' para cancelar.\n";
    }
}
