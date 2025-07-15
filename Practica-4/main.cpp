#include "Red.h"        // Lógica de la red y los enrutadores
#include <iostream>     // Entrada / salida por consola

using namespace std;

// Esta función verifica si el nombre ingresado para un enrutador es válido.
// Se considera válido si:
// - No está vacío
// - Solo contiene letras (a-z, A-Z) o números (0-9)
bool esNombreValido(const string& nombre) {
    // Si el nombre está vacío, no es válido
    if (nombre.empty())
        return false;

    // Recorremos cada carácter del nombre
    for (char caracter : nombre) {
        // Si encontramos un carácter que no sea letra ni número, es inválido
        if (!isalnum(caracter))
            return false;
    }

    // Si pasó todas las verificaciones, el nombre es válido
    return true;
}

int main() {
    Red miRed;                 // Objeto principal que gestiona la red
    string origen, destino;    // Variables reutilizadas en el menú
    int opcion;                // Selección del menú

    //1) Cargar topología inicial desde red.txt
    miRed.cargarDesdeArchivo("red.txt");
    miRed.calcularTablasEnrutamiento();

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Mostrar tabla de un enrutador\n";
        cout << "2. Ver costo entre dos enrutadores\n";
        cout << "3. Ver ruta entre dos enrutadores\n";
        cout << "4. Desconectar dos enrutadores\n";
        cout << "5. Eliminar un enrutador\n";
        cout << "6. Cargar nueva red desde archivo\n";
        cout << "7. Agregar nuevo enrutador\n";
        cout << "8. Conectar enrutadores manualmente\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        // Validación de entrada
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada inválida. Ingrese un número del menú.\n";
            continue;
        }
        switch (opcion) {

        // 1. Mostrar tabla
        case 1:
            cout << "Ingrese nombre del enrutador: ";
            cin  >> origen;
            if (!esNombreValido(origen)) {
                cout << "Nombre invalido.\n";
                break;
            }
            miRed.mostrarTabla(origen);
            break;

        // 2. Ver costo
        case 2:
            cout << "Ingrese enrutador origen: ";
            cin  >> origen;
            cout << "Ingrese enrutador destino: ";
            cin  >> destino;

            if (!esNombreValido(origen) || !esNombreValido(destino)) {
                cout << "Nombres invalidos.\n";
                break;
            }

            if (int costo = miRed.obtenerCosto(origen, destino); costo != -1)
                cout << "Costo total desde " << origen
                     << " hasta " << destino << ": " << costo << '\n';
            else
                cout << "No hay ruta entre " << origen
                     << " y " << destino << ".\n";
            break;

        // 3. Ver ruta
        case 3:
            cout << "Ingrese enrutador origen: ";
            cin  >> origen;
            cout << "Ingrese enrutador destino: ";
            cin  >> destino;

            if (!esNombreValido(origen) || !esNombreValido(destino)) {
                cout << "Nombres invalidos.\n";
                break;
            }

            if (auto ruta = miRed.obtenerRuta(origen, destino); ruta.empty()) {
                cout << "No hay ruta disponible.\n";
            } else {
                cout << "Ruta mas eficiente: ";
                for (size_t i = 0; i < ruta.size(); ++i) {
                    cout << ruta[i];
                    if (i + 1 < ruta.size()) cout << " -> ";
                }
                cout << '\n';
            }
            break;

        // 4. Desconectar
        case 4:
            cout << "Ingrese los enrutadores a desconectar (ej. A B): ";
            cin  >> origen >> destino;

            if (!esNombreValido(origen) || !esNombreValido(destino)) {
                cout << "Nombres invalidos.\n";
                break;
            }

            miRed.desconectar(origen, destino);
            miRed.calcularTablasEnrutamiento();
            cout << "Enlace eliminado y tablas actualizadas.\n";
            break;

        // 5. Eliminar enrutador
        case 5:
            cout << "Ingrese nombre del enrutador a eliminar: ";
            cin  >> origen;
            if (!esNombreValido(origen)) {
                cout << "Nombre invalido.\n";
                break;
            }
            miRed.eliminarEnrutador(origen);
            miRed.calcularTablasEnrutamiento();
            cout << "Enrutador eliminado.\n";
            break;

        // 6. Cargar desde archivo
        case 6:
        {
            string archivo;
            cout << "Ingrese nombre del archivo (ej. red.txt): ";
            cin  >> archivo;

            miRed = Red();                      // Limpiar red actual
            miRed.cargarDesdeArchivo(archivo);  // Cargar nueva
            miRed.calcularTablasEnrutamiento();
            cout << "Red cargada y tablas recalculadas.\n";
        }
        break;

        // 7. Agregar enrutador
        case 7:
            cout << "Ingrese nombre del nuevo enrutador: ";
            cin  >> origen;
            if (!esNombreValido(origen)) {
                cout << "Nombre invalido.\n";
                break;
            }
            miRed.agregarEnrutador(origen);
            miRed.calcularTablasEnrutamiento();
            cout << "Enrutador agregado.\n";
            break;

        // 8. Conectar enrutadores
        case 8:
            int costo;
            cout << "Ingrese los enrutadores a conectar (ej. A B): ";
            cin  >> origen >> destino;
            cout << "Ingrese el costo del enlace (>0): ";
            cin  >> costo;

            if (!esNombreValido(origen) || !esNombreValido(destino) || costo <= 0) {
                cout << "Datos invalidos.\n";
                break;
            }

            miRed.conectar(origen, destino, costo);
            miRed.calcularTablasEnrutamiento();
            cout << "Enlace agregado y tablas actualizadas.\n";
            break;

        // 0. Salir
        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);

    return 0;
}
