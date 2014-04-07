#include "maindefs.h"
#ifndef __XC8
#include <usart.h>
#else
#include <plib/usart.h>
#endif
#include "my_uart.h"
#include "my_i2c.h"

static uart_comm *uc_ptr;

void init_uart_recv(uart_comm *uc) {
    uc_ptr = uc;
    uc_ptr->Tx_buflen = 0;
}

void uart_send_int_handler() {

    if (uc_ptr->Tx_buflen == uc_ptr->msg_length) {
        PIE1bits.TX1IE = 0; // Clear TXIE to end write.
        uc_ptr->Tx_buflen = 0;
    } else {
        WriteUSART(uc_ptr->Tx_buffer[uc_ptr->Tx_buflen]);
        uc_ptr->Tx_buflen++;
    }
}

void uart_retrieve_buffer(int length, unsigned char* msgbuffer) {

    uc_ptr->Tx_buflen = 0;

    // Go Forward without a degree
    if (msgbuffer[0] == 0x01 && msgbuffer[4] == 0) {
        // Get the length of motor command.
        uc_ptr->msg_length = 2;
        uc_ptr->Tx_buffer[0] = msgbuffer[2];
        uc_ptr->Tx_buffer[1] = msgbuffer[3];
    } else if (msgbuffer[0] == 0x05) {
        // Get the length of motor command.
        uc_ptr->msg_length = 2;
        uc_ptr->Tx_buffer[0] = 0x00;
        uc_ptr->Tx_buffer[1] = 0x00;
    }
}