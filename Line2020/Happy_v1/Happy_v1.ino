#include <QTRSensors.h>
#include <LiquidCrystal.h>

/*
 * Hardware:
 * - TCS: Sensor de color
 * - QTR: Sensor de linea
 * 
 * -----------------------
 * |        PINES        |
 * -----------------------
 */

//S0, S1, S2, S3 y OUT respectivamente
const int TCSIzq[] = {50, 48, 44, 46, 42};
const int TCSDer[] = {51, 53, 47, 45, 49};

const uint8_t QTR[] = {24, 26, 28, 30, 32, 38, 36, 34};
const int QTREmisor = 22;

const int motores[] = {5, 6, 7, 8, 9, 10, 11, 12};
const int lcds[] = {19, 18, 17, 16, 15, 14};

const int boton = 41;

/* --------------------------
 * |   VARIABLES GLOBALES   |
 * --------------------------
 */

String texto[] = {"", "", "", ""};
enum Color{BLANCO, NEGRO, ROJO, VERDE, AZUL};
QTRSensors qtrrc;
LiquidCrystal lcd(lcds[0], lcds[1], lcds[2], lcds[3], lcds[4], lcds[5]);

/* ---------------
 * |   MOTORES   |
 * ---------------
 */

/*
 * Clase que corresponde a un solo motor o llanta
 */
class Motor {
  private:
    byte pinA, pinB;

    //Avanza la llanta con rapidez de 0 a 255
    void avanza(byte rapidez) {
      analogWrite(pinA, rapidez);
      analogWrite(pinB, 0);
    }

    //Regresa la llanta con rapidez de 0 a 255
    void regresa(byte rapidez) {
      analogWrite(pinA, 0);
      analogWrite(pinB, rapidez);
    }
    
  public:
    //Crea un nuevo motor con los pines definidos por el usuario
    Motor(byte pinA, byte pinB) {
      this->pinA = pinA;
      this->pinB = pinB;
      pinMode(pinA, OUTPUT);
      pinMode(pinB, OUTPUT);
    }

    //Mueve la llanta a cierta rapidez y si el segundo parametro es verdadero se regresa en lugar de avanzar
    void mover(byte rapidez, bool regresar = false) {
      if(regresar) {
        regresa(rapidez);
      } else {
        avanza(rapidez);
      }
    }
};

//Define los pines de cada motor y crea una nueva instancia de la clase motor para cada llanta
Motor frontalIzq(motores[4], motores[5]);
Motor frontalDer(motores[3], motores[2]);
Motor traseraIzq(motores[6], motores[7]);
Motor traseraDer(motores[1], motores[0]);

//Gira los cuatro llantas con rapidez de 0 a 255 hacia adelante
void avanzar(byte rapidez) {
  frontalIzq.mover(rapidez);
  frontalDer.mover(rapidez);
  traseraIzq.mover(rapidez);
  traseraDer.mover(rapidez);
}

//Gira los cuatro llantas hacia atras con rapidez de 0 a 255
void regresar(byte rapidez) {
  frontalIzq.mover(rapidez, true);
  frontalDer.mover(rapidez, true);
  traseraIzq.mover(rapidez, true);
  traseraDer.mover(rapidez, true);
}

//Gira los cuatro llantas (dos adelante y dos atras) para hacer un movimiento giratorio a la derecha
void girarDerecha(byte rapidez) {
  frontalIzq.mover(rapidez);
  traseraIzq.mover(rapidez);
  frontalDer.mover(rapidez, true);
  traseraDer.mover(rapidez, true);
}

//Gira los cuatro llantas (dos adelante y dos atras) para hacer un movimiento giratorio a la izquierda
void girarIzquierda(byte rapidez) {
  frontalIzq.mover(rapidez, true);
  traseraIzq.mover(rapidez, true);
  frontalDer.mover(rapidez);
  traseraDer.mover(rapidez);
}

//Solo gira las llantas de un lado para hacer una rotación mas amplia que la función de girarDerecha
void girarAmpliamenteDerecha(byte rapidez) {
  frontalIzq.mover(rapidez);
  traseraIzq.mover(rapidez);
  frontalDer.mover(0);
  traseraDer.mover(0);
}

//Solo gira las llantas de un lado para hacer una rotación mas amplia que la función de girarIzquierda
void girarAmpliamenteIzquierda(byte rapidez) {
  frontalIzq.mover(0);
  traseraIzq.mover(0);
  frontalDer.mover(rapidez);
  traseraDer.mover(rapidez);
}

//Detiene las cuatro llantas
void detener() {
  frontalIzq.mover(0);
  traseraIzq.mover(0);
  frontalDer.mover(0);
  traseraDer.mover(0);
}

