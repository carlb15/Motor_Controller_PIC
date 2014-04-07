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

    // Flips on each wheel rotation
    if (timer0Counter >= maxTickZero) {
        DEBUG_ON(TMR0_DBG);
        DEBUG_OFF(TMR0_DBG);
    }




    // Stops wheels after set number of ticks
    //    if (timer0Counter >= maxTickZero) {
    //        WriteUSART(0x40);
    //    }
}

// A function called by the interrupt handler
// This one does the action I wanted for this program on a timer1 interrupt

void timer1_int_handler() {
    // Encoder count for motor 1.
    timer1Counter++;
    // Reset the timer
    WriteTimer1(0xFFCF);

    // Flips on each wheel rotation
    if (timer1Counter >= maxTickOne) {
        DEBUG_ON(TMR1_DBG);
        DEBUG_OFF(TMR1_DBG);
    }



    //        // Stops wheels after set number of ticks
    //    if (timer1Counter >= maxTickOne) {
    //        //Stop the motor
    //        WriteUSART(0xC0);
    //    }
}