//Problema 1 https://www.tinkercad.com/things/k7DeisWRZXy-practica-2-p1
unsigned long int plata;

void setup() {
    Serial.begin(9600);
    Serial.println("Ingrese una cantidad de dinero:");
}

void loop() {
while (Serial.available() == 0) {
    }
    plata = Serial.parseInt();
    Serial.println(plata);
    if (plata >= 50000) {
        Serial.print("50000: ");
        Serial.println(plata / 50000);
        plata %= 50000;
    } else {
        Serial.println("50000: 0");
    }

    if (plata >= 20000) {
        Serial.print("20000: ");
        Serial.println(plata / 20000);
        plata %= 20000;
    } else {
        Serial.println("20000: 0");
    }

    if (plata >= 10000) {
        Serial.print("10000: ");
        Serial.println(plata / 10000);
        plata %= 10000;
    } else {
        Serial.println("10000: 0");
    }

    if (plata >= 5000) {
        Serial.print("5000: ");
        Serial.println(plata / 5000);
        plata %= 5000;
    } else {
        Serial.println("5000: 0");
    }

    if (plata >= 2000) {
        Serial.print("2000: ");
        Serial.println(plata / 2000);
        plata %= 2000;
    } else {
        Serial.println("2000: 0");
    }

    if (plata >= 1000) {
        Serial.print("1000: ");
        Serial.println(plata / 1000);
        plata %= 1000;
    } else {
        Serial.println("1000: 0");
    }

    if (plata >= 500) {
        Serial.print("500: ");
        Serial.println(plata / 500);
        plata %= 500;
    } else {
        Serial.println("500: 0");
    }

    if (plata >= 200) {
        Serial.print("200: ");
        Serial.println(plata / 200);
        plata %= 200;
    } else {
        Serial.println("200: 0");
    }

    if (plata >= 100) {
        Serial.print("100: ");
        Serial.println(plata / 100);
        plata %= 100;
    } else {
        Serial.println("100: 0");
    }

    if (plata >= 50) {
        Serial.print("50: ");
        Serial.println(plata / 50);
        plata %= 50;
    } else {
        Serial.println("50: 0");
    }

    if (plata > 0) {
        Serial.print("Faltante: ");
        Serial.println(plata);
    }

}