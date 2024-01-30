#include <elapsedMillis.h>
#include <wiring_time.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795

#include "lib/Serial.h"

// #define LED_BUILTIN PA_5
HardwareSerial Serial1(PA_10, PA_9); // PA_10:RX - PA_9:TX

Lechugator::SerialLogger serialLogger(9600);


// Motor 1 = M1
int M1_EN = PA_4;
int M1_R = PA_0;
int M1_L = PA_1;
int M1_vel = 0;

// Encoder del Motor 1
int Enc1 = PC_2;
int Enc1_Vue = PC_3;
volatile unsigned Mue_Act_Int1 = 0;
volatile unsigned Mue_Ant_Int1 = 0;
volatile unsigned Del_Mue_Int1 = 0;
double Fre_M1 = 0;
double Wr_M1 = 0;
double RPM_M1 = 0;
double Vel_Lin_M1 = 0;
int Ran_M1 = 15;
int Con_Enc1 = 0;
int Res_Eco1 = 3;
int Tam_Enc1 = 10;
volatile unsigned Pro_Enc1 = 0;
float Vec_Enc1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Motor 2 = M2
int M2_EN = PA_5;
int M2_R = PA_6;
int M2_L = PA_7;
int M2_vel = 0;
// Encoder del Motor 2
int Enc2 = PC_1;
int Enc2_Vue = PC_0;
volatile unsigned Mue_Act_Int2 = 0;
volatile unsigned Mue_Ant_Int2 = 0;
volatile unsigned Del_Mue_Int2 = 0;
double Fre_M2 = 0;
double Wr_M2 = 0;
double RPM_M2 = 0;
double Vel_Lin_M2 = 0;
int Ran_M2 = 15;
int Con_Enc2 = 0;
int Res_Eco2 = 3;
int Tam_Enc2 = 10;
volatile unsigned Pro_Enc2 = 0;
float Vec_Enc2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Motor 3 = M3
int M3_EN = PB_2;
int M3_R = PB_1;
int M3_L = PB_0;
int M3_vel = 0;
// Encoder del Motor 3
int Enc3 = PB_10;
int Enc3_Vue = PB_13;
volatile unsigned Mue_Act_Int3 = 0;
volatile unsigned Mue_Ant_Int3 = 0;
volatile unsigned Del_Mue_Int3 = 0;
double Fre_M3 = 0;
double Wr_M3 = 0;
double RPM_M3 = 0;
double Vel_Lin_M3 = 0;
int Ran_M3 = 15;   // Ranuras del enconder
int Con_Enc3 = 0;  // Contador del encoder
int Res_Eco3 = 3;  // Numero de pulso que cuanta
int Tam_Enc3 = 10; // Tamaño del vetor
volatile unsigned Pro_Enc3 = 0;
float Vec_Enc3[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Motor 4 = M4
int M4_EN = PB_3;
int M4_R = PB_5;
int M4_L = PB_6;
int M4_vel = 0;
// Encoder del Motor 4
int Enc4 = PB_9;
int Enc4_Vue = PB_8;
volatile unsigned Mue_Act_Int4 = 0;
volatile unsigned Mue_Ant_Int4 = 0;
volatile unsigned Del_Mue_Int4 = 0;
double Fre_M4 = 0;
double Wr_M4 = 0;
double RPM_M4 = 0;
double Vel_Lin_M4 = 0;
int Ran_M4 = 15;
int Con_Enc4 = 0;
int Res_Eco4 = 3;
int Tam_Enc4 = 10;
volatile unsigned Pro_Enc4 = 0;
float Vec_Enc4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Velocidad Totla
int Vel_Mov = 15;
int Vel_Gir = 150;

// Comunicacion
char estado;

void setup()
{
  serialLogger.addLogger(Serial1);
  serialLogger.initLoggers();

  // Serial.begin(115200);
  // Serial1.begin(115200);

  // Declaracion de pines Motor 1
  pinMode(M1_EN, OUTPUT);
  pinMode(M1_R, OUTPUT);
  pinMode(M1_L, OUTPUT);

  // Declaracion de pines Motor 2
  pinMode(M2_EN, OUTPUT);
  pinMode(M2_R, OUTPUT);
  pinMode(M2_L, OUTPUT);

  // Declaracion de pines Motor 3
  pinMode(M3_EN, OUTPUT);
  pinMode(M3_R, OUTPUT);
  pinMode(M3_L, OUTPUT);

  // Declaracion de pines Motor 4
  pinMode(M4_EN, OUTPUT);
  pinMode(M4_R, OUTPUT);
  pinMode(M4_L, OUTPUT);
  // pinMode(Enc4, INPUT);
  // pinMode(Sen4_Gui, INPUT);

  // Encoder 1
  attachInterrupt(digitalPinToInterrupt(Enc1), Encoder1, FALLING);
  attachInterrupt(digitalPinToInterrupt(Enc1_Vue), Encoder1_Vuelta, FALLING);

  // Encoder 2
  attachInterrupt(digitalPinToInterrupt(Enc2), Encoder2, FALLING);
  attachInterrupt(digitalPinToInterrupt(Enc2_Vue), Encoder2_Vuelta, FALLING);

  // Encoder 3
  attachInterrupt(digitalPinToInterrupt(Enc3), Encoder3, FALLING);
  attachInterrupt(digitalPinToInterrupt(Enc3_Vue), Encoder3_Vuelta, FALLING);

  // Encoder 4
  attachInterrupt(digitalPinToInterrupt(Enc4), Encoder4, FALLING);
  attachInterrupt(digitalPinToInterrupt(Enc4_Vue), Encoder4_Vuelta, FALLING);
}

void loop()
{

  // estado = Serial1.read();
  estado = Serial.read();

  Mue_Act_Int1 = millis();
  Mue_Act_Int2 = millis();
  Mue_Act_Int3 = millis();
  Mue_Act_Int4 = millis();

  if (Del_Mue_Int1 >= 200 * Res_Eco1)
  {
    Fre_M1 = 0;
  }
  //------------------ --------Calculo de la velocidades  Motor 1--------------------------------------

  // Serial1.print("frecuancia: ");
  // Serial1.println(Fre_M4);
  // Serial1.print("velocidad Angular: ");
  // Serial1.println(Wr_M4);
  serialLogger.print("RPM 1 : ");
  serialLogger.println(RPM_M1);
  serialLogger.println(Del_Mue_Int1);
  // Serial1.print("RPM 1 : ");
  // Serial1.println(RPM_M1);
  // Serial1.println(Del_Mue_Int1);
  // Serial1.print("RPM 2 : ");
  // Serial1.println(RPM_M2);
  // Serial1.print("RPM 3 : ");
  // Serial1.println(RPM_M3);
  // Serial1.print("RPM 4 : ");
  // Serial1.println(RPM_M4);
  // Serial1.print("velocidad lineal: ");
  // Serial1.println(Vel_Lin_M4);

  switch (estado)
  {

  case 'w':
    serialLogger.println("Adelante");
    // Serial.println("Adelante");
    // Serial1.println("Adelante");
    Adelante();

    estado = 0;
    break;

  case 's':
    serialLogger.println("Atras");
    // Serial.println("Atras");
    // Serial1.println("Atras");
    Atras();
    estado = 0;
    break;

  case 'a':
    Derecha();
    estado = 0;
    break;

  case 'd':
    Izquierda();
    estado = 0;
    break;

  case 'q':
    serialLogger.println("Stop");
    // Serial.println("Stop");
    // Serial1.println("Stop");
    Stop();
    estado = 0;
    break;
  }
}

void Adelante()
{
  // Motor 1
  digitalWrite(M1_EN, HIGH);
  analogWrite(M1_R, Vel_Mov);
  analogWrite(M1_L, 0);
  // Motor 2
  digitalWrite(M2_EN, HIGH);
  analogWrite(M2_R, Vel_Mov);
  analogWrite(M2_L, 0);
  // Motor 3
  digitalWrite(M3_EN, HIGH);
  analogWrite(M3_R, Vel_Mov);
  analogWrite(M3_L, 0);
  // Motor 4
  digitalWrite(M4_EN, HIGH);
  analogWrite(M4_R, Vel_Mov);
  analogWrite(M4_L, 0);
}

void Atras()
{
  // Motor 1
  digitalWrite(M1_EN, HIGH);
  analogWrite(M1_R, 0);
  analogWrite(M1_L, Vel_Mov);
  // Motor 2
  digitalWrite(M2_EN, HIGH);
  analogWrite(M2_R, 0);
  analogWrite(M2_L, Vel_Mov);
  // Motor 3
  digitalWrite(M3_EN, HIGH);
  analogWrite(M3_R, 0);
  analogWrite(M3_L, Vel_Mov);
  // Motor 4
  digitalWrite(M4_EN, HIGH);
  analogWrite(M4_R, 0);
  analogWrite(M4_L, Vel_Mov);
}

void Izquierda()
{
  // Motor 1
  digitalWrite(M1_EN, HIGH);
  analogWrite(M1_R, Vel_Gir);
  analogWrite(M1_L, 0);
  // Motor 2
  digitalWrite(M2_EN, HIGH);
  analogWrite(M2_R, Vel_Gir);
  analogWrite(M2_L, 0);
  // Motor 3
  digitalWrite(M3_EN, HIGH);
  analogWrite(M3_R, 0);
  analogWrite(M3_L, Vel_Gir);
  // Motor 4
  digitalWrite(M4_EN, HIGH);
  analogWrite(M4_R, 0);
  analogWrite(M4_L, Vel_Gir);
}

void Derecha()
{
  // Motor 1
  digitalWrite(M1_EN, HIGH);
  analogWrite(M1_R, 0);
  analogWrite(M1_L, Vel_Gir);
  // Motor 2
  digitalWrite(M2_EN, HIGH);
  analogWrite(M2_R, 0);
  analogWrite(M2_L, Vel_Gir);
  // Motor 3
  digitalWrite(M3_EN, HIGH);
  analogWrite(M3_R, Vel_Gir);
  analogWrite(M3_L, 0);
  // Motor 4
  digitalWrite(M4_EN, HIGH);
  analogWrite(M4_R, Vel_Gir);
  analogWrite(M4_L, 0);
}

void Stop()
{
  // Motor 1
  digitalWrite(M1_EN, LOW);
  analogWrite(M1_R, 0);
  analogWrite(M1_L, 0);
  // Motor 2
  digitalWrite(M2_EN, LOW);
  analogWrite(M2_R, 0);
  analogWrite(M2_L, 0);
  // Motor 3
  digitalWrite(M3_EN, LOW);
  analogWrite(M3_R, 0);
  analogWrite(M3_L, 0);
  // Motor 4
  digitalWrite(M4_EN, LOW);
  analogWrite(M4_R, 0);
  analogWrite(M4_L, 0);
}

void Encoder1()
{
  Con_Enc1++;

  if (Con_Enc1 == Res_Eco1)
  {
    Pro_Enc1 = 0;
    Mue_Act_Int1 = millis();
    Del_Mue_Int1 = Mue_Act_Int1 - Mue_Ant_Int1;
    //----------------------------PROMEDIO DE LOS DATOS Encoder 1------------------------------
    for (int e = 0; e < Tam_Enc1 - 1; e++)
    {
      Vec_Enc1[e] = Vec_Enc1[e + 1];
    }
    Vec_Enc1[Tam_Enc1 - 1] = Del_Mue_Int1;
    for (int e = 0; e < Tam_Enc1; e++)
    {
      Pro_Enc1 = Vec_Enc1[e] + Pro_Enc1;
    }
    Pro_Enc1 = Pro_Enc1 / Tam_Enc1;
    Del_Mue_Int1 = Pro_Enc1;
    //--------------------------- Calculo de la frecuancia Encoder 1----------------------------
    Fre_M1 = (1000) / (double)Del_Mue_Int1;
    //--------------------------- cambio del muestreo anterior----------------------------------
    Mue_Ant_Int1 = Mue_Act_Int1;
    //--------------------------- Contdor de pulsos a 0 ----------------------------------------
    Con_Enc1 = 0;
  }
  Wr_M1 = ((2 * 3.141516) / Ran_M1) * Fre_M1;
  RPM_M1 = ((60 / (2 * PI)) * Wr_M1) * 13;
  Vel_Lin_M1 = Wr_M1 * 0.17;
}

void Encoder1_Vuelta()
{
}

void Encoder2()
{
  Con_Enc2++;

  if (Con_Enc2 == Res_Eco2)
  {

    Pro_Enc2 = 0;
    Del_Mue_Int2 = Mue_Act_Int2 - Mue_Ant_Int2;

    for (int q = 0; q < Tam_Enc2 - 1; q++)
    {
      Vec_Enc2[q] = Vec_Enc2[q + 1];
    }
    Vec_Enc2[Tam_Enc2 - 1] = Del_Mue_Int2;
    for (int q = 0; q < Tam_Enc2; q++)
    {
      Pro_Enc2 = Vec_Enc2[q] + Pro_Enc2;
    }
    Pro_Enc2 = Pro_Enc2 / Tam_Enc2;
    Del_Mue_Int2 = Pro_Enc2;
    Mue_Ant_Int2 = Mue_Act_Int2;
    Fre_M2 = (1000) / (double)Del_Mue_Int2;
    Wr_M2 = ((2 * 3.141516) / Ran_M2) * Fre_M2;
    RPM_M2 = ((60 / (2 * 3.1416)) * Wr_M2);
    Vel_Lin_M2 = Wr_M2 * 0.17;
    Con_Enc2 = 0;
  }
}

void Encoder2_Vuelta()
{
}

void Encoder3()
{
  Con_Enc3++;

  if (Con_Enc3 == Res_Eco3)
  {

    Pro_Enc3 = 0;
    Del_Mue_Int3 = Mue_Act_Int3 - Mue_Ant_Int3;

    for (int j = 0; j < Tam_Enc3 - 1; j++)
    {
      Vec_Enc3[j] = Vec_Enc3[j + 1];
    }
    Vec_Enc3[Tam_Enc3 - 1] = Del_Mue_Int3;
    for (int j = 0; j < Tam_Enc3; j++)
    {
      Pro_Enc3 = Vec_Enc3[j] + Pro_Enc3;
    }
    Pro_Enc3 = Pro_Enc3 / Tam_Enc3;
    Del_Mue_Int3 = Pro_Enc3;
    Mue_Ant_Int3 = Mue_Act_Int3;
    Fre_M3 = (1000) / (double)Del_Mue_Int3;
    Wr_M3 = ((2 * 3.141516) / Ran_M3) * Fre_M3;
    RPM_M3 = (60 / (2 * 3.1416)) * Wr_M3;
    Vel_Lin_M3 = Wr_M3 * 0.17;
    Con_Enc3 = 0;
  }
}
void Encoder3_Vuelta()
{
}

void Encoder4()
{
  Con_Enc4++;

  if (Con_Enc4 == Res_Eco4)
  {

    Pro_Enc4 = 0;
    Del_Mue_Int4 = Mue_Act_Int4 - Mue_Ant_Int4;

    for (int i = 0; i < Tam_Enc4 - 1; i++)
    {
      Vec_Enc4[i] = Vec_Enc4[i + 1];
    }
    Vec_Enc4[Tam_Enc4 - 1] = Del_Mue_Int4;
    for (int i = 0; i < Tam_Enc4; i++)
    {
      Pro_Enc4 = Vec_Enc4[i] + Pro_Enc4;
    }
    Pro_Enc4 = Pro_Enc4 / Tam_Enc4;
    Del_Mue_Int4 = Pro_Enc4;

    Mue_Ant_Int4 = Mue_Act_Int4;
    Fre_M4 = (1000) / (double)Del_Mue_Int4;
    Wr_M4 = ((2 * 3.141516) / Ran_M4) * Fre_M4;
    RPM_M4 = (60 / (2 * 3.1416)) * Wr_M4;
    Vel_Lin_M4 = Wr_M4 * 0.17;
    Con_Enc4 = 0;
  }
}

void Encoder4_Vuelta()
{
}