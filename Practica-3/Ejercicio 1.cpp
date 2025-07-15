#include <iostream>
#include <fstream>    // Para manejar archivos: ifstream, ofstream

using namespace std;

// Declaracion de funciones
void convertirCaracterABinario(unsigned char caracter, char binario[8]);
bool* convertirArchivoABits(const char* nombreArchivo, int& cantidadBits);
void aplicarMetodo1(bool* bits, int cantidadBits, int semilla);
void aplicarMetodo2(bool* bits, int cantidadBits, int semilla);
void escribirBitsEnBinario(const char* nombreSalida, bool* bits, int cantidadBits);

// Funcion principal
int main() {
    char nombreEntrada[100];
    char nombreSalida[100];
    int semilla;
    int metodo;

    // Pedir al usuario los nombres de archivo, semilla y metodo
    cout << "Nombre del archivo de entrada (.txt): ";
    cin >> nombreEntrada;
    cout << "Nombre del archivo de salida (.bin): ";
    cin >> nombreSalida;
    cout << "Semilla (numero de bits por bloque): ";
    cin >> semilla;
    cout << "Metodo de codificacion (1 o 2): ";
    cin >> metodo;

    int cantidadBits = 0;

    // Convertimos el archivo de texto a un arreglo de bits
    bool* bits = convertirArchivoABits(nombreEntrada, cantidadBits);

    // Verificacion de errores: archivo vacio o no se leyo
    if (bits == nullptr || cantidadBits == 0) {
        cout << "Error: No se pudo leer ningun bit. Verifique el archivo." << endl;
        return 1;
    }

    // Elegir el metodo de codificacion
    if (metodo == 1) {
        aplicarMetodo1(bits, cantidadBits, semilla);
    } else if (metodo == 2) {
        aplicarMetodo2(bits, cantidadBits, semilla);
    } else {
        cout << "Metodo invalido. Solo se permite 1 o 2." << endl;
        delete[] bits;
        return 1;
    }

    // Escribir el resultado codificado en un archivo binario
    escribirBitsEnBinario(nombreSalida, bits, cantidadBits);

    // Liberar memoria usada
    delete[] bits;

    cout << "Archivo codificado con exito." << endl;
    return 0;
}

void convertirCaracterABinario(unsigned char caracter, char binario[8]) {
    // Se llena el arreglo binario[] con '0' y '1' desde el bit menos significativo (derecha) al mas significativo
    for (int i = 7; i >= 0; --i) {
        binario[i] = (caracter % 2) + '0';
        // (caracter % 2) obtiene el ultimo bit (0 o 1) del valor ASCII del caracter.
        // Luego se suma '0' (ASCII 48) para convertir el numero 0 o 1 al caracter '0' o '1'.
        caracter = caracter / 2;
        // Desplazamos el caracter hacia la derecha para extraer el siguiente bit.
    }
}

bool* convertirArchivoABits(const char* nombreArchivo, int& cantidadBits) {

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "No se pudo abrir el archivo de entrada." << endl;
        return nullptr;
    }

    int capacidad = 1024;
    char* caracteres = new char[capacidad]; // Arreglo donde guardaremos todo el texto
    int cantidadCaracteres = 0;
    char caracter;

    // Leemos el archivo caracter por caracter
    while (archivo.get(caracter)) {
        // Si se alcanza la capacidad del arreglo, lo duplicamos
        if (cantidadCaracteres >= capacidad) {
            int nuevaCapacidad = capacidad * 2;
            char* nuevo = new char[nuevaCapacidad]; // Nuevo arreglo más grande
            for (int i = 0; i < capacidad; i++) {
                nuevo[i] = caracteres[i]; // Copiamos los caracteres ya leídos
            }
            delete[] caracteres; // Liberamos el arreglo viejo
            caracteres = nuevo;  // Reemplazamos el puntero por el nuevo
            capacidad = nuevaCapacidad;
        }
        caracteres[cantidadCaracteres++] = caracter; // Guardamos el caracter leido
    }

    archivo.close(); // Cerramos el archivo al finalizar la lectura

    if (cantidadCaracteres == 0) {
        // Si no se leyó ningún caracter, no hay nada que codificar
        cout << "El archivo esta vacio. No hay bits para procesar." << endl;
        delete[] caracteres;
        return nullptr;
    }

    cantidadBits = cantidadCaracteres * 8; // Cada caracter son 8 bits
    bool* bits = new bool[cantidadBits];   // Arreglo donde guardaremos los bits (true = 1, false = 0)
    char binario[8]; // Arreglo temporal para convertir cada caracter en bits
    int posicion = 0;

    // Recorremos cada caracter y lo convertimos a sus 8 bits
    for (int i = 0; i < cantidadCaracteres; ++i) {
        convertirCaracterABinario((unsigned char)caracteres[i], binario);
        for (int j = 0; j < 8; ++j) {
            // Guardamos el bit como true si es '1', o false si es '0'
            bits[posicion++] = (binario[j] == '1');
        }
    }

    delete[] caracteres;
    return bits;
}

