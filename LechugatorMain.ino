#include <Lechugator.h>
#include "pins_lechugator.h"

HardwareSerial Serial1(EXTRA_SERIAL_RX, EXTRA_SERIAL_TX);

std::array<Lechugator::Motor, 4> motors = {
    Lechugator::Motor(
        Lechugator::MotorPins(MOTOR_1_ENABLE, MOTOR_1_CW_PWM, MOTOR_1_CCW_PWM),
        Lechugator::EncoderPins(ENCODER_1_PULSO, ENCODER_1_VUELTA),
        Lechugator::DigitalController(CONTROLLER_1_NUMERATOR, CONTROLLER_1_DENOMINATOR),
        1),
    Lechugator::Motor(
        Lechugator::MotorPins(MOTOR_2_ENABLE, MOTOR_2_CW_PWM, MOTOR_2_CCW_PWM),
        Lechugator::EncoderPins(ENCODER_2_PULSO, ENCODER_2_VUELTA),
        Lechugator::DigitalController(CONTROLLER_2_NUMERATOR, CONTROLLER_2_DENOMINATOR),
        2),
    Lechugator::Motor(
        Lechugator::MotorPins(MOTOR_3_ENABLE, MOTOR_3_CW_PWM, MOTOR_3_CCW_PWM),
        Lechugator::EncoderPins(ENCODER_3_PULSO, ENCODER_3_VUELTA),
        Lechugator::DigitalController(CONTROLLER_3_NUMERATOR, CONTROLLER_3_DENOMINATOR),
        3),
    Lechugator::Motor(
        Lechugator::MotorPins(MOTOR_4_ENABLE, MOTOR_4_CW_PWM, MOTOR_4_CCW_PWM),
        Lechugator::EncoderPins(ENCODER_4_PULSO, ENCODER_4_VUELTA),
        Lechugator::DigitalController(CONTROLLER_4_NUMERATOR, CONTROLLER_4_DENOMINATOR),
        4)};

Lechugator::TimerMuestreo timerHandler(motors);
Lechugator::TimerEncoders timerEncoders;

Lechugator::LedsRGB ledsR(LED_RIGHT_RED, LED_RIGHT_GREEN, LED_RIGHT_BLUE);
Lechugator::LedsRGB ledsL(LED_LEFT_RED, LED_LEFT_GREEN, LED_LEFT_BLUE);

std::array<double, 4> velocidad_motores = {0, 0, 0, 0};
uint32_t delay_motores = 1 * 1000;
// std::array<double, 4> velocidad_motores;

// Comunicacion
char estado;

void setup()
{
  velocidad_motores.fill(0.09375 * 2);
  // velocidad_motores.fill(1.7647);

  Serial.begin(115200);
  Serial1.begin(115200);
  while (!Serial)
    ;
  while (!Serial1)
    ;

  timerEncoders.init();

  for (auto &&motor : motors)
  {
    motor.init(timerEncoders.getTimerRef());
  }
  timerHandler.init();

  timerEncoders.run();

  ledsR.init();
  ledsL.init();

  Serial.println();
  Serial.println();

  ledsR.prenderAzulClaro();
  ledsL.prenderAzulClaro();

  Polyfill::pinMode(STM_COM_INPUT, INPUT_PULLDOWN);
  Polyfill::pinMode(STM_COM_OUTPUT, OUTPUT);
  digitalWriteFast(STM_COM_OUTPUT, LOW);
}

