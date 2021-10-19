#include <Keypad.h>     // import library Keypad

#include <SPI.h>    // include library interface SPI
#include <SD.h>     // include library for SD memory

#define SSpin 53    // Slave Select in digital pin 53

File archivo;     // Type file


const byte FILAS = 4;     // define rows
const byte COLUMNAS = 4;    // define number of columns
char keys[FILAS][COLUMNAS] = {    // define distribution of de keys
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

int vuelta=0;
byte pinesFilas[FILAS] = {43,45,47,49};  // pins corresponding to rows {43,45,47,49}
byte pinesColumnas[COLUMNAS] = {35,37,39,41}; // pins corresponding to columns {35,37,39,41}

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // create object

char TECLA;       // stores the key pressed
int  contador = 1;    // counts the level of the menu in which you are

int a=0;

         ///////////
         //Group 1//
         ///////////

//motor
#define STEPA 5      // STEP pin from A4988 to pin 4
#define DIRA 4     // DIR pin from A4988 to pin 5

// Sensor 
#define S0 7    // S0 to pin 4
#define S1 6    // S1 to pin 5
#define S2 9    // S2 to pin 6
#define S3 8    // S3 to pin 7
#define salidaTCS1 10 // TCS output to pin 8
          ///////////
         //Group 2//
         ///////////

//motor
#define STEPB 12      // STEP pin from A4988 to pin 4
#define DIRB 11    // DIR pin from A4988 to pin 5

// Sensor 
#define S4 14    // S0 to pin 4
#define S5 13    // S1 to pin 5
#define S6 16    // S2 to pin 6
#define S7 15    // S3 to pin 7
#define salidaTCS2 17 // TCS output to pin 8

          ///////////
         //Group 3//
         //////////

//motor
#define STEPC  19     // STEP pin from A4988 to pin 4
#define DIRC 18    // DIR pin from A4988 to pin 5

// Sensor 
#define S8 21    // S0 to pin 4
#define S9 20    // S1 to pin 5
#define S10 23    // S2 to pin 6
#define S11 22    // S3 to pin 7
#define salidaTCS3 24 // TCS output to pin 8



// 
#include <Wire.h>      // communication library by I2C
#include <LCD.h>      // library for LCD functions
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D

int n=5;        //sensor sample counter
long ared=0;  //Red
long tred=0;  //Red
long red=0;   //Red

long green=0;  //green
long agreen=0;  //green
long tgreen=0;  //green

long blue=0;  //blue
long ablue=0;  //blue
long tblue=0;  //blue

void setup()
{

 Serial.begin(9600);       // initialize serial monitor at 9600 bps
 
 ////// Home screen menu //////
 
  lcd.setBacklightPin(3,POSITIVE);  // P3 port of PCF8574 as positive
  lcd.setBacklight(HIGH);   // enables LCD backlighting
  lcd.begin(20, 4);     // 16 columns by 2 lines for LCD 1602A
  lcd.clear();      // clean screen
  lcd.backlight();
  Serial.println("Listo");    // Sample text Done
  lcd.setCursor(0, 0);
  lcd.display();
  lcd.print("IGEM 2021 ");
  lcd.setCursor(0, 1);
  lcd.print("BY:PORCEL ");
  delay(2500);
  lcd.clear();

 ////// Outputs //////

                   ////// Group1 //////     
  pinMode(13,OUTPUT);
  pinMode(S0, OUTPUT);    // pin 4 as output
  pinMode(S1, OUTPUT);    // pin 5 as output
  pinMode(S2, OUTPUT);    // pin 6 as output
  pinMode(S3, OUTPUT);    // pin 7 as output
  pinMode(salidaTCS1, INPUT);  // pin 8 as output
  
  digitalWrite(S0,HIGH);  // set output frequency
  digitalWrite(S1,LOW);   // of the module to 20 percent
  
  pinMode(STEPA, OUTPUT); // pin 4 as output
  pinMode(DIRA, OUTPUT);   // pin 5 as output

                ////// Group2 //////     

  pinMode(S4, OUTPUT);    // pin 4 as output
  pinMode(S5, OUTPUT);    // pin 5 as output
  pinMode(S6, OUTPUT);    // pin 6 as output
  pinMode(S7, OUTPUT);    // pin 7 as output
  pinMode(salidaTCS2, INPUT);  // pin 8 as output
  
  digitalWrite(S4,HIGH);  // set output frequency
  digitalWrite(S5,LOW);   // of the module to 20 percent
  
  pinMode(STEPB, OUTPUT); // pin 4 as output
  pinMode(DIRB, OUTPUT);   // pin 5 as output

                ////// Group3 //////     

  pinMode(S8, OUTPUT);    // pin 4 as output
  pinMode(S9, OUTPUT);    // pin 5 as output
  pinMode(S10, OUTPUT);    // pin 6 as output
  pinMode(S11, OUTPUT);    // pin 7 as output
  pinMode(salidaTCS2, INPUT);  // pin 8 as output
  
  digitalWrite(S8,HIGH);  // set output frequency
  digitalWrite(S9,LOW);   // of the module to 20 percent
  
  pinMode(STEPC, OUTPUT); // pin 4 as output
  pinMode(DIRC, OUTPUT);   // pin 5 as output


 }

void loop(){

                                         ///////////////////////////////////////////////////
                                       //////// KEY 1, READING OF 5 SAMPLES //////////
                                        ///////////////////////////////////////////////////

 if(TECLA == '1'){              // key on keypad
   for(int t=0 ; t<5 ; t++){    // two cycles
    
        ared=0; //reset e counter
        ablue=0; //reset e counter
        agreen=0; //reset e counter
    digitalWrite(13,1);
    lcd.setCursor(0, 0);
    lcd.print("SENSOR 1 ; 5 LECTURAS");
    Serial.print("ok");
   //motor 
   digitalWrite(DIRA, HIGH);          // twist one way
   for(int i = 0; i < 33.3; i++){     // 200 steps for 0.9 degree step angle motor
   digitalWrite(STEPA, HIGH);       // high level
   delay(1);          // por 10 mseg
   digitalWrite(STEPA, LOW);        // high level
   delay(1);          // por 10 mseg
   }
   
              //////// sensor /////////
              
   for(int d=0; d<n ; d++){  // number of sensor readings
    
   digitalWrite(S2,LOW);     // set photodiodes
   digitalWrite(S3,LOW);     // with red filter
    red = pulseIn(salidaTCS1, LOW); // get sensor output pulse duration
   delay(200);       // 200 msec delay
  
   digitalWrite(S2,HIGH);    // set photodiodes
   digitalWrite(S3,HIGH);    // with green filter
    green = pulseIn(salidaTCS1, LOW);  // get sensor output pulse duration
   delay(200);       // 200 msec delay
  
   digitalWrite(S2,LOW);     // set photodiodes
   digitalWrite(S3,HIGH);    // with blue filter
    blue = pulseIn(salidaTCS1, LOW); // get sensor output pulse duration
   delay(200);       // 200 msec delay

                 //////// Screen printing /////////

   lcd.setCursor(0, 3);
   lcd.print("R:"); 
   Serial.print("R:");     // shows text
   Serial.print(red);     // shows red variable value
   lcd.print(red);  
   Serial.print("\t");     // tab space
   lcd.print(" ");
   lcd.print("V:");  
   Serial.print("V:");     // shows text
   Serial.print(green);    // shows green variable value
   lcd.print(green);
   Serial.print("\t");     // tab space
   lcd.print(" A:"); 
   Serial.print("A:");     // tab space
   Serial.println(blue);   // shows blue variable value
   lcd.print(blue);                      // and line break
  
   //COUNTERS//
   
   red=red+ared;   
   ared=red;   
    
   blue=blue+ablue;   
   ablue=blue;    

   green=green+agreen;   
   agreen=green;
            
   }
   
   //// averaged results /////
      tred = ared/n;
      tblue = ablue/n;
      tgreen = agreen/n;

                                   ///// printing results LCD SCREEN /////
   Serial.print("red ");
   Serial.print(t+1);  
   Serial.print(": ");
   Serial.println(tred);
    Serial.println("ok");
   
   if ( tred < 180 && tgreen > 180 && tblue > 180){    // if values ​​within the range
    lcd.setCursor(t, 1);
    lcd.print("O");            // sample text
    Serial.println("O");       // sample text
    delay(2500);
  }
  else{
    lcd.setCursor(t, 1);
    lcd.print("X"); 
    Serial.println("X");  
  }
                              
                              
                              ////////SAVING RESULTS IN SD /////////
                              
  Serial.println("Initializing card ...");  // text in monitor window
  if (!SD.begin(SSpin)) {     // SD card initialization
    Serial.println("initialization failure !");// if it fails, corresponding text is displayed and
    return;         // setup () is exited to end the program
  }
  
  Serial.println("correct initialization");  // correct initialization text
  archivo = SD.open("test.txt", FILE_WRITE);  // open for reading / writing test.txt file

  if (archivo) {
    archivo.print("red ");   //// red 
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tred);
    
    archivo.print("blue ");   //// blue
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tblue);

    archivo.print("green ");   //// green
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tgreen);
    
    Serial.println("Writing in test.txt file..."); // text on serial monitor
    archivo.close();        // cierre del archivo
    Serial.println("correct writing"); // texto de correct writing en monitor serie
  } else {
    Serial.println("error in opening test.txt");  // fault text on file open
  }

  archivo = SD.open("test.txt");    // open file test.txt
  if (archivo) {
    Serial.println("Contents of test.txt:"); // text on serial monitor
    while (archivo.available()) {   // as long as there is content in the file
      Serial.write(archivo.read());     // reading one character at a time
    }
    //archivo.close();        // closing file
  } else {
    Serial.println("error in opening test.txt");// fault text on file open
  }
    }  ///final for
} //// final tecla 1
                                        ///////////////////////////////////////////////////
                                       //////// TECLA 2 , LECTURA DE 2 MUESTRAS //////////
                                        ///////////////////////////////////////////////////

 if(TECLA == '2'){              // key on keypad
   for(int t=0 ; t<5 ; t++){    // two cycles
    
        ared=0; //reset e counter
        ablue=0; //reset e counter
        agreen=0; //reset e counter
    digitalWrite(13,1);
    lcd.setCursor(0, 0);
    lcd.print("SENSOR 2 ; 5 LECTURAS");
    Serial.print("ok");
   //motor 
   digitalWrite(DIRB, HIGH);          // twist one way
   for(int i = 0; i < 33.3; i++){     // 200 steps for 0.9 degree step angle motor
   digitalWrite(STEPB, HIGH);       // high level
   delay(1);          // por 10 mseg
   digitalWrite(STEPB, LOW);        // low level
   delay(1);          // por 10 mseg
   }
   
              //////// sensor /////////
              
   for(int d=0; d<n ; d++){  // numeo de lecturas del sensor
    
   digitalWrite(S6,LOW);     // set photodiodes
   digitalWrite(S7,LOW);     // with net filter
    red = pulseIn(salidaTCS2, LOW); // get sensor output pulse duration
   delay(200);       // 200 msec delay
  
   digitalWrite(S6,HIGH);    // set photodiodes
   digitalWrite(S7,HIGH);    // with filter green
    green = pulseIn(salidaTCS2, LOW);  // get sensor output pulse duration
   delay(200);       // 200 msec delay
  
   digitalWrite(S6,LOW);     // set photodiodes
   digitalWrite(S7,HIGH);    // with filter blue
    blue = pulseIn(salidaTCS2, LOW); // get sensor output pulse duration
   delay(200);       // 200 msec delay


                 //////// Impresion en pantalla /////////

   lcd.setCursor(0, 3);
   lcd.print("R:"); 
   Serial.print("R:");     // shows text
   Serial.print(red);     // show value of variable network
   lcd.print(red);  
   Serial.print("\t");     // tab space
   lcd.print(" ");
   lcd.print("V:");  
   Serial.print("V:");     // shows text
   Serial.print(green);    // show value of variable green
   lcd.print(green);
   Serial.print("\t");     // tab space
   lcd.print(" A:"); 
   Serial.print("A:");     // shows text
   Serial.println(blue);   // show value of variable blue
   lcd.print(blue);                      // and line break
  
   //CONTADORES//
   
   red=red+ared;   
   ared=red;   
    
   blue=blue+ablue;   
   ablue=blue;    

   green=green+agreen;   
   agreen=green;
            
   }
   
   //// resultados promediados /////
      tred = ared/n;
      tblue = ablue/n;
      tgreen = agreen/n;

                                   ///// impresion de resultados PANTALLA LCD /////
   Serial.print("red ");
   Serial.print(t+1);  
   Serial.print(": ");
   Serial.println(tred);
    Serial.println("ok");
   
   if ( tred < 180 && tgreen > 180 && tblue > 180){    // if values ​​within the range
    lcd.setCursor(t, 1);
    lcd.print("O");            // shows text
    Serial.println("O");       // shows text
    delay(2500);
  }
  else{
    lcd.setCursor(t, 1);
    lcd.print("X"); 
    Serial.println("X");  
  }
                              
                              
                              ////////fault text on file open /////////
                              
  Serial.println("Initializing card ...");  // text in monitor window
  if (!SD.begin(SSpin)) {     // SD card initialization
    Serial.println("initialization failure !");// if it fails it shows corresponding text and
    return;         // setup () is exited to end the program
  }
  
  Serial.println("correct initialization");  // correct initialization text
  archivo = SD.open("test.txt", FILE_WRITE);  // open for reading / writing file test.txt

  if (archivo) {
    archivo.print("red ");   //// red 
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tred);
    
    archivo.print("blue ");   //// blue
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tblue);

    archivo.print("green ");   //// green
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tgreen);
    
    Serial.println("Writing in test.txt file..."); // text on serial monitor
    archivo.close();        // cierre del archivo
    Serial.println("correct writing"); // texto de correct writing en monitor serie
  } else {
    Serial.println("error in opening test.txt");  // fault text on file open
  }

  archivo = SD.open("test.txt");    // open file test.txt
  if (archivo) {
    Serial.println("Contents of test.txt:"); // text on serial monitor
    while (archivo.available()) {   // as long as there is content in the file
      Serial.write(archivo.read());     // reading one character at a time
    }
    //archivo.close();        // closing file
  } else {
    Serial.println("error in opening test.txt");// fault text on file open
  }
    }  ///final for
} //// final tecla 2


                                       ///////////////////////////////////////////////////
                                       //////// KEY 3, READING SAMPLES //////////
                                        ///////////////////////////////////////////////////

 if(TECLA == '3'){              // key on keypad
   for(int t=0 ; t<5 ; t++){    // two cycles
    
        ared=0; //reset e counter
        ablue=0; //reset e counter
        agreen=0; //reset e counter
    digitalWrite(13,1);
    lcd.setCursor(0, 0);
    lcd.print("SENSOR 3 ; 5 LECTURAS");
    Serial.print("ok");
   //motor 
   digitalWrite(DIRC, HIGH);          // twist one way
   for(int i = 0; i < 33.3; i++){     // 200 steps for 0.9 degree step angle motor
   digitalWrite(STEPC, HIGH);       // high level
   delay(1);          // por 10 mseg
   digitalWrite(STEPC, LOW);        // low level
   delay(1);          // por 10 mseg
   }
   
              //////// sensor /////////
              
   for(int d=0; d<n ; d++){  // number of sensor readings
    
   digitalWrite(S10,LOW);     // set photodiodes
   digitalWrite(S11,LOW);     // with net filter
    red = pulseIn(salidaTCS3, LOW); // get sensor output pulse duration
   delay(200);       // 200 msec delay
  
   digitalWrite(S10,HIGH);    // set photodiodes
   digitalWrite(S11,HIGH);    // with green filter
    green = pulseIn(salidaTCS3, LOW);  // get sensor output pulse duration
   delay(200);       // 200 msec delay
  
   digitalWrite(S10,LOW);     // set photodiodes
   digitalWrite(S11,HIGH);    // with blue filter
    blue = pulseIn(salidaTCS3, LOW); // get sensor output pulse duration
   delay(200);       // 200 msec delay


                 //////// Screen printing /////////

   lcd.setCursor(0, 3);
   lcd.print("R:"); 
   Serial.print("R:");     // shows text
   Serial.print(red);     // show value of variable network
   lcd.print(red);  
   Serial.print("\t");     // tab space
   lcd.print(" ");
   lcd.print("V:");  
   Serial.print("V:");     // shows text
   Serial.print(green);    // show value of variable green
   lcd.print(green);
   Serial.print("\t");     // tab space
   lcd.print(" A:"); 
   Serial.print("A:");     // shows text
   Serial.println(blue);   // show value of variable blue
   lcd.print(blue);                      // and line break
  
   //CONTADORES//
   
   red=red+ared;   
   ared=red;   
    
   blue=blue+ablue;   
   ablue=blue;    

   green=green+agreen;   
   agreen=green;
            
   }
   
   //// averaged results /////
      tred = ared/n;
      tblue = ablue/n;
      tgreen = agreen/n;

                                   ///// printing results LCD SCREEN /////
   Serial.print("red ");
   Serial.print(t+1);  
   Serial.print(": ");
   Serial.println(tred);
    Serial.println("ok");
   
   if ( tred < 180 && tgreen > 180 && tblue > 180){    // if values ​​within the range
    lcd.setCursor(t, 1);
    lcd.print("O");            // shows text
    Serial.println("O");       // shows text
    delay(2500);
  }
  else{
    lcd.setCursor(t, 1);
    lcd.print("X"); 
    Serial.println("X");  
  }
                              
                              
                              ////////SAVING RESULTS IN SD /////////
                              
  Serial.println("Initializing card ...");  // text in monitor window
  if (!SD.begin(SSpin)) {     // SD card initialization
    Serial.println("initialization failure !");// if it fails it shows corresponding text and
    return;         // setup () is exited to end the program
  }
  
  Serial.println("correct initialization");  // correct initialization text
  archivo = SD.open("test.txt", FILE_WRITE);  // open for reading / writing test.txt file

  if (archivo) {
    archivo.print("red ");   //// red 
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tred);
    
    archivo.print("blue ");   //// blue
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tblue);

    archivo.print("green ");   //// green
    archivo.print(t+1);  
    archivo.print(": ");
    archivo.println(tgreen);
    
    Serial.println("Writing in test.txt file..."); // text on serial monitor
    archivo.close();        // closing the file
    Serial.println("correct writing"); // correct writing text on serial monitor
  } else {
    Serial.println("error in opening test.txt");  // fault text on file open
  }

  archivo = SD.open("test.txt");    // open file test.txt
  if (archivo) {
    Serial.println("Contents of test.txt:"); // text on serial monitor
    while (archivo.available()) {   // as long as there is content in the file
      Serial.write(archivo.read());     // reading one character at a time
    }
    //archivo.close();        // closing file
  } else {
    Serial.println("error in opening test.txt");// fault text on file open
  }
    }  ///final for
} //// final key 2


    } //Final de void Loop

 
