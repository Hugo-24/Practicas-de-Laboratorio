#include <iostream>
#include <fstream>  // Para manejar archivos binarios y de texto

using namespace std;


// Declaración de funciones
bool* leerBitsDesdeBinario(const char* nombreArchivo, int& cantidadBits);
void aplicarMetodo1Inverso(bool* bits, int cantidadBits, int semilla);
void aplicarMetodo2Inverso(bool* bits, int cantidadBits, int semilla);
void escribirTextoDesdeBits(const char* nombreArchivo, bool* bits, int cantidadBits);

// Función principal
int main() {
    char nombreEntrada[100];
    char nombreSalida[100];
    int semilla;
    int metodo;

    // Solicita datos al usuario por consola
    cout << "Nombre del archivo binario (.bin): ";
    cin >> nombreEntrada;
    cout << "Nombre del archivo de salida (.txt): ";
    cin >> nombreSalida;
    cout << "Semilla (numero de bits por bloque): ";
    cin >> semilla;
    cout << "Metodo de decodificacion (1 o 2): ";
    cin >> metodo;

    int cantidadBits = 0;

    // Cargamos los bits desde el archivo binario
    bool* bits = leerBitsDesdeBinario(nombreEntrada, cantidadBits);

    // Verificación de error de lectura
    if (bits == nullptr || cantidadBits == 0) {
        cout << "No se pudo leer el archivo binario o esta vacio." << endl;
        return 1;
    }

    // Aplicamos el método de decodificación elegido
    if (metodo == 1) {
        aplicarMetodo1Inverso(bits, cantidadBits, semilla);
    } else if (metodo == 2) {
        aplicarMetodo2Inverso(bits, cantidadBits, semilla);
    } else {
        cout << "Metodo invalido. Solo se permite 1 o 2." << endl;
        delete[] bits;
        return 1;
    }

    // Convertimos los bits de nuevo a texto y los escribimos al archivo de salida
    escribirTextoDesdeBits(nombreSalida, bits, cantidadBits);

    // Liberamos la memoria dinámica usada para los bits
    delete[] bits;

    cout << "Archivo decodificado con exito." << endl;
    return 0;
}

// Esta función abre un archivo binario y extrae todos sus bits como valores true/false.
// Cada byte leído se convierte en 8 bits individuales y se almacena en un arreglo dinámico.
bool* leerBitsDesdeBinario(const char* nombreArchivo, int& cantidadBits) {
    ifstream archivo(nombreArchivo, ios::binary); // Abrimos archivo en modo binario
    if (!archivo) {
        cout << "No se pudo abrir el archivo binario." << endl;
        return nullptr;
    }

    // seekg(pos, modo): mueve el cursor de lectura
    // Aquí lo usamos para ir al final y saber cuántos bytes tiene el archivo
    archivo.seekg(0, ios::end);
    int tamañoArchivo = archivo.tellg();  // Cantidad de bytes del archivo
    archivo.seekg(0, ios::beg);           // Volvemos al inicio para leer

    cantidadBits = tamañoArchivo * 8;     // Cada byte = 8 bits
    bool* bits = new bool[cantidadBits];  // Creamos arreglo dinámico para guardar bits

    unsigned char byte;
    int posicion = 0;

    // Leemos el archivo byte por byte
    while (archivo.read(reinterpret_cast<char*>(&byte), 1)) {
        // Extraemos sus 8 bits usando máscaras (operaciones a nivel de bits)
        for (int i = 7; i >= 0; --i) {
            bits[posicion++] = (byte & (1 << i)) != 0;  // extrae bit i
        }
    }

    archivo.close();
    return bits;
}

