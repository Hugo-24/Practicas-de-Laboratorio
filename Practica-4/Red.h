#ifndef RED_H
#define RED_H

#include "Enrutador.h"

#include <string>      // Para usar string
#include <map>         // Para map (diccionario)
#include <vector>      // Para vector (arreglo dinámico)

using namespace std;

// Clase que representa la red completa de enrutadores
class Red {
private:
    map<string, map<string, int>> topologiaRed;   // Representa el grafo: nodo → (vecino → costo)
    map<string, Enrutador> enrutadores;           // Mapa de nombres a objetos Enrutador

public:
    void agregarEnrutador(const string& nombre);
    void eliminarEnrutador(const string& nombre);

    void conectar(const string& origen, const string& destino, int costo);
    void desconectar(const string& origen, const string& destino);

    void calcularTablasEnrutamiento();

    int obtenerCosto(const string& origen, const string& destino);
    vector<string> obtenerRuta(const string& origen, const string& destino);

    void cargarDesdeArchivo(const string& nombreArchivo);
    void mostrarTabla(const string& nombreEnrutador);
};

#endif // RED_H
