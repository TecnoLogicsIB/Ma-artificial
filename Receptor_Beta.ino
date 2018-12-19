 /* TR Mà artificial. Versió alfa (probes) 2018-19
https://tecnologicsib.wixsite.com/artificialhandtr/blog/programa-del-receptor-versi%C3%B3-alfa */
#include <SoftwareSerial.h>
SoftwareSerial BT(10,11); 
#include <Servo.h>

// valors amb que treballem:
int posicio1 = 175;   // posició servo dits en repos
int posicio2 = 50;  // posició servo dits agarre
int posicio_servo = posicio1;  // per desar la posició en que estan els servos en cada moment
char dada_rebuda;  // per desar la dada rebuda per bluetooth
bool estat_ma = false;  // 0 (servos quiets) / 1 (servos en moviment)
Servo miServo;  // objecte relacionat amb la llibreria Servo

void setup() 
{
  BT.begin(9600);  // inici comuniació sèrie
    miServo.attach(6);  // activació del pin dels servos
    miServo.write(posicio1);  // posicionament inicial (dits en repós)
}

void loop() 
{   
    // Només si es reben dades pel port sèrie, si aquestes tenen el valor definit (A), s'invertirà el valor de estat_ma (de fals a veritable o de veritable a fals):
    if (BT.available() > 0) 
    { 
      dada_rebuda = BT.read();  // Definir el valor de la variable com el del que es rebi pel port sèrie
      if (dada_rebuda == 'A') {estat_ma = !estat_ma;}
    }
             
    // Els servos només s'han de moure quan es rebi la dada procedent del sensor (estat_ma sigui veritable):
    if (estat_ma == true) 
    {
        // Els servos ha de canviar de posició. el valor de posicio_servo s'ha d'actualitzar:
        if (posicio_servo == posicio1) 
        {
            miServo.write(posicio2);
            posicio_servo = posicio2;
            // Serial.println ("vaig a P2");  // per comprovació per consola. desactivat
        } 
        else if (posicio_servo == posicio2) 
        {
            miServo.write(posicio1);
            posicio_servo = posicio1;
            // Serial.println ("vaig a P1");  // per comprovació per consola. desactivat
        }
        
        // Deixem temps per que els servos vagin a la nova posició abans de tornar a fer fals l'estat_ma per que els servos no intentin tornar a poscionar-se
        delay(100);
        estat_ma = false;
    }
}
