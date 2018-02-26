/* 
 * Copyright (c) 2017 - 2018. Padmanaba Robotik Team.
 * All right reserved.
 * 
 * Author: Yosef Adi Sulistyo
 * This is the main code for PadzBot minimum system
 * Written for Arduino Due, Arduino Mega, and Arduino Uno
 * 
 * Make sure: You use the proper arduino shield,
 * Arduino Due only operate at 3V3
 * Arduino Mega and Uno can tolerate up to 5V
 * 
 * 12/31/2017
 * 
 */

// portconfig

// initialize sensor analog port
//front sensor
  #define FRONT1_SENSOR A0
  #define FRONT2_SENSOR A1
#if (defined(PADZBOT_DUE) && PADZBOT_DUE == 1) || (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1)
  #define FRONT3_SENSOR A6 
  #define FRONT4_SENSOR A7
#endif
// left sensor
  #define L1_SENSOR A2
  #define L2_SENSOR A3
#if (defined(PADZBOT_DUE) && PADZBOT_DUE == 1) || (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1)
  #define L3_SENSOR A8
  #define L4_SENSOR A9
#endif
#if defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1
  #define L5_SENSOR A12
#endif
// right sensor
  #define R1_SENSOR A4
  #define R2_SENSOR A5
#if (defined(PADZBOT_DUE) && PADZBOT_DUE == 1) || (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1)
  #define R3_SENSOR A10
  #define R4_SENSOR A11
#endif
#if defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1
  #define R5_SENSOR A13
#endif

// port config
// dcfg: LCD
#if (defined(PADZBOT_DUE) && PADZBOT_DUE == 1) || (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1)
 #define LCD_RW 48
 #define LCD_RS 46
 #define LCD_EN 44
 #define LCD_D4 42
 #define LCD_D5 40
 #define LCD_D6 38
 #define LCD_D7 36
 #define LCD_AGATE 34
/* #elif defined(PADZBOT_UNO) && PADZBOT_UNO == 1
 * #define LCD_RS 2
 * #define LCD_EN 3
 * #define LCD_D4 4
 * #define LCD_D5 5
 * #define LCD_D6 6
 * #define LCD_D7 7
 */
#endif

// dcfg: button
#if defined(PADZBOT_UNO) && PADZBOT_UNO == 1
#if defined(LINEFOLLOWER) && LINEFOLLOWER == 1
  #define BUTTON_EXIT 8
  #define BUTTON_MIN 11
  #define BUTTON_PLUS 12
  #define BUTTON_NEXT 13
#else
  #define PSX_DATA 8
  #define PSX_CMD 11
  #define PSX_ATT 12
  #define PSX_CLK 13
#elif (defined(PADZBOT_DUE) && PADZBOT_DUE == 1) || (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1)
  #define BUTTON_EXIT 53
  #define BUTTON_MIN 51
  #define BUTTON_PLUS 49
  #define BUTTON_BACK 47
  #define BUTTON_NEXT 45
  #define BUTTON_SCURSOR 43
#endif

// dcfg: motor
#if defined(PADZBOT_UNO) && PADZBOT_UNO == 1
  #define MTR_LEFT_FWD 9
  #define MTR_RIGHT_FWD 10
#elif (defined(PADZBOT_DUE) && PADZBOT_DUE == 1) || (defined(PADZBOT_MEGA) && PADZBOT_MEGA == 1)
  #define MTR_LEFT_FWD 2
  #define MTR_RIGHT_FWD 3
  #define MTR_LEFT_BWD 4
  #define MTR_RIGHT_BWD 5
#endif

#if defined(LINEFOLLOWER) && LINEFOLLOWER == 0
  #define TRANS_SERVO1 2
  #define TRANS_SERVO2 3
#endif
