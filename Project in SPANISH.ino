#include <Keypad.h>     // importa libreria Keypad

#include <SPI.h>    // incluye libreria interfaz SPI
#include <SD.h>     // incluye libreria para tarjetas SD

#define SSpin 53    // Slave Select en pin digital 53

File archivo;     // objeto archivo del tipo File


const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 4;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

int vuelta=0;
byte pinesFilas[FILAS] = {43,45,47,49};  // pines correspondientes a las filas{43,45,47,49}
byte pinesColumnas[COLUMNAS] = {35,37,39,41}; // pines correspondientes a las columnas  {35,37,39,41};

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;       // almacena la tecla presionada
int  contador = 1;    // cuenta el nivel del menu en el que se esta

int a=0;

         ///////////
         //Grupo 1//
         ///////////

//motor
#define STEPA 5      // pin STEP de A4988 a pin 4
#define DIRA 4     // pin DIR de A4988 a pin 5

// Sensor 
#define S0 7    // S0 a pin 4
#define S1 6    // S1 a pin 5
#define S2 9    // S2 a pin 6
#define S3 8    // S3 a pin 7
#define salidaTCS1 10 // salidaTCS a pin 8

          ///////////
         //Grupo 2//
         ///////////

//motor
#define STEPB 12      // pin STEP de A4988 a pin 4
#define DIRB 11    // pin DIR de A4988 a pin 5

// Sensor 
#define S4 14    // S0 a pin 4
#define S5 13    // S1 a pin 5
#define S6 16    // S2 a pin 6
#define S7 15    // S3 a pin 7
#define salidaTCS2 17 // salidaTCS a pin 8

          ///////////
         //Grupo 3//
         //////////

//motor
#define STEPC  19     // pin STEP de A4988 a pin 4
#define DIRC 18    // pin DIR de A4988 a pin 5

// Sensor 
#define S8 21    // S0 a pin 4
#define S9 20    // S1 a pin 5
#define S10 23    // S2 a pin 6
#define S11 22    // S3 a pin 7
#define salidaTCS3 24 // salidaTCS a pin 8



// 
#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D

int n=5;        //contador de muestras del sensor
long arojo=0;  //rojo
long trojo=0;  //rojo
long rojo=0;   //rojo

long verde=0;  //verde
long averde=0;  //verde
long tverde=0;  //verde

long azul=0;  //azul
long aazul=0;  //azul
long tazul=0;  //azul

void setup()
{

 Serial.begin(9600);       // inicializa monitor serie a 9600 bps
 
 ////// Menu pantalla de inicio //////
 
  lcd.setBacklightPin(3,POSITIVE);  // puerto P3 de PCF8574 como positivo
  lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
  lcd.begin(20, 4);     // 16 columnas por 2 lineas para LCD 1602A
  lcd.clear();      // limpia pantalla
  lcd.backlight();
  Serial.println("Listo");    // Muestra texto Listo
  lcd.setCursor(0, 0);
  lcd.display();
  lcd.print("IGEM 2021 ");
  lcd.setCursor(0, 1);
  lcd.print("BY:PORCEL ");
  delay(2500);
  lcd.clear();

 ////// SAlidas //////

                   ////// Grupo1 //////     
  pinMode(13,OUTPUT);
  pinMode(S0, OUTPUT);    // pin 4 como salida
  pinMode(S1, OUTPUT);    // pin 5 como salida
  pinMode(S2, OUTPUT);    // pin 6 como salida
  pinMode(S3, OUTPUT);    // pin 7 como salida
  pinMode(salidaTCS1, INPUT);  // pin 8 como salida
  
  digitalWrite(S0,HIGH);  // establece frecuencia de salida
  digitalWrite(S1,LOW);   // del modulo al 20 por ciento
  
  pinMode(STEPA, OUTPUT); // pin 4 como salida
  pinMode(DIRA, OUTPUT);   // pin 5 como salida

                ////// Grupo2 //////     

  pinMode(S4, OUTPUT);    // pin 4 como salida
  pinMode(S5, OUTPUT);    // pin 5 como salida
  pinMode(S6, OUTPUT);    // pin 6 como salida
  pinMode(S7, OUTPUT);    // pin 7 como salida
  pinMode(salidaTCS2, INPUT);  // pin 8 como salida
  
  digitalWrite(S4,HIGH);  // establece frecuencia de salida
  digitalWrite(S5,LOW);   // del modulo al 20 por ciento
  
  pinMode(STEPB, OUTPUT); // pin 4 como salida
  pinMode(DIRB, OUTPUT);   // pin 5 como salida

                ////// Grupo3 //////     

  pinMode(S8, OUTPUT);    // pin 4 como salida
  pinMode(S9, OUTPUT);    // pin 5 como salida
  pinMode(S10, OUTPUT);    // pin 6 como salida
  pinMode(S11, OUTPUT);    // pin 7 como salida
  pinMode(salidaTCS2, INPUT);  // pin 8 como salida
  
  digitalWrite(S8,HIGH);  // establece frecuencia de salida
  digitalWrite(S9,LOW);   // del modulo al 20 por ciento
  
  pinMode(STEPC, OUTPUT); // pin 4 como salida
  pinMode(DIRC, OUTPUT);   // pin 5 como salida


 }

