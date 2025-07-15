//Problema 6 https://www.tinkercad.com/things/e5QAgiczudQ-practica-2-p6
void setup() {
    Serial.begin(9600);  // Iniciar la comunicación serial
    Serial.println("Ingresa una cadena de texto:");
}

void loop() {
    if (Serial.available() > 0) {
        char palabra[50] = {0};  
        int indice = 0;
        delay(100);  
        while (Serial.available() > 0) {
            char c = Serial.read();
            if (c == '\n') {  
                palabra[indice] = '\0';  
                break;
            }
            if (indice < 49) {  
                palabra[indice++] = c;
            }
        }
        palabra[indice] = '\0';
        Serial.print("Original: ");
        Serial.println(palabra);
        for (int i = 0; palabra[i] != '\0'; i++) {
            if (palabra[i] >= 'a' && palabra[i] <= 'z') {
                palabra[i] = palabra[i] - (32);  
            }
        }
        Serial.print("En mayusculas: ");
        Serial.println(palabra);
        Serial.println("Ingresa otra cadena:");
    }
}