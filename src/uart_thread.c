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
            // Execute main command.
            length = msgForMotorcontroller(msgbuffer[0], msgbuffer);
            // Send UART command to motorcontroller
            if (uart_retrieve_buffer(length, msgbuffer) == 0) {
                ToMainHigh_sendmsg(length, msgtype, (void*) msgbuffer);
            }
        } else {
            DEBUG_ON(UART_THREAD_DBG);
            DEBUG_OFF(UART_THREAD_DBG);
            DEBUG_ON(UART_THREAD_DBG);
            DEBUG_OFF(UART_THREAD_DBG);
            // Setup encoder message
            length = msgForMotorcontroller(msgbuffer[0], msgbuffer);
            // Send Encoder Data to Master
            start_i2c_slave_reply(length, msgbuffer);
        }
    }
}
