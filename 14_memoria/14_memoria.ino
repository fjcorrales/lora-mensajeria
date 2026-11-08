//ESPACIO DE VARIABLES
String textos[20];
char textos2[20][64];

const String relleno = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
//SETUP Y LOOP
void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()){
    String comando = Serial.readStringUntil('\n');
    comando.trim();

    if(comando.equals("/mem") || comando.equals("/mem ")){
      imprimirHeap("");

    }else if(comando.equals("/string") || comando.equals("/string ")){

      imprimirHeap("Antes de llenar el array");
      for(int i = 0 ; i<20 ; i++){
        textos[i] = "mensaje " + String(i) + ": " + relleno;
      }
      imprimirHeap("Despues de llenar el array");

    }else if(comando.equals("/char") || comando.equals("/char ")){

      imprimirHeap("Antes de llenar el array");
      Serial.println("Tamaño del array antes de llenarlo: " + String(sizeof(textos2)));
      for(int i = 0 ; i<20 ; i++){
        snprintf(textos2[i], sizeof(textos2[i]), "mensaje %d: %s", i, relleno.c_str());
      }
      imprimirHeap("Despues de llenar el array");
      Serial.println("Tamaño del array despues de llenarlo: " + String(sizeof(textos2)));

    }else if(comando.equals("/largo") || comando.equals("/largo ")){

      char buf[16];
      String relleno2 = "0123456789012345678901234567890123456789";
      int n = snprintf(buf, sizeof(buf), "%s", relleno2.c_str());
      Serial.println(buf);
      Serial.println(n);

    }
  }
}

//ESPACIO DE FUNCIONES
void imprimirHeap(String tag){
  Serial.println(tag);
  Serial.println("Los espacios disponibles son los siguientes: ");
  Serial.println("Bytes libres de heap: " + String(ESP.getFreeHeap()));
  Serial.println("Minimo numero de bytes libres desde arranque: " + String(ESP.getMinFreeHeap()));
  Serial.println("Mayor bloque contiguo es de " + String(ESP.getMaxAllocHeap()) + " bytes");
}

//RESPUESTAS A PREGUNTAS
/*
¿Cuántos bytes de heap consumieron los 20 String? ¿Más o menos que 20 × 60=1200?
los 20 string han ocupado 1680 bytes, por lo tanto, han ocupado mas.

¿Por qué /char no cambia el heap libre?
por la propia naturaleza de la variable de tipo char, al crear diretamente un array de caracteres estos reservan un espacio fijo al compilar

¿Qué devuelve snprintf cuando el texto no cabe, y cómo lo usarías para detectar un mensaje truncado?
al ejecutar /largo, solamente me ha devuelto una cadena a medias, no todo el string que es,
Para aprovechar esto, sera necesario comparar el tamaño de buffer al tamaño de la longitud del mensaje para saber si este se fragmenta

Si ejecutas /string dos veces, ¿qué le pasa al heap?
Se mantiene igual, dado que estamos "editando" un espacio de memoria ya reservado, no estamos ocupando memoria adicional
*/