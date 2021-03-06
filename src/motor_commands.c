#include "maindefs.h"
#include "motor_commands.h"
#include "messages.h"
#include "debug.h"
#include "my_uart.h"
#include "stop_sensor.h"
/**
 * Changes message state for motorcontroller
 */
int msgForMotorcontroller(int msgtype_moto, unsigned char* msgbuffer) {

    int length;
    ticks_flag = 0;

    currentMsgtype = msgtype_moto;

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

                stopFlag = 1;

                DEBUG_ON(MOTOR_DBG);
                DEBUG_OFF(MOTOR_DBG);
                turnLeft(msgbuffer);
            } else if (msgbuffer[2] == RIGHT) {

                DEBUG_ON(MOTOR_DBG);
                DEBUG_OFF(MOTOR_DBG);
                if (msgbuffer[4] != 0x07) {
                    if (postRight) {
                        postRight = 2;
                        turnRight(msgbuffer);
                    } else {
                        postRight = 1;
                        forwardAdjusted(msgbuffer);
                    }
                } else {
                    turnRight(msgbuffer);
                }
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
    maxTickZero = 5;
    maxTickOne = 5;
    postAlignFlag = 1;

    switch (msgbuffer[2]) {
        case ALIGN_L:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            msgbuffer[0] = 0x55; // motor 0 - fwd
            msgbuffer[1] = 0xA5; // motor 1 - rev
            break;

        case ALIGN_R:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            msgbuffer[0] = 0x1E; // motor 0  - rev
            msgbuffer[1] = 0xC8; // motor 1  - fwd
            break;

        default:
            break;
    }
}

/**
 * Formats the motor encoder message to send to the ARM.
 * @param msgbuffer
 *      msg buffer containing the motor encoder message.
 */
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
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            msgbuffer[0] = 0x48; // 72
            msgbuffer[1] = 0xC8; // 200
            break;
        case FWD_2:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            msgbuffer[0] = 0x48;
            msgbuffer[1] = 0xC8;
            break;
        case FWD_3:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            msgbuffer[0] = 0x48;
            msgbuffer[1] = 0xC8;
            break;
        case FWD_4:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            msgbuffer[0] = 0x48;
            msgbuffer[1] = 0xC8;
            break;
        default:
            break;
    }
}

void forwardAdjusted(unsigned char* msgbuffer) {
    maxTickZero = 40;
    maxTickOne = 40;
    ticks0Counter = 0;
    ticks1Counter = 0;
    ticks_flag = 1;

    DEBUG_ON(MOTOR_DBG);
    DEBUG_OFF(MOTOR_DBG);
    // Forward 1
    msgbuffer[0] = 0x51;
    msgbuffer[1] = 0xCF;
}

void reverse(unsigned char* msgbuffer) {
    maxTickZero = 60;
    maxTickOne = 60;
    ticks0Counter = 0;
    ticks1Counter = 0;
    ticks_flag = 1;

    switch (msgbuffer[3]) {
        case REV_1:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            msgbuffer[0] = 0x20;
            msgbuffer[1] = 0xA0;
            break;
        case REV_2:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            msgbuffer[0] = 0x20;
            msgbuffer[1] = 0xB0;
            break;
        case REV_3:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            msgbuffer[0] = 0x19;
            msgbuffer[1] = 0xA0;
            break;
        case REV_4:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
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
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 15;
            maxTickOne = 15;
            msgbuffer[0] = 0x5F;
            msgbuffer[1] = 0xA0;
            break;

        case LEFT_30:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 20;
            maxTickOne = 20;
            msgbuffer[0] = 0x19;
            msgbuffer[1] = 0xDE;
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
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 35;
            maxTickOne = 35;
            msgbuffer[0] = 0x19;
            msgbuffer[1] = 0xDE;
            break;

        case LEFT_75:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 55;
            maxTickOne = 55;
            msgbuffer[0] = 0x19;
            msgbuffer[1] = 0xDE;
            break;

        case LEFT_90:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 72;
            maxTickOne = 72;
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
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 15;
            maxTickOne = 15;
            msgbuffer[0] = 0x19;
            msgbuffer[1] = 0xDE;
            break;

        case RIGHT_30:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 30;
            maxTickOne = 30;
            msgbuffer[0] = 0x5F;
            msgbuffer[1] = 0xA0;
            break;

        case RIGHT_45:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 45;
            maxTickOne = 45;
            msgbuffer[0] = 0x5F;
            msgbuffer[1] = 0xA0;
            break;

        case RIGHT_60:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 60;
            maxTickOne = 60;
            msgbuffer[0] = 0x5F;
            msgbuffer[1] = 0xA0;
            break;

        case RIGHT_75:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 75;
            maxTickOne = 75;
            msgbuffer[0] = 0x5F;
            msgbuffer[1] = 0xA0;
            break;

        case RIGHT_90:
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            maxTickZero = 80;
            maxTickOne = 90;
            msgbuffer[0] = 0x71;
            msgbuffer[1] = 0x9E;
            break;

        default:
            break;
    }
}