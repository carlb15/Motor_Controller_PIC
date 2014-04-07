#include "maindefs.h"
#include <stdio.h>
#include "uart_thread.h"
#include "my_uart.h"
#include "user_interrupts.h"
#include "motor_commands.h"
#include "debug.h"
#include "timer1_thread.h"
// This is a "logical" thread that processes messages from the UART
// It is not a "real" thread because there is only the single main thread
// of execution on the PIC because we are not using an RTOS.

int uart_lthread(uart_thread_struct *uptr, int msgtype, int length, unsigned char *msgbuffer) {
    if (msgtype == MSGT_OVERRUN) {
        // TODO handle when buffer overruns.
    } else if (msgtype == MSGT_I2C_DATA) {
        // Send motor command to motorcontroller
        if (msgbuffer[0] != MOTOR_ENCODER) {
            DEBUG_ON(UART_THREAD_DBG);
            DEBUG_OFF(UART_THREAD_DBG);
            // Send UART command to motorcontroller
            uart_retrieve_buffer(length, msgbuffer);
            // Set UART TXF interrupt flag
            PIE1bits.TX1IE = 0x1;
        } else {
            DEBUG_ON(UART_THREAD_DBG);
            DEBUG_OFF(UART_THREAD_DBG);
            DEBUG_ON(UART_THREAD_DBG);
            DEBUG_OFF(UART_THREAD_DBG);
            // Send Encoder Data to Master
            motorEncoderBuffer[0] = 0x07;
            motorEncoderBuffer[1] = 0x02;
            motorEncoderBuffer[2] = timer0Counter;
            motorEncoderBuffer[3] = timer1Counter;
            motorEncoderBuffer[4] = timer0Counter ^ timer1Counter;
            length = 5;
            start_i2c_slave_reply(length, motorEncoderBuffer);
            // Reset Encoder counts
            timer0Counter = 0;
            timer1Counter = 0;
        }
    }
}