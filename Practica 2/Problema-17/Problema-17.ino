// Problema 17: Numeros Amigables en Arduino
// El usuario ingresa un numero por el monitor serial
// El programa encuentra la suma de todos los numeros amigables menores o iguales a ese numero
// Ejemplo: si se ingresa 284, se detecta el par 220 y 284, y se suma 220 + 284 = 504

// Funcion que retorna la suma de los divisores propios de n (excluye n)
int sumaDivisores(int n) {
  int suma = 0;
  for (int i = 1; i <= n / 2; i++) {
    if (n % i == 0) {
      suma += i;
    }
  }
  return suma;
}

// Funcion que verifica si dos numeros son amigables
bool sonAmigables(int a, int b) {
  return sumaDivisores(a) == b && sumaDivisores(b) == a;
}

void setup() {
  Serial.begin(9600); // Inicializa comunicacion serial
  while (!Serial) {
    ; // Espera a que la conexion Serial se establezca
  }

  // Mensaje de bienvenida e instrucciones
  Serial.println("Ingrese un numero entero mayor a 1 para hallar la suma de numeros amigables menores o iguales a ese numero:");
}

void loop() {
  static bool procesado = false; // Evita que se procese multiples veces

  if (Serial.available() > 0 && !procesado) {
    int limite = Serial.parseInt(); // Lee el numero ingresado por el usuario

    if (limite <= 1) {
      Serial.println("Debe ingresar un numero mayor a 1.");
      procesado = true;
      return;
    }

    int sumaTotal = 0; // Variable para almacenar la suma total de numeros amigables

    for (int a = 2; a <= limite; a++) {
      int b = sumaDivisores(a);
      // Verificamos si a y b son amigables, diferentes, y que a < b para no contar pares duplicados
      if (b != a && b <= limite && a < b && sonAmigables(a, b)) {
        sumaTotal += a + b; // Sumar ambos numeros del par amigable
      }
    }

    Serial.print("El resultado de la suma es: ");
    Serial.println(sumaTotal);

    procesado = true; // Marca como procesado para que no se repita
  }
}