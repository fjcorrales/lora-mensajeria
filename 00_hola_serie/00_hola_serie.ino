//ESPACIO DE CONSTANTES
const unsigned long SEGUNDO = 1000;

//ESPACIO DE VARIABLES
int x = 0;
unsigned long ultimaVez = 0;
bool pausa = true;
String nombreUsuario = "Anonimo";
String sala = "general";
String historial[5];

void setup() {
  Serial.begin(115200);
  delay(2000);
}

void loop() {
  
  //Bloque de contador
  if((millis() - ultimaVez) >= SEGUNDO && !pausa){

    //Serial.println("Hola: " + String(x));
    //ultimaVez = millis();
    //x = x + 1; 

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

    }else if(comando.startsWith("/historial ") || comando.equals("/historial")){

      Serial.println("Los ultimos cinco mensajes han sido: ");
      for (int i = 0; i < 5; i++){
        
        if(historial[i].length() != 0){

          Serial.println(historial[i]);

        }

      }

    }else{
      
      historial[x] = "[" + sala + "] " + nombreUsuario + ": " + comando;
      if(x<4){
        x++;
      }else{
        x = 0;
      }

      Serial.println("[" + sala + "] " + nombreUsuario + ": " + comando);
    
    }

  }

}