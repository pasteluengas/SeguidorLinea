/*
 * IN1 E IN2 DEBEN SER DEL MOTOR IZQUIERDO
 * IN3 E IN4 DEBEN SER DEL MOTOR DERECHO
 * 
 * PARA QUE CADA SENSOR DIRIGA LA RUEDA DEL LADO OPUESTO
 * 
 */

#include <Bonezegei_HCSR04.h>

// DEFINIENDO PINES Y ESTADOSS
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

#define SensorIzq 9
#define SensorDer 10

#define SIGUIENDOLINEA 0
#define EVADIENDOOBSTACULO 1

#define ECHO_PIN 11
#define TRIGGER_PIN 13

#define CMSIBILIDAD 13

Bonezegei_HCSR04 ultrasonic(TRIGGER_PIN, ECHO_PIN);
/*
LA FUNCION RECIBE UN ARRAY DE LA FORMA
[LOW/HIGH, LOW/HIGH, LOW/HIGH, LOW/HIGH]
DONDE
[0] = IN1
[1] = IN2
[2] = IN3
[3] = IN4

*/

// SEGUIDOR DE LINEA
int PuenteH_Values[4] = {LOW, LOW, LOW, LOW};
int PuenteH_Pins[4] = {IN1, IN2, IN3, IN4};

void blindUpdate(int what, int to) {
  digitalWrite(PuenteH_Pins[what], to);
  PuenteH_Values[what] = to;
}

void PuenteH_Update(int newValues[]) {
    if (PuenteH_Values[0] != newValues[0]) blindUpdate(0, newValues[0]);
    if (PuenteH_Values[1] != newValues[1]) blindUpdate(1, newValues[1]);
    if (PuenteH_Values[2] != newValues[2]) blindUpdate(2, newValues[2]);
    if (PuenteH_Values[3] != newValues[3]) blindUpdate(3, newValues[3]);
}


// EVASOR DE OBSTACULOS
int Look4Obs() {
  // getDistance() te masturba en centimetros
  int d=ultrasonic.getDistance();
  if ((d <= CMSIBILIDAD)) return EVADIENDOOBSTACULO;
  return SIGUIENDOLINEA;
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(SensorIzq, INPUT);
  pinMode(SensorDer, INPUT);
}

int state = SIGUIENDOLINEA;
void loop() {
    if(state == SIGUIENDOLINEA) {
      int newvals[4] = {
      (digitalRead(SensorDer)), // IN1
      !(digitalRead(SensorDer)), // IN2
      (digitalRead(SensorIzq)), // IN3
      !(digitalRead(SensorIzq)) // IN4
      };
      PuenteH_Update(newvals);
    }

    /*
    state = Look4Obs();
    
    if (state == EVADIENDOOBSTACULO) {
       int valus[4] = {1, 1, 1, 1,};
       PuenteH_Update(valus);
       delay(2000);

       int valus2[4] = {0, 1, 1, 0,};
       PuenteH_Update(valus2);
       delay(2000);

       int valus3[4] = {1, 0, 0, 1,};
       PuenteH_Update(valus3);
       delay(2000);

       int valus4[4] = {0, 1, 0, 1,};
       PuenteH_Update(valus4);
    }*/
    delay(50);
}
