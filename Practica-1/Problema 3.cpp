#include <iostream>

using namespace std;

/*
    Problema 3. Escriba un programa que debe leer un mes y un día de dicho mes para luego decir si esa combinación de mes y día son válidos. 
    El caso más especial es el 29 de febrero, en dicho caso imprimir "posiblemente año bisiesto".
*/

int main() {
    signed short int mes, dia;

    cout << "Ingrese una fecha en forma numérica para saber si es válida o no.\n";
    cout << "Primeramente, ingrese el número del mes como un entero positivo: ";
    cin >> mes;
    cout << endl;

    if (mes > 0 && mes <= 12) {
        cout << "Ahora ingrese el día de esa fecha: ";
        cin >> dia;
        cout << endl;

        if (dia > 0 && dia <= 31) {
            if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia == 31) {
                cout << "La fecha " << dia << "/" << mes << " es inválida.";
            } 
            else if (mes == 2 && dia > 28) {
                if (dia == 29) {
                    cout << "La fecha " << dia << "/" << mes << " es válida en bisiesto.";
                } else {
                    cout << "La fecha " << dia << "/" << mes << " es inválida.";
                }
            } 
            else {
                cout << "La fecha " << dia << "/" << mes << " es válida.";
            }
        } 
        else {
            cout << "La fecha " << dia << "/" << mes << " es inválida (el día debe estar entre 1 y 31, dependiendo del mes).";
        }
    } 
    else {
        cout << "La fecha es inválida (el mes debe estar entre 1 y 12).";
    }

    return 0;
}