/****************************************************************
*                  Arduino lectura del sensor CMPS10            *
*                    CMPS10 en modo I2C                         *
*                    Aitor Azpiroz, 2014                        *
*****************************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>
#include<TimerOne.h>
#include <SPI.h>
#include <SD.h>

#define ADDRESS 0x60        // La didreccion I2C del sensor
byte highByte, lowByte, fine;              // highByte y lowByte miden el Byte alto y bajo de la desbiacion y fine el decimal 
int pitch, roll;                          // Miden y guardan las inclinaciones lateral y frontal
int bearing;                               // Guarda la desbiacion
const int chipSelect = 4;
   
 void setup()
  {
  Timer1.initialize(1000000);     //Iniciar Interrupciom a 0,1 sg
  Timer1.attachInterrupt(timelsr);
  //Serial.print("Poniendo en marcha la lectura del movimiento de cabeza ...");
  Serial.begin(9600);            // Comenzar la comunicacion Serie
  Wire.begin();                  // Arrancar la comunicacion I2C
  pinMode(10, OUTPUT);         // Esto es necesario aunque creas que no lo usas.
  if (!SD.begin(chipSelect))
    {
    //Serial.println("Error al leer la tarjeta.");
    return;
    }
  }

 void loop()
   {
   Wire.beginTransmission(ADDRESS);           //Poner en marcha la comunicacion I2C
   Wire.write(2);                              //El registro que queremos leer en el Sensor
   Wire.endTransmission();
   Wire.requestFrom(ADDRESS, 4);              // pedir la lectura de 4 Bytes
   while(Wire.available() < 4);               // Esperar a que los 4 Bytes estén listos
   highByte = Wire.read();                    // HAcer las 3 lecturas del sensor y guardarlas
   lowByte = Wire.read();            
   pitch = Wire.read();              
   roll = Wire.read();               
   
   bearing = ((highByte<<8)+lowByte)/10;      // Calcular la desbiación que tenemos con respecto al norte
   fine = ((highByte<<8)+lowByte)%10;         // Calcular la decimal de la desviacion  
   
   //Serial.print("Pitch: ");         // Escribir las lecturas en el monitor Serie
   Serial.print(pitch);
   Serial.print("\n");
   //Serial.print("Roll: ");
   Serial.print(roll);
   Serial.print("\n");
   //Serial.print("Bearing: ");
   Serial.print(bearing);
    Serial.print("\n");
   
   
    // Abrimos el fichero donde vamos a guardar los datos (Si no existe se crea automaticamente).
  File dataFile1 = SD.open("Bearing.txt", FILE_WRITE); 
  File dataFile2 = SD.open("Pitch.txt", FILE_WRITE); 
  File dataFile3 = SD.open("Roll.txt", FILE_WRITE); 
   
     // Si el fichero es correcto escribimos en el.
  if (dataFile1) {
    // Escribimos en el fichero "Bearing: "
    dataFile1.print("Bearing: ");
    // A continuacion escribimos el valor de la variable bearing y saltamos a la linea siguiente.
    dataFile1.println(bearing);
    // Cerramos el archivo.
    dataFile1.close();
   
    // Avisamos de que se ha podido escribir correctamente.
   // Serial.println("");
  //  Serial.println("Impresion en SD Bearing correcta");
   
  // Si no pudimos escribir en el fichero avisamos por el puerto serie.
  }else{
   // Serial.println("Error al escribir en Bearing.txt");
  }
 
        // Si el fichero es correcto escribimos en el.
  if (dataFile2) {
    // Escribimos en el fichero "Pitch: "
    dataFile2.print("Pitch: ");
    // A continuacion escribimos el valor de la variable pitch y saltamos a la linea siguiente.
    dataFile2.println(pitch);
    // Cerramos el archivo.
    dataFile2.close();
   
    // Avisamos de que se ha podido escribir correctamente.
   // Serial.println("Impresion en SD Pitch correcta");
   
  // Si no pudimos escribir en el fichero avisamos por el puerto serie.
  }else{
  //  Serial.println("Error al escribir en Pitch.txt");
  }
 
   
      // Si el fichero es correcto escribimos en el.
  if (dataFile3) {
    // Escribimos en el fichero "Roll: "
    dataFile3.print("Roll: ");
    // A continuacion escribimos el valor de la variable roll y saltamos a la linea siguiente.
    dataFile3.println(roll);
    // Cerramos el archivo.
    dataFile3.close();
   
    // Avisamos de que se ha podido escribir correctamente.
   
   // Serial.println("Impresion en SD Roll correcta");
   //Serial.println("");
  // Si no pudimos escribir en el fichero avisamos por el puerto serie.
  }else{
   // Serial.println("Error al escribir en Roll.txt");
  }
   delay(500);
   }

void timelsr()
   {
 
   
   }
