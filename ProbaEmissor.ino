



// Valors amb que treballem:
const int sensor = A0;
const int consigna = 50;
int valor_sensor = 0;
int estat_actual = 0;
int estat_anteror = 0;

void setup() 
{
    Serial.begin(9600);
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
    if ((estat_actual != estat_anteror)) {Serial.println('A');}
    
    // L'estat actual serà l'estat anterior per al següent bucle d'execució:
    estat_anteror = estat_actual;
    
    // petita pausa per estabilitzar abans de tornar a executar el bucle:
    delay(10);
}
