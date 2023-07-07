#include <Lab4 Code Files/lcd.h>
#include <Lab4 Code Files/open_interface.h>
#include <Lab4 Code Files/Timer.h>

#define ANGLE_MOD 11
#define BACKWARD_BUMP_MM 150

double move_forward(oi_t *sensor_data, double distance_mm)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(500, 500); //move forward at full speed
    while (sum < distance_mm)
    {
        oi_update(sensor_data);
        sum += sensor_data->distance; // use -> notation since pointer
    }
    oi_setWheels(0, 0); //stop
    return sum;
}

double move_backward(oi_t *sensor_data, double distance_mm)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(-500, -500); //move forward at full speed
    while (sum < distance_mm)
    {
        oi_update(sensor_data);
        sum -= sensor_data->distance; // use -> notation since pointer
    }
    oi_setWheels(0, 0); //stop
    return sum;
}

void turn_right(oi_t *sensor_data, double degrees)
{
    degrees -= ANGLE_MOD;
    double sum = 0;
    oi_setWheels(-250, 250);
    while (sum < degrees)
    {
        oi_update(sensor_data);
        sum -= sensor_data->angle;
    }
    oi_setWheels(0, 0); //stop

}

void turn_left(oi_t *sensor_data, double degrees)
{
    degrees -= ANGLE_MOD;
    double sum = 0;
    oi_setWheels(250, -250);
    while (sum < degrees)
    {
        oi_update(sensor_data);
        sum += sensor_data->angle;
    }
    oi_setWheels(0, 0); //stop
}

void bump(oi_t *sensor_data, double distance_mm)
{
    double sum = 0; // distance member in oi_t struct is type double
    int r_bump_status = 0;
    int l_bump_status = 0;
    //move forward at full speed
    oi_setWheels(500, 500);
    while (sum < distance_mm)
    {
        oi_update(sensor_data);
        sum += sensor_data->distance; // use -> notation since pointer
        r_bump_status = sensor_data->bumpRight; //update the value of the right bump sensor
        l_bump_status = sensor_data->bumpLeft; //update the value of the left bump sensor
        if (r_bump_status != 0)
        {
            oi_setWheels(0, 0);
            move_backward(sensor_data, BACKWARD_BUMP_MM);
            sum -= BACKWARD_BUMP_MM;
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_right(sensor_data, 90);
            oi_setWheels(500, 500);
        }
        if (l_bump_status != 0)
        {
            oi_setWheels(0, 0);
            move_backward(sensor_data, BACKWARD_BUMP_MM);
            sum -= BACKWARD_BUMP_MM;
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_left(sensor_data, 90);
            oi_setWheels(500, 500);
        }

    }
    oi_setWheels(0, 0); //stop

}

