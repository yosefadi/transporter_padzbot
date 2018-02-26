/* Transporter mikrokontroller
 *  Written by Yosef Adi Sulistyo
 *  1/1/2018
 *  
 *  Beberapa kode diambil dari source code
 *  PADZBOT OS
 *  
 */

// compiler flag
#define DEBUG_EN 1

// padzbot header
#include "padzbot_pcfg.h"

// set padzbot variant
// change me everytime you compile this for another version!
#define LINEFOLLOWER 0

#define PADZBOT_DUE 0
#define PADZBOT_MEGA 0
#define PADZBOT_UNO 1

// include some header needed for padzbot os v1
#include <LiquidCrystal.h>
#if defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1
#include <Tlc5940.h>
#include <tlc_config.h>
#elif defined(PADZBOT_DUE) && PADZBOT_DUE == 1
#include <due_tlc5940.h>
#include <due_tlc5940_config.h>
#endif

// add by yosefadi: 1/1/2018
#if defined(LINEFOLLOWER) && LINEFOLLOWER == 0
#include <Servo.h> 
#include <Tlc5940.h>
#include <tlc_config.h>
#include <PS2X_lib.h>

Servo transervo1;
Servo transervo2;
#endif

// lcd port config!
//LiquidCrystal padz_lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// initialize public variable
#if defined(PADZBOT_UNO) && PADZBOT_UNO == 1
const char* model = "uno"; //please fix me!
#elif defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1
const char* model = "mega"; //please fix me!
#else
const char* model = "due"; //please fix me!
#endif

#if defined(LINEFOLLOWER) && LINEFOLLOWER == 0
int error;
byte type;
byte vibrate;
int servpos;
#endif

unsigned char lpwm;
unsigned char rpwm;

#if defined(LINEFOLLOWER) && LINEFOLLOWER == 1
unsigned char vCounter;
unsigned char vFreeLeft;
unsigned char vFreeRight;
#if defined(PADZBOT_UNO) && PADZBOT_UNO == 1
const int ADC_SENSOR[6] = {L1_SENSOR, L2_SENSOR, FRONT1_SENSOR, FRONT2_SENSOR, R1_SENSOR, R2_SENSOR};
#elif defined(PADZBOT_DUE) && PADZBOT_DUE == 1
const int ADC_SENSOR[12] = {L1_SENSOR, L2_SENSOR, L3_SENSOR, L4_SENSOR, FRONT1_SENSOR, FRONT2_SENSOR, FRONT3_SENSOR, FRONT4_SENSOR, R1_SENSOR, R2_SENSOR, R3_SENSOR, R4_SENSOR};
#elif defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1
const int ADC_SENSOR[14] = {L1_SENSOR, L2_SENSOR, L3_SENSOR, L4_SENSOR, L5_SENSOR, FRONT1_SENSOR, FRONT2_SENSOR, FRONT3_SENSOR, FRONT4_SENSOR, R1_SENSOR, R2_SENSOR, R3_SENSOR, R4_SENSOR, R5_SENSOR};
#endif
#endif


#if defined(DEBUG_EN) && DEBUG_EN == 1
void init_debug() {
  Serial.begin(9600);
  Serial.print("Serial pin enabled!");
  delay(100);
}
#endif

void init_motor() {
  pinMode(MTR_LEFT_FWD, OUTPUT);
  pinMode(MTR_RIGHT_FWD, OUTPUT);
    // check hw: motor
  digitalWrite(MTR_LEFT_FWD, HIGH);
  digitalWrite(MTR_RIGHT_FWD, HIGH);
  delay(500);
  digitalWrite(MTR_LEFT_FWD, LOW);
  digitalWrite(MTR_RIGHT_FWD, LOW);
#if (defined(PADZBOT_DUE) && PADZBOT_DUE == 1) || (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1)
  pinMode(MTR_LEFT_BWD, OUTPUT);
  pinMode(MTR_RIGHT_BWD, OUTPUT);
    // check hw: motor
  digitalWrite(MTR_LEFT_BWD, HIGH);
  digitalWrite(MTR_RIGHT_BWD, HIGH);
  delay(500);
  digitalWrite(MTR_LEFT_BWD, LOW);
  digitalWrite(MTR_RIGHT_BWD, LOW);
#endif
}

