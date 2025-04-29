//Practica 1. Grupo
//Hugo Esteban Barrero Garcia. C.C: 1021923268
//Ivonne Lizeth Rosero Cardona. C.C: 1007687589
#include <iostream>

using namespace std;

int potencia(int base, int exponente) {
    int resultado = 1;
    for (int i = 0; i < exponente; i++) {
        resultado *= base;
    }
    return resultado;
}
int MCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int MCM(int a, int b) {
    return (a / MCD(a, b)) * b;
}
int main() {
    /*
    Ejercicio 1. Escriba un programa que pida dos números A y B e imprima en pantalla el residuo
    de la división A/B. Ej: si se ingresan 8 y 3 se debe imprimir: El residuo de la division 8/3 es: 2
    signed int a, b;
    cout << "Ingrese un numero entero positivo entero para dividirlo y obtener un residuo: ";
    cin >> a;
    cout << "Ingrese el numero entero positivo por el cual lo quiere dividir: ";
    cin >> b;
    cout << endl;
    cout << "El residuo de la division: " << a << "/" << b << " es: " << a%b << endl;
    */
    /*
    Ejercicio 2. Escriba un programa que pida un número N e imprima en pantalla si es par o impar.
    Ej: si se ingresa 5 se debe imprimir: 5 es impar
    signed int N;
    cout << "Ingrese un numero numero entero positivo para saber si es par o impar: ";
    cin >> N;
    if (N%2 == 0)
    {
        cout << endl;
        cout <<"El numero " << N << " es par." << endl;
    }
    else
    {
        cout << endl;
        cout <<"El numero " << N << " es impar." << endl;
    }
    */
    /*
    Ejercicio 3. Escriba un programa que pida dos números A y B e imprima en pantalla el mayor.
    signed int a, b;
    cout << "Ingrese dos numeros enteros positivos para saber cual es mayor: ";
    cin >> a;
    cout << "Ahora ingrese el segundo numero entero positivo para compararlos: ";
    cin >> b;
    cout << endl;
    if (a > b )
    {
        cout << endl;
        cout <<"El numero mayor es el: " << a << endl;
    }
    else
    {
        cout << endl;
        cout <<"El numero mayor es el: " << b <<  endl;
    }
    */
    /*
    Ejercicio 4. Escriba un programa que pida dos números A y B e imprima en pantalla el menor.
    signed int a, b;
    cout << "Ingrese dos numeros enteros positivos para saber cual es mayor: ";
    cin >> a;
    cout << "Ahora ingrese el segundo numero entero positivo para compararlos: ";
    cin >> b;
    cout << endl;
    if (a < b )
    {
        cout << endl;
        cout <<"El numero menor es el: " << a << endl;
    }
    else
    {
        cout << endl;
        cout <<"El numero menor es el: " << b <<  endl;
    }
    */
    /*
    Ejercicio 5. Escriba un programa que pida dos números A y B e imprima en pantalla la división A/B con redondeo.
    signed int a, b;
    cout << "Ingrese un numero entero positivo para dividirlo y obtener el resultado (si el resultado no es exacto, se aproxima): ";
    cin >> a;
    cout << "Ingrese el numero entero positivo por el cual lo quiere dividir: ";
    cin >> b;
    cout << endl;
    cout << "El resultado de la division: " << a << "/" << b << " es: " << a/b << endl;
    */
    /*
    Ejercicio 6. Escriba un programa que pida dos números A y B e imprima en pantalla la potencia AB, sin hacer uso de librerías matemáticas.
    signed int a, b, c;
    c = 1;
    cout << "Ingrese un entero positivo para saber su potencia: ";
    cin >> a;
    cout << "Ahora ingrese la potencia a la cual lo quiere elevar, como un entero positivo: ";
    cin >> b;
    cout << endl;
    for (short int i = 1; i <= b; i++){
             c = c * a;
        }
    cout << "El resultado de la potencia: " << a << "^" << b << " es: " << c << endl;
    */
    /*
    Ejercicio 7. Escriba un programa que pida un número N e imprima en pantalla la suma de todos los números entre 0 y N (incluyéndose el mismo).
    signed int a, b;
    b = 0;
    cout << "Ingrese un entero positivo para obtener la suma de todos los numeros entre el cero y ese numero: ";
    cin >> a;
    for (short int i = 0; i <= a; i++){
        b = b + i;
    }
    cout << endl;
    cout << "La sumatoria desde 0 hasta " << a << " es: " << b << endl;
    */
    /*
    Ejercicio 8. Escriba un programa que pida un número N e imprima en pantalla su factorial.
    signed int a, b;
    b = 1;
    cout << "Ingrese un entero positivo para obtener su factorial: ";
    cin >> a;
    for (short int i = 1; i <= a; i++){
        b = b * i;
    }
    cout << endl;
    cout << "El factorial de " << a << " es: " << b << endl;
    */
    /*
    Ejercicio 9. Escriba un programa que pida un número N e imprima el perímetro y área de un círculo con radio N. Nota: use 3.1416 como una aproximación de pi.
    signed int a;
    cout << "Ingrese un el radio de un circulo como un entero positivo para obtener su perimetro y area: ";
    cin >> a;
    cout << endl;
    cout << "El area del circulo es: " << 3.1416*a*a <<endl;
    cout << "El perimetro del circulo es: " << 2*3.1416*a <<endl;
    */
    /*
    Ejercicio 13. Escriba un programa que pida un número N e imprima todos los divisores de N.
    signed int a;
    a = 0;
    cout << "Ingrese un entero positivo para saber sus divisores: ";
    cin >> a;
    cout << endl;
    cout << "Divisores de " << a << " son: " << endl;
    for (short int i = 1; i <= a; i++){
        if (a%i == 0)
        {
            cout << i << endl;
        }
    }
    */
    /*Ejercicio 19. Escriba un programa que pida un número N e imprima si es o no un número primo.
    signed int p;
    cout << "Ingrese un numero entero positivo para saber si es primo: ";
    cin >> p;
    cout << endl;
    if (p <= 1) {
        cout << p << " no es un numero primo." << endl;
    }
    else {
        bool primo = true;
        for (int i = 2; i * i <= p; i++) {
            if (p % i == 0) {
                primo = false;
                break;
            }
    }
    if (primo == true) {
            cout << p << " es un numero primo." << endl;
        } else {
            cout << p << " no es un numero primo." << endl;
    }
    }
    */
    char letra;

    cout << "Ingrese un caracter: ";
    cin >> letra;
    cout << endl;

    if (letra >= 'A' && letra <= 'Z') {
        letra = letra + 32; // Convertir a minúscula
    }

    cout << "El caracter ingresado '" << letra << "':";

    switch (letra) {
    case 'a': case 'e': case 'i': case 'o': case 'u':
        cout << " es una vocal." << endl;
        break;
    default:
        if ((letra >= 'b' && letra <= 'z') && letra != 'e' && letra != 'i' && letra != 'o' && letra != 'u') {
            cout << " es una consonante." << endl;
        } else {
            cout << " no es una letra." << endl;
        }
    }
    /*
    Problema 1. Escriba un programa que identique si un carácter ingresado es una vocal, una consonante o ninguna de las 2 e imprima un mensaje según el caso.
    char letra;
    cout << "Ingrese un caracter: ";
    cin >> letra;
    cout << endl;
    if (letra >= 'A' && letra <= 'Z'){
        cout << "El caracter ingresado '" << letra << "':";
        letra = letra+32;
    }
    else {
        cout << "El caracter ingresado '" << letra << "':";
    }

    switch (letra) {
    case 'a': case 'e': case 'i': case 'o': case 'u':
        cout << " es una vocal." << endl;
        break;
    default:
        if ((letra >= 'b' && letra <= 'z')) {
            cout << " es una consonante." << endl;
        } else {
            cout << " no es una letra." << endl;
        }
    }
    */

    //Problema 2. Hacer un programa que entregue el número de billetes y monedas de cada denominación para completar la cantidad deseada.
    /*
    int valor, vuelto, aux;

    cout << "ingrese un valor: ";
    cin >> valor;

    aux = valor / 50000;
    vuelto = valor % 50000;
    cout<<"billetes de 50.000 :"<<aux<<endl;

    aux=vuelto/20000;
    vuelto=vuelto%20000;
    cout<<"billetes de 20.000 :"<<aux<<endl;

    aux=vuelto/10000;
    vuelto=vuelto%10000;
    cout<<"billetes de 10.000 :"<<aux<<endl;

    aux=vuelto/5000;
    vuelto=vuelto%5000;
    cout<<"billetes de 5.000 :"<<aux<<endl;

    aux=vuelto/2000;
    vuelto=vuelto%2000;
    cout<<"billetes de 2.000 :"<<aux<<endl;

    aux=vuelto/1000;
    vuelto=vuelto%1000;
    cout<<"billetes de 1.000 :"<<aux<<endl;

    aux=vuelto/500;
    vuelto=vuelto%500;
    cout<<"monedas de 500 :"<<aux<<endl;

    aux=vuelto/200;
    vuelto=vuelto%200;
    cout<<"monedas de 200 :"<<aux<<endl;

    aux=vuelto/100;
    vuelto=vuelto%100;
    cout<<"monedas de 100 :"<<aux<<endl;

    aux=vuelto/50;
    vuelto=vuelto%50;
    cout<<"monedas de 50 :"<<aux<<endl;

    vuelto=vuelto%50;
    cout<<"restante :"<<vuelto<<endl;
    */
    /*
    Problema 2. Hacer un programa que entregue el número de billetes y monedas de cada denominación para completar la cantidad deseada.
    int plata;
    cout << "Ingrese la cantidad de dinero para determinar la menor cantidad de billetes y monedas para completarla: ";
    cin >> plata;
    cout << endl;
    if (plata >= 50000) {
        cout << "50000: " << plata / 50000 << endl;
        plata %= 50000;
    } else {
        cout << "50000: 0" << endl;
    }

    if (plata >= 20000) {
        cout << "20000: " << plata / 20000 << endl;
        plata %= 20000;
    } else {
        cout << "20000: 0" << endl;
    }

    if (plata >= 10000) {
        cout << "10000: " << plata / 10000 << endl;
        plata %= 10000;
    } else {
        cout << "10000: 0" << endl;
    }

    if (plata >= 5000) {
        cout << "5000: " << plata / 5000 << endl;
        plata %= 5000;
    } else {
        cout << "5000: 0" << endl;
    }

    if (plata >= 2000) {
        cout << "2000: " << plata / 2000 << endl;
        plata %= 2000;
    } else {
        cout << "2000: 0" << endl;
    }

    if (plata >= 1000) {
        cout << "1000: " << plata / 1000 << endl;
        plata %= 1000;
    } else {
        cout << "1000: 0" << endl;
    }

    if (plata >= 500) {
        cout << "500: " << plata / 500 << endl;
        plata %= 500;
    } else {
        cout << "500: 0" << endl;
    }

    if (plata >= 200) {
        cout << "200: " << plata / 200 << endl;
        plata %= 200;
    } else {
        cout << "200: 0" << endl;
    }

    if (plata >= 100) {
        cout << "100: " << plata / 100 << endl;
        plata %= 100;
    } else {
        cout << "100: 0" << endl;
    }

    if (plata >= 50) {
        cout << "50: " << plata / 50 << endl;
        plata %= 50;
    } else {
        cout << "50: 0" << endl;
    }

    if (plata > 0) {
        cout << "Faltante: " << plata << endl;
    }
    */
    /*
    Problema 3. Escriba un programa que debe leer un mes y un día de dicho mes para luego decir si esa combinación de mes y día son válidos. El caso más especial es el 29 de febrero, en dicho caso imprimir posiblemente año bisiesto.
    signed short int mes, dia;
    cout << "Ingrese una fecha en forma numerica para saber si es valida o no, primeramente ingrese el numero del mes como un entero positivo: ";
    cin >> mes;
    cout << endl;
    if (mes > 0 && mes <= 12){
        cout << "Ahora ingrese el dia de esa fecha: ";
        cin >> dia;
        cout << endl;
        if (dia > 0 && dia <= 31){
            if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && (dia == 31)){
                cout << "La fecha " << dia << "/" << mes << " es invalida.";
            }
            else if (mes == 2 && dia > 28 ){
                if (dia == 29){
                    cout << "La fecha " << dia << "/" << mes << " es valida en bisiesto.";
                }
                else {
                    cout << "La fecha " << dia << "/" << mes << " es invalida.";
                }

            }
            else {
                cout << "La fecha " << dia << "/" << mes << " es valida.";
            }
        }
        else {
            cout << "La fecha " << dia << "/" << mes << " es invalida (ingrese el dia como un numero entre 1-31(dependiendo del mes))." << endl;
        }
    }
    else {
        cout << "Esa fecha es invalida (ingrese el mes como un numero entre 1-12)." << endl;
    }
    */
    /*Problema 4. Escriba un programa para leer dos números enteros con el siguiente signicado: el valor del primer número representa una hora del día en un reloj de 24 horas, de modo que 1245 representa las doce y cuarenta y cinco de la tarde.
    El segundo entero representa un tiempo de duración de la misma manera, por lo que 345 representa tres horas y 45 minutos.
    int horacompleta1, horacompleta2, minuto1, minuto2, hora1, hora2, resultado1, resultado2;

    cout << "Ingrese la primera hora sin puntos ni espacios: ";
    cin >> horacompleta1;

    cout << "Ingrese la segunda hora sin puntos ni espacios: ";
    cin >> horacompleta2;

    hora1 = horacompleta1 / 100;
    minuto1 = horacompleta1 % 100;
    hora2 = horacompleta2 / 100;
    minuto2 = horacompleta2 % 100;

    if (hora1 >= 24 || hora2 >= 24){
        cout << "Ingrese una hora del 0 al 23" << endl;
        return 0;
    }
    else if (minuto1 >= 60 || minuto2 >= 60){
        cout << "Ingrese minutos del 0 al 59" << endl;
        return 0;
    }
    else {
        resultado1 = hora1 + hora2;
        resultado2 = minuto1 + minuto2;

    }

    if (resultado2 >= 60) {
        resultado1 += resultado2 / 60;
        resultado2 %= 60;
    }

    if (resultado1 >= 24) {
        resultado1 %= 24;
    }

    cout << "La suma de las horas es: " << resultado1 << ":" << resultado2 << endl;
    */
    /*
    Problema 5. Escriba un programa que muestre el siguiente patrón en la pantalla:
    signed int x;
    while (true){
    cout << "Ingrese un entero positivo impar para imprimir un patron de asteriscos en la pantalla:";
    cin >> x;
    cout << endl;
    if (x%2 != 0){
        for (short int i = 1; i <= x; i += 2 ){
                for (short int j = i; j < x; j+=2 ){
                    cout << " ";
                }
                for (short int k = 0; k < i ; k++){
                    cout << "*";
                }
                cout <<endl;
            }
        for (short int i = x-2; i >= 1; i -= 2 ){
                for (short int j = i; j < x; j+=2 ){
                    cout << " ";
                }
                for (short int k = 0; k < i ; k++){
                    cout << "*";
                }
                cout <<endl;
        }
        break;
    }
    else {
        cout << "Por favor ingrese lo que se le pide, ingrese un numero impar." << endl;
    }
    }
    */
    /*
    Problema 6. Escriba un programa que encuentre el valor aproximado del número de euler en base a la siguiente suma infita:
    int x,factorial;
    double resultado=0;
    cout<<"introduce el numero de elementos del arreglo: ";
    cin>>x;
    for(int i=0;i<x;i++){
        if (i==0){
            factorial=1;
        }
        else {
            factorial=factorial*i;
        }

        resultado = resultado + 1.0/factorial;
    }
    cout << "e es aproximadamente: "<<resultado;
    */
    /*
    Problema 7. En la serie de Fibonacci, cada número es la suma de los 2 anteriores. Escriba un programa que reciba un número n y halle la suma de todos los números pares en la serie de Fibonacci menores a n.
    signed int n;
    cout << "Ingrese un numero entero positivo para sacar la suma de todos los pares en la serie de Fibonacci menores a n: ";
    cin >> n;
    cout << endl;
    int a = 1, b = 1, suma = 0, serie;
    while (b < n) {
        if (b % 2 == 0) {
            suma += b;
        }
        serie = a + b;
        a = b;
        b = serie;
    }
    cout << "El resultado de la suma es: " << suma << endl;
    */
    /*
    //Problema 8. Escriba un programa que reciba 3 números a, b, c, y calcule la suma de todos los múltiplos de a y b que sean menores a c. Tenga en cuenta no sumar 2 veces los múltiplos comunes.
    int a, b, c, multiplo;
    int ctd1=1, ctd2 =1;
    int sumatoria=0;
    bool bandera=true;
    cout <<"introduce a:";
    cin>>a;
    cout<<"introduce b:";
    cin>>b;
    cout<<"introduce c:";
    cin>>c;

    multiplo = a*ctd1;
    while(multiplo<c){
        sumatoria += multiplo;
        cout << multiplo<< " + ";
        ctd1 += 1;
        multiplo = a*ctd1;
    }

    multiplo = b*ctd2;
    while(multiplo<c){
        for (int i = 1; i<=ctd1;i++){
            if(a*i==multiplo){
                bandera = false;
            }
        }
        if (bandera == true){
            sumatoria += multiplo;
            cout << multiplo<< " + ";
        }
        else{
            bandera = true;
        }
        ctd2 += 1;
        multiplo = b*ctd2;
    }
    cout << " = "<<sumatoria;
    */
    /*
    Problema 9. Escriba un programa que pida un número entero N e imprima el resultado de la suma de todos sus dígitos elevados a sí mismos.
    signed int n;
    cout << "Ingrese un numero entero positivo para saber el resultado de la suma de todos sus digitos elevados a si mismos: ";
    cin >> n;
    cout << endl;
    int suma = 0;
    int numero = n;
    while (numero > 0) {
        int digito = numero % 10;
        suma += potencia(digito, digito);
        numero /= 10;
    }
    cout << "El resultado de la suma es: " << suma << endl;
    */
    /*Problema 11. Escriba un programa que reciba un número y calcule el mínimo común múltiplo de todos los números enteros entre 1 y el número ingresado.
    signed int N;
    cout << "Ingrese un numero entero positivo para hallar el minimo comun multiplo de todos los numeros entre el 1 y el numero: ";
    cin >> N;
    cout << endl;
    signed int resultado = 1;
    for (int i = 2; i <= N; i++) {
        resultado = MCM(resultado, i);
    }
    cout << "El minimo comun multiplo es: " << resultado << endl;
    */
    /*
    Problema 12. Escriba un programa que calcula el máximo factor primo de un número.
    int x, ctd = 0, aux = 2,primo=1;
    bool bandera;

    cout << "ingrese el numero: ";
    cin >> x;


    for (int i = 2; i  <= x; i++) {
        bandera=true;
        if (x % i == 0) {
            for(int j = 2; j * j<=aux;j++){
                if(aux % j==0){
                    bandera=false;
                    break;
                }
            }
            if(bandera){
                primo=aux;
            }
        }
        aux += 1;
    }
    cout << "El mayor factor primo de: "<< x <<" es: "<<primo;
    */
    /*Problema 13. Escriba un programa que reciba un número y calcule la suma de todos los primos menores que el número ingresado.
    signed int p;
    cout << "Ingrese un numero entero positivo para calcular la suma de todos los primos menores a este: " << endl;
    cin >> p;
    cout << endl;
    signed int suma = 0;
    for (int num = 2; num < p; num++) {
        bool primo = true;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                primo = false;
                break;
            }
        }
        if (primo) {
            suma += num;
        }
    }
    cout << "El resultado de la suma es: " << suma << endl;
    */
    /*
    Problema 15. Empezando con el número 1 y moviéndose hacia la izquierda y en sentido horario se genera una espiral de números como la siguiente:
    int n;
    cout << "Ingrese un numero impar: ";
    cin >> n;
    if (n % 2 == 0) {
        cout << "El numero debe ser impar." << endl;
        return 0;
    }
    int matriz[n][n] = {0};
    int num = 1;
    int x = n / 2, y = n / 2;
    int dx = -1, dy = 0;
    int pasos = 1, cambios = 0;

    while (num <= n * n) {
        for (int i = 0; i < pasos; i++) {
            if (num > n * n) break;
            matriz[y][x] = num++;
            x += dx;
            y += dy;
        }
        cambios++;
        if (cambios == 2) {
            cambios = 0;
            pasos++;
        }
        int temp = dx;
        dx = dy;
        dy = -temp;
    }

    int suma = 0;
    for (int i = 0; i < n; i++) {
        suma += matriz[i][i];
        if (i != n - 1 - i) suma += matriz[i][n - 1 - i];
    }

    cout << "En una espiral de " << n << "x" << n << ", la suma es: " << suma << "." << endl;

    cout << "Espiral generada:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
    */
    /*
    Problema 16. La serie de Collatz se conforma con la siguiente regla: sea n un elemento de la serie, si n es par, el siguiente elemento es n/2, y si n es impar, el siguiente elemento es 3n+1.
    int x, aux = 0,semilla=0,ctd=0,ctdn=0;

    cout << "ingrese el numero: ";
    cin >> x;
    for(int i=x-1; i >1;i--){
        aux = i;
        ctd=0;
        while(aux != 1){
            if(aux%2==0){
                aux = aux/2;
                ctd+=1;
            }
            else{
                aux = (aux*3)+1;
                ctd+=1;
            }
        }
        if(ctd>ctdn){
            ctdn=ctd;
            semilla = i;
        }
    }
    cout<<"La serie mas larga es con la semilla: "<< semilla <<" , teniendo "<< ctdn<<" terminos";
    */
    /*
    Problema 17. La secuencia de números triangulares se forma al sumar su posición en el arreglo con el valor del número anterior: 1, 1+2=3, 3+3=6, 6+4=10, 10+5=15, 15+6=21, 21+7=28...  Si listamos los números triangulares y sus divisores tenemos:
    int k;
    cout << "Ingrese un numero k: ";
    cin >> k;
    cout << endl;
    int n = 1, triangular = 1, count;

    while (true) {
        count = 0;
        for (int i = 1; i * i <= triangular; i++) {
            if (triangular % i == 0) {
                count++;
                if (i != triangular / i) count++;
            }
        }
        if (count > k) {
            cout << "El numero es: " << triangular << " que tiene " << count << " divisores." << endl;
            break;
        }
        n++;
        triangular = n * (n + 1) / 2;
    }
    */

}
