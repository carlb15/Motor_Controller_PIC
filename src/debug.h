/*
 * File:   debug.h
 * Author: ECE4534
 *
 * Created on February 10, 2014, 8:08 PM
 */

#ifndef DEBUG_H
#define DEBUG_H
#define I2C_DBG LATAbits.LATA0
#define UART_THREAD_DBG LATAbits.LATA1
#define TMR0_DBG LATAbits.LATA2
#define TMR1_DBG LATAbits.LATA3
#define MOTOR_DBG LATCbits.LATC1

// Define this to turn on instrumentation
#define DO_DEBUG
//      Use definitions to make debugging configurable


//      Define our debugging functions
#ifdef  DO_DEBUG

#define DEBUG_ON(a){ \
    a = 1; \
    }

#define DEBUG_OFF(a){ \
    a = 0; \
    }

#else
}
#define DEBUG_ON(a)
#define DEBUG_OFF(a)
#endif
#endif