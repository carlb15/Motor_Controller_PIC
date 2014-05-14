#include "stop_sensor.h"
#include "maindefs.h"
#include "interrupts.h"
#include "messages.h"

/**
 * Checks if the stop sensor is enabled.
 * @return
 */
int checkStopSensorFlag() {
    return (PORTDbits.RD3 && PORTDbits.RD4 && PORTDbits.RD5 && PORTDbits.RD6 && PORTDbits.RD7);
}