#include "open_interface.h"
#include "movement.h"
#include "lcd.h"

/*
 * @Param sensor_data
 * @Param distance_mm
 * Moves the roomba forward given the distance in millimeters
 * If it detects a collision, goes into the move_around protocol
 */
    double move_forward(oi_t *sensor_data, double distance_mm) {

        double sum = 0;

        oi_setWheels(200,200); //Starts moving forward
        while(sum < distance_mm) {
            oi_update(sensor_data); //Updates the sensor
            if((sensor_data -> bumpLeft) != 0 || (sensor_data -> bumpRight) != 0) { //If it detects a bump go into move around protocol
                oi_setWheels(0,0);
                move_around(sensor_data);
                sum -= 50.0;
                sum += 400.0;
                oi_setWheels(200,200);
            } else { //Adds sensor distance to sum
                sum += sensor_data -> distance;
                lcd_printf("%f", sum);
            }
        }
        oi_setWheels(0,0); //Stops Roomba
        return sum;
    }

/*
 * @Param sensor_data
 * @Param distance_mm
 * Moves the roomba backwards given the distance in millimeters
 */
    double move_backwards(oi_t *sensor_data, double distance_mm) {
            double sum = 0;

              oi_setWheels(-100,-100); //Starts moving backwards
              while(sum > distance_mm) {
                  oi_update(sensor_data); //Updates sensor
                  sum += sensor_data -> distance; //Subtracts sensor distance from sum
               }
               oi_setWheels(0,0); //Stops Roomba
               return sum;
    }

/*
 * @Param sensor
 * @Param degrees
 * Turns the Roomba based on the given angle in degrees
 * Positive degrees to turn left, negative to turn right
 */
    void turn(oi_t *sensor, double degrees) {
        double tempDegrees = 0;
        if(degrees >= 0) { //Turns left if degrees is positive
           oi_setWheels(50,-50);
           while(degrees >= tempDegrees) {
               oi_update(sensor);
               tempDegrees += sensor -> angle; //Adds sensor angle to tempDegrees
           }
        } else { //Turns right if degrees is negative
            oi_setWheels(-50, 50);
            while(degrees <= tempDegrees) {
                oi_update(sensor);
                tempDegrees += sensor -> angle; //Adds sensor angle to tempDegrees
            }
        }
        oi_setWheels(0,0); //Stops Roomba
    }

/*
 * @Param sensor
 * Moves the Roomba backwards 150 millimeters, then turns left or right depending on what bump sensor was triggered, moves 250 millimeters, turns the opposite direction from before,
 * then continues forward
 */
    void move_around(oi_t *sensor) {
        double bumpR = sensor -> bumpRight; //Stores if bumpRight was triggered
        move_backwards(sensor, -50); //Moves Roomba backwards 150 millimeters
        if(bumpR != 0) { //If the right bumper was triggered, turns the Roomba left, moves it 250mm, then turns it right
            turn(sensor, 87.5);
            move_forward(sensor, 300);
            turn(sensor, -87.5);
            move_forward(sensor, 400);
            turn(sensor, -87.5);
            move_forward(sensor, 300);
            turn(sensor, 87.5);
        } else { //If the left bumper was triggered, turns the Roomba right, moves it 250mm, then turns if left
            turn(sensor, -87.5);
            move_forward(sensor, 300);
            turn(sensor, 87.5);
            move_forward(sensor, 400);
            turn(sensor, 87.5);
            move_forward(sensor, 300);
            turn(sensor, -87.5);
        }
    }
