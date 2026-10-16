int number = 0;
void setup() {
  Serial.begin(115200);
  delay(2000);
}

void loop() {

  Serial.println("Hola: " + String(number));
  //Serial.println(number);
  

  if(Serial.available()){

    Serial.println("La ESP32 ha leído: " + Serial.readStringUntil('\n'));

  }
  delay(1000);
  number = number + 1;  
}