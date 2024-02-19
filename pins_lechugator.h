// ? *************** SERIAL ***************
// ? ******* PINS
#define EXTRA_SERIAL_RX PC_7
#define EXTRA_SERIAL_TX PC_6



// ? *************** MOTORS ***************

// ? *********** MOTOR 1 ***********
// ? ******* PINS
#define MOTOR_1_ENABLE PA_4
#define MOTOR_1_CW_PWM PC_8
#define MOTOR_1_CCW_PWM PB_9
// ? *********** MOTOR 2 ***********
// ? ******* PINS
#define MOTOR_2_ENABLE PA_13
#define MOTOR_2_CW_PWM PA_6
#define MOTOR_2_CCW_PWM PA_5
// ? *********** MOTOR 3 ***********
// ? ******* PINS
#define MOTOR_3_ENABLE PB_2
#define MOTOR_3_CW_PWM PB_7
#define MOTOR_3_CCW_PWM PB_8
// ? *********** MOTOR 4 ***********
// ? ******* PINS
#define MOTOR_4_ENABLE PB_4
#define MOTOR_4_CW_PWM PB_5
#define MOTOR_4_CCW_PWM PB_6



// ? *************** ENCODERS ***************

// ? *********** ENCODER 1 ***********
// ? ******* PINS
#define ENCODER_1_PULSO PA_8
#define ENCODER_1_VUELTA PC_0
// ? *********** ENCODER 2 ***********
// ? ******* PINS
#define ENCODER_2_PULSO PA_9
#define ENCODER_2_VUELTA PC_3
// ? *********** ENCODER 3 ***********
// ? ******* PINS
#define ENCODER_3_PULSO PA_10
#define ENCODER_3_VUELTA PB_13
// ? *********** ENCODER 4 ***********
// ? ******* PINS
#define ENCODER_4_PULSO PA_11
#define ENCODER_4_VUELTA PB_12



// ? *************** CONTROLLER EXAMPLE ***************
// u         q1 + q2 * z^-1
// ------ = ------------------- 
// error     1 - z^-1

// u = u1 + q1 * e + q2 * e1

// ? *************** CONTROLLERS ***************

// ? *********** CONTROLLER 1 ***********
// ? ******* GAINS
#define CONTROLLER_1_NUMERATOR {5.092, -5.059}
#define CONTROLLER_1_DENOMINATOR {1.0, -1.0}
// ? *********** CONTROLLER 2 ***********
// ? ******* GAINS
#define CONTROLLER_2_NUMERATOR {4.7737, -4.7415}
#define CONTROLLER_2_DENOMINATOR {1.0, -1.0}
// ? *********** CONTROLLER 3 ***********
// ? ******* GAINS
#define CONTROLLER_3_NUMERATOR {4.584, -4.5513}
#define CONTROLLER_3_DENOMINATOR {1.0, -1.0}
// ? *********** CONTROLLER 4 ***********
// ? ******* GAINS
// #define CONTROLLER_4_NUMERATOR {7.7996, -7.7598}
#define CONTROLLER_4_NUMERATOR {4.584, -4.5513}
// #define CONTROLLER_4_NUMERATOR {10.435, -10.388}
#define CONTROLLER_4_DENOMINATOR {1.0, -1.0}
// #define CONTROLLER_4_NUMERATOR {13580.0, -27039.0, 13459.0}
// #define CONTROLLER_4_DENOMINATOR {1.0, 0.5521, -0.4479}



// ? *************** LEDS ***************
// Lechugator::LedsRGB ledsR(PC_5, PC_6, PC_7);
// Lechugator::LedsRGB ledsL(PC_8, PC_9, PC_10);

// ? *********** LED RIGHT ***********
// ? ******* PINS
#define LED_RIGHT_RED PC_4
#define LED_RIGHT_GREEN PC_2
#define LED_RIGHT_BLUE PC_5
// ? *********** LED LEFT ***********
// ? ******* PINS
#define LED_LEFT_RED PC_10
#define LED_LEFT_GREEN PC_8
#define LED_LEFT_BLUE PC_11


// ? *************** LEDS ***************
// Lechugator::LedsRGB ledsR(PC_5, PC_6, PC_7);
// Lechugator::LedsRGB ledsL(PC_8, PC_9, PC_10);

// ? *********** LED RIGHT ***********
// ? ******* PINS
#define STM_COM_INPUT PC_12
#define STM_COM_OUTPUT PC_1