void loop()
{
  if (Serial.available())
  {
    estado = Serial.read();
  }
  if (Serial1.available())
  {
    estado = Serial1.read();
  }
  if (digitalReadFast(STM_COM_INPUT))
  {
    estado = 'g';
  }

  switch (estado)
  {

  case 't':
    estado = 0;
    // Serial.println("Adelante");
    Serial1.println("Adelante");
    for (auto &&motor : motors)
    {
      motor.moveW(10);
    }

    break;
  case 'w':
    estado = 0;
    // Serial.println("Adelante");
    Serial1.println("Adelante");
    for (auto &&motor : motors)
    {
      motor.moveW(20);
    }

    break;

  case 's':
    estado = 0;
    // Serial.println("Atras");
    Serial1.println("Atras");
    for (auto &&motor : motors)
    {
      motor.moveW(-20);
    }
    break;

  case 'a':
    estado = 0;
    for (auto &&motor : motors)
    {
      motor.moveW(60);
    }
    break;

  case 'd':
    estado = 0;
    for (auto &&motor : motors)
    {
      motor.moveW(-60);
    }
    break;

  case 'q':
    estado = 0;

    // Serial.println("Stop");
    Serial1.println("Stop");

    for (auto &&motor : motors)
    {
      motor.move(0);
      motor.moveRpm(0);
    }
    break;

  case '1':
    // Serial.println("Control M1 50 RPM");
    Serial1.println("Control M1 50 RPM");
    estado = 0;
    // motors.at(0).moveRpm(50);
    motors.at(0).moveW(2.8);
    break;
  case '2':
    // Serial.println("Control M2 50 RPM");
    Serial1.println("Control M2 50 RPM");
    estado = 0;
    // motors.at(1).moveRpm(50);
    motors.at(1).moveW(2.8);
    break;
  case '3':
    // Serial.println("Control M3 50 RPM");
    Serial1.println("Control M3 50 RPM");
    estado = 0;
    // motors.at(2).moveRpm(50);
    motors.at(2).moveW(2.8);
    break;
  case '4':
    // Serial.println("Control M4 50 RPM");
    Serial1.println("Control M4 50 RPM");
    estado = 0;
    // motors.at(3).moveRpm(50);
    motors.at(3).moveW(2.8);
    break;
  case '5':
    // Serial.println("Control M1 50 RPM");
    Serial1.println("Control M1 50 RPM");
    estado = 0;
    // motors.at(0).moveRpm(50);
    motors.at(0).moveW(15);
    break;
  case '6':
    // Serial.println("Control M2 50 RPM");
    Serial1.println("Control M2 50 RPM");
    estado = 0;
    // motors.at(1).moveRpm(50);
    motors.at(1).moveW(15);
    break;
  case '7':
    // Serial.println("Control M3 50 RPM");
    Serial1.println("Control M3 50 RPM");
    estado = 0;
    // motors.at(2).moveRpm(50);
    motors.at(2).moveW(15);
    break;
  case '8':
    // Serial.println("Control M4 50 RPM");
    Serial1.println("Control M4 50 RPM");
    estado = 0;
    // motors.at(3).moveRpm(50);
    motors.at(3).moveW(15);
    break;
  case 'g':
    // Serial.println("Control M4 50 RPM");
    // Serial1.println("Mov 30 cm ");
    estado = 0;
    // motors.at(3).moveRpm(50);
    ledsR.prenderRojo();
    ledsL.prenderRojo();
    for (size_t i = 0; i < motors.size(); i++)
    {
      motors.at(i).moveW(velocidad_motores.at(i));
    }
    while (
        motors.at(0).getEncoder().getW() < velocidad_motores.at(0) &&
        motors.at(1).getEncoder().getW() < velocidad_motores.at(1) &&
        motors.at(2).getEncoder().getW() < velocidad_motores.at(2) &&
        motors.at(3).getEncoder().getW() < velocidad_motores.at(3))
      ;
    delay(delay_motores);
    for (auto &&motor : motors)
    {
      motor.moveW(0);
    }
    ledsR.prenderVerde();
    ledsL.prenderVerde();

    digitalWriteFast(STM_COM_OUTPUT, HIGH);
    delay(1000);
    digitalWriteFast(STM_COM_OUTPUT, LOW);
    break;
  default:
    // Serial.println("nada");
    // Serial1.println("nada");
    estado = 0;
    break;
  }
}
