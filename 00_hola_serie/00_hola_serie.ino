//ESPACIO DE CONSTANTES
const unsigned long SEGUNDO = 1000;

//ESPACIO DE VARIABLES
int x = 0;
unsigned long ultimaVez = 0;
bool pausado = true;
String nombreUsuario = "Anonimo";
String sala = "general";
String historial[5];

void setup() {
  Serial.begin(115200);
  delay(2000);
}

void loop() {
  
  //Bloque de contador
  if((millis() - ultimaVez) >= SEGUNDO && !pausado){

    //Serial.println("Hola: " + String(x));
    //ultimaVez = millis();
    //x = x + 1; 

  }

  //Bloque de eco
  if(Serial.available()){

    String comando = Serial.readStringUntil('\n');
    comando.trim();
    if(comando.length()==0){return;}    //control de mensaje vacio

    if(comando.startsWith("/")){
      if(comando.equals("/")){
        Serial.println("Comandos aceptados actualmente:");
        Serial.println("/pausa: pausa la ejecucion del contador");
        Serial.println("/seguir: reinicia la ejecucion del contador");
        Serial.println("/nombre [nombre]: cambia el nombre del remitente o devuelve el nombre actual");
        Serial.println("/sala [nombre de sala]: cambia la sala o devuelve la sala actual");
        Serial.println("/historial: devuelve los ultimos 5 mensajes enviados");
      }else if(comando.startsWith("/pausa ") || comando.equals("/pausa")){
        pausa();
      }else if(comando.startsWith("/seguir ") || comando.equals("/seguir")){
        seguir();
      }else if(comando.startsWith("/nombre ") || comando.equals("/nombre")){
        nombre(comando);
      }else if(comando.startsWith("/sala ") || comando.equals("/sala")){
        cambioSala(comando);
      }else if(comando.startsWith("/historial ") || comando.equals("/historial")){
        printHistorial(); 
      }else{
        Serial.println("El comando introducido no esta registrado escribe '/' para recibir el listado de comandos disponibles");
      }
    }else{
      guardarMsg(comando);
    }
  }
}

//ESPACIO DE FUNCIONES
void pausa(){
  pausado = true;
  Serial.println("Contador pausado");
}

void seguir(){
  pausado = false;
  Serial.println("Contador reanudado");
}

void nombre(String comando){
  String nombreUsuario2 = comando.substring(8);
  nombreUsuario2.trim();
  if(nombreUsuario.equals(nombreUsuario2) || nombreUsuario2.length() == 0){

    Serial.println("Tu nombre actual es: " + nombreUsuario);

  }else{
      
    Serial.println("Nombre registrado: " + nombreUsuario2);
    nombreUsuario = nombreUsuario2;

  }
}

void cambioSala(String comando){
  String sala2 = comando.substring(6);
  sala2.trim();
  if(sala.equals(sala2) || sala2.length() == 0){

    Serial.println("Estas actualmente en la sala: " + sala);

  }else{
      
    Serial.println("Has cambiado a la sala: " + sala2);
    sala = sala2;

  }
}

void guardarMsg(String comando){
  String linea = "[" + sala + "] " + nombreUsuario + ": " + comando;
  historial[x] = linea;
  if(x<4){
    x++;
  }else{
    x = 0;
  }
  Serial.println(linea);
}

void printHistorial(){
  Serial.println("Historial: ");
  for (int i = 0; i < 5; i++){
    int indice = (x+i)%5;
    if(historial[indice].length() != 0){

      Serial.println(historial[indice]);

    }
  }  
}
