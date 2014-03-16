#include "maindefs.h"
#include <stdio.h>
#include "uart_thread.h"
#include "my_uart.h"

// This is a "logical" thread that processes messages from the UART
// It is not a "real" thread because there is only the single main thread
// of execution on the PIC because we are not using an RTOS.

int uart_lthread(uart_thread_struct *uptr, int msgtype, int length, unsigned char *msgbuffer) {
    if (msgtype == MSGT_OVERRUN) {
        // TODO handle when buffer overruns.
    } else if (msgtype == MSGT_I2C_DATA) {
        // Send UART command to motorcontroller
        uart_retrieve_buffer(length, msgbuffer);
        // Set UART TXF interrupt flag
        PIE1bits.TX1IE = 0x1;
    }
}