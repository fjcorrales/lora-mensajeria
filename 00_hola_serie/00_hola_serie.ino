//ESPACIO DE CONSTANTES
const unsigned long SEGUNDO = 1000;

//ESPACIO DE VARIABLES
int number = 0;
unsigned long ultimaVez = 0;
bool pausa = true;
String nombreUsuario = "Anonimo";

void setup() {
  Serial.begin(115200);
  delay(2000);
}

void loop() {
  
  //Bloque de contador
  if((millis() - ultimaVez) >= SEGUNDO && !pausa){

    //Serial.println("Hola: " + String(number));
    //ultimaVez = millis();
    //number = number + 1; 

  }

  //Bloque de eco
  if(Serial.available()){

    String comando = Serial.readStringUntil('\n');
    comando.trim();

    if(comando=="pausa"){

      pausa = true;
      Serial.println("Contador pausado");

    }else if(comando=="seguir"){

      pausa = false;
      Serial.println("Contador reanudado");

    }else if(comando.startsWith("/nombre ")){

      nombreUsuario = comando.substring(8);
      Serial.println("Nombre registrado: " + nombreUsuario);
      

    }else{

      Serial.println(nombreUsuario + ": " + comando);
    
    }

  }

}