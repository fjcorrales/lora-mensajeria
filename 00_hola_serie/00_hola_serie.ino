//ESPACIO DE ESTRUCTURAS
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

//ESPACIO DE ENUM
enum Pantalla{MENU, CHAT, AJUSTES, EDITAR_NOMBRE};

//ESPACIO DE CONSTANTES
const int MAX_SALAS = 4;

//ESPACIO DE VARIABLES
int totalSalas = 0;
int salaActual = 0;
unsigned int siguienteId = 1;   //identificador de mensajes no de usuarios
String nombreUsuario = "Anonimo";
Sala salas[MAX_SALAS];
Pantalla pantallaActual = MENU;

//SETUP Y LOOP
void setup() {
  Serial.begin(115200);
  delay(2000);
  salas[0].nombreSala = "general";
  salas[0].x = 0;
  totalSalas = 1;
  cambiarPantalla(MENU);
}

void loop() {
  //Bloque de eco
  if(Serial.available()){

    String comando = Serial.readStringUntil('\n');
    comando.trim();
    if(comando.length()==0){return;}    //control de mensaje vacio

    switch(pantallaActual){
      case MENU:
        procesarMenu(comando);
        break;
      case CHAT:
        procesarChat(comando);
        break;
      case AJUSTES:
        procesarAjustes(comando);
        break;
      case EDITAR_NOMBRE:
        procesarEditarNombre(comando);
        break;
    }
  }
}

//ESPACIO DE FUNCIONES
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

void cambiarPantalla(Pantalla nueva){
  pantallaActual = nueva;
  dibujarPantalla();
}

void dibujarPantalla(){
  switch(pantallaActual){
    case MENU:
      Serial.println("=== MENU ===");
      Serial.println("1. Chat");
      Serial.println("2. Ajustes");
      break;
    case CHAT:
      Serial.println("=== CHAT (sala: " + salas[salaActual].nombreSala + ") ===");
      break;
    case AJUSTES:
      Serial.println("=== AJUSTES ===");
      Serial.println("1. Cambiar nombre");
      Serial.println("0. Volver");
      break;
    case EDITAR_NOMBRE:
      Serial.println("Escribe tu nuevo nombre: ");
      break;
  }
}

void procesarMenu(String entrada){ 
  if(entrada.equals("1")){
    cambiarPantalla(CHAT);
  }else if(entrada.equals("2")){
    cambiarPantalla(AJUSTES);
  }else{
    Serial.println("Comando invalido");
  }
}

void procesarChat(String entrada){
  if(entrada.startsWith("/")){
    if(entrada.equals("/")){
      Serial.println("Comandos aceptados actualmente:");
      Serial.println("/nombre [nombre]: cambia el nombre del remitente o devuelve el nombre actual");
      Serial.println("/sala [nombre de sala]: cambia la sala o devuelve la sala actual");
      Serial.println("/salas: lista las salas disponibles actualmente");
      Serial.println("/historial: devuelve los ultimos 5 mensajes enviados");
      Serial.println("/menu: sal al menu principal");
    }else if(entrada.startsWith("/nombre ") || entrada.equals("/nombre")){
      nombre(entrada);
    }else if(entrada.startsWith("/sala ") || entrada.equals("/sala")){
      cambioSala(entrada);
    }else if(entrada.startsWith("/salas ") || entrada.equals("/salas")){
      printSalas(); 
    }else if(entrada.startsWith("/historial ") || entrada.equals("/historial")){
      printHistorial(); 
    }else if(entrada.startsWith("/menu ") || entrada.equals("/menu")){
      cambiarPantalla(MENU); 
    }else{
      Serial.println("El comando introducido no esta registrado escribe '/' para recibir el listado de comandos disponibles");
    }
  }else{
    guardarMsg(entrada);
  }
}

void procesarAjustes(String entrada){  
  if(entrada.equals("1")){
    cambiarPantalla(EDITAR_NOMBRE);
  }else if(entrada.equals("0")){
    cambiarPantalla(MENU);
  }else{
    Serial.println("Comando invalido");
  }
}

void procesarEditarNombre(String entrada){
  if(nombreUsuario.equals(entrada) || entrada.length() == 0){
    Serial.println("Tu nombre actual ya es: " + nombreUsuario);
  }else{ 
    Serial.println("Nombre registrado: " + entrada);
    nombreUsuario = entrada;
  }
  cambiarPantalla(AJUSTES);
}