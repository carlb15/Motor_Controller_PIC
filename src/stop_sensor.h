/* 
 * File:   stop_sensor.h
 * Author: ECE4534
 *
 * Checks the stop sensor.
 * Created on May 3, 2014, 3:04 AM
 */

#ifndef STOP_SENSOR_H
#define	STOP_SENSOR_H

// Set after a right or left turn to stop rover on second pass of the start line.
int stopFlag = 0;

/**
 * Checks if the stop sensor has changed.
 * @return
 *      0 - stop
 *      1 - do nothing
 */
int checkStopSensorFlag();

#endif	/* STOP_SENSOR_H */

