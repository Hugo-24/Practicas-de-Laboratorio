#include <iostream>

using namespace std;

/*
    Problema 4. Escriba un programa para leer dos números enteros con el siguiente significado: 
    - El valor del primer número representa una hora del día en un reloj de 24 horas, 
      de modo que 1245 representa las doce y cuarenta y cinco de la tarde.
    - El segundo entero representa un tiempo de duración de la misma manera, 
      por lo que 345 representa tres horas y 45 minutos.
*/

int main() {
    int horacompleta1, horacompleta2;
    int minuto1, minuto2, hora1, hora2;
    int resultado1, resultado2;

    cout << "Ingrese la primera hora sin puntos ni espacios (formato 24h, ej: 1245): ";
    cin >> horacompleta1;

    cout << "Ingrese la segunda hora sin puntos ni espacios (duración, ej: 345): ";
    cin >> horacompleta2;

    hora1 = horacompleta1 / 100;
    minuto1 = horacompleta1 % 100;
    hora2 = horacompleta2 / 100;
    minuto2 = horacompleta2 % 100;

    if (hora1 >= 24 || hora2 >= 24) {
        cout << "Ingrese una hora válida entre 0 y 23." << endl;
        return 0;
    } 
    else if (minuto1 >= 60 || minuto2 >= 60) {
        cout << "Ingrese minutos válidos entre 0 y 59." << endl;
        return 0;
    }

    resultado1 = hora1 + hora2;
    resultado2 = minuto1 + minuto2;

    if (resultado2 >= 60) {
        resultado1 += resultado2 / 60;
        resultado2 %= 60;
    }

    if (resultado1 >= 24) {
        resultado1 %= 24;
    }

    cout << "La suma de las horas es: " 
         << (resultado1 < 10 ? "0" : "") << resultado1 << ":" 
         << (resultado2 < 10 ? "0" : "") << resultado2 << endl;

    return 0;
}