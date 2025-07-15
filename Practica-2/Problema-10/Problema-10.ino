//Problema 10 https://www.tinkercad.com/things/7ycxEOXMnAZ-practica-2-p10
String romano = "";  // Variable para almacenar el número romano ingresado
int arabigo = 0;     // Variable para almacenar el resultado en formato arábigo

// Función que convierte un carácter romano en su valor arábigo
int valorRomano(char c) {
  switch (c) {
    case 'M': return 1000;  // 'M' es 1000
    case 'D': return 500;   // 'D' es 500
    case 'C': return 100;   // 'C' es 100
    case 'L': return 50;    // 'L' es 50
    case 'X': return 10;    // 'X' es 10
    case 'V': return 5;     // 'V' es 5
    case 'I': return 1;     // 'I' es 1
    default: return 0;      // Si el carácter no es válido, retorna 0
  }
}

void setup() {
  Serial.begin(9600);   // Inicializa la comunicación serial a 9600 baudios
  while (!Serial) {}    // Espera hasta que el monitor serial esté listo
  Serial.println("Ingresa un numero romano (en mayusculas):");  // Solicita al usuario que ingrese un número romano
}

void loop() {
  if (Serial.available() > 0) {  // Verifica si hay datos disponibles en el monitor serial
    romano = Serial.readStringUntil('\n');  // Lee la entrada del usuario hasta el salto de línea
    romano.trim();  // Elimina los espacios en blanco al principio y al final de la cadena

    arabigo = 0;  // Reinicia el valor del número arábigo

    int longitud = romano.length();  // Obtiene la longitud de la cadena ingresada

    // Recorre cada carácter de la cadena romana
    for (int i = 0; i < longitud; i++) {
      // Obtiene el valor arábigo del carácter romano actual
      int actual = valorRomano(romano.charAt(i));  
      // Obtiene el valor del siguiente carácter (o 0 si es el último)
      int siguiente = (i + 1 < longitud) ? valorRomano(romano.charAt(i + 1)) : 0;  

      // Si el valor actual es menor que el siguiente, se resta del total
      if (actual < siguiente) {
        arabigo -= actual;  
      } else {  // Si no, se suma al total
        arabigo += actual;  
      }
    }

    // Imprime el número romano ingresado y su equivalente arábigo
    Serial.print("El numero ingresado fue: ");
    Serial.println(romano);
    Serial.print("Que corresponde a: ");
    Serial.println(arabigo);
    
    // Solicita otro número romano
    Serial.println("\nIngresa otro numero romano:");
    delay(500);  // Espera medio segundo antes de continuar
  }
}