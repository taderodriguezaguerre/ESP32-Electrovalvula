const int pinEntradaESP = 6;
const int pinRele = 7;
const int ledInterno = 13;

void setup() {
  Serial.begin(9600);

  pinMode(pinEntradaESP, INPUT);
  pinMode(ledInterno, OUTPUT);

  // Primero establecemos el estado de reposo del relé.
  // HIGH = relé apagado (módulo Active LOW).
  digitalWrite(pinRele, HIGH);
  pinMode(pinRele, OUTPUT);

  // LED interno apagado al iniciar.
  digitalWrite(ledInterno, LOW);

  Serial.println("Arduino Mega iniciado");
}

void loop() {
  int estadoESP = digitalRead(pinEntradaESP);

  if (estadoESP == HIGH) {
    // El ESP32 solicita activar la electroválvula.
    digitalWrite(ledInterno, HIGH);
    digitalWrite(pinRele, LOW);

    Serial.println("Senal recibida: ON");
  } else {
    // El ESP32 solicita desactivar la electroválvula.
    digitalWrite(ledInterno, LOW);
    digitalWrite(pinRele, HIGH);
  }
}