void setMotor(unsigned char lpwm, unsigned char rpwm) {
  if ( lpwm > 0 ) {
#if (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1) || (defined(PADZBOT_DUE) && PADZBOT_DUE == 1)
    digitalWrite(MTR_LEFT_BWD, LOW);
#endif
    analogWrite(MTR_LEFT_FWD, lpwm);
  } else if ( lpwm < 0 )  {
    digitalWrite(MTR_LEFT_FWD, LOW);
#if (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1) || (defined(PADZBOT_DUE) && PADZBOT_DUE == 1)
    analogWrite(MTR_LEFT_BWD, -lpwm);
#endif
  } else if ( lpwm == 0 ) {
    digitalWrite(MTR_LEFT_FWD, LOW);
#if (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1) || (defined(PADZBOT_DUE) && PADZBOT_DUE == 1)
    digitalWrite(MTR_LEFT_BWD, LOW);
#endif
  }

  if ( rpwm > 0 ) {
#if (defined(PADZBOT_MEGA)  && PADZBOT_MEGA == 1) || (defined(PADZBOT_DUE) && PADZBOT_DUE == 1)
    digitalWrite(MTR_RIGHT_BWD, LOW);
#endif
    analogWrite(MTR_RIGHT_FWD, rpwm);
  } else if ( rpwm < 0 ) {
    digitalWrite(MTR_RIGHT_FWD, LOW);
#if (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1) || (defined(PADZBOT_DUE) && PADZBOT_DUE == 1)
    analogWrite(MTR_RIGHT_BWD, -rpwm);
#endif
  } else if ( rpwm == 0 ) {
    digitalWrite(MTR_RIGHT_FWD, LOW);
#if (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1) || (defined(PADZBOT_DUE) && PADZBOT_DUE == 1)
    digitalWrite(MTR_RIGHT_BWD, LOW);
#endif
  }
}

void init_servo() {
  transervo1.attach(TRANS_SERVO1);
  transervo2.attach(TRANS_SERVO2);
}

void set_servo(unsigned char psxtrans1, unsigned char psxtrans2) {
  //float left_gripper = 90 + psxtrans;
  //float right_gripper = 90 - psxtrans;

  float servoval1 = 90 + psxtrans1;
  float servoval2 = 90 + psxtrans2;
  
  //transervo1.write(left_gripper);
  //transervo2.write(right_gripper);

  transervo1.write(servoval1);
  transervo2.write(servoval2);
}

void init_button() {
  error = ps2x.config_gamepad(PSX_CLK, PSX_CMD, PSX_ATT, PSX_DATA, true, true);
  type = ps2x.readType();
}

void read_button() {
  ps2x.read_gamepad(false, vibrate);

  //float psxval = ps2x.Analog(PSS_LX) / 255 * 90

  if(ps2x.ButtonPressed(PSB_BLUE)) {
    set_servo(90,0);
  } else if(ps2x.ButtonReleased(PSB_BLUE)) {
    set_servo(0,0)
  }

  if(ps2x.ButtonPressed(PSB_RED))  {
    set_servo(0,90);
  } else if(ps2x.ButtonReleased(PSB_RED)) {
    set_servo(0,0);
  }

  unsigned char xAxisAnalog = ps2x.Analog(PSS_LX);
  unsigned char yAxisAnalog = ps2x.Analog(PSS_LY);
  
  if(yAxisAnalog > 128 && xAxisAnalog = 128) {
    float pwm = (ps2x.Analog(PSS_LY) - 128) / 128 * 255
    setMotor(pwm,pwm);
  } else if (yAxisAnalog = 128 && xAxisAnalog = 128) {
    setMotor(0,0);
  } else if (yAxisAnalog < 128 && xAxisAnalog = 128) {
    float pwm = ps2x.Analog(PSS_LY) / 128 * 255
    setMotor(-pwm,-pwm);
  } else if (yAxisAnalog > 128 && xAxisAnalog > 128) {
    float leftnewpwm = ((yAxisAnalog - 128) / 128 * 255) + ((xAxisAnalog - 128) / 128 * 255);
    float rightnewpwm = ((yAxisAnalog - 128) / 128 * 255)
    setMotor(leftnewpwm, rightnewpwm);
  } else if (yAxisAnalog > 128 && xAxisAnalog < 128) {
    float leftnewpwm = ((yAxisAnalog - 128) / 128 * 255)
    float rightnewpwm = ((yAxisAnalog - 128) / 128 * 255) + (xAxisAnalog/ 128 * 255);
    setMotor(leftnewpwm, rightnewpwm);
  } else if (yAxisAnalog  < 128 && xAxisAnalog > 128) {
    float leftnewpwm = ((yAxisAnalog) / 128 * 255)  + ((xAxisAnalog - 128)/ 128 * 255);
    float rightnewpwm = ((yAxisAnalog) / 128 * 255)
    setMotor(-leftnewpwm, -rightnewpwm);
  } else if (yAxisAnalog  < 128 && xAxisAnalog > 128) {
    float leftnewpwm = ((yAxisAnalog - 128) / 128 * 255)  
    float rightnewpwm = ((yAxisAnalog - 128) / 128 * 255) + (xAxisAnalog/ 128 * 255);
    setMotor(-leftnewpwm, -rightnewpwm);
  }
}

void setup() {
  // put your setup code here, to run once:
#if defined(DEBUG_EN) && DEBUG_EN == 1
  init_debug();
#endif
  init_motor();
  init_servo();
  init_button();
}

void loop() {
  // put your main code here, to run repeatedly:
  //bool robotstat = ps2x.Button(PSB_START);

  read_button();
}
