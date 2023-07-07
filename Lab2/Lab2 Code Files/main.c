/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include <Lab2 Code Files/lcd.h>
#include <Lab2 Code Files/Timer.h>
#include <Lab2 Code Files/movement.h>
#include <Lab2 Code Files/open_interface.h>

void main()
{
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()

    oi_init(sensor_data); // do this only once at start of main()
    // the following code could be put in function move_forward()

    timer_init(); // Initialize Timer, needed before any LCD screen functions can be called
                  // and enables time functions (e.g. timer_waitMillis)

    lcd_init();   // Initialize the LCD screen.  This also clears the screen.
    cyBot_uart_init();
                    //              bump(sensor_data, 2000);
    cyBot_sendByte('d');
    oi_free(sensor_data);  // do this once at end of main()
}
