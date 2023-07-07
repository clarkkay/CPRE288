#ifndef movement
#define movement

    double move_forward(oi_t *sensor_data, double distance_mm);
    double move_backwards(oi_t *sensor_data, double distance_mm);
    void move_around(oi_t *sensor);
    void turn(oi_t *sensor, double degrees);

#endif
