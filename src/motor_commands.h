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

int fwd_state = 1;
int rev_state = 1;
int left_state = 1;
int right_state = 1;

// Motor Encoder Max ticks
int maxTickZero = 60;
int maxTickOne = 60;
// Motor Encoder counters
int timer0Counter, timer1Counter;
unsigned char motorEncoderBuffer[5];

void forward();
void reverse();
void turnLeft();
void turnRight();
void stop();
void motorEncoder();
void alignment();

int msgForMotorcontroller(unsigned char* msgbuffer);
#endif