//Orienta el robot 90° a la izquierda
void orientarIzquierda() {
  girarAmpliamenteIzquierda(150);
  delay(800);
  girarIzquierda(100);
  delay(800);
}

//Orienta el robot 90° a la derecha
void orientarDerecha() {
  girarAmpliamenteDerecha(150);
  delay(800);
  girarDerecha(100);
  delay(800);
}

/* -----------------
 * |   FUNCIONES   |
 * -----------------
 */

//Recibe datos del sensor TCS3200 y utilizando cálculos matemáticos obtiene el color como un enumerador
Color detectarColor(int TCS[]) {
  unsigned long frecuencia;
  digitalWrite(TCS[2], LOW);
  digitalWrite(TCS[3], LOW);
  frecuencia = pulseIn(TCS[4], LOW);
  frecuencia = map(frecuencia, 25, 72, 255, 0);
  unsigned long r = frecuencia;
  digitalWrite(TCS[2], HIGH);
  digitalWrite(TCS[3], HIGH);
  frecuencia = pulseIn(TCS[4], LOW);
  frecuencia = map(frecuencia, 30, 90, 255, 0);
  unsigned long g = frecuencia;
  digitalWrite(TCS[2], LOW);
  digitalWrite(TCS[3], HIGH);
  frecuencia = pulseIn(TCS[4], LOW);
  frecuencia = map(frecuencia, 25, 70, 255, 0);
  unsigned long b = frecuencia;
  float avg = (r + g + b) / 3; //Promedio
  float stddev = sqrt(((r - avg) * (r - avg) + (g - avg) * (g - avg) + (b - avg) * (b - avg)) / 3); //Desviación estandar
  if(stddev < 40) {
    return BLANCO;
  }
  if (stddev < 300) {
    return NEGRO;
  }
  if(r > g && r > b) {
    return ROJO;
  }
  if (g > b) {
    return VERDE;
  }
  return AZUL;
}

//Imprime una nueva linea al display de LCD, recorriendo los demás lineas hacia arriba
void imprime(String str) {
  if(str.length() > 20) {
    str = str.substring(0, 20);
  }
  while(str.length() < 20) {
    str += " ";
  }
  for(int i = 0; i < 3; i++) {
    texto[i] = texto[i + 1];
  }
  texto[3] = str;
  for(int i = 0; i < 4; i++) {
    lcd.setCursor(0, i);
    lcd.print(texto[i]);
  }
}

/* --------------------
 * |   SETUP Y LOOP   |
 * --------------------
 */

//Se inicializan los pines, la LCD, el sensor QTR y el sensor TCS
void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);
  imprime("<- Mover ->");
  imprime("Calibrando");
  for(int i = 0; i < 4; i++) {
    pinMode(TCSIzq[i], OUTPUT);
    pinMode(TCSDer[i], OUTPUT);
  }
  pinMode(TCSIzq[4], INPUT);
  pinMode(TCSDer[4], INPUT);
  pinMode(boton, INPUT);
  digitalWrite(TCSIzq[0], HIGH);
  digitalWrite(TCSIzq[1], LOW);
  digitalWrite(TCSDer[0], HIGH);
  digitalWrite(TCSDer[1], LOW);
  qtrrc.setTypeRC();
  qtrrc.setSensorPins(QTR, 8);
  qtrrc.setEmitterPin(QTREmisor);
  lcd.setCursor(10, 3);
  for (int i = 0; i < 400; i++) {
    if(i % 100 == 0) {
      lcd.write("."); //Pequeño efecto que crea puntos después de la palabra calibrando
    }
    qtrrc.calibrate();
  }
  imprime("Happy va a bailar!");
}

//Se obtienen los valores relevantes de los sensores y se actua en base a ellos
void loop() {
  bool botonActivado = digitalRead(boton); //Obtiene el valor del switch que esta en la parte frontal del robot
  Color izq = detectarColor(TCSIzq); //Obtiene el color del sensor de la izquierda
  Color der = detectarColor(TCSDer); //Obtiene el color del sensor de la derecha
  uint16_t valoresDeLinea[8];
  bool linea[8]; //Arreglo de booleanos que indica true si la linea negra esta debajo de este sensor
  int ubicacionDeLinea = qtrrc.readLineBlack(valoresDeLinea);
  for(int i = 0; i < 8; i++) {
    linea[i] = valoresDeLinea[i] >= 650;
  }
  logica(izq, der, linea, ubicacionDeLinea, botonActivado);
}

/* --------------
 * |   LÓGICA   |
 * --------------
 */

void logica(Color izq, Color der, bool linea[], int ubicacion, bool botonActivado) {
  
}
