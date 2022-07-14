#include <QTRSensors.h>
#include <Pixy2.h>

/*
 * Hardware:
 * - TCS: Sensor de color
 * - QTR: Sensor de linea
 * 
 * -----------------------
 * |        PINES        |
 * -----------------------
 */
 
//const uint8_t QTR[] = {23, 25, 27, 29, 31, 33, 35, 37};
const uint8_t QTR[] = {37, 35, 33, 31, 29, 27, 25, 23};
const int QTREmisor = 39;
const int motores[] = {5, 6, 7, 8, 9, 10, 11, 12};
const int pushPin = A7;
const int pixyWidth = 316;
const int pixyHeight = 208;
const bool calibrar = true;

/* --------------------------
 * |   VARIABLES GLOBALES   |
 * --------------------------
 */

QTRSensors qtrrc;
Pixy2 pixy;
int timeoutLento = 0;
int timeoutLinea = 0;
int timeoutPixy = 0;
bool verdeIzq = false;
bool verdeDer = false;

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
  avanzar(100);
  delay(200);
  girarIzquierda(100);
  delay(1525);
  avanzar(150);
  delay(600);
}

//Orienta el robot 90° a la derecha
void orientarDerecha() {
  avanzar(100);
  delay(200);
  girarDerecha(100);
  delay(1650);
  avanzar(150);
  delay(600);
}

void orientarAtras() {
  avanzar(100);
  delay(200);
  girarIzquierda(100);
  delay(3200);
  avanzar(150);
  delay(600);
}

/* --------------------
 * |   SETUP Y LOOP   |
 * --------------------
 */

void setup() {
  Serial.begin(9600);
  pinMode(pushPin, INPUT);
  qtrrc.setTypeRC();
  qtrrc.setSensorPins(QTR, 8);
  qtrrc.setEmitterPin(QTREmisor);
  Serial.print("Calibrando");
  for (int i = 0; i < 400; i++) {
    if(i % 100 == 0) {
      Serial.print(".");
    }
    if(calibrar) {
      qtrrc.calibrate();
    }
  }
  Serial.print("\n");
  pixy.init();
}

void loop() {
  uint16_t valoresDeLinea[8];
  bool linea[8];
  short ubicacionDeLinea = qtrrc.readLineBlack(valoresDeLinea);
  bool boton = digitalRead(pushPin);
  bool sobreLinea = false;
  
  if(boton == 1) {
    regresar(100);
    delay(600);
    orientarIzquierda();
    avanzar(100);
    delay(500);
    orientarDerecha();
    avanzar(100);
    delay(1400);
    orientarDerecha();
    avanzar(100);
    delay(500);
    orientarIzquierda();
    avanzar(100);
    delay(300);
  }
  
  for(int i = 0; i < 8; i++) {
    linea[i] = valoresDeLinea[i] >= 650;
    sobreLinea |= linea[i];
  }
  if(!sobreLinea) {
    timeoutLinea++;
  } else {
    timeoutLinea = 0;
  }

  if(timeoutLinea > 80 && timeoutLento == 0) {
    regresar(255);
    delay(900);
    timeoutLento = 300;
  }
  
  pixy.ccc.getBlocks();
  for(int i = 0; i < pixy.ccc.numBlocks; i++) {
    if(abs(pixy.ccc.blocks[i].m_y - pixyHeight / 2) < 80) {
      if(pixy.ccc.blocks[i].m_x < pixyWidth / 2) {
        verdeIzq = true;
      } else {
        verdeDer = true;
      }
    }
  }
  
  if(verdeIzq || verdeDer) {
    if(timeoutPixy > 20) {
      if(verdeIzq && verdeDer) {
        orientarAtras();
      } else if (verdeIzq) {
        orientarIzquierda();
      } else if (verdeDer) {
        orientarDerecha();
      }
      timeoutPixy = 0;
      verdeIzq = false;
      verdeDer = false;
    } else {
      timeoutPixy++;
    }
  }
  
  //Manejo del robot
  byte giroIzq = (linea[0] + linea[1] + linea[2] + linea[3]) * 63;
  byte giroDer = (linea[7] + linea[6] + linea[5] + linea[4]) * 63;
  if(giroIzq > giroDer) {
    giroIzq -= giroDer;
    giroDer = 0;
  } else if (giroDer > giroIzq) {
    giroDer -= giroIzq;
    giroIzq = 0;
  } else if (giroIzq == giroDer) {
    giroIzq = 0;
    giroDer = 0;
  }
  if(giroIzq > 0 && giroDer > 0) {
    if(timeoutLento > 0) {
      avanzar(40);
      timeoutLento--;
    } else {
      avanzar(100);
    }
  } else if (giroIzq > 0) {
    girarIzquierda(giroIzq);
  } else if (giroDer > 0) {
    girarDerecha(giroDer);
  } else {
    if(timeoutLento > 0) {
      avanzar(40);
      timeoutLento--;
    } else {
      avanzar(100);
    }
  }
}