// Esta función revierte la codificación del método 1.
// Aplica las mismas reglas pero al revés: usando una copia auxiliar original[]
// para poder reconstruir los valores originales bloque a bloque.
void aplicarMetodo1Inverso(bool* bits, int cantidadBits, int semilla) {
    int cantidadBloques = (cantidadBits + semilla - 1) / semilla;

    bool* original = new bool[cantidadBits]; // Usado para guardar la decodificación paso a paso

    for (int bloque = 0; bloque < cantidadBloques; ++bloque) {
        int inicio = bloque * semilla;
        int fin = (inicio + semilla < cantidadBits) ? inicio + semilla : cantidadBits;

        if (bloque == 0) {
            // El primer bloque se invirtió completamente, así que simplemente lo reinvertimos
            for (int i = inicio; i < fin; ++i) {
                original[i] = !bits[i];
            }
        } else {
            // Analizamos el bloque anterior ya decodificado
            int inicioAnterior = (bloque - 1) * semilla;
            int finAnterior = (inicioAnterior + semilla < cantidadBits) ? inicioAnterior + semilla : cantidadBits;

            int unos = 0, ceros = 0;
            for (int i = inicioAnterior; i < finAnterior; ++i) {
                if (original[i]) unos++;
                else ceros++;
            }

            // Revertimos la operación aplicada en la codificación, según la regla que haya sido usada
            if (unos == ceros) {
                for (int i = inicio; i < fin; ++i) {
                    original[i] = !bits[i];
                }
            } else if (ceros > unos) {
                for (int i = inicio; i < fin; i += 2) {
                    original[i] = !bits[i];
                    if (i + 1 < fin) {
                        original[i + 1] = !bits[i + 1];
                    }
                }
            } else {
                for (int i = inicio; i < fin; i += 3) {
                    for (int j = 0; j < 3 && i + j < fin; ++j) {
                        original[i + j] = !bits[i + j];
                    }
                }
            }
        }
    }

    // Copiamos el resultado al arreglo original de bits
    for (int i = 0; i < cantidadBits; ++i) {
        bits[i] = original[i];
    }

    delete[] original;
}

// Esta función revierte el método 2 (rotación a la derecha).
// Para hacerlo, aplica una rotación a la izquierda sobre cada bloque.
void aplicarMetodo2Inverso(bool* bits, int cantidadBits, int semilla) {
    int cantidadBloques = (cantidadBits + semilla - 1) / semilla;

    for (int bloque = 0; bloque < cantidadBloques; ++bloque) {
        int inicio = bloque * semilla;
        int fin = (inicio + semilla < cantidadBits) ? inicio + semilla : cantidadBits;
        int tamanio = fin - inicio;

        // Hacemos una copia temporal del bloque
        bool* temporal = new bool[tamanio];
        for (int i = 0; i < tamanio; ++i) {
            temporal[i] = bits[inicio + i];
        }

        // Rotamos hacia la izquierda:
        // El último bit original se mueve a la posición anterior
        for (int i = 0; i < tamanio; ++i) {
            if (i == tamanio - 1) {
                bits[inicio + i] = temporal[0];
            } else {
                bits[inicio + i] = temporal[i + 1];
            }
        }

        delete[] temporal;
    }
}

// Esta función toma los bits decodificados y reconstruye los caracteres originales
// Agrupa los bits de a 8, los convierte a un caracter ASCII y lo guarda en el archivo de salida.
void escribirTextoDesdeBits(const char* nombreArchivo, bool* bits, int cantidadBits) {
    ofstream archivo(nombreArchivo);  // Abrimos archivo de salida en modo texto
    if (!archivo) {
        cout << "No se pudo abrir el archivo de salida." << endl;
        return;
    }

    // Procesamos cada grupo de 8 bits
    for (int i = 0; i < cantidadBits; i += 8) {
        unsigned char caracter = 0;

        // Construimos el byte desplazando e insertando cada bit
        for (int j = 0; j < 8 && i + j < cantidadBits; ++j) {
            caracter = (caracter << 1) | bits[i + j];
        }

        archivo << caracter;  // Escribimos el carácter al archivo
    }

    archivo.close();
}
