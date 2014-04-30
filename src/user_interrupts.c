// This is where the "user" interrupts handlers should go
// The *must* be declared in "user_interrupts.h"

#include "maindefs.h"
#ifndef __XC8
#include <timers.h>
#else
#include <plib/timers.h>
#endif
#include "user_interrupts.h"
#include "messages.h"
#include "debug.h"
#include "timer0_thread.h"
#include "motor_commands.h"

// A function called by the interrupt handler
// This one does the action I wanted for this program on a timer0 interrupt

void timer0_int_handler() {
    // Encoder count for motor 0.
    timer0Counter++;
    // Reset the timer
    WriteTimer0(0xCF);

    DEBUG_ON(TMR0_DBG);
    DEBUG_OFF(TMR0_DBG);

    if (ticks_flag) {
        // Reverse counter to prevent it from going a set distance.
        ticks0Counter++;
        // Going thru right hand turn
        if (ticks0Counter >= maxTickZero && postRight == 1) {
            postRight = 2;
            WriteUSART(0x00);
            // Turn right 90
            motorBuffer[0] = 0x01;
            motorBuffer[1] = 0x03;
            motorBuffer[2] = 0x04;
            motorBuffer[3] = 0x01;
            motorBuffer[4] = 0x0C;
            motorBuffer[5] = 0x09;

            ToMainHigh_sendmsg(MOTORLEN, MSGT_I2C_DATA, (void *) motorBuffer);
        } else if (ticks0Counter >= maxTickZero && postRight == 2) {
            // Move forward after right turn
            postRight = 0;

            motorBuffer[0] = 0x01;
            motorBuffer[1] = 0x03;
            motorBuffer[2] = 0x01;
            motorBuffer[3] = 0x01;
            motorBuffer[4] = 0x00;
            motorBuffer[5] = 0x00;

            ToMainHigh_sendmsg(MOTORLEN, MSGT_I2C_DATA, (void *) motorBuffer);
        } else if (ticks0Counter >= maxTickZero && postAlignFlag) {
            postAlignFlag = 0;
            motorBuffer[0] = 0x01;
            motorBuffer[1] = 0x03;
            motorBuffer[2] = 0x01;
            motorBuffer[3] = 0x01;
            motorBuffer[4] = 0x00;
            motorBuffer[5] = 0x00;

            ToMainHigh_sendmsg(MOTORLEN, MSGT_I2C_DATA, (void *) motorBuffer);
        } else if (ticks0Counter >= maxTickZero) {
            //Stops wheels after set number of ticks
            WriteUSART(0x00);
        }
    }
}


// A function called by the interrupt handler
// This one does the action I wanted for this program on a timer1 interrupt

void timer1_int_handler() {
    // Encoder count for motor 1.
    timer1Counter++;
    // Reset the timer
    WriteTimer1(0xFFCF);

    DEBUG_ON(TMR1_DBG);
    DEBUG_OFF(TMR1_DBG);

    if (ticks_flag) {
        // Reverse counter to prevent it from going a set distance.
        ticks1Counter++;
        if (ticks1Counter >= maxTickOne && postRight == 1) {
            postRight = 2;
            // Turn right 90
            motorBuffer[0] = 0x01;
            motorBuffer[1] = 0x03;
            motorBuffer[2] = 0x04;
            motorBuffer[3] = 0x01;
            motorBuffer[4] = 0x0C;
            motorBuffer[5] = 0x09;

            ToMainHigh_sendmsg(MOTORLEN, MSGT_I2C_DATA, (void *) motorBuffer);
        } else if (ticks1Counter >= maxTickOne && postRight == 2) {
            // Move forward after right turn
            postRight = 0;

            motorBuffer[0] = 0x01;
            motorBuffer[1] = 0x03;
            motorBuffer[2] = 0x01;
            motorBuffer[3] = 0x01;
            motorBuffer[4] = 0x00;
            motorBuffer[5] = 0x00;

            ToMainHigh_sendmsg(MOTORLEN, MSGT_I2C_DATA, (void *) motorBuffer);
        } else if (ticks1Counter >= maxTickOne && postAlignFlag) {
            postAlignFlag = 0;
            motorBuffer[0] = 0x01;
            motorBuffer[1] = 0x03;
            motorBuffer[2] = 0x01;
            motorBuffer[3] = 0x01;
            motorBuffer[4] = 0x00;
            motorBuffer[5] = 0x00;

            ToMainHigh_sendmsg(MOTORLEN, MSGT_I2C_DATA, (void *) motorBuffer);
        } else if (ticks1Counter >= maxTickOne) {
            // Stops wheels after set number of ticks
            WriteUSART(0x00);
        }
    }
}