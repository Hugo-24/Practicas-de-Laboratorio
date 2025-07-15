#include "Red.h"
#include <iostream>   // Para cout, cin
#include <fstream>    // Para leer archivos
#include <set>        // Para mantener nodos visitados
#include <queue>      // Para priority_queue (cola de prioridad)
#include <limits>     // Para numeric_limits (infinito)

// Agrega un enrutador nuevo si no existe
void Red::agregarEnrutador(const string& nombre) {
    if (enrutadores.count(nombre) == 0) {
        enrutadores[nombre] = Enrutador(nombre); // Crear objeto
        topologiaRed[nombre] = map<string, int>(); // Inicializar su lista de vecinos
    }
}

// Elimina un enrutador y sus conexiones
void Red::eliminarEnrutador(const string& nombre) {
    enrutadores.erase(nombre);        // Elimina el objeto
    topologiaRed.erase(nombre);       // Elimina sus vecinos

    // Elimina referencias a este enrutador desde otros vecinos
    for (auto& [origen, vecinos] : topologiaRed) {
        vecinos.erase(nombre);
    }
}

// Conecta dos enrutadores con un costo dado (enlace bidireccional)
void Red::conectar(const string& origen, const string& destino, int costo) {
    topologiaRed[origen][destino] = costo;
    topologiaRed[destino][origen] = costo;
}

// Desconecta dos enrutadores
void Red::desconectar(const string& origen, const string& destino) {
    topologiaRed[origen].erase(destino);
    topologiaRed[destino].erase(origen);
}

// Calcula la tabla de enrutamiento para cada enrutador usando Dijkstra
void Red::calcularTablasEnrutamiento() {
    for (const auto& [nombreOrigen, _] : topologiaRed) {
        // Inicializa las distancias y los siguientes saltos
        map<string, int> distanciaMinima;
        map<string, string> siguienteSalto;
        set<string> nodosVisitados;

        // Inicializa las distancias como infinitas
        for (const auto& [nombreNodo, _] : topologiaRed) {
            distanciaMinima[nombreNodo] = numeric_limits<int>::max();
        }

        // Cola de prioridad (min-heap) para Dijkstra
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> cola;

        // El nodo origen tiene distancia 0 hacia sí mismo
        distanciaMinima[nombreOrigen] = 0;
        cola.push({0, nombreOrigen});

        while (!cola.empty()) {
            auto [distanciaActual, nodoActual] = cola.top();
            cola.pop();

            // Si ya fue visitado, no procesarlo de nuevo
            if (nodosVisitados.count(nodoActual)) continue;
            nodosVisitados.insert(nodoActual);

            // Explorar vecinos
            for (const auto& [vecino, costoEnlace] : topologiaRed[nodoActual]) {
                int nuevaDistancia = distanciaMinima[nodoActual] + costoEnlace;

                // Si encontramos un camino más corto al vecino
                if (nuevaDistancia < distanciaMinima[vecino]) {
                    distanciaMinima[vecino] = nuevaDistancia;

                    // Si estoy en el origen, el siguiente salto es el vecino directamente
                    // Si no, uso el siguiente salto de quien me trajo aquí
                    siguienteSalto[vecino] = (nodoActual == nombreOrigen) ? vecino : siguienteSalto[nodoActual];

                    // Agregar a la cola de prioridad
                    cola.push({nuevaDistancia, vecino});
                }
            }
        }

        // Crear tabla de enrutamiento final para el nodo origen
        map<string, pair<int, string>> tabla;
        for (const auto& [destino, distancia] : distanciaMinima) {
            if (destino != nombreOrigen && distancia != numeric_limits<int>::max()) {
                tabla[destino] = {distancia, siguienteSalto[destino]};
            }
        }

        // Guardar la tabla en el objeto Enrutador correspondiente
        enrutadores[nombreOrigen].establecerTabla(tabla);
    }
}

// Retorna el costo total de enviar un paquete de un nodo a otro
int Red::obtenerCosto(const string& origen, const string& destino) {
    if (enrutadores.count(origen) == 0 || enrutadores.count(destino) == 0)
        return -1; // Enrutadores no existen

    const auto& tabla = enrutadores[origen].obtenerTabla(); // Acceso constante
    auto it = tabla.find(destino);
    if (it != tabla.end()) return it->second.first;

    return -1; // No hay ruta conocida
}

// Retorna la secuencia de nodos desde origen hasta destino
vector<string> Red::obtenerRuta(const string& origen, const string& destino) {
    vector<string> ruta;

    // Verifica que ambos nodos existan
    if (origen == destino || enrutadores.count(origen) == 0 || enrutadores.count(destino) == 0)
        return ruta;

    ruta.push_back(origen);
    string actual = origen;

    // Seguir el siguiente salto desde cada nodo hasta llegar al destino
    while (actual != destino) {
        const auto& tabla = enrutadores[actual].obtenerTabla();
        auto it = tabla.find(destino);

        if (it == tabla.end()) {
            ruta.clear(); // No hay ruta
            return ruta;
        }

        actual = it->second.second;
        ruta.push_back(actual);
    }

    return ruta;
}

// Carga una red desde un archivo de texto
// Cada línea del archivo debe tener: nodoA nodoB costo
void Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string nodoA, nodoB;
    int costo;

    while (archivo >> nodoA >> nodoB >> costo) {
        agregarEnrutador(nodoA);
        agregarEnrutador(nodoB);
        conectar(nodoA, nodoB, costo);
    }
}

// Muestra la tabla de enrutamiento de un enrutador
void Red::mostrarTabla(const string& nombreEnrutador) {
    if (enrutadores.count(nombreEnrutador) == 0) {
        cout << "Enrutador no encontrado.\n";
        return;
    }

    cout << "Tabla de enrutamiento de " << nombreEnrutador << ":\n";
    for (const auto& [destino, par] : enrutadores[nombreEnrutador].obtenerTabla()) {
        cout << " -> Destino: " << destino << ", Costo: " << par.first
             << ", Siguiente salto: " << par.second << '\n';
    }
}
