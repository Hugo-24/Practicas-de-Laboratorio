#include <iostream>
using namespace std;

/*
    Problema 14. Un número palíndromo es igual de derecha a izquierda y de izquierda a derecha.
*/

int main() {
    int unidades, decenas, centenas, um, dem, cem;
    long resultado = 0, mayor1, mayor2, resultadoa;

    for (long i = 100; i <= 999; i++) {
        for (long j = i; j <= 999; j++) {
            resultadoa = i * j;

            if (resultadoa < 100000) {
                // Trabajo con 5 cifras
                unidades = resultadoa % 10;
                decenas = (resultadoa % 100) / 10;
                um = (resultadoa / 1000) % 10;
                dem = resultadoa / 10000;

                if (unidades == dem && decenas == um && resultadoa > resultado) {
                    // Es un palíndromo
                    mayor1 = i;
                    mayor2 = j;
                    resultado = resultadoa;
                }
            } else {
                // Trabajo con 6 cifras
                unidades = resultadoa % 10;
                decenas = (resultadoa % 100) / 10;
                centenas = (resultadoa % 1000) / 100;
                um = (resultadoa / 1000) % 10;
                dem = ((resultadoa / 1000) % 100) / 10;
                cem = resultadoa / 100000;

                if (unidades == cem && decenas == dem && centenas == um && resultadoa > resultado) {
                    // Es un palíndromo
                    mayor1 = i;
                    mayor2 = j;
                    resultado = resultadoa;
                }
            }
        }
    }

    cout << mayor1 << " * " << mayor2 << " = " << resultado << endl;

    return 0;
}