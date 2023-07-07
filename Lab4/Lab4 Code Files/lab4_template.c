/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"
#include "open_interface.h"   // Functions for communicating between CyBot and Putty (via UART)
// PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#define REPLACEME 0

char button[] = "button";

int main(void)
{
    button_init();
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    cyBot_uart_init(); // Don't forget to initialize the cyBot UART before trying to use it
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()

    oi_init(sensor_data); // do this only once at start of main()

    // YOUR CODE HERE
    lcd_clear();

    while (1)
    {
        int i = 0;
        int c = button_getButton();
        // YOUR CODE HERE
        cyBot_sendByte(c);

        if (c == 4)
        {
            strcpy(button, "button 4");

        }
        else if (c == 3)
        {
            strcpy(button, "button 3");

        }
        else if (c == 2)
        {
            strcpy(button, "button 2");

        }
        else if (c == 1)
        {
            strcpy(button, "button 1");
        }
        if (c != 0)
        {
            for (i = 0; i < strlen(button); i++)
            {
                cyBot_sendByte(button[i]);
            }
        }
        oi_free(sensor_data);
    }

}
