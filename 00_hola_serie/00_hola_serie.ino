//DEFINICION DE ESTRUCTURAS
struct Mensaje{
  String remitente;
  int indiceSala;
  String texto;
  unsigned int id = 0;
};

struct Sala{
  String nombreSala;
  Mensaje historial[5];
  int x = 0;
};

//ESPACIO DE CONSTANTES
const unsigned long SEGUNDO = 1000;
const int MAX_SALAS = 4;

//ESPACIO DE VARIABLES
//int x = 0;
//String sala = "general";
//Mensaje historial[5];

int totalSalas = 0;
int salaActual = 0;
unsigned int siguienteId = 1;   //identificador de mensajes no de usuarios
unsigned long ultimaVez = 0;
bool pausado = true;
String nombreUsuario = "Anonimo";
Sala salas[MAX_SALAS];

//SETUP Y LOOP
void setup() {
  Serial.begin(115200);
  delay(2000);
  salas[0].nombreSala = "general";
  salas[0].x = 0;
  totalSalas = 1;
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
        Serial.println("/salas: lista las salas disponibles actualmente");
        Serial.println("/historial: devuelve los ultimos 5 mensajes enviados");
      }else if(comando.startsWith("/pausa ") || comando.equals("/pausa")){
        pausa();
      }else if(comando.startsWith("/seguir ") || comando.equals("/seguir")){
        seguir();
      }else if(comando.startsWith("/nombre ") || comando.equals("/nombre")){
        nombre(comando);
      }else if(comando.startsWith("/sala ") || comando.equals("/sala")){
        cambioSala(comando);
      }else if(comando.startsWith("/salas ") || comando.equals("/salas")){
        printSalas(); 
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
  int indiceSala = buscarSala(sala2);

  if(indiceSala >= 0){
    salaActual = indiceSala;
    Serial.println("Se ha cambiado a la sala: " + salas[salaActual].nombreSala);
  }else if(sala2.length()>0){
    Sala nuevaSala;
    nuevaSala.nombreSala = sala2;
    if(totalSalas < MAX_SALAS){
      salas[totalSalas] = nuevaSala;
      salaActual = totalSalas;
      totalSalas++;
      Serial.println("Se ha creado y cambiado a la sala: " + salas[salaActual].nombreSala);
    }else{
      Serial.println("Se ha llegado al maximo numero de salas permitidas.");
    }
  }else{
    Serial.println("Actualmente estas en la sala: " + salas[salaActual].nombreSala);
  }
}

void guardarMsg(String comando){
  Sala &actual = salas[salaActual];
  Mensaje msg;
  msg.remitente = nombreUsuario;
  msg.indiceSala = salaActual;
  msg.texto = comando;
  msg.id = siguienteId;
  siguienteId++;
  
  actual.historial[actual.x] = msg;
  if(actual.x<4){
    actual.x++;
  }else{
    actual.x = 0;
  }
  Serial.println(formatear(msg));
}

void printHistorial(){
  Sala &actual = salas[salaActual];
  Serial.println("Historial: ");
  for (int i = 0; i < 5; i++){
    int indice = (actual.x+i)%5;
    if(actual.historial[indice].id != 0){

      Serial.println(formatear(actual.historial[indice]));

    }
  }  
}

String formatear(Mensaje m){
  String linea = "#" + String(m.id) + " " + "[" + salas[m.indiceSala].nombreSala + "] " + m.remitente + ": " + m.texto;
  return linea;
}

int buscarSala(String nombre){

  for(int i = 0 ; i < totalSalas ; i++){

    if(nombre.equals(salas[i].nombreSala)){
      return i;
    }
  }
  return -1;
}

void printSalas(){
  Serial.println("Estas son las salas disponibles actualmente: ");

  for(int i = 0 ; i<totalSalas ; i++){
    Serial.println(salas[i].nombreSala);
  }
}