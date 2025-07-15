#include "Enrutador.h"

// Constructor por defecto: nombre vacío
Enrutador::Enrutador() : nombreEnrutador("") {}

// Constructor con nombre inicial
Enrutador::Enrutador(const string& nombre) : nombreEnrutador(nombre) {}

// Cambiar el nombre del enrutador
void Enrutador::establecerNombre(const string& nombre) {
    this->nombreEnrutador = nombre;
}

// Obtener el nombre actual del enrutador
string Enrutador::obtenerNombre() const {
    return nombreEnrutador;
}

// Guardar una nueva tabla de enrutamiento completa
void Enrutador::establecerTabla(const map<string, pair<int, string>>& nuevaTabla) {
    tablaEnrutamiento = nuevaTabla;
}

// Obtener la tabla de enrutamiento (constante)
const map<string, pair<int, string>>& Enrutador::obtenerTabla() const {
    return tablaEnrutamiento;
}
