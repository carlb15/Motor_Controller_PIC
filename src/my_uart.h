#ifndef __my_uart_h
#define __my_uart_h

#include "messages.h"

#define MAXUARTBUF 4
#if (MAXUARTBUF > MSGLEN)
#define MAXUARTBUF MSGLEN
#endif

typedef struct __uart_comm {
    unsigned char Tx_buffer[MAXUARTBUF];
    unsigned char Tx_buflen;
    unsigned char msg_length;
} uart_comm;

void init_uart_recv(uart_comm *);
void uart_send_int_handler();
void uart_retrieve_buffer(int length, unsigned char*);

#endif