void loop(){

                                         ///////////////////////////////////////////////////
                                       //////// TECLA 1 , LECTURA DE 5 MUESTRAS //////////
                                        ///////////////////////////////////////////////////

 if(TECLA == '1'){              // tecla en el keypad
   for(int t=0 ; t<5 ; t++){    // dos ciclos
    
        arojo=0; //reinicio e contador 
        aazul=0; //reinicio e contador
        averde=0; //reinicio e contador
    digitalWrite(13,1);
    lcd.setCursor(0, 0);
    lcd.print("SENSOR 1 ; 5 LECTURAS");
    Serial.print("ok");
   //motor 
   digitalWrite(DIRA, HIGH);          // giro en un sentido
   for(int i = 0; i < 33.3; i++){     // 200 pasos para motor de 0.9 grados de angulo de paso
   digitalWrite(STEPA, HIGH);       // nivel alto
   delay(1);          // por 10 mseg
   digitalWrite(STEPA, LOW);        // nivel bajo
   delay(1);          // por 10 mseg
   }
   
              //////// sensor /////////
              
   for(int d=0; d<n ; d++){  // numeo de lecturas del sensor
    
   digitalWrite(S2,LOW);     // establece fotodiodos
   digitalWrite(S3,LOW);     // con filtro rojo
    rojo = pulseIn(salidaTCS1, LOW); // obtiene duracion de pulso de salida del sensor
   delay(200);       // demora de 200 mseg
  
   digitalWrite(S2,HIGH);    // establece fotodiodos
   digitalWrite(S3,HIGH);    // con filtro verde
    verde = pulseIn(salidaTCS1, LOW);  // obtiene duracion de pulso de salida del sensor
   delay(200);       // demora de 200 mseg
  
   digitalWrite(S2,LOW);     // establece fotodiodos
   digitalWrite(S3,HIGH);    // con filtro azul
    azul = pulseIn(salidaTCS1, LOW); // obtiene duracion de pulso de salida del sensor
   delay(200);       // demora de 200 mseg


                 //////// Impresion en pantalla /////////

   lcd.setCursor(0, 3);
   lcd.print("R:"); 
   Serial.print("R:");     // muestra texto
   Serial.print(rojo);     // muestra valor de variable rojo
   lcd.print(rojo);  
   Serial.print("\t");     // espacio de tabulacion
   lcd.print(" ");
   lcd.print("V:");  
   Serial.print("V:");     // muestra texto
   Serial.print(verde);    // muestra valor de variable verde
   lcd.print(verde);
   Serial.print("\t");     // espacio de tabulacion
   lcd.print(" A:"); 
   Serial.print("A:");     // muestra texto
   Serial.println(azul);   // muestra valor de variable azul
   lcd.print(azul);                      // y salto de linea 
  
   //CONTADORES//
   
   rojo=rojo+arojo;   
   arojo=rojo;   
    
   azul=azul+aazul;   
   aazul=azul;    

   verde=verde+averde;   
   averde=verde;
            
   }
   
   //// resultados promediados /////
      trojo = arojo/n;
      tazul = aazul/n;
      tverde = averde/n;

                                   ///// impresion de resultados PANTALLA LCD /////
   Serial.print("ROJO ");
   Serial.print(t+1);  
   Serial.print(": ");
   Serial.println(trojo);
    Serial.println("ok");
   
   if ( trojo < 180 && tverde > 180 && tazul > 180){    // si valores dentro del rango
    lcd.setCursor(t, 1);
    lcd.print("O");            // muestra texto
    Serial.println("O");       // muestra texto
    delay(2500);
  }
  else{
    lcd.setCursor(t, 1);
    lcd.print("X"); 
    Serial.println("X");  
  }
                              
                              
                              ////////GUARDADO DE RESULTADOS EN SD /////////
                              
  Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("prueba.txt", FILE_WRITE);  // apertura para lectura/escritura de archivo prueba.txt

  if (archivo) {
    archivo.print("ROJO ");   //// rojo 
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(trojo);
    
    archivo.print("Azul ");   //// azul
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tazul);

    archivo.print("Verde ");   //// verde
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tverde);
    
    Serial.println("Escribiendo en archivo prueba.txt..."); // texto en monitor serie
    archivo.close();        // cierre del archivo
    Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie
  } else {
    Serial.println("error en apertura de prueba.txt");  // texto de falla en apertura de archivo
  }

  archivo = SD.open("prueba.txt");    // apertura de archivo prueba.txt
  if (archivo) {
    Serial.println("Contenido de prueba.txt:"); // texto en monitor serie
    while (archivo.available()) {   // mientras exista contenido en el archivo
      Serial.write(archivo.read());     // lectura de a un caracter por vez
    }
    //archivo.close();        // cierre de archivo
  } else {
    Serial.println("error en la apertura de prueba.txt");// texto de falla en apertura de archivo
  }
    }  ///final for
} //// final tecla 1
                                        ///////////////////////////////////////////////////
                                       //////// TECLA 2 , LECTURA DE 2 MUESTRAS //////////
                                        ///////////////////////////////////////////////////

 if(TECLA == '2'){              // tecla en el keypad
   for(int t=0 ; t<5 ; t++){    // dos ciclos
    
        arojo=0; //reinicio e contador 
        aazul=0; //reinicio e contador
        averde=0; //reinicio e contador
    digitalWrite(13,1);
    lcd.setCursor(0, 0);
    lcd.print("SENSOR 2 ; 5 LECTURAS");
    Serial.print("ok");
   //motor 
   digitalWrite(DIRB, HIGH);          // giro en un sentido
   for(int i = 0; i < 33.3; i++){     // 200 pasos para motor de 0.9 grados de angulo de paso
   digitalWrite(STEPB, HIGH);       // nivel alto
   delay(1);          // por 10 mseg
   digitalWrite(STEPB, LOW);        // nivel bajo
   delay(1);          // por 10 mseg
   }
   
              //////// sensor /////////
              
   for(int d=0; d<n ; d++){  // numeo de lecturas del sensor
    
   digitalWrite(S6,LOW);     // establece fotodiodos
   digitalWrite(S7,LOW);     // con filtro rojo
    rojo = pulseIn(salidaTCS2, LOW); // obtiene duracion de pulso de salida del sensor
   delay(200);       // demora de 200 mseg
  
   digitalWrite(S6,HIGH);    // establece fotodiodos
   digitalWrite(S7,HIGH);    // con filtro verde
    verde = pulseIn(salidaTCS2, LOW);  // obtiene duracion de pulso de salida del sensor
   delay(200);       // demora de 200 mseg
  
   digitalWrite(S6,LOW);     // establece fotodiodos
   digitalWrite(S7,HIGH);    // con filtro azul
    azul = pulseIn(salidaTCS2, LOW); // obtiene duracion de pulso de salida del sensor
   delay(200);       // demora de 200 mseg


                 //////// Impresion en pantalla /////////

   lcd.setCursor(0, 3);
   lcd.print("R:"); 
   Serial.print("R:");     // muestra texto
   Serial.print(rojo);     // muestra valor de variable rojo
   lcd.print(rojo);  
   Serial.print("\t");     // espacio de tabulacion
   lcd.print(" ");
   lcd.print("V:");  
   Serial.print("V:");     // muestra texto
   Serial.print(verde);    // muestra valor de variable verde
   lcd.print(verde);
   Serial.print("\t");     // espacio de tabulacion
   lcd.print(" A:"); 
   Serial.print("A:");     // muestra texto
   Serial.println(azul);   // muestra valor de variable azul
   lcd.print(azul);                      // y salto de linea 
  
   //CONTADORES//
   
   rojo=rojo+arojo;   
   arojo=rojo;   
    
   azul=azul+aazul;   
   aazul=azul;    

   verde=verde+averde;   
   averde=verde;
            
   }
   
   //// resultados promediados /////
      trojo = arojo/n;
      tazul = aazul/n;
      tverde = averde/n;

                                   ///// impresion de resultados PANTALLA LCD /////
   Serial.print("ROJO ");
   Serial.print(t+1);  
   Serial.print(": ");
   Serial.println(trojo);
    Serial.println("ok");
   
   if ( trojo < 180 && tverde > 180 && tazul > 180){    // si valores dentro del rango
    lcd.setCursor(t, 1);
    lcd.print("O");            // muestra texto
    Serial.println("O");       // muestra texto
    delay(2500);
  }
  else{
    lcd.setCursor(t, 1);
    lcd.print("X"); 
    Serial.println("X");  
  }
                              
                              
                              ////////GUARDADO DE RESULTADOS EN SD /////////
                              
  Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("prueba.txt", FILE_WRITE);  // apertura para lectura/escritura de archivo prueba.txt

  if (archivo) {
    archivo.print("ROJO ");   //// rojo 
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(trojo);
    
    archivo.print("Azul ");   //// azul
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tazul);

    archivo.print("Verde ");   //// verde
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tverde);
    
    Serial.println("Escribiendo en archivo prueba.txt..."); // texto en monitor serie
    archivo.close();        // cierre del archivo
    Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie
  } else {
    Serial.println("error en apertura de prueba.txt");  // texto de falla en apertura de archivo
  }

  archivo = SD.open("prueba.txt");    // apertura de archivo prueba.txt
  if (archivo) {
    Serial.println("Contenido de prueba.txt:"); // texto en monitor serie
    while (archivo.available()) {   // mientras exista contenido en el archivo
      Serial.write(archivo.read());     // lectura de a un caracter por vez
    }
    //archivo.close();        // cierre de archivo
  } else {
    Serial.println("error en la apertura de prueba.txt");// texto de falla en apertura de archivo
  }
    }  ///final for
} //// final tecla 2


                                       ///////////////////////////////////////////////////
                                       //////// TECLA 3 , LECTURA DE MUESTRAS //////////
                                        ///////////////////////////////////////////////////

 if(TECLA == '3'){              // tecla en el keypad
   for(int t=0 ; t<5 ; t++){    // dos ciclos
    
        arojo=0; //reinicio e contador 
        aazul=0; //reinicio e contador
        averde=0; //reinicio e contador
    digitalWrite(13,1);
    lcd.setCursor(0, 0);
    lcd.print("SENSOR 3 ; 5 LECTURAS");
    Serial.print("ok");
   //motor 
   digitalWrite(DIRC, HIGH);          // giro en un sentido
   for(int i = 0; i < 33.3; i++){     // 200 pasos para motor de 0.9 grados de angulo de paso
   digitalWrite(STEPC, HIGH);       // nivel alto
   delay(1);          // por 10 mseg
   digitalWrite(STEPC, LOW);        // nivel bajo
   delay(1);          // por 10 mseg
   }
   
              //////// sensor /////////
              
   for(int d=0; d<n ; d++){  // numeo de lecturas del sensor
    
   digitalWrite(S10,LOW);     // establece fotodiodos
   digitalWrite(S11,LOW);     // con filtro rojo
    rojo = pulseIn(salidaTCS3, LOW); // obtiene duracion de pulso de salida del sensor
   delay(200);       // demora de 200 mseg
  
   digitalWrite(S10,HIGH);    // establece fotodiodos
   digitalWrite(S11,HIGH);    // con filtro verde
    verde = pulseIn(salidaTCS3, LOW);  // obtiene duracion de pulso de salida del sensor
   delay(200);       // demora de 200 mseg
  
   digitalWrite(S10,LOW);     // establece fotodiodos
   digitalWrite(S11,HIGH);    // con filtro azul
    azul = pulseIn(salidaTCS3, LOW); // obtiene duracion de pulso de salida del sensor
   delay(200);       // demora de 200 mseg


                 //////// Impresion en pantalla /////////

   lcd.setCursor(0, 3);
   lcd.print("R:"); 
   Serial.print("R:");     // muestra texto
   Serial.print(rojo);     // muestra valor de variable rojo
   lcd.print(rojo);  
   Serial.print("\t");     // espacio de tabulacion
   lcd.print(" ");
   lcd.print("V:");  
   Serial.print("V:");     // muestra texto
   Serial.print(verde);    // muestra valor de variable verde
   lcd.print(verde);
   Serial.print("\t");     // espacio de tabulacion
   lcd.print(" A:"); 
   Serial.print("A:");     // muestra texto
   Serial.println(azul);   // muestra valor de variable azul
   lcd.print(azul);                      // y salto de linea 
  
   //CONTADORES//
   
   rojo=rojo+arojo;   
   arojo=rojo;   
    
   azul=azul+aazul;   
   aazul=azul;    

   verde=verde+averde;   
   averde=verde;
            
   }
   
   //// resultados promediados /////
      trojo = arojo/n;
      tazul = aazul/n;
      tverde = averde/n;

                                   ///// impresion de resultados PANTALLA LCD /////
   Serial.print("ROJO ");
   Serial.print(t+1);  
   Serial.print(": ");
   Serial.println(trojo);
    Serial.println("ok");
   
   if ( trojo < 180 && tverde > 180 && tazul > 180){    // si valores dentro del rango
    lcd.setCursor(t, 1);
    lcd.print("O");            // muestra texto
    Serial.println("O");       // muestra texto
    delay(2500);
  }
  else{
    lcd.setCursor(t, 1);
    lcd.print("X"); 
    Serial.println("X");  
  }
                              
                              
                              ////////GUARDADO DE RESULTADOS EN SD /////////
                              
  Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
  if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("prueba.txt", FILE_WRITE);  // apertura para lectura/escritura de archivo prueba.txt

  if (archivo) {
    archivo.print("ROJO ");   //// rojo 
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(trojo);
    
    archivo.print("Azul ");   //// azul
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tazul);

    archivo.print("Verde ");   //// verde
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tverde);
    
    Serial.println("Escribiendo en archivo prueba.txt..."); // texto en monitor serie
    archivo.close();        // cierre del archivo
    Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie
  } else {
    Serial.println("error en apertura de prueba.txt");  // texto de falla en apertura de archivo
  }

  archivo = SD.open("prueba.txt");    // apertura de archivo prueba.txt
  if (archivo) {
    Serial.println("Contenido de prueba.txt:"); // texto en monitor serie
    while (archivo.available()) {   // mientras exista contenido en el archivo
      Serial.write(archivo.read());     // lectura de a un caracter por vez
    }
    //archivo.close();        // cierre de archivo
  } else {
    Serial.println("error en la apertura de prueba.txt");// texto de falla en apertura de archivo
  }
    }  ///final for
} //// final tecla 2


    } //Final de void Loop

 
