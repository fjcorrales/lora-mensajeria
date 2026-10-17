//ESPACIO DE CONSTANTES
const unsigned long SEGUNDO = 1000;

//ESPACIO DE VARIABLES
int number = 0;
unsigned long ultimaVez = 0;
bool pausa = true;
String nombreUsuario = "Anonimo";
String sala = "general";

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

    }else if(comando.startsWith("/nombre ") || comando.equals("/nombre")){

      String nombreUsuario2 = comando.substring(8);
      nombreUsuario2.trim();
      if(nombreUsuario.equals(nombreUsuario2) || nombreUsuario2.length() == 0){

        Serial.println("Tu nombre actual es: " + nombreUsuario);

      }else{
      
        Serial.println("Nombre registrado: " + nombreUsuario2);
        nombreUsuario = nombreUsuario2;

      }
      
      

    }else if(comando.startsWith("/sala ") || comando.equals("/sala")){

      String sala2 = comando.substring(6);
      sala2.trim();
      if(sala.equals(sala2) || sala2.length() == 0){

        Serial.println("Estas actualmente en la sala: " + sala);

      }else{
      
        Serial.println("Has cambiado a la sala: " + sala2);
        sala = sala2;

      }

    }else{

      Serial.println("[" + sala + "] " + nombreUsuario + ": " + comando);
    
    }

  }

}