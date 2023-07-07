#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Lab8 Code Files/open_interface.h>

    double move_forward(oi_t *sensor_data, double distance_mm);
    void turn_right(oi_t*sensor_data, double degrees);
    void turn_left(oi_t *sensor_data, double degrees);
    void bump(oi_t *sensor_data, double distance_mm);
    double move_backward(oi_t *sensor_data, double distance_mm);


#endif
