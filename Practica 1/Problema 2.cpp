 //Problema 2. Hacer un programa que entregue el número de billetes y monedas de cada denominación para completar la cantidad deseada.
#include <iostream>
using namespace std;

int main() {
    int valor, vuelto, aux;
    cout << "Ingrese un valor: ";
    cin >> valor;

    aux = valor / 50000;
    vuelto = valor % 50000;
    cout << "Billetes de 50.000: " << aux << endl;

    aux = vuelto / 20000;
    vuelto = vuelto % 20000;
    cout << "Billetes de 20.000: " << aux << endl;

    aux = vuelto / 10000;
    vuelto = vuelto % 10000;
    cout << "Billetes de 10.000: " << aux << endl;

    aux = vuelto / 5000;
    vuelto = vuelto % 5000;
    cout << "Billetes de 5.000: " << aux << endl;

    aux = vuelto / 2000;
    vuelto = vuelto % 2000;
    cout << "Billetes de 2.000: " << aux << endl;

    aux = vuelto / 1000;
    vuelto = vuelto % 1000;
    cout << "Billetes de 1.000: " << aux << endl;

    aux = vuelto / 500;
    vuelto = vuelto % 500;
    cout << "Monedas de 500: " << aux << endl;

    aux = vuelto / 200;
    vuelto = vuelto % 200;
    cout << "Monedas de 200: " << aux << endl;

    aux = vuelto / 100;
    vuelto = vuelto % 100;
    cout << "Monedas de 100: " << aux << endl;

    aux = vuelto / 50;
    vuelto = vuelto % 50;
    cout << "Monedas de 50: " << aux << endl;

    cout << "Restante: " << vuelto << endl;
    return 0;
}