void aplicarMetodo1(bool* bits, int cantidadBits, int semilla) {
    // Calculamos la cantidad total de bloques de tamaño 'semilla'
    // Esta formula es equivalente a redondear hacia arriba: (cantidadBits / semilla)
    int cantidadBloques = (cantidadBits + semilla - 1) / semilla;

    // Creamos una copia de los bits originales antes de modificarlos.
    // Esto es necesario porque para codificar el bloque actual,
    // necesitamos analizar el bloque anterior sin codificar.
    bool* original = new bool[cantidadBits];
    for (int i = 0; i < cantidadBits; ++i) {
        original[i] = bits[i];
    }

    // Recorremos todos los bloques
    for (int bloque = 0; bloque < cantidadBloques; ++bloque) {
        // Calculamos el índice de inicio y fin del bloque actual
        int inicio = bloque * semilla;
        int fin = (inicio + semilla < cantidadBits) ? inicio + semilla : cantidadBits;

        // Si es el primer bloque, se invierte completamente
        if (bloque == 0) {
            for (int i = inicio; i < fin; ++i) {
                bits[i] = !original[i]; // Invertimos el bit (1→0, 0→1)
            }
        } else {
            // Para los demás bloques, analizamos el bloque anterior
            int inicioAnterior = (bloque - 1) * semilla;
            int finAnterior = (inicioAnterior + semilla < cantidadBits) ? inicioAnterior + semilla : cantidadBits;

            // Contamos la cantidad de unos y ceros en el bloque anterior
            int unos = 0, ceros = 0;
            for (int i = inicioAnterior; i < finAnterior; ++i) {
                if (original[i]) {
                    unos++;
                } else {
                    ceros++;
                }
            }

            // Regla 1: si hay la misma cantidad de 1s y 0s → invertir todo el bloque actual
            if (unos == ceros) {
                for (int i = inicio; i < fin; ++i) {
                    bits[i] = !original[i];
                }

                // Regla 2: si hay más ceros → invertir cada 2 bits del bloque actual
            } else if (ceros > unos) {
                for (int i = inicio; i < fin; i += 2) {
                    bits[i] = !original[i];
                    if (i + 1 < fin) {
                        bits[i + 1] = !original[i + 1];
                    }
                }

                // Regla 3: si hay más unos → invertir cada 3 bits del bloque actual
            } else {
                for (int i = inicio; i < fin; i += 3) {
                    for (int j = 0; j < 3 && i + j < fin; ++j) {
                        bits[i + j] = !original[i + j];
                    }
                }
            }
        }
    }

    delete[] original;
}

void aplicarMetodo2(bool* bits, int cantidadBits, int semilla) {
    // Calculamos cuántos bloques hay según la semilla
    int cantidadBloques = (cantidadBits + semilla - 1) / semilla;

    // Recorremos cada bloque uno por uno
    for (int bloque = 0; bloque < cantidadBloques; ++bloque) {
        // Calculamos inicio y fin del bloque actual
        int inicio = bloque * semilla;
        int fin = (inicio + semilla < cantidadBits) ? inicio + semilla : cantidadBits;
        int tamanio = fin - inicio; // longitud real del bloque (por si el último es más corto)

        // Creamos un arreglo temporal para guardar el bloque original antes de rotarlo
        bool* temporal = new bool[tamanio];
        for (int i = 0; i < tamanio; ++i) {
            temporal[i] = bits[inicio + i]; // copiamos los bits del bloque
        }

        // Aplicamos la rotación a la derecha:
        // El último bit se vuelve el primero, y los demás se corren una posición
        for (int i = 0; i < tamanio; ++i) {
            if (i == 0) {
                bits[inicio + i] = temporal[tamanio - 1]; // primer bit = último del bloque original
            } else {
                bits[inicio + i] = temporal[i - 1]; // los demás se recorren desde la izquierda
            }
        }

        delete[] temporal;
    }
}

void escribirBitsEnBinario(const char* nombreSalida, bool* bits, int cantidadBits) {
    ofstream archivo;

    try {
        // Activamos excepciones si hay error al escribir
        archivo.exceptions(ofstream::failbit | ofstream::badbit);
        // failbit = error logico (por ejemplo: archivo mal abierto)
        // badbit = error fisico (problema real de escritura en disco, etc)

        archivo.open(nombreSalida, ios::binary); // ios::binary para escribir datos binarios (no texto)

        unsigned char byte = 0;

        for (int i = 0; i < cantidadBits; ++i) {
            byte = byte << 1; // Mueve los bits hacia la izquierda para hacer espacio al nuevo bit
            if (bits[i]) {
                byte = byte | 1; // Si el bit es true (1), activamos el ultimo bit con OR. byte | 00000001
            }

            // Cada 8 bits completamos un byte
            if ((i + 1) % 8 == 0) {
                archivo.write(reinterpret_cast<char*>(&byte), 1);
                // reinterpret_cast convierte un unsigned char* a char* para que write() lo acepte
                byte = 0;
            }
        }

        // Si sobran bits al final, se completan con ceros
        int resto = cantidadBits % 8;
        if (resto != 0) {
            byte = byte << (8 - resto); // Llenamos los bits vacios con ceros a la derecha
            // Desplazamos los bits sobrantes hacia la izquierda para llenar el byte completo.
            // Esto agrega ceros a la derecha y posiciona los bits al principio del byte.
            archivo.write(reinterpret_cast<char*>(&byte), 1);
            // reinterpret_cast convierte un unsigned char* a char* para que write() lo acepte
        }

        archivo.close();
    } catch (const ofstream::failure& e) {
        cerr << "Error al escribir archivo binario: " << e.what() << endl;
    }
}
