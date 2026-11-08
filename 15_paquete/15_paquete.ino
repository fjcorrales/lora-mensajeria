//ESPACIO DE ESTRUCTURAS
struct  Mensaje{
  //Formato que va a tener el mensaje que se envie por radio
  String origen;              //Es el identificador del nodo que envia el mensaje
  unsigned int id = 0;        //Identificador del propio mensaje
  String sala;                //Sala de la que origina el mensaje
  String remitente;           //Nombre del usuario que haya enviado el mensaje
  String texto;               //Mensaje en si
};

//ESPACIO DE VARIABLES
const int MAX_PAQUETE = 200;  //El modulo de LoRa adminte solo 255 bytes por paquete. Se deja 200 para dejar margen
const String NODO_ID = "N0";  //El identificador de este nodo concreto
String userName = "Anonimo";  //El nombre del usuario de este terminal
String sala = "general";      //Sala desde la que se está escribiendo
int siguienteId = 1;

//ESPACIO SETUP Y LOOP
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available()){

    String comando = Serial.readStringUntil('\n');
    comando.trim();

    int esp = comando.indexOf(' ');
    String comm, txt;
    
    if(esp == -1){
      comm = comando;
      txt = "";
    }else{
      comm = comando.substring(0, esp);
      txt = comando.substring(esp+1);
      txt.trim();
    }
    
    if(comm.equals("/enviar")){
      //Si queremos enviar un mensaje, lo construimos y serializamos
      Mensaje m;
      m.origen = NODO_ID;
      m.id = siguienteId;
      siguienteId++;
      m.sala = sala;
      m.remintente = userName;
      m.texto = txt;

      String paquete = serializar(m);

      if(sizeOf(paquete)>MAX_PAQUETE){
        Serial.println("ERROR: el mensaje que se desea enviar es demasiado grande");
      }else{
        Serial.println("Mensaje enviado: " + paquete); 
      }
    }else if(comm.equals("/recibir")){

    }else if(comm.equals("/eco")){
      
    }else if(comm.equals("/nombre")){
      
    }
  }
}

//ESPACIO DE FUNCIONES
String serializar(Mensaje m){
  //Esta funcion le da formato al mensaje como tal que se empaquetara para el envio
  return m.origen + "|" + String(m.id) + "|" + m.sala  + "|" + m.remitente + "|" + m.texto;
}

bool parsear(String linea, Mensaje &m, String &error){
  //Comprueba si la linea recibida es valida, en cuyo caso rellena m y devuevle true

}

String formatear(Mensaje m){
  //Formatea el mensaje para mostrarlo por pantalla
  return "#" + m.id + " " + m.remitente + " (" + origen + "): " + m.texto;
}