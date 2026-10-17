//ESPACIO DE CONSTANTES
const unsigned long SEGUNDO = 1000;

//ESPACIO DE VARIABLES
int number = 0;
unsigned long ultimaVez = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);
}

void loop() {
  
  //Bloque de contador
  if((millis() - ultimaVez) >= SEGUNDO){

    Serial.println("Hola: " + String(number));
    ultimaVez = millis();
    number = number + 1; 

  }

  //Bloque de eco
  if(Serial.available()){

    Serial.println("La ESP32 ha leído: " + Serial.readStringUntil('\n'));

  }

}