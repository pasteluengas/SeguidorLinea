/*
 * IN1 E IN2 DEBEN SER DEL MOTOR IZQUIERDO
 * IN3 E IN4 DEBEN SER DEL MOTOR DERECHO
 * 
 * PARA QUE CADA SENSOR DIRIGA LA RUEDA DEL LADO OPUESTO
 * 
 */

#define IN1 5
#define IN2 6
#define IN3 7
#define IN4 8

#define SensorIzq 9
#define SensorDer 10


/*
LA FUNCION RECIBE UN ARRAY DE LA FORMA
[LOW/HIGH, LOW/HIGH, LOW/HIGH, LOW/HIGH]
DONDE
[0] = IN1
[1] = IN2
[2] = IN3
[3] = IN4

*/
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

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(SensorIzq, INPUT);
  pinMode(SensorDer, INPUT);
}

void loop() {
    int newvals[4] = {
      !(digitalRead(SensorDer)), // IN1
      (digitalRead(SensorDer)), // IN2
      !(digitalRead(SensorIzq)), // IN3
      (digitalRead(SensorIzq)) // IN4
    };
      
  PuenteH_Update(newvals);
  
  delay(15);
}
