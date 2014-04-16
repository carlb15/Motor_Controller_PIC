#include "maindefs.h"
#include "motor_commands.h"
#include "messages.h"
#include "debug.h"
#include "my_uart.h"

/**
 * Change message state for motorcontroller
 */
int msgForMotorcontroller(int msgtype_moto, unsigned char* msgbuffer) {

    int length;
    ticks_flag = 0;

    switch (msgtype_moto) {
        case MOTOR_COMMAND:
            // Motor commands direction.
            if (msgbuffer[2] == FWD) {
                DEBUG_ON(MOTOR_DBG);
                DEBUG_OFF(MOTOR_DBG);
                forward(msgbuffer);
            } else if (msgbuffer[2] == REV) {
                DEBUG_ON(MOTOR_DBG);
                DEBUG_OFF(MOTOR_DBG);
                DEBUG_ON(MOTOR_DBG);
                DEBUG_OFF(MOTOR_DBG);
                reverse(msgbuffer);
            } else if (msgbuffer[2] == LEFT) {
                DEBUG_ON(MOTOR_DBG);
                DEBUG_OFF(MOTOR_DBG);
                turnLeft(msgbuffer);
            } else if (msgbuffer[2] == RIGHT) {
                DEBUG_ON(MOTOR_DBG);
                DEBUG_OFF(MOTOR_DBG);
                turnRight(msgbuffer);
            }

            length = 2;
            break;

        case STOP:

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            msgbuffer[0] = 0x0;
            msgbuffer[1] = 0x0;
            length = 2;
            break;

        case ALIGNMENT:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            length = 2;
            alignment(msgbuffer);
            break;
        case MOTOR_ENCODER:

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            length = 5;
            motorEncoder(msgbuffer);
            break;
        default:
            break;
    }
    return length;
}

void alignment(unsigned char* msgbuffer) {
    // Setup counters and flag for align
    ticks_flag = 1;
    ticks0Counter = 0;
    ticks1Counter = 0;
    maxTickZero = 3;
    maxTickOne = 3;

    switch (msgbuffer[2]) {
        case ALIGN_L:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            msgbuffer[0] = 0x5F;
            msgbuffer[1] = 0xA0;
            break;

        case ALIGN_R:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            msgbuffer[0] = 0x19;
            msgbuffer[1] = 0xDE;
            break;

        default:
            break;
    }
}

void motorEncoder(unsigned char* msgbuffer) {
    // Calculate the distance travled since last encoder request in centimeters.
    distanceTraveledByMotor0 = (timer0Counter / 360) * circumference;
    distanceTraveledByMotor1 = (timer1Counter / 360) * circumference;

    // Setup message to send to Master PIC via i2c.
    msgbuffer[0] = 0x07;
    msgbuffer[1] = 0x02;
    msgbuffer[2] = distanceTraveledByMotor0;
    msgbuffer[3] = distanceTraveledByMotor1;
    msgbuffer[4] = distanceTraveledByMotor0 ^ distanceTraveledByMotor1;

    // Reset encoder counters.
    timer0Counter = 0;
    timer1Counter = 0;
}

void forward(unsigned char* msgbuffer) {
    ticks_flag = 0;

    switch (msgbuffer[3]) {

        case FWD_1:
            msgbuffer[0] = 0x51;
            msgbuffer[1] = 0xCF;
            break;
        case FWD_2:
            msgbuffer[0] = 0x61;
            msgbuffer[1] = 0xE0;
            break;
        case FWD_3:
            msgbuffer[0] = 0x71;
            msgbuffer[1] = 0xF0;
            break;
        case FWD_4:
            msgbuffer[0] = 0x7F;
            msgbuffer[1] = 0xFF;
            break;
        default:
            break;
    }
}

void reverse(unsigned char* msgbuffer) {
    maxTickZero = 60;
    maxTickOne = 60;
    ticks0Counter = 0;
    ticks1Counter = 0;
    ticks_flag = 1;

    switch (msgbuffer[3]) {
        case REV_1:
            msgbuffer[0] = 0x20;
            msgbuffer[1] = 0xA0;
            break;
        case REV_2:
            msgbuffer[0] = 0x20;
            msgbuffer[1] = 0xB0;
            break;
        case REV_3:
            msgbuffer[0] = 0x19;
            msgbuffer[1] = 0xA0;
            break;
        case REV_4:
            msgbuffer[0] = 0x0F;
            msgbuffer[1] = 0x90;
            break;
        default:
            break;
    }
}

void turnLeft(unsigned char* msgbuffer) {
    ticks_flag = 1;
    ticks0Counter = 0;
    ticks1Counter = 0;

    switch (msgbuffer[4]) {
        case LEFT_15:
            break;

        case LEFT_30:
            break;

        case LEFT_45:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 30;
            maxTickOne = 30;
            msgbuffer[0] = 0x19;
            msgbuffer[1] = 0xDE;
            break;

        case LEFT_60:
            break;

        case LEFT_75:
            break;

        case LEFT_90:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 55; // 60
            maxTickOne = 55; // 60
            msgbuffer[0] = 0x19;
            msgbuffer[1] = 0xDE;
            break;

        default:
            break;
    }
}

void turnRight(unsigned char* msgbuffer) {
    ticks_flag = 1;
    ticks0Counter = 0;
    ticks1Counter = 0;

    switch (msgbuffer[4]) {
        case RIGHT_15:
            break;

        case RIGHT_30:
            break;

        case RIGHT_45:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 30;
            maxTickOne = 30;
            msgbuffer[0] = 0x5F;
            msgbuffer[1] = 0xA0;
            break;

        case RIGHT_60:
            break;

        case RIGHT_75:
            break;

        case RIGHT_90:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 60;
            maxTickOne = 60;
            msgbuffer[0] = 0x5F;
            msgbuffer[1] = 0xA0;
            break;

        default:
            break;
    }
}