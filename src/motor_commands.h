/* 
 * File:   motor_commands.h
 * Author: ECE4534
 *
 * Created on March 25, 2014, 1:54 AM
 */

#ifndef MOTOR_COMMANDS_H
#define	MOTOR_COMMANDS_H

// Msgtype
#define MOTOR_COMMAND 0x01
#define STOP 0x05
#define MOTOR_ENCODER 0x13
#define ALIGNMENT 0x08


// Alignment
#define ALIGN_L 0
#define ALIGN_R 1

// Motor Commands
// Direction
#define FWD 1
#define REV 2
#define LEFT 3
#define RIGHT 4

// Forward Commands
#define FWD_1 1
#define FWD_2 2
#define FWD_3 3
#define FWD_4 4

// Reverse Commands
#define REV_1 1
#define REV_2 2
#define REV_3 3
#define REV_4 4

#define LEFT_15 0x01
#define LEFT_30 0x02
#define LEFT_45 0x03
#define LEFT_60 0x04
#define LEFT_75 0x05
#define LEFT_90 0x06


#define RIGHT_15 0x07
#define RIGHT_30 0x08
#define RIGHT_45 0x09
#define RIGHT_60 0x0A
#define RIGHT_75 0x0B
#define RIGHT_90 0x0C


// Calculations for motors:
// Diameter of Wheel is d = 12.04cm
// Circumference is C = pi*d = 3.14*12.04 = 37.81cm
// Distance Traveled = (Encoder Ticks / 360) * Circumference
int distanceTraveledByMotor0 = 0, distanceTraveledByMotor1 = 0;
const int circumference = 38;

// Motor Encoder Max ticks
int maxTickZero = 60;
int maxTickOne = 60;
// Motor Encoder counters
int timer0Counter, timer1Counter;
int ticks0Counter = 61, ticks1Counter = 61, ticks_flag = 0;

unsigned char motorEncoderBuffer[5];

void motorEncoder(unsigned char*);
void forward(unsigned char*);
void reverse(unsigned char*);
void turnLeft(unsigned char*);
void turnRight(unsigned char*);
void stop(unsigned char*);
void motorEncoder(unsigned char*);
void alignment(unsigned char* msgbuffer);
int msgForMotorcontroller(int msgtype_moto, unsigned char* msgbuffer);
#endif