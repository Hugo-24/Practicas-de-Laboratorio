#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
using namespace std;

// Clase que representa un enrutador individual con su tabla de enrutamiento
class Enrutador {
private:
    string nombreEnrutador; // Nombre identificador del enrutador (ej: "A", "B")
    map<string, pair<int, string>> tablaEnrutamiento;
    // destino → (costo, siguiente salto)

public:
    Enrutador();                                 // Constructor por defecto
    Enrutador(const string& nombre);             // Constructor con nombre

    void establecerNombre(const string& nombre); // Cambia el nombre
    string obtenerNombre() const;                // Retorna el nombre

    void establecerTabla(const map<string, pair<int, string>>& nuevaTabla); // Carga la tabla
    const map<string, pair<int, string>>& obtenerTabla() const;             // Retorna la tabla
};

#endif // ENRUTADOR_H
