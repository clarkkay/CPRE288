 

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
//#include <lcd.h>
#include <movement.h>
#include <open_interface.h>
#include <Timer.h>
#include <stdio.h>
#include "string.h"
//#include "cyBot_uart.h"
//#include "cyBot_Scan.h"

void move_forward_smart(oi_t *sensor_data, double distance_mm, int move_speed);

double move_forward(oi_t *sensor_data, double distance_mm, int moveSpeed);

double move_backward(oi_t *sensor_data, double distance_mm, int moveSpeed);


void turn_right(oi_t *sensor_data, double degrees);

void turn_left(oi_t *sensor_data, double degrees);




#endif  MOVEMENT_H_ 
