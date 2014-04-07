#include "maindefs.h"
#include "motor_commands.h"
#include "messages.h"
#include "debug.h"

unsigned char msgtype_moto = MOTOR_COMMAND;

/**
 * Change message state for motorcontroller
 */
int msgForMotorcontroller(unsigned char* msgbuffer) {


    int length;

    switch (msgtype_moto) {
        case MOTOR_COMMAND:

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            length = 6;
            msgbuffer[0] = 0x01;
            msgbuffer[1] = 0x03;
            msgbuffer[2] = 0x61;
            msgbuffer[3] = 0xE0;
            msgbuffer[4] = 0x00;
            msgbuffer[5] = 0x81;
            msgtype_moto = STOP;
            break;

        case STOP:

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            length = 3;
            msgbuffer[0] = 0x05;
            msgbuffer[1] = 0;
            msgbuffer[2] = 0;

            break;

        case ALIGNMENT:

            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);
            DEBUG_ON(MOTOR_DBG);
            DEBUG_OFF(MOTOR_DBG);

            length = 3;
            msgbuffer[0] = 0x08;
            msgbuffer[1] = 1;
            msgbuffer[2] = 0;
            msgbuffer[3] = 0;
            break;

        default:
            break;
    }
    return length;
}
