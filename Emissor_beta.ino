/* TR Mà artificial. Versió alfa (probes) 2018-19
https://tecnologicsib.wixsite.com/artificialhandtr/blog/programa-de-l-emissor-versió-alfa */
#include <SoftwareSerial.h>  
SoftwareSerial BT(10,11);
// Valors amb que treballem:
const int sensor = A0;  // pin de connexió del sensor
const int consigna = 150; // depen de l'usuari
int valor_sensor = 0;  // valor de la lectura del pin del sensor
int estat_actual = 0;
int estat_anteror = 0;

void setup() 
{
    BT.begin(9600);
    
    pinMode(sensor, INPUT);
}

void loop() 
{
    // Desem el valor de la lectura del sensor:
    valor_sensor = analogRead(sensor);
    
    // Comparem la lectura del sensor amb la consigna establerta i definim el valor de l'estat actual segons el resultat de la comparació:
    if ((valor_sensor > consigna)) {estat_actual = 1;}
    else {estat_actual = 0;}
    
    // Només s'enviarà una dada per bluetooth si ha canviat l'estat actual respecte al bucle anterior:
    if ((estat_actual != estat_anteror)) {BT.println('A');}
    
    // L'estat actual serà l'estat anterior per al següent bucle d'execució:
    estat_anteror = estat_actual;
    
    // petita pausa per estabilitzar abans de tornar a executar el bucle:
    delay(10);
}
