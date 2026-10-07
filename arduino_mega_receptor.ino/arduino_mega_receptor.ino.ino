const int pinEntradaESP = 2;
const int pinRele = 3;
const int ledInterno = 13; 

void setup() {
  Serial.begin(9600);
  pinMode(pinEntradaESP, INPUT); // CRÍTICO: INPUT normal, no INPUT_PULLUP
  pinMode(pinRele, OUTPUT);
  pinMode(ledInterno, OUTPUT);
  
  // La mayoría de los relés de 5V se activan con LOW. 
  // Iniciamos apagándolo.
  digitalWrite(pinRele, HIGH); 
}

void loop() {
  int estadoESP = digitalRead(pinEntradaESP);
  
  if (estadoESP == HIGH) {
    digitalWrite(ledInterno, HIGH); // Prende LED interno
    digitalWrite(pinRele, LOW);     // Activa el relé (lógica inversa)
    Serial.println("Señal recibida: ON");
  } else {
    digitalWrite(ledInterno, LOW);  // Apaga LED interno
    digitalWrite(pinRele, HIGH);    // Desactiva el relé
  }